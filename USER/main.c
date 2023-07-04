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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		// ����ϵͳ�ж����ȼ�����2
	delay_init(168);				// ��ʱ��ʼ�� 
	
	uart_init(9600);				// ��ʼ������
	BCOMPONENT_Init();				// ��ʼ���Զ�������
	EXTIX_Init();					// �ⲿ�жϳ�ʼ��
	Remote_Init();					// ������ճ�ʼ��
	Dac1_Init();		 			// DACͨ��1��ʼ��
	Dac2_Init();					// DACͨ��2��ʼ��
	
	u8 contrastState = 0;			// �Աȶ�״̬λ	1-����ת 2-����ת
	u8 lightSource = 0;				// ��Դ״̬λ 	1-����ת 2-����ת
	u8 key = 0;						// ����ң������
	u8 keyState = 0;				// ���ⰴ��״̬
	u8 warningState = 0;			// ��λ����״̬
	
	// ռ�ձȳ�ʼ��
	//TIM1_PWM_Init(500-1, 168-1);	// 84M/84=1Mhz�ļ���Ƶ��,��װ��ֵ500������PWMƵ��Ϊ 1M/500=2Khz.     
	//TIM8_PWM_Init(500-1, 168-1);
	
	// ��ˢ��� M6 ��ͣת��
	//GPIO_SetBits(GPIOC, GPIO_Pin_8);
	//TIM_SetCompare4(TIM8, 100);
	
	/*
	ʹ��ռ�ձȿ��Ƶ��
	0-����ת  500-����ת
	TIM_SetCompare1(TIM1, 250);
	TIM_SetCompare2(TIM1, 250);
	TIM_SetCompare3(TIM1, 250);
	TIM_SetCompare1(TIM8, 250);
	TIM_SetCompare2(TIM8, 250);
	TIM_SetCompare4(TIM8, 0);
	*/
	
	/*
	while ( HC05_Init() ) 			// ��ʼ��HC05����ģ��
	{
		delay_ms(100);
		printf("������ʼ����...\r\n");
	}
	*/
	
	/*
	101-����ת  110-����ת
	
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
	 
	 
	�������
	USART3_RX_BUF[len] = 0;									// �ӽ�����
	printf("�������͵���ϢΪ: \r%s\r\n\r\n", USART3_RX_BUF);	// �������ݵ���λ��
	 
	 
	�������
	printf("�����͵���ϢΪ: \r");
	for ( u8 t = 0; t < len; ++t )
	{
		USART_SendData(USART1, USART_RX_BUF[t]);         		// �򴮿�1��������
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);	// �ȴ����ͽ���
	}
	printf("\r\n\r\n");	// ���뻻��
	*/
	
	while(1)
	{
		// ����
		delay_ms(10);
		
		// �����ж���λ
		if ( LIMIT0 != 0 || LIMIT1 != 0 ) {
			GPIO_ResetBits(GPIOB, GPIO_Pin_0);	// PB0 = 0
		}
		
		// �䱶�ж���λ
		if ( LIMIT2 != 0 || LIMIT3 != 0 ) {
			GPIO_ResetBits(GPIOE, GPIO_Pin_7);	// PE7 = 0
		}
		
		// �Աȶ��ж�����λ
		if ( LIMIT4 != 0 && contrastState == 1 ) {
			GPIO_ResetBits(GPIOD, GPIO_Pin_8);	// PD8 = 0
			contrastState = 3;
		}
		
		// �Աȶ��ж�����λ
		if ( LIMIT5 != 0 && contrastState == 2 ) {
			GPIO_ResetBits(GPIOD, GPIO_Pin_8);	// PD8 = 0
			contrastState = 4;
		}
		
		// ˫��Դ�ж�����λ
		if ( LIMIT6 != 0 && lightSource == 1 ) {
			GPIO_ResetBits(GPIOG, GPIO_Pin_6);	// PG6 = 0
			lightSource = 3;
		}
		
		// ˫��Դ�ж�����λ
		if ( LIMIT7 != 0 && lightSource == 2 ) {
			GPIO_ResetBits(GPIOG, GPIO_Pin_6);	// PG6 = 0
			lightSource = 4;
		}

		/*
		// ����
		if( USART3_RX_STA & 0X8000 )
		{
			u8 len = USART3_RX_STA & 0X7FFF;
			
			// ��������ť - ����
			if ( USART3_RX_BUF[0] == 'a' ) {
				if ( LIMIT0 != 0 ) {
					u3_printf("FL\r\n");					// ��������λ�Ѵ���
				} else {
					GPIO_SetBits(GPIOB, GPIO_Pin_0);		// PB0 = 1
					GPIO_ResetBits(GPIOE, GPIO_Pin_8);		// PE8 = 0
					GPIO_SetBits(GPIOE, GPIO_Pin_9);		// PE9 = 1
					
					if ( LIMIT1 != 0 ) {
						// ����λ����������£���תһ��ȷ���뿪��λ
						delay_ms(500);
					}
				}
			}
			
			// ��������ť - ̧��
			if ( USART3_RX_BUF[0] == 'b' ) {
				GPIO_ResetBits(GPIOB, GPIO_Pin_0);			// PB0 = 0
			}
				
			// ��������ť - ����
			if ( USART3_RX_BUF[0] == 'c' ) {
				if ( LIMIT1 != 0 ) {
					u3_printf("FR\r\n");					// ��������λ�Ѵ���
				} else {
					GPIO_SetBits(GPIOB, GPIO_Pin_0);		// PB0 = 1
					GPIO_SetBits(GPIOE, GPIO_Pin_8);		// PE8 = 1
					GPIO_ResetBits(GPIOE, GPIO_Pin_9);		// PE9 = 0
					
					if ( LIMIT0 != 0 ) {
						// ����λ����������£���תһ��ȷ���뿪��λ
						delay_ms(500);
					}
				}
			}
			
			// ��������ť - ̧��
			if ( USART3_RX_BUF[0] == 'd' ) {
				GPIO_ResetBits(GPIOB, GPIO_Pin_0);			// PB0 = 0
			}
			
			//------------------------------------------------------------------------------
			
			// �䱶����ť - ����
			if ( USART3_RX_BUF[0] == 'e' ) {
				if ( LIMIT2 != 0 ) {
					u3_printf("ZL\r\n");					// �䱶����λ�Ѵ���
				} else {
					//
					// �㶯ģʽ
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
						// ����λ����������£���תһ��ȷ���뿪��λ
						delay_ms(100);
					}
				}
			}
			
			// �䱶����ť - ̧��
			if ( USART3_RX_BUF[0] == 'f' ) {
				GPIO_ResetBits(GPIOE, GPIO_Pin_7);			// PE7 = 0
			}
				
			//  �䱶����ť - ����
			if ( USART3_RX_BUF[0] == 'g' ) {
				if ( LIMIT3 != 0 ) {
					u3_printf("ZR\r\n");					// �䱶����λ�Ѵ���
				} else {
					//
					// �㶯ģʽ
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
						// ����λ����������£���תһ��ȷ���뿪��λ
						delay_ms(100);
					}
				}
			}
			
			//  �䱶����ť - ̧��
			if ( USART3_RX_BUF[0] == 'h' ) {
				GPIO_ResetBits(GPIOE, GPIO_Pin_7);			// PE7 = 0
			}

			//------------------------------------------------------------------------------
			
			// ����������ť - ����
			if ( USART3_RX_BUF[0] == 'i' ) {
				GPIO_SetBits(GPIOE, GPIO_Pin_14);			// PE14 = 1
				GPIO_ResetBits(GPIOE, GPIO_Pin_13);			// PE13 = 0
				GPIO_SetBits(GPIOE, GPIO_Pin_12);			// PE12 = 1
			}
			
			// ����������ť - ̧��
			if ( USART3_RX_BUF[0] == 'j' ) {
				GPIO_ResetBits(GPIOE, GPIO_Pin_14);			// PE14 = 0
			}
			
			// ����������ť - ����
			if ( USART3_RX_BUF[0] == 'k' ) {
				GPIO_SetBits(GPIOE, GPIO_Pin_14);			// PE14 = 1
				GPIO_SetBits(GPIOE, GPIO_Pin_13);			// PE13 = 1
				GPIO_ResetBits(GPIOE, GPIO_Pin_12);			// PE12 = 0
			}
			
			// ����������ť - ̧��
			if ( USART3_RX_BUF[0] == 'l' ) {
				GPIO_ResetBits(GPIOE, GPIO_Pin_14);			// PE14 = 0
			}
			
			//------------------------------------------------------------------------------
			
			// �Աȶ�����ť - ����
			if ( USART3_RX_BUF[0] == 'm' )
			{
				if ( LIMIT4 != 0 && contrastState == 1 ) {	
					u3_printf("CL\r\n");					// �Աȶ�����λ�Ѵ���
				} else {
					GPIO_SetBits(GPIOD, GPIO_Pin_8);		// PD8 = 1
					GPIO_ResetBits(GPIOA, GPIO_Pin_7);		// PA7 = 0
					GPIO_SetBits(GPIOC, GPIO_Pin_6);		// PC6 = 1
					contrastState = 1;						// ����ת
				}
			}
			
			// �Աȶ�����ť - ����
			if ( USART3_RX_BUF[0] == 'n' )
			{
				if ( LIMIT5 != 0 && contrastState == 2 ) {
					u3_printf("CR\r\n");					// �Աȶ�����λ�Ѵ���
				} else {
					GPIO_SetBits(GPIOD, GPIO_Pin_8);		// PD8 = 1
					GPIO_SetBits(GPIOA, GPIO_Pin_7);		// PA7 = 1
					GPIO_ResetBits(GPIOC, GPIO_Pin_6);		// PC6 = 0
					contrastState = 2;						// ����ת
				}
			}
			
			//------------------------------------------------------------------------------
			
			// ˫��Դ����ť - ����
			if ( USART3_RX_BUF[0] == 'o' )
			{
				if ( LIMIT6 != 0 && lightSource == 1 ) {	
					u3_printf("LL\r\n");					// ˫��Դ����λ�Ѵ���
				} else {
					GPIO_SetBits(GPIOG, GPIO_Pin_6);		// PG6 = 1
					GPIO_ResetBits(GPIOB, GPIO_Pin_14);		// PB14 = 0
					GPIO_SetBits(GPIOC, GPIO_Pin_7);		// PC7 = 1
					lightSource = 1;						// ����ת	
				}
			}
			
			// ˫��Դ����ť - ����
			if ( USART3_RX_BUF[0] == 'p' )
			{
				if ( LIMIT7 != 0 && lightSource == 2 ) {
					u3_printf("LR\r\n");					// ˫��Դ����λ�Ѵ���
				} else {
					GPIO_SetBits(GPIOG, GPIO_Pin_6);		// PG6 = 1
					GPIO_SetBits(GPIOB, GPIO_Pin_14);		// PB14 = 1
					GPIO_ResetBits(GPIOC, GPIO_Pin_7);		// PC7 = 0
					lightSource = 2;						// ����ת
				}
			}
			
			//------------------------------------------------------------------------------
			
			// ��׼
			if ( USART3_RX_BUF[0] == 'q' ) {
				// �����źŸ���λ�����򿪶�׼���
				printf("8");
			}
			
			// ����
			if ( USART3_RX_BUF[0] == 'r' ) {
				// �����źŸ���λ������������
				printf("9");
			}
			
			USART3_RX_STA = 0;
		}
		*/
		
		// ����
		if ( USART_RX_STA & 0x8000 )
		{
			// ���ݳ���
			u8 len = USART_RX_STA & 0x3fff;
			
			// ���� M1
			if ( USART_RX_BUF[0] == 'a' ) {
				if ( LIMIT0 != 0 ) {
					printf("FL");							// ��������λ�Ѵ���
				} else {
					GPIO_SetBits(GPIOB, GPIO_Pin_0);		// PB0 = 1
					GPIO_ResetBits(GPIOE, GPIO_Pin_8);		// PE8 = 0
					GPIO_SetBits(GPIOE, GPIO_Pin_9);		// PE9 = 1
					
					if ( LIMIT1 != 0 ) {
						// ����λ����������£���תһ��ȷ���뿪��λ
						delay_ms(500);
					}
				}
			}
			
			if ( USART_RX_BUF[0] == 'b' ) {
				GPIO_ResetBits(GPIOB, GPIO_Pin_0);			// PB0 = 0
			}
			
			if ( USART_RX_BUF[0] == 'c' ) {
				if ( LIMIT1 != 0 ) {
					printf("FR");							// ��������λ�Ѵ���
				} else {
					GPIO_SetBits(GPIOB, GPIO_Pin_0);		// PB0 = 1
					GPIO_SetBits(GPIOE, GPIO_Pin_8);		// PE8 = 1
					GPIO_ResetBits(GPIOE, GPIO_Pin_9);		// PE9 = 0
					
					if ( LIMIT0 != 0 ) {
						// ����λ����������£���תһ��ȷ���뿪��λ
						delay_ms(500);
					}
				}
			}
			
			if ( USART_RX_BUF[0] == 'd' ) {
				GPIO_ResetBits(GPIOB, GPIO_Pin_0);			// PB0 = 0
			}
			
			//------------------------------------------------------------------------------
			
			// �䱶 M2
			if ( USART_RX_BUF[0] == 'e' ) {
				if ( LIMIT2 != 0 ) {
					printf("ZL");							// �䱶����λ�Ѵ���
				} else {
					GPIO_SetBits(GPIOE, GPIO_Pin_7);		// PE7 = 1
					GPIO_ResetBits(GPIOE, GPIO_Pin_10);		// PE10 = 0
					GPIO_SetBits(GPIOE, GPIO_Pin_11);		// PE11 = 1
					
					if ( LIMIT3 != 0 ) {
						// ����λ����������£���תһ��ȷ���뿪��λ
						delay_ms(100);
					}
				}
			}
			
			if ( USART_RX_BUF[0] == 'f' ) {
				GPIO_ResetBits(GPIOE, GPIO_Pin_7);			// PE7 = 0
			}
			
			if ( USART_RX_BUF[0] == 'g' ) {
				if ( LIMIT3 != 0 ) {
					printf("ZR");							// �䱶����λ�Ѵ���
				} else {
					GPIO_SetBits(GPIOE, GPIO_Pin_7);		// PE7 = 1
					GPIO_SetBits(GPIOE, GPIO_Pin_10);		// PE10 = 1
					GPIO_ResetBits(GPIOE, GPIO_Pin_11);		// PE11 = 0
					
					if ( LIMIT2 != 0 ) {
						// ����λ����������£���תһ��ȷ���뿪��λ
						delay_ms(100);
					}
				}
			}
			
			if ( USART_RX_BUF[0] == 'h' ) {
				GPIO_ResetBits(GPIOE, GPIO_Pin_7);			// PE7 = 0
			}
			
			//------------------------------------------------------------------------------
			
			// ������ M3
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
			
			// �Աȶ� M4
			if ( USART_RX_BUF[0] == 'm' )
			{
				if ( LIMIT4 != 0 && (contrastState == 1 || contrastState == 3) ) {	
					printf("CL");							// �Աȶ�����λ�Ѵ���
				} else {
					GPIO_SetBits(GPIOD, GPIO_Pin_8);		// PD8 = 1
					GPIO_ResetBits(GPIOA, GPIO_Pin_7);		// PA7 = 0
					GPIO_SetBits(GPIOC, GPIO_Pin_6);		// PC6 = 1
					contrastState = 1;						// ����ת
				}
			}
			
			if ( USART_RX_BUF[0] == 'n' )
			{
				if ( LIMIT5 != 0 && (contrastState == 2 || contrastState == 4) ) {
					printf("CR");							// �Աȶ�����λ�Ѵ���
				} else {
					GPIO_SetBits(GPIOD, GPIO_Pin_8);		// PD8 = 1
					GPIO_SetBits(GPIOA, GPIO_Pin_7);		// PA7 = 1
					GPIO_ResetBits(GPIOC, GPIO_Pin_6);		// PC6 = 0
					contrastState = 2;						// ����ת
				}
			}
			
			//------------------------------------------------------------------------------
			
			// ˫��Դ M5
			if ( USART_RX_BUF[0] == 'o' )
			{
				if ( LIMIT6 != 0 && (lightSource == 1 || lightSource == 3) ) {	
					printf("LL");							// ˫��Դ����λ�Ѵ���
				} else {
					GPIO_SetBits(GPIOG, GPIO_Pin_6);		// PG6 = 1
					GPIO_ResetBits(GPIOB, GPIO_Pin_14);		// PB14 = 0
					GPIO_SetBits(GPIOC, GPIO_Pin_7);		// PC7 = 1
					lightSource = 1;						// ����ת
				}
			}
			
			if ( USART_RX_BUF[0] == 'p' )
			{
				if ( LIMIT7 != 0 && (lightSource == 2 || lightSource == 4) ) {
					printf("LR");							// ˫��Դ����λ�Ѵ���
				} else {
					GPIO_SetBits(GPIOG, GPIO_Pin_6);		// PG6 = 1
					GPIO_SetBits(GPIOB, GPIO_Pin_14);		// PB14 = 1
					GPIO_ResetBits(GPIOC, GPIO_Pin_7);		// PC7 = 0
					lightSource = 2;						// ����ת	
				}
			}
			
			//------------------------------------------------------------------------------
			
			// ������ - ����
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
			
			// ������ - �䰵
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
			
			// DA������
			if ( USART_RX_BUF[0] == 'z' )
			{
				// �ַ�����ȡ
				//char *ret;
				//strncpy(ret, USART_RX_BUF + 2, len - 2);
				
				// �ַ����ָ��ȡ����
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
				
				// �ܵ�ѹ = �궨��ѹ * ������Χ
				float scanVoltage = 0;
				if ( wavelengthCount == 0 ) {
					scanVoltage = voltage_calibration;
				} else {
					scanVoltage = voltage_calibration * wavelengthCount;
				}
				
				// ��ѹ��� = �ܵ�ѹ / �ɼ�����
				double average = scanVoltage / (imageCount - 1);
				
				// ��ǰ��ѹ��������ѹ���
				float current_voltage = 0;
				float average_voltage = voltage_start + average;
				int num = 0;
				
				// ��ʼ��ѹΪ0
				if ( channel == 0 ) {
					DAC_SetChannel1Data(DAC_Align_12b_R, 0);
				} else {
					DAC_SetChannel2Data(DAC_Align_12b_R, 0);
				}
				
				while ( current_voltage < voltage_start + scanVoltage + average )
				{
					// ��һ�ε�ѹ������ʼ��ѹʱ���ɼ���һ��ͼƬ
					if ( num == 0 && current_voltage >= voltage_start ) {
						delay_ms(duration_dormancy);
						printf("tp");
						delay_ms(exposure + delay);
						num++;
					}

					// ��ǰ��ѹ����������ѹ���ʱ���ɼ�ͼƬ�����¼�����ѹ���
					if ( current_voltage >= average_voltage ) {
						current_voltage = average_voltage;
						delay_ms(duration_dormancy);
						printf("tp");
						delay_ms(exposure + delay);
						num++;
						average_voltage = voltage_start + average * num;
					}

					// �˳�ѭ��
					if ( num == imageCount ) {
						// ͼ��ɼ����
						if ( wavelengthCount == 0 ) {
							// �궨
							printf("cc-%d-%d-%d-%d", x, y, w, h);
						} else {
							// ����
							printf("cp");
						}
						
						delay_ms(exposure + delay);
						
						// ��ѹ�ص� 0V
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

					// ������ѹ
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

		// �������
		key = Remote_Scan();	
		if (key)
		{	 	  
			//printf("%d", key);
			switch (key)
			{
				// С����0	����+
				case 104: {
					if ( warningState != 1 ) {
						if ( LIMIT1 != 0 ) {
							warningState = 1;	// ������λ����
							printf("FR");		// ��������λ�Ѵ���
						} 
					}
					
					if ( keyState != 1 ) {
						// �������ȫ��ֹͣ
						keyState = 1;
						GPIO_ResetBits(GPIOE, GPIO_Pin_7);	// �䱶ֹͣ  PE7 = 0
						GPIO_ResetBits(GPIOE, GPIO_Pin_14);	// ����ֹͣ	PE14 = 0
						
						if ( LIMIT1 == 0 ) {
							GPIO_SetBits(GPIOB, GPIO_Pin_0);	// PB0 = 1
							GPIO_SetBits(GPIOE, GPIO_Pin_8);	// PE8 = 1
							GPIO_ResetBits(GPIOE, GPIO_Pin_9);	// PE9 = 0
					
							// ����λ����������£���תһ��ȷ���뿪��λ
							if ( LIMIT0 != 0 ) {
								delay_ms(500);
							}
						}
					}
				} break;	
				
				// С����1	����-
				case 48: {
					if ( warningState != 2 ) {
						if ( LIMIT0 != 0 ) {
							warningState = 2;	// ������λ����
							printf("FL");		// ��������λ�Ѵ���
						} 
					}
					
					if ( keyState != 2 ) {
						// �������ȫ��ֹͣ
						keyState = 2;
						GPIO_ResetBits(GPIOE, GPIO_Pin_7);	// �䱶ֹͣ  PE7 = 0
						GPIO_ResetBits(GPIOE, GPIO_Pin_14);	// ����ֹͣ	PE14 = 0
						
						if ( LIMIT0 == 0 ) {
							GPIO_SetBits(GPIOB, GPIO_Pin_0);	// PB0 = 1
							GPIO_ResetBits(GPIOE, GPIO_Pin_8);	// PE8 = 0
							GPIO_SetBits(GPIOE, GPIO_Pin_9);	// PE9 = 1
					
							// ����λ����������£���תһ��ȷ���뿪��λ
							if ( LIMIT1 != 0 ) {
								delay_ms(500);
							}
						}
					}
				} break;
				
				// С����2	�䱶+
				case 24: {
					if ( warningState != 3 ) {
						if ( LIMIT3 != 0 ) {
							warningState = 3;	// ������λ����
							printf("ZR");		// �䱶����λ�Ѵ���
						} 
					}
					
					if ( keyState != 3 ) {
						// �������ȫ��ֹͣ
						keyState = 3;
						GPIO_ResetBits(GPIOB, GPIO_Pin_0);	// ����ֹͣ	PB0 = 0
						GPIO_ResetBits(GPIOE, GPIO_Pin_14);	// ����ֹͣ	PE14 = 0
						
						if ( LIMIT3 == 0 ) {
							GPIO_SetBits(GPIOE, GPIO_Pin_7);	// PE7 = 1
							GPIO_SetBits(GPIOE, GPIO_Pin_10);	// PE10 = 1
							GPIO_ResetBits(GPIOE, GPIO_Pin_11);	// PE11 = 0
					
							if ( LIMIT2 != 0 ) {
								// ����λ����������£���תһ��ȷ���뿪��λ
								delay_ms(100);
							} else {
								// �㶯ģʽ���˶�һ�º�ֹͣ
								delay_ms(50);
							}
							
							// �䱶���ֹͣ
							GPIO_ResetBits(GPIOE, GPIO_Pin_7);	// PE7 = 0
						}
					}
				} break;
				
				// С����3	�䱶-
				case 122: {
					if ( warningState != 4 ) {
						if ( LIMIT2 != 0 ) {
							warningState = 4;	// ������λ����
							printf("ZL");		// �䱶����λ�Ѵ���
						} 
					}
					
					if ( keyState != 4 ) {
						// �������ȫ��ֹͣ
						keyState = 4;
						GPIO_ResetBits(GPIOB, GPIO_Pin_0);	// ����ֹͣ	PB0 = 0
						GPIO_ResetBits(GPIOE, GPIO_Pin_14);	// ����ֹͣ	PE14 = 0
						
						if ( LIMIT2 == 0 ) {
							GPIO_SetBits(GPIOE, GPIO_Pin_7);	// PE7 = 1
							GPIO_ResetBits(GPIOE, GPIO_Pin_10);	// PE10 = 0
							GPIO_SetBits(GPIOE, GPIO_Pin_11);	// PE11 = 1
					
							if ( LIMIT3 != 0 ) {
								// ����λ����������£���תһ��ȷ���뿪��λ
								delay_ms(100);
							} else {
								// �㶯ģʽ���˶�һ�º�ֹͣ
								delay_ms(50);
							}
							
							// �䱶���ֹͣ
							GPIO_ResetBits(GPIOE, GPIO_Pin_7);	// PE7 = 0
						}
					}
				} break;
				
				// С����4	����-
				case 16: {
					if ( keyState != 5 ) {
						// �������ȫ��ֹͣ
						keyState = 5;
						GPIO_ResetBits(GPIOB, GPIO_Pin_0);	// ����ֹͣ	PB0 = 0
						GPIO_ResetBits(GPIOE, GPIO_Pin_7);	// �䱶ֹͣ  PE7 = 0
					
						GPIO_SetBits(GPIOE, GPIO_Pin_14);	// PE14 = 1
						GPIO_ResetBits(GPIOE, GPIO_Pin_13);	// PE13 = 0
						GPIO_SetBits(GPIOE, GPIO_Pin_12);	// PE12 = 1
						
						// �㶯ģʽ���˶�һ�º�ֹͣ
						delay_ms(50);
						GPIO_ResetBits(GPIOE, GPIO_Pin_14);	// PE14 = 0
					}
				} break;
				
				// С����5	����+
				case 56: {
					if ( keyState != 6 ) {
						// �������ȫ��ֹͣ
						keyState = 6;
						GPIO_ResetBits(GPIOB, GPIO_Pin_0);	// ����ֹͣ	PB0 = 0
						GPIO_ResetBits(GPIOE, GPIO_Pin_7);	// �䱶ֹͣ  PE7 = 0
					
						GPIO_SetBits(GPIOE, GPIO_Pin_14);	// PE14 = 1
						GPIO_SetBits(GPIOE, GPIO_Pin_13);	// PE13 = 1
						GPIO_ResetBits(GPIOE, GPIO_Pin_12);	// PE12 = 0
						
						// �㶯ģʽ���˶�һ�º�ֹͣ
						delay_ms(50);
						GPIO_ResetBits(GPIOE, GPIO_Pin_14);	// PE14 = 0
					}
				} break;
				
				// С����6	�Աȶ��л�
				case 90: {
					if ( contrastState == 0 || contrastState == 3 || contrastState == 4 ) {
						// �������ȫ��ֹͣ
						GPIO_ResetBits(GPIOB, GPIO_Pin_0);	// ����ֹͣ	PB0 = 0
						GPIO_ResetBits(GPIOE, GPIO_Pin_7);	// �䱶ֹͣ  PE7 = 0
						GPIO_ResetBits(GPIOE, GPIO_Pin_14);	// ����ֹͣ	PE14 = 0
						
						if ( contrastState == 3 ) {
							GPIO_SetBits(GPIOD, GPIO_Pin_8);		// PD8 = 1
							GPIO_SetBits(GPIOA, GPIO_Pin_7);		// PA7 = 1
							GPIO_ResetBits(GPIOC, GPIO_Pin_6);		// PC6 = 0
							contrastState = 2;						// ����ת
						} else {
							GPIO_SetBits(GPIOD, GPIO_Pin_8);		// PD8 = 1
							GPIO_ResetBits(GPIOA, GPIO_Pin_7);		// PA7 = 0
							GPIO_SetBits(GPIOC, GPIO_Pin_6);		// PC6 = 1
							contrastState = 1;						// ����ת
						}
					}
				} break;
				
				// С����7	˫��Դ�л�
				case 66: {
					if ( lightSource == 0 || lightSource == 3 || lightSource == 4 ) {
						// �������ȫ��ֹͣ
						GPIO_ResetBits(GPIOB, GPIO_Pin_0);	// ����ֹͣ	PB0 = 0
						GPIO_ResetBits(GPIOE, GPIO_Pin_7);	// �䱶ֹͣ  PE7 = 0
						GPIO_ResetBits(GPIOE, GPIO_Pin_14);	// ����ֹͣ	PE14 = 0
						
						if ( lightSource == 3 ) {	
							GPIO_SetBits(GPIOG, GPIO_Pin_6);		// PG6 = 1
							GPIO_SetBits(GPIOB, GPIO_Pin_14);		// PB14 = 1
							GPIO_ResetBits(GPIOC, GPIO_Pin_7);		// PC7 = 0
							lightSource = 2;						// ����ת
						} else {
							GPIO_SetBits(GPIOG, GPIO_Pin_6);		// PG6 = 1
							GPIO_ResetBits(GPIOB, GPIO_Pin_14);		// PB14 = 0
							GPIO_SetBits(GPIOC, GPIO_Pin_7);		// PC7 = 1
							lightSource = 1;						// ����ת
						}
					}
				} break;
				
				// С����8	����
				case 74: {
					if ( keyState == 0 ) {
						keyState = 7;
						printf("9");
					}
				} break;
				
				// С����9	��׼
				case 82: {
					if ( keyState == 0 ) {
						keyState = 8;
						printf("8");
					}
				} break;
			}
		} else {
			if ( keyState != 0 ) {
				// û�а������£�״̬��ԭ
				keyState = 0;
				warningState = 0;
				GPIO_ResetBits(GPIOB, GPIO_Pin_0);	// ����ֹͣ	PB0 = 0
			}
		}
	}
}
