#include "stm32f10x.h"
#include "uart.h"
#include "ili9320.h"
#include <stdio.h>
#include <string.h>

uint8_t TxBuffer1[101]={"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzUUUUUUUUUUUUUUUUUUUU"};
uint8_t RxBuffer1[101]={0};


UART_parameter Uart1;

void UART_parameter_Init(void)					
{
		
	Uart1.Pack_Size=100;
	Uart1.TxSend_Pack=10;
	Uart1.TxSend_Pack_counter=0;
	Uart1.RxSend_Pack_counter=0;
	Uart1.ErrorCounter=0;
	Uart1.Error_Pack=0;
	Uart1.MaxError=0;
	Uart1.RxCounter=0;
	Uart1.TxCounter=0;
	Uart1.pRxBuf=RxBuffer1;
	Uart1.pTxBuf=TxBuffer1;
}

void USART1_Configuration(void)
{

	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

  

	/* 第1步：打开GPIO和USART部件的时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	/* 第2步：将USART Tx的GPIO配置为推挽复用模式 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* 第3步：将USART Rx的GPIO配置为浮空输入模式
		由于CPU复位后，GPIO缺省都是浮空输入模式，因此下面这个步骤不是必须的
		但是，我还是建议加上便于阅读，并且防止其它地方修改了这个口线的设置参数
	*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/*  第3步已经做了，因此这步可以不做
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	*/
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	/* 第4步：配置USART参数
	    - BaudRate = 115200 baud
	    - Word Length = 8 Bits
	    - One Stop Bit
	    - No parity
	    - Hardware flow control disabled (RTS and CTS signals)
	    - Receive and transmit enabled
	*/
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;


	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);

	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	  //Uart1接收中断
	USART_ClearITPendingBit(USART1,USART_IT_CTS|USART_IT_LBD|USART_IT_TC|USART_IT_RXNE);

	/* 第5步：使能 USART， 配置完毕 */
	USART_Cmd(USART1, ENABLE);

	/* CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
		如下语句解决第1个字节无法正确发送出去的问题 */
	USART_ClearFlag(USART1, USART_FLAG_TC);     /* 清发送外城标志，Transmission Complete flag */
}


/////////////////////////////////////////////////////////////////////////////////////////////////
void USART_String(uint8_t *p)
{
	while(*p)
	{
		USART_SendData(USART1,*(p++));	
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)== RESET);
		Uart1.TxCounter++;
	}

}
///////////////////////////////////////////////////////////////////////////////////////////////////
 /**
  * @brief  This function handles USARTz global interrupt request.
  * @param  None
  * @retval None
  */

void USART1_IRQHandler(void)
{
  
#ifdef SEND

  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {

    Uart1.pRxBuf[Uart1.RxCounter++] = USART_ReceiveData(USART1);

	if( (Uart1.pRxBuf[Uart1.RxCounter-1] != Uart1.pTxBuf[Uart1.RxCounter-1]))//||( Uart1.TxCounter!=Uart1.RxCounter) )
	{
		 Uart1.ErrorCounter++;
	}
	if(Uart1.RxCounter == Uart1.Pack_Size)
	{
		Uart1.RxCounter=0;
		Uart1.RxSend_Pack_counter++;
		Uart1.TxCounter=0;
		ili9320_DisplayStringLine(Line5, " Error NUM is",Red,White);
		ili9320_Display_NUM(15,Line5,(uint32_t)Uart1.ErrorCounter,Black,White);

		ili9320_DisplayStringLine(Line8, "    Recieve Pack is  ",Red,White);
		ili9320_Display_NUM(23,Line8,(uint32_t)Uart1.RxSend_Pack_counter,Black,White);
		

		if(Uart1.ErrorCounter>Uart1.MaxError)
		{
			Uart1.MaxError=Uart1.ErrorCounter;
			ili9320_DisplayStringLine(Line5, "                        Max Error is",Red,White);
			ili9320_Display_NUM(35,Line5,(uint32_t)Uart1.MaxError,Black,White);
		}
		Uart1.ErrorCounter=0;
/*
< 0 buf1 less than buf2 
0 buf1 identical to buf2 
> 0 buf1 greater than buf2 
*/
		if(memcmp(Uart1.pRxBuf, Uart1.pTxBuf, Uart1.Pack_Size)!=0)
		{
			ili9320_DisplayStringLine(Line3, "    ERROR Pack is ",Red,White);
			Uart1.Error_Pack++;
			ili9320_Display_NUM(35,Line3,(uint32_t)Uart1.Error_Pack,Black,White);
		}		
	}
 else
  {
  	USART_ClearITPendingBit(USART1,USART_IT_CTS|USART_IT_LBD|USART_IT_TC|USART_IT_RXNE);
  }	
 } 

#else
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  		{

			Uart1.pRxBuf[Uart1.RxCounter++] = USART_ReceiveData(USART1);;
			if(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_8)==Bit_RESET)
			{
				Uart1.pRxBuf[Uart1.RxCounter-1]+=1;	
			}
			USART_SendData(USART1,Uart1.pRxBuf[Uart1.RxCounter-1]);
			if(Uart1.RxCounter==Uart1.Pack_Size)  //满足一个帧容量
			{
				Uart1.RxCounter=0;
			//	Uart1.RxSend_Pack_counter++;
				if(memcmp(Uart1.pRxBuf, Uart1.pTxBuf, Uart1.Pack_Size)!=0) //接收一帧数据与发送数据做比较
				{

					Uart1.ErrorCounter++;
					
					GPIO_Write(GPIOF,~((Uart1.ErrorCounter<<6)&0x01c0));
					
				}		

					
			}
		}
	else
		{
 	 		USART_ClearITPendingBit(USART1,USART_IT_CTS|USART_IT_LBD|USART_IT_TC|USART_IT_RXNE);
			USART_ClearFlag(USART1,USART_IT_CTS|USART_IT_LBD|USART_IT_TC|USART_IT_RXNE);
		}	
 
#endif


}
															 