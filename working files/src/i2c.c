#include "header.h"

int etap_settings_test_frequency = -1;

/**************************************/
//������������ I2C
/**************************************/
void Configure_I2C(I2C_TypeDef* I2Cx)
{
  I2C_InitTypeDef  I2C_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  uint16_t current_count_tim4, new_count_tim4;
  unsigned int delta;

  /* ����������� I2C  */
  I2C_Cmd(I2Cx, DISABLE);

  /***
  ����������, ��� �� SDA ������������ 1
  ***/
  /* ���������� I2C ��� SCL Output Open-drain */
  GPIO_InitStructure.GPIO_Pin = GPIO_I2C_SCL;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIO_I2C, &GPIO_InitStructure);
  /* ������������ ��� SCL � ������� �����*/
  GPIO_SetBits(GPIO_I2C, GPIO_I2C_SCL);
  while(GPIO_ReadOutputDataBit(GPIO_I2C, GPIO_I2C_SCL) == Bit_RESET);

  /*���������� I2C ��� SDA  �� ���*/
  GPIO_InitStructure.GPIO_Pin = GPIO_I2C_SDA;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIO_I2C, &GPIO_InitStructure);
  
  while(GPIO_ReadInputDataBit(GPIO_I2C, GPIO_I2C_SDA) == RESET)
  {
    /* SCL -> "0" */
    GPIO_ResetBits(GPIO_I2C, GPIO_I2C_SCL);
    current_count_tim4 = ((uint16_t)TIM4->CNT);
    delta = 0;
    while (delta < 4) // <= 4x10 = 40(���)
    {
      new_count_tim4 = ((uint16_t)TIM4->CNT);
      if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
      else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
    }

    /* SCL -> "1" */
    GPIO_SetBits(GPIO_I2C, GPIO_I2C_SCL);
    while(GPIO_ReadOutputDataBit(GPIO_I2C, GPIO_I2C_SCL) == Bit_RESET);
    current_count_tim4 = ((uint16_t)TIM4->CNT);
    delta = 0;
    while (delta < 4) // <= 4x10 = 40(���)
    {
      new_count_tim4 = ((uint16_t)TIM4->CNT);
      if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
      else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
    }
  }
  /*******/
  
  /***
  ���������� ��� �� �������� ��������������
  ***/
  /* ���������� I2C �� SDA �� Output Open-drain */
  GPIO_InitStructure.GPIO_Pin = GPIO_I2C_SDA;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIO_I2C, &GPIO_InitStructure);
  /* ������������ ��� SCL � SDA � ������� �����*/
  GPIO_SetBits(GPIO_I2C, (GPIO_I2C_SCL | GPIO_I2C_SDA));
  while(GPIO_ReadOutputDataBit(GPIO_I2C, GPIO_I2C_SCL) == Bit_RESET);
  /*******/
  
  /***
  ��������� SOFTWARE RESET ��� EEPROM: Start + 9-bit + Start + Stop 
  ****/

  /*- Start -*/
  /*SCL = 1 � SCA = 1*/

  /* SCL -> "0" */
  GPIO_ResetBits(GPIO_I2C, GPIO_I2C_SCL);
  current_count_tim4 = ((uint16_t)TIM4->CNT);
  delta = 0;
  while (delta < 2) // <= 2x10 = 20(���)
  {
    new_count_tim4 = ((uint16_t)TIM4->CNT);
    if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
    else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
  }
    
  /* SCL -> "1" */
  GPIO_SetBits(GPIO_I2C, GPIO_I2C_SCL);
  while(GPIO_ReadOutputDataBit(GPIO_I2C, GPIO_I2C_SCL) == Bit_RESET);
  current_count_tim4 = ((uint16_t)TIM4->CNT);
  delta = 0;
  while (delta < 2) // <= 2x10 = 20(���)
  {
    new_count_tim4 = ((uint16_t)TIM4->CNT);
    if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
    else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
  }
  
  /* SDA -> "0" */
  GPIO_ResetBits(GPIO_I2C, GPIO_I2C_SDA);
  current_count_tim4 = ((uint16_t)TIM4->CNT);
  delta = 0;
  while (delta < 2) // <= 2x10 = 20(���)
  {
    new_count_tim4 = ((uint16_t)TIM4->CNT);
    if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
    else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
  }

  /* SCL -> "0" */
  GPIO_ResetBits(GPIO_I2C, GPIO_I2C_SCL);
  current_count_tim4 = ((uint16_t)TIM4->CNT);
  delta = 0;
  while (delta < 2) // <= 2x10 = 20(���)
  {
    new_count_tim4 = ((uint16_t)TIM4->CNT);
    if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
    else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
  }
  
  /* SDA -> "1" */
  GPIO_SetBits(GPIO_I2C, GPIO_I2C_SDA);

  /*- 9 ����� -*/
  for(unsigned int i = 0; i < 9; i++)
  {
    /* SCL = "0" */
    current_count_tim4 = ((uint16_t)TIM4->CNT);
    delta = 0;
    while (delta < 2) // <= 2x10 = 20(���)
    {
      new_count_tim4 = ((uint16_t)TIM4->CNT);
      if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
      else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
    }

    /* SCL -> "1" */
    GPIO_SetBits(GPIO_I2C, GPIO_I2C_SCL);
    while(GPIO_ReadOutputDataBit(GPIO_I2C, GPIO_I2C_SCL) == Bit_RESET);
    current_count_tim4 = ((uint16_t)TIM4->CNT);
    delta = 0;
    while (delta < 4) // <= 4x10 = 40(���)
    {
      new_count_tim4 = ((uint16_t)TIM4->CNT);
      if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
      else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
    }

    /* SCL -> "0" */
    GPIO_ResetBits(GPIO_I2C, GPIO_I2C_SCL);
    current_count_tim4 = ((uint16_t)TIM4->CNT);
    delta = 0;
    while (delta < 2) // <= 2x10 = 20(���)
    {
      new_count_tim4 = ((uint16_t)TIM4->CNT);
      if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
      else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
    }
  }

  /*- Start -*/
  /*SCL = 0 � SCA = 1*/

  current_count_tim4 = ((uint16_t)TIM4->CNT);
  delta = 0;
  while (delta < 2) // <= 2x10 = 20(���)
  {
    new_count_tim4 = ((uint16_t)TIM4->CNT);
    if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
    else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
  }
    
  /* SCL -> "1" */
  GPIO_SetBits(GPIO_I2C, GPIO_I2C_SCL);
  while(GPIO_ReadOutputDataBit(GPIO_I2C, GPIO_I2C_SCL) == Bit_RESET);
  current_count_tim4 = ((uint16_t)TIM4->CNT);
  delta = 0;
  while (delta < 2) // <= 2x10 = 20(���)
  {
    new_count_tim4 = ((uint16_t)TIM4->CNT);
    if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
    else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
  }
  
  /* SDA -> "0" */
  GPIO_ResetBits(GPIO_I2C, GPIO_I2C_SDA);
  current_count_tim4 = ((uint16_t)TIM4->CNT);
  delta = 0;
  while (delta < 2) // <= 2x10 = 20(���)
  {
    new_count_tim4 = ((uint16_t)TIM4->CNT);
    if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
    else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
  }

  /* SCL -> "0" */
  GPIO_ResetBits(GPIO_I2C, GPIO_I2C_SCL);
  current_count_tim4 = ((uint16_t)TIM4->CNT);
  delta = 0;
  while (delta < 2) // <= 2x10 = 20(���)
  {
    new_count_tim4 = ((uint16_t)TIM4->CNT);
    if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
    else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
  }

  /*- Stop -*/
  /*SCL = 0 � SCA = 0*/

  current_count_tim4 = ((uint16_t)TIM4->CNT);
  delta = 0;
  while (delta < 2) // <= 2x10 = 20(���)
  {
    new_count_tim4 = ((uint16_t)TIM4->CNT);
    if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
    else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
  }
    
  /* SCL -> "1" */
  GPIO_SetBits(GPIO_I2C, GPIO_I2C_SCL);
  while(GPIO_ReadOutputDataBit(GPIO_I2C, GPIO_I2C_SCL) == Bit_RESET);
  current_count_tim4 = ((uint16_t)TIM4->CNT);
  delta = 0;
  while (delta < 2) // <= 2x10 = 20(���)
  {
    new_count_tim4 = ((uint16_t)TIM4->CNT);
    if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
    else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
  }
  
  /* SDA -> "1" */
  GPIO_SetBits(GPIO_I2C, GPIO_I2C_SDA);
  current_count_tim4 = ((uint16_t)TIM4->CNT);
  delta = 0;
  while (delta < 2) // <= 2x10 = 20(���)
  {
    new_count_tim4 = ((uint16_t)TIM4->CNT);
    if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
    else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
  }

  /* SCL -> "0" */
  GPIO_ResetBits(GPIO_I2C, GPIO_I2C_SCL);
  current_count_tim4 = ((uint16_t)TIM4->CNT);
  delta = 0;
  while (delta < 2) // <= 2x10 = 20(���)
  {
    new_count_tim4 = ((uint16_t)TIM4->CNT);
    if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
    else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
  }

  /* ������������ ��� SCL � SDA � ������� �����*/
  GPIO_SetBits(GPIO_I2C, (GPIO_I2C_SCL | GPIO_I2C_SDA));
  while(GPIO_ReadOutputDataBit(GPIO_I2C, GPIO_I2C_SCL) == Bit_RESET);
  /*******/
  
  /*
  ��������� ��� �� ��������� I2C
  */
  //����������� ��� PB8/I2C1_SCL � PB9/I2C1_SDA
  GPIO_PinAFConfig(GPIO_I2C, GPIO_I2C_SCLSource, GPIO_AF_I2C);
  GPIO_PinAFConfig(GPIO_I2C, GPIO_I2C_SDASource, GPIO_AF_I2C);

  /* ���������� I2C ���: SCL � SDA */
  GPIO_InitStructure.GPIO_Pin =  GPIO_I2C_SCL | GPIO_I2C_SDA;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIO_I2C, &GPIO_InitStructure);
  /*******/

  /* ������� �� I2C ������� */
  I2C_SoftwareResetCmd(I2Cx, ENABLE);
  I2C_SoftwareResetCmd(I2Cx, DISABLE);

  /* ���������� I2C*/
  I2C_Cmd(I2Cx, ENABLE);


  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = EEPROM_ADDRESS;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = /*(low_speed_i2c == 0 ) ? CLOCKSPEED_1MBIT :*/ CLOCKSPEED;
  I2C_Init(I2Cx, &I2C_InitStructure);

  /* ���������� ��� I2C ��������� ���������� �� �������� */
  I2C_ITConfig(I2Cx, I2C_IT_ERR, ENABLE);
}
/**************************************/

