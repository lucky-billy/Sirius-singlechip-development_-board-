#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sys.h"
#include "delay.h"

#include "usart.h"
#include "hc05.h" 	 
#include "usart3.h" 
#include "bcomponent.h"
#include "exti.h"

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		// ����ϵͳ�ж����ȼ�����2
	delay_init(168);				// ��ʱ��ʼ�� 
	
	uart_init(9600);				// ��ʼ������
	BCOMPONENT_Init();				// ��ʼ���Զ�������
	EXTIX_Init();					// �ⲿ�жϳ�ʼ��
	
	while ( HC05_Init() ) 			// ��ʼ��HC05����ģ��
	{
		delay_ms(100);
		printf("������ʼ����...\r\n");
	}
	
	/*
	 M1:
	 GPIO_SetBits(GPIOB, GPIO_Pin_0);		// PB0 = 1
	 GPIO_ResetBits(GPIOE, GPIO_Pin_8);		// PE8 = 0
	 GPIO_SetBits(GPIOE, GPIO_Pin_9);		// PE9 = 1

	 GPIO_SetBits(GPIOB, GPIO_Pin_0);		// PB0 = 1
	 GPIO_SetBits(GPIOE, GPIO_Pin_8);		// PE8 = 1
	 GPIO_ResetBits(GPIOE, GPIO_Pin_9);		// PE9 = 0
		
	 GPIO_ResetBits(GPIOB, GPIO_Pin_0);		// PB0 = 0
	 GPIO_ResetBits(GPIOE, GPIO_Pin_8);		// PE8 = 0
	 GPIO_ResetBits(GPIOE, GPIO_Pin_9);		// PE9 = 0
	 
	
	 M2:
	 GPIO_SetBits(GPIOE, GPIO_Pin_7);		// PE7 = 1
	 GPIO_ResetBits(GPIOE, GPIO_Pin_10);	// PE10 = 0
	 GPIO_SetBits(GPIOE, GPIO_Pin_11);		// PE11 = 1
	 
	 GPIO_SetBits(GPIOE, GPIO_Pin_7);		// PE7 = 1
	 GPIO_SetBits(GPIOE, GPIO_Pin_10);		// PE10 = 1
	 GPIO_ResetBits(GPIOE, GPIO_Pin_11);	// PE11 = 0
	 
	 GPIO_ResetBits(GPIOE, GPIO_Pin_7);		// PE7 = 0
	 GPIO_ResetBits(GPIOE, GPIO_Pin_10);	// PE10 = 0
	 GPIO_ResetBits(GPIOE, GPIO_Pin_11);	// PE11 = 0
	 
	 
	 M3:
	 GPIO_SetBits(GPIOE, GPIO_Pin_14);		// PE14 = 1
	 GPIO_ResetBits(GPIOE, GPIO_Pin_12);	// PE12 = 0
	 GPIO_SetBits(GPIOE, GPIO_Pin_13);		// PE13 = 1
	 
	 GPIO_SetBits(GPIOE, GPIO_Pin_14);		// PE14 = 1
	 GPIO_SetBits(GPIOE, GPIO_Pin_12);		// PE12 = 1
	 GPIO_ResetBits(GPIOE, GPIO_Pin_13);	// PE13 = 0
	 
	 GPIO_ResetBits(GPIOE, GPIO_Pin_14);	// PE14 = 0
	 GPIO_ResetBits(GPIOE, GPIO_Pin_12);	// PE12 = 0
	 GPIO_ResetBits(GPIOE, GPIO_Pin_13);	// PE13 = 0
	 
	 
	 M4:
	 GPIO_SetBits(GPIOD, GPIO_Pin_8);		// PD8 = 1
	 GPIO_ResetBits(GPIOA, GPIO_Pin_7);		// PA7 = 0
	 GPIO_SetBits(GPIOC, GPIO_Pin_6);		// PC6 = 1
	 
	 GPIO_SetBits(GPIOD, GPIO_Pin_8);		// PD8 = 1
	 GPIO_SetBits(GPIOA, GPIO_Pin_7);		// PA7 = 1
	 GPIO_ResetBits(GPIOC, GPIO_Pin_6);		// PC6 = 0
		
	 GPIO_ResetBits(GPIOD, GPIO_Pin_8);		// PD8 = 0
	 GPIO_ResetBits(GPIOA, GPIO_Pin_7);		// PA7 = 0
	 GPIO_ResetBits(GPIOC, GPIO_Pin_6);		// PC6 = 0
	 
	 
	 M5:
	 GPIO_SetBits(GPIOC, GPIO_Pin_9);		// PC9 = 1
	 GPIO_ResetBits(GPIOB, GPIO_Pin_14);	// PB14 = 0
	 GPIO_SetBits(GPIOC, GPIO_Pin_7);		// PC7 = 1
	 
	 GPIO_SetBits(GPIOC, GPIO_Pin_9);		// PC9 = 1
	 GPIO_SetBits(GPIOB, GPIO_Pin_14);		// PB14 = 1
	 GPIO_ResetBits(GPIOC, GPIO_Pin_7);		// PC7 = 0
	 
	 GPIO_ResetBits(GPIOC, GPIO_Pin_9);		// PC9 = 0
	 GPIO_ResetBits(GPIOB, GPIO_Pin_14);	// PB14 = 0
	 GPIO_ResetBits(GPIOC, GPIO_Pin_7);		// PC7 = 0
	 
	 
	 M6:
	 GPIO_SetBits(GPIOG, GPIO_Pin_7);		// PG7 = 1
	 GPIO_ResetBits(GPIOB, GPIO_Pin_15);	// PB15 = 0
	 GPIO_SetBits(GPIOC, GPIO_Pin_8);		// PC8 = 1
	 
	 GPIO_SetBits(GPIOG, GPIO_Pin_7);		// PG7 = 1
	 GPIO_SetBits(GPIOB, GPIO_Pin_15);		// PB15 = 1
	 GPIO_ResetBits(GPIOC, GPIO_Pin_8);		// PC8 = 0
	 
	 GPIO_ResetBits(GPIOG, GPIO_Pin_7);		// PG7 = 0
	 GPIO_ResetBits(GPIOB, GPIO_Pin_15);	// PB15 = 0
	 GPIO_ResetBits(GPIOC, GPIO_Pin_8);		// PC8 = 0
	 */
	
	while(1)
	{
		// ����
		delay_ms(10);
		
		// �ж���λ
		if ( LIMIT0 != 0 || LIMIT1 != 0 ) {
			// ������λ����
			GPIO_ResetBits(GPIOB, GPIO_Pin_0);	// PB0 = 0
		}
		if ( LIMIT2 != 0 || LIMIT3 != 0 ) {
			// �䱶��λ����
			GPIO_ResetBits(GPIOE, GPIO_Pin_7);	// PE7 = 0
		}
		if ( LIMIT4 != 0 || LIMIT5 != 0 ) {
			// �Աȶ���λ����
			GPIO_ResetBits(GPIOD, GPIO_Pin_8);	// PD8 = 0
		}
		
		// ����
		if( USART3_RX_STA & 0X8000 )
		{
			u8 len = USART3_RX_STA & 0X7FFF;
			
			// ��������ť - ����
			if ( USART3_RX_BUF[0] == '1' ) {
				GPIO_SetBits(GPIOB, GPIO_Pin_0);		// PB0 = 1
				GPIO_ResetBits(GPIOE, GPIO_Pin_8);		// PE8 = 0
				GPIO_SetBits(GPIOE, GPIO_Pin_9);		// PE9 = 1
				u3_printf("Focus - reduce pressed !\r\n");
			}
			
			// ��������ť - ̧��
			if ( USART3_RX_BUF[0] == '2' ) {
				GPIO_ResetBits(GPIOB, GPIO_Pin_0);		// PB0 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_8);		// PE8 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_9);		// PE9 = 0
				u3_printf("Focus - reduce released !\r\n");
			}
				
			// ��������ť - ����
			if ( USART3_RX_BUF[0] == '3' ) {
				GPIO_SetBits(GPIOB, GPIO_Pin_0);		// PB0 = 1
				GPIO_SetBits(GPIOE, GPIO_Pin_8);		// PE8 = 1
				GPIO_ResetBits(GPIOE, GPIO_Pin_9);		// PE9 = 0
				u3_printf("Focus - increase pressed !\r\n");
			}
			
			// ��������ť - ̧��
			if ( USART3_RX_BUF[0] == '4' ) {
				GPIO_ResetBits(GPIOB, GPIO_Pin_0);		// PB0 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_8);		// PE8 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_9);		// PE9 = 0
				u3_printf("Focus - increase released !\r\n");
			}
			
			//------------------------------------------------------------------------------
			
			// �䱶����ť - ����
			if ( USART3_RX_BUF[0] == '5' ) {
				GPIO_SetBits(GPIOE, GPIO_Pin_7);		// PE7 = 1
				GPIO_ResetBits(GPIOE, GPIO_Pin_10);		// PE10 = 0
				GPIO_SetBits(GPIOE, GPIO_Pin_11);		// PE11 = 1
				u3_printf("Zoom - reduce pressed !\r\n");
			}
			
			// �䱶����ť - ̧��
			if ( USART3_RX_BUF[0] == '6' ) {
				GPIO_ResetBits(GPIOE, GPIO_Pin_7);		// PE7 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_10);		// PE10 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_11);		// PE11 = 0
				u3_printf("Zoom - reduce released !\r\n");
			}
				
			//  �䱶����ť - ����
			if ( USART3_RX_BUF[0] == '7' ) {
				GPIO_SetBits(GPIOE, GPIO_Pin_7);		// PE7 = 1
				GPIO_SetBits(GPIOE, GPIO_Pin_10);		// PE10 = 1
				GPIO_ResetBits(GPIOE, GPIO_Pin_11);		// PE11 = 0
				u3_printf("Zoom - increase pressed !\r\n");
			}
			
			
			//  �䱶����ť - ̧��
			if ( USART3_RX_BUF[0] == '8' ) {
				GPIO_ResetBits(GPIOE, GPIO_Pin_7);		// PE7 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_10);		// PE10 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_11);		// PE11 = 0
				u3_printf("Zoom - increase released !\r\n");
			}

			//------------------------------------------------------------------------------
			
			// �Աȶ�
			if ( USART3_RX_BUF[0] == 'a' ) {
				// �ȸ�����λȷ��λ�ã���ת����һ��λ��
				
				if ( LIMIT4 == 0 ) 
				{
					GPIO_SetBits(GPIOD, GPIO_Pin_8);		// PD8 = 1
					GPIO_SetBits(GPIOA, GPIO_Pin_7);		// PA7 = 1
					GPIO_ResetBits(GPIOC, GPIO_Pin_6);		// PC6 = 0
				}
				else if ( LIMIT5 == 0 )
				{
					GPIO_SetBits(GPIOD, GPIO_Pin_8);		// PD8 = 1
					GPIO_ResetBits(GPIOA, GPIO_Pin_7);		// PA7 = 0
					GPIO_SetBits(GPIOC, GPIO_Pin_6);		// PC6 = 1
				}

				u3_printf("Contrast !\r\n");
			}
			
			// ��׼
			if ( USART3_RX_BUF[0] == 'b' ) {
				// �����źŸ���λ�����򿪶�׼���
				u3_printf("Align !\r\n");
				printf("8");
			}
			
			// ����
			if ( USART3_RX_BUF[0] == 'c' ) {
				// �����źŸ���λ������������
				u3_printf("Measure !\r\n");
				printf("9");
			}
			
			/*
			USART3_RX_BUF[len] = 0;									// �ӽ�����
			printf("�������͵���ϢΪ: \r%s\r\n\r\n", USART3_RX_BUF);	// �������ݵ���λ��
			*/
			
			USART3_RX_STA = 0;
		}
		
		// ����
		if ( USART_RX_STA & 0x8000 )
		{
			u8 len = USART_RX_STA & 0x3fff;	// �õ��˴ν��յ������ݳ���
			
			// ���� M1
			if ( USART_RX_BUF[0] == 'a' )
			{
				GPIO_SetBits(GPIOB, GPIO_Pin_0);		// PB0 = 1
				GPIO_ResetBits(GPIOE, GPIO_Pin_8);		// PE8 = 0
				GPIO_SetBits(GPIOE, GPIO_Pin_9);		// PE9 = 1
				printf("Focus - reduce pressed !\r\n");
			}
			
			if ( USART_RX_BUF[0] == 'b' )
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_0);		// PB0 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_8);		// PE8 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_9);		// PE9 = 0
				printf("Focus - reduce released !\r\n");
			}
			
			if ( USART_RX_BUF[0] == 'c' )
			{
				GPIO_SetBits(GPIOB, GPIO_Pin_0);		// PB0 = 1
				GPIO_SetBits(GPIOE, GPIO_Pin_8);		// PE8 = 1
				GPIO_ResetBits(GPIOE, GPIO_Pin_9);		// PE9 = 0
				printf("Focus - increase pressed !\r\n");
			}
			
			if ( USART_RX_BUF[0] == 'd' )
			{
				GPIO_ResetBits(GPIOB, GPIO_Pin_0);		// PB0 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_8);		// PE8 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_9);		// PE9 = 0
				printf("Focus - increase released !\r\n");
			}
			
			//------------------------------------------------------------------------------
			
			// �䱶 M5
			if ( USART_RX_BUF[0] == 'e' )
			{
				GPIO_SetBits(GPIOE, GPIO_Pin_7);		// PE7 = 1
				GPIO_ResetBits(GPIOE, GPIO_Pin_10);		// PE10 = 0
				GPIO_SetBits(GPIOE, GPIO_Pin_11);		// PE11 = 1
				printf("Zoom - reduce pressed !\r\n");
			}
			
			if ( USART_RX_BUF[0] == 'f' )
			{
				GPIO_ResetBits(GPIOE, GPIO_Pin_7);		// PE7 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_10);		// PE10 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_11);		// PE11 = 0
				printf("Zoom - reduce released !\r\n");
			}
			
			if ( USART_RX_BUF[0] == 'g' )
			{
				GPIO_SetBits(GPIOE, GPIO_Pin_7);		// PE7 = 1
				GPIO_SetBits(GPIOE, GPIO_Pin_10);		// PE10 = 1
				GPIO_ResetBits(GPIOE, GPIO_Pin_11);		// PE11 = 0
				printf("Zoom - increase pressed !\r\n");
			}
			
			if ( USART_RX_BUF[0] == 'h' )
			{
				GPIO_ResetBits(GPIOE, GPIO_Pin_7);		// PE7 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_10);		// PE10 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_11);		// PE11 = 0
				printf("Zoom - increase released !\r\n");
			}
			
			//------------------------------------------------------------------------------
			
			// ������ M3
			if ( USART_RX_BUF[0] == 'i' )
			{
				GPIO_SetBits(GPIOE, GPIO_Pin_14);		// PE14 = 1
				GPIO_ResetBits(GPIOE, GPIO_Pin_12);		// PE12 = 0
				GPIO_SetBits(GPIOE, GPIO_Pin_13);		// PE13 = 1
				printf("Bright - reduce pressed !\r\n");
			}
			
			if ( USART_RX_BUF[0] == 'j' )
			{
				GPIO_ResetBits(GPIOE, GPIO_Pin_14);		// PE14 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_12);		// PE12 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_13);		// PE13 = 0
				printf("Bright - reduce released !\r\n");
			}
			
			if ( USART_RX_BUF[0] == 'k' )
			{
				GPIO_SetBits(GPIOE, GPIO_Pin_14);		// PE14 = 1
				GPIO_SetBits(GPIOE, GPIO_Pin_12);		// PE12 = 1
				GPIO_ResetBits(GPIOE, GPIO_Pin_13);		// PE13 = 0
				printf("Bright - increase pressed !\r\n");
			}
			
			if ( USART_RX_BUF[0] == 'l' )
			{
				GPIO_ResetBits(GPIOE, GPIO_Pin_14);		// PE14 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_12);		// PE12 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_13);		// PE13 = 0
				printf("Bright - increase released !\r\n");
			}
			
			//------------------------------------------------------------------------------
			
			// �Աȶ� M4
			if ( USART_RX_BUF[0] == 'm' )
			{
				if ( LIMIT4 == 0 ) 
				{
					printf("CL");
				}
				else if ( LIMIT5 == 0 )
				{
					GPIO_SetBits(GPIOD, GPIO_Pin_8);		// PD8 = 1
					GPIO_ResetBits(GPIOA, GPIO_Pin_7);		// PA7 = 0
					GPIO_SetBits(GPIOC, GPIO_Pin_6);		// PC6 = 1
					printf("Contrast - reduce pressed !\r\n");
				}
			}
			
			if ( USART_RX_BUF[0] == 'n' )
			{
				if ( LIMIT4 == 0 ) 
				{
					GPIO_SetBits(GPIOD, GPIO_Pin_8);		// PD8 = 1
					GPIO_SetBits(GPIOA, GPIO_Pin_7);		// PA7 = 1
					GPIO_ResetBits(GPIOC, GPIO_Pin_6);		// PC6 = 0
					printf("Contrast - increase pressed !\r\n");
				}
				else if ( LIMIT5 == 0 )
				{
					printf("CR");
				}
			}
			
			//------------------------------------------------------------------------------
			
			// ������ - ����
			if ( USART_RX_BUF[0] == '1' )
			{
				GPIO_SetBits(GPIOE, GPIO_Pin_12);		// PE12 = 1
				GPIO_ResetBits(GPIOE, GPIO_Pin_13);		// PE13 = 0
				GPIO_SetBits(GPIOE, GPIO_Pin_14);		// PE14 = 1
				delay_ms(50);
				GPIO_ResetBits(GPIOE, GPIO_Pin_12);		// PE12 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_13);		// PE13 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_14);		// PE14 = 0
				
				printf("Bright - increase 1 !\r\n");
			}
			
			if ( USART_RX_BUF[0] == '2' )
			{
				GPIO_SetBits(GPIOE, GPIO_Pin_12);		// PE12 = 1
				GPIO_ResetBits(GPIOE, GPIO_Pin_13);		// PE13 = 0
				GPIO_SetBits(GPIOE, GPIO_Pin_14);		// PE14 = 1
				delay_ms(100);
				GPIO_ResetBits(GPIOE, GPIO_Pin_12);		// PE12 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_13);		// PE13 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_14);		// PE14 = 0
				
				printf("Bright - increase 2 !\r\n");
			}
			
			if ( USART_RX_BUF[0] == '3' )
			{
				GPIO_SetBits(GPIOE, GPIO_Pin_12);		// PE12 = 1
				GPIO_ResetBits(GPIOE, GPIO_Pin_13);		// PE13 = 0
				GPIO_SetBits(GPIOE, GPIO_Pin_14);		// PE14 = 1
				delay_ms(150);
				GPIO_ResetBits(GPIOE, GPIO_Pin_12);		// PE12 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_13);		// PE13 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_14);		// PE14 = 0
				
				printf("Bright - increase 3 !\r\n");
			}
			
			// ������ - �䰵
			if ( USART_RX_BUF[0] == '4' )
			{
				GPIO_SetBits(GPIOE, GPIO_Pin_12);		// PE12 = 1
				GPIO_SetBits(GPIOE, GPIO_Pin_13);		// PE13 = 1
				GPIO_ResetBits(GPIOE, GPIO_Pin_14);		// PE14 = 0
				delay_ms(50);
				GPIO_ResetBits(GPIOE, GPIO_Pin_12);		// PE12 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_13);		// PE13 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_14);		// PE14 = 0
				
				printf("Bright - reduce 1 !\r\n");
			}
			
			if ( USART_RX_BUF[0] == '5' )
			{
				GPIO_SetBits(GPIOE, GPIO_Pin_12);		// PE12 = 1
				GPIO_SetBits(GPIOE, GPIO_Pin_13);		// PE13 = 1
				GPIO_ResetBits(GPIOE, GPIO_Pin_14);		// PE14 = 0
				delay_ms(100);
				GPIO_ResetBits(GPIOE, GPIO_Pin_12);		// PE12 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_13);		// PE13 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_14);		// PE14 = 0
				
				printf("Bright - reduce 2 !\r\n");
			}
			
			if ( USART_RX_BUF[0] == '6' )
			{
				GPIO_SetBits(GPIOE, GPIO_Pin_12);		// PE12 = 1
				GPIO_SetBits(GPIOE, GPIO_Pin_13);		// PE13 = 1
				GPIO_ResetBits(GPIOE, GPIO_Pin_14);		// PE14 = 0
				delay_ms(150);
				GPIO_ResetBits(GPIOE, GPIO_Pin_12);		// PE12 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_13);		// PE13 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_14);		// PE14 = 0
				
				printf("Bright - reduce 3 !\r\n");
			}
			
			/*
			printf("�����͵���ϢΪ: \r");
			for ( u8 t = 0; t < len; ++t )
			{
				USART_SendData(USART1, USART_RX_BUF[t]);         		// �򴮿�1��������
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);	// �ȴ����ͽ���
			}
			printf("\r\n\r\n");	// ���뻻��
			*/

			USART_RX_STA = 0;
		}
	}
}
