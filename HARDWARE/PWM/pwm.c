#include "pwm.h"

void PWM_Init()
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
	
	// M1����
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource8, GPIO_AF_TIM1);			// GPIOE8����Ϊ��ʱ��1
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_TIM1); 		// GPIOE9����Ϊ��ʱ��1
	
	// M2����
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource10, GPIO_AF_TIM1);		// GPIOE10����Ϊ��ʱ��1
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_TIM1); 		// GPIOE11����Ϊ��ʱ��1
	
	// M3����
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource12, GPIO_AF_TIM1); 		// GPIOE12����Ϊ��ʱ��1
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_TIM1); 		// GPIOE13����Ϊ��ʱ��1
	
	// M4����
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM8); 		// GPIOA7����Ϊ��ʱ��8
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM8); 		// GPIOC6����Ϊ��ʱ��8
	
	// M5����
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_TIM8); 		// GPIOB14����Ϊ��ʱ��8
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM8); 		// GPIOC7����Ϊ��ʱ��8
	
	// M6����
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_TIM8); 		// GPIOB15����Ϊ��ʱ��8
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM8); 		// GPIOC8����Ϊ��ʱ��8
	
	// TIM1��TIM8��ʱ������
	TIM_TimeBaseStructure.TIM_Prescaler=84-1;  						// ��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 		// ���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=240-1;   						// �Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);					// ��ʼ����ʱ��1
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);					// ��ʼ����ʱ��8

	// ��ʼ��TIM1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 				// ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 	// �Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; // ���ƶ�ӦCH1N���
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 		// �������:TIM����Ƚϼ��Ե�
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low; 		// �������:TIM_CH1N����Ƚϼ��Ե�
	TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Set;		// ����״̬��CHͨ������״̬
	TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCNIdleState_Set;
	TIM_OCInitStructure.TIM_Pulse = 120;							// ռ�ձ�
	
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  						// ����Tָ���Ĳ�����ʼ������TIM1_CH1
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable); 				// ʹ��TIM1��CCR1�ϵ�Ԥװ�ؼĴ���
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);  						// ����Tָ���Ĳ�����ʼ������TIM1_CH2
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable); 				// ʹ��TIM1��CCR2�ϵ�Ԥװ�ؼĴ���
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);  						// ����Tָ���Ĳ�����ʼ������TIM1_CH3
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable); 				// ʹ��TIM1��CCR3�ϵ�Ԥװ�ؼĴ���

	TIM_OC1Init(TIM8, &TIM_OCInitStructure);  						// ����Tָ���Ĳ�����ʼ������TIM8_CH1
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable); 				// ʹ��TIM8��CCR1�ϵ�Ԥװ�ؼĴ���
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);  						// ����Tָ���Ĳ�����ʼ������TIM8_CH2
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable); 				// ʹ��TIM8��CCR2�ϵ�Ԥװ�ؼĴ���
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);  						// ����Tָ���Ĳ�����ʼ������TIM8_CH3
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable); 				// ʹ��TIM8��CCR3�ϵ�Ԥװ�ؼĴ���

	TIM_ARRPreloadConfig(TIM1, ENABLE);								// ARPEʹ��TIM1
	TIM_ARRPreloadConfig(TIM8, ENABLE);								// ARPEʹ��TIM8
	
	TIM_Cmd(TIM1, ENABLE);  										// ʹ��TIM1
	TIM_CtrlPWMOutputs(TIM1, ENABLE);								// �߼���ʱ����Ӵ˾䣨��TIM1��TIM8Ϊ�߼���ʱ����
	TIM_Cmd(TIM8, ENABLE);  										// ʹ��TIM8
	TIM_CtrlPWMOutputs(TIM8, ENABLE);								// �߼���ʱ����Ӵ˾�
	
	/*
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
	TIM_SetCompare1(TIM1,0);	// M1
	TIM_SetCompare2(TIM1,120);	// M2
	TIM_SetCompare3(TIM1,120);	// M3
	TIM_SetCompare1(TIM8,120);	// M4
	TIM_SetCompare2(TIM8,120);	// M5
	TIM_SetCompare3(TIM8,120);	// M6
	*/
}
