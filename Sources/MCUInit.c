//--------------------------------------------------------------------------*
// �ļ���:  MCUInit.c (DZ60ϵͳ��ʼ���ӳ���)                                *
// ˵  ��: ϵͳ��ʼ������,����MCGC1��MCGC2�Ĵ���,SOPT1��SOPT2�Ĵ�������,����*
//         ������f = 4MHz,�����ڲ�����ʱ��Ƶ��f = 16MHz                     *
//--------------------------------------------------------------------------*
#include "MCUInit.h"    //ӳ��Ĵ�����ַͷ�ļ�

void MCUInit(void)
{
/* disable COP */
  SOPT1 = 0x00;     /* disable COP, enable stop mode */

  /* Init Clock, Use PLL Engaged External mode, from 8MHz crystal -> 16 MHz bus */  
  MCGC2 = 0x36;
  while (!MCGSC_OSCINIT);

  MCGC1 = 0xB8;
  while (!MCGSC_IREFST);       
  while(MCGSC_CLKST != 2);
  
  MCGC1 = 0x90;
  MCGC3 = 0x44;
  while(!MCGSC_PLLST);

  while (!MCGSC_LOCK);

  MCGC1 = 0x10;
  while(MCGSC_CLKST != 3);
  
  MCGC2_BDIV = 0; 
}
void IO_INIT(void)
{

    PTDD  =0x00;  //  Hignt 
    PTDDD =0xFF;  //   out LED 
    
    PTED_PTED2 = 0x00;
    PTED_PTED3 = 0x00;
    PTCD_PTCD0 = 0x00;
    PTCD_PTCD1 = 0x00;
    PTEDD_PTEDD2 =0x1;
    PTEDD_PTEDD3 =0x1;
    PTCDD_PTCDD0 =0x1;
    PTCDD_PTCDD1 =0x1;
}
void TIMER1_init(void) 
{
// Timer1 Overflow every 1ms
  TPM1MODH = 0x41;
  TPM1MODL = 0x1a;
  //6e-5 ms /tick
  
  // Enable Interrupt Overflow Timer1 and 
  // select bus clock as clock source. Prescaler Divisor = 1
  TPM1SC = 0x48;
}  
void WATCHDOG_init() 
{
    SOPT1 = 0xc0;
    SOPT2 = 0x00;
}

void WATCHDOG()
{
 
      SRS = 0x55;                         /* Reset watchdog counter write 55, AA */
      SRS = 0xAA;
}
