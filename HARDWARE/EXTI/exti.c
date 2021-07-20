#include "exti.h"
#include "delay.h" 

// 外部中断初始化程序
void EXTIX_Init(void)
{
	// 引脚配置
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);			// 使能GPIOD时钟
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;					// 普通输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;				// 100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;					// 上拉
	GPIO_Init(GPIOD, &GPIO_InitStructure);							// 初始化 GPIOD0 - GPIOD7
	
	// 外部IO中断配置
	EXTI_InitTypeDef   EXTI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);			// 使能SYSCFG时钟
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource0);	// PE0 连接到中断线0
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource1);	// PE1 连接到中断线1
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource2);	// PE2 连接到中断线2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource3);	// PE3 连接到中断线3
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource4);	// PE4 连接到中断线4
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource5);	// PE5 连接到中断线5
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource6);	// PE6 连接到中断线6
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource7);	// PE7 连接到中断线7
	
	// 配置EXTI_Line
	NVIC_InitTypeDef   NVIC_InitStructure;

	EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line1 | EXTI_Line2 | EXTI_Line3 | EXTI_Line4 | EXTI_Line5 | EXTI_Line6 | EXTI_Line7;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;				// 中断事件
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 		// 下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;						// 使能LINE0
	EXTI_Init(&EXTI_InitStructure);									// 配置
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;				// 外部中断0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	// 抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;			// 子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					// 使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);									// 配置
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;				// 外部中断1
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	// 抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;			// 子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					// 使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);									// 配置
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;				// 外部中断2
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	// 抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;			// 子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					// 使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);									// 配置
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;				// 外部中断3
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	// 抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;			// 子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					// 使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);									// 配置
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;				// 外部中断4
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x04;	// 抢占优先级4
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;			// 子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					// 使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);									// 配置
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;				// 外部中断5-9
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x05;	// 抢占优先级5
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;			// 子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					// 使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);									// 配置   
}

// 外部中断0服务程序
void EXTI0_IRQHandler(void)
{
	delay_ms(10);	// 消抖
	if( EXTI_GetITStatus(EXTI_Line0) == SET )	 
	{
		// 调焦左限位触发
		//GPIO_ResetBits(GPIOB, GPIO_Pin_0);	// PB0 = 0
	}		 
	EXTI_ClearITPendingBit(EXTI_Line0); // 清除LINE0上的中断标志位 
}	

// 外部中断1服务程序
void EXTI1_IRQHandler(void)
{
	delay_ms(10);	// 消抖
	if( EXTI_GetITStatus(EXTI_Line1) == SET )	 
	{
		// 调焦右限位触发
		//GPIO_ResetBits(GPIOB, GPIO_Pin_0);	// PB0 = 0
	}	 
	EXTI_ClearITPendingBit(EXTI_Line1);	// 清除LINE1上的中断标志位 
}

// 外部中断2服务程序
void EXTI2_IRQHandler(void)
{
	delay_ms(10);	// 消抖
	if( EXTI_GetITStatus(EXTI_Line2) == SET )	 
	{
		// 变倍左限位触发
		//GPIO_ResetBits(GPIOE, GPIO_Pin_7);	// PE7 = 0
	}		 
	EXTI_ClearITPendingBit(EXTI_Line2); // 清除LINE2上的中断标志位  
}

// 外部中断3服务程序
void EXTI3_IRQHandler(void)
{
	delay_ms(10);	// 消抖
	if( EXTI_GetITStatus(EXTI_Line3) == SET )	 
	{
		// 变倍右限位触发
		//GPIO_ResetBits(GPIOE, GPIO_Pin_7);	// PE7 = 0
	}		 
	EXTI_ClearITPendingBit(EXTI_Line3);	// 清除LINE3上的中断标志位  
}

// 外部中断4服务程序
void EXTI4_IRQHandler(void)
{
	delay_ms(10);	// 消抖
	if( EXTI_GetITStatus(EXTI_Line4) == SET )	 
	{
		// 对比度左限位触发
		//GPIO_ResetBits(GPIOD, GPIO_Pin_8);	// PD8 = 0
	}		 
	EXTI_ClearITPendingBit(EXTI_Line4);	// 清除LINE4上的中断标志位  
}

// 外部中断5-9服务程序
void EXTI9_5_IRQHandler(void)
{
	if( EXTI_GetITStatus(EXTI_Line5) == SET )	 
	{
		delay_ms(10);	// 消抖
		
		// 对比度右限位触发
		//GPIO_ResetBits(GPIOD, GPIO_Pin_8);	// PD8 = 0
		
		EXTI_ClearITPendingBit(EXTI_Line5);	// 清除LINE5上的中断标志位  
	}
	
	if( EXTI_GetITStatus(EXTI_Line6) == SET )	 
	{
		delay_ms(10);	// 消抖
		
		// 限位6触发
		
		EXTI_ClearITPendingBit(EXTI_Line6);	// 清除LINE6上的中断标志位  
	}	
	
	if( EXTI_GetITStatus(EXTI_Line7) == SET )	 
	{
		delay_ms(10);	// 消抖
		
		// 限位7触发
		
		EXTI_ClearITPendingBit(EXTI_Line7);	// 清除LINE7上的中断标志位  
	}	
}