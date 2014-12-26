/***************************************************************************************
 *	FileName					:	LCD1602.c
 *	CopyRight					:	2014/07/23
 *	ModuleName					:	lcd1602 module
 *
 *	CPU							:	stc1602,HJ1602A
 *	RTOS						:
 *
 *	Create Data					:	2014/07/24
 *	Author/Corportation			:	Ray
 *
 *	Abstract Description		:	
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Data		Revised By			Item			Description
 *	1	v1.0	   	7/24		Ray
 *
 ***************************************************************************************/



/**************************************************************
*	Debug switch Section
**************************************************************/


/**************************************************************
*	Include File Section
**************************************************************/
# include <reg52.h>
# include <intrins.h>
# include "LCD1602.h"

/**************************************************************
*	Macro Define Section
**************************************************************/

/**************************************************************
*	Struct Define Section
**************************************************************/


/**************************************************************
*	Prototype Declare Section
**************************************************************/
static void is_busy();
static void delay_1ms(uint time);

/**************************************************************
*	Global Variable Declare Section
**************************************************************/
sbit lcd_rs = P1^0;
sbit lcd_rw = P1^1;
sbit lcd_en = P2^5;
sbit wela = P2^7;
sbit dula = P2^6;

/**************************************************************
*	File Static Variable Define Section
**************************************************************/


/**************************************************************
*	Function Define Section
**************************************************************/
/**
 *  @name 			void write_cmd(uchar cmd)
 *	@description  	write a command-address to LCD1602
 *	@param		 	cmd - unsigned char,the command-address	
 */
void write_cmd(uchar cmd)
{

	is_busy();
	lcd_rw = 0;
	/*
	 * 这里无忙检测亦可以成功运行，最好加上忙检测
	 */
	lcd_rs = 0;
	LCD_BUS = cmd;
	delay_1ms(5);
	lcd_en = 1;
	delay_1ms(5);
	lcd_en = 0;
	
	return;	
}

/**
 *  @name  			void write_dat(uchar dat)
 *	@description 	write a 8-bit data to LCD1602
 *	@param			dat - unsigned char,the 8-bit data
 */
void write_dat(uchar dat)
{
	is_busy();
	lcd_rw = 0;
	lcd_rs = 1;
	LCD_BUS = dat;
	delay_1ms(5);
	lcd_en = 1;
	delay_1ms(5);
	lcd_en = 0;
	
	return;	
}

/**
 *  @name			void init_1602() 	
 *	@description 	initilize the LCD1602's option
 */
void init_1602()
{
	lcd_rw = 0;
	lcd_en = 0;
	dula = 0;
	wela = 0;
	
	write_cmd(0x38);
	write_cmd(0x0c);
	write_cmd(0x06);
	write_cmd(0x01);
//	write_cmd(0x02);	
}


/**
 *  @name 			void is_busy()
 *	@description 	test LCD1602's busy-status
 */
static void is_busy()
{
	lcd_rs = 0;
	lcd_rw = 1;
	lcd_en = 1;
	_nop_();

	while(LCD_BUS&0x80)
	{
		lcd_en = 0;
		_nop_();
		lcd_en = 1;
		_nop_();	
	}
}

static void delay_1ms(uint time)
{
	uchar i;

	while(time--)
	{
		for(i=0; i<110; i++)
			;
	}
}

/**
 *  @name
 *	@description
 *	@param			
 *	@return		
 *  @notice
 */
