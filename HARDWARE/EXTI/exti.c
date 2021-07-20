#include "exti.h"
#include "delay.h" 

// �ⲿ�жϳ�ʼ������
void EXTIX_Init(void)
{
	// ��������
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);			// ʹ��GPIODʱ��
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;					// ��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;				// 100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;					// ����
	GPIO_Init(GPIOD, &GPIO_InitStructure);							// ��ʼ�� GPIOD0 - GPIOD7
	
	// �ⲿIO�ж�����
	EXTI_InitTypeDef   EXTI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);			// ʹ��SYSCFGʱ��
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource0);	// PE0 ���ӵ��ж���0
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource1);	// PE1 ���ӵ��ж���1
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource2);	// PE2 ���ӵ��ж���2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource3);	// PE3 ���ӵ��ж���3
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource4);	// PE4 ���ӵ��ж���4
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource5);	// PE5 ���ӵ��ж���5
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource6);	// PE6 ���ӵ��ж���6
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource7);	// PE7 ���ӵ��ж���7
	
	// ����EXTI_Line
	NVIC_InitTypeDef   NVIC_InitStructure;

	EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line1 | EXTI_Line2 | EXTI_Line3 | EXTI_Line4 | EXTI_Line5 | EXTI_Line6 | EXTI_Line7;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;				// �ж��¼�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 		// �½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;						// ʹ��LINE0
	EXTI_Init(&EXTI_InitStructure);									// ����
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;				// �ⲿ�ж�0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	// ��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;			// �����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					// ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);									// ����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;				// �ⲿ�ж�1
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	// ��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;			// �����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					// ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);									// ����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;				// �ⲿ�ж�2
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	// ��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;			// �����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					// ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);									// ����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;				// �ⲿ�ж�3
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	// ��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;			// �����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					// ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);									// ����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;				// �ⲿ�ж�4
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x04;	// ��ռ���ȼ�4
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;			// �����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					// ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);									// ����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;				// �ⲿ�ж�5-9
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x05;	// ��ռ���ȼ�5
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;			// �����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					// ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);									// ����   
}

// �ⲿ�ж�0�������
void EXTI0_IRQHandler(void)
{
	delay_ms(10);	// ����
	if( EXTI_GetITStatus(EXTI_Line0) == SET )	 
	{
		// ��������λ����
		//GPIO_ResetBits(GPIOB, GPIO_Pin_0);	// PB0 = 0
	}		 
	EXTI_ClearITPendingBit(EXTI_Line0); // ���LINE0�ϵ��жϱ�־λ 
}	

// �ⲿ�ж�1�������
void EXTI1_IRQHandler(void)
{
	delay_ms(10);	// ����
	if( EXTI_GetITStatus(EXTI_Line1) == SET )	 
	{
		// ��������λ����
		//GPIO_ResetBits(GPIOB, GPIO_Pin_0);	// PB0 = 0
	}	 
	EXTI_ClearITPendingBit(EXTI_Line1);	// ���LINE1�ϵ��жϱ�־λ 
}

// �ⲿ�ж�2�������
void EXTI2_IRQHandler(void)
{
	delay_ms(10);	// ����
	if( EXTI_GetITStatus(EXTI_Line2) == SET )	 
	{
		// �䱶����λ����
		//GPIO_ResetBits(GPIOE, GPIO_Pin_7);	// PE7 = 0
	}		 
	EXTI_ClearITPendingBit(EXTI_Line2); // ���LINE2�ϵ��жϱ�־λ  
}

// �ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{
	delay_ms(10);	// ����
	if( EXTI_GetITStatus(EXTI_Line3) == SET )	 
	{
		// �䱶����λ����
		//GPIO_ResetBits(GPIOE, GPIO_Pin_7);	// PE7 = 0
	}		 
	EXTI_ClearITPendingBit(EXTI_Line3);	// ���LINE3�ϵ��жϱ�־λ  
}

// �ⲿ�ж�4�������
void EXTI4_IRQHandler(void)
{
	delay_ms(10);	// ����
	if( EXTI_GetITStatus(EXTI_Line4) == SET )	 
	{
		// �Աȶ�����λ����
		//GPIO_ResetBits(GPIOD, GPIO_Pin_8);	// PD8 = 0
	}		 
	EXTI_ClearITPendingBit(EXTI_Line4);	// ���LINE4�ϵ��жϱ�־λ  
}

// �ⲿ�ж�5-9�������
void EXTI9_5_IRQHandler(void)
{
	if( EXTI_GetITStatus(EXTI_Line5) == SET )	 
	{
		delay_ms(10);	// ����
		
		// �Աȶ�����λ����
		//GPIO_ResetBits(GPIOD, GPIO_Pin_8);	// PD8 = 0
		
		EXTI_ClearITPendingBit(EXTI_Line5);	// ���LINE5�ϵ��жϱ�־λ  
	}
	
	if( EXTI_GetITStatus(EXTI_Line6) == SET )	 
	{
		delay_ms(10);	// ����
		
		// ��λ6����
		
		EXTI_ClearITPendingBit(EXTI_Line6);	// ���LINE6�ϵ��жϱ�־λ  
	}	
	
	if( EXTI_GetITStatus(EXTI_Line7) == SET )	 
	{
		delay_ms(10);	// ����
		
		// ��λ7����
		
		EXTI_ClearITPendingBit(EXTI_Line7);	// ���LINE7�ϵ��жϱ�־λ  
	}	
}