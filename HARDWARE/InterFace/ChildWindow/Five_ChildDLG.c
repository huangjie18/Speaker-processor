/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.32                          *
*        Compiled Oct  8 2015, 11:59:02                              *
*        (c) 2015 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0 (GUI_ID_USER + 0x00)
#define ID_SLIDER_0 (GUI_ID_USER + 0x01)
#define ID_SLIDER_1 (GUI_ID_USER + 0x02)
#define ID_TEXT_0 (GUI_ID_USER + 0x04)
#define ID_TEXT_1 (GUI_ID_USER + 0x05)


// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] =
{
    { WINDOW_CreateIndirect, "Five_Child", ID_WINDOW_0, 0, 0, 285, 240, 0, 0x0, 0 },
    { SLIDER_CreateIndirect, "Slider", ID_SLIDER_0, 27, 28, 224, 43, 0, 0x0, 0 },
    { SLIDER_CreateIndirect, "Slider", ID_SLIDER_1, 27, 107, 224, 43, 0, 0x0, 0 },
    { TEXT_CreateIndirect, "Text", ID_TEXT_0, 27, 7, 109, 20, 0, 0x64, 0 },
    { TEXT_CreateIndirect, "Text", ID_TEXT_1, 27, 79, 109, 20, 0, 0x64, 0 },
    // USER START (Optionally insert additional widgets)
    // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

//无效区域设置
static GUI_RECT Rect_3[]=
{
    {136,7,156,27},
    {136,79,156,99},
};

//滑块结构体
//typedef struct
//{
//    int Value;  //滑块的值
//    int x;      //x位置
//    int y;      //y位置
//}SLIDER_Show;

//static signed char SLIDER_Value[2] = {-80,-80}; //定义三个滑块值

//显示滑块值
static void _ShowSlidervalue(void)
{
    GUI_SetColor(GUI_RED);           //设置显示颜色
    GUI_SetTextMode(GUI_TM_TRANS);   //设置显示模式为透明模式即是不会覆盖背景
    GUI_SetFont(&GUI_Font20_1);      //显示字体大小
    GUI_GotoXY(136,7);               //设置第一个滑块位置
    GUI_DispDecMin(Input1_data1[INPUT_channel].Aux7MixerGain); //显示第一个滑块值
    GUI_GotoXY(136,79);              //设置第二个滑块位置
    GUI_DispDecMin(Input1_data1[INPUT_channel].Aux8MixerGain); //显示第二个滑块值
}

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg)
{
    WM_HWIN hItem;
    int     NCode;
    int     Id;
    // USER START (Optionally insert additional variables)
    // USER END

    switch (pMsg->MsgId)
    {
    case WM_INIT_DIALOG:
        //滑块7的范围调整
        hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_0); //获得句柄
        SLIDER_SetRange(hItem,-80,0); //设置滑块范围
        SLIDER_SetValue(hItem,Input1_data1[INPUT_channel].Aux7MixerGain); //设置滑块的值

        //滑块8的范围调整
        hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_1); //获得句柄
        SLIDER_SetRange(hItem,-80,0); //设置滑块范围
        SLIDER_SetValue(hItem,Input1_data1[INPUT_channel].Aux8MixerGain); //设置滑块的值
        //
        // Initialization of 'Text'
        //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
        TEXT_SetText(hItem, "Aux7MixerGain:");
        TEXT_SetFont(hItem, GUI_FONT_16B_1);
        //
        // Initialization of 'Text'
        //
        hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
        TEXT_SetText(hItem, "Aux8MixerGain:");
        TEXT_SetFont(hItem, GUI_FONT_16B_1);
        // USER START (Optionally insert additional code for further widget initialization)
        // USER END
        break;
    case WM_NOTIFY_PARENT:
        Id    = WM_GetId(pMsg->hWinSrc);
        NCode = pMsg->Data.v;
        switch(Id)
        {
        case ID_SLIDER_0: // Notifications sent by 'Slider'
            switch(NCode)
            {
            case WM_NOTIFICATION_CLICKED:
                // USER START (Optionally insert code for reacting on notification message)
                // USER END
                break;
            case WM_NOTIFICATION_RELEASED:
                // USER START (Optionally insert code for reacting on notification message)
                // USER END
                break;
            case WM_NOTIFICATION_VALUE_CHANGED: //滑块位置发生变化会执行下面语句
                hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_0); //获得滑块句柄
                Input1_data1[INPUT_channel].Aux7MixerGain = SLIDER_GetValue(hItem); //保存滑块值
                WM_InvalidateRect(pMsg->hWin,&Rect_3[0]); //无效化该值重新刷新显示值
                break;
                // USER START (Optionally insert additional code for further notification handling)
                // USER END
            }
            break;
        case ID_SLIDER_1: // Notifications sent by 'Slider'
            switch(NCode)
            {
            case WM_NOTIFICATION_CLICKED:
                // USER START (Optionally insert code for reacting on notification message)
                // USER END
                break;
            case WM_NOTIFICATION_RELEASED:
                // USER START (Optionally insert code for reacting on notification message)
                // USER END
                break;
            case WM_NOTIFICATION_VALUE_CHANGED:
                hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_1); //获得滑块句柄
                Input1_data1[INPUT_channel].Aux8MixerGain = SLIDER_GetValue(hItem); //保存滑块值
                WM_InvalidateRect(pMsg->hWin,&Rect_3[1]); //无效化该值重新刷新显示值
                break;
                // USER START (Optionally insert additional code for further notification handling)
                // USER END
            }
            break;
            // USER START (Optionally insert additional code for further Ids)
            // USER END
        }
        break;
    case WM_PAINT:  //绘制
        _ShowSlidervalue(); //显示滑块值
        break;

    default:
        WM_DefaultProc(pMsg);
        break;
    }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateFive_Child
*/

WM_HWIN CreateFive_Child(void)
{
    WM_HWIN hWin;

    hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
    return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
