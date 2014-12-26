/***************************************************************************************
 *	FileName					:	Scale.c
 *	CopyRight					:	2014/07/23
 *	ModuleName					:	
 *
 *	CPU							:
 *	RTOS						:
 *
 *	Create Data					:	2014/07/23
 *	Author/Corportation			:	Ray
 *
 *	Abstract Description		:	
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Data		Revised By			Item			Description
 *	1	v1.0		8/17		Ray	
 *	2	v1.1		12/26		Ray									�����ӳӹ��ܷ�װ��һ��ģ�飬���Ż���ʾ
 *
 ***************************************************************************************/



/**************************************************************
*	Debug switch Section
**************************************************************/


/**************************************************************
*	Include File Section
**************************************************************/
# include <reg52.h>
# include "Scale.h"

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
static uchar ENTER = 0,len = 0 ;
static uchar s[20];
static float idata weight,z_weight = 77.58;

/**************************************************************
*	File Static Variable Define Section
**************************************************************/


/**************************************************************
*	Function Define Section
**************************************************************/

//******ģ�����������******
int main(void)
{		
	init_1602();

	while(1)
	{
		Scale();
	}

	return 0;
}
/**************************/


/**
 *  @name			void Scale();
 *	@description 	ʵ�ֵ��ӳӹ��ܵĺ���
 *	@param			��
 *	@return			��
 *  @notice			��Ҫ�õ�LCD1602�����Ա����ȳ�ʼ�����ڴ˺����ڻ����ε�������ģ��ĺ���ʵ�ֹ���
 */
void Scale()
{
	ulong dig = HX711_GetAD();
	uchar tmp;

	if( keyScan_one_KEY(&tmp) )
		Key_process(&z_weight,dig,tmp);
	weight = Caculate_weight(dig)-z_weight;
	Display_LCD(weight);
	
	return;	
}

/**
 *  @name			void Display_LCD(float weight)
 *	@description 	��LCD������ʾ���֡��۸���ENTER=1,����㲢����۸�
 */
void Display_LCD(float weight)
{
	char wei[16],pri[16],i;
	float price,total;
	sprintf(wei,"%.2fkg  \0",weight);
//	wei[6] = 0;
	
	//��ʾ����
	write_cmd(0x80);
	for(i=0; wei[i]!=0&&i<16; i++)
	{		
		write_dat(wei[i]);
	}
	//��ʾ����
	write_cmd(0x80+0x40);
	for(i=0; i<len; i++)	
	{		
		write_dat(s[i]);
	}  

	//���Ѱ���ȷ�ϼ�������ʾ�ܼ�
	if(ENTER == 1)
	{	
		price = transform_to_digital();
		total = price*weight;
		sprintf(pri,"%.2f\0",total);
		write_cmd(0x80+0x40+10);
		for(i=0; i<10&&pri[i]!='\0'; i++)
		{
//			write_cmd(0x80+0x40+10+i);
		//	Delay(10);
			write_dat(pri[i]);
		//	Delay(10);
		}
//		ENTER = 0;
	}
}


/**
 *  @name 			float transform_to_digital()
 *	@description	��һ���ַ���ת����һ��float�����ݷ���		
 *	@return			float - ���صĸ���������
 *  @notice			�������õ��ַ�����һȫ�ֱ���char s[10]
 */
float transform_to_digital()
{
	float f = 0,flag = 1,temp = 1;
	uchar i;
	for(i=0; s[i]!='\0'; i++)
	{
		if(s[i] == '.')
		{
			flag = 0;
			continue;
		}
		if(flag)
			f = f*10+s[i]-'0';
		else
		{
			temp *= 0.1;
			f += temp*(s[i]-'0');
		}
	}	

	return f;
}

/**
 *  @name			void Key_process(ulennt *pzero,uchar dig)
 *	@description	�������ص�ֵ�����ַ�Ӧ
 *	@param			float * - pzero,ָ��zero��ָ�룬�����޸ĳ�ʼ����
 					uchar  - dig,��ADת����������	
					uchar  - key,���̰�����ѡ��(0~f) 		
 */
void Key_process(float *pzero,ulong dig,uchar key)
{
	switch (key)
	{		
	//������һ�а���
		case 0x00:
			s[len++] = '7';
			break;
		case 0x01:
			s[len++] = '8';
			break;
		case 0x02:
			s[len++] = '9';
			break;
		case 0x03:				//������м۸�����
			len = 0;
			write_cmd(0x01);
			ENTER = 0;
			break;
	//�����µڶ���
		case 0x04:
			s[len++] = '4';
			break;
		case 0x05:
			s[len++] = '5';
			break;
		case 0x06:
			s[len++] = '6';
			break;
		case 0x07:
			*pzero = Caculate_weight(dig);	 		//��������0
			write_cmd(0x01);
			break;
	//�����µ�����
		case 0x08:
			s[len++] = '1';
			break;
		case 0x09:
			s[len++] = '2';
			break;
		case 0x0a:
			s[len++] = '3';
			break;
		case 0x0b:
			if(len > 0)
			{	
				write_cmd(0x01); 	
				len--;				//�����һ����������	
			}
			break;	
	//���һ��
		case 0x0c:
			break;
		case 0x0d:
			s[len++] = '.';
			break;
		case 0x0e:
			s[len++] = '0';
			break;
		case 0x0f:
			s[len] = '\0';
			ENTER = 1;			//ȷ��
			break;
	}	
}


/**
 *  @name
 *	@description
 *	@param			
 *	@return		
 *  @notice
 */
