#include "CAN.h"

//---------------------------------------------------------------------*
//������: CANInit                                                      *
//��  ��: ��ʼ��CANģ��                                                *
//��  ��: ��                                                           *
//��  ��: ��                                                           *
//˵  ��:                                                              *
//        (1)CANʱ��Դʹ��оƬ����ʱ�ӣ�����CANͨ��Ƶ��Ϊ800KHz        *
//        (2)�ر��˲���������CAN���������еı���                       *
//---------------------------------------------------------------------*
void CANInit(void)
{
    char sj,p;
    char t_seg1, t_seg2;

    //�ж�CANģ���Ƿ�����
    if(0==CANCTL1_CANE)
    {
        //ϵͳ��ʼ��
        CANCTL1_CANE=1;//ϵͳ��ʼ����CANģ��Ĭ�Ͻ����ʼ��״̬
    } 
    else
    {
        //CANģ���Ѿ�����
        CANCTL0_SLPRQ=1;
        while(0==CANCTL1_SLPAK);//��CANģ������˯��ģʽ
        CANCTL0_INITRQ=1;
        while(0==CANCTL1_INITAK);//��CANģ�������ʼ��ģʽ
    }
    
    //�ر��˲���                            
    CANIDMR0 = 0xFF;
    CANIDMR1 = 0xFF;
    CANIDMR2 = 0xFF;
    CANIDMR3 = 0xFF;
    CANIDMR4 = 0xFF;
    CANIDMR5 = 0xFF;
    CANIDMR6 = 0xFF;
    CANIDMR7 = 0xFF;
    
    //����ͬ����������Ԥ��Ƶ��
    sj = (SJW-1)<<6;
    p = (BRP-1);
    CANBTR0 = (sj|p);
    //ʱ��1��ʱ��2 ��tq����               
    t_seg1 = (TSEG1-1);
    t_seg2 = (TSEG2-1)<<4;
    CANBTR1 = (t_seg1 | t_seg2);    
    //ʹ��MSCANģ��,����Ϊһ������ģʽ,ʹ���ڲ�ʱ��Դ
    //λʱ�䳤��(ͨ��Ƶ�ʵ���)=SYSTEM_CLOCK/BRP/(1+TSEG1+TSEG2) 
    CANCTL1 = 0xc0;

    // ����һ��ģʽ����
    CANCTL0 = 0x00;
    // �ȴ��ص�һ������ģʽ
    while(CANCTL1_INITAK); 
    // �ȴ�����ʱ��ͬ��
    while(0==CANCTL0_SYNCH);   
}

//---------------------------------------------------------------------*
//������: CANSendMsg                                                   *
//��  ��: ͨ��CANģ�鷢��һ������                                      *
//��  ��: CANMsg *sendMsgBuf �����͵ı���ָ��                          *
//��  ��: uint8 ָʾ�Ƿ�ɹ�����                                       *
//˵  ��: �ڷ�����ǰ��Ҫ����ͳ�ʼ��һ�����ı���������ΪCANMsg         *
//---------------------------------------------------------------------*
uint8 CANSendMsg(const CANMsg *sendMsgBuf)
{
    uint8 txEmptyBuf; //���з��ͻ���������
    uint8 i;

    // ������ݳ���
    if(sendMsgBuf->dataLen > 8)
    {
        return 0;
    }
    // �������ʱ��
    if(0==CANCTL0_SYNCH)
    {
        return 0;
    } 

    txEmptyBuf = 0;
    do
    {
        // Ѱ�ҿ��еĻ�����
        CANTBSEL=CANTFLG;
        txEmptyBuf=CANTBSEL;
    }
    while(!txEmptyBuf); 

    // д���ʶ��
    
    if(0 == sendMsgBuf->IDE)
    {
        //��׼��ʽID
        CANTIDR0 = (unsigned char)(sendMsgBuf->sendID>>3);
        CANTIDR1 = (unsigned char)(sendMsgBuf->sendID<<5);
    } 
    else
    {
        //��չID��ʽ 
        return 0; 
    }

    //�ж��Ƿ�Ϊ����֡
    if(0==sendMsgBuf->RTR)
    {
        // д������֡
        for(i = 0; i < sendMsgBuf->dataLen; i++)
        {
            *((&CANTDSR0)+i) = sendMsgBuf->data[i];
        }
        // д�����ݳ���
        CANTDLR = sendMsgBuf->dataLen;         
    }
    else
    {
        //Զ��֡
        CANTDLR = 0;
    }

    // д�����ȼ�
    CANTTBPR = sendMsgBuf->priority;
    // ��TXx��־��������׼������
    CANTFLG = txEmptyBuf;//���λд1����
    return 1;
}

//---------------------------------------------------------------------*
//������: CANGetMsg                                                    *
//��  ��: ����һ��CANģ�鱨��                                          *
//��  ��: CANMsg *reMsgBuf ���ձ��Ļ�������ָ��                        *
//��  ��: uint8 ָʾ�Ƿ�ɹ�����                                       *
//˵  ��: ����֮ǰ�ȶ���һ�����ջ�����������ΪCANMsg                   *
//---------------------------------------------------------------------*
uint8 CANGetMsg(CANMsg *reMsgBuf)
{
    uint8 i;
    uint32 sendIDH= 0;
    uint32 sendIDL= 0;
//    uint32 idTemp;
    // �����ձ�־
    if(!(CANRFLG&0x01))
    return 0;
  
    // ��� CANЭ�鱨��ģʽ ��һ��/��չ�� ��ʶ��
    // ������ʶ��
    if(0 == (CANRIDR1&0x08))
    {  
         //�յ���׼ID��ʽ
    	reMsgBuf->sendID = (uint32)(CANRIDR0<<3) | 
    	            (uint32)(CANRIDR1>>5);
        
    } 
    else
    {
        //��չ��ʽID
        sendIDH =(uint32)(CANRIDR0<<6)|
        (uint32)((CANRIDR1>>5)<<3)|
        (uint32)((CANRIDR1<<5)>>5);
        sendIDL =(uint32)(CANRIDR2<<7)|
        (uint32)(CANRIDR3>>1);   
        reMsgBuf->sendID = (sendIDH<<15) |sendIDL ;           

        reMsgBuf->RTR=CANRIDR3_RTR;
        reMsgBuf->IDE=1; 
    }

    //�ж��Ƿ�Ϊ����֡
    if(0==reMsgBuf->RTR)
    {
        // ��ȡ����֡���� 
        reMsgBuf->dataLen = CANRDLR_DLC;

        // ��ȡ����
        for(i = 0; i < reMsgBuf->dataLen&&i<8; i++)
        reMsgBuf->data[i] = *((&CANRDSR0)+i);
    }
    else
    {
        //Զ��֡
        reMsgBuf->dataLen = 0;
    }

    // �� RXF ��־λ (������׼������)
    CANRFLG = 0x01;               //���λд1����
    
    return 1;
}
