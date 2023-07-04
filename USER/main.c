#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sys.h"
#include "delay.h"
#include "usart.h"
//#include "hc05.h" 	 
//#include "usart3.h" 
#include "bcomponent.h"
#include "exti.h"
#include "remote.h"
#include "dac.h"
//#include "pwm.h"

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		// 设置系统中断优先级分组2
	delay_init(168);				// 延时初始化 
	
	uart_init(9600);				// 初始化串口
	BCOMPONENT_Init();				// 初始化自定义引脚
	EXTIX_Init();					// 外部中断初始化
	Remote_Init();					// 红外接收初始化
	Dac1_Init();		 			// DAC通道1初始化
	Dac2_Init();					// DAC通道2初始化
	
	u8 contrastState = 0;			// 对比度状态位	1-往左转 2-往右转
	u8 lightSource = 0;				// 光源状态位 	1-往左转 2-往右转
	u8 key = 0;						// 红外遥控输入
	u8 keyState = 0;				// 红外按键状态
	u8 warningState = 0;			// 限位警告状态
	
	// 占空比初始化
	//TIM1_PWM_Init(500-1, 168-1);	// 84M/84=1Mhz的计数频率,重装载值500，所以PWM频率为 1M/500=2Khz.     
	//TIM8_PWM_Init(500-1, 168-1);
	
	// 无刷电机 M6 不停转动
	//GPIO_SetBits(GPIOC, GPIO_Pin_8);
	//TIM_SetCompare4(TIM8, 100);
	
	/*
	使用占空比控制电机
	0-往右转  500-往左转
	TIM_SetCompare1(TIM1, 250);
	TIM_SetCompare2(TIM1, 250);
	TIM_SetCompare3(TIM1, 250);
	TIM_SetCompare1(TIM8, 250);
	TIM_SetCompare2(TIM8, 250);
	TIM_SetCompare4(TIM8, 0);
	*/
	
	/*
	while ( HC05_Init() ) 			// 初始化HC05蓝牙模块
	{
		delay_ms(100);
		printf("蓝牙初始化中...\r\n");
	}
	*/
	
	/*
	101-往左转  110-往右转
	
	M1:
	GPIO_SetBits(GPIOB, GPIO_Pin_0);		// PB0 = 1
	GPIO_ResetBits(GPIOE, GPIO_Pin_8);		// PE8 = 0
	GPIO_SetBits(GPIOE, GPIO_Pin_9);		// PE9 = 1

	GPIO_SetBits(GPIOB, GPIO_Pin_0);		// PB0 = 1
	GPIO_SetBits(GPIOE, GPIO_Pin_8);		// PE8 = 1
	GPIO_ResetBits(GPIOE, GPIO_Pin_9);		// PE9 = 0
		
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);		// PB0 = 0
	
	
	M2:
	GPIO_SetBits(GPIOE, GPIO_Pin_7);		// PE7 = 1
	GPIO_ResetBits(GPIOE, GPIO_Pin_10);	// PE10 = 0
	GPIO_SetBits(GPIOE, GPIO_Pin_11);		// PE11 = 1
	 
	GPIO_SetBits(GPIOE, GPIO_Pin_7);		// PE7 = 1
	GPIO_SetBits(GPIOE, GPIO_Pin_10);		// PE10 = 1
	GPIO_ResetBits(GPIOE, GPIO_Pin_11);	// PE11 = 0
	 
	GPIO_ResetBits(GPIOE, GPIO_Pin_7);		// PE7 = 0
	 
	 
	M3:
	GPIO_SetBits(GPIOE, GPIO_Pin_14);		// PE14 = 1
	GPIO_ResetBits(GPIOE, GPIO_Pin_13);	// PE13 = 0
	GPIO_SetBits(GPIOE, GPIO_Pin_12);		// PE12 = 1

	GPIO_SetBits(GPIOE, GPIO_Pin_14);		// PE14 = 1
	GPIO_SetBits(GPIOE, GPIO_Pin_13);		// PE13 = 1
	GPIO_ResetBits(GPIOE, GPIO_Pin_12);	// PE12 = 0
	 
	GPIO_ResetBits(GPIOE, GPIO_Pin_14);	// PE14 = 0
	 
	 
	M4:
	GPIO_SetBits(GPIOD, GPIO_Pin_8);		// PD8 = 1
	GPIO_ResetBits(GPIOA, GPIO_Pin_7);		// PA7 = 0
	GPIO_SetBits(GPIOC, GPIO_Pin_6);		// PC6 = 1
	 
	GPIO_SetBits(GPIOD, GPIO_Pin_8);		// PD8 = 1
	GPIO_SetBits(GPIOA, GPIO_Pin_7);		// PA7 = 1
	GPIO_ResetBits(GPIOC, GPIO_Pin_6);		// PC6 = 0
		
	GPIO_ResetBits(GPIOD, GPIO_Pin_8);		// PD8 = 0
	 
	 
	M5:
	GPIO_SetBits(GPIOG, GPIO_Pin_6);		// PG6 = 1
	GPIO_ResetBits(GPIOB, GPIO_Pin_14);	// PB14 = 0
	GPIO_SetBits(GPIOC, GPIO_Pin_7);		// PC7 = 1
	 
	GPIO_SetBits(GPIOG, GPIO_Pin_6);		// PG6 = 1
	GPIO_SetBits(GPIOB, GPIO_Pin_14);		// PB14 = 1
	GPIO_ResetBits(GPIOC, GPIO_Pin_7);		// PC7 = 0
	 
	GPIO_ResetBits(GPIOG, GPIO_Pin_6);		// PG6 = 0
	 
	 
	M6:
	GPIO_SetBits(GPIOC, GPIO_Pin_8);		// PC8 = 1
	GPIO_ResetBits(GPIOC, GPIO_Pin_8);		// PC8 = 0
	 
	 
	蓝牙输出
	USART3_RX_BUF[len] = 0;									// 加结束符
	printf("蓝牙发送的消息为: \r%s\r\n\r\n", USART3_RX_BUF);	// 发送数据到上位机
	 
	 
	串口输出
	printf("您发送的消息为: \r");
	for ( u8 t = 0; t < len; ++t )
	{
		USART_SendData(USART1, USART_RX_BUF[t]);         		// 向串口1发送数据
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);	// 等待发送结束
	}
	printf("\r\n\r\n");	// 插入换行
	*/
	
	while(1)
	{
		// 消抖
		delay_ms(10);
		
		// 调焦判断限位
		if ( LIMIT0 != 0 || LIMIT1 != 0 ) {
			GPIO_ResetBits(GPIOB, GPIO_Pin_0);	// PB0 = 0
		}
		
		// 变倍判断限位
		if ( LIMIT2 != 0 || LIMIT3 != 0 ) {
			GPIO_ResetBits(GPIOE, GPIO_Pin_7);	// PE7 = 0
		}
		
		// 对比度判断左限位
		if ( LIMIT4 != 0 && contrastState == 1 ) {
			GPIO_ResetBits(GPIOD, GPIO_Pin_8);	// PD8 = 0
			contrastState = 3;
		}
		
		// 对比度判断右限位
		if ( LIMIT5 != 0 && contrastState == 2 ) {
			GPIO_ResetBits(GPIOD, GPIO_Pin_8);	// PD8 = 0
			contrastState = 4;
		}
		
		// 双光源判断左限位
		if ( LIMIT6 != 0 && lightSource == 1 ) {
			GPIO_ResetBits(GPIOG, GPIO_Pin_6);	// PG6 = 0
			lightSource = 3;
		}
		
		// 双光源判断右限位
		if ( LIMIT7 != 0 && lightSource == 2 ) {
			GPIO_ResetBits(GPIOG, GPIO_Pin_6);	// PG6 = 0
			lightSource = 4;
		}

		/*
		// 蓝牙
		if( USART3_RX_STA & 0X8000 )
		{
			u8 len = USART3_RX_STA & 0X7FFF;
			
			// 调焦左旋钮 - 按下
			if ( USART3_RX_BUF[0] == 'a' ) {
				if ( LIMIT0 != 0 ) {
					u3_printf("FL\r\n");					// 调焦左限位已触发
				} else {
					GPIO_SetBits(GPIOB, GPIO_Pin_0);		// PB0 = 1
					GPIO_ResetBits(GPIOE, GPIO_Pin_8);		// PE8 = 0
					GPIO_SetBits(GPIOE, GPIO_Pin_9);		// PE9 = 1
					
					if ( LIMIT1 != 0 ) {
						// 右限位触发的情况下，先转一会确保离开限位
						delay_ms(500);
					}
				}
			}
			
			// 调焦左旋钮 - 抬起
			if ( USART3_RX_BUF[0] == 'b' ) {
				GPIO_ResetBits(GPIOB, GPIO_Pin_0);			// PB0 = 0
			}
				
			// 调焦右旋钮 - 按下
			if ( USART3_RX_BUF[0] == 'c' ) {
				if ( LIMIT1 != 0 ) {
					u3_printf("FR\r\n");					// 调焦右限位已触发
				} else {
					GPIO_SetBits(GPIOB, GPIO_Pin_0);		// PB0 = 1
					GPIO_SetBits(GPIOE, GPIO_Pin_8);		// PE8 = 1
					GPIO_ResetBits(GPIOE, GPIO_Pin_9);		// PE9 = 0
					
					if ( LIMIT0 != 0 ) {
						// 左限位触发的情况下，先转一会确保离开限位
						delay_ms(500);
					}
				}
			}
			
			// 调焦右旋钮 - 抬起
			if ( USART3_RX_BUF[0] == 'd' ) {
				GPIO_ResetBits(GPIOB, GPIO_Pin_0);			// PB0 = 0
			}
			
			//------------------------------------------------------------------------------
			
			// 变倍左旋钮 - 按下
			if ( USART3_RX_BUF[0] == 'e' ) {
				if ( LIMIT2 != 0 ) {
					u3_printf("ZL\r\n");					// 变倍左限位已触发
				} else {
					//
					// 点动模式
					GPIO_ResetBits(GPIOE, GPIO_Pin_10);		// PE10 = 0
					GPIO_SetBits(GPIOE, GPIO_Pin_11);		// PE11 = 1
					
					int count = 1;
					while( LIMIT2 == 0 )
					{
						if ( count == 20 ) {
							break;
						}
						
						GPIO_SetBits(GPIOE, GPIO_Pin_7);	// PE7 = 1
						delay_ms(2);
						GPIO_ResetBits(GPIOE, GPIO_Pin_7);	// PE7 = 0
						delay_ms(5);
						
						count++;
					}
					//
					
					GPIO_SetBits(GPIOE, GPIO_Pin_7);		// PE7 = 1
					GPIO_ResetBits(GPIOE, GPIO_Pin_10);		// PE10 = 0
					GPIO_SetBits(GPIOE, GPIO_Pin_11);		// PE11 = 1
					
					if ( LIMIT3 != 0 ) {
						// 右限位触发的情况下，先转一会确保离开限位
						delay_ms(100);
					}
				}
			}
			
			// 变倍左旋钮 - 抬起
			if ( USART3_RX_BUF[0] == 'f' ) {
				GPIO_ResetBits(GPIOE, GPIO_Pin_7);			// PE7 = 0
			}
				
			//  变倍右旋钮 - 按下
			if ( USART3_RX_BUF[0] == 'g' ) {
				if ( LIMIT3 != 0 ) {
					u3_printf("ZR\r\n");					// 变倍右限位已触发
				} else {
					//
					// 点动模式
					GPIO_SetBits(GPIOE, GPIO_Pin_10);		// PE10 = 1
					GPIO_ResetBits(GPIOE, GPIO_Pin_11);		// PE11 = 0
					
					int count = 1;
					while( LIMIT3 == 0 )
					{
						if ( count == 20 ) {
							break;
						}
						
						GPIO_SetBits(GPIOE, GPIO_Pin_7);	// PE7 = 1
						delay_ms(2);
						GPIO_ResetBits(GPIOE, GPIO_Pin_7);	// PE7 = 0
						delay_ms(5);
						
						count++;
					}
					//
					
					GPIO_SetBits(GPIOE, GPIO_Pin_7);		// PE7 = 1
					GPIO_SetBits(GPIOE, GPIO_Pin_10);		// PE10 = 1
					GPIO_ResetBits(GPIOE, GPIO_Pin_11);		// PE11 = 0
					
					if ( LIMIT2 != 0 ) {
						// 左限位触发的情况下，先转一会确保离开限位
						delay_ms(100);
					}
				}
			}
			
			//  变倍右旋钮 - 抬起
			if ( USART3_RX_BUF[0] == 'h' ) {
				GPIO_ResetBits(GPIOE, GPIO_Pin_7);			// PE7 = 0
			}

			//------------------------------------------------------------------------------
			
			// 明亮度左旋钮 - 按下
			if ( USART3_RX_BUF[0] == 'i' ) {
				GPIO_SetBits(GPIOE, GPIO_Pin_14);			// PE14 = 1
				GPIO_ResetBits(GPIOE, GPIO_Pin_13);			// PE13 = 0
				GPIO_SetBits(GPIOE, GPIO_Pin_12);			// PE12 = 1
			}
			
			// 明亮度左旋钮 - 抬起
			if ( USART3_RX_BUF[0] == 'j' ) {
				GPIO_ResetBits(GPIOE, GPIO_Pin_14);			// PE14 = 0
			}
			
			// 明亮度右旋钮 - 按下
			if ( USART3_RX_BUF[0] == 'k' ) {
				GPIO_SetBits(GPIOE, GPIO_Pin_14);			// PE14 = 1
				GPIO_SetBits(GPIOE, GPIO_Pin_13);			// PE13 = 1
				GPIO_ResetBits(GPIOE, GPIO_Pin_12);			// PE12 = 0
			}
			
			// 明亮度右旋钮 - 抬起
			if ( USART3_RX_BUF[0] == 'l' ) {
				GPIO_ResetBits(GPIOE, GPIO_Pin_14);			// PE14 = 0
			}
			
			//------------------------------------------------------------------------------
			
			// 对比度左旋钮 - 按下
			if ( USART3_RX_BUF[0] == 'm' )
			{
				if ( LIMIT4 != 0 && contrastState == 1 ) {	
					u3_printf("CL\r\n");					// 对比度左限位已触发
				} else {
					GPIO_SetBits(GPIOD, GPIO_Pin_8);		// PD8 = 1
					GPIO_ResetBits(GPIOA, GPIO_Pin_7);		// PA7 = 0
					GPIO_SetBits(GPIOC, GPIO_Pin_6);		// PC6 = 1
					contrastState = 1;						// 往左转
				}
			}
			
			// 对比度右旋钮 - 按下
			if ( USART3_RX_BUF[0] == 'n' )
			{
				if ( LIMIT5 != 0 && contrastState == 2 ) {
					u3_printf("CR\r\n");					// 对比度右限位已触发
				} else {
					GPIO_SetBits(GPIOD, GPIO_Pin_8);		// PD8 = 1
					GPIO_SetBits(GPIOA, GPIO_Pin_7);		// PA7 = 1
					GPIO_ResetBits(GPIOC, GPIO_Pin_6);		// PC6 = 0
					contrastState = 2;						// 往右转
				}
			}
			
			//------------------------------------------------------------------------------
			
			// 双光源左旋钮 - 按下
			if ( USART3_RX_BUF[0] == 'o' )
			{
				if ( LIMIT6 != 0 && lightSource == 1 ) {	
					u3_printf("LL\r\n");					// 双光源左限位已触发
				} else {
					GPIO_SetBits(GPIOG, GPIO_Pin_6);		// PG6 = 1
					GPIO_ResetBits(GPIOB, GPIO_Pin_14);		// PB14 = 0
					GPIO_SetBits(GPIOC, GPIO_Pin_7);		// PC7 = 1
					lightSource = 1;						// 往左转	
				}
			}
			
			// 双光源右旋钮 - 按下
			if ( USART3_RX_BUF[0] == 'p' )
			{
				if ( LIMIT7 != 0 && lightSource == 2 ) {
					u3_printf("LR\r\n");					// 双光源右限位已触发
				} else {
					GPIO_SetBits(GPIOG, GPIO_Pin_6);		// PG6 = 1
					GPIO_SetBits(GPIOB, GPIO_Pin_14);		// PB14 = 1
					GPIO_ResetBits(GPIOC, GPIO_Pin_7);		// PC7 = 0
					lightSource = 2;						// 往右转
				}
			}
			
			//------------------------------------------------------------------------------
			
			// 对准
			if ( USART3_RX_BUF[0] == 'q' ) {
				// 发送信号给上位机，打开对准相机
				printf("8");
			}
			
			// 测量
			if ( USART3_RX_BUF[0] == 'r' ) {
				// 发送信号给上位机，启动测量
				printf("9");
			}
			
			USART3_RX_STA = 0;
		}
		*/
		
		// 串口
		if ( USART_RX_STA & 0x8000 )
		{
			// 数据长度
			u8 len = USART_RX_STA & 0x3fff;
			
			// 调焦 M1
			if ( USART_RX_BUF[0] == 'a' ) {
				if ( LIMIT0 != 0 ) {
					printf("FL");							// 调焦左限位已触发
				} else {
					GPIO_SetBits(GPIOB, GPIO_Pin_0);		// PB0 = 1
					GPIO_ResetBits(GPIOE, GPIO_Pin_8);		// PE8 = 0
					GPIO_SetBits(GPIOE, GPIO_Pin_9);		// PE9 = 1
					
					if ( LIMIT1 != 0 ) {
						// 右限位触发的情况下，先转一会确保离开限位
						delay_ms(500);
					}
				}
			}
			
			if ( USART_RX_BUF[0] == 'b' ) {
				GPIO_ResetBits(GPIOB, GPIO_Pin_0);			// PB0 = 0
			}
			
			if ( USART_RX_BUF[0] == 'c' ) {
				if ( LIMIT1 != 0 ) {
					printf("FR");							// 调焦右限位已触发
				} else {
					GPIO_SetBits(GPIOB, GPIO_Pin_0);		// PB0 = 1
					GPIO_SetBits(GPIOE, GPIO_Pin_8);		// PE8 = 1
					GPIO_ResetBits(GPIOE, GPIO_Pin_9);		// PE9 = 0
					
					if ( LIMIT0 != 0 ) {
						// 左限位触发的情况下，先转一会确保离开限位
						delay_ms(500);
					}
				}
			}
			
			if ( USART_RX_BUF[0] == 'd' ) {
				GPIO_ResetBits(GPIOB, GPIO_Pin_0);			// PB0 = 0
			}
			
			//------------------------------------------------------------------------------
			
			// 变倍 M2
			if ( USART_RX_BUF[0] == 'e' ) {
				if ( LIMIT2 != 0 ) {
					printf("ZL");							// 变倍左限位已触发
				} else {
					GPIO_SetBits(GPIOE, GPIO_Pin_7);		// PE7 = 1
					GPIO_ResetBits(GPIOE, GPIO_Pin_10);		// PE10 = 0
					GPIO_SetBits(GPIOE, GPIO_Pin_11);		// PE11 = 1
					
					if ( LIMIT3 != 0 ) {
						// 右限位触发的情况下，先转一会确保离开限位
						delay_ms(100);
					}
				}
			}
			
			if ( USART_RX_BUF[0] == 'f' ) {
				GPIO_ResetBits(GPIOE, GPIO_Pin_7);			// PE7 = 0
			}
			
			if ( USART_RX_BUF[0] == 'g' ) {
				if ( LIMIT3 != 0 ) {
					printf("ZR");							// 变倍右限位已触发
				} else {
					GPIO_SetBits(GPIOE, GPIO_Pin_7);		// PE7 = 1
					GPIO_SetBits(GPIOE, GPIO_Pin_10);		// PE10 = 1
					GPIO_ResetBits(GPIOE, GPIO_Pin_11);		// PE11 = 0
					
					if ( LIMIT2 != 0 ) {
						// 左限位触发的情况下，先转一会确保离开限位
						delay_ms(100);
					}
				}
			}
			
			if ( USART_RX_BUF[0] == 'h' ) {
				GPIO_ResetBits(GPIOE, GPIO_Pin_7);			// PE7 = 0
			}
			
			//------------------------------------------------------------------------------
			
			// 明亮度 M3
			if ( USART_RX_BUF[0] == 'i' ) {
				GPIO_SetBits(GPIOE, GPIO_Pin_14);			// PE14 = 1
				GPIO_ResetBits(GPIOE, GPIO_Pin_13);			// PE13 = 0
				GPIO_SetBits(GPIOE, GPIO_Pin_12);			// PE12 = 1
			}
			
			if ( USART_RX_BUF[0] == 'j' ) {
				GPIO_ResetBits(GPIOE, GPIO_Pin_14);			// PE14 = 0
			}
			
			if ( USART_RX_BUF[0] == 'k' ) {
				GPIO_SetBits(GPIOE, GPIO_Pin_14);			// PE14 = 1
				GPIO_SetBits(GPIOE, GPIO_Pin_13);			// PE13 = 1
				GPIO_ResetBits(GPIOE, GPIO_Pin_12);			// PE12 = 0
			}
			
			if ( USART_RX_BUF[0] == 'l' ) {
				GPIO_ResetBits(GPIOE, GPIO_Pin_14);			// PE14 = 0
			}
			
			//------------------------------------------------------------------------------
			
			// 对比度 M4
			if ( USART_RX_BUF[0] == 'm' )
			{
				if ( LIMIT4 != 0 && (contrastState == 1 || contrastState == 3) ) {	
					printf("CL");							// 对比度左限位已触发
				} else {
					GPIO_SetBits(GPIOD, GPIO_Pin_8);		// PD8 = 1
					GPIO_ResetBits(GPIOA, GPIO_Pin_7);		// PA7 = 0
					GPIO_SetBits(GPIOC, GPIO_Pin_6);		// PC6 = 1
					contrastState = 1;						// 往左转
				}
			}
			
			if ( USART_RX_BUF[0] == 'n' )
			{
				if ( LIMIT5 != 0 && (contrastState == 2 || contrastState == 4) ) {
					printf("CR");							// 对比度右限位已触发
				} else {
					GPIO_SetBits(GPIOD, GPIO_Pin_8);		// PD8 = 1
					GPIO_SetBits(GPIOA, GPIO_Pin_7);		// PA7 = 1
					GPIO_ResetBits(GPIOC, GPIO_Pin_6);		// PC6 = 0
					contrastState = 2;						// 往右转
				}
			}
			
			//------------------------------------------------------------------------------
			
			// 双光源 M5
			if ( USART_RX_BUF[0] == 'o' )
			{
				if ( LIMIT6 != 0 && (lightSource == 1 || lightSource == 3) ) {	
					printf("LL");							// 双光源左限位已触发
				} else {
					GPIO_SetBits(GPIOG, GPIO_Pin_6);		// PG6 = 1
					GPIO_ResetBits(GPIOB, GPIO_Pin_14);		// PB14 = 0
					GPIO_SetBits(GPIOC, GPIO_Pin_7);		// PC7 = 1
					lightSource = 1;						// 往左转
				}
			}
			
			if ( USART_RX_BUF[0] == 'p' )
			{
				if ( LIMIT7 != 0 && (lightSource == 2 || lightSource == 4) ) {
					printf("LR");							// 双光源右限位已触发
				} else {
					GPIO_SetBits(GPIOG, GPIO_Pin_6);		// PG6 = 1
					GPIO_SetBits(GPIOB, GPIO_Pin_14);		// PB14 = 1
					GPIO_ResetBits(GPIOC, GPIO_Pin_7);		// PC7 = 0
					lightSource = 2;						// 往右转	
				}
			}
			
			//------------------------------------------------------------------------------
			
			// 明亮度 - 变亮
			if ( USART_RX_BUF[0] == '1' )
			{
				GPIO_SetBits(GPIOE, GPIO_Pin_13);			// PE13 = 1
				GPIO_ResetBits(GPIOE, GPIO_Pin_12);			// PE12 = 0
				
				GPIO_SetBits(GPIOE, GPIO_Pin_14);			// PE14 = 1
				delay_ms(15);
				GPIO_ResetBits(GPIOE, GPIO_Pin_14);			// PE14 = 0
			}
			
			if ( USART_RX_BUF[0] == '2' )
			{
				GPIO_SetBits(GPIOE, GPIO_Pin_13);			// PE13 = 1
				GPIO_ResetBits(GPIOE, GPIO_Pin_12);			// PE12 = 0
				
				GPIO_SetBits(GPIOE, GPIO_Pin_14);			// PE14 = 1
				delay_ms(30);
				GPIO_ResetBits(GPIOE, GPIO_Pin_14);			// PE14 = 0
			}
			
			if ( USART_RX_BUF[0] == '3' )
			{
				GPIO_SetBits(GPIOE, GPIO_Pin_13);			// PE13 = 1
				GPIO_ResetBits(GPIOE, GPIO_Pin_12);			// PE12 = 0
				
				GPIO_SetBits(GPIOE, GPIO_Pin_14);			// PE14 = 1
				delay_ms(45);
				GPIO_ResetBits(GPIOE, GPIO_Pin_14);			// PE14 = 0
			}
			
			// 明亮度 - 变暗
			if ( USART_RX_BUF[0] == '4' )
			{
				GPIO_ResetBits(GPIOE, GPIO_Pin_13);			// PE13 = 0
				GPIO_SetBits(GPIOE, GPIO_Pin_12);			// PE12 = 1
				
				GPIO_SetBits(GPIOE, GPIO_Pin_14);			// PE14 = 1
				delay_ms(15);
				GPIO_ResetBits(GPIOE, GPIO_Pin_14);			// PE14 = 0
			}
			
			if ( USART_RX_BUF[0] == '5' )
			{
				GPIO_ResetBits(GPIOE, GPIO_Pin_13);			// PE13 = 0
				GPIO_SetBits(GPIOE, GPIO_Pin_12);			// PE12 = 1
				
				GPIO_SetBits(GPIOE, GPIO_Pin_14);			// PE14 = 1
				delay_ms(30);
				GPIO_ResetBits(GPIOE, GPIO_Pin_14);			// PE14 = 0
			}
			
			if ( USART_RX_BUF[0] == '6' )
			{
				GPIO_ResetBits(GPIOE, GPIO_Pin_13);			// PE13 = 0
				GPIO_SetBits(GPIOE, GPIO_Pin_12);			// PE12 = 1
				
				GPIO_SetBits(GPIOE, GPIO_Pin_14);			// PE14 = 1
				delay_ms(45);
				GPIO_ResetBits(GPIOE, GPIO_Pin_14);			// PE14 = 0
			}
			
			// DA卡控制
			if ( USART_RX_BUF[0] == 'z' )
			{
				// 字符串截取
				//char *ret;
				//strncpy(ret, USART_RX_BUF + 2, len - 2);
				
				// 字符串分割，获取参数
				char *token = NULL;
				token = strtok(USART_RX_BUF, "-");

				token = strtok(NULL, "-");
				u8 channel = atoi(token);
				
				token = strtok(NULL, "-");
				u8 imageCount = atoi(token);
				
				token = strtok(NULL, "-");
				float wavelengthCount = atof(token);
				
				token = strtok(NULL, "-");
				float voltage_calibration = atof(token);
				
				token = strtok(NULL, "-");
				float voltage_start = atof(token);
				
				token = strtok(NULL, "-");
				float voltage_step = atof(token);
				
				token = strtok(NULL, "-");
				float exposure = atof(token);
				
				token = strtok(NULL, "-");
				u8 delay = atoi(token);
				
				token = strtok(NULL, "-");
				u8 duration_step = atoi(token);
				
				token = strtok(NULL, "-");
				u8 duration_dormancy = atoi(token);
				
				u32 x = 0;
				u32 y = 0;
				u32 w = 0;
				u32 h = 0;
				if ( wavelengthCount == 0 ) {
					token = strtok(NULL, "-");
					x = atoi(token);
					token = strtok(NULL, "-");
					y = atoi(token);
					token = strtok(NULL, "-");
					w = atoi(token);
					token = strtok(NULL, "-");
					h = atoi(token);
				}
				
				// 总电压 = 标定电压 * 波长范围
				float scanVoltage = 0;
				if ( wavelengthCount == 0 ) {
					scanVoltage = voltage_calibration;
				} else {
					scanVoltage = voltage_calibration * wavelengthCount;
				}
				
				// 电压间隔 = 总电压 / 采集数量
				double average = scanVoltage / (imageCount - 1);
				
				// 当前电压，计数电压间隔
				float current_voltage = 0;
				float average_voltage = voltage_start + average;
				int num = 0;
				
				// 初始电压为0
				if ( channel == 0 ) {
					DAC_SetChannel1Data(DAC_Align_12b_R, 0);
				} else {
					DAC_SetChannel2Data(DAC_Align_12b_R, 0);
				}
				
				while ( current_voltage < voltage_start + scanVoltage + average )
				{
					// 第一次电压超过起始电压时，采集第一张图片
					if ( num == 0 && current_voltage >= voltage_start ) {
						delay_ms(duration_dormancy);
						printf("tp");
						delay_ms(exposure + delay);
						num++;
					}

					// 当前电压超过计数电压间隔时，采集图片并更新计数电压间隔
					if ( current_voltage >= average_voltage ) {
						current_voltage = average_voltage;
						delay_ms(duration_dormancy);
						printf("tp");
						delay_ms(exposure + delay);
						num++;
						average_voltage = voltage_start + average * num;
					}

					// 退出循环
					if ( num == imageCount ) {
						// 图像采集完毕
						if ( wavelengthCount == 0 ) {
							// 标定
							printf("cc-%d-%d-%d-%d", x, y, w, h);
						} else {
							// 测量
							printf("cp");
						}
						
						delay_ms(exposure + delay);
						
						// 电压回到 0V
						while ( current_voltage >= voltage_step * 5 )
						{
							current_voltage -= voltage_step * 5;
							float vol = current_voltage * 4096 / 10;
							
							if ( channel == 0 ) {
								DAC_SetChannel1Data(DAC_Align_12b_R, vol);
							} else {
								DAC_SetChannel2Data(DAC_Align_12b_R, vol);
							}
							
							delay_ms(duration_step);
						}
						
						if ( channel == 0 ) {
							DAC_SetChannel1Data(DAC_Align_12b_R, 0);
						} else {
							DAC_SetChannel2Data(DAC_Align_12b_R, 0);
						}

						break;
					}

					// 单步增压
					current_voltage += voltage_step;
					float vol = current_voltage * 4096 / 10;
					
					if ( channel == 0 ) {
						DAC_SetChannel1Data(DAC_Align_12b_R, vol);
					} else {
						DAC_SetChannel2Data(DAC_Align_12b_R, vol);
					}
					
					delay_ms(duration_step);
				}
			}

			USART_RX_STA = 0;
		}

		// 红外接收
		key = Remote_Scan();	
		if (key)
		{	 	  
			//printf("%d", key);
			switch (key)
			{
				// 小键盘0	调焦+
				case 104: {
					if ( warningState != 1 ) {
						if ( LIMIT1 != 0 ) {
							warningState = 1;	// 触发限位报警
							printf("FR");		// 调焦右限位已触发
						} 
					}
					
					if ( keyState != 1 ) {
						// 其他电机全部停止
						keyState = 1;
						GPIO_ResetBits(GPIOE, GPIO_Pin_7);	// 变倍停止  PE7 = 0
						GPIO_ResetBits(GPIOE, GPIO_Pin_14);	// 亮度停止	PE14 = 0
						
						if ( LIMIT1 == 0 ) {
							GPIO_SetBits(GPIOB, GPIO_Pin_0);	// PB0 = 1
							GPIO_SetBits(GPIOE, GPIO_Pin_8);	// PE8 = 1
							GPIO_ResetBits(GPIOE, GPIO_Pin_9);	// PE9 = 0
					
							// 左限位触发的情况下，先转一会确保离开限位
							if ( LIMIT0 != 0 ) {
								delay_ms(500);
							}
						}
					}
				} break;	
				
				// 小键盘1	调焦-
				case 48: {
					if ( warningState != 2 ) {
						if ( LIMIT0 != 0 ) {
							warningState = 2;	// 触发限位报警
							printf("FL");		// 调焦左限位已触发
						} 
					}
					
					if ( keyState != 2 ) {
						// 其他电机全部停止
						keyState = 2;
						GPIO_ResetBits(GPIOE, GPIO_Pin_7);	// 变倍停止  PE7 = 0
						GPIO_ResetBits(GPIOE, GPIO_Pin_14);	// 亮度停止	PE14 = 0
						
						if ( LIMIT0 == 0 ) {
							GPIO_SetBits(GPIOB, GPIO_Pin_0);	// PB0 = 1
							GPIO_ResetBits(GPIOE, GPIO_Pin_8);	// PE8 = 0
							GPIO_SetBits(GPIOE, GPIO_Pin_9);	// PE9 = 1
					
							// 右限位触发的情况下，先转一会确保离开限位
							if ( LIMIT1 != 0 ) {
								delay_ms(500);
							}
						}
					}
				} break;
				
				// 小键盘2	变倍+
				case 24: {
					if ( warningState != 3 ) {
						if ( LIMIT3 != 0 ) {
							warningState = 3;	// 触发限位报警
							printf("ZR");		// 变倍右限位已触发
						} 
					}
					
					if ( keyState != 3 ) {
						// 其他电机全部停止
						keyState = 3;
						GPIO_ResetBits(GPIOB, GPIO_Pin_0);	// 调焦停止	PB0 = 0
						GPIO_ResetBits(GPIOE, GPIO_Pin_14);	// 亮度停止	PE14 = 0
						
						if ( LIMIT3 == 0 ) {
							GPIO_SetBits(GPIOE, GPIO_Pin_7);	// PE7 = 1
							GPIO_SetBits(GPIOE, GPIO_Pin_10);	// PE10 = 1
							GPIO_ResetBits(GPIOE, GPIO_Pin_11);	// PE11 = 0
					
							if ( LIMIT2 != 0 ) {
								// 左限位触发的情况下，先转一会确保离开限位
								delay_ms(100);
							} else {
								// 点动模式，运动一下后停止
								delay_ms(50);
							}
							
							// 变倍电机停止
							GPIO_ResetBits(GPIOE, GPIO_Pin_7);	// PE7 = 0
						}
					}
				} break;
				
				// 小键盘3	变倍-
				case 122: {
					if ( warningState != 4 ) {
						if ( LIMIT2 != 0 ) {
							warningState = 4;	// 触发限位报警
							printf("ZL");		// 变倍左限位已触发
						} 
					}
					
					if ( keyState != 4 ) {
						// 其他电机全部停止
						keyState = 4;
						GPIO_ResetBits(GPIOB, GPIO_Pin_0);	// 调焦停止	PB0 = 0
						GPIO_ResetBits(GPIOE, GPIO_Pin_14);	// 亮度停止	PE14 = 0
						
						if ( LIMIT2 == 0 ) {
							GPIO_SetBits(GPIOE, GPIO_Pin_7);	// PE7 = 1
							GPIO_ResetBits(GPIOE, GPIO_Pin_10);	// PE10 = 0
							GPIO_SetBits(GPIOE, GPIO_Pin_11);	// PE11 = 1
					
							if ( LIMIT3 != 0 ) {
								// 右限位触发的情况下，先转一会确保离开限位
								delay_ms(100);
							} else {
								// 点动模式，运动一下后停止
								delay_ms(50);
							}
							
							// 变倍电机停止
							GPIO_ResetBits(GPIOE, GPIO_Pin_7);	// PE7 = 0
						}
					}
				} break;
				
				// 小键盘4	亮度-
				case 16: {
					if ( keyState != 5 ) {
						// 其他电机全部停止
						keyState = 5;
						GPIO_ResetBits(GPIOB, GPIO_Pin_0);	// 调焦停止	PB0 = 0
						GPIO_ResetBits(GPIOE, GPIO_Pin_7);	// 变倍停止  PE7 = 0
					
						GPIO_SetBits(GPIOE, GPIO_Pin_14);	// PE14 = 1
						GPIO_ResetBits(GPIOE, GPIO_Pin_13);	// PE13 = 0
						GPIO_SetBits(GPIOE, GPIO_Pin_12);	// PE12 = 1
						
						// 点动模式，运动一下后停止
						delay_ms(50);
						GPIO_ResetBits(GPIOE, GPIO_Pin_14);	// PE14 = 0
					}
				} break;
				
				// 小键盘5	亮度+
				case 56: {
					if ( keyState != 6 ) {
						// 其他电机全部停止
						keyState = 6;
						GPIO_ResetBits(GPIOB, GPIO_Pin_0);	// 调焦停止	PB0 = 0
						GPIO_ResetBits(GPIOE, GPIO_Pin_7);	// 变倍停止  PE7 = 0
					
						GPIO_SetBits(GPIOE, GPIO_Pin_14);	// PE14 = 1
						GPIO_SetBits(GPIOE, GPIO_Pin_13);	// PE13 = 1
						GPIO_ResetBits(GPIOE, GPIO_Pin_12);	// PE12 = 0
						
						// 点动模式，运动一下后停止
						delay_ms(50);
						GPIO_ResetBits(GPIOE, GPIO_Pin_14);	// PE14 = 0
					}
				} break;
				
				// 小键盘6	对比度切换
				case 90: {
					if ( contrastState == 0 || contrastState == 3 || contrastState == 4 ) {
						// 其他电机全部停止
						GPIO_ResetBits(GPIOB, GPIO_Pin_0);	// 调焦停止	PB0 = 0
						GPIO_ResetBits(GPIOE, GPIO_Pin_7);	// 变倍停止  PE7 = 0
						GPIO_ResetBits(GPIOE, GPIO_Pin_14);	// 亮度停止	PE14 = 0
						
						if ( contrastState == 3 ) {
							GPIO_SetBits(GPIOD, GPIO_Pin_8);		// PD8 = 1
							GPIO_SetBits(GPIOA, GPIO_Pin_7);		// PA7 = 1
							GPIO_ResetBits(GPIOC, GPIO_Pin_6);		// PC6 = 0
							contrastState = 2;						// 往右转
						} else {
							GPIO_SetBits(GPIOD, GPIO_Pin_8);		// PD8 = 1
							GPIO_ResetBits(GPIOA, GPIO_Pin_7);		// PA7 = 0
							GPIO_SetBits(GPIOC, GPIO_Pin_6);		// PC6 = 1
							contrastState = 1;						// 往左转
						}
					}
				} break;
				
				// 小键盘7	双光源切换
				case 66: {
					if ( lightSource == 0 || lightSource == 3 || lightSource == 4 ) {
						// 其他电机全部停止
						GPIO_ResetBits(GPIOB, GPIO_Pin_0);	// 调焦停止	PB0 = 0
						GPIO_ResetBits(GPIOE, GPIO_Pin_7);	// 变倍停止  PE7 = 0
						GPIO_ResetBits(GPIOE, GPIO_Pin_14);	// 亮度停止	PE14 = 0
						
						if ( lightSource == 3 ) {	
							GPIO_SetBits(GPIOG, GPIO_Pin_6);		// PG6 = 1
							GPIO_SetBits(GPIOB, GPIO_Pin_14);		// PB14 = 1
							GPIO_ResetBits(GPIOC, GPIO_Pin_7);		// PC7 = 0
							lightSource = 2;						// 往右转
						} else {
							GPIO_SetBits(GPIOG, GPIO_Pin_6);		// PG6 = 1
							GPIO_ResetBits(GPIOB, GPIO_Pin_14);		// PB14 = 0
							GPIO_SetBits(GPIOC, GPIO_Pin_7);		// PC7 = 1
							lightSource = 1;						// 往左转
						}
					}
				} break;
				
				// 小键盘8	测量
				case 74: {
					if ( keyState == 0 ) {
						keyState = 7;
						printf("9");
					}
				} break;
				
				// 小键盘9	对准
				case 82: {
					if ( keyState == 0 ) {
						keyState = 8;
						printf("8");
					}
				} break;
			}
		} else {
			if ( keyState != 0 ) {
				// 没有按键按下，状态还原
				keyState = 0;
				warningState = 0;
				GPIO_ResetBits(GPIOB, GPIO_Pin_0);	// 调焦停止	PB0 = 0
			}
		}
	}
}
