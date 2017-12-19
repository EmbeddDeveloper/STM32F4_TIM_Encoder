/**
  ******************************************************************************
  * @�ļ���     �� bsp_timer.c
  * @����       �� strongerHuang
  * @�汾       �� V1.0.0
  * @����       �� 2017��12��19��
  * @ժҪ       �� TIM�ײ�Դ�ļ�
  ******************************************************************************/
/*----------------------------------------------------------------------------
  ������־:
  2017-12-19 V1.0.0:��ʼ�汾
  ----------------------------------------------------------------------------*/
/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "bsp_timer.h"


/************************************************
�������� �� TIMER_Initializes
��    �� �� TIMER��ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void TIMER_Initializes(void)
{
  TIM_DELAY_Configuration();
  TIM_ENCODER_Configuration();
}

/************************************************
�������� �� TIM_DELAY_Configuration
��    �� �� ��ʱTIM����
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void TIM_DELAY_Configuration(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

  /* ʱ������ */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  /* ʱ������ */
  TIM_TimeBaseStructure.TIM_Prescaler = TIM2_PRESCALER_VALUE;        //Ԥ��Ƶֵ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;        //���ϼ���ģʽ
  TIM_TimeBaseStructure.TIM_Period = TIM2_PERIOD_TIMING;             //��ʱ����
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;            //ʱ�ӷ�Ƶ����
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* ʹ��Ԥ��Ƶֵ */
  TIM_ARRPreloadConfig(TIM2, ENABLE);                                //ʹ������ֵ
}

/************************************************
�������� �� TIMDelay_N10us
��    �� �� ��ʱ����ʱN��10us
��    �� �� Times --- Nֵ
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void TIMDelay_N10us(uint16_t Times)
{
  TIM_Cmd(TIM2, ENABLE);                                             //������ʱ��
  while(Times--)
  {
    while(RESET == TIM_GetFlagStatus(TIM2, TIM_FLAG_Update));
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);                            //�����־
  }
  TIM_Cmd(TIM2, DISABLE);                                            //�رն�ʱ��
}

/************************************************
�������� �� TIMDelay_Nms
��    �� �� ��ʱ����ʱNms
��    �� �� Times --- Nֵ
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void TIMDelay_Nms(uint16_t Times)
{
  while(Times--)
  {
    TIMDelay_N10us(100);
  }
}

/************************************************
�������� �� TIM_ENCODER_Configuration
��    �� �� ������TIM����
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void TIM_ENCODER_Configuration(void)
{
  GPIO_InitTypeDef        GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

  /* ʱ������ */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,  ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,   ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  /* �������� */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_7;           //����(A��B��)
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;                      //����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* �������� */
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM3);            //��������
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM3);            //��������

  /* ʱ������ */
  TIM_TimeBaseStructure.TIM_Prescaler = 0;                           //Ԥ��Ƶֵ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;        //���ϼ���ģʽ
  TIM_TimeBaseStructure.TIM_Period = 10000;                          //��ʱ����
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;            //ʱ�ӷ�Ƶ����
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* ���������� */
  TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

  /* ��ʼ�� */
  TIM_SetCounter(TIM3, 0);
  TIM_Cmd(TIM3, ENABLE);
}

/************************************************
�������� �� ENCODER_Read
��    �� �� ��ȡ����������
��    �� �� Dir --- ����
            Cnt --- ����
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void ENCODER_Read(uint32_t *Dir, uint32_t *Cnt)
{
  *Dir = (TIM3->CR1) & TIM_CR1_DIR;
  *Cnt = TIM_GetCounter(TIM3);
}


/**** Copyright (C)2017 strongerHuang. All Rights Reserved **** END OF FILE ****/