/*****************************************************/
//�����  ������ ������ �� I2C
/*
  ���������
  0 - ������� ����� ����
  1 - ������ ���� �������
  2 - �� ��������� ���� ����� ������� �� i2C
*/
/*****************************************************/
unsigned int start_write_buffer_via_I2C(uint32_t device_id, uint32_t WriteAddr,  uint8_t *pBuffer, uint32_t number)
{
  unsigned int error = 0; //0 - ������ ��������; 1 - ���� �������; 2 - ���� �������
  //���������� �� � ������ ������ ���������� ���������� ������ ��������� �������
  if (type_error_of_exchanging_via_i2c != 0)
  {
    type_error_of_exchanging_via_i2c |= (1<<ERROR_TOTAL_BIT);
    error = 2;
  }
  else
  {
    /*���������� �� ���� � �������� �� ������ ������� ���� �������*/
    if (I2C_GetFlagStatus(I2C, I2C_FLAG_BUSY))
    {
      if (number_busy_state < MAX_NUMBER_BUSY_STATE)
      {
        error = 1;
        number_busy_state++;
      }
      else
      {
        type_error_of_exchanging_via_i2c |= (1<<ERROR_TOTAL_BIT);
        error = 2;
      }
          
      /***/
      //��������, �� � ����������� ����
      /***/
      unsigned int temp_value = 0;
      while (((I2C_GetLastEvent(I2C) & I2C_EVENT_MASTER_BYTE_RECEIVED_NO_BUSY) !=0) && (temp_value < 100 ))
      {
        I2C_AcknowledgeConfig(I2C, DISABLE);
        I2C_GenerateSTOP(I2C, ENABLE);
        I2C_ReceiveData(I2C);
        temp_value++;
      }
      if (temp_value >= 100 )
      {
        type_error_of_exchanging_via_i2c |= (1<<ERROR_TOTAL_BIT);
        error = 2;
      }
      /***/
    }
    else
    {
      //������� ������� BUSY ������
      number_busy_state = 0;

      //���������� ��������� �������� ����� ����� I2C
      driver_i2c.state_execution = 0;
      driver_i2c.device_id = device_id;
      driver_i2c.action = 2;
      driver_i2c.internal_address = WriteAddr;
      driver_i2c.number_bytes = number;
      driver_i2c.point_buffer = pBuffer;
      
      //����������� ��������� ACK �������� ������� (��� ��� �������� ������ ��� �� �� ��� �� ��������)
      I2C_AcknowledgeConfig(I2C, ENABLE);

      /*������� ������ �������, �� ������ ���� ������������ � ������ �������*/
      I2C_ClearFlag(I2C, I2C_FLAG_TIMEOUT | I2C_FLAG_OVR | I2C_FLAG_AF | I2C_FLAG_ARLO | I2C_FLAG_BERR);
      
      /* ���������� ��� I2C ��������� ���������� �� ����� */
      I2C_ITConfig(I2C, I2C_IT_EVT, ENABLE);
      
      /* �������� STRAT*/
      I2C_GenerateSTART(I2C, ENABLE);
    }
  }
  
  return error;      
}
/*****************************************************/

