#ifndef __BCOMPONENT_H
#define __BCOMPONENT_H
#include "sys.h"

/*
 * Ԫ������				ARM��Ӧ����				��ע
 * JP1					PD0 - PD3				��չIO
 * JP2					PD4 - PD7				��չIO
 * JP3					PG9 - PG12				��չIO
 * JP4					PE2 - PE5				��չIO
 *
 * BlueTooth1			PC0 (GBC_LED)			����ģ��
 *						PB10 (USART3_TX)
 *						PB11 (USART3_RX)
 *						PF6 (GBC_KEY)
 *
 * M-Ctrl1 (1-9)		PB0						��� 1 ʹ��
 *						PE8						��� 1
 *						PE9						��� 1
 *						PE10					��� 2
 *						PE7						��� 2 ʹ��
 *						PE11					��� 2
 *						PE12					��� 3
 *						PE13					��� 3
 *						PE14					��� 3 ʹ��
 *
 * M-Ctrl2 (1-9)		PB14					��� 5
 *						PB15					��� 6
 *						PD8						��� 4 ʹ��
 *						PA7						��� 4
 *						PC6						��� 4
 *						PC7						��� 5
 *						PC8						��� 6
 *						PC9						��� 5 ʹ��
 *						PG7						��� 6 ʹ��
 */

void BCOMPONENT_Init(void);			// ��ʼ��

#endif
