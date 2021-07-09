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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		// 设置系统中断优先级分组2
	delay_init(168);				// 延时初始化 
	
	uart_init(9600);				// 初始化串口
	BCOMPONENT_Init();				// 初始化自定义引脚
	EXTIX_Init();					// 外部中断初始化
	
	while ( HC05_Init() ) 			// 初始化HC05蓝牙模块
	{
		delay_ms(100);
		printf("蓝牙初始化中...\r\n");
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
		// 消抖
		delay_ms(10);
		
		// 判断限位
		if ( LIMIT0 != 0 || LIMIT1 != 0 ) {
			// 调焦限位触发
			GPIO_ResetBits(GPIOB, GPIO_Pin_0);	// PB0 = 0
		}
		if ( LIMIT2 != 0 || LIMIT3 != 0 ) {
			// 变倍限位触发
			GPIO_ResetBits(GPIOE, GPIO_Pin_7);	// PE7 = 0
		}
		if ( LIMIT4 != 0 || LIMIT5 != 0 ) {
			// 对比度限位触发
			GPIO_ResetBits(GPIOD, GPIO_Pin_8);	// PD8 = 0
		}
		
		// 蓝牙
		if( USART3_RX_STA & 0X8000 )
		{
			u8 len = USART3_RX_STA & 0X7FFF;
			
			// 调焦左旋钮 - 按下
			if ( USART3_RX_BUF[0] == '1' ) {
				GPIO_SetBits(GPIOB, GPIO_Pin_0);		// PB0 = 1
				GPIO_ResetBits(GPIOE, GPIO_Pin_8);		// PE8 = 0
				GPIO_SetBits(GPIOE, GPIO_Pin_9);		// PE9 = 1
				u3_printf("Focus - reduce pressed !\r\n");
			}
			
			// 调焦左旋钮 - 抬起
			if ( USART3_RX_BUF[0] == '2' ) {
				GPIO_ResetBits(GPIOB, GPIO_Pin_0);		// PB0 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_8);		// PE8 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_9);		// PE9 = 0
				u3_printf("Focus - reduce released !\r\n");
			}
				
			// 调焦右旋钮 - 按下
			if ( USART3_RX_BUF[0] == '3' ) {
				GPIO_SetBits(GPIOB, GPIO_Pin_0);		// PB0 = 1
				GPIO_SetBits(GPIOE, GPIO_Pin_8);		// PE8 = 1
				GPIO_ResetBits(GPIOE, GPIO_Pin_9);		// PE9 = 0
				u3_printf("Focus - increase pressed !\r\n");
			}
			
			// 调焦右旋钮 - 抬起
			if ( USART3_RX_BUF[0] == '4' ) {
				GPIO_ResetBits(GPIOB, GPIO_Pin_0);		// PB0 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_8);		// PE8 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_9);		// PE9 = 0
				u3_printf("Focus - increase released !\r\n");
			}
			
			//------------------------------------------------------------------------------
			
			// 变倍左旋钮 - 按下
			if ( USART3_RX_BUF[0] == '5' ) {
				GPIO_SetBits(GPIOE, GPIO_Pin_7);		// PE7 = 1
				GPIO_ResetBits(GPIOE, GPIO_Pin_10);		// PE10 = 0
				GPIO_SetBits(GPIOE, GPIO_Pin_11);		// PE11 = 1
				u3_printf("Zoom - reduce pressed !\r\n");
			}
			
			// 变倍左旋钮 - 抬起
			if ( USART3_RX_BUF[0] == '6' ) {
				GPIO_ResetBits(GPIOE, GPIO_Pin_7);		// PE7 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_10);		// PE10 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_11);		// PE11 = 0
				u3_printf("Zoom - reduce released !\r\n");
			}
				
			//  变倍右旋钮 - 按下
			if ( USART3_RX_BUF[0] == '7' ) {
				GPIO_SetBits(GPIOE, GPIO_Pin_7);		// PE7 = 1
				GPIO_SetBits(GPIOE, GPIO_Pin_10);		// PE10 = 1
				GPIO_ResetBits(GPIOE, GPIO_Pin_11);		// PE11 = 0
				u3_printf("Zoom - increase pressed !\r\n");
			}
			
			
			//  变倍右旋钮 - 抬起
			if ( USART3_RX_BUF[0] == '8' ) {
				GPIO_ResetBits(GPIOE, GPIO_Pin_7);		// PE7 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_10);		// PE10 = 0
				GPIO_ResetBits(GPIOE, GPIO_Pin_11);		// PE11 = 0
				u3_printf("Zoom - increase released !\r\n");
			}

			//------------------------------------------------------------------------------
			
			// 对比度
			if ( USART3_RX_BUF[0] == 'a' ) {
				// 先根据限位确定位置，再转到另一个位置
				
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
			
			// 对准
			if ( USART3_RX_BUF[0] == 'b' ) {
				// 发送信号给上位机，打开对准相机
				u3_printf("Align !\r\n");
				printf("8");
			}
			
			// 测量
			if ( USART3_RX_BUF[0] == 'c' ) {
				// 发送信号给上位机，启动测量
				u3_printf("Measure !\r\n");
				printf("9");
			}
			
			/*
			USART3_RX_BUF[len] = 0;									// 加结束符
			printf("蓝牙发送的消息为: \r%s\r\n\r\n", USART3_RX_BUF);	// 发送数据到上位机
			*/
			
			USART3_RX_STA = 0;
		}
		
		// 串口
		if ( USART_RX_STA & 0x8000 )
		{
			u8 len = USART_RX_STA & 0x3fff;	// 得到此次接收到的数据长度
			
			// 调焦 M1
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
			
			// 变倍 M5
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
			
			// 明亮度 M3
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
			
			// 对比度 M4
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
			
			// 明亮度 - 变亮
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
			
			// 明亮度 - 变暗
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
			printf("您发送的消息为: \r");
			for ( u8 t = 0; t < len; ++t )
			{
				USART_SendData(USART1, USART_RX_BUF[t]);         		// 向串口1发送数据
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);	// 等待发送结束
			}
			printf("\r\n\r\n");	// 插入换行
			*/

			USART_RX_STA = 0;
		}
	}
}
