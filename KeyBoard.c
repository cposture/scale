/***************************************************************************************
 *	FileName					:	KeyBoard.C
 *	CopyRight					:	2014/08/10
 *	ModuleName					:	KeyBoard
 *
 *	CPU							:
 *	RTOS						:
 *
 *	Create Data					:	2014/08/10
 *	Author/Corportation			:	Zhuo
 *
 *	Abstract Description		:	此文件提供矩阵键盘的使用函数
 *									1. 使用该文件需修改连接矩阵键盘IO口的宏定义，KEY_BUS
 *									2. 此文件使用循环等待按键弹起，可能导致响应时间过长
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Data		Revised By			Item			Description
 *	1	V1.0		2014/08/10	ZhuoJianHuan		All				建立文件
 *
 ***************************************************************************************/

/**************************************************************
*	Debug switch Section
**************************************************************/
#define D_DISP_BASE
/**************************************************************
*	Include File Section
**************************************************************/
#include <reg52.h>
#include "KeyBoard.h"

/**************************************************************
*	Macro Define Section
**************************************************************/
#define KEY_BUS P3

/**************************************************************
*	Struct Define Section
**************************************************************/


/**************************************************************
*	Prototype Declare Section
**************************************************************/

/**************************************************************
*	Global Variable Declare Section
**************************************************************/


/**************************************************************
*	File Static Variable Define Section
**************************************************************/

/**************************************************************
*	Function Define Section
**************************************************************/
/**
 *	@description	提供一个较为粗糙的毫秒级延迟函数
 *	@param			传入的延迟时间
 *	@return	
 */
static void delay_KEY(unsigned int z)
{
	unsigned int x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}


/**
 *	@name			unsigned char keyCheck_KEY()
 *	@description	检测单个键按下的函数，多个按键按下时，返回第一个按下的键
 *	@param			存储按键的变量，低四位为相对应按下的键(0~f)
 *	@return			0，表示无键按下，1，表示有键按下，
 */
char keyScan_one_KEY(unsigned char *re){

	unsigned char res = 0x00;
	unsigned char x,y;					//两个循环所用
	unsigned char j	= 0x10;				//IO设置辅助
	unsigned char h;					//
	
	//扫描第一行
	for(x=0; x<4; x++){					//共扫描四行
		KEY_BUS	= ~j;					//第一次时KEY_BUS = 0xef
		res		= KEY_BUS & 0x0f;		//获得线与结果，初次获得
		if(res!=0x0f){
			delay_KEY(10);					//消抖
			res		= KEY_BUS & 0x0f;		//获得线与结果，再次确认
			if(res!=0x0f){
				h = 0x01;					//逐列扫描。重置
				for(y=0; y<4; y++){
					if(0xff !=(res | ~h)){
						*re = x*4+y;
						while(0xff !=(KEY_BUS & 0x0f | ~h));
						return 1;	//有按键则返回
					}
					h <<= 1;						
				}//end of for(y)
			}//end of if(res!=0x0f)
		}//end of if(res!=0x0f)
		j <<= 1;
	}//end of for(x)
	return 0;								//无按键，返回0
}


/**
 *	@description	示例函数
 *//*
void main(){

	unsigned char re=0x00;
	while(1){
		while(!(re=keyScan_one_KEY()));		//直到有键按下
		P1 = re;							//显示返回的按键号
	}
}
//*/