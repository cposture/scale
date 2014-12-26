/***************************************************************************************
 *	File Name				:	Scale.h	
 *	CopyRight				:
 *	ModuleName				:	���ӳ�ͷ�ļ�	
 *
 *	CPU						:
 *	RTOS					:
 *
 *	Create Data				:	2014/12/26
 *	Author/Corportation		:	Ray
 *
 *	Abstract Description	:	this will be used for "Scale.c" 
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Data		Revised By			Item			Description
 *	1	v1.0		12/26		Ray									Create this files
 *
 ***************************************************************************************/


/**************************************************************
*	Multi-Include-Prevent Section
**************************************************************/
#ifndef SCALE_H
#define SCALE_H


/**************************************************************
*	Debug switch Section
**************************************************************/



/**************************************************************
*	Include File Section
**************************************************************/
# include "HX711.h"
# include "Keyboard.h"
# include "LCD1602.h"
# include <stdio.h>
# include "Caculate.h"

/**************************************************************
*	Macro Define Section
**************************************************************/
# define uchar unsigned char
# define uint unsigned int
# define ulong unsigned long

/**************************************************************
*	Struct Define Section
**************************************************************/



/**************************************************************
*	Prototype Declare Section
**************************************************************/
static void Display_LCD(float weight);
static void Key_process(float *pzero,ulong dig,uchar key);
static float transform_to_digital();

extern void Scale();		//���ⲿʹ�õ�ֻ���������

/**************************************************************
*	End-Multi-Include-Prevent Section
**************************************************************/
#endif