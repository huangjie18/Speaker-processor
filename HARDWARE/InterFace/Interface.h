#ifndef __INTERFACE_H
#define __INTERFACE_H
#include "GUI.h"
#include "DIALOG.h"

//定义按钮的信息ID
#define MSG_KEY_ESC      (GUI_ID_USER + 0xF0)
#define MSG_KEY_SYSTEM   (GUI_ID_USER + 0xF1)
#define MSG_KEY_INPUT     (GUI_ID_USER + 0xF2)
#define MSG_KEY_OUTPUT   (GUI_ID_USER + 0xF3)
#define MSG_KEY_VOL_INPUT  (GUI_ID_USER + 0xF4)
#define MSG_KEY_VOL_OUTPUT (GUI_ID_USER + 0xF5)
#define MSG_KEY_CONTROL    (GUI_ID_USER + 0xF6)

//定义旋钮的信息ID
#define MSG_KNOB_INPUT_LEFT    (GUI_ID_USER + 0xF7)
#define MSG_KNOB_INPUT_RIGHT   (GUI_ID_USER + 0xF8)
#define MSG_KNOB_OUT_LEFT      (GUI_ID_USER + 0xF9)
#define MSG_KNOB_OUT_RIGHT     (GUI_ID_USER + 0xFA)
#define MSG_KNOB_CONTROL_LEFT  (GUI_ID_USER + 0xFB)
#define MSG_KNOB_CONTROL_RIGHT (GUI_ID_USER + 0xFC)

//定义一个变量来存放当前的页面的句柄
extern WM_HWIN hWin_now;


//皮肤设置函数
void Button_flex(void); //按钮皮肤设置
void Framewin_flex(void); //框架皮肤设置

//界面函数
WM_HWIN CreateMainface(void); //主界面窗口

//第二层界面
WM_HWIN CreateINPUT_CHANNEL(void); //通道界面窗口

//第三层界面

/****************Input1************************/

//右边子窗口存放数据结构体
typedef struct
{
	char Invert;
	unsigned char RMSTC;  
	unsigned char Hold;
	unsigned char Decay;
	signed char Gain;
	signed char Aux1MixerGain;
	signed char Aux2MixerGain;
	signed char Aux3MixerGain;
	signed char Aux4MixerGain;
	signed char Aux5MixerGain;
	signed char Aux6MixerGain;
	signed char Aux7MixerGain;
	signed char Aux8MixerGain;
	
}Input_data;
	
extern Input_data Input1_data1[8]; //存放数据的变量

WM_HWIN Createthird_layer(void); //Input1界面窗口

//右边第一个子窗口
WM_HWIN CreateWindow_Child(void); //右边第一个子窗口界面
WM_HWIN Get_child_hWin(I32 ID);  //Input1右边子窗口获得控件句柄

//右边第二个子窗口
WM_HWIN CreateSecond_Child(void);

//右边第三个子窗口
WM_HWIN CreateThird_Child(void);

//右边第四个子窗口
WM_HWIN CreateFour_Child(void);

//右边第五个子窗口
WM_HWIN CreateFive_Child(void);
/*****************end*************************/
#endif
