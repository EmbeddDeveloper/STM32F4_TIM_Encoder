/**
  ******************************************************************************
  * @文件名     ： bsp_timer.c
  * @作者       ： strongerHuang
  * @版本       ： V1.0.0
  * @日期       ： 2017年12月19日
  * @摘要       ： TIM底层源文件
  ******************************************************************************/
/*----------------------------------------------------------------------------
  更新日志:
  2017-12-19 V1.0.0:初始版本
  ----------------------------------------------------------------------------*/
/* 包含的头文件 --------------------------------------------------------------*/
#include "bsp_timer.h"


/************************************************
函数名称 ： TIMER_Initializes
功    能 ： TIMER初始化
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void TIMER_Initializes(void)
{
  TIM_DELAY_Configuration();
  TIM_ENCODER_Configuration();
}

/************************************************
函数名称 ： TIM_DELAY_Configuration
功    能 ： 延时TIM配置
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void TIM_DELAY_Configuration(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

  /* 时钟配置 */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  /* 时基配置 */
  TIM_TimeBaseStructure.TIM_Prescaler = TIM2_PRESCALER_VALUE;        //预分频值
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;        //向上计数模式
  TIM_TimeBaseStructure.TIM_Period = TIM2_PERIOD_TIMING;             //定时周期
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;            //时钟分频因子
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* 使能预分频值 */
  TIM_ARRPreloadConfig(TIM2, ENABLE);                                //使能重载值
}

/************************************************
函数名称 ： TIMDelay_N10us
功    能 ： 定时器延时N个10us
参    数 ： Times --- N值
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void TIMDelay_N10us(uint16_t Times)
{
  TIM_Cmd(TIM2, ENABLE);                                             //启动定时器
  while(Times--)
  {
    while(RESET == TIM_GetFlagStatus(TIM2, TIM_FLAG_Update));
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);                            //清除标志
  }
  TIM_Cmd(TIM2, DISABLE);                                            //关闭定时器
}

/************************************************
函数名称 ： TIMDelay_Nms
功    能 ： 定时器延时Nms
参    数 ： Times --- N值
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void TIMDelay_Nms(uint16_t Times)
{
  while(Times--)
  {
    TIMDelay_N10us(100);
  }
}

/************************************************
函数名称 ： TIM_ENCODER_Configuration
功    能 ： 编码器TIM配置
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void TIM_ENCODER_Configuration(void)
{
  GPIO_InitTypeDef        GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

  /* 时钟配置 */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,  ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,   ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  /* 引脚配置 */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_7;           //引脚(A、B项)
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;                      //复用模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* 复用配置 */
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM3);            //复用配置
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM3);            //复用配置

  /* 时基配置 */
  TIM_TimeBaseStructure.TIM_Prescaler = 0;                           //预分频值
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;        //向上计数模式
  TIM_TimeBaseStructure.TIM_Period = 10000;                          //定时周期
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;            //时钟分频因子
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* 编码器配置 */
  TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

  /* 初始化 */
  TIM_SetCounter(TIM3, 0);
  TIM_Cmd(TIM3, ENABLE);
}

/************************************************
函数名称 ： ENCODER_Read
功    能 ： 读取编码器数据
参    数 ： Dir --- 方向
            Cnt --- 计数
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void ENCODER_Read(uint32_t *Dir, uint32_t *Cnt)
{
  *Dir = (TIM3->CR1) & TIM_CR1_DIR;
  *Cnt = TIM_GetCounter(TIM3);
}


/**** Copyright (C)2017 strongerHuang. All Rights Reserved **** END OF FILE ****/
