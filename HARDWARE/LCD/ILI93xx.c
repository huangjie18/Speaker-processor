#include "ILI93xx.h"
#include "delay.h"

#define LCD_WR_REG_DATA  LCD_WriteReg

/*
 * ��������LCD_GPIO_Config
 * ����  ������FSMC����LCD��I/O
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����        
 */
static void LCD_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /* config lcd gpio clock base on FSMC */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD 
	| RCC_APB2Periph_GPIOE , ENABLE);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    /* config tft back_light gpio base on the PT4101 BL*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;		
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
	/* config tft RST gpio */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 	 
    GPIO_Init(GPIOD, &GPIO_InitStructure); 	   
    
    /* config tft data lines base on FSMC
	 * data lines,FSMC-D0~D15: PD 14 15 0 1,PE 7 8 9 10 11 12 13 14 15,PD 8 9 10
	 */	
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9 | 
                                  GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
                                  GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
                                  GPIO_Pin_15;
    GPIO_Init(GPIOE, &GPIO_InitStructure); 
	
	
	/* config tft control lines base on FSMC
	 * PD4-FSMC_NOE  :LCD-RD
   * PD5-FSMC_NWE  :LCD-WR
	 * PD7-FSMC_NE1  :LCD-CS
   * PD11-FSMC_A16 :LCD-DC
	 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);  
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);
	/* tft control gpio init */	 
    GPIO_SetBits(GPIOD, GPIO_Pin_12);		 // RST	= 1			
    GPIO_SetBits(GPIOD, GPIO_Pin_4);		 // RD = 1  
    GPIO_SetBits(GPIOD, GPIO_Pin_5);		 // WR = 1 
	GPIO_SetBits(GPIOD, GPIO_Pin_11);		 // RS
    GPIO_SetBits(GPIOD, GPIO_Pin_7);		 //	CS = 1

	GPIO_SetBits(GPIOD, GPIO_Pin_13);	 	 //	BL = 1 
		
}

/*
 * ��������LCD_FSMC_Config
 * ����  ��LCD  FSMC ģʽ����
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����        
 */
#if FSMC_Enable
static void LCD_FSMC_Config(void)
{
    FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef  p; 
	FSMC_NORSRAMTimingInitTypeDef  readWriteTiming; 
	FSMC_NORSRAMTimingInitTypeDef  writeTiming;
    /* Enable the FSMC Clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
    
    p.FSMC_AddressSetupTime = 0x02;	 //��ַ����ʱ��
    p.FSMC_AddressHoldTime = 0x00;	 //��ַ����ʱ��
    p.FSMC_DataSetupTime = 0x05;		 //���ݽ���ʱ��
    p.FSMC_BusTurnAroundDuration = 0x00;
    p.FSMC_CLKDivision = 0x00;
    p.FSMC_DataLatency = 0x00;

    p.FSMC_AccessMode = FSMC_AccessMode_B;	 // һ��ʹ��ģʽB������LCD
    
    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;      //��������ʹ��NE1
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; // ���������ݵ�ַ
    FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR;    //NOR
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b; //�洢�����ݿ��Ϊ16bit
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;  //  �洢��дʹ��
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable; // ��дʹ��ͬ����ʱ��
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;  //��ʱ��
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;      //дʱ��
    
    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);   //��ʼ��FSMC����
    
    /* Enable FSMC Bank1_SRAM Bank */
    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE); 


	  
	
//	  readWriteTiming.FSMC_AddressSetupTime = 0x01;	 //��ַ����ʱ�䣨ADDSET��Ϊ2��HCLK 1/36M=27ns
//	  readWriteTiming.FSMC_AddressHoldTime = 0x00;	 //��ַ����ʱ�䣨ADDHLD��ģʽAδ�õ�	
//	  readWriteTiming.FSMC_DataSetupTime = 0x0f;		 // ���ݱ���ʱ��Ϊ16��HCLK,��ΪҺ������IC�Ķ����ݵ�ʱ���ٶȲ���̫�죬�����1289���IC��
//	  readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
//	  readWriteTiming.FSMC_CLKDivision = 0x00;
//	  readWriteTiming.FSMC_DataLatency = 0x00;
//	  readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //ģʽA 
//		

