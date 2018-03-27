#ifndef __KEY_H
#define __KEY_H
#include "sys.h"

#define col1  PCout(9)
#define col2  PCout(10)
#define col3  PCout(11)
#define row1  PCin(6)
#define row2  PCin(7)
#define row3  PCin(8)

typedef enum
{
	KEY_NONE = 0,
	KEY_INPUT,
	KEY_ESC,
	KEY_OUTPUT,
	KEY_SYSTEM,
}KEY_ENUM;


void KEY_GPIO_Init(void); //按键硬件初始化
u8 KEY_Scan(u8 mode); //按键扫描函数
#endif
