#include "header.h"

/*****************************************************/
//������� ����� ����������� ���������� �� ���� ����������� ������������ � ���� ����� ���'��
/*****************************************************/
void make_ekran_info()
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_INFO][MAX_COL_LCD] = 
  {
    {
      "   ������ ��    ",
      "   ������ ��    ",
      " �������� ����� "
#if (MODYFIKACIA_VERSII_PZ >= 10)
                        ,
      "   MAC-�����    "
#endif
    },
    {
      "   ����� ��    ",
      "   ����� ��    ",
      " ������� ����� "
#if (MODYFIKACIA_VERSII_PZ >= 10)
                        ,
      "   MAC-������   "
#endif
    },
    {
      "   VER.of F/W   ",
      "   VER.of MM    ",
      " Serial number  "
#if (MODYFIKACIA_VERSII_PZ >= 10)
                        ,
      "  MAC address   "
#endif
    },
    {
      "   ������ ��    ",
      "   ������ ��    ",
      " �������� ����� "
#if (MODYFIKACIA_VERSII_PZ >= 10)
                        ,
      "   MAC-�����    "
#endif
    }
  };
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  unsigned char value_str[MAX_COL_LCD];
  
  //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  int first_char_row1, last_chat_row1;
  
  for (unsigned int i = 0; i< MAX_ROW_LCD; i++)
  {
    if (index_of_ekran < (MAX_ROW_FOR_INFO<<1))//�������� �� ��� ��������� MAX_ROW_FOR_INFO ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
    {
      if ((i & 0x1) == 0)
      {
        //� ��������� ����� ����� �������� ���������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) 
        {
          working_ekran[i][j] = name_string[index_language][index_of_ekran>>1][j];
          value_str[j] = ' ';
        }
        
        if ((index_of_ekran>>1) == INDEX_ML_INFO_FIRMWARE)
        {
          unsigned int index_tmp = 0;

#if VERSIA_PZ > 9
          value_str[index_tmp++] = (VERSIA_PZ / 10) + 0x30;
          value_str[index_tmp++] = (VERSIA_PZ % 10) + 0x30;
#else
          value_str[index_tmp++] = VERSIA_PZ + 0x30;
#endif

          value_str[index_tmp++] = '.';
          
#if MODYFIKACIA_VERSII_PZ > 9
          value_str[index_tmp++] = (MODYFIKACIA_VERSII_PZ / 10) + 0x30;
          value_str[index_tmp++] = (MODYFIKACIA_VERSII_PZ % 10) + 0x30;
#else
          value_str[index_tmp++] = MODYFIKACIA_VERSII_PZ + 0x30;
#endif

          value_str[index_tmp++] = '.';
          
#if ZBIRKA_VERSII_PZ > 9
          value_str[index_tmp++] = (ZBIRKA_VERSII_PZ / 10) + 0x30;
          value_str[index_tmp++] = (ZBIRKA_VERSII_PZ % 10) + 0x30;
#else
          value_str[index_tmp++] = ZBIRKA_VERSII_PZ + 0x30;
#endif

          value_str[index_tmp++] = '.';
          
#if ZBIRKA_PIDVERSII_PZ > 9
          value_str[index_tmp++] = (ZBIRKA_PIDVERSII_PZ / 10) + 0x30;
          value_str[index_tmp++] = (ZBIRKA_PIDVERSII_PZ % 10) + 0x30;
#else
          value_str[index_tmp++] = ZBIRKA_PIDVERSII_PZ + 0x30;
#endif

          unsigned int shift = (MAX_COL_LCD - index_tmp) >> 1;
          first_char_row1 = shift;
          last_chat_row1 = first_char_row1 + index_tmp;
          index_tmp--;
          for (int k = index_tmp; k >= 0; k-- ) 
          {
            value_str[k + shift] = value_str[k];
            value_str[k] = ' ';
          }
          
        }
        else if ((index_of_ekran>>1) == INDEX_ML_INFO_MEMORY_MAP)
        {
#if VERSIA_GMM > 9
          value_str[COL_INFO_BEGIN_2 + 0] = (VERSIA_GMM / 10) + 0x30;
          value_str[COL_INFO_BEGIN_2 + 1] = (VERSIA_GMM % 10) + 0x30;
#else
          value_str[COL_INFO_BEGIN_2 + 0] = ' ';
          value_str[COL_INFO_BEGIN_2 + 1] = VERSIA_GMM + 0x30;
#endif

          value_str[COL_INFO_BEGIN_2 + 2] = '.';
          
#if MODYFIKACIA_VERSII_GMM > 9
          value_str[COL_INFO_BEGIN_2 + 3] = (MODYFIKACIA_VERSII_GMM / 10) + 0x30;
          value_str[COL_INFO_BEGIN_2 + 4] = (MODYFIKACIA_VERSII_GMM % 10) + 0x30;
#else
          value_str[COL_INFO_BEGIN_2 + 3] = MODYFIKACIA_VERSII_GMM + 0x30;
          value_str[COL_INFO_BEGIN_2 + 4] = ' ';
#endif
        }
        else if ((index_of_ekran>>1) == INDEX_ML_INFO_SERIAL_NUMBER)
        {
          uint32_t value = serial_number_dev;
          uint32_t value_tmp = value;
          uint32_t number_digits = 0;
          do
          {
            number_digits++;
            value_tmp /= 10;
          }
          while(value_tmp != 0);
          
          first_char_row1 = (MAX_COL_LCD - number_digits) >> 1;
          last_chat_row1 = first_char_row1 + number_digits;
          uint32_t index = last_chat_row1 - 1;
          for (uint32_t j = 0; j < number_digits; j++)
          {
            value_tmp = value % 10;
            value_str[index--] = value_tmp + 0x30;
            value /= 10;
          }
        }
#if (MODYFIKACIA_VERSII_PZ >= 10)
        else if ((index_of_ekran>>1) == INDEX_ML_INFO_MAC_ADDRESS)
        {
          uint16_t MAC_address_tmp[3] = {0x0080, 0xE100, serial_number_dev};
          const uint8_t string[] = "0123456789ABCDEF";
          
          value_str[5] = value_str[10] = ':';
          uint32_t index = 4;
          for (size_t k1 = 0; k1 < 3; k1++)
          {
            for (size_t k2 = 0; k2 < 4; k2++)
            {
              value_str[index--] = string[MAC_address_tmp[k1] & 0xf];
              MAC_address_tmp[k1] >>= 4;
            }
            index += (4 + 1 + 4);
          }
        }
#endif        
      }
      else
      {
        //� ������� ����� ����� �������� ��������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = value_str[j];
      }
    }
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }

  //³���������� ������ �� �������� � ������ ������ �� ���� � ��� �� ��������� ������
  current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
  int last_position_cursor_x = MAX_COL_LCD;

  //������ �� ���������� ������������ �� ������� ������ � �������, ���� �� �� � ����� �����������, ������ ������� ���� ��������� � ������ main_manu_function
  if (
      (current_ekran.index_position == INDEX_ML_INFO_FIRMWARE) ||
      (current_ekran.index_position == INDEX_ML_INFO_SERIAL_NUMBER)
     )  
  {
    current_ekran.position_cursor_x = first_char_row1;
    last_position_cursor_x = last_chat_row1;
  }
  else if (current_ekran.index_position == INDEX_ML_INFO_MEMORY_MAP)
  {
    current_ekran.position_cursor_x = COL_INFO_BEGIN_2;
    last_position_cursor_x = COL_END_END_2;
  }
  else 
  {
    current_ekran.position_cursor_x = 0;
    last_position_cursor_x = MAX_COL_LCD;
  }

  //ϳ������� ������ �� ������� �������
  while (((working_ekran[current_ekran.position_cursor_y][current_ekran.position_cursor_x + 1]) == ' ') && 
         (current_ekran.position_cursor_x < (last_position_cursor_x -1))) current_ekran.position_cursor_x++;

  //������ ������� ���, ��� �� ��� ����� ������
  if (((working_ekran[current_ekran.position_cursor_y][current_ekran.position_cursor_x]) != ' ') && 
      (current_ekran.position_cursor_x > 0)) current_ekran.position_cursor_x--;

  //������ �������
  current_ekran.cursor_on = 1;
  //������ �� ����
  if(current_ekran.edition == 0)current_ekran.cursor_blinking_on = 0;
  else current_ekran.cursor_blinking_on = 1;
  //�������� �������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� ��� ���� � ���� ��������
