//-------------------------------------------------------------------------*
// �� �� ��: CAN_Recv                                                      *
// Ӳ������: ���Ӵ���1��������PC���ͽ��յ���CAN����                        *
// ��������: CANģ���жϷ�ʽ����CAN�����е����ݣ���������ͨ�����ڷ��͸�PC  *
// Ŀ    ��: ��������CANͨ�ŵĻ���֪ʶ                                     *
// ˵    ��: CANͨ��Ƶ��ѡ��Ϊ800k,ʹ��SCI1ͨ������Ϊ9600                  *
//----------------���ݴ�ѧ��˼����Ƕ��ʽϵͳʵ����2010��-------------------*

#include "Includes.h"
//�ڴ����ȫ�ֱ�������
CANMsg g_msgGet;                    //���Ľ��ջ�����
CANMsg g_msgSend;
uint8 tag = 0;
uint8 timer_off = 0;
uint16 timer_count = 0;
void main(void)
{
	g_msgSend.IDE = 0;
	g_msgSend.RTR = 0;
	g_msgSend.data[0]  = 21;
	g_msgSend.dataLen = 8;
	g_msgSend.sendID = 0x3;
    //1 �����ж�
    DisableInterrupts();
    //2 ģ���ʼ��
    MCUInit();                      //2.1 оƬ��ʼ��
    //SCIInit(1,SYSTEM_CLOCK,9600);   //2.2 UARTģ���ʼ��
    CANInit();                     //2.3 CANģ���ʼ��
    IO_INIT();                      //2.4 IOģ���ʼ��
    TIMER1_init();
    //WATCHDOG_init();                     
    //3 �����ж�                           
   // EnableSCIReInt();               //3.1����SCI�����ж�
    EnableCANReInt();               //3.2����CAN�����ж�
    EnableInterrupts();             //3.3�������ж�
    //4 ��ѭ��                                                                                                              
   // SCISendN(1,sizeof(sciMsg),sciMsg);//����"Hello! World!"   
    while (1)                      
    {   
    	
    	            	
    	         
       // WATCHDOG(); 
    }
}
