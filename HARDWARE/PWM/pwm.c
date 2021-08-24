#include "pwm.h"

void PWM_Init()
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
	
	// M1引脚
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource8, GPIO_AF_TIM1);			// GPIOE8复用为定时器1
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_TIM1); 		// GPIOE9复用为定时器1
	
	// M2引脚
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource10, GPIO_AF_TIM1);		// GPIOE10复用为定时器1
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_TIM1); 		// GPIOE11复用为定时器1
	
	// M3引脚
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource12, GPIO_AF_TIM1); 		// GPIOE12复用为定时器1
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_TIM1); 		// GPIOE13复用为定时器1
	
	// M4引脚
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM8); 		// GPIOA7复用为定时器8
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM8); 		// GPIOC6复用为定时器8
	
	// M5引脚
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_TIM8); 		// GPIOB14复用为定时器8
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM8); 		// GPIOC7复用为定时器8
	
	// M6引脚
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_TIM8); 		// GPIOB15复用为定时器8
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM8); 		// GPIOC8复用为定时器8
	
	// TIM1和TIM8定时器设置
	TIM_TimeBaseStructure.TIM_Prescaler=84-1;  						// 定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 		// 向上计数模式
	TIM_TimeBaseStructure.TIM_Period=240-1;   						// 自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);					// 初始化定时器1
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);					// 初始化定时器8

	// 初始化TIM1 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 				// 选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 	// 比较输出使能
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; // 控制对应CH1N输出
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 		// 输出极性:TIM输出比较极性低
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low; 		// 输出极性:TIM_CH1N输出比较极性低
	TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Set;		// 空闲状态下CH通道引脚状态
	TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCNIdleState_Set;
	TIM_OCInitStructure.TIM_Pulse = 120;							// 占空比
	
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  						// 根据T指定的参数初始化外设TIM1_CH1
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable); 				// 使能TIM1在CCR1上的预装载寄存器
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);  						// 根据T指定的参数初始化外设TIM1_CH2
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable); 				// 使能TIM1在CCR2上的预装载寄存器
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);  						// 根据T指定的参数初始化外设TIM1_CH3
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable); 				// 使能TIM1在CCR3上的预装载寄存器

	TIM_OC1Init(TIM8, &TIM_OCInitStructure);  						// 根据T指定的参数初始化外设TIM8_CH1
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable); 				// 使能TIM8在CCR1上的预装载寄存器
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);  						// 根据T指定的参数初始化外设TIM8_CH2
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable); 				// 使能TIM8在CCR2上的预装载寄存器
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);  						// 根据T指定的参数初始化外设TIM8_CH3
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable); 				// 使能TIM8在CCR3上的预装载寄存器

	TIM_ARRPreloadConfig(TIM1, ENABLE);								// ARPE使能TIM1
	TIM_ARRPreloadConfig(TIM8, ENABLE);								// ARPE使能TIM8
	
	TIM_Cmd(TIM1, ENABLE);  										// 使能TIM1
	TIM_CtrlPWMOutputs(TIM1, ENABLE);								// 高级定时器需加此句（仅TIM1与TIM8为高级定时器）
	TIM_Cmd(TIM8, ENABLE);  										// 使能TIM8
	TIM_CtrlPWMOutputs(TIM8, ENABLE);								// 高级定时器需加此句
	
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
