/**
  ******************************************************************************
  * @�ļ���     �� bsp_usart.c
  * @����       �� strongerHuang
  * @�汾       �� V1.0.0
  * @����       �� 2017��12��19��
  * @ժҪ       �� USART�ײ�Դ�ļ�
  ******************************************************************************/
/*----------------------------------------------------------------------------
  ������־:
  2017-12-19 V1.0.0:��ʼ�汾
  ----------------------------------------------------------------------------*/
/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "bsp_usart.h"


/************************************************
�������� �� USART_GPIO_Configuration
��    �� �� USART��������
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void USART_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* ʱ������ */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

  /* �������� */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                       //����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/************************************************
�������� �� USART_Configuration
��    �� �� ����USART
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void USART_Configuration(void)
{
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /* ʱ������ */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

  /* �����ж� */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;          //�����ȼ�
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* USART���� */
  USART_InitStructure.USART_BaudRate = 115200;                       //������
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;        //����λ��
  USART_InitStructure.USART_StopBits = USART_StopBits_1;             //ֹͣλ
  USART_InitStructure.USART_Parity = USART_Parity_No ;               //У��λ
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;    //�շ�����
  USART_Init(USART1, &USART_InitStructure);

  USART_ClearFlag(USART1, USART_FLAG_RXNE);
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                     //ʹ�ܽ����ж�

  USART_Cmd(USART1, ENABLE);                                         //ʹ��USART
}

/************************************************
�������� �� USART_Initializes
��    �� �� ���ڳ�ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void USART_Initializes(void)
{
  USART_GPIO_Configuration();
  USART_Configuration();
}

/************************************************
�������� �� USART1_SendChar
��    �� �� ����1����һ���ַ�
��    �� �� Data --- ����
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void USART1_SendByte(uint8_t Data)
{
  while(RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE));
  USART_SendData(USART1, Data);
  while(RESET == USART_GetFlagStatus(USART1, USART_FLAG_TC));
}

/************************************************
�������� �� USART1_SendNByte
��    �� �� ����1����N���ַ�
��    �� �� pData ----- �ַ���
            Length --- ����
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void USART1_SendNByte(uint8_t *pData, uint16_t Length)
{
  while(Length--)
  {
    USART1_SendByte(*pData);
    pData++;
  }
}

/******************************************* �����ض��� *******************************************/
/************************************************
�������� �� fputc
��    �� �� �ض���putc����
��    �� �� ch --- �ַ�
            *f --- �ļ�ָ��
�� �� ֵ �� �ַ�
��    �� �� strongerHuang
*************************************************/
int fputc(int ch, FILE *f)
{
  USART1_SendByte((uint8_t)ch);

  return ch;
}

/************************************************
�������� �� fgetc
��    �� �� �ض���getc����
��    �� �� *f --- �ļ�ָ��
�� �� ֵ �� �ַ�
��    �� �� strongerHuang
*************************************************/
int fgetc(FILE *f)
{
  while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

  return (int)USART_ReceiveData(USART1);
}


/**** Copyright (C)2017 strongerHuang. All Rights Reserved **** END OF FILE ****/
