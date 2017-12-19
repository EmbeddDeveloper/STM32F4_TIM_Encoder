/**
  ******************************************************************************
  * @文件名     ： main.c
  * @作者       ： strongerHuang
  * @版本       ： V1.0.0
  * @日期       ： 2017年12月19日
  * @摘要       ： 主函数 - Demo软件工程
  ******************************************************************************/
/*----------------------------------------------------------------------------
  更新日志:
  2017-12-19 V1.0.0:初始版本
  ----------------------------------------------------------------------------*/
/* 包含的头文件 --------------------------------------------------------------*/
#include "bsp.h"
#include "bsp_timer.h"
#include "bsp_usart.h"


/************************************************
函数名称 ： System_Initializes
功    能 ： 系统初始化
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void System_Initializes(void)
{
  BSP_Initializes();
  TIMER_Initializes();
  USART_Initializes();
}

/************************************************
函数名称 ： main
功    能 ： 主函数入口
参    数 ： 无
返 回 值 ： int
作    者 ： strongerHuang
*************************************************/
int main(void)
{
  static uint32_t dir;
  static uint32_t cnt;

  System_Initializes();

  while(1)
  {
    ENCODER_Read(&dir, &cnt);                    //读取编码数值, 并打印
    printf("Dir = %X; Cnt = %d;\n", dir, cnt);

    LED_TOGGLE();                                //LED变化
    TIMDelay_Nms(120);                           //TIM延时

  }
}


/**** Copyright (C)2017 strongerHuang. All Rights Reserved **** END OF FILE ****/
