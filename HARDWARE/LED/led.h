#ifndef __LED_H
#define __LED_H
#include "sys.h"
#define LED1_On   GPIO_SetBits(GPIOC, GPIO_Pin_0)
#define LED1_Off  GPIO_ResetBits(GPIOC,GPIO_Pin_0)
#define LED2_On   GPIO_SetBits(GPIOC, GPIO_Pin_1)
#define LED2_Off  GPIO_ResetBits(GPIOC,GPIO_Pin_1)
#define LED3_On   GPIO_SetBits(GPIOC, GPIO_Pin_2)
#define LED3_Off  GPIO_ResetBits(GPIOC,GPIO_Pin_2)
#define LED4_On   GPIO_SetBits(GPIOC, GPIO_Pin_3)
#define LED4_Off  GPIO_ResetBits(GPIOC,GPIO_Pin_3)

void LED_GPIO_Init(void);

#endif