/*****************************************************/
//�����  ������� ������ �� I2C
/*
  ���������
  0 - ������� ����� ����
  1 - ������ ���� �������
  2 - �� ��������� ���� ����� ������� �� i2C
*/
/*****************************************************/
unsigned int start_read_buffer_via_I2C(uint32_t device_id, uint32_t ReadAddr, uint8_t *pBuffer, uint32_t number)
{
  unsigned int error = 0; //0 - ������ ��������; 1 - ���� �������; 2 - ���� �������
  //���������� �� � ������ ������ ���������� ���������� ������ ��������� �������
  if (type_error_of_exchanging_via_i2c != 0)
  {
    type_error_of_exchanging_via_i2c |= (1<<ERROR_TOTAL_BIT);
    error = 2;
  }
  else
  {
    /*���������� �� ���� � �������� �� ������ ������� ���� �������*/
    if (I2C_GetFlagStatus(I2C, I2C_FLAG_BUSY))
    {
      if (number_busy_state < MAX_NUMBER_BUSY_STATE)
      {
        error = 1;
        number_busy_state++;
      }
      else
      {
        type_error_of_exchanging_via_i2c |= (1<<ERROR_TOTAL_BIT);
        error = 2;
      }
          
      /***/
      //��������, �� � ����������� ����
      /***/
      unsigned int temp_value = 0;
      while (((I2C_GetLastEvent(I2C) & I2C_EVENT_MASTER_BYTE_RECEIVED_NO_BUSY) !=0) && (temp_value < 100 ))
      {
        I2C_AcknowledgeConfig(I2C, DISABLE);
        I2C_GenerateSTOP(I2C, ENABLE);
        I2C_ReceiveData(I2C);
        temp_value++;
      }
      if (temp_value >= 100 )
      {
        type_error_of_exchanging_via_i2c |= (1<<ERROR_TOTAL_BIT);
        error = 2;
      }
      /***/
    }
    else
    {
      //������� ������� BUSY ������
      number_busy_state = 0;
      
      //���������� ��������� �������� ����� ����� I2C
      driver_i2c.state_execution = 0;
      driver_i2c.device_id = device_id;
      driver_i2c.action = 0;
      driver_i2c.internal_address = ReadAddr;
      driver_i2c.number_bytes = number;
      driver_i2c.point_buffer = pBuffer;
      
      //����������� ��������� ACK �������� �������
      I2C_AcknowledgeConfig(I2C, ENABLE);

      /*������� ������ �������, �� ������ ���� ������������ � ������ �������*/
      I2C_ClearFlag(I2C, I2C_FLAG_TIMEOUT | I2C_FLAG_OVR | I2C_FLAG_AF | I2C_FLAG_ARLO | I2C_FLAG_BERR);
      
      /* ���������� ��� I2C ��������� ���������� �� ����� */
      I2C_ITConfig(I2C, I2C_IT_EVT, ENABLE);
      
      /* �������� STRAT*/
      I2C_GenerateSTART(I2C, ENABLE);
    }
  }
  
  return error;      
}
/*****************************************************/

