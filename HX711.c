/***************************************************************************************
 *	FileName					:	HX711.c	
 *	CopyRight					:	
 *	ModuleName					:	称重运放AD模块
 *
 *	CPU							:
 *	RTOS						:
 *
 *	Create Date					:	2014/08/17
 *	Author/Corportation			:	ChenJiaqi
 *
 *	Abstract Description		:	
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Date		Revised By			Item			Description
 *	1	V1.0		2014/08/17	ChenJiaqi			All				Create the file
 *
 ***************************************************************************************/



/**************************************************************
*	Debug switch Section
**************************************************************/ 

/**************************************************************
*	Include File Section
**************************************************************/
#include "HX711.h"
#include <INTRINS.h>
#include <reg52.h>
/**************************************************************
*	Macro Define Section
**************************************************************/

/**************************************************************
*	Struct Define Section
**************************************************************/

/**************************************************************
*	Prototype Declare Section
**************************************************************/

/**************************************************************
*	Global Variable Declare Section
**************************************************************/
sbit ADOUT =P2^0;			//数据输出端DT
sbit ADSCK =P2^1;			//时钟信号输入端SCK
/**************************************************************
*	File Static Variable Define Section
**************************************************************/

/**************************************************************
*	Function Define Section
**************************************************************/
/**
 *	Name...........:HX711_GetAD
 *	description....:称重运放AD函数
 *	param..........:无
 *	return.........:24位AD转换结果，类型为unsigned long
 *	precondition...:
 *	postcondition..:
 */
ulong HX711_GetAD()
{
	unsigned long	Count;
	unsigned char	i;
	ADSCK=0;   					//使能AD（PD_SCK 置低）
	Count=0;
	//_nop_();_nop_();_nop_();_nop_();
	while(ADOUT);  				//AD转换未结束则等待，否则开始读取
	for(i=0;i<24;i++)
	{
		ADSCK=1;   				//PD_SCK 置高（发送脉冲）
		Count=Count<<1; 		//下降沿来时变量Count左移一位，右侧补零
		ADSCK=0;   				//PD_SCK 置低
		if(ADOUT) 
			Count++;
	}
	ADSCK=1;
	Count=Count^0x800000;		//第25个脉冲下降沿来时，转换数据
	ADSCK=0;
	/*
	for(;flag>0;flag--)			//根据flag产生第26或27脉冲
	{
		ADSCK=1;
		_nop_();
		ADSCK=0; 	
	}
	*/
	return Count;
}