【版本】
（1）V0.1
更新：创建文件
 (2) V0.2
更新：封装电子秤，优化其显示模块

【重要位】
//HX711模块需要的引脚
sbit ADOUT =P1^5;	//数据输出端DT
sbit ADSCK =P0^0;	//时钟信号输入端SCK

//LCD1602需要的引脚
sbit lcd_rs = P1^0;
sbit lcd_rw = P1^1;
sbit lcd_en = P2^5;

【注意】


【几个重要宏】
# define LCD_BUS P0				//LCD1602的数据总线
#define KEY_BUS P3				//矩阵键盘的总线
	
【几个重要函数】
（1）
/**
 *  @name			void Scale();
 *	@description 	实现电子秤功能的函数
 *	@param			无
 *	@return			无
 *  @notice			需要用到LCD1602，所以必须先初始化。在此函数内会依次调用其他模块的函数实现功能
 */

【Demo】
（1）
int main(void)
{		
	init_1602();

	while(1)
	{
		Scale();
	}

	return 0;
}

