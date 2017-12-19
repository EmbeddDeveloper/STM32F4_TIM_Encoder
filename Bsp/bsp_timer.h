/**
  ******************************************************************************
  * @�ļ���     �� bsp_timer.h
  * @����       �� strongerHuang
  * @�汾       �� V1.0.0
  * @����       �� 2017��12��19��
  * @ժҪ       �� TIM�ײ�ͷ�ļ�
  ******************************************************************************/

/* �����ֹ�ݹ���� ----------------------------------------------------------*/
#ifndef _BSP_TIMER_H
#define _BSP_TIMER_H


/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "stm32f4xx.h"


/* �궨�� --------------------------------------------------------------------*/
#define TIM2_COUNTER_CLOCK        1000000                  //����ʱ��(1M��/��)
                                                           //Ԥ��Ƶֵ
#define TIM2_PRESCALER_VALUE      (SystemCoreClock/TIM2_COUNTER_CLOCK - 1)
#define TIM2_PERIOD_TIMING        (10 - 1)                 //��ʱ���ڣ�����ڼ���ʱ��:1���� = 1����ʱ�ӣ�


/* �������� ------------------------------------------------------------------*/
void TIMER_Initializes(void);

void TIM_DELAY_Configuration(void);
void TIMDelay_N10us(uint16_t Times);
void TIMDelay_Nms(uint16_t Times);

void TIM_ENCODER_Configuration(void);
void ENCODER_Read(uint32_t *Dir, uint32_t *Cnt);


#endif /* _BSP_TIMER_H */

/**** Copyright (C)2017 strongerHuang. All Rights Reserved **** END OF FILE ****/
