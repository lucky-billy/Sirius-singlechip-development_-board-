#ifndef __EXTI_H
#define __EXIT_H 
#include "sys.h"

/*
(1)ʹ�ܱ�����ӳ�䵽��I/O�˿�ʱ��

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

(2)ʹ�ܱ�����ӳ�������ʱ��

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

(3)ʹ��AFIO���ܵ�ʱ��

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

(4)������ӳ��

    GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);
	
	
	�жϱ�̵�˳��
    1. ��ʼ��IO��Ϊ���룻
    2. ����IO�ڸ���ʱ�ӣ�����IO�����ж��ߵ�ӳ���ϵ��
    3. �������IO����Ե������ж�/�¼������ô���������
    4. �����жϷ��飨NVIC������ʹ���жϣ�
	5. ��д�жϷ�������
	
�ο����ӣ�
https://blog.csdn.net/zzwdkxx/article/details/9036679
https://blog.csdn.net/weixin_43793181/article/details/109056730
https://blog.csdn.net/zht_2000/article/details/103556556
https://blog.csdn.net/feilusia/article/details/52859232
 */

#define LIMIT0 	GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) 	// PA0	��������λ
#define LIMIT1 	GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6)	// PA6	��������λ
#define LIMIT2 	GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3) 	// PC3	�䱶����λ
#define LIMIT3 	GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) 	// PA3	�䱶����λ
#define LIMIT4 	GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2) 	// PC2	�Աȶ�����λ
#define LIMIT5 	GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) 	// PA2	�Աȶ�����λ
#define LIMIT6 	GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1) 	// PC1	˫��Դ����λ
#define LIMIT7 	GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) 	// PA1	˫��Դ����λ

void EXTIX_Init(void);	// �ⲿ�жϳ�ʼ��		

#endif

























