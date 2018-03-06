#include "stm32f10x.h"
#include "delay.h"
#include "ILI93xx.h"
#include "malloc.h"
#include "GUI.h"
void Lcd_ColorBox(u16 xStart,u16 yStart,u16 xLong,u16 yLong,u16 Color)
{
	u32 temp;

	BlockWrite(xStart,xStart+xLong-1,yStart,yStart+yLong-1);
	for (temp=0; temp<xLong*yLong; temp++)
	{
		*(__IO u16 *) (Bank1_LCD_D) = Color;
	}
}

int main(void)
{
	delay_init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Lcd_Initialize();
	my_mem_init(SRAMIN);
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,ENABLE);
	GUI_Init();  //STemWin初始化
	GUI_SetBkColor(GUI_BLUE);  //设置背景色
	GUI_SetColor(GUI_YELLOW);  //设置颜色
	GUI_Clear();   //清屏
	GUI_SetFont(&GUI_Font24B_ASCII);
	GUI_DispStringAt("Hello Word!",0,0);
//	Lcd_ColorBox(0,0,400,240,0xffff);
	while(1)
	{
	}
	
}