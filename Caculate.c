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
 *	Abstract Description		:	��ADֵ��������
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
 *	@description	���ݾ�ADת������������������
 *	@param			dig - unsigned long,24λADת������		
 *	@return			float - ����������������λΪkg������������
 *  @notice			�����������Ǿ�HX711 24λADת��������������
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
 *	@description 	����x��n����
 *	@param			x - unsigned char ,����
 					n - unsigned char ,����
 *	@return			x^n�η�	
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
