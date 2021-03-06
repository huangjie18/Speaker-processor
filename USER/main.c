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
#include "Interface.h"
#include "example.h"


const GUI_POINT aPoints[] =
{
    { 40, 20},
    { 0, 20},
    { 20, 0}
};
/* 用于存储放大后的坐标点 */
GUI_POINT aEnlargedPoints[GUI_COUNTOF(aPoints)];
void Sample(void)
{
    int i;
    /* 清屏 */
    GUI_Clear();
    /* 设置绘图模式 */
	GUI_SetPenSize(1);
    GUI_SetDrawMode(GUI_DM_XOR);
    /* 绘制多边形 */
    GUI_FillPolygon(aPoints, /* 指向要显示和填充的多边形 */
                    GUI_COUNTOF(aPoints), /* 点列表中指定的点数量 */
                    140, /* 原点的 X 位置 */
                    110); /* 原点的 Y 位置 */
    for (i = 1; i < 10; i++)
    {
        GUI_EnlargePolygon(aEnlargedPoints, /* 指向目标多边形 */
                           aPoints, /* 指向源多边形 */
                           GUI_COUNTOF(aPoints), /* 点列表中指定的点数量 */
                           i * 5); /* 扩展多边形的长度 （像素） */
        /* 绘制放大后的多边形 */
        GUI_FillPolygon(aEnlargedPoints, GUI_COUNTOF(aPoints), 140, 110);

    }
}


//当前页面句柄
WM_HWIN hWin_now;
/**************************************************************************

*注意：该软件GP芯片使用的stm32的flash下载算法，如果不行请使用回GD的flash算法
*该屏的DB13和DB15要掉转

***************************************************************************/
void GPIO_TEST(void)
{
    GUI_Init();
    /* 调用测试函数 */
	GUI_SetBkColor(GUI_WHITE);
	GUI_SetColor(GUI_BLACK);
    GUI_Clear();
GUI_SetDrawMode(GUI_DRAWMODE_NORMAL);
GUI_FillCircle(120, 64, 40);
GUI_SetDrawMode(GUI_DRAWMODE_XOR);
GUI_FillCircle(140, 84, 40);
    while (1)
    {
        GUI_Delay(10);
    }
}

int main(void)
{
    u8 key_value = 0;
    u8 key_value1 = 0;
    u8 key_value2 = 0;
    u8 key_value3 = 0;
    u16 count = 0;
    GUI_COLOR color;


    delay_init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    LED_GPIO_Init();        //按键LED初始化,全亮
    KEY_GPIO_Init();        //按键初始化
    Encoder_GPIO_Init();    //编码器初始化
    Lcd_Initialize();       //LCD初始化
    TIM3_Int_Init(999, 71); //1KHZ 定时器1ms
    my_mem_init(SRAMIN);



    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,
                          ENABLE); //使能CRC时钟，否则STemWin不能使用
//  GPIO_TEST();  //测试引脚是否短路

	MainTask(); //主程序

    while(1)
    {
        if(WM_IsWindow(hWin_now)) //判断hWin_now是否有效,Framewin窗口客户区句柄
        {

            //旋钮检测
            //有问题，里面有while循环
            key_value1 = Encoder_Check_One();   //旋钮1检测
            key_value2 = Encoder_Check_Two();   //旋钮2检测
            key_value3 = Encoder_Check_Three(); //旋钮3检测
            //此程序一次只检测一个旋钮动作
            if((key_value1 != Encoder_static) || (key_value2 != Encoder_static)
               || (key_value3 != Encoder_static)) //有动作
            {
                if(key_value1)
                {
                    key_value = key_value1;
                }
                else if(key_value2)
                {
                    key_value = key_value2;
                }
                else if(key_value3)
                {
                    key_value = key_value3;
                }

                switch(key_value)
                {
                    case Encoder1_left:
                        WM_SendMessageNoPara(hWin_now, MSG_KNOB_INPUT_LEFT); //输入旋钮发送的信息
                        //会直接执行被聚焦窗口的回调函数
                        //调用过程：GUI_SendKeyMsg->WM_SendMessage->回调函数->发送WM_NOTIFY_PARENT
                        //给父窗口

                        break;

                    case Encoder1_right:
                        WM_SendMessageNoPara(hWin_now, MSG_KNOB_INPUT_RIGHT);
                        break;

                    case Encoder2_left:
                        WM_SendMessageNoPara(hWin_now, MSG_KNOB_OUT_LEFT); //输出旋钮
                        break;

                    case Encoder2_right:
                        WM_SendMessageNoPara(hWin_now, MSG_KNOB_OUT_RIGHT);
                        break;

                    case Encoder3_left:
                        WM_SendMessageNoPara(hWin_now, MSG_KNOB_CONTROL_LEFT); //control旋钮
                        break;
                    case Encoder3_right:
                        WM_SendMessageNoPara(hWin_now, MSG_KNOB_CONTROL_RIGHT);
                        break;

                    default:
                        break;
                }
//              WM_Exec();
//              delay_ms(150);

            }


            //按键检测
            key_value = KEY_Scan(0);
            if(key_value)
            {
                switch(key_value)
                {
                    //输入按钮
                    case KEY_INPUT:
                        WM_SendMessageNoPara(hWin_now, MSG_KEY_INPUT);
                        //先把灯全灭
                        LED_All_Off;
                        Input_led_On; //灯亮
                        break;

                    //退出按钮
                    case KEY_ESC:
                        //先把灯全灭
                        LED_All_Off;
                        Esc_led_On; //灯亮
                        WM_SendMessageNoPara(hWin_now, MSG_KEY_ESC);
                        break;

                    //输出按钮
                    case KEY_OUTPUT:
                        //先把灯全灭
                        LED_All_Off;
                        Out_led_On; //灯亮
                        WM_SendMessageNoPara(hWin_now, MSG_KEY_OUTPUT);
                        break;

                    //系统按钮
                    case KEY_SYSTEM:
                        LED_All_Off;
                        Sys_led_On; //灯亮
                        WM_SendMessageNoPara(hWin_now, MSG_KEY_SYSTEM);
                        break;

                    //旋钮1
                    case KEY_EN_1:
                        WM_SendMessageNoPara(hWin_now, MSG_KEY_INPUT);
                        break;

                    //旋钮2
                    case KEY_EN_2:
                        WM_SendMessageNoPara(hWin_now, MSG_KEY_OUTPUT);
                        break;

                    //旋钮3
                    case KEY_EN_3:
//                  GUI_SendKeyMsg(GUI_KEY_ENTER, 1);  //发送确定按键的信息
                        WM_SendMessageNoPara(hWin_now, MSG_KEY_CONTROL);
                        break;
                    default:
                        break;
                }
//              WM_Exec();
//              delay_ms(300);

            }
        }
        else   //无效则刷黑屏
        {
            GUI_SetBkColor(GUI_RED);
            GUI_Clear();

            GUI_SetColor(GUI_BLACK);
            GUI_GotoXY(0, 0);
            GUI_DispDecMin(GUI_ALLOC_GetNumFreeBytes());
        }

        if(count == 1000)
        {
            count = 0;
            LED = ~LED;  //LED反转，用来检测系统是否正常运行
        }
        GUI_Delay(1);
        count++;


//      delay_ms(1000);
//      LED = ~LED;

    }

}

