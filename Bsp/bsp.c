/**
  ******************************************************************************
  * @�ļ���     �� bsp.c
  * @����       �� strongerHuang
  * @�汾       �� V1.0.0
  * @����       �� 2017��12��19��
  * @ժҪ       �� BSP�ײ�Դ�ļ�
  ******************************************************************************/
/*----------------------------------------------------------------------------
  ������־:
  2017-12-19 V1.0.0:��ʼ�汾
  ----------------------------------------------------------------------------*/
/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "bsp.h"


/************************************************
�������� �� RCC_Configuration
��    �� �� ʱ������
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void RCC_Configuration(void)
{
  /* ʹ��AHB1ʱ�� */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | 
                         RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD | 
                         RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF | 
                         RCC_AHB1Periph_GPIOG | RCC_AHB1Periph_GPIOH, ENABLE);

  /* ʹ��AHB2ʱ�� */
  RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);

  /* ʹ��APB1ʱ�� */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  /* ʹ��APB2ʱ�� */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
}

/************************************************
�������� �� LED_Initializes
��    �� �� LED��ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void LED_Initializes(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* ʹ��ʱ�� */
  RCC_AHB1PeriphClockCmd(LED_GPIO_CLK, ENABLE);

  /* �������� */
  GPIO_InitStructure.GPIO_Pin = LED_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);

  LED_OFF();

#if 0
  /* MCOʱ����� */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  RCC_MCO1Config(RCC_MCO1Source_PLLCLK, RCC_MCO1Div_2);
#endif
}

/************************************************
�������� �� BSP_Initializes
��    �� �� �ײ��ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void BSP_Initializes(void)
{
  LED_Initializes();                             //LED��ʼ��
}


/**** Copyright (C)2017 strongerHuang. All Rights Reserved **** END OF FILE ****/
