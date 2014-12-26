/***************************************************************************************
 *	FileName					:	Caculate.c	
 *	CopyRight					:	2014/07/23
 *	ModuleName					:	
 *
 *	CPU							:
 *	RTOS						:
 *
 *	Create Data					:	2014/08/16
 *	Author/Corportation			:	Ray
 *
 *	Abstract Description		:	由AD值计算重量
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Date		Revised By			Item			Description
 *	1	v1.0		8/16		Ray	
 *
 ***************************************************************************************/



/**************************************************************
*	Debug switch Section
**************************************************************/


/**************************************************************
*	Include File Section
**************************************************************/
# include <reg52.h>
# include "Caculate.h"

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
static ulong pow(uchar x,uchar n);

/**************************************************************
*	File Static Variable Define Section
**************************************************************/


/**************************************************************
*	Function Define Section
**************************************************************/
/**
 *  @name			float Caculate_weight(ulong dig)
 *	@description	根据经AD转换的数字量计算重量
 *	@param			dig - unsigned long,24位AD转换数字		
 *	@return			float - 计算所得质量，单位为kg，浮点型数据
 *  @notice			所用数字量是经HX711 24位AD转换而来的数字量
 */

float Caculate_weight(ulong dig)
{
	ulong num = pow(2,RATE);
	float max_dig = (MAX_VOLTAGE*1*0.001*AMPLIFICATION/MAX_VOLTAGE*num);
	float weight = dig/max_dig*20;		

	return weight; 			
}

/**
 *  @name			uint pow(uint x,uchar rate)
 *	@description 	计算x的n次幂
 *	@param			x - unsigned char ,基数
 					n - unsigned char ,次幂
 *	@return			x^n次方	
 */
static ulong pow(uchar x,uchar n)
{
	uchar i;
	ulong sum = 1;

	for(i=0; i<n; i++)
		sum *= x;

	return sum;		
}
/**
 *  @name
 *	@description
 *	@param			
 *	@return		
 *  @notice
 */
