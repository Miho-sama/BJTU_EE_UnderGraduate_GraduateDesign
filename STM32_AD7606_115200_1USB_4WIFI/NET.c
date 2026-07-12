// 单片机头文件
#include "stm32f10x.h"

// 网络设备驱动
#include "esp8266.h"

// 硬件驱动
#include "delay.h"
#include "uart_DMA.h"

// C库
#include <string.h>
#include <stdio.h>

#define ESP8266_WIFI_INFO "AT+CWJAP=\"Miho\",\"NULL\"\r\n"						  // wifi
#define ESP8266_ONENET_INFO "AT+CIPSTART=\"TCP\",\"mqtts.heclouds.com\",1883\r\n" // 新版OneNET地址

unsigned char esp8266_buf[128];
unsigned short esp8266_cnt = 0, esp8266_cntPre = 0;

void ESP8266_Clear(void)
{

	memset(esp8266_buf, 0, sizeof(esp8266_buf));
	esp8266_cnt = 0;
}
