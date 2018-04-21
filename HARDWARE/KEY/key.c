#include "key.h"

u8 KEY_Value[][3] =
{
    {5, 6, 7},
    {3, 2, 4},
    {1},
};




//��ť�ṹ��
typedef struct
{
    Encoder_State encoder_state;  //��ť״̬
	

} Encoder_struct;
//��ťʵ����
Encoder_struct Encoder_sample[three+1];  //��������ť
/*
 * ��������KEY_GPIO_Init
 * ����  ����ʼ��������IO����
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
void KEY_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    //��������ģʽ
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8; //KEY1-KEY4
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
    GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC6,7,8,���þ���ɨ��


    //�������ģʽ
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure); //��ʼ��GPIOC9,10,11

    col1 = 1; //ȫ��������Ч������Ϊ�͵�ƽ��ʱ�������Ч����
    col2 = 1;
    col3 = 1;
}

/*
 * ��������KEY_Scan
 * ����  ����������ɨ�躯��
 * ����  ��mode: 1��֧��������0��֧��������
 * ���  ������ֵ
 * ����  ���ڲ�����
 */

u8 KEY_Scan(u8 mode)
{
    u8 i, j;
    static u8 key_up = 1;  //�������ɿ���־
    if(mode)key_up = 1;    //֧������
    if(key_up)
    {
        col1 = 1;
        col2 = 1;
        col3 = 1;
        for(i = 1; i < 4; i++)
        {
            switch(i)
            {
                case 1:
                    col1 = 0;
                    col3 = 1;
                    break;
                case 2:
                    col2 = 0;
                    col1 = 1;
                    break;
                case 3:
                    col3 = 0;
                    col2 = 1;
                    break;
                default :
                    break;
            }
            if(row1 == 0 || row2 == 0 || row3 == 0)
            {
                key_up = 0;

                if(row1 == 0)
                {
                    return KEY_Value[0][i - 1];   //��һ��
                }
                else if(row2 == 0)
                {
                    return KEY_Value[1][i - 1];
                }
                else if(row3 == 0)
                {
                    return KEY_Value[2][i - 1];
                }
            }
        }
    }
    else
    {
        col1 = 0;
        col2 = 0;
        col3 = 0;
        if(row1 == 1 && row2 == 1 && row3 == 1) key_up = 1;
    }
    return 0;
}


//���������ų�ʼ��
void Encoder_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4
                                   | GPIO_Pin_5
                                   | GPIO_Pin_6; //KEY1-KEY4
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
    GPIO_Init(GPIOE, &GPIO_InitStructure);

}

//���������
/********************
���ԭ��
���Ŷ�Ϊ��������ʱ����ֹʱA,B��Ϊ�ߵ�ƽ��
��A�͵�ƽʱ˵����ť��������ʱ��AΪ�͵�ƽ�����ʱ������B��0��1������������Ϊ��ת����ת��;
B��1��0������������ת����ת��
********************/

//��ť������1��⣬ ����ֵΪ��⵽����ť����״̬
u8 Encoder_Check_One(void)
{
    static u8 encoder_now_b = 0;   //B���ڵ�״̬
    static u8 encoder_last_b = 0 ; //B��һ�ε�״̬
	static u8 updata=0;
	
	if(ES1_A&&ES1_B)  //A��B��Ϊ�ߵ�ƽ
	{
		updata = 0;
		Encoder_sample[one].encoder_state = Encoder_static; //��������ֹ״̬
		return Encoder_sample[one].encoder_state;  //������ť״̬
	}
	
	//������������е�����˵����ť������
	encoder_last_b = ES1_B;  //��¼B�ź�
	while(!ES1_A)  //�ȴ�A�ɵͱ��
	{
		encoder_now_b = ES1_B;  //��¼�ȴ��ڼ�� B�ź�
		updata = 1;
	}
	if(updata)
	{
		updata = 0;
		if((encoder_last_b==0)&&(encoder_now_b==1))
		{
			Encoder_sample[one].encoder_state = Encoder1_right;
		}
		else if((encoder_last_b==1)&&(encoder_now_b==0))
		{
			Encoder_sample[one].encoder_state = Encoder1_left;
		}
		else
		{
			Encoder_sample[one].encoder_state = Encoder_static; //������
		}
		return Encoder_sample[one].encoder_state;  //������ť״̬
	}
	
}


//��ť������2��⣬ ����ֵΪ��⵽����ť����״̬
u8 Encoder_Check_Two(void)
{
    static u8 encoder_now_b = 0;   //B���ڵ�״̬
    static u8 encoder_last_b = 0 ; //B��һ�ε�״̬
	static u8 updata=0;
	
	if(ES2_A&&ES2_B)  //A��B��Ϊ�ߵ�ƽ
	{
		updata = 0;
		Encoder_sample[two].encoder_state = Encoder_static; //��������ֹ״̬
		return Encoder_sample[two].encoder_state;  //������ť״̬
	}
	
	//������������е�����˵����ť������
	encoder_last_b = ES2_B;  //��¼B�ź�
	while(!ES2_A)  //�ȴ�A�ɵͱ��
	{
		encoder_now_b = ES2_B;  //��¼�ȴ��ڼ�� B�ź�
		updata = 1;
	}
	if(updata)
	{
		updata = 0;
		if((encoder_last_b==0)&&(encoder_now_b==1))
		{
			Encoder_sample[two].encoder_state = Encoder2_right;
		}
		else if((encoder_last_b==1)&&(encoder_now_b==0))
		{
			Encoder_sample[two].encoder_state = Encoder2_left;
		}
		else
		{
			Encoder_sample[two].encoder_state = Encoder_static; //������
		}
		return Encoder_sample[two].encoder_state;  //������ť״̬
	}
	
}

//��ť������3��⣬ ����ֵΪ��⵽����ť����״̬
u8 Encoder_Check_Three(void)
{
    static u8 encoder_now_b = 0;   //B���ڵ�״̬
    static u8 encoder_last_b = 0 ; //B��һ�ε�״̬
	static u8 updata=0;
	
	if(ES3_A&&ES3_B)  //A��B��Ϊ�ߵ�ƽ
	{
		updata = 0;
		Encoder_sample[three].encoder_state = Encoder_static; //��������ֹ״̬
		return Encoder_sample[three].encoder_state;  //������ť״̬
	}
	
	//������������е�����˵����ť������
	encoder_last_b = ES3_B;  //��¼B�ź�
	while(!ES3_A)  //�ȴ�A�ɵͱ��
	{
		encoder_now_b = ES3_B;  //��¼�ȴ��ڼ�� B�ź�
		updata = 1;
	}
	if(updata)
	{
		updata = 0;
		if((encoder_last_b==0)&&(encoder_now_b==1))
		{
			Encoder_sample[three].encoder_state = Encoder3_right;
		}
		else if((encoder_last_b==1)&&(encoder_now_b==0))
		{
			Encoder_sample[three].encoder_state = Encoder3_left;
		}
		else
		{
			Encoder_sample[three].encoder_state = Encoder_static; //������
		}
		return Encoder_sample[three].encoder_state;  //������ť״̬
	}
	
}