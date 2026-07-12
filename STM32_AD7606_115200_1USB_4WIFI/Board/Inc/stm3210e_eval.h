/**
  ******************************************************************************
  * @file    stm3210e_eval.h
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    06/19/2009
  * @brief   This file contains definitions for STM3210E_EVAL's Leds, push-buttons
  *          and COM ports hardware resources.  
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM3210E_EVAL_H
#define __STM3210E_EVAL_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
	 
#define LEDn                        3
	 
#define LED1_GPIO_PORT              GPIOF
#define LED1_GPIO_CLK               RCC_APB2Periph_GPIOF
#define LED1_GPIO_PIN               GPIO_Pin_10
  
#define LED2_GPIO_PORT              GPIOB
#define LED2_GPIO_CLK               RCC_APB2Periph_GPIOB
#define LED2_GPIO_PIN               GPIO_Pin_1
  
#define LED3_GPIO_PORT              GPIOF
#define LED3_GPIO_CLK               RCC_APB2Periph_GPIOF
#define LED3_GPIO_PIN               GPIO_Pin_11
  


#define BUTTONn                    3
/**
 * @brief S1
 */
#define S1_PORT          GPIOF
#define S1_CLK           RCC_APB2Periph_GPIOF
#define S1_PIN           GPIO_Pin_12
#define S1_EXTI_LINE     EXTI_Line12
#define S1_PORT_SOURCE   GPIO_PortSourceGPIOF
#define S1_PIN_SOURCE    GPIO_PinSource12
#define S1_IRQn          EXTI15_10_IRQn 

/**
 * @brief S2
 */
#define S2_PORT          GPIOF
#define S2_CLK           RCC_APB2Periph_GPIOF
#define S2_PIN           GPIO_Pin_13
#define S2_EXTI_LINE     EXTI_Line13
#define S2_PORT_SOURCE   GPIO_PortSourceGPIOF
#define S2_PIN_SOURCE    GPIO_PinSource13
#define S2_IRQn   EXTI15_10_IRQn 

 
/**
 * @brief S3
 */  
#define S3_PORT             GPIOF
#define S3_CLK              RCC_APB2Periph_GPIOF
#define S3_PIN              GPIO_Pin_14
#define S3_EXTI_LINE        EXTI_Line14
#define S3_PORT_SOURCE      GPIO_PortSourceGPIOF
#define S3_PIN_SOURCE       GPIO_PinSource14
#define S3_IRQn             EXTI15_10_IRQn   

       
/////////////////////////////////////////////////////////////
//这里用于检测GPS 的1PPS信号是否接入。 目前在单片机的PB7口，有接入，则1PPS为 100ms的低电平，平时为高电平
/*
#define GPS_BUTTON_PORT          GPIOB
#define GPS_BUTTON_CLK           RCC_APB2Periph_GPIOB
#define GPS_BUTTON_PIN           GPIO_Pin_7
#define GPS_BUTTON_EXTI_LINE     EXTI_Line7
#define GPS_BUTTON_PORT_SOURCE   GPIO_PortSourceGPIOB
#define GPS_BUTTON_PIN_SOURCE    GPIO_PinSource7
#define GPS_BUTTON_IRQn          EXTI9_5_IRQn 
*/

#ifdef __cplusplus
}
#endif
  
#endif /* __STM3210E_EVAL_H */
/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