//		writeTiming.FSMC_AddressSetupTime = 0x00;	 //��ַ����ʱ�䣨ADDSET��Ϊ1��HCLK  
//	  writeTiming.FSMC_AddressHoldTime = 0x00;	 //��ַ����ʱ�䣨A		
//	  writeTiming.FSMC_DataSetupTime = 0x03;		 ////���ݱ���ʱ��Ϊ4��HCLK	
//	  writeTiming.FSMC_BusTurnAroundDuration = 0x00;
//	  writeTiming.FSMC_CLKDivision = 0x00;
//	  writeTiming.FSMC_DataLatency = 0x00;
//	  writeTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //ģʽA 

//	 
//	  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;//  ��������ʹ��NE4 ��Ҳ�Ͷ�ӦBTCR[6],[7]��
//	  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; // ���������ݵ�ַ
//	  FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;// FSMC_MemoryType_SRAM;  //SRAM   
//	  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//�洢�����ݿ��Ϊ16bit   
//	  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;// FSMC_BurstAccessMode_Disable; 
//	  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
//	  FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable; 
//	  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;   
//	  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
//	  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;	//  �洢��дʹ��
//	  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;   
//	  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable; // ��дʹ�ò�ͬ��ʱ��
//	  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable; 
//	  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming; //��дʱ��
//	  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &writeTiming;  //дʱ��

//	  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //��ʼ��FSMC����

// 	  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);  // ʹ��BANK1 
}

void WriteComm(u16 CMD)
{			
	*(__IO u16 *) (Bank1_LCD_C) = CMD;
}
 void WriteData(u16 tem_data)
{			
	*(__IO u16 *) (Bank1_LCD_D) = tem_data;
}

#else
void WriteComm(u16 CMD)
{
	u8 i;
	u8 temp1;
	LCD_RS = 0;
	LCD_RD = 1;
	LCD_CS = 0;
	LCD_WR = 1;
	for(i=0;i<16;i++)
	{
		temp1 = (CMD>>i)&0x0001;
		switch(i)
		{
			case 0: DB0 = temp1; break;
			case 1: DB1 = temp1; break;
			case 2: DB2 = temp1; break;
			case 3: DB3 = temp1; break;
			case 4: DB4 = temp1; break;
			case 5: DB5 = temp1; break;
			case 6: DB6 = temp1; break;
			case 7: DB7 = temp1; break;
			case 8: DB8 = temp1; break;
			case 9: DB9 = temp1; break;
			case 10: DB10 = temp1; break;
			case 11: DB11 = temp1; break;
			case 12: DB12 = temp1; break;
			case 13: DB13 = temp1; break;
			case 14: DB14 = temp1; break;
			case 15: DB15 = temp1; break;
		}
		
	}
	LCD_WR = 0;
	LCD_WR = 1;
	LCD_CS = 1;
}

void WriteData(u16 tem_data)
{
	u8 i;
	u8 temp1;
	LCD_RS = 0;
	LCD_RD = 1;
	LCD_CS = 0;
	LCD_WR = 1;
	for(i=0;i<16;i++)
	{
		temp1 = (tem_data>>i)&0x0001;
		switch(i)
		{
			case 0: DB0 = temp1; break;
			case 1: DB1 = temp1; break;
			case 2: DB2 = temp1; break;
			case 3: DB3 = temp1; break;
			case 4: DB4 = temp1; break;
			case 5: DB5 = temp1; break;
			case 6: DB6 = temp1; break;
			case 7: DB7 = temp1; break;
			case 8: DB8 = temp1; break;
			case 9: DB9 = temp1; break;
			case 10: DB10 = temp1; break;
			case 11: DB11 = temp1; break;
			case 12: DB12 = temp1; break;
			case 13: DB13 = temp1; break;
			case 14: DB14 = temp1; break;
			case 15: DB15 = temp1; break;
		}
		
	}
	LCD_WR = 0;
	LCD_WR = 1;
	LCD_CS = 1;
}
#endif

