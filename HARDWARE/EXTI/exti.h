#ifndef __EXTI_H
#define __EXIT_H 
#include "sys.h"

/*
(1)使能被重新映射到的I/O端口时钟

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

(2)使能被重新映射的外设时钟

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

(3)使能AFIO功能的时钟

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

(4)进行重映射

    GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);
	
	
	中断编程的顺序：
    1. 初始化IO口为输入；
    2. 开启IO口复用时钟，设置IO口与中断线的映射关系；
    3. 开启与该IO口相对的线上中断/事件，设置触发条件；
    4. 配置中断分组（NVIC），并使能中断；
	5. 编写中断服务函数；
	
参考链接：
https://blog.csdn.net/zzwdkxx/article/details/9036679
https://blog.csdn.net/weixin_43793181/article/details/109056730
https://blog.csdn.net/zht_2000/article/details/103556556
https://blog.csdn.net/feilusia/article/details/52859232
 */

#define LIMIT0 	GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0) 	// PD0	调焦左限位
#define LIMIT1 	GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_1)	// PD1	调焦右限位
#define LIMIT2 	GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2) 	// PD2	变倍左限位
#define LIMIT3 	GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3) 	// PD3	变倍右限位
#define LIMIT4 	GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4) 	// PD4	对比度左限位
#define LIMIT5 	GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_5) 	// PD5	对比度右限位
#define LIMIT6 	GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_6) 	// PD6	预留限位
#define LIMIT7 	GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7) 	// PD7	预留限位

void EXTIX_Init(void);	// 外部中断初始化		

#endif

























