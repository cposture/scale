���汾��
��1��V0.1
���£������ļ�
 (2) V0.2
���£���װ���ӳӣ��Ż�����ʾģ��

����Ҫλ��
//HX711ģ����Ҫ������
sbit ADOUT =P1^5;	//���������DT
sbit ADSCK =P0^0;	//ʱ���ź������SCK

//LCD1602��Ҫ������
sbit lcd_rs = P1^0;
sbit lcd_rw = P1^1;
sbit lcd_en = P2^5;

��ע�⡿


��������Ҫ�꡿
# define LCD_BUS P0				//LCD1602����������
#define KEY_BUS P3				//������̵�����
	
��������Ҫ������
��1��
/**
 *  @name			void Scale();
 *	@description 	ʵ�ֵ��ӳӹ��ܵĺ���
 *	@param			��
 *	@return			��
 *  @notice			��Ҫ�õ�LCD1602�����Ա����ȳ�ʼ�����ڴ˺����ڻ����ε�������ģ��ĺ���ʵ�ֹ���
 */

��Demo��
��1��
int main(void)
{		
	init_1602();

	while(1)
	{
		Scale();
	}

	return 0;
}

