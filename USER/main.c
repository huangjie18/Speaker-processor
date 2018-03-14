#include "stm32f10x.h"
#include "delay.h"
#include "ILI93xx.h"
#include "malloc.h"
#include "GUI.h"
#include "timer.h"
#include "GUIDemo.h"
#include "test.h"

void ceshi_ID(void)
{
	u16 id;
	WriteComm(0x0000);
	delay_us(5);
	id = LCD_RD_DATA();
	if(id<0xff||id==0xffff||id==9300)
	{
		
	}
	WriteComm(0xd3);
	id = LCD_RD_DATA();
	id = LCD_RD_DATA();
	id = LCD_RD_DATA();
	id <<= 8;
	id |= LCD_RD_DATA();
	GUI_DispHexAt(id,150,50,4);
}


int main(void)
{
	u16 rbg;
	delay_init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	Lcd_Initialize(); //初始化
	TIM3_Int_Init(999,71);	//1KHZ 定时器1ms 
	my_mem_init(SRAMIN);

	
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,ENABLE);//使能CRC时钟，否则STemWin不能使用 
//	GUI_Init();  //STemWin初始化
//	GUI_SetBkColor(GUI_BLACK);  //设置背景色
//	GUI_SetColor(GUI_YELLOW);  //设置颜色
//	GUI_Clear();   //清屏
//	GUI_SetFont(&GUI_Font24B_ASCII);
//	GUI_DispStringAt("Hello Word!",0,0);
	MainTask();

	while(1)
	{
	}
	
}

