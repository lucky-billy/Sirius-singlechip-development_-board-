#ifndef __BCOMPONENT_H
#define __BCOMPONENT_H
#include "sys.h"

/*
 * 元件名称				ARM对应引脚				备注
 * JP1					PD0 - PD3				扩展IO
 * JP2					PD4 - PD7				扩展IO
 * JP3					PG9 - PG12				扩展IO
 * JP4					PE2 - PE5				扩展IO
 *
 * BlueTooth1			PC0 (GBC_LED)			蓝牙模块
 *						PB10 (USART3_TX)
 *						PB11 (USART3_RX)
 *						PF6 (GBC_KEY)
 *
 * M-Ctrl1 (1-9)		PB0						电机 1 使能
 *						PE8						电机 1
 *						PE9						电机 1
 *						PE10					电机 2
 *						PE7						电机 2 使能
 *						PE11					电机 2
 *						PE12					电机 3
 *						PE13					电机 3
 *						PE14					电机 3 使能
 *
 * M-Ctrl2 (1-9)		PB14					电机 5
 *						PB15					电机 6
 *						PD8						电机 4 使能
 *						PA7						电机 4
 *						PC6						电机 4
 *						PC7						电机 5
 *						PC8						电机 6
 *						PC9						电机 5 使能
 *						PG7						电机 6 使能
 */

void BCOMPONENT_Init(void);			// 初始化

#endif
