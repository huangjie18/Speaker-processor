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

//��ǰҳ����
WM_HWIN hWin_now;
/*
ע�⣺�����GPоƬʹ�õ�stm32��flash�����㷨�����������ʹ�û�GD��flash�㷨
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
	u16 count=0;
    GUI_COLOR color;
	
	
    delay_init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    LED_GPIO_Init();        //����LED��ʼ��,ȫ��
    KEY_GPIO_Init();        //������ʼ��
    Encoder_GPIO_Init();    //��������ʼ��
	Lcd_Initialize();       //LCD��ʼ��
    TIM3_Int_Init(999, 71); //1KHZ ��ʱ��1ms
    my_mem_init(SRAMIN);



    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,
                          ENABLE); //ʹ��CRCʱ�ӣ�����STemWin����ʹ��
//  GPIO_TEST();  //���������Ƿ��·

    MainTask(); //������
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
        if(WM_IsWindow(hWin_now)) //�ж�hWin_now�Ƿ���Ч,Framewin���ڿͻ������
        {

            //��ť���
			//�����⣬������whileѭ��
            key_value1 = Encoder_Check_One();   //��ť1���
			key_value2 = Encoder_Check_Two();   //��ť2���
			key_value3 = Encoder_Check_Three(); //��ť3���
			//�˳���һ��ֻ���һ����ť����
            if((key_value1!=Encoder_static) || (key_value2!=Encoder_static)
				|| (key_value3!=Encoder_static)) //�ж���
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
						WM_SendMessageNoPara(hWin_now, MSG_KNOB_INPUT_LEFT); //������ť���͵���Ϣ
						//��ֱ��ִ�б��۽����ڵĻص�����
					//���ù��̣�GUI_SendKeyMsg->WM_SendMessage->�ص�����->����WM_NOTIFY_PARENT
					//��������
					
						break;
					
					case Encoder1_right:
						WM_SendMessageNoPara(hWin_now, MSG_KNOB_INPUT_RIGHT);
						break;
					
					case Encoder2_left:
						WM_SendMessageNoPara(hWin_now, MSG_KNOB_OUT_LEFT); //�����ť
						break;
					
					case Encoder2_right:
						WM_SendMessageNoPara(hWin_now, MSG_KNOB_OUT_RIGHT);
						break;
					
                    case Encoder3_left:
                        WM_SendMessageNoPara(hWin_now, MSG_KNOB_CONTROL_LEFT); //control��ť
                        break;
                    case Encoder3_right:
                        WM_SendMessageNoPara(hWin_now, MSG_KNOB_CONTROL_RIGHT);
                        break;

                    default:
                        break;
                }
//				WM_Exec();
//				delay_ms(150);
				
            }
			

            //�������
            key_value = KEY_Scan(0);
            if(key_value)
            {
                switch(key_value)
                {
                    //���밴ť
                    case KEY_INPUT:
                        WM_SendMessageNoPara(hWin_now, MSG_KEY_INPUT);
						GPIOC->ODR = (GPIOA->IDR & 0xfff0);  //�Ȱѵ�ȫ��
						Input_led_On; //����
                        break;

                    //�˳���ť
                    case KEY_ESC:
						GPIOC->ODR = (GPIOA->IDR & 0xfff0);  //�Ȱѵ�ȫ��
						Esc_led_On; //����
                        WM_SendMessageNoPara(hWin_now, MSG_KEY_ESC);
                        break;

                    //�����ť
                    case KEY_OUTPUT:
						GPIOC->ODR = (GPIOA->IDR & 0xfff0);  //�Ȱѵ�ȫ��
						Out_led_On; //����
                        WM_SendMessageNoPara(hWin_now, MSG_KEY_OUTPUT);
                        break;

                    //ϵͳ��ť
                    case KEY_SYSTEM:
						GPIOC->ODR = (GPIOA->IDR & 0xfff0);  //�Ȱѵ�ȫ��
						Sys_led_On; //����
                        WM_SendMessageNoPara(hWin_now, MSG_KEY_SYSTEM);
                        break;

                    //��ť1
                    case KEY_EN_1:
                        WM_SendMessageNoPara(hWin_now, MSG_KEY_INPUT);
                        break;

                    //��ť2
                    case KEY_EN_2:
                        WM_SendMessageNoPara(hWin_now, MSG_KEY_OUTPUT);
                        break;

                    //��ť3
                    case KEY_EN_3:
//                  GUI_SendKeyMsg(GUI_KEY_ENTER, 1);  //����ȷ����������Ϣ
                        WM_SendMessageNoPara(hWin_now, MSG_KEY_CONTROL);
                        break;
                    default:
                        break;
                }

            }
        }
		else   //��Ч��ˢ����
		{
			GUI_SetBkColor(GUI_RED);
			GUI_Clear();
			
			GUI_SetColor(GUI_BLACK);
			GUI_GotoXY(0,0);
			GUI_DispDecMin(GUI_ALLOC_GetNumFreeBytes());
		}
		
		if(count==1000)
		{
			count = 0;
			LED = ~LED;  //LED��ת���������ϵͳ�Ƿ���������
		}
        GUI_Delay(1);
		count++;


//		delay_ms(1000);
//		LED = ~LED;

    }

}

