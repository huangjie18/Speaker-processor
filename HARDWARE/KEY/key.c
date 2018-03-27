#include "key.h"

u8 KEY_Value[][3]=
{
	{1,2,3},
	{4,5,6},
	{7},
};

/*
 * 函数名：KEY_GPIO_Init
 * 描述  ：初始化按键的IO引脚
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用        
 */
void KEY_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	//配置输入模式
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;//KEY1-KEY4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC6,7,8,采用矩阵扫描
	
	
	//配置输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure); //初始化GPIOC9,10,11
	
	col1 = 1; //全部按键无效操作，为低电平的时候才是有效操作
	col2 = 1;
	col3 = 1;
}

/*
 * 函数名：KEY_Scan
 * 描述  ：按键矩阵扫描函数
 * 输入  ：mode: 1则支持连按，0不支持连按；
 * 输出  ：按键值
 * 调用  ：内部调用        
 */

u8 KEY_Scan(u8 mode)
{
	u8 i,j;
	static u8 key_up = 1;  //按键按松开标志
	if(mode)key_up=1;      //支持连按
	if(key_up)
	{
		col1 = 1;
		col2 = 1;
		col3 = 1;
		for(i = 1;i < 4; i++)
		{
			switch(i)
			{
				case 1: col1 = 0; col3 = 1; break;
				case 2: col2 = 0; col1 = 1; break;
				case 3: col3 = 0; col2 = 1; break;
				default : break;
			}
			if(row1 == 0 ||row2 == 0 || row3 == 0)
			{
				key_up = 0;
				
				if(row1==0) {return KEY_Value[0][i-1];} //第一行
				else if(row2==0) {return KEY_Value[1][i-1];}
				else if(row3==0) {return KEY_Value[2][i-1];}
			}
		}
	}
	else
	{
		col1 = 0;
		col2 = 0;
		col3 = 0;
		if(row1==1&&row2==1&&row3==1) key_up = 1;
	}
	return 0;
}