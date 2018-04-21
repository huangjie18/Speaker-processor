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

//当前页面句柄
WM_HWIN hWin_now;
/*
注意：该软件GP芯片使用的stm32的flash下载算法，如果不行请使用回GD的flash算法
*/
void GPIO_TEST(void)
{
    Lcd_Initialize();
//  DB0 = 1;
//  DB1 = 1;
//  DB2 = 0;
//  DB3 = 0;
//  DB4 = 1;
//  DB5 = 1;
//  DB6 = 0;
//  DB7 = 0;
//  DB8 = 1;
//  DB9 = 1;
//  DB10 = 0;
//  DB11 = 0;
//  DB12 = 1;
//  DB13 = 1;
//  DB14 = 0;
//  DB15 = 0;
//  Lcd_Clear(0X8430);
    while(1)
    {
    }
}

int main(void)
{
    u8 key_value = 0;
    u8 key_value1 = 0; 
    u8 key_value2 = 0;
	u8 key_value3 = 0;
    GUI_COLOR color;
	
	
    delay_init(72);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    LED_GPIO_Init();        //LED初始化,全亮
    KEY_GPIO_Init();        //按键初始化
    Encoder_GPIO_Init();    //编码器初始化
//  Lcd_Initialize();       //LCD初始化
    TIM3_Int_Init(999, 71); //1KHZ 定时器1ms
    my_mem_init(SRAMIN);



    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,
                          ENABLE); //使能CRC时钟，否则STemWin不能使用
//  GPIO_TEST();  //测试引脚是否短路


    MainTask(); //主程序
//  GUI_Init();
//  GUI_SetBkColor(GUI_GRAY);
//  GUI_Clear();
//  DrawPixel(0,0,Red);
//    DrawPixel(0,1,Red);
//    DrawPixel(0,2,Blue);
//    color = GetPoint(0,0);
//  GUI_SetFont(&GUI_Font24B_ASCII);
//    GUI_DispHexAt(color,50,50,4);

    while(1)
    {
        if(WM_IsWindow(hWin_now)) //判断hWin_now是否有效,Framewin窗口客户区句柄
        {

            //旋钮检测
            key_value1 = Encoder_Check_One();   //旋钮1检测
			key_value2 = Encoder_Check_Two();   //旋钮2检测
			key_value3 = Encoder_Check_Three(); //旋钮3检测
			//此程序一次只检测一个旋钮动作
            if(key_value1 || key_value2 || key_value3) //有动作
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
						WM_SendMessageNoPara(hWin_now, MSG_KNOB_INPUT_LEFT); //输入旋钮
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
            }
			

            //按键检测
            key_value = KEY_Scan(0);
            if(key_value)
            {
                switch(key_value)
                {
                    //输入按钮
                    case KEY_INPUT:
//                  GUI_SendKeyMsg(GUI_KEY_ENTER, 1);
                        WM_SendMessageNoPara(hWin_now, MSG_KEY_INPUT);
                        break;

                    //退出按钮
                    case KEY_ESC:
//                  GUI_SendKeyMsg(GUI_KEY_ESCAPE, 1);
                        WM_SendMessageNoPara(hWin_now, MSG_KEY_ESC);
                        break;

                    //输出按钮
                    case KEY_OUTPUT:
                        WM_SendMessageNoPara(hWin_now, MSG_KEY_OUTPUT);
                        break;

                    //系统按钮
                    case KEY_SYSTEM:
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

            }
        }
		else   //无效则刷黑屏
		{
			GUI_SetBkColor(GUI_BLACK);
			GUI_Clear();
		}
		
        GUI_Delay(10);

    }

}

