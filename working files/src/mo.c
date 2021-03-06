#include "header.h"

/***********************************************************************************
������ ����� ����� ��������� CANAL1_MO
***********************************************************************************/
void start_receive_data_via_CANAL1_MO(void)
{
  //���������� ������� ������������ ��� �������, �� ���� ������ ����������
  clear_diagnostyka[0] |= WORD_0_MASKA_ERRORS_FROM_CANAL_1;
  clear_diagnostyka[1] |= WORD_1_MASKA_ERRORS_FROM_CANAL_1;
  clear_diagnostyka[2] |= WORD_2_MASKA_ERRORS_FROM_CANAL_1;
  clear_diagnostyka[3] |= WORD_3_MASKA_ERRORS_FROM_CANAL_1;
  
  //��������� ����� ���������
  if ((DMA_StreamCANAL1_MO_Rx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamCANAL1_MO_Rx->CR &= ~(uint32_t)DMA_SxCR_EN;  
  
  if(DMA_StreamCANAL1_MO_Rx->NDTR != BUFFER_CANAL1_MO)
  {
    uint32_t error_status = 0;
    do
    {
      error_status |= CANAL1_MO->SR;
    }
    while ((error_status & (USART_FLAG_IDLE | USART_FLAG_LBD)) == 0);
    int32_t size_packet = BUFFER_CANAL1_MO - (uint16_t)(DMA_StreamCANAL1_MO_Rx->NDTR);
    
    error_status &= (USART_FLAG_ORE | USART_FLAG_NE | USART_FLAG_FE | USART_FLAG_PE);
    
    //������� ���� � ������������� ����� �� ������ 1
    if (
        (error_status == 0) &&
        (size_packet >= 3) &&
        (Canal1_MO_Received[0] == START_BYTE_MO) && 
        (Canal1_MO_Received[size_packet - 1] == STOP_BYTE_MO)  
       )   
    {
      //���������� ������
      if (
          (Canal1_MO_Received[1] == BROADCAST_ADDRESS_MO) ||
          (Canal1_MO_Received[1] == my_address_mo)
         )   
      {
        //���������� ���������� ����
        uint8_t sum = 0;
        for (int32_t i = 0; i < (size_packet - 3); i++) sum += Canal1_MO_Received[1 + i];
        if (sum == Canal1_MO_Received[size_packet - 2])
        { 
          IEC_board_uncall = 0;
          IEC_board_address = Canal1_MO_Received[2];
          
          uint32_t index = 4;
          switch (Canal1_MO_Received[3])
          {
          case SENDING_GOOSE_INFO:
            {
              //����� � �� ��� ����� �� �� � ���
              uint32_t IEC_queue_mo = 0;
              uint8_t *point = (uint8_t*)(&IEC_queue_mo);
              for (uint32_t i = 0; ((i < sizeof(IEC_queue_mo)) && (index < BUFFER_CANAL1_MO)); i++) 
              {
                *(point++) = Canal1_MO_Received[index++];
              }
              
              if (_GET_OUTPUT_STATE(IEC_queue_mo, IEC_STATE_QUEUE_MO_ASK_BASIC_SETTINGS)) 
                _SET_STATE(queue_mo_irq, STATE_QUEUE_MO_ASK_BASIC_SETTINGS);
              else 
                _CLEAR_STATE(queue_mo_irq, STATE_QUEUE_MO_ASK_BASIC_SETTINGS);

              if (_GET_OUTPUT_STATE(IEC_queue_mo, IEC_STATE_QUEUE_MO_ASK_MAKING_MEMORY_BLOCK)) 
                _SET_STATE(queue_mo_irq, STATE_QUEUE_MO_ASK_MAKING_MEMORY_BLOCK);
              else 
                _CLEAR_STATE(queue_mo_irq, STATE_QUEUE_MO_ASK_MAKING_MEMORY_BLOCK);

              if (_GET_OUTPUT_STATE(IEC_queue_mo, IEC_STATE_QUEUE_MO_ASK_SENDING_SETTING_NETWORK_LAYER)) 
                _SET_STATE(queue_mo_irq, STATE_QUEUE_MO_ASK_SENDING_SETTING_NETWORK_LAYER);
              else 
                _CLEAR_STATE(queue_mo_irq, STATE_QUEUE_MO_ASK_SENDING_SETTING_NETWORK_LAYER);

              if (_GET_OUTPUT_STATE(IEC_queue_mo, IEC_STATE_QUEUE_MO_NEW_MODBUS_TCP_REQ)) 
                _SET_STATE(queue_mo_irq, STATE_QUEUE_MO_ASK_NEW_MODBUS_TCP_REQ);
              else 
                _CLEAR_STATE(queue_mo_irq, STATE_QUEUE_MO_ASK_NEW_MODBUS_TCP_REQ);
              
              if (_GET_OUTPUT_STATE(IEC_queue_mo, IEC_STATE_QUEUE_MO_TRANSACTION_PROGRESS)) 
                _SET_STATE(queue_mo_irq, STATE_QUEUE_MO_TRANSACTION_PROGRESS_IN_IEC);
              else 
                _CLEAR_STATE(queue_mo_irq, STATE_QUEUE_MO_TRANSACTION_PROGRESS_IN_IEC);
              
              //������������� ����
              index += sizeof(time_t) + sizeof(int32_t);
              if (Canal1_MO_Received[index++] != 0)
              {
                //����� ���������� ��������� ���
                int32_t index_tmp = index - 1 - sizeof(time_t) - sizeof(int32_t);
                if (index_tmp > 0)
                {
                  for(size_t i = 0; i < sizeof(time_t); i++)  *((uint8_t *)(&time_dat_save_h) + i) = Canal1_MO_Received[index_tmp++];
                  int32_t time_ms_tmp;
                  for(size_t i = 0; i < sizeof(int32_t); i++)  *((uint8_t *)(&time_ms_tmp) + i) = Canal1_MO_Received[index_tmp++];
                  time_ms_save_h = time_ms_tmp / 1000;
                  save_time_dat_h = 3;
                }
                else total_error_sw_fixed(84);
              }
              
              /***
              ���������� ����
              ***/
              while (
                     (Canal1_MO_Received[index] == START_LABEL_NEW_TM) &&
                     (index < BUFFER_CANAL1_MO)  
                    )   
              {
                index++;
                if (Canal1_MO_Received[index++] == 0) /*��� ����� ������� ����������� ������ ����*/
                {
                  size_t shift = Canal1_MO_Received[index + 0] | (Canal1_MO_Received[index + 1] << 8);
                  size_t size = Canal1_MO_Received[index + 2] | (Canal1_MO_Received[index + 3] << 8);
                  index += 4;
                  
                  if ((index + size) < BUFFER_CANAL1_MO)
                  {
                    for (size_t i = 0; i < size; i++)
                    {
                      size_t shift_tmp = shift + i;
                      if (shift_tmp < sizeof(Input_In_GOOSE_block))
                      {
                        *((uint8_t*)(&Input_In_GOOSE_block) + shift_tmp) = Canal1_MO_Received[index++];
                      }
                      else
                      {
                        shift_tmp -= sizeof(Input_In_GOOSE_block);
                        if (shift_tmp < sizeof(Input_In_MMS_block))
                        {
                          *((uint8_t*)(&Input_In_MMS_block) + shift_tmp) = Canal1_MO_Received[index++];
                        }
                        else
                        {
                          shift_tmp -= sizeof(Input_In_MMS_block);
                          if (shift_tmp < sizeof(Input_ctrl_In_GOOSE_block))
                          {
                            *((uint8_t*)(&Input_ctrl_In_GOOSE_block) + shift_tmp) = Canal1_MO_Received[index++];
                          }
                          else
                          {
                            shift_tmp -= sizeof(Input_ctrl_In_GOOSE_block);
                            if (shift_tmp < sizeof(Input_ctrl_In_MMS_block))
                            {
                              *((uint8_t*)(&Input_ctrl_In_MMS_block) + shift_tmp) = Canal1_MO_Received[index++];
                            }
                            else total_error_sw_fixed(85);
                          }
                        }
                      }
                    }
                  }
                  else total_error_sw_fixed(220);
                }
                else total_error_sw_fixed(89);
              }

              if(
                 ((index + 1 +  sizeof(confirm_diagnostyka_mo)) < BUFFER_CANAL1_MO) &&
                 (Canal1_MO_Received[index++] == START_LABEL_CONF_DIAGN)
                )   
              {
                //ĳ��������� ����� �� ������1
                point = (uint8_t*)(&confirm_diagnostyka_mo);
                for (uint32_t i = 0; i < sizeof(confirm_diagnostyka_mo); i++) 
                {
                  *(point++) = Canal1_MO_Received[index++];
                }
                if (_GET_OUTPUT_STATE(confirm_diagnostyka_mo, ERROR_RECEIVING_CANAL_1)      ) _SET_BIT(set_diagnostyka, ERROR_IEC_RECEIVING_CANAL_1);
                if (_GET_OUTPUT_STATE(confirm_diagnostyka_mo, ERROR_RECEIVED_PACKET_CANAL_1)) _SET_BIT(set_diagnostyka, ERROR_IEC_RECEIVED_PACKET_CANAL_1);
                if (_GET_OUTPUT_STATE(confirm_diagnostyka_mo, ERROR_REQUEST_CANAL_1)        ) _SET_BIT(set_diagnostyka, ERROR_IEC_REQUEST_CANAL_1);
                if (_GET_OUTPUT_STATE(confirm_diagnostyka_mo, ERROR_NO_ANSWER_CANAL_1)      ) _SET_BIT(set_diagnostyka, ERROR_IEC_NO_ANSWER_CANAL_1);

                if (_GET_OUTPUT_STATE(confirm_diagnostyka_mo, ERROR_RECEIVING_CANAL_2)      ) _SET_BIT(set_diagnostyka, ERROR_IEC_RECEIVING_CANAL_2);
                if (_GET_OUTPUT_STATE(confirm_diagnostyka_mo, ERROR_RECEIVED_PACKET_CANAL_2)) _SET_BIT(set_diagnostyka, ERROR_IEC_RECEIVED_PACKET_CANAL_2);
                if (_GET_OUTPUT_STATE(confirm_diagnostyka_mo, ERROR_REQUEST_CANAL_2)        ) _SET_BIT(set_diagnostyka, ERROR_IEC_REQUEST_CANAL_2);
              }
              
              
              /***/
              break;
            }
          default:
            {
              _SET_BIT(set_diagnostyka, ERROR_CPU_ANSWER_CANAL_1);
              
              break;
            }
          }
        }
        else _SET_BIT(set_diagnostyka, ERROR_CPU_RECEIVED_PACKET_CANAL_1);
      }
    }
    else _SET_BIT(set_diagnostyka, ERROR_CPU_RECEIVING_CANAL_1);
  }
  else
  {
    //�� ������� ���� � ������������� ����� �� ������ 1
    if (restart_KP_irq == 0)
    {
      if (IEC_board_uncall == 0) _SET_BIT(set_diagnostyka, ERROR_CPU_NO_ANSWER_CANAL_1);
      else IEC_board_uncall--;
    }
  }
      
  //������� �� ������ �������
  CANAL1_MO->SR;
  (unsigned short int)(CANAL1_MO->DR & (uint16_t)0x01FF);
  CANAL1_MO->SR = (uint16_t)(~(uint32_t)USART_FLAG_LBD);
      
  // ������� ���������, �� �������� ��� ���������� �������� ����� ��� DMA1 �� ������ RS-485_RX 
  DMA_ClearFlag(DMA_StreamCANAL1_MO_Rx, DMA_FLAG_TCCANAL1_MO_Rx | DMA_FLAG_HTCANAL1_MO_Rx | DMA_FLAG_TEICANAL1_MO_Rx | DMA_FLAG_DMEICANAL1_MO_Rx | DMA_FLAG_FEICANAL1_MO_Rx);

  DMA_StreamCANAL1_MO_Rx->NDTR = BUFFER_CANAL1_MO;
  //��������� ���������� �������
  DMA_StreamCANAL1_MO_Rx->CR |= (uint32_t)DMA_SxCR_EN;
}
/***********************************************************************************/

/***********************************************************************************
������ ������� ��� �������� ����� ����� ��������� CANAL1_MO
***********************************************************************************/
void start_transmint_data_via_CANAL1_MO(void)
{
  uint8_t sum = 0;
  uint32_t index = 0;
  
         Canal1_MO_Transmit[index++] = START_BYTE_MO;
  sum += Canal1_MO_Transmit[index++] = BROADCAST_ADDRESS_MO;
  sum += Canal1_MO_Transmit[index++] = my_address_mo;
  
  sum += Canal1_MO_Transmit[index++] = SENDIND_TM_INFO;
    
  for(size_t i = 0; i < sizeof(time_t); i++) sum += Canal1_MO_Transmit[index++] = *((uint8_t *)(&time_dat) + i);
  int32_t time_ms_tmp = time_ms * 1000;
  for(size_t i = 0; i < sizeof(int32_t); i++) sum += Canal1_MO_Transmit[index++] = *((uint8_t *)(&time_ms_tmp) + i);
  
  //���������� ����
  if ((index + 1 + 1 + 2 + 2 + SIZE_SENDING_DATA_TM) < BUFFER_CANAL1_MO)
  {
    sum += Canal1_MO_Transmit[index++] = START_LABEL_NEW_TM;
    
    sum += Canal1_MO_Transmit[index++] = 0;
    
    sum += Canal1_MO_Transmit[index++] = 0;
    sum += Canal1_MO_Transmit[index++] = 0;
    
    sum += Canal1_MO_Transmit[index++] = (SIZE_SENDING_DATA_TM & 0xff);
    sum += Canal1_MO_Transmit[index++] = ((SIZE_SENDING_DATA_TM >> 8) & 0xff);
    
    for (uint32_t i = 0; i < sizeof(measurement); i++) 
    {
      sum += Canal1_MO_Transmit[index++] = *(((uint8_t *)measurement) + i);
    }
    
    float frequency_tmp  = frequency;
    uint8_t *point = (uint8_t*)(&frequency_tmp);
    for (uint32_t i = 0; i < sizeof(frequency_tmp); i++) 
    {
      sum += Canal1_MO_Transmit[index++] = *(point++);
    }
    
    for (uint32_t i = 0; i < sizeof(resistance); i++) 
    {
      sum += Canal1_MO_Transmit[index++] = *(((uint8_t *)resistance) + i);
    }
    
    uint32_t bank_for_calc_power_tmp = (state_calc_power == false ) ? bank_for_calc_power : ((bank_for_calc_power ^ 0x1) & 0x1);
    
    point = (uint8_t*)(&P[bank_for_calc_power_tmp]);
    for (uint32_t i = 0; i < (sizeof(P) >> 1); i++) 
    {
      sum += Canal1_MO_Transmit[index++] = *(point++);
    }
    
    point = (uint8_t*)(&Q[bank_for_calc_power_tmp]);
    for (uint32_t i = 0; i < (sizeof(Q) >> 1); i++) 
    {
      sum += Canal1_MO_Transmit[index++] = *(point++);
    }
    
    point = (uint8_t*)(&S[bank_for_calc_power_tmp]);
    for (uint32_t i = 0; i < (sizeof(S) >> 1); i++) 
    {
      sum += Canal1_MO_Transmit[index++] = *(point++);
    }
    
    point = (uint8_t*)(&cos_phi_x1000[bank_for_calc_power_tmp]);
    for (uint32_t i = 0; i < (sizeof(cos_phi_x1000) >> 1); i++) 
    {
      sum += Canal1_MO_Transmit[index++] = *(point++);
    }

    uint32_t bank_for_calc_energy_tmp = (state_calc_energy == false ) ? 0 : 1;
    
    point = (uint8_t*)(&energy[bank_for_calc_energy_tmp]);
    for (uint32_t i = 0; i < (sizeof(energy) >> 1); i++) 
    {
      sum += Canal1_MO_Transmit[index++] = *(point++);
    }

    uint32_t bank_for_calc_phi_angle_tmp = (state_calc_phi_angle == false ) ? bank_for_calc_phi_angle : ((bank_for_calc_phi_angle ^ 0x1) & 0x1);
    
    point = (uint8_t*)(&phi_angle[bank_for_calc_phi_angle_tmp]);
    for (uint32_t i = 0; i < (sizeof(phi_angle) >> 1); i++) 
    {
      sum += Canal1_MO_Transmit[index++] = *(point++);
    }
    
    point = (uint8_t*)(&resurs_vymykacha);
    for (uint32_t i = 0; i < sizeof(resurs_vymykacha); i++) 
    {
      sum += Canal1_MO_Transmit[index++] = *(point++);
    }

    point = (uint8_t*)(&resurs_vidkljuchennja);
    for (uint32_t i = 0; i < sizeof(resurs_vidkljuchennja); i++) 
    {
      sum += Canal1_MO_Transmit[index++] = *(point++);
    }

    for (uint32_t i = 0; i < sizeof(state_inputs); i++) 
    {
      sum += Canal1_MO_Transmit[index++] = *(((uint8_t *)&state_inputs) + i);
    }
    
    for (uint32_t i = 0; i < sizeof(state_outputs); i++) 
    {
      sum += Canal1_MO_Transmit[index++] = *(((uint8_t *)&state_outputs) + i);
    }
    
    for (uint32_t i = 0; i < sizeof(state_leds); i++) 
    {
      sum += Canal1_MO_Transmit[index++] = *(((uint8_t *)&state_leds) + i);
    }
    
    for (uint32_t i = 0; i < sizeof(active_functions); i++) 
    {
      sum += Canal1_MO_Transmit[index++] = *(((uint8_t *)active_functions) + i);
    }
    
    for (uint32_t i = 0; i < sizeof(diagnostyka); i++) 
    {
      sum += Canal1_MO_Transmit[index++] = *(((uint8_t *)diagnostyka) + i);
    }
    
    for (uint32_t i = 0; i < sizeof(Output_Out_LAN_block); i++) 
    {
      sum += Canal1_MO_Transmit[index++] = *(((uint8_t *)Output_Out_LAN_block) + i);
    }
  }
    
  if ((index + 1 + sizeof(confirm_diagnostyka_mo)) < BUFFER_CANAL1_MO)
  {
    sum += Canal1_MO_Transmit[index++] = START_LABEL_CONF_DIAGN;
    uint8_t *point = (uint8_t*)(&confirm_diagnostyka_mo);
    for (uint32_t i = 0; i < sizeof(confirm_diagnostyka_mo); i++) 
    {
      sum += Canal1_MO_Transmit[index++] = *(point++);
    }
    confirm_diagnostyka_mo = 0; //������� ����������� ���������� ������ ����� ��� ������ 1
  }

  if ((index + 2) >= BUFFER_CANAL1_MO) total_error_sw_fixed(22);
  
  Canal1_MO_Transmit[index++] = sum;
  Canal1_MO_Transmit[index++] = STOP_BYTE_MO;
  
  //������� ��, �� ��������, �� ��������� ���� ���������
  USART_ClearFlag(CANAL1_MO, USART_FLAG_TC);

  //��������� ���� DMA ���� �� ���������
  if ((DMA_StreamCANAL1_MO_Tx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamCANAL1_MO_Tx->CR &= ~(uint32_t)DMA_SxCR_EN;
  DMA_StreamCANAL1_MO_Tx->NDTR = index;
  //���������� �������� ����� DMA
  if ((CANAL1_MO->CR3 & USART_DMAReq_Tx) == 0) CANAL1_MO->CR3 |= USART_DMAReq_Tx;

  //������� ���������, �� �������� ��� ���������� �������� ����� ��� DMA1 �� ������ CANAL1_MO_TX
  DMA_ClearFlag(DMA_StreamCANAL1_MO_Tx, DMA_FLAG_TCCANAL1_MO_Tx | DMA_FLAG_HTCANAL1_MO_Tx | DMA_FLAG_TEICANAL1_MO_Tx | DMA_FLAG_DMEICANAL1_MO_Tx | DMA_FLAG_FEICANAL1_MO_Tx);
  //��������� ��������
  DMA_StreamCANAL1_MO_Tx->CR |= (uint32_t)(DMA_SxCR_EN/* | DMA_IT_TC*/);
  
//  for (size_t i = 0; i < index; i++)
//  {
//    test_Canal1_MO_Transmit[test][i] = Canal1_MO_Transmit[i];
//  }
//  test_index[test] = index;
//  if (++test >= 5) test = 0;
}
/***********************************************************************************/

/***********************************************************************************
������ �������-�������� ����� ����� ��������� CANAL2_MO
***********************************************************************************/
void CANAL2_MO_routine()
{
  typedef enum _CANAL2_MO_states
  {
    CANAL2_MO_FREE = 0,
    CANAL2_MO_SENDING,
    CANAL2_MO_RECEIVING,
    CANAL2_MO_RECEIVED,
    CANAL2_MO_ERROR,
    CANAL2_MO_BREAK_LAST_ACTION
  } __CANAL2_MO_states;
  
  static __CANAL2_MO_states CANAL2_MO_state;

  queue_mo &= (uint32_t)(~QUEUQ_MO_IRQ);
  if (!_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_RESTART_KP))
  {
    //���� ������� ������� ������������� ��
    queue_mo |= queue_mo_irq;
  }
  else
  {
    if (
        (queue_mo == MASKA_FOR_BIT(STATE_QUEUE_MO_RESTART_KP)) &&
        (CANAL2_MO_state == CANAL2_MO_FREE)
       )
    {
      restart_KP_irq = 5;
    }
  }
  
  static uint32_t tick;
  static uint32_t rx_ndtr;
  static uint32_t packet_number;
  
  uint8_t sum = 0;
  uint32_t index_w = 0;

  static uint32_t delta_max;
      
  
  if (CANAL2_MO_state == CANAL2_MO_BREAK_LAST_ACTION)
  {
           Canal2_MO_Transmit[index_w++] = START_BYTE_MO;
    sum += Canal2_MO_Transmit[index_w++] = IEC_board_address;
    sum += Canal2_MO_Transmit[index_w++] = my_address_mo;
  
    sum += Canal2_MO_Transmit[index_w++] = BREAK_LAST_ACTION;

    _SET_STATE(queue_mo, STATE_QUEUE_MO_BREAK_LAST_ACTION_IN_IEC);
  }  
  else if (CANAL2_MO_state == CANAL2_MO_FREE)
  {
    //�� ����� ������ �� ��� ����������� ����� �� ������ 2
    if (!_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_TRANSACTION_PROGRESS_IN_IEC))
    {
      if (Canal1 == true)
      {
        if (_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_ASK_BASIC_SETTINGS))
        {
                 Canal2_MO_Transmit[index_w++] = START_BYTE_MO;
          sum += Canal2_MO_Transmit[index_w++] = IEC_board_address;
          sum += Canal2_MO_Transmit[index_w++] = my_address_mo;
  
          sum += Canal2_MO_Transmit[index_w++] = SENDING_BASIC_SETTINGS;
          
          sum += Canal2_MO_Transmit[index_w++] = VERSIA_PZ;
          sum += Canal2_MO_Transmit[index_w++] = MODYFIKACIA_VERSII_PZ;
          sum += Canal2_MO_Transmit[index_w++] = ZBIRKA_VERSII_PZ;
          sum += Canal2_MO_Transmit[index_w++] = ZBIRKA_PIDVERSII_PZ;

          sum += Canal2_MO_Transmit[index_w++] = serial_number_dev & 0xff;
          sum += Canal2_MO_Transmit[index_w++] = (serial_number_dev >> 8) & 0xff;
          
          sum += Canal2_MO_Transmit[index_w++] = current_settings.IP4[0] & 0xff;
          sum += Canal2_MO_Transmit[index_w++] = current_settings.IP4[1] & 0xff;
          sum += Canal2_MO_Transmit[index_w++] = current_settings.IP4[2] & 0xff;
          sum += Canal2_MO_Transmit[index_w++] = current_settings.IP4[3] & 0xff;
        
          sum += Canal2_MO_Transmit[index_w++] = current_settings.mask;

          sum += Canal2_MO_Transmit[index_w++] = current_settings.gateway[0] & 0xff;
          sum += Canal2_MO_Transmit[index_w++] = current_settings.gateway[1] & 0xff;
          sum += Canal2_MO_Transmit[index_w++] = current_settings.gateway[2] & 0xff;
          sum += Canal2_MO_Transmit[index_w++] = current_settings.gateway[3] & 0xff;
        
          sum += Canal2_MO_Transmit[index_w++] = current_settings.IP_time_server[0] & 0xff;
          sum += Canal2_MO_Transmit[index_w++] = current_settings.IP_time_server[1] & 0xff;
          sum += Canal2_MO_Transmit[index_w++] = current_settings.IP_time_server[2] & 0xff;
          sum += Canal2_MO_Transmit[index_w++] = current_settings.IP_time_server[3] & 0xff;

          unsigned int port_time_server = current_settings.port_time_server;
          sum += Canal2_MO_Transmit[index_w++] = port_time_server        & 0xff;
          sum += Canal2_MO_Transmit[index_w++] = (port_time_server >> 8) & 0xff;
          
          unsigned int period_sync = current_settings.period_sync;
          sum += Canal2_MO_Transmit[index_w++] = period_sync         & 0xff;
          sum += Canal2_MO_Transmit[index_w++] = (period_sync >>  8) & 0xff;
          sum += Canal2_MO_Transmit[index_w++] = (period_sync >> 16) & 0xff;
          sum += Canal2_MO_Transmit[index_w++] = (period_sync >> 24) & 0xff;
          
          unsigned int period = TIM2_CCR1_VAL*60/*Prescaler*//60/*������ ������� ������� � ���*/; /*��������� � ���*/
          sum += Canal2_MO_Transmit[index_w++] = period        & 0xff;
          sum += Canal2_MO_Transmit[index_w++] = (period >> 8) & 0xff;
        
          _SET_STATE(queue_mo, STATE_QUEUE_MO_TRANSMITING_BASIC_SETTINGS);
        } 
        else if (_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_ASK_MAKING_MEMORY_BLOCK))
        {
                 Canal2_MO_Transmit[index_w++] = START_BYTE_MO;
          sum += Canal2_MO_Transmit[index_w++] = IEC_board_address;
          sum += Canal2_MO_Transmit[index_w++] = my_address_mo;
  
          sum += Canal2_MO_Transmit[index_w++] = MAKING_NEW_BLOCKS;
          sum += Canal2_MO_Transmit[index_w++] = 1; /*LSB: �������� ������� �����, �� ����� ��������*/
          sum += Canal2_MO_Transmit[index_w++] = 0; /*MSB: �������� ������� �����, �� ����� ��������*/
        
          packet_number = 0; /*����� ������*/
          sum += Canal2_MO_Transmit[index_w++] = packet_number & 0xff; /*LSB: ����� ������*/
          sum += Canal2_MO_Transmit[index_w++] = (packet_number >> 8) & 0xff; /*MSB: ����� ������*/
  
          sum += Canal2_MO_Transmit[index_w++] = START_LABEL_NEW_BLOCK; /*������� ������� ���������� �� ������������ �����*/
          sum += Canal2_MO_Transmit[index_w++] = 0; /*ID ������������ �����*/

          sum += Canal2_MO_Transmit[index_w++] = 0; /*��� �������� ����� ��� ������������ �������*/
          sum += Canal2_MO_Transmit[index_w++] = 1; /*ʳ������ �����*/

          sum += Canal2_MO_Transmit[index_w++] = SIZE_SENDING_DATA_TM        & 0xff; /*LSB: ����� ������ �� ������ ����������� ����� � �� � ��*/
          sum += Canal2_MO_Transmit[index_w++] = (SIZE_SENDING_DATA_TM >> 8) & 0xff; /*MSB: ����� ������ �� ������ ����������� ����� � �� � ��*/

          sum += Canal2_MO_Transmit[index_w++] = SIZE_RECEIVING_DATA_TM        & 0xff; /*LSB: ����� ������ �� �������� ����������� ����� � �� � ��*/
          sum += Canal2_MO_Transmit[index_w++] = (SIZE_RECEIVING_DATA_TM >> 8) & 0xff; /*MSB: ����� ������ �� �������� ����������� ����� � �� � ��*/

          sum += Canal2_MO_Transmit[index_w++] = SIZE_RECEIVING_ACT_DATA_TM        & 0xff; /*LSB: ����� ������ �� �������� �������� ��������� ����������� ����� � �� � ��*/
          sum += Canal2_MO_Transmit[index_w++] = (SIZE_RECEIVING_ACT_DATA_TM >> 8) & 0xff; /*MSB: ����� ������ �� �������� �������� ��������� ����������� ����� � �� � ��*/

          sum += Canal2_MO_Transmit[index_w++] = SIZE_DESCRIPTION_DATA_TM         & 0xff; /*LSW->LSB: ����� ������ ������� ������� ����������� �����*/
          sum += Canal2_MO_Transmit[index_w++] = (SIZE_DESCRIPTION_DATA_TM >>  8) & 0xff; /*LSW->MSB: ����� ������ ������� ������� ����������� �����*/
          sum += Canal2_MO_Transmit[index_w++] = (SIZE_DESCRIPTION_DATA_TM >> 16) & 0xff; /*MSW->LSB: ����� ������ ������� ������� ����������� �����*/
          sum += Canal2_MO_Transmit[index_w++] = (SIZE_DESCRIPTION_DATA_TM >> 24) & 0xff; /*MSW->MSB: ����� ������ ������� ������� ����������� �����*/

          sum += Canal2_MO_Transmit[index_w++] = false; /*�� ���� ����������� ����������� �����������*/
        
          _SET_STATE(queue_mo, STATE_QUEUE_MO_TRANSMITING_MAKING_MEMORY_BLOCK);
        }
        else if (_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_ASK_SENDING_SETTING_NETWORK_LAYER))
        {
                 Canal2_MO_Transmit[index_w++] = START_BYTE_MO;
          sum += Canal2_MO_Transmit[index_w++] = IEC_board_address;
          sum += Canal2_MO_Transmit[index_w++] = my_address_mo;
  
          sum += Canal2_MO_Transmit[index_w++] = REQUEST_SETTINGS_NETWORK_LAYER;
        
          _SET_STATE(queue_mo, STATE_QUEUE_MO_RECEIVING_SETTING_NETWORK_LAYER);
        }
        else if (_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_ASK_NEW_MODBUS_TCP_REQ))
        {
                 Canal2_MO_Transmit[index_w++] = START_BYTE_MO;
          sum += Canal2_MO_Transmit[index_w++] = IEC_board_address;
          sum += Canal2_MO_Transmit[index_w++] = my_address_mo;
  
          sum += Canal2_MO_Transmit[index_w++] = REQUEST_MODBUS_TCP_REQ;
        
          _SET_STATE(queue_mo, STATE_QUEUE_MO_RECEIVING_NEW_MODBUS_TCP_REQ);
        }
        else if (_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_SEND_MODBUS_TCP_RESP))
        {
          _CLEAR_STATE(queue_mo, STATE_QUEUE_MO_SEND_MODBUS_TCP_RESP);

          if ((LAN_transmiting_count > 0) && (LAN_transmiting_count < (BUFFER_LAN - 2)))
          {
            unsigned int length = LAN_transmiting_count;
            
                   Canal2_MO_Transmit[index_w++] = START_BYTE_MO;
            sum += Canal2_MO_Transmit[index_w++] = IEC_board_address;
            sum += Canal2_MO_Transmit[index_w++] = my_address_mo;
  
            sum += Canal2_MO_Transmit[index_w++] = SENDIND_MODBUS_TCP_RESP;
        
            sum += Canal2_MO_Transmit[index_w++] = length;
            for (size_t i = 0; i < length; i++) sum += Canal2_MO_Transmit[index_w++] = LAN_transmiting[i];
            
            _SET_STATE(queue_mo, STATE_QUEUE_MO_TRANSMITING_MODBUS_TCP_RESP);
          }
        }
      }
    }
    else
    {
      uint32_t tick_tmp = TIM4->CNT;
      uint32_t delta;
      
      if (tick_tmp >= tick) delta = tick_tmp - tick;
      else delta = (0x10000 - tick) + tick_tmp; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
      
//      if (delta > 1000 /*1000x10��� = 10000��� = 10��*/) CANAL2_MO_state = CANAL2_MO_BREAK_LAST_ACTION;
      if (delta > 50000 /*50000x10��� = 500000��� = 500��*/) CANAL2_MO_state = CANAL2_MO_BREAK_LAST_ACTION;
      
      if (delta_max < delta) delta_max = delta;
    }
  }
  else if (CANAL2_MO_state == CANAL2_MO_SENDING)
  {
    if (DMA_StreamCANAL2_MO_Tx->NDTR == 0) 
    {
      CANAL2_MO_state = CANAL2_MO_RECEIVING;
      tick = TIM4->CNT;
      rx_ndtr = DMA_StreamCANAL2_MO_Rx->NDTR;
    }
  }
  else if (CANAL2_MO_state == CANAL2_MO_RECEIVING)
  {
    uint32_t rx_ndtr_tmp = DMA_StreamCANAL2_MO_Rx->NDTR;
    if (rx_ndtr_tmp != rx_ndtr)
    {
      rx_ndtr = rx_ndtr_tmp;
    }
    else
    {
      uint32_t tick_tmp = TIM4->CNT;
      uint32_t delta;
      if (tick_tmp >= tick) delta = tick_tmp - tick;
      else delta = (0x10000 - tick) + tick_tmp; //0x10000 - �� ������ ����� �������, �� �� �������� ���� ���������� �������� [0; 65535]
      
      if (rx_ndtr == BUFFER_CANAL2_MO)
      {
        //�� �������� ������� �����
//        if (delta > 1000 /*1000x10��� = 10000��� = 10��*/) CANAL2_MO_state = CANAL2_MO_ERROR;
        if (delta > 50000 /*50000x10��� = 500000��� = 500��*/) CANAL2_MO_state = CANAL2_MO_ERROR;
      
        if (delta_max < delta) delta_max = delta;
      }
      else
      {
        //� ������� �����
        if (delta > 1 /*10��� = 10���*/) CANAL2_MO_state = CANAL2_MO_RECEIVED;
      }
      
      //������ �������� ������
      if (
          (CANAL2_MO_state == CANAL2_MO_RECEIVED) ||
          (CANAL2_MO_state == CANAL2_MO_ERROR)  
         )
      {
        //���������� ������� ������������ ��� ������� ������� ������ 2, �� ���� ������ ����������
        clear_diagnostyka[0] |= WORD_0_MASKA_RECEIVING_ERRORS_CANAL_2;
        clear_diagnostyka[1] |= WORD_1_MASKA_RECEIVING_ERRORS_CANAL_2;
        clear_diagnostyka[2] |= WORD_2_MASKA_RECEIVING_ERRORS_CANAL_2;
        clear_diagnostyka[3] |= WORD_3_MASKA_RECEIVING_ERRORS_CANAL_2;

        int32_t size_packet = BUFFER_CANAL2_MO - rx_ndtr;
        if(size_packet != 0)
        {
          uint32_t error_status = CANAL2_MO->SR &  (USART_FLAG_ORE | USART_FLAG_NE | USART_FLAG_FE | USART_FLAG_PE);
    
          //������� ���� � ������������� ����� �� ������ 1
          if (
              (error_status == 0) &&
              (size_packet >= 3) &&
              (Canal2_MO_Received[0] == START_BYTE_MO) && 
              (Canal2_MO_Received[size_packet - 1] == STOP_BYTE_MO)  
            )   
          {
            if ((Canal2_MO_Received[1] == my_address_mo))
            {
              //���������� ���������� ����
              sum = 0;
              for (int32_t i = 0; i < (size_packet - 3); i++) sum += Canal2_MO_Received[1 + i];
              if (sum == Canal2_MO_Received[size_packet - 2])
              { 
                if (
                    !(
                      ((_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_BREAK_LAST_ACTION_IN_IEC       )) && (Canal2_MO_Received[3] == CONFIRM_BREAKING_LAST_ACTION  )       ) ||
                      ((_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_TRANSMITING_MAKING_MEMORY_BLOCK)) && (Canal2_MO_Received[3] == ANSWER_FOR_MAKING_NEW_BLOCKS  )       ) ||
                      ((_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_TRANSMITING_BASIC_SETTINGS     )) && (Canal2_MO_Received[3] == ANY_CONFIRMATION              )       ) ||
                      ((_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_RECEIVING_SETTING_NETWORK_LAYER)) && (
                                                                                                         (Canal2_MO_Received[3] == SENDING_SETTINGS_NETWORK_LAYER) ||
                                                                                                         (Canal2_MO_Received[3] == ANY_CONFIRMATION              )
                                                                                                        )                                                               ) ||
                      ((_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_RECEIVING_NEW_MODBUS_TCP_REQ  )) && (
                                                                                                         (Canal2_MO_Received[3] == SENDING_MODBUS_TCP_REQ) ||
                                                                                                         (Canal2_MO_Received[3] == ANY_CONFIRMATION      )
                                                                                                        )                                                               ) ||
                      ((_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_TRANSMITING_MODBUS_TCP_RESP    )) && (Canal2_MO_Received[3] == ANY_CONFIRMATION              )       )
                     )   
                   )
                {
                  _SET_BIT(set_diagnostyka, ERROR_CPU_ANSWER_CANAL_2);
                  CANAL2_MO_state = CANAL2_MO_ERROR;
                }
              }
              else 
              {
                _SET_BIT(set_diagnostyka, ERROR_CPU_RECEIVED_PACKET_CANAL_2);
              }
            }
          }
          else 
          {
            _SET_BIT(set_diagnostyka, ERROR_CPU_RECEIVING_CANAL_2);
            CANAL2_MO_state = CANAL2_MO_ERROR;
          }
        }
        else 
        {
          _SET_BIT(set_diagnostyka, ERROR_CPU_NO_ANSWER_CANAL_2);
          CANAL2_MO_state = CANAL2_MO_ERROR;
        }
      }
    }
  }
  
  if (
      (CANAL2_MO_state == CANAL2_MO_RECEIVED) ||
      (CANAL2_MO_state == CANAL2_MO_ERROR)  
     )   
  {
    if (CANAL2_MO_state == CANAL2_MO_RECEIVED)
    {
      sum = 0;
  
             Canal2_MO_Transmit[index_w++] = START_BYTE_MO;
      sum += Canal2_MO_Transmit[index_w++] = IEC_board_address;
      sum += Canal2_MO_Transmit[index_w++] = my_address_mo;
  
      if (_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_BREAK_LAST_ACTION_IN_IEC)) 
      {
        index_w = 0;
        _CLEAR_STATE(queue_mo, STATE_QUEUE_MO_BREAK_LAST_ACTION_IN_IEC);

        CANAL2_MO_state = CANAL2_MO_FREE;
        Canal2 = true;
      }
      else if (
               (_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_TRANSMITING_BASIC_SETTINGS)) ||
               (_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_TRANSMITING_MODBUS_TCP_RESP))
              )   
      {
        index_w = 0;
        if (_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_TRANSMITING_BASIC_SETTINGS)) _CLEAR_STATE(queue_mo, STATE_QUEUE_MO_TRANSMITING_BASIC_SETTINGS);
        else  
        {
          LAN_transmiting_count = 0; //�� � ������� ����, �� �����-������� ������ ��������
          _CLEAR_STATE(queue_mo, STATE_QUEUE_MO_TRANSMITING_MODBUS_TCP_RESP);
        }
        
        if (Canal2_MO_Received[4] == true)
        {
          CANAL2_MO_state = CANAL2_MO_FREE;
          Canal2 = true;
        }
        else
        {
          CANAL2_MO_state = CANAL2_MO_ERROR;
        }
      }
      else if (_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_TRANSMITING_MAKING_MEMORY_BLOCK)) 
      {
        index_w = 0;
        state_array_control_state = Canal2_MO_Received[4] | (Canal2_MO_Received[5] << 8);
        _CLEAR_STATE(queue_mo, STATE_QUEUE_MO_TRANSMITING_MAKING_MEMORY_BLOCK);
        
        if (
            ((state_array_control_state & (MASKA_FOR_BIT(ACS_MADE) | MASKA_FOR_BIT(ACS_ALL_BLOCKS_CREATED))) == (MASKA_FOR_BIT(ACS_MADE) | MASKA_FOR_BIT(ACS_ALL_BLOCKS_CREATED))) &&
            ((Canal2_MO_Received[6] | (Canal2_MO_Received[7] << 8)) == 0)
           )   
        {
          CANAL2_MO_state = CANAL2_MO_FREE;
          Canal2 = true;
        }
        else
        {
          CANAL2_MO_state = CANAL2_MO_ERROR;
        }
      }
      else if (_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_RECEIVING_SETTING_NETWORK_LAYER)) 
      {
        if (Canal2_MO_Received[3] == SENDING_SETTINGS_NETWORK_LAYER)
        {
          //�������� ������������ ���������� ���� Ethernet
          uint16_t IPv4_tmp[4] = {Canal2_MO_Received[4], Canal2_MO_Received[5], Canal2_MO_Received[6], Canal2_MO_Received[7]};
          uint32_t mask_tmp = Canal2_MO_Received[8];
          uint16_t gateway_tmp[4] = {Canal2_MO_Received[9], Canal2_MO_Received[10], Canal2_MO_Received[11], Canal2_MO_Received[12]};
          if (
              (current_settings.IP4[0] != IPv4_tmp[0]) ||
              (current_settings.IP4[1] != IPv4_tmp[1]) ||
              (current_settings.IP4[2] != IPv4_tmp[2]) ||
              (current_settings.IP4[3] != IPv4_tmp[3]) ||
              (current_settings.mask != mask_tmp) ||
              (current_settings.gateway[0] != gateway_tmp[0]) ||
              (current_settings.gateway[1] != gateway_tmp[1]) ||
              (current_settings.gateway[2] != gateway_tmp[2]) ||
              (current_settings.gateway[3] != gateway_tmp[3])
             )
          {
            //�������, �� ���� ��������� ����� ���� ������
            changed_settings = CHANGED_ETAP_EXECUTION;
            
            current_settings.IP4[0] = IPv4_tmp[0];
            current_settings.IP4[1] = IPv4_tmp[1];
            current_settings.IP4[2] = IPv4_tmp[2];
            current_settings.IP4[3] = IPv4_tmp[3];
            current_settings.mask = mask_tmp;
            current_settings.gateway[0] = gateway_tmp[0];
            current_settings.gateway[1] = gateway_tmp[1];
            current_settings.gateway[2] = gateway_tmp[2];
            current_settings.gateway[3] = gateway_tmp[3];

            //������� ����� � ������� ��������� ��� ���� ������������ � ��������� ����� � EEPROM ����� ���������
            fix_change_settings(0, 4);

            //����������� �������, �� �� ������ ����� �������� ����������
            new_state_keyboard |= (1<<BIT_REWRITE);
          }
          
          //³�������� ������������ ��������� ����������� ���������� ���� Ethernet
          sum += Canal2_MO_Transmit[index_w++] = CONFIRM_RECEIVING_SETTINGS_NETWORK_LAYER;
          sum += Canal2_MO_Transmit[index_w++] = true;
        }
        else 
        {
          index_w = 0;
          _CLEAR_STATE(queue_mo, STATE_QUEUE_MO_RECEIVING_SETTING_NETWORK_LAYER);
          
          if (
              (Canal2_MO_Received[3] == ANY_CONFIRMATION) &&
              (Canal2_MO_Received[4] == true)
             )
          {
            CANAL2_MO_state = CANAL2_MO_FREE;
            Canal2 = true;
          }
          else
          {
            CANAL2_MO_state = CANAL2_MO_ERROR;
          }
        }
      }
      else if (_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_RECEIVING_NEW_MODBUS_TCP_REQ)) 
      {
        if (Canal2_MO_Received[3] == SENDING_MODBUS_TCP_REQ)
        {
          //�������� �����-����� Modbus-TCP � ��
          LAN_received_count = Canal2_MO_Received[4];
          unsigned int answer;
          if ((LAN_received_count >= 0) && (LAN_received_count < BUFFER_LAN))
          {
            for (intptr_t i = 0; i < LAN_received_count; i++) LAN_received[i] = Canal2_MO_Received[5 + i];
            answer = true;
          }
          else answer = false;
          
          //³�������� ������������ ��������� ����������� ���������� ���� Ethernet
          sum += Canal2_MO_Transmit[index_w++] = CONFIRM_RECEIVING_MODBUS_TCP_REQ;
          sum += Canal2_MO_Transmit[index_w++] = answer;
        }
        else 
        {
          index_w = 0;
          _CLEAR_STATE(queue_mo, STATE_QUEUE_MO_RECEIVING_NEW_MODBUS_TCP_REQ);
          
          if (
              (Canal2_MO_Received[3] == ANY_CONFIRMATION) &&
              (Canal2_MO_Received[4] == true)
             )
          {
            CANAL2_MO_state = CANAL2_MO_FREE;
            Canal2 = true;
          }
          else
          {
            CANAL2_MO_state = CANAL2_MO_ERROR;
          }
        }
      }
    }
    else if (CANAL2_MO_state == CANAL2_MO_ERROR)
    {
      CANAL2_MO_state = CANAL2_MO_BREAK_LAST_ACTION;
      if (_GET_OUTPUT_STATE(queue_mo, STATE_QUEUE_MO_TRANSMITING_MODBUS_TCP_RESP)) 
      {
        _CLEAR_STATE(queue_mo, STATE_QUEUE_MO_TRANSMITING_MODBUS_TCP_RESP);
        _SET_STATE(queue_mo, STATE_QUEUE_MO_SEND_MODBUS_TCP_RESP);
      }
    }
  
    tick = TIM4->CNT; /*���� ��������� ���� ���� ��������� ������� ��������� �������� � �������� ��� ��� ��*/
  }
  
  if (index_w != 0)
  {
    CANAL2_MO_state = CANAL2_MO_SENDING;

    //����������������� ���� � ���� ����������������
    Canal2_MO_Transmit[index_w++] = sum;
    Canal2_MO_Transmit[index_w++] = STOP_BYTE_MO;
  
    /*
    ϳ����������� ����� �� ��������� �����
    */
    //��������� ����� ���������
    if ((DMA_StreamCANAL2_MO_Rx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamCANAL2_MO_Rx->CR &= ~(uint32_t)DMA_SxCR_EN;  
      
    //������� �� ������ �������
    CANAL2_MO->SR;
    (unsigned short int)(CANAL2_MO->DR & (uint16_t)0x01FF);
    CANAL2_MO->SR = (uint16_t)(~(uint32_t)USART_FLAG_LBD);
      
    // ������� ���������, �� �������� ��� ���������� �������� ����� ��� DMA 
    DMA_ClearFlag(DMA_StreamCANAL2_MO_Rx, DMA_FLAG_TCCANAL2_MO_Rx | DMA_FLAG_HTCANAL2_MO_Rx | DMA_FLAG_TEICANAL2_MO_Rx | DMA_FLAG_DMEICANAL2_MO_Rx | DMA_FLAG_FEICANAL2_MO_Rx);

    DMA_StreamCANAL2_MO_Rx->NDTR = BUFFER_CANAL2_MO;
    //��������� ���������� �������
    DMA_StreamCANAL2_MO_Rx->CR |= (uint32_t)DMA_SxCR_EN;
    /***/

    /*
    �������� ���������� ����
    */
    //������� ��, �� ��������, �� ��������� ���� ���������
    USART_ClearFlag(CANAL2_MO, USART_FLAG_TC);

    //��������� ���� DMA ���� �� ���������
    if ((DMA_StreamCANAL2_MO_Tx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamCANAL2_MO_Tx->CR &= ~(uint32_t)DMA_SxCR_EN;
    DMA_StreamCANAL2_MO_Tx->NDTR = index_w;
    //���������� �������� ����� DMA
    if ((CANAL2_MO->CR3 & USART_DMAReq_Tx) == 0) USART2->CR3 |= USART_DMAReq_Tx;

    //������� ���������, �� �������� ��� ���������� �������� ����� ��� DMA1 �� ������ CANAL1_MO_TX
    DMA_ClearFlag(DMA_StreamCANAL2_MO_Tx, DMA_FLAG_TCCANAL2_MO_Tx | DMA_FLAG_HTCANAL2_MO_Tx | DMA_FLAG_TEICANAL2_MO_Tx | DMA_FLAG_DMEICANAL2_MO_Tx | DMA_FLAG_FEICANAL2_MO_Tx);
    //��������� ��������
    DMA_StreamCANAL2_MO_Tx->CR |= (uint32_t)DMA_SxCR_EN;
    /***/
  }
}
/***********************************************************************************/
