//皮肤设置

#include "DIALOG.h"

//按钮聚焦皮肤设置
void Button_flex(void)
{
	BUTTON_SKINFLEX_PROPS Props;
	BUTTON_GetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_FOCUSSED); //聚焦的状态
	Props.aColorFrame[0] = GUI_GREEN; //圆角边框的外部颜色
	Props.aColorFrame[1] = GUI_BLACK; //圆角边框的内部颜色
	Props.aColorFrame[2] = GUI_RED;   //框架与内部区域的颜色
	Props.aColorLower[0] = GUI_RED;   //下层渐变的（上层）颜色
	Props.aColorLower[1] = GUI_RED;   //下层渐变的（下层）颜色
	Props.aColorUpper[0] = GUI_RED;   //上层渐变的（上层）颜色
	Props.aColorUpper[1] = GUI_RED;   //上层渐变的（下层）颜色
	BUTTON_SetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_FOCUSSED);
}

//Framewin皮肤设置
void Framewin_flex(void)
{
	  //设置按钮皮肤
  	FRAMEWIN_SKINFLEX_PROPS Props;
	FRAMEWIN_GetSkinFlexProps(&Props,FRAMEWIN_SKINFLEX_PI_ACTIVE); //获得活动状态的皮肤
	Props.aColorFrame[0] = GUI_BLACK;
	Props.aColorFrame[1] = GUI_BLACK;
	Props.aColorFrame[2] = GUI_BLACK;
	Props.aColorTitle[0] = 0xC0CEDC;
	Props.aColorTitle[1] = GUI_BLACK;
	Props.BorderSizeL = 0;
	Props.BorderSizeR = 0;
	Props.BorderSizeB = 0;
	Props.Radius = 0;
	FRAMEWIN_SetSkinFlexProps(&Props,FRAMEWIN_SKINFLEX_PI_ACTIVE);//设置活动状态的皮肤
}

