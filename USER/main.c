#include "stm32f10x.h"
#include "delay.h"
#include "ILI93xx.h"
#include "malloc.h"
#include "GUI.h"
#include "timer.h"
#include "GUIDemo.h"
#include "test.h"
#include "led.h"
#include "key.h"


void GPIO_TEST(void)
{
	Lcd_Initialize();
//	DB0 = 1;
//	DB1 = 1;
//	DB2 = 0;
//	DB3 = 0;
//	DB4 = 1;
//	DB5 = 1;
//	DB6 = 0;
//	DB7 = 0;
//	DB8 = 1;
//	DB9 = 1;
//	DB10 = 0;
//	DB11 = 0;
//	DB12 = 1;
//	DB13 = 1;
//	DB14 = 0;
//	DB15 = 0;
//	Lcd_Clear(0X8430);
	while(1)
	{
	}
}


int main(void)
{
	u8 key_value;
	GUI_COLOR color;
	delay_init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_GPIO_Init();  //LED初始化,全亮
	KEY_GPIO_Init();  //按键初始化
	Encoder_GPIO_Init();  //编码器初始化
//	Lcd_Initialize(); //LCD初始化
	TIM3_Int_Init(999,71);	//1KHZ 定时器1ms 
	my_mem_init(SRAMIN);

	
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,ENABLE);//使能CRC时钟，否则STemWin不能使用 
//	GPIO_TEST();  //测试引脚是否短路
	
	
	MainTask(); //主程序
//	GUI_Init();
//	GUI_SetBkColor(GUI_GRAY);
//	GUI_Clear();
//	DrawPixel(0,0,Red);
//    DrawPixel(0,1,Red);
//    DrawPixel(0,2,Blue);
//    color = GetPoint(0,0);
//	GUI_SetFont(&GUI_Font24B_ASCII);
//    GUI_DispHexAt(color,50,50,4);

	while(1)
	{
		//旋钮3检测
		key_value = Encoder_Check_Three();
		if(key_value) //有动作
		{
			switch(key_value)
			{
				case Encoder_left:
					GUI_SendKeyMsg(GUI_KEY_TAB, 1);  //发送切换下一个按钮的信息
					break;
				case Encoder_right:
					GUI_SendKeyMsg(GUI_KEY_BACKTAB, 1); //发送切换上一个按钮的信息
					break;
				
				default:
					break;
			}
		}
		
		//按键检测
		key_value = KEY_Scan(0);
		if(key_value)
		{
			switch(key_value)
			{
				case KEY_EN_3:
					GUI_SendKeyMsg(GUI_KEY_ENTER, 1);  //发送确定按键的信息
					break;
				default:
					break;
			}
		}
		GUI_Delay(10);
	}
	
}