/*****************************************************/
//��������� ������ ����� I2C
/*****************************************************/
void main_routines_for_i2c(void)
{
  static unsigned int temp_value_for_rtc;
  static uint8_t reg_RTC[7];
  static uint8_t copy_register8_RTC;
  static uint8_t temp_register_rtc[2];
  
  if ((save_time_dat_l == 2) || (save_time_dat_h == 2))
  {
    if (save_time_dat_l == 2) save_time_dat_l = 1;
    if (save_time_dat_h == 2) save_time_dat_h = 1;
    
    _SET_BIT(control_i2c_taskes, TASK_START_WRITE_RTC_BIT);
    _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
  }

  if (driver_i2c.state_execution < 0)
  {
    /*************************************************/
    //����� ����� ���������� ���� ���������� ����� I2C
    /*************************************************/
    
    if(_CHECK_SET_BIT(control_i2c_taskes, TASK_SET_START_SETTINGS_RTC_BIT) !=0)
    {
      unsigned int rez;
      
      //����������� ������� RTC � ������� ������� �������� ��� ����, ��� �� ����� ���� 1 ��
      if (etap_settings_test_frequency == 0)
      {
        read_write_i2c_buffer[0] = temp_register_rtc[0];
        rez = start_write_buffer_via_I2C(RTC_ADDRESS, 0xC, read_write_i2c_buffer, 1);
      }
      else if (etap_settings_test_frequency == 1)
      {
        read_write_i2c_buffer[0] = 0xf0;
        rez = start_write_buffer_via_I2C(RTC_ADDRESS, 0x13, read_write_i2c_buffer, 1);
      }
      else
      {
        read_write_i2c_buffer[0] = temp_register_rtc[1];
        rez = start_write_buffer_via_I2C(RTC_ADDRESS, 0xA, read_write_i2c_buffer, 1);
      }
      
      //�������� ��������� ������� ������ ������
      if (rez > 1)
      {
        error_start_i2c();
        
        //������ ������ ������� �����, ��� ����������� �������, � ����������� �� ����� ���� ��������������
        type_error_of_exchanging_via_i2c = 0;
      }
      else if (rez == 0) _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);
    }
    else if((_CHECK_SET_BIT(control_i2c_taskes, TASK_RESET_OF_RTC_BIT) !=0) || (_CHECK_SET_BIT(control_i2c_taskes, TASK_RESET_ST_RTC_BIT) !=0))
    {
      unsigned int rez;
      
      if (_CHECK_SET_BIT(control_i2c_taskes, TASK_RESET_OF_RTC_BIT) !=0)
      {
        //�������� OF-�� � RTC
        if (etap_reset_of_bit == ETAP_CLEAR_OF_ST_STOP)
          read_write_i2c_buffer[0] = reg_RTC[1] | (1<<7); //ST = 1
        else if (etap_reset_of_bit == ETAP_CLEAR_OF_ST_CLEAR)
          read_write_i2c_buffer[0] = reg_RTC[1] & (~(1<<7)) ; //ST = 0
        else
          read_write_i2c_buffer[0] = (unsigned char)(temp_value_for_rtc) & (~(1<<2)) ; //OF = 0
      }
      else
      {
        read_write_i2c_buffer[0] = reg_RTC[1] & (~(1<<7)) ; //ST = 0
      }
      if ((_CHECK_SET_BIT(control_i2c_taskes, TASK_RESET_OF_RTC_BIT) !=0) && (etap_reset_of_bit != ETAP_CLEAR_OF_ST_STOP) &&(etap_reset_of_bit != ETAP_CLEAR_OF_ST_CLEAR))
        rez = start_write_buffer_via_I2C(RTC_ADDRESS, 0xF, read_write_i2c_buffer, 1);
      else 
        rez = start_write_buffer_via_I2C(RTC_ADDRESS, 0x1, read_write_i2c_buffer, 1);
      
      //�������� ��������� ������� ������ ������
      if (rez > 1)
      {
        error_start_i2c();
        
        //������ ������ ������� �����, ��� ����������� �������, � ����������� �� ����� ���� ��������������
        type_error_of_exchanging_via_i2c = 0;
      }
      else if (rez == 0) _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);
    }
    else if(_CHECK_SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT) !=0)
    {
      //����� ����� �������� � �������� ����������, ���� ������ �������� � ���� ����������
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_RTC_BIT) !=0)
    {
      copying_time_dat = 1;
      time_t time_dat_tmp = time_dat_copy + 1; //+1 ��� ���������� ��������, ���� ���� ������� �� �������� �������, ��� ��� �� �����...
      copying_time_dat = 0;
      struct tm *p;
      p = gmtime(&time_dat_tmp);
      
      
      //��������� ������ ������ ���� � RTC
      read_write_i2c_buffer[0] = 0;
      
      int tmp_reg = p->tm_sec;
      read_write_i2c_buffer[1] = INT_TO_BCD(tmp_reg) & 0x7F;

      tmp_reg = p->tm_min;
      read_write_i2c_buffer[2] = INT_TO_BCD(tmp_reg) & 0x7F;

      tmp_reg = p->tm_hour;
      read_write_i2c_buffer[3] = INT_TO_BCD(tmp_reg) & 0x3F;

      tmp_reg = p->tm_wday + 1;
      read_write_i2c_buffer[4] = tmp_reg & 0x7;

      tmp_reg = p->tm_mday;
      read_write_i2c_buffer[5] = INT_TO_BCD(tmp_reg) & 0x3F;

      tmp_reg = p->tm_mon + 1;
      read_write_i2c_buffer[6] = INT_TO_BCD(tmp_reg) & 0x1F;

      tmp_reg = p->tm_year - 100;
      read_write_i2c_buffer[7] = INT_TO_BCD(tmp_reg) & 0xFF;
      
      read_write_i2c_buffer[8] = (calibration & 0x3f) | (copy_register8_RTC & 0xC0);
      
      //��������� ���, ���� ����� � ��� ������� ����  ����� ������ 0
      time_t time_dat_tmp1;
      do
      {
        copying_time_dat = 1;
        time_dat_tmp1 = time_dat_copy;
        copying_time_dat = 0;
        
        watchdog_routine();
      }
      while (time_dat_tmp1 < time_dat_tmp);
      
      unsigned int rez = start_write_buffer_via_I2C(RTC_ADDRESS, START_ADDRESS_TIME_REGISTERS, read_write_i2c_buffer, 9);
      
      //�������� ��������� ������� ������ ������
      if (rez > 1)
      {
        error_start_i2c();
        
        //������ ������ ������� �����, ��� ����������� �������, � ����������� �� ����� ���� ��������������
        type_error_of_exchanging_via_i2c = 0;
      }
      else if (rez == 0)
      {
        _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);

        //��� �������� ������� ������� ������� �� ������� ������� RTC � ����������� �� ������� ������� RTC
        _SET_BIT(control_i2c_taskes, TASK_WRITING_RTC_BIT);
        _CLEAR_BIT(control_i2c_taskes, TASK_START_WRITE_RTC_BIT);
        
        if ((save_time_dat_l == 1) || (save_time_dat_h == 1))
        {
          if (save_time_dat_l == 1) save_time_dat_l = 0;
          if (save_time_dat_h == 1) save_time_dat_h = 0;
        }
      }
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_READ_RTC_BIT) !=0)
    {
      unsigned int rez;

      //��������� ������ ������� RTC
      rez = start_read_buffer_via_I2C(RTC_ADDRESS, START_ADDRESS_TIME_REGISTERS, read_write_i2c_buffer, MAX_NUMBER_REGISTERS_RTC);
      
      //�������� ��������� ������� ������ ������
      if (rez > 1)
      {
        error_start_i2c();
        
        //������ ������ ������� �����, ��� ����������� �������, � ����������� �� ����� ���� ��������������
        type_error_of_exchanging_via_i2c = 0;
      }
      else if (rez == 0)
      {
        _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);

        //��� �������� ������� ������� ������� �� ������� ������� RTC � ����������� �� ������� ������� RTC
        _SET_BIT(control_i2c_taskes, TASK_READING_RTC_BIT);
        _CLEAR_BIT(control_i2c_taskes, TASK_START_READ_RTC_BIT);
      }
    }
    
    /*************************************************/
  }
  else if (driver_i2c.state_execution == 1)
  {
    /*************************************************/
    //���� ���������� ��� �������
    /*************************************************/
    //����������� �����������, �� I2C ������� �� ���� ���������� 
    driver_i2c.state_execution = -1;

    if (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_RTC_BIT) !=0)
    {
      //�������� ��������� ����
      if (
          ((read_write_i2c_buffer[0xA ] & (1<< 6)) == 0 ) /*SQWE = 0*/ ||
          ((read_write_i2c_buffer[0xC] &  (1<< 6)) != 0 ) /*HT  = 1 */ ||
          ((read_write_i2c_buffer[0x13]          ) != 0xf0) /*������� �������*/ 
         )
      {
        //����� ������� ���  � ����� ��������� � ������ ��������, ��� �� ����� �������� 1��
        temp_register_rtc[0] = read_write_i2c_buffer[0xC ] & (unsigned char)(~ (1<< 6));
        temp_register_rtc[1] = read_write_i2c_buffer[0xA ] | (1<< 6);

        //����������� ��� �� ������������ �����������, ���� �� ��� �����-�� ����� ����������
        if((state_i2c_task & STATE_FIRST_READING_RTC) == 0 ) _SET_BIT(set_diagnostyka, RTC_WORK_FIELD_NOT_SET_BIT);
        else _SET_BIT(clear_diagnostyka, RTC_WORK_FIELD_NOT_SET_BIT);
        
        etap_settings_test_frequency = 0;
        _SET_BIT(control_i2c_taskes, TASK_SET_START_SETTINGS_RTC_BIT);
      } 
      else
        _SET_BIT(clear_diagnostyka, RTC_WORK_FIELD_NOT_SET_BIT);
      
      if ((read_write_i2c_buffer[0x1] &  (1<< 7)) != 0) /*ST = 1 */
      {
        //����� ���������� ��������� ��� RTC
        _SET_BIT(control_i2c_taskes, TASK_RESET_ST_RTC_BIT);
      }
      else if ((etap_reset_of_bit < ETAP_CLEAR_OF_ST_STOP) && ((read_write_i2c_buffer[0xf] & (1<<2)) != 0))
      {
        _SET_BIT(set_diagnostyka, RTC_OSCILLATOR_FAIL_BIT);
        //����� ST-�� ��������� � 1 � ������� ������� ���� � 0. �������� ����� 5 ������ �� �� ���������
        if((state_i2c_task & STATE_FIRST_READING_RTC) == 0 )
        {
          etap_reset_of_bit = ETAP_CLEAR_OF_ST_STOP;
          _SET_BIT(control_i2c_taskes, TASK_RESET_OF_RTC_BIT);
        }
        else
          etap_reset_of_bit = ETAP_CLEAR_OF_ST_START_WAITING_5S;
      }
      else if (etap_reset_of_bit == ETAP_CLEAR_OF_WRITE_OF_0)
      {
        //����� �������� OF-��
        temp_value_for_rtc = read_write_i2c_buffer[0xf];
        _SET_BIT(control_i2c_taskes, TASK_RESET_OF_RTC_BIT);
      }
      
      if ((read_write_i2c_buffer[0xC] & (1<< 6)) != 0)
      {
        //����������� ��� �� ������������ �����������, ���� �� ��� �����-�� ����� ����������
        if((state_i2c_task & STATE_FIRST_READING_RTC) == 0 )_SET_BIT(set_diagnostyka, RTC_UPDATING_HALTED_BIT);
        else _SET_BIT(clear_diagnostyka, RTC_UPDATING_HALTED_BIT);
      }
      else _SET_BIT(clear_diagnostyka, RTC_UPDATING_HALTED_BIT);
      if ((read_write_i2c_buffer[0x1] &  (1<< 7)) != 0) _SET_BIT(set_diagnostyka, RTC_OSCILLATOR_STOPED_BIT);
      else _SET_BIT(clear_diagnostyka, RTC_OSCILLATOR_STOPED_BIT);
      if ((read_write_i2c_buffer[0xF] &  (1<< 4)) != 0) _SET_BIT(set_diagnostyka, RTC_BATTERY_LOW_BIT);
      else _SET_BIT(clear_diagnostyka, RTC_BATTERY_LOW_BIT);
      if ((read_write_i2c_buffer[0xF] &  (1<< 2)) == 0) _SET_BIT(clear_diagnostyka, RTC_OSCILLATOR_FAIL_BIT);
      
      //���������� ���
      reg_RTC[0] = read_write_i2c_buffer[0] & 0xff;
      reg_RTC[1] = read_write_i2c_buffer[1] & 0x7f;
      reg_RTC[2] = read_write_i2c_buffer[2] & 0x7f;
      reg_RTC[3] = read_write_i2c_buffer[3] & 0x3f;
      reg_RTC[4] = read_write_i2c_buffer[5] & 0x3f;
      reg_RTC[5] = read_write_i2c_buffer[6] & 0x1f;
      reg_RTC[6] = read_write_i2c_buffer[7] & 0xff;
      copy_register8_RTC = read_write_i2c_buffer[8];
      calibration = copy_register8_RTC & 0x3f;

      struct tm orig;
      unsigned int tmp_reg = reg_RTC[1];
      orig.tm_sec = 10*(tmp_reg >> 4) + (tmp_reg & 0xf);

      tmp_reg = reg_RTC[2];
      orig.tm_min = 10*(tmp_reg >> 4) + (tmp_reg & 0xf);

      tmp_reg = reg_RTC[3];
      orig.tm_hour = 10*(tmp_reg >> 4) + (tmp_reg & 0xf);

      tmp_reg = reg_RTC[4];
      orig.tm_mday = 10*(tmp_reg >> 4) + (tmp_reg & 0xf);

      tmp_reg = reg_RTC[5];
      orig.tm_mon = 10*(tmp_reg >> 4) + (tmp_reg & 0xf) - 1;

      tmp_reg = reg_RTC[6];
      orig.tm_year = 10*(tmp_reg >> 4) + (tmp_reg & 0xf) + 100;

      orig.tm_wday = 0;
      orig.tm_yday = 0;
      orig.tm_isdst = -1;

      lt_or_utc = true;
#if (__VER__ >= 8000000)
      _ForceReloadDstRules();
#endif
      //������ � Watchdog
      watchdog_routine();
      time_t time_dat_tmp = mktime (&orig);
      lt_or_utc = false;
#if (__VER__ >= 8000000)
      _ForceReloadDstRules();
#endif
      tmp_reg = reg_RTC[0];
      int32_t time_ms_tmp = 100*(tmp_reg >> 4) + 10*(tmp_reg & 0xf);
      
      if((state_i2c_task & STATE_FIRST_READING_RTC) !=0)
      {
        //����� ���������� ����� ���������� ����� � RTC - ������� �� ������� �������
        state_i2c_task &= (unsigned int)(~STATE_FIRST_READING_RTC);
      }

      if(
         (_CHECK_SET_BIT(    diagnostyka, EVENT_START_SYSTEM_BIT       ) != 0) ||
         (_CHECK_SET_BIT(set_diagnostyka, EVENT_START_SYSTEM_BIT       ) != 0) ||
         (_CHECK_SET_BIT(    diagnostyka, EVENT_RESTART_SYSTEM_BIT     ) != 0) ||
         (_CHECK_SET_BIT(set_diagnostyka, EVENT_RESTART_SYSTEM_BIT     ) != 0) ||
         (_CHECK_SET_BIT(    diagnostyka, EVENT_SOFT_RESTART_SYSTEM_BIT) != 0) ||
         (_CHECK_SET_BIT(set_diagnostyka, EVENT_SOFT_RESTART_SYSTEM_BIT) != 0)
        )
      {
        static unsigned int fixed_power_down_into_RTC;
        
        //�� ����� ���� �� �� ������� ����� ������� ������ ����
        if((read_write_i2c_buffer[0xC] & (1<< 6)) != 0)
        {
          //������� ���, ���� ������� �������� � RTC �������� ���������� ��������
          fixed_power_down_into_RTC = 1; //����������� ����������� ��� ��, �� ���� ����������� ���������� �������� �� ��������� RTC �� ����, �� �������� ���������� ��������

          if ((head_fifo_buffer_pr_err_records > 1) && (tail_fifo_buffer_pr_err_records == 0))
          {
            //�� �������������, �� ������ � ����� ���� �� ���� �� ������ ��� ������ � ����� FIFO ���� ��� ������� ������ ������� � �����/������� �������, � ����� � ��������� dataFlash ��  � ����������
            unsigned int local_point_for_time = tail_fifo_buffer_pr_err_records*SIZE_ONE_RECORD_PR_ERR + 1 ; //������ ������� ����� ���� � ��� ������� ����� (������ ����� ������ �� ���� - ������� ������ �������) (tail_fifo_buffer_pr_err_records �� ���������� 0 � ������ ���� ��������)
            //���, ���� ����� ���������� � RTC �� ������� �������� ��� HT ����� �� ��� �� ���������� �������� � ��������� RTC
            for(unsigned int i = 0; i < sizeof(time_t); i++)  buffer_pr_err_records[local_point_for_time + i] = *((unsigned char*)(&time_dat_tmp) + i);
            for(unsigned int i = 0; i < sizeof(int32_t); i++)  buffer_pr_err_records[local_point_for_time + sizeof(time_t) + i] = *((unsigned char*)(&time_ms_tmp) + i);
          }
        }
        else
        {
          //������� ����� ������ ���� � ������� �������/����������� ��������
          unsigned int local_point_for_time;

          if (fixed_power_down_into_RTC == 0)
          {
            //�� ������, �� �������� �� ���������� ���� ���������� �������� �� ��������� RTC �� ������� �������/����������� ��������
            /*
            ���� ���� ��� ������� �������� ���� �������� �� ���������� �� �����
            ������ ������������ "������" ������ FIF0  � �������� 1
            (����� 0 �� ������� ������������� ������ � ��������� ���������� ����,
            ����� ������������ ����������� ������������  - �� ���� ��� ������� ������ �������,
            � 1 - �� �������� ����)
            */
            if ((head_fifo_buffer_pr_err_records > 0) && (tail_fifo_buffer_pr_err_records == 0))
            {
              //�� �������������, �� ������ � ����� ���� �� ���� �� ������ ��� ������ � ����� FIFO ���� ��� ������� ������ ������� � �����/������� �������, � ����� � ��������� dataFlash ��  � ����������
              /*
              ���� ����� �������� ���� ����� (head_fifo_buffer_pr_err_records > 0)
              �� ���������� ������� ��� ���� �� ������������ �� ��� �� ������ �� ������, � ��� 
              head_fifo_buffer_pr_err_records = 0 � tail_fifo_buffer_pr_err_records = 0,
              � �� ���� ��������. �� ���� ����� ������ � ���� �� ������ � ���� � �����. �� ������ 
              ������������� �� ���� � �������. ��� �� � ���������, �� �� ������, � � ����� ���� ������㳿
              ������������ ����������� ������������.
              
              ���� �� ����� �� ���������� ������� ��� ���� �� ������������ ��������.
              �� � � ���� � ���� �� ���� ��������, ���� ���� ������� ���������, ��� ����. �� ��� ������ ��������
              �� ����� ������, �� ��� �� � ���������, �� �� ������, � � ����� ���� ������㳿
              ������������ ����������� ������������  - ��� � �� �����, �� �� � ������� �� ����������� 
              ������ "�������" ������� ����������� ������������
              */
              tail_fifo_buffer_pr_err_records += 1;
              while(tail_fifo_buffer_pr_err_records >= MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER) tail_fifo_buffer_pr_err_records -= MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER;
            }

            local_point_for_time = tail_fifo_buffer_pr_err_records*SIZE_ONE_RECORD_PR_ERR + 1; //������ ������� ����� ���� � ������� �����, ���� ���� �� ����� � DataFlash
          }
          else
          {
            local_point_for_time = (tail_fifo_buffer_pr_err_records + 1)*SIZE_ONE_RECORD_PR_ERR + 1; //������ ������� ����� ���� � ������� �����, ���� ���� �� ����� � DataFlash
          }

          copying_time_to_RTC = 2;
          time_dat_RTC = time_dat_tmp;
          time_ms_RTC = time_ms_tmp;
          copying_time_to_RTC = 1;

          //������������ ����� ���� ��� ��� ����, �� ���� ���� �� ���������� ����� ������� ������ ����
          /*
          ����� local_point_for_time ����� ����� �� ����� ����� ���� ������� ������ (���� ���� �������� ���������� �������� ����� �������),
          ��� ������� ������ (���� ���������� �������� �� RTC ����� ������� �������� �� ���� �����������)
          */
          
          //������� ������� ����������� ������������ ������ �� ������� ������������� ������������ ��� ������� ����
          temporary_block_writing_records_pr_err_into_DataFlash = 1;
          /*���� � ���� � ��������� ������ ���������� � ������ ��� ����, �� 
          �� ������� ���� ���� � ����-���� ������ ���� ���� ��������� ���������������
          �������, ��� ������ ����� ����� (��� ������ ���� ������� ���,
          ���� ���� ��䳿 ��� ������/���������� ). ��� ���� ��� � ������ � ����������
          ���� ��� ������/���������� ��������, �� � ����� ������ ���������� ������
          ����������� � ��������� DataFlash �, ���� �������, ������������ ������� ����
          � ������ ���������� ������.
          ����, ���������� ���� ����, �� ����� ���� ��� �� ����������, ��� �� �������
          ������ ��䳿 �������/�����������, ����������� ����� ����� � ����� �� ���� ������ ����.
          ���� �������� �������� ���� ������ �������� ������������ ������� ���� � ����� 
          ���������� ������, ���� � �������� ������� �� �������������� ������� ����
          � ������ �������.
          �� ���� �������� ���������� ������������ ������������ ������� ���� ���� �����������
          ����������� ������ � ��������� DataFlash.
          ��� ����� �� ����� �������, �� � ����� ������, �� ����� ���� ��������� 
          � � ������ ���������� ������ � �������������� ������� ���� � ���� ������� ��������
          ���� ������� ������������ ������ ����, �� ���� �� �� ������� � ����
          ������� ��������, �� �� ���� �������� ������� ������ �������� ����. �����
          �� ��� ������ ���� �� ���� ���� "�����" ������ ����, ��� �� �� � �����. 
          � ������� ������� ������������ ���� ���� ����� ���� ��������� �������.
          */
          do
          {
            while (
                   (local_point_for_time < (head_fifo_buffer_pr_err_records*SIZE_ONE_RECORD_PR_ERR)) &&
                   (local_point_for_time <  SIZE_BUFFER_FOR_PR_ERR)
                  )
            {
              for(unsigned int i = 0; i < sizeof(time_t); i++)  buffer_pr_err_records[local_point_for_time + i] = *((unsigned char*)(&time_dat_tmp) + i);
              for(unsigned int i = 0; i < sizeof(int32_t); i++)  buffer_pr_err_records[local_point_for_time + sizeof(time_t) + i] = *((unsigned char*)(&time_ms_tmp) + i);
              local_point_for_time += SIZE_ONE_RECORD_PR_ERR;
            }
            
            //������� ��� ������� �������� ��� �� �����������
            _SET_BIT(clear_diagnostyka, EVENT_START_SYSTEM_BIT);
            _SET_BIT(clear_diagnostyka, EVENT_RESTART_SYSTEM_BIT);
            _SET_BIT(clear_diagnostyka, EVENT_SOFT_RESTART_SYSTEM_BIT);
          }
          while (
                 (local_point_for_time < (head_fifo_buffer_pr_err_records*SIZE_ONE_RECORD_PR_ERR)) &&
                 (local_point_for_time <  SIZE_BUFFER_FOR_PR_ERR) &&
                 (copying_time_to_RTC == 2)  
                );
          //������������ ������� ����������� ������������ ������, �� � ������, �� ����� ���� � ��� ����������� ���������
          temporary_block_writing_records_pr_err_into_DataFlash = 0;
        }
      }
      else
      {
        copying_time_to_RTC = 2;
        time_dat_RTC = time_dat_tmp;
        time_ms_RTC = time_ms_tmp;
        copying_time_to_RTC = 1;
      }

      //������� ����������� ��� ������� ���������� ����
      _CLEAR_BIT(control_i2c_taskes, TASK_READING_RTC_BIT);
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_RTC_BIT) !=0)
    {
      //����������� ������� ������� ���������� ���� 
      _SET_BIT(control_i2c_taskes, TASK_START_READ_RTC_BIT);
      _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);

      _CLEAR_BIT(control_i2c_taskes, TASK_WRITING_RTC_BIT);
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_SET_START_SETTINGS_RTC_BIT) !=0)
    {
      etap_settings_test_frequency++;
      if (etap_settings_test_frequency > 2)
      {
        etap_settings_test_frequency = -1;

        //�������� ��������� ������� ������� RTC
        _SET_BIT(control_i2c_taskes, TASK_START_READ_RTC_BIT);
        _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);

        //������� �� ����������� ��� � ���� � ������� ��������, ���� �� ���� ��������
        _CLEAR_BIT(control_i2c_taskes, TASK_SET_START_SETTINGS_RTC_BIT);
      }
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_RESET_ST_RTC_BIT) !=0)
    {
      //������� �� ������� ���������� RTC
      _CLEAR_BIT(control_i2c_taskes, TASK_RESET_ST_RTC_BIT);
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_RESET_OF_RTC_BIT) !=0)
    {
      etap_reset_of_bit++;
      if (etap_reset_of_bit == ETAP_CLEAR_OF_ST_START_WAITING_5S)
      {
        //������� �������� �������� ������������  �������� OF-���, ��� �� ���� ��������� 5� ��� ����������� �������� OF-���
        _CLEAR_BIT(control_i2c_taskes, TASK_RESET_OF_RTC_BIT);
      }
      else if (etap_reset_of_bit >= ETAP_CLEAR_OF_WRITE_OF_0)
      {
        //������� �������� �������� �������� OF-���
        etap_reset_of_bit = ETAP_CLEAR_OF_NONE;
        _CLEAR_BIT(control_i2c_taskes, TASK_RESET_OF_RTC_BIT);
      }
    }
    else
    {
      //����, ����������, ������ �� ���� � ����
      //� ��� ������� �������� ������ �� ������
    }
    /*************************************************/
  }
  else if (driver_i2c.state_execution == 2)
  {
    /*************************************************/
    //���� ���������� � ��������
    /*************************************************/

    //������ ������ ������� �����, ��� ����������� �������, � ����������� �� ����� ���� ��������������
    type_error_of_exchanging_via_i2c = 0;
    
    //����������� �����������, �� I2C ������� �� ���� ���������� 
    driver_i2c.state_execution = -1;

    //����������� � ���������� ����
    if (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_RTC_BIT) !=0)
    {
      //����� ����� ������� RTC
      
      //�������� ��������� ������ ������� RTC
      _SET_BIT(control_i2c_taskes, TASK_START_READ_RTC_BIT);
      _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
      _CLEAR_BIT(control_i2c_taskes, TASK_READING_RTC_BIT);
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_RTC_BIT) !=0)
    {
      //����� ����� ������ RTC
      
      //�������� ��������� ������ ������ RTC
      _SET_BIT(control_i2c_taskes, TASK_START_WRITE_RTC_BIT);
      _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        
      _CLEAR_BIT(control_i2c_taskes, TASK_WRITING_RTC_BIT);
    }
    else if (
             (_CHECK_SET_BIT(control_i2c_taskes, TASK_RESET_OF_RTC_BIT          ) !=0) ||
             (_CHECK_SET_BIT(control_i2c_taskes, TASK_SET_START_SETTINGS_RTC_BIT) !=0) ||
             (_CHECK_SET_BIT(control_i2c_taskes, TASK_RESET_ST_RTC_BIT          ) !=0)
            )
    {
      //�������� ��������� �������� � ���� ������ ����, ��� �� ������
    }
    else
    {
      //� ��� ������� �������� ������ �� ������
    }
    /*************************************************/
  }
}
/*****************************************************/

/*****************************************************/
//���������������� I2C ��� ����������� ���������� ������� ����������
/*****************************************************/
void error_start_i2c(void)
{
  _SET_BIT(set_diagnostyka, ERROR_START_VIA_I2C_BIT);
          
  /**************/
  //����������������� I2C
  /**************/
  //��������� ��������� ���������� �� I2C
  I2C_ITConfig(I2C, I2C_IT_ERR | I2C_IT_EVT | I2C_IT_BUF, DISABLE);
           
  //��������� ������ DMA ���� ���� ��������
  if ((DMA_StreamI2C_Tx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamI2C_Tx->CR &= ~(uint32_t)DMA_SxCR_EN;
  if ((DMA_StreamI2C_Rx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamI2C_Rx->CR &= ~(uint32_t)DMA_SxCR_EN;
          
  //����������������� I2C
  Configure_I2C(I2C);
  /**************/
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/