static void LCD_rst(void)
{
	GPIO_ResetBits(GPIOD,GPIO_Pin_12);
	delay_ms(100);
	GPIO_SetBits(GPIOD,GPIO_Pin_12);
	delay_ms(100);
}

void LCD_WriteReg(u16 LCD_Reg,u16 LCD_RegValue)
{	
	WriteComm(LCD_Reg);	 
	WriteData(LCD_RegValue);   		 
}
void Lcd_Initialize(void)
{
	LCD_GPIO_Config();  //IO����
	
	#if FSMC_Enable
	LCD_FSMC_Config();  //FSMC����
	#endif
	
	delay_ms(50);
	LCD_rst();
	
	//

	//
	WriteComm(0x2a);//Column Address Set
	WriteData(0x00);
	WriteData(0x00);
	WriteData(0x00);
	WriteData(0xEF);

	WriteComm(0x2B);//Row Address Set
	WriteData(0x00);
	WriteData(0x00);
	WriteData(0x01);
	WriteData(0x8F);

	WriteComm(0x35);//Tearing Effect Line on
	WriteData(0x00);

	WriteComm(0xB1);//Frame 
	WriteData(0x11);
	WriteData(0x0E);

	WriteComm(0xB4);//Inversion control
	WriteData(0x02);

	WriteComm(0xB6);//Display Control
	WriteData(0x1E);
	WriteData(0x02);

	WriteComm(0xC0);//Power control
	WriteData(0x10);

	WriteComm(0xC1);//Power control
	WriteData(0x01);
	WriteData(0x0B);

	WriteComm(0xC5);//Power control
	WriteData(0x17);
	WriteData(0x27);

	WriteComm(0xFA);//Gamma set
	WriteData(0x01);
	//****Gamma Setting****//
	//gamma  red
	WriteComm(0xE0);
	WriteData(0x00);
	WriteData(0x08);
	WriteData(0x11);
	WriteData(0x0D);
	WriteData(0x13);
	WriteData(0x17);
	WriteData(0x1C);
	WriteData(0x7B);
	WriteData(0x2D);
	WriteData(0x10);
	WriteData(0x2F);
	WriteData(0x29);
	WriteData(0x12);
	WriteData(0x1C);
	WriteData(0x2F);

	WriteComm(0xE1);
	WriteData(0x2B);
	WriteData(0x2E);
	WriteData(0x29);
	WriteData(0x0D);
	WriteData(0x16);
	WriteData(0x15);
	WriteData(0x29);
	WriteData(0x57);
	WriteData(0x2F);
	WriteData(0x09);
	WriteData(0x1A);
	WriteData(0x23);
	WriteData(0x31);
	WriteData(0x37);
	WriteData(0x3C);

	//gamma  GREEN
	WriteComm(0xE2);
	WriteData(0x00);
	WriteData(0x08);
	WriteData(0x11);
	WriteData(0x0D);
	WriteData(0x13);
	WriteData(0x17);
	WriteData(0x1C);
	WriteData(0x7B);
	WriteData(0x2D);
	WriteData(0x10);
	WriteData(0x2F);
	WriteData(0x29);
	WriteData(0x12);
	WriteData(0x1C);
	WriteData(0x2F);

	WriteComm(0xE3);
	WriteData(0x2B);
	WriteData(0x2E);
	WriteData(0x29);
	WriteData(0x0D);
	WriteData(0x16);
	WriteData(0x15);
	WriteData(0x29);
	WriteData(0x57);
	WriteData(0x2F);
	WriteData(0x09);
	WriteData(0x1A);
	WriteData(0x23);
	WriteData(0x31);
	WriteData(0x37);
	WriteData(0x3C);

	//gamma  BLUE
	WriteComm(0xE4);
	WriteData(0x00);
	WriteData(0x08);
	WriteData(0x11);
	WriteData(0x0D);
	WriteData(0x13);
	WriteData(0x17);
	WriteData(0x1C);
	WriteData(0x7B);
	WriteData(0x2D);
	WriteData(0x10);
	WriteData(0x2F);
	WriteData(0x29);
	WriteData(0x12);
	WriteData(0x1C);
	WriteData(0x2F);

	WriteComm(0xE5);
	WriteData(0x2B);
	WriteData(0x2E);
	WriteData(0x29);
	WriteData(0x0D);
	WriteData(0x16);
	WriteData(0x15);
	WriteData(0x29);
	WriteData(0x57);
	WriteData(0x2F);
	WriteData(0x09);
	WriteData(0x1A);
	WriteData(0x23);
	WriteData(0x31);
	WriteData(0x37);
	WriteData(0x3C);


	WriteComm(0x3A);
	WriteData(0x55);


	WriteComm(0x36);//
	WriteData(0x60);

	WriteComm(0x11);//sleep out
	delay_ms(120);

	WriteComm(0x29);//Display on


}

