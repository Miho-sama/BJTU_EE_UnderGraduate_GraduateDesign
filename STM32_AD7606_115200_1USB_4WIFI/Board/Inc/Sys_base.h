#ifndef __SYS_BASE_H  
#define __SYS_BASE_H

//#define SYSTICK_IST_EN
#define SYSTICK_DELAY_EN

#define Stk_COUNTFLAG 0x00010000	   //Returns 1 if timer counted to 0 since last time this was read.
#define Stk_CLKSOURCE 0X00000004	  //   0: AHB/8       1: Processor clock (AHB)
#define Stk_TICKINT   0x00000002      //SysTick exception request enable   ''1: Counting down to zero to asserts the SysTick exception request.
#define Stk_ENABLE	  0x00000001      // Counter enable   1: Counter enabled

void Systick_Init(void);
void Delay_ms(u16 Nms);
void Delay_us(u32 Nus);




#endif 
