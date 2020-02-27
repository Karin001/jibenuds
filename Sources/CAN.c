#include "CAN.h"

//---------------------------------------------------------------------*
//函数名: CANInit                                                      *
//功  能: 初始化CAN模块                                                *
//参  数: 无                                                           *
//返  回: 无                                                           *
//说  明:                                                              *
//        (1)CAN时钟源使用芯片总线时钟，设置CAN通信频率为800KHz        *
//        (2)关闭滤波器，接收CAN总线上所有的报文                       *
//---------------------------------------------------------------------*
void CANInit(void)
{
    char sj,p;
    char t_seg1, t_seg2;

    //判断CAN模块是否启动
    if(0==CANCTL1_CANE)
    {
        //系统初始化
        CANCTL1_CANE=1;//系统初始化后CAN模块默认进入初始化状态
    } 
    else
    {
        //CAN模块已经运行
        CANCTL0_SLPRQ=1;
        while(0==CANCTL1_SLPAK);//将CAN模块置入睡眠模式
        CANCTL0_INITRQ=1;
        while(0==CANCTL1_INITAK);//将CAN模块置入初始化模式
    }
    
    //关闭滤波器                            
    CANIDMR0 = 0xFF;
    CANIDMR1 = 0xFF;
    CANIDMR2 = 0xFF;
    CANIDMR3 = 0xFF;
    CANIDMR4 = 0xFF;
    CANIDMR5 = 0xFF;
    CANIDMR6 = 0xFF;
    CANIDMR7 = 0xFF;
    
    //设置同步及波特率预分频数
    sj = (SJW-1)<<6;
    p = (BRP-1);
    CANBTR0 = (sj|p);
    //时段1和时段2 的tq个数               
    t_seg1 = (TSEG1-1);
    t_seg2 = (TSEG2-1)<<4;
    CANBTR1 = (t_seg1 | t_seg2);    
    //使能MSCAN模块,设置为一般运行模式,使用内部时钟源
    //位时间长度(通信频率倒数)=SYSTEM_CLOCK/BRP/(1+TSEG1+TSEG2) 
    CANCTL1 = 0xc0;

    // 返回一般模式运行
    CANCTL0 = 0x00;
    // 等待回到一般运行模式
    while(CANCTL1_INITAK); 
    // 等待总线时钟同步
    while(0==CANCTL0_SYNCH);   
}

//---------------------------------------------------------------------*
//函数名: CANSendMsg                                                   *
//功  能: 通过CAN模块发送一个报文                                      *
//参  数: CANMsg *sendMsgBuf 待发送的报文指针                          *
//返  回: uint8 指示是否成功发送                                       *
//说  明: 在发数据前，要定义和初始化一个报文变量，类型为CANMsg         *
//---------------------------------------------------------------------*
uint8 CANSendMsg(const CANMsg *sendMsgBuf)
{
    uint8 txEmptyBuf; //空闲发送缓冲区掩码
    uint8 i;

    // 检查数据长度
    if(sendMsgBuf->dataLen > 8)
    {
        return 0;
    }
    // 检查总线时钟
    if(0==CANCTL0_SYNCH)
    {
        return 0;
    } 

    txEmptyBuf = 0;
    do
    {
        // 寻找空闲的缓冲器
        CANTBSEL=CANTFLG;
        txEmptyBuf=CANTBSEL;
    }
    while(!txEmptyBuf); 

    // 写入标识符
    
    if(0 == sendMsgBuf->IDE)
    {
        //标准格式ID
        CANTIDR0 = (unsigned char)(sendMsgBuf->sendID>>3);
        CANTIDR1 = (unsigned char)(sendMsgBuf->sendID<<5);
    } 
    else
    {
        //扩展ID格式 
        return 0; 
    }

    //判断是否为数据帧
    if(0==sendMsgBuf->RTR)
    {
        // 写入数据帧
        for(i = 0; i < sendMsgBuf->dataLen; i++)
        {
            *((&CANTDSR0)+i) = sendMsgBuf->data[i];
        }
        // 写入数据长度
        CANTDLR = sendMsgBuf->dataLen;         
    }
    else
    {
        //远程帧
        CANTDLR = 0;
    }

    // 写入优先级
    CANTTBPR = sendMsgBuf->priority;
    // 清TXx标志，缓冲器准备发送
    CANTFLG = txEmptyBuf;//相关位写1清零
    return 1;
}

//---------------------------------------------------------------------*
//函数名: CANGetMsg                                                    *
//功  能: 接收一个CAN模块报文                                          *
//参  数: CANMsg *reMsgBuf 接收报文缓冲区首指针                        *
//返  回: uint8 指示是否成功接收                                       *
//说  明: 接收之前先定义一个接收缓冲区，类型为CANMsg                   *
//---------------------------------------------------------------------*
uint8 CANGetMsg(CANMsg *reMsgBuf)
{
    uint8 i;
    uint32 sendIDH= 0;
    uint32 sendIDL= 0;
//    uint32 idTemp;
    // 检测接收标志
    if(!(CANRFLG&0x01))
    return 0;
  
    // 检测 CAN协议报文模式 （一般/扩展） 标识符
    // 读出标识符
    if(0 == (CANRIDR1&0x08))
    {  
         //收到标准ID格式
    	reMsgBuf->sendID = (uint32)(CANRIDR0<<3) | 
    	            (uint32)(CANRIDR1>>5);
        
    } 
    else
    {
        //扩展格式ID
        sendIDH =(uint32)(CANRIDR0<<6)|
        (uint32)((CANRIDR1>>5)<<3)|
        (uint32)((CANRIDR1<<5)>>5);
        sendIDL =(uint32)(CANRIDR2<<7)|
        (uint32)(CANRIDR3>>1);   
        reMsgBuf->sendID = (sendIDH<<15) |sendIDL ;           

        reMsgBuf->RTR=CANRIDR3_RTR;
        reMsgBuf->IDE=1; 
    }

    //判断是否为数据帧
    if(0==reMsgBuf->RTR)
    {
        // 读取数据帧长度 
        reMsgBuf->dataLen = CANRDLR_DLC;

        // 读取数据
        for(i = 0; i < reMsgBuf->dataLen&&i<8; i++)
        reMsgBuf->data[i] = *((&CANRDSR0)+i);
    }
    else
    {
        //远程帧
        reMsgBuf->dataLen = 0;
    }

    // 清 RXF 标志位 (缓冲器准备接收)
    CANRFLG = 0x01;               //相关位写1清零
    
    return 1;
}