/*****************************************************/
void make_ekran_date_time_pz(void)
{
  unsigned char name_string[2*MAX_ROW_FOR_DATE_TIME_PZ][MAX_COL_LCD] = 
  {
    "   XX-XX-20XX   ",
    "     XX:XX      "
  };
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  
  index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  /******************************************/
  //���������� ���� ���������� �������
  /******************************************/
  //����
  name_string[0][3 ] = (DAY_VER >>  4) + 0x30;
  name_string[0][4 ] = (DAY_VER & 0xf) + 0x30;

  //̳����
  name_string[0][6 ] = (MONTH_VER >>  4) + 0x30;
  name_string[0][7 ] = (MONTH_VER & 0xf) + 0x30;

  //г�
  name_string[0][11] = (YEAR_VER >>  4) + 0x30;
  name_string[0][12] = (YEAR_VER & 0xf) + 0x30;

  //������
  name_string[1][5 ] = (HOUR_VER >>  4) + 0x30;
  name_string[1][6 ] = (HOUR_VER & 0xf) + 0x30;

  //�������
  name_string[1][8 ] = (MINUTE_VER >>  4) + 0x30;
  name_string[1][9 ] = (MINUTE_VER & 0xf) + 0x30;
  /******************************************/
  
  //�������  ����� � ������� �����
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    //�������� ����� ����� ���������, �� �� ����� ����������
    if (index_of_ekran < (2*MAX_ROW_FOR_DATE_TIME_PZ))
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_of_ekran][j];
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }

  //������ �� ���������� ������� �� ������ �������
  current_ekran.position_cursor_x = 0;
  //³���������� ������ �� �������� � 0
  current_ekran.position_cursor_y = 0;
  //������ �� �������
  current_ekran.cursor_on = 0;
  //������ �� ����
  current_ekran.cursor_blinking_on = 0;
  //�������� �������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
