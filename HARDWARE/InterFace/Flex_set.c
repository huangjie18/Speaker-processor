//Ƥ������

#include "DIALOG.h"

//��ť�۽�Ƥ������
void Button_flex(void)
{
	BUTTON_SKINFLEX_PROPS Props;
	BUTTON_GetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_FOCUSSED); //�۽���״̬
	Props.aColorFrame[0] = GUI_GREEN; //Բ�Ǳ߿���ⲿ��ɫ
	Props.aColorFrame[1] = GUI_BLACK; //Բ�Ǳ߿���ڲ���ɫ
	Props.aColorFrame[2] = GUI_RED;   //������ڲ��������ɫ
	Props.aColorLower[0] = GUI_RED;   //�²㽥��ģ��ϲ㣩��ɫ
	Props.aColorLower[1] = GUI_RED;   //�²㽥��ģ��²㣩��ɫ
	Props.aColorUpper[0] = GUI_RED;   //�ϲ㽥��ģ��ϲ㣩��ɫ
	Props.aColorUpper[1] = GUI_RED;   //�ϲ㽥��ģ��²㣩��ɫ
	BUTTON_SetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_FOCUSSED);
}

//FramewinƤ������
void Framewin_flex(void)
{
	  //���ð�ťƤ��
  	FRAMEWIN_SKINFLEX_PROPS Props;
	FRAMEWIN_GetSkinFlexProps(&Props,FRAMEWIN_SKINFLEX_PI_ACTIVE); //��û״̬��Ƥ��
	Props.aColorFrame[0] = GUI_BLACK;
	Props.aColorFrame[1] = GUI_BLACK;
	Props.aColorFrame[2] = GUI_BLACK;
	Props.aColorTitle[0] = 0xC0CEDC;
	Props.aColorTitle[1] = GUI_BLACK;
	Props.BorderSizeL = 0;
	Props.BorderSizeR = 0;
	Props.BorderSizeB = 0;
	Props.Radius = 0;
	FRAMEWIN_SetSkinFlexProps(&Props,FRAMEWIN_SKINFLEX_PI_ACTIVE);//���û״̬��Ƥ��
}

