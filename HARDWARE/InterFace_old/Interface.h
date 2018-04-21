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
WM_HWIN CreateINPUT_CHANNEL(void);
WM_HWIN CreateMainface(void); //�����洰��
#endif
