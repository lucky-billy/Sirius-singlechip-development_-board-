#include "pwm.h"

void TIM1_PWM_Init(u32 arr1, u32 psc1)
{     
	// 此部分需手动修改IO口设置
    GPIO_InitTypeDef  GPIO_InitStructure;	
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
     
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);    	// TIM1时钟使能  
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);   	// 使能PORTA时钟
	
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_TIM1);  	// GPIOA8复用为定时器1
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1);  	// GPIOA7复用为定时器1
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource10,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource12,GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_TIM1);
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;  	// GPIOE8/E9(M1)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;       		// 复用功能
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     		// 推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   		// 不上下拉
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 		// 速度100MHz
    GPIO_Init(GPIOE,&GPIO_InitStructure);              		// 初始化PA8
     
	TIM_TimeBaseStructure.TIM_Prescaler = psc1;             // Timer clock = sysclock /(TIM_Prescaler+1) = 168M 定时器分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   // 向上计数模式
	TIM_TimeBaseStructure.TIM_Period = arr1;                      // 自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;        
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);          // 初始化定时器1
		
 	// 初始化TIM1 Channel1 PWM模式	
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;     	// 选择定时器模式:TIM脉冲宽度调制模式2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  	// 比较输出使能
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; // 互补输出允许
    TIM_OCInitStructure.TIM_Pulse = (arr1+1)/2;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  		// High为占空比高极性，此时占空比为50%，Low则为反极性，占空比为50%
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;  	// 互补输出，与以上相反
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
 
    TIM_OC1Init(TIM1,&TIM_OCInitStructure);   				// 根据T指定的参数初始化外设TIM1OC1
	TIM_OC2Init(TIM1,&TIM_OCInitStructure); 
	TIM_OC3Init(TIM1,&TIM_OCInitStructure); 
	
 	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  		// 使能TIM1在CCR1上的预装载寄存器（CR自动装载默认是打开的）
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
    TIM_ARRPreloadConfig(TIM1,ENABLE);						// ARPE使能(ARR自动装载默认是打开的，可以不设置)
    TIM_Cmd(TIM1,ENABLE);
    TIM_CtrlPWMOutputs(TIM1,ENABLE); 						// 使能TIM1的PWM输出       
}

void TIM8_PWM_Init(u32 arr8,u32 psc8)
{     
	// 此部分需手动修改IO口设置
    GPIO_InitTypeDef  GPIO_InitStructure;	
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
     
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);    // TIM1时钟使能  
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);   // 使能PORTA时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM8);  // GPIOA8复用为定时器1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_TIM8); // GPIOA7复用为定时器1
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM8);
     
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;  				// GPIOE8/E9(M1)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;       		// 复用功能
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     		// 推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   		// 不上下拉
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 		// 速度100MHz
    GPIO_Init(GPIOA,&GPIO_InitStructure);              		// 初始化PA8
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;  			// GPIOE8/E9(M1)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;       		// 复用功能
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     		// 推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   		// 不上下拉
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 		// 速度100MHz
    GPIO_Init(GPIOB,&GPIO_InitStructure);              		// 初始化PA8
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_9;	// GPIOE8/E9(M1)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;       		// 复用功能
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     		// 推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   		// 不上下拉
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 		// 速度100MHz
    GPIO_Init(GPIOC,&GPIO_InitStructure);              		// 初始化PA8
	 
	TIM_TimeBaseStructure.TIM_Prescaler = psc8;             // Timer clock = sysclock /(TIM_Prescaler+1) = 168M 定时器分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	// 向上计数模式
	TIM_TimeBaseStructure.TIM_Period = arr8;                    // 自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;        
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure);          // 初始化定时器1
		
 	// 初始化TIM1 Channel1 PWM模式	
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;     	// 选择定时器模式:TIM脉冲宽度调制模式2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 	// 比较输出使能
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;	// 互补输出允许
    TIM_OCInitStructure.TIM_Pulse = (arr8+1)/2;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  		// High为占空比高极性，此时占空比为50%，Low则为反极性，占空比为50%
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;  	// 互补输出，与以上相反
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
 
    TIM_OC1Init(TIM8,&TIM_OCInitStructure);   				// 根据T指定的参数初始化外设TIM1OC1
	TIM_OC2Init(TIM8,&TIM_OCInitStructure); 
	TIM_OC3Init(TIM8,&TIM_OCInitStructure); 
	TIM_OC4Init(TIM8,&TIM_OCInitStructure);
	
 	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  		// 使能TIM1在CCR1上的预装载寄存器（CR自动装载默认是打开的）
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
	
    TIM_ARRPreloadConfig(TIM8,ENABLE);						// ARPE使能(ARR自动装载默认是打开的，可以不设置)
    TIM_Cmd(TIM8,ENABLE);
    TIM_CtrlPWMOutputs(TIM8,ENABLE); 						// 使能TIM1的PWM输出                           
}	