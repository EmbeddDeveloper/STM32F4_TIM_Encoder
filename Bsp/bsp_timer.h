/**
  ******************************************************************************
  * @文件名     ： bsp_timer.h
  * @作者       ： strongerHuang
  * @版本       ： V1.0.0
  * @日期       ： 2017年12月19日
  * @摘要       ： TIM底层头文件
  ******************************************************************************/

/* 定义防止递归包含 ----------------------------------------------------------*/
#ifndef _BSP_TIMER_H
#define _BSP_TIMER_H


/* 包含的头文件 --------------------------------------------------------------*/
#include "stm32f4xx.h"


/* 宏定义 --------------------------------------------------------------------*/
#define TIM2_COUNTER_CLOCK        1000000                  //计数时钟(1M次/秒)
                                                           //预分频值
#define TIM2_PRESCALER_VALUE      (SystemCoreClock/TIM2_COUNTER_CLOCK - 1)
#define TIM2_PERIOD_TIMING        (10 - 1)                 //定时周期（相对于计数时钟:1周期 = 1计数时钟）


/* 函数申明 ------------------------------------------------------------------*/
void TIMER_Initializes(void);

void TIM_DELAY_Configuration(void);
void TIMDelay_N10us(uint16_t Times);
void TIMDelay_Nms(uint16_t Times);

void TIM_ENCODER_Configuration(void);
void ENCODER_Read(uint32_t *Dir, uint32_t *Cnt);


#endif /* _BSP_TIMER_H */

/**** Copyright (C)2017 strongerHuang. All Rights Reserved **** END OF FILE ****/
