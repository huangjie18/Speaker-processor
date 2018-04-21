#ifndef __INTERFACE_H
#define __INTERFACE_H
#include "GUI.h"
#include "DIALOG.h"

//���尴ť����ϢID
#define MSG_KEY_ESC      (GUI_ID_USER + 0xF0)
#define MSG_KEY_SYSTEM   (GUI_ID_USER + 0xF1)
#define MSG_KEY_INPUT     (GUI_ID_USER + 0xF2)
#define MSG_KEY_OUTPUT   (GUI_ID_USER + 0xF3)
#define MSG_KEY_VOL_INPUT  (GUI_ID_USER + 0xF4)
#define MSG_KEY_VOL_OUTPUT (GUI_ID_USER + 0xF5)
#define MSG_KEY_CONTROL    (GUI_ID_USER + 0xF6)

//������ť����ϢID
#define MSG_KNOB_INPUT_LEFT    (GUI_ID_USER + 0xF7)
#define MSG_KNOB_INPUT_RIGHT   (GUI_ID_USER + 0xF8)
#define MSG_KNOB_OUT_LEFT      (GUI_ID_USER + 0xF9)
#define MSG_KNOB_OUT_RIGHT     (GUI_ID_USER + 0xFA)
#define MSG_KNOB_CONTROL_LEFT  (GUI_ID_USER + 0xFB)
#define MSG_KNOB_CONTROL_RIGHT (GUI_ID_USER + 0xFC)

//����һ����������ŵ�ǰ��ҳ��ľ��
extern WM_HWIN hWin_now;


//Ƥ�����ú���
void Button_flex(void); //��ťƤ������
void Framewin_flex(void); //���Ƥ������

//���溯��
WM_HWIN CreateMainface(void); //�����洰��

//�ڶ������
WM_HWIN CreateINPUT_CHANNEL(void); //ͨ�����洰��

//���������

/****************Input1************************/

//�ұ��Ӵ��ڴ�����ݽṹ��
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
	
extern Input_data Input1_data1[8]; //������ݵı���

WM_HWIN Createthird_layer(void); //Input1���洰��

//�ұߵ�һ���Ӵ���
WM_HWIN CreateWindow_Child(void); //�ұߵ�һ���Ӵ��ڽ���
WM_HWIN Get_child_hWin(I32 ID);  //Input1�ұ��Ӵ��ڻ�ÿؼ����

//�ұߵڶ����Ӵ���
WM_HWIN CreateSecond_Child(void);

//�ұߵ������Ӵ���
WM_HWIN CreateThird_Child(void);

//�ұߵ��ĸ��Ӵ���
WM_HWIN CreateFour_Child(void);

//�ұߵ�����Ӵ���
WM_HWIN CreateFive_Child(void);
/*****************end*************************/
#endif