/**********************************************
��������Lcdȫ����������
���ܣ���Lcd������Ϊָ����ɫ
��ڲ�����color ָ��Lcdȫ����ɫ RGB(5-6-5)
����ֵ����
***********************************************/
void Lcd_Clear(u16 Color)
{
	u32 temp;
	WriteComm(0x2C);
	if((Color>>8)==(Color&0x00ff))
	{
		for (temp = 0; temp < 76800*2-1; temp++)
		{
			WriteData(0);
		}
	}	
	else
	{
		for (temp = 0; temp < 76800; temp++)
		{
			WriteData(0);
		}
	}

}
/**********************************************
��������BlockWrite
���ܣ���Lcdһ��������Ϊָ����ɫ
��ڲ�����x�������յ㣬y�������յ㣬color ָ��Lcdȫ����ɫ RGB(5-6-5)
����ֵ����
***********************************************/
void BlockWrite(unsigned int Xstart,unsigned int Xend,unsigned int Ystart,unsigned int Yend)
{
	WriteComm(0x2a);   
	WriteData(Xstart>>8);
	WriteData(Xstart&0xff);
	WriteData(Xend>>8);
	WriteData(Xend&0xff);

	WriteComm(0x2b);   
	WriteData(Ystart>>8);
	WriteData(Ystart&0xff);
	WriteData(Yend>>8);
	WriteData(Yend&0xff);
	
	WriteComm(0x2c);
}
/**********************************************
��������DrawPixel��㺯��
���ܣ���Lcdһ�����Ϊָ����ɫ
��ڲ�����x��λ�ã�y��λ�ã�color ָ��Lcdȫ����ɫ RGB(5-6-5)
����ֵ����
***********************************************/
void DrawPixel(u16 x,u16 y, int Color)
{
	BlockWrite(x,x,y,y);
	*(__IO u16 *)(Bank1_LCD_D) = Color;
}

/**********************************************
��������DrawPixel��㺯��
���ܣ���Lcdһ�����Ϊָ����ɫ
��ڲ�����x��λ�ã�y��λ�ã�color ָ��Lcdȫ����ɫ RGB(5-6-5)
����ֵ����
***********************************************/
u16 GetPoint(u16 x, u16 y)
{
	volatile u16 a;
	WriteComm(0x2a);   
	WriteData(x>>8);
	WriteData(x&0xff);
	WriteData((x+1)>>8);
	WriteData((x+1)&0xff);

	WriteComm(0x2b);   
	WriteData(y>>8);
	WriteData(y&0xff);
	WriteData((y+1)>>8);
	WriteData((y+1)&0xff);
	
	WriteComm(0x2E);
	
	a = *(__IO u16 *) (Bank1_LCD_D);
	a = *(__IO u16 *) (Bank1_LCD_D);
	a = (a&0xf800)|((a&0x00fc)<<3)|((*(__IO u16 *) (Bank1_LCD_D))>>11);
	return a;
}

/*************************************************
��������Lcd�����㶨λ����
���ܣ�ָ��320240Һ���ϵ�һ����Ϊд���ݵ���ʼ��
��ڲ�����x ���� 0~239
          y ���� 0~319
����ֵ����
*************************************************/
void Lcd_SetCursor(u16 x,u16 y)
{ 
	//�����ת
	LCD_WR_REG_DATA(0x20,y);//ˮƽ����
	LCD_WR_REG_DATA(0x21,x);//��ֱ����  
}