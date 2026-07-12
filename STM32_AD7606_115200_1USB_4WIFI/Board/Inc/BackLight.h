/****************************************************************************
* Copyright (C), 2009-2010, www.armfly.com
*
* 文件名: BackLight.h
* 内容简述: 头文件
*
* 文件历史:
* 版本号  日期       作者    说明
* v0.1    2009-12-28 armfly  创建该文件
*
*/

#ifndef __BACKLIGHT_H
#define __BACKLIGHT_H

#define BRIGHT_MAX		255
#define BRIGHT_MIN		0
#define BRIGHT_DEFAULT	200

#define BRIGHT_STEP		5

void SetBackLight(uint8_t _bright);


#endif


