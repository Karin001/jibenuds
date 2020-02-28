//-------------------------------------------------------------------------*
// 工 程 名: can base  250k                                                  *
//                *
//-----------------------------------*

#include "Includes.h"
//在此添加全局变量定义
CANMsg g_msgGet;                    //报文接收缓冲区
CANMsg g_msgSend;

void main(void)
{
	g_msgSend.IDE = 0;
	g_msgSend.RTR = 0;
	g_msgSend.data[0]  = 21;
	g_msgSend.dataLen = 8;
	g_msgSend.sendID = 0x3;
    //1 关总中断
    DisableInterrupts();
    //2 模块初始化
    MCUInit();                      //2.1 芯片初始化
    //SCIInit(1,SYSTEM_CLOCK,9600);   //2.2 UART模块初始化
    CANInit();                     //2.3 CAN模块初始化
    //IO_INIT();                      //2.4 IO模块初始化
    TIMER1_init();
    //WATCHDOG_init();                     
    //3 开放中断                           
   // EnableSCIReInt();               //3.1开放SCI接收中断
    EnableCANReInt();               //3.2开放CAN接收中断
    EnableInterrupts();             //3.3开放总中断
    //4 主循环                                                                                                              
   // SCISendN(1,sizeof(sciMsg),sciMsg);//发送"Hello! World!"   
    while (1)                      
    {   
    	
    	            	
    	         
       // WATCHDOG(); 
    }
}
