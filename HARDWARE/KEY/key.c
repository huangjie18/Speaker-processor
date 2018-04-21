#include "key.h"

u8 KEY_Value[][3] =
{
    {5, 6, 7},
    {3, 2, 4},
    {1},
};




//旋钮结构体
typedef struct
{
    Encoder_State encoder_state;  //旋钮状态
	

} Encoder_struct;
//旋钮实例化
Encoder_struct Encoder_sample[three+1];  //有三个旋钮
/*
 * 函数名：KEY_GPIO_Init
 * 描述  ：初始化按键的IO引脚
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
void KEY_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    //配置输入模式
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8; //KEY1-KEY4
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
    GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC6,7,8,采用矩阵扫描


    //配置输出模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure); //初始化GPIOC9,10,11

    col1 = 1; //全部按键无效操作，为低电平的时候才是有效操作
    col2 = 1;
    col3 = 1;
}

/*
 * 函数名：KEY_Scan
 * 描述  ：按键矩阵扫描函数
 * 输入  ：mode: 1则支持连按，0不支持连按；
 * 输出  ：按键值
 * 调用  ：内部调用
 */

u8 KEY_Scan(u8 mode)
{
    u8 i, j;
    static u8 key_up = 1;  //按键按松开标志
    if(mode)key_up = 1;    //支持连按
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
                    return KEY_Value[0][i - 1];   //第一行
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


//编码器引脚初始化
void Encoder_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4
                                   | GPIO_Pin_5
                                   | GPIO_Pin_6; //KEY1-KEY4
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
    GPIO_Init(GPIOE, &GPIO_InitStructure);

}

//编码器检测
/********************
检测原理：
引脚都为上拉输入时，静止时A,B都为高电平，
当A低电平时说明旋钮动作，这时在A为低电平的这段时间里，如果B从0到1上拉动作，则为右转（左转）;
B从1到0下拉动作，左转（右转）
********************/

//旋钮编码器1检测， 返回值为检测到的旋钮动作状态
u8 Encoder_Check_One(void)
{
    static u8 encoder_now_b = 0;   //B现在的状态
    static u8 encoder_last_b = 0 ; //B上一次的状态
	static u8 updata=0;
	
	if(ES1_A&&ES1_B)  //A和B都为高电平
	{
		updata = 0;
		Encoder_sample[one].encoder_state = Encoder_static; //编码器静止状态
		return Encoder_sample[one].encoder_state;  //返回旋钮状态
	}
	
	//如果程序能运行到这里说明旋钮动作了
	encoder_last_b = ES1_B;  //记录B信号
	while(!ES1_A)  //等待A由低变高
	{
		encoder_now_b = ES1_B;  //记录等待期间的 B信号
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
			Encoder_sample[one].encoder_state = Encoder_static; //错误检测
		}
		return Encoder_sample[one].encoder_state;  //返回旋钮状态
	}
	
}


//旋钮编码器2检测， 返回值为检测到的旋钮动作状态
u8 Encoder_Check_Two(void)
{
    static u8 encoder_now_b = 0;   //B现在的状态
    static u8 encoder_last_b = 0 ; //B上一次的状态
	static u8 updata=0;
	
	if(ES2_A&&ES2_B)  //A和B都为高电平
	{
		updata = 0;
		Encoder_sample[two].encoder_state = Encoder_static; //编码器静止状态
		return Encoder_sample[two].encoder_state;  //返回旋钮状态
	}
	
	//如果程序能运行到这里说明旋钮动作了
	encoder_last_b = ES2_B;  //记录B信号
	while(!ES2_A)  //等待A由低变高
	{
		encoder_now_b = ES2_B;  //记录等待期间的 B信号
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
			Encoder_sample[two].encoder_state = Encoder_static; //错误检测
		}
		return Encoder_sample[two].encoder_state;  //返回旋钮状态
	}
	
}

//旋钮编码器3检测， 返回值为检测到的旋钮动作状态
u8 Encoder_Check_Three(void)
{
    static u8 encoder_now_b = 0;   //B现在的状态
    static u8 encoder_last_b = 0 ; //B上一次的状态
	static u8 updata=0;
	
	if(ES3_A&&ES3_B)  //A和B都为高电平
	{
		updata = 0;
		Encoder_sample[three].encoder_state = Encoder_static; //编码器静止状态
		return Encoder_sample[three].encoder_state;  //返回旋钮状态
	}
	
	//如果程序能运行到这里说明旋钮动作了
	encoder_last_b = ES3_B;  //记录B信号
	while(!ES3_A)  //等待A由低变高
	{
		encoder_now_b = ES3_B;  //记录等待期间的 B信号
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
			Encoder_sample[three].encoder_state = Encoder_static; //错误检测
		}
		return Encoder_sample[three].encoder_state;  //返回旋钮状态
	}
	
}