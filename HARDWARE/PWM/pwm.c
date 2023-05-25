#include "pwm.h"

void TIM1_PWM_Init(u32 arr1, u32 psc1)
{     
	// �˲������ֶ��޸�IO������
    GPIO_InitTypeDef  GPIO_InitStructure;	
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
     
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);    	// TIM1ʱ��ʹ��  
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);   	// ʹ��PORTAʱ��
	
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_TIM1);  	// GPIOA8����Ϊ��ʱ��1
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1);  	// GPIOA7����Ϊ��ʱ��1
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource10,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource12,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_TIM1);
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;  	// GPIOE8/E9(M1)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;       		// ���ù���
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     		// ���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   		// ��������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 		// �ٶ�100MHz
    GPIO_Init(GPIOE,&GPIO_InitStructure);              		// ��ʼ��PA8
     
	TIM_TimeBaseStructure.TIM_Prescaler = psc1;             // Timer clock = sysclock /(TIM_Prescaler+1) = 168M ��ʱ����Ƶ
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   // ���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period = arr1;                      // �Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;        
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);          // ��ʼ����ʱ��1
		
 	// ��ʼ��TIM1 Channel1 PWMģʽ	
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;     	// ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  	// �Ƚ����ʹ��
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; // �����������
    TIM_OCInitStructure.TIM_Pulse = (arr1+1)/2;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  		// HighΪռ�ձȸ߼��ԣ���ʱռ�ձ�Ϊ50%��Low��Ϊ�����ԣ�ռ�ձ�Ϊ50%
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;  	// ����������������෴
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
 
    TIM_OC1Init(TIM1,&TIM_OCInitStructure);   				// ����Tָ���Ĳ�����ʼ������TIM1OC1
	TIM_OC2Init(TIM1,&TIM_OCInitStructure); 
	TIM_OC3Init(TIM1,&TIM_OCInitStructure); 
	
 	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  		// ʹ��TIM1��CCR1�ϵ�Ԥװ�ؼĴ�����CR�Զ�װ��Ĭ���Ǵ򿪵ģ�
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
    TIM_ARRPreloadConfig(TIM1,ENABLE);						// ARPEʹ��(ARR�Զ�װ��Ĭ���Ǵ򿪵ģ����Բ�����)
    TIM_Cmd(TIM1,ENABLE);
    TIM_CtrlPWMOutputs(TIM1,ENABLE); 						// ʹ��TIM1��PWM���       
}

void TIM8_PWM_Init(u32 arr8,u32 psc8)
{     
	// �˲������ֶ��޸�IO������
    GPIO_InitTypeDef  GPIO_InitStructure;	
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
     
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);    // TIM1ʱ��ʹ��  
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);   // ʹ��PORTAʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM8);  // GPIOA8����Ϊ��ʱ��1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_TIM8); // GPIOA7����Ϊ��ʱ��1
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM8);
     
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;  				// GPIOE8/E9(M1)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;       		// ���ù���
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     		// ���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   		// ��������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 		// �ٶ�100MHz
    GPIO_Init(GPIOA,&GPIO_InitStructure);              		// ��ʼ��PA8
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;  			// GPIOE8/E9(M1)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;       		// ���ù���
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     		// ���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   		// ��������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 		// �ٶ�100MHz
    GPIO_Init(GPIOB,&GPIO_InitStructure);              		// ��ʼ��PA8
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_9;	// GPIOE8/E9(M1)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;       		// ���ù���
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     		// ���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   		// ��������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 		// �ٶ�100MHz
    GPIO_Init(GPIOC,&GPIO_InitStructure);              		// ��ʼ��PA8
	 
	TIM_TimeBaseStructure.TIM_Prescaler = psc8;             // Timer clock = sysclock /(TIM_Prescaler+1) = 168M ��ʱ����Ƶ
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	// ���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period = arr8;                    // �Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;        
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure);          // ��ʼ����ʱ��1
		
 	// ��ʼ��TIM1 Channel1 PWMģʽ	
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;     	// ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 	// �Ƚ����ʹ��
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;	// �����������
    TIM_OCInitStructure.TIM_Pulse = (arr8+1)/2;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  		// HighΪռ�ձȸ߼��ԣ���ʱռ�ձ�Ϊ50%��Low��Ϊ�����ԣ�ռ�ձ�Ϊ50%
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;  	// ����������������෴
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
 
    TIM_OC1Init(TIM8,&TIM_OCInitStructure);   				// ����Tָ���Ĳ�����ʼ������TIM1OC1
	TIM_OC2Init(TIM8,&TIM_OCInitStructure); 
	TIM_OC3Init(TIM8,&TIM_OCInitStructure); 
	TIM_OC4Init(TIM8,&TIM_OCInitStructure);
	
 	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  		// ʹ��TIM1��CCR1�ϵ�Ԥװ�ؼĴ�����CR�Զ�װ��Ĭ���Ǵ򿪵ģ�
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
	
    TIM_ARRPreloadConfig(TIM8,ENABLE);						// ARPEʹ��(ARR�Զ�װ��Ĭ���Ǵ򿪵ģ����Բ�����)
    TIM_Cmd(TIM8,ENABLE);
    TIM_CtrlPWMOutputs(TIM8,ENABLE); 						// ʹ��TIM1��PWM���                           
}	