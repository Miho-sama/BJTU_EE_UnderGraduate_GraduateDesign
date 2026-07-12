#ifndef __UART_H  
#define __UART_H

void USART1_IRQHandler(void);
extern void USART1_Configuration(void);
extern void UART_parameter_Init(void);
extern void USART_String(uint8_t *p);


//////////////////////////////////////////////////////////////////
typedef struct
{
//	USART_TypeDef *uart;		//指定串口
	uint8_t *pTxBuf;			//发送缓冲区 
	uint8_t *pRxBuf;			//接收缓冲区 
	uint32_t TxCounter;	    	//发送计数 
	uint32_t RxCounter;		    //接收计数
	uint32_t ErrorCounter;	    //错误计数
	uint32_t MaxError;			//记录最大错误个数
	uint32_t Error_Pack;        //记录错误帧个数
	uint32_t TxSend_Pack;       //发送帧个数
	uint32_t TxSend_Pack_counter;//发送帧计数
	uint32_t RxSend_Pack_counter;//接收帧计数
	uint32_t Pack_Size;         //帧容量
}UART_parameter;
////////////////////////////////////////////////////////////////////////////

#endif 



