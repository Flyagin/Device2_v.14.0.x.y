#include "header.h"

/*****************************************************/
//������� ����� ������ ��/����/�� ��� ����������
/* 
-------------------------------------------------------
������� ��������
0  - �����
1  - ������
2  - ��������
3  - ������������� �������
4  - ������������� ������
5  - ������������� ������
6  - ����������� "�"
7  - ����������� "���"
8  - ����������� "����.���"
9  - ����������� "��"
10 - ������������ �������
11 - ������� GOOSE ����
12 - ������� MMS ����
13 - �������� ��������� ����
-------------------------------------------------------
*/
/*****************************************************/
void make_ekran_chose_of_list_for_ranguvannja(__id_input_output type_of_window)
{
  const unsigned char information[MAX_NAMBER_LANGUAGE][_MAX_ID_INPUT_OUPUT][MAX_COL_LCD] = 
  {
    {
      " ���.           ",
      " ����.          ",
      " ��             ",
      " �-�������      ",
      " F              ",
      " �-�������      ",
      " �-�            ",
      " �-���          ",
      " �-����.���     ",
      " �-��           ",
      " ���.�.         "
#if (MODYFIKACIA_VERSII_PZ >= 10)
      ,
      " ��.GOOSE ����  ",
      " ��.MMS ����    ",
      " ���            "
#endif
    },
    {
      " ���.           ",
      " ����.          ",
      " ��             ",
      " �-�������      ",
      " F              ",
      " �-�����       ",
      " �-�            ",
      " �-���          ",
      " �-����.���     ",
      " �-��           ",
      " ���.�.         "
#if (MODYFIKACIA_VERSII_PZ >= 10)
      , 
      " ��.GOOSE ����  ",
      " ��.MMS ����    ", 
      " ���            "
#endif
    },
    {
      " BI.            ",
      " BO.            ",
      " LED            ",
      " UD-Function    ",
      " F              ",
      " UD-FF          ",
      " AND            ",
      " OR             ",
      " XOR            ",
      " NOT            ",
      " Transfer func  "
#if (MODYFIKACIA_VERSII_PZ >= 10)
      ,
      " GSERECEIVxx    ",
      " MMSRECEIVxx    ",
      " NETSENDxx      "
#endif
    },
    {
      " ���.           ",
      " ����.          ",
      " ��             ",
      " �-�������      ",
      " F              ",
      " �-�������      ",
      " �-�            ",
      " �-���          ",
      " �-����.���     ",
      " �-��           ",
      " ���.�.         "
#if (MODYFIKACIA_VERSII_PZ >= 10)
      ,
      " ��.GOOSE ����  ",
      " ��.MMS ����    ",
      " ���            "
#endif
    }
  };

  const unsigned int first_index_number[MAX_NAMBER_LANGUAGE][_MAX_ID_INPUT_OUPUT] = 
  {
    {5, 6, 3, 10, 2, 10, 4, 6, 11, 5, 7
#if (MODYFIKACIA_VERSII_PZ >= 10)
      , 14, 12, 4 
#endif
    },
    {5, 6, 3, 10, 2,  9, 4, 6, 11, 5, 7
#if (MODYFIKACIA_VERSII_PZ >= 10)
      , 14, 12, 4
#endif
    },
    {4, 4, 4, 12, 2, 13, 7, 6,  7, 6, 6
#if (MODYFIKACIA_VERSII_PZ >= 10)
      , 13, 13, 4
#endif
    },
    {5, 6, 3, 10, 2, 10, 4, 6, 11, 5, 7
#if (MODYFIKACIA_VERSII_PZ >= 10)
      , 14, 12, 4
#endif
    }
  };
  
  const unsigned int max_row[_MAX_ID_INPUT_OUPUT] =
  {
    MAX_ROW_LIST_INPUTS_FOR_RANGUVANNJA,
    MAX_ROW_LIST_OUTPUTS_FOR_RANGUVANNJA,
    MAX_ROW_LIST_LEDS_FOR_RANGUVANNJA,
    MAX_ROW_FOR_LIST_DF,
    MAX_ROW_LIST_BUTTONS_FOR_RANGUVANNJA,
    MAX_ROW_FOR_LIST_DT,
    MAX_ROW_FOR_LIST_D_AND,
    MAX_ROW_FOR_LIST_D_OR,
    MAX_ROW_FOR_LIST_D_XOR,
    MAX_ROW_FOR_LIST_D_NOT,
    MAX_ROW_FOR_LIST_TF
      
#if (MODYFIKACIA_VERSII_PZ >= 10)    
    ,
    N_IN_GOOSE,
    N_IN_MMS,
    N_OUT_LAN
#endif
  };
  
  int index_language = index_language_in_array(current_settings.language);
  unsigned int first_index_number_1 = first_index_number[index_language][type_of_window];
        
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  //������� �����  � ������� �����
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    unsigned int number = index_of_ekran + 1;
    int tmp_1 = -1, tmp_2 = -1;
    
    if (type_of_window == ID_INPUT)
    {
      for (size_t j = 0; j < N_INPUT_BOARDS; j++)
      {
        if (number <= input_boards[j][0])
        {
          tmp_1 = input_boards[j][1];
          tmp_2 = (j == 0) ? number : number - input_boards[j - 1][0];
          
          break;
        }
      }
    }
    else if (type_of_window == ID_OUTPUT)
    {
      for (size_t j = 0; j < N_OUTPUT_BOARDS; j++)
      {
        if (number <= output_boards[j][0])
        {
          tmp_1 = output_boards[j][1];
          tmp_2 = (j == 0) ? number : number - output_boards[j - 1][0];
          
          break;
        }
      }
    }
    else
    {
      tmp_1 = (number / 10);
      tmp_2 = number - tmp_1*10;
    }

    //�������� ����� ����� ���������, �� �� ����� ���������� � ������� �����������
    if (index_of_ekran < max_row[type_of_window])
    {
      for (unsigned int j = 0; j<MAX_COL_LCD; j++)
      {
        if ((j < first_index_number_1) || (j >= (first_index_number_1 + 3)))
           working_ekran[i][j] = information[index_language][type_of_window][j];
        else
        {
          if (j == (first_index_number_1 + 0))
          {
            if (tmp_1 < 0) working_ekran[i][j] = '?';
            else if (tmp_1 > 0 ) 
            {
              if (
                  (type_of_window != ID_INPUT) &&
                  (type_of_window != ID_OUTPUT)
                 )  
              {
                working_ekran[i][j] = tmp_1 + 0x30;
              }
              else
              {
                working_ekran[i][j] = tmp_1 + 0x40;
              }
            }
          }
          else if (
                   (j == (first_index_number_1 + 1)) &&
                   (
                    (type_of_window == ID_INPUT) ||
                    (type_of_window == ID_OUTPUT)
                   )   
                  )   
          {
            working_ekran[i][j] = '.';
          }
          else if (
                   (j == (first_index_number_1 + 1))
                   /*��������� �������� ��� ���������, �� ���� (j == (first_index_number_1 + 1)), �� type_of_window != ID_INPUT � ID_OUTPUT*/  
                   ||
                   (
                    (j == (first_index_number_1 + 2)) &&
                    (
                     (type_of_window == ID_INPUT) ||
                     (type_of_window == ID_OUTPUT)
                    )   
                   ) 
                  )   
          {
            if (
                (tmp_1 > 0) ||
                (tmp_1 < 0)  
               )   
            {
              if (tmp_2 < 0) working_ekran[i][j] = '?';
              else working_ekran[i][j] = tmp_2 + 0x30;
            }
            else
            {
              if (tmp_2 < 0) working_ekran[i][j] = '?';
              else
              {
                working_ekran[i][j - 1] = tmp_2 + 0x30;
                working_ekran[i][j] = ' ';
              }
            }
          }
          else working_ekran[i][j] = ' ';  
        }
      }
    }
    else
    {
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';
    }

    index_of_ekran++;
  }

  //������ �� ���������� ������������ �� ������ �������
  current_ekran.position_cursor_x = 0;
  //³���������� ������ �� ��������
  current_ekran.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
  //������ �������
  current_ekran.cursor_on = 1;
  //������ �� ����
  current_ekran.cursor_blinking_on = 0;
  //�������� �������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� ����������� ������� �� �������� ����
/*****************************************************/
void make_ekran_set_function_in_bi(unsigned int number_ekran, unsigned int type_ekran, uint32_t temp_state[]
#if (MODYFIKACIA_VERSII_PZ >= 10)
                                                                                                            , int type_LN, int n_LN
#endif
                                                                                                                          )
{
#define NUMBER_ROW_FOR_NOTHING_INFORMATION 2
  
#if (MODYFIKACIA_VERSII_PZ >= 10)
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_TOTAL_SIGNAL_FOR_RANG_SMALL + (1 - N_IN_GOOSE)  + (1 - N_IN_MMS) + (1 - N_OUT_LAN) + (1 - NUMBER_UP_SIGNAL_FOR_RANG_SMALL)][MAX_COL_LCD] = 
#else
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_TOTAL_SIGNAL_FOR_RANG_SMALL + (1 - NUMBER_UP_SIGNAL_FOR_RANG_SMALL)][MAX_COL_LCD] = 
#endif
  {
    {
      "      ���       ",
      "  ������������  ",
      NAME_RANG_SMALL_RU
    },
    {
      "      ����      ",
      "   ����������   ",
      NAME_RANG_SMALL_UA
    },
    {
      "       No       ",
      "  signal conf   ",
      NAME_RANG_SMALL_EN
    },
    {
      "      ���       ",
      "  ������������  ",
      NAME_RANG_SMALL_KZ
    }
  };
  
  const uint32_t index_number_UP_small[MAX_NAMBER_LANGUAGE][1] = 
  {
    {11}, 
    {11}, 
    {12}, 
    {11} 
  };
  
  unsigned char name_string_tmp[NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_TOTAL_SIGNAL_FOR_RANG_SMALL][MAX_COL_LCD];

  int index_language = index_language_in_array(current_settings.language);
  for(size_t index_1 = 0; index_1 < (NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_TOTAL_SIGNAL_FOR_RANG_SMALL); index_1++)
  {
    size_t index_row;
    if (index_1 < (NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL)) 
    {
#if (MODYFIKACIA_VERSII_PZ >= 10)
      if (index_1 < (NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL - (N_IN_GOOSE + N_IN_MMS + N_OUT_LAN))) 
      {
        index_row = index_1;
      }
      else if (index_1 < (NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL - (N_IN_MMS + N_OUT_LAN))) 
      {
        index_row = NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_SMALL_BLOCK_IN_GOOSE1 + ((index_1 - (NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL - (N_IN_GOOSE + N_IN_MMS + N_OUT_LAN))) % 1);
      }
      else if (index_1 < (NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL - (N_OUT_LAN))) 
      {
        index_row = NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_SMALL_BLOCK_IN_MMS1 + (1 - N_IN_GOOSE) + ((index_1 - (NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL - (N_IN_MMS + N_OUT_LAN))) % 1);
      }
      else
      {
        index_row = NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_SMALL_BLOCK_OUT_LAN1 + (1 - N_IN_GOOSE) + (1 - N_IN_MMS) + ((index_1 - (NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL - (N_OUT_LAN))) % 1);
      }
#else
      index_row = index_1;
#endif        
    }
    else if (index_1 < (NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_SMALL_BLOCK_UP1)) 
    {
      index_row = index_1
#if (MODYFIKACIA_VERSII_PZ >= 10)
                   + 1 - N_IN_GOOSE + 1 - N_IN_MMS + 1 - N_OUT_LAN
#endif        
                  ;
    }
    else if (index_1 < (NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_SMALL_BLOCK_UP1 + NUMBER_UP_SIGNAL_FOR_RANG_SMALL))
    {
      index_row = NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_SMALL_BLOCK_UP1
#if (MODYFIKACIA_VERSII_PZ >= 10)
                   + 1 - N_IN_GOOSE + 1 - N_IN_MMS + 1 - N_OUT_LAN
#endif
                   + ((index_1 - (NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_SMALL_BLOCK_UP1)) % 1);
    }
    else
    {
      index_row = index_1 
#if (MODYFIKACIA_VERSII_PZ >= 10)
                  + 1 - N_IN_GOOSE + 1 - N_IN_MMS + 1 - N_OUT_LAN
#endif        
                  + 1 - NUMBER_UP_SIGNAL_FOR_RANG_SMALL;
    }
      
    for(size_t index_2 = 0; index_2 < MAX_COL_LCD; index_2++)
    {
#if (MODYFIKACIA_VERSII_PZ >= 10)
      if (
          (index_1 >= (NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL - (N_IN_GOOSE + N_IN_MMS + N_OUT_LAN)))  &&
          (index_1 <  (NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL - (N_IN_MMS + N_OUT_LAN))) &&
          (index_2 >=  index_n_In_GOOSE[index_language][(index_1 - (NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_SMALL_BLOCK_IN_GOOSE1)) % 1]) &&
          (index_2 <= (index_n_In_GOOSE[index_language][(index_1 - (NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_SMALL_BLOCK_IN_GOOSE1)) % 1] + 1)) 
         )   
      {
        unsigned int n = index_1 - (NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_SMALL_BLOCK_IN_GOOSE1);
        if ((n + 1) < 10)
        {
          if (index_2 == index_n_In_GOOSE[index_language][n % 1])
            name_string_tmp[index_1][index_2] = 0x30 + (n + 1);
          else
            name_string_tmp[index_1][index_2] = ' ';
        }
        else
        {
          if (index_2 == index_n_In_GOOSE[index_language][n % 1])
            name_string_tmp[index_1][index_2] = 0x30 + (n / 1 + 1) / 10;
          else
            name_string_tmp[index_1][index_2] = 0x30 + (n / 1 + 1) % 10;
        }
      }
      else if (
               (index_1 >= (NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL - (N_IN_MMS + N_OUT_LAN)))  &&
               (index_1 <  (NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL - (N_OUT_LAN))) &&
               (index_2 == index_n_In_MMS[index_language][(index_1 - (NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_SMALL_BLOCK_IN_MMS1)) % 1]) 
              )   
      {
        name_string_tmp[index_1][index_2] = 0x30 + ((index_1 - (NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_SMALL_BLOCK_IN_MMS1)) / 1 + 1);
      }
      else if (
               (index_1 >= (NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL - (N_OUT_LAN)))  &&
               (index_1 <  (NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL)) &&
               (index_2 == index_n_Out_LAN[index_language][(index_1 - (NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_SMALL_BLOCK_OUT_LAN1)) % 1]) 
              )   
      {
        name_string_tmp[index_1][index_2] = 0x30 + ((index_1 - (NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_SMALL_BLOCK_OUT_LAN1)) / 1 + 1);
      }
      else 
#endif
      {
        if (
            (index_1 >= (NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_SMALL_BLOCK_UP1))  &&
            (index_1 <  (NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_SMALL_BLOCK_UP1 + NUMBER_UP_SIGNAL_FOR_RANG_SMALL)) &&
            (index_2 == index_number_UP_small[index_language][(index_1 - (NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_SMALL_BLOCK_UP1)) % 1]) 
           )   
        {
          name_string_tmp[index_1][index_2] = 0x30 + ((index_1 - (NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_SMALL_BLOCK_UP1)) / 1 + 1);
        }
        else name_string_tmp[index_1][index_2] = name_string[index_language][index_row][index_2];
      }
    }
  }
  
  if ((current_settings.control_zz & CTR_ZZ1_TYPE) != 0)
  {
    const unsigned char name_block_zz[MAX_NAMBER_LANGUAGE][MAX_COL_LCD] = 
    {
      "    ����.��     ",
      "    ����.��     ",
      "    SEFP Blk    ",
      "    ����.��     "
    };
    for (size_t index_1 = 0; index_1 < MAX_COL_LCD; index_1++)
    {
      name_string_tmp[NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_SMALL_BLOCK_NZZ][index_1] = name_block_zz[index_language][index_1];
    }
  }
  
  unsigned int state_viewing_input[N_SMALL];
  for (size_t i = 0; i < N_SMALL; i++ ) state_viewing_input[i] = temp_state[i];
  if(current_ekran.edition == 0)
  {
    //�������, ���� �� ������������� ���������� ������� �� ����
    if (
        (state_viewing_input[0] == 0) &&
        (state_viewing_input[1] == 0) &&
        (state_viewing_input[2] == 0)
       )
    {
      //�� ������, �� �� ����� ���� ������ �� �����������
      
      //������ ������� � ������ ���������� �� ��� �������
      current_ekran.index_position = 0;
      position_in_current_level_menu[number_ekran] = 0;

      //�������  ����� � ������� �����
      for (unsigned int i=0; i< MAX_ROW_LCD; i++)
      {
        //������� � ������� ����� ����������, �� ������ �� �����������
        if (i < NUMBER_ROW_FOR_NOTHING_INFORMATION)
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string_tmp[i][j];
        else
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';
      }

      //³���������� ������ �� ��������
      current_ekran.position_cursor_y = 0;
      //������ ���������
      current_ekran.cursor_on = 0;
    }
    else
    {
      /************************************************************/
      //������� ������ �� �������, �� ������� �����������
      /************************************************************/
      unsigned int position_temp = current_ekran.index_position;
      unsigned int index_of_ekran;
      unsigned int i = 0, offset = 0;
      unsigned int state_current_bit;

      while ((i + offset) < NUMBER_TOTAL_SIGNAL_FOR_RANG_SMALL)
      {
        state_current_bit = state_viewing_input[(i + offset)>>5] & (1<<((i + offset) & 0x1f));

        if (state_current_bit == 0)
        {
          for (unsigned int j = i; j < (NUMBER_TOTAL_SIGNAL_FOR_RANG_SMALL - offset); j++)
          {
            if ((j + 1) < (NUMBER_TOTAL_SIGNAL_FOR_RANG_SMALL - offset))
            {
              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION + 1][k];
            }
            else 
            {
              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = ' ';
            }
          }
          if (current_ekran.index_position >= ((int)(i + offset))) position_temp--;
          offset++;
        }
        else i++;
      }
      /************************************************************/

      index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
      
      //�������  ����� � ������� �����
      for (i=0; i< MAX_ROW_LCD; i++)
      {
        //�������� ����� ����� ���������, �� �� ����� ���������� � ������� ������������
        if (index_of_ekran < NUMBER_TOTAL_SIGNAL_FOR_RANG_SMALL)
        {
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string_tmp[index_of_ekran + NUMBER_ROW_FOR_NOTHING_INFORMATION][j];

          //ϳ������� �����, ��� �� ���� ������ ������ ������
          unsigned int iteration = 0;
          while (
                 (working_ekran[i][0] == ' ') &&
                 (working_ekran[i][1] == ' ') &&
                 (iteration < (MAX_COL_LCD - 1 - 1))
                )
          {
            for (unsigned int j = 1; j < MAX_COL_LCD; j++)
            {
              if ((j + 1) < MAX_COL_LCD)
                working_ekran[i][j] = working_ekran[i][j + 1];
              else
                working_ekran[i][j] = ' ';
            }
            iteration++;
          }
        }
        else
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

        index_of_ekran++;
      }
      //³���������� ������ �� ��������
      current_ekran.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
      //������ �������
      current_ekran.cursor_on = 1;
    }
    
    //������ �� ���������� ������������ �� ������ �������
    current_ekran.position_cursor_x = 0;
    //������ �� ����
    current_ekran.cursor_blinking_on = 0;
  }
  else
  {
    unsigned int position_temp = current_ekran.index_position;
    unsigned int index_of_ekran;
    unsigned int i, offset = 0;
    int min_max_number[TOTAL_NUMBER_PROTECTION][2] =
    {
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ04_SIGNAL_FOR_RANG_SMALL - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ04_SIGNAL_FOR_RANG_SMALL),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ04_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ04_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ04_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ04_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ04_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL + NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ04_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL + NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ04_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL + NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL + NUMBER_APV_SIGNAL_FOR_RANG_SMALL - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ04_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL + NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL + NUMBER_APV_SIGNAL_FOR_RANG_SMALL),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ04_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL + NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL + NUMBER_APV_SIGNAL_FOR_RANG_SMALL + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ04_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL + NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL + NUMBER_APV_SIGNAL_FOR_RANG_SMALL + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ04_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL + NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL + NUMBER_APV_SIGNAL_FOR_RANG_SMALL + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL  + NUMBER_UROV_SIGNAL_FOR_RANG_SMALL - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ04_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL + NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL + NUMBER_APV_SIGNAL_FOR_RANG_SMALL + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL  + NUMBER_UROV_SIGNAL_FOR_RANG_SMALL),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ04_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL + NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL + NUMBER_APV_SIGNAL_FOR_RANG_SMALL + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL  + NUMBER_UROV_SIGNAL_FOR_RANG_SMALL + NUMBER_ZOP_SIGNAL_FOR_RANG_SMALL - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ04_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL + NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL + NUMBER_APV_SIGNAL_FOR_RANG_SMALL + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL  + NUMBER_UROV_SIGNAL_FOR_RANG_SMALL + NUMBER_ZOP_SIGNAL_FOR_RANG_SMALL),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ04_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL + NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL + NUMBER_APV_SIGNAL_FOR_RANG_SMALL + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL  + NUMBER_UROV_SIGNAL_FOR_RANG_SMALL + NUMBER_ZOP_SIGNAL_FOR_RANG_SMALL + NUMBER_UMIN_SIGNAL_FOR_RANG_SMALL - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ04_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL + NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL + NUMBER_APV_SIGNAL_FOR_RANG_SMALL + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL  + NUMBER_UROV_SIGNAL_FOR_RANG_SMALL + NUMBER_ZOP_SIGNAL_FOR_RANG_SMALL + NUMBER_UMIN_SIGNAL_FOR_RANG_SMALL),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ04_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL + NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL + NUMBER_APV_SIGNAL_FOR_RANG_SMALL + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL  + NUMBER_UROV_SIGNAL_FOR_RANG_SMALL + NUMBER_ZOP_SIGNAL_FOR_RANG_SMALL + NUMBER_UMIN_SIGNAL_FOR_RANG_SMALL + NUMBER_UMAX_SIGNAL_FOR_RANG_SMALL - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ04_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL + NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL + NUMBER_APV_SIGNAL_FOR_RANG_SMALL + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL  + NUMBER_UROV_SIGNAL_FOR_RANG_SMALL + NUMBER_ZOP_SIGNAL_FOR_RANG_SMALL + NUMBER_UMIN_SIGNAL_FOR_RANG_SMALL + NUMBER_UMAX_SIGNAL_FOR_RANG_SMALL),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ04_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL + NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL + NUMBER_APV_SIGNAL_FOR_RANG_SMALL + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL  + NUMBER_UROV_SIGNAL_FOR_RANG_SMALL + NUMBER_ZOP_SIGNAL_FOR_RANG_SMALL + NUMBER_UMIN_SIGNAL_FOR_RANG_SMALL + NUMBER_UMAX_SIGNAL_FOR_RANG_SMALL + NUMBER_UP_SIGNAL_FOR_RANG_SMALL - 1)
      },
      {-1,-1},
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ04_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL + NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL + NUMBER_APV_SIGNAL_FOR_RANG_SMALL + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL + NUMBER_UROV_SIGNAL_FOR_RANG_SMALL + NUMBER_ZOP_SIGNAL_FOR_RANG_SMALL + NUMBER_UMIN_SIGNAL_FOR_RANG_SMALL + NUMBER_UMAX_SIGNAL_FOR_RANG_SMALL + NUMBER_UP_SIGNAL_FOR_RANG_SMALL + NUMBER_VMP_SIGNAL_FOR_RANG_SMALL),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ04_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL + NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL + NUMBER_APV_SIGNAL_FOR_RANG_SMALL + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL + NUMBER_UROV_SIGNAL_FOR_RANG_SMALL + NUMBER_ZOP_SIGNAL_FOR_RANG_SMALL + NUMBER_UMIN_SIGNAL_FOR_RANG_SMALL + NUMBER_UMAX_SIGNAL_FOR_RANG_SMALL + NUMBER_UP_SIGNAL_FOR_RANG_SMALL + NUMBER_VMP_SIGNAL_FOR_RANG_SMALL + NUMBER_EL_SIGNAL_FOR_RANG_SMALL - 1)
      }
    };
    
    /*************************************************************/
    //Գ������� �������, ���� � ����� ������������ ����������
    /*************************************************************/
    if(
       (type_ekran == INDEX_VIEWING_BUTTON)
#if (MODYFIKACIA_VERSII_PZ >= 10)
       ||
       (type_ekran == INDEX_VIEWING_IEC61850_RANG)
#endif
      )   
    {
      /*************************************************************/
      //� �������, ���� ����������� ����������� ���� �������������� ������, ��.GOOSE �����, ���  ��.MMS �����
      /*************************************************************/
      const uint32_t *p_array;
      if (type_ekran == INDEX_VIEWING_BUTTON) p_array = buttons_mode[(current_settings.buttons_mode >> (number_ekran - EKRAN_RANGUVANNJA_BUTTON_1)) & 0x1];
#if (MODYFIKACIA_VERSII_PZ >= 10)
      else 
      {
        if ((type_LN == INDEX_TYPE_IEC61850_IN_GOOSE) || (type_LN == INDEX_TYPE_IEC61850_IN_MMS)) p_array = rang_iec61850_blocks[type_LN];
        else total_error_sw_fixed(184);
      }
#endif

      for (unsigned int index_deleted_function = 0; index_deleted_function < NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL; index_deleted_function++)
      {
        if (
            (_CHECK_SET_BIT(p_array, index_deleted_function) == 0) 
#if (MODYFIKACIA_VERSII_PZ >= 10)
            ||
            ((type_LN == INDEX_TYPE_IEC61850_IN_GOOSE) && (index_deleted_function == (RANG_SMALL_BLOCK_IN_GOOSE1 + n_LN)))
            ||
            ((type_LN == INDEX_TYPE_IEC61850_IN_MMS) && (index_deleted_function == (RANG_SMALL_BLOCK_IN_MMS1 + n_LN)))
#endif
           )   
        {
          /*************************************************************/
          //³������� ��'� ���� ������� � ������ ���
          /*************************************************************/

          //������� ����� ��, �� �� ����� ��������� ��� ���������� ���� ����
          unsigned int maska[N_SMALL] = {0, 0, 0};
          for (unsigned int j = 0; j < (index_deleted_function - offset); j++) _SET_BIT(maska, j);
          
          /***/
          //������ ��� ����� ����������� ������� ����� �� �� �������
          /***/
          unsigned int new_temp_data_1[N_SMALL], new_temp_data_2[N_SMALL];

          for (unsigned int k = 0; k < N_SMALL; k++)
          {
            new_temp_data_1[k] = state_viewing_input[k] & maska[k];

            new_temp_data_2[k] = state_viewing_input[k] & (~maska[k]);
          }

          for (unsigned int k = 0; k < (N_SMALL - 1); k++)
          {
            new_temp_data_2[k] = ( (new_temp_data_2[k] >> 1) | ((new_temp_data_2[k + 1] & 0x1) << 31) ) & (~maska[k]);
          }
          new_temp_data_2[N_SMALL - 1] =  (new_temp_data_2[N_SMALL - 1] >> 1) & (~maska[N_SMALL - 1]);
                
          for (unsigned int k = 0; k < N_SMALL; k++)
          {
            state_viewing_input[k] = new_temp_data_1[k] | new_temp_data_2[k];
          }
          /***/
          for (unsigned int j = (index_deleted_function - offset); j < (NUMBER_TOTAL_SIGNAL_FOR_RANG_SMALL - offset); j++)
          {
            if ((j + 1) < (NUMBER_TOTAL_SIGNAL_FOR_RANG_SMALL - offset))
            {
              for (unsigned int k = 0; k < MAX_COL_LCD; k++)
                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION + 1][k];
            }
            else 
            {
              for (unsigned int k = 0; k  <MAX_COL_LCD; k++)
                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = ' ';
            }
          }
          if (current_ekran.index_position >= ((int)index_deleted_function)) position_temp--;
          offset++;
          /*************************************************************/
        }
      }
      /*************************************************************/
    }

    //������� ���������� ����������� ���������� (���� ����������� � ������� ������), ���� �������� � ������� �������
    int index_in_list = NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL;
    
    for (i = 0; i < TOTAL_NUMBER_PROTECTION; i++)
    {
      
      if((current_settings.configuration & (1 << i)) != 0)
      {
        //������ ������������, ���� ������� ����������� �� ������� - ���������� ������ �� �������� �������
        //������ ������� ������� �� ��������� �������, ���� ��� ��������� ������� ������� ���� �������� �������,
        //�� ������ �� ��� ����������� �� ������ ���������� �������
        if(min_max_number[i][0] >=0)
        {
          if(
             (type_ekran == INDEX_VIEWING_BUTTON)
#if (MODYFIKACIA_VERSII_PZ >= 10)
             ||
             (type_ekran == INDEX_VIEWING_IEC61850_RANG)
#endif
            )   
          {
            /*
            ������� ���� ���� ������� ����� �������������
            */
            const uint32_t *p_array;
            if (type_ekran == INDEX_VIEWING_BUTTON) p_array = buttons_mode[(current_settings.buttons_mode >> (number_ekran - EKRAN_RANGUVANNJA_BUTTON_1)) & 0x1];
#if (MODYFIKACIA_VERSII_PZ >= 10)
            else 
            {
              if ((type_LN == INDEX_TYPE_IEC61850_IN_GOOSE) || (type_LN == INDEX_TYPE_IEC61850_IN_MMS)) p_array = rang_iec61850_blocks[type_LN];
              else total_error_sw_fixed(185);
            }
#endif

            //³������� ����� ������� � ������ ��� ����� ����� � ���� �������, ���� ������� ������� � ������ ��� ���������� ��� ������ �������
            //������� ����� ��, �� �� ����� ��������� ��� ���������� ���� ����
            unsigned int maska[N_SMALL] = {0, 0, 0};
            unsigned int j1;
            for (j1 = 0; j1 < (min_max_number[i][0] - offset); j1++) _SET_BIT(maska, j1);
          
            //³������� ����� ������� �� ������, �� � �������
            while(index_in_list <= min_max_number[i][1])
            {
              if (_CHECK_SET_BIT(p_array, index_in_list) == 0) 
              {
                /***/
                //������ ��� ����� ����������� ������� ����� �� �� �������
                /***/
                unsigned int new_temp_data_1[N_SMALL], new_temp_data_2[N_SMALL];

                for (unsigned int k = 0; k < N_SMALL; k++)
                {
                  new_temp_data_1[k] = state_viewing_input[k] & maska[k];

                  new_temp_data_2[k] = state_viewing_input[k] & (~maska[k]);
                }

                for (unsigned int k = 0; k < (N_SMALL - 1); k++)
                {
                  new_temp_data_2[k] = ( (new_temp_data_2[k] >> 1) | ((new_temp_data_2[k + 1] & 0x1) << 31) ) & (~maska[k]);
                }
                new_temp_data_2[N_SMALL - 1] =  (new_temp_data_2[N_SMALL - 1] >> 1) & (~maska[N_SMALL - 1]);
                
                for (unsigned int k = 0; k < N_SMALL; k++)
                {
                  state_viewing_input[k] = new_temp_data_1[k] | new_temp_data_2[k];
                }
                /***/
                for (unsigned int j = (index_in_list - offset); j < (NUMBER_TOTAL_SIGNAL_FOR_RANG_SMALL - offset); j++)
                {
                  if ((j + 1) < (NUMBER_TOTAL_SIGNAL_FOR_RANG_SMALL - offset))
                  {
                    for (unsigned int k = 0; k < MAX_COL_LCD; k++)
                      name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION + 1][k];
                  }
                  else 
                  {
                    for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                      name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = ' ';
                  }
                }
                if (current_ekran.index_position >= index_in_list) position_temp--;
          
                offset++;
              }
              else
              {
                _SET_BIT(maska, j1);
                j1++;
              }
                
              index_in_list++;
            }
          }
          else
            index_in_list += ((min_max_number[i][1] - min_max_number[i][0]) + 1);
        }
      }
      else if (min_max_number[i][0] >=0)
      {
        //³������� ����� ������� � ������ ��� ����� ����� � ���� �������, ���� ������� ������� � ������ ��� ���������� ��� ������ �������
        //������� ����� ��, �� �� ����� ��������� ��� ���������� ���� ����
        unsigned int maska[N_SMALL] = {0, 0, 0};
        for (unsigned int j = 0; j < (min_max_number[i][0] - offset); j++) _SET_BIT(maska, j);
          
        //³������� ����� ������� �� ������, �� � �������
        while(index_in_list <= min_max_number[i][1])
        {
          /***/
          //������ ��� ����� ����������� ������� ����� �� �� �������
          /***/
          unsigned int new_temp_data_1[N_SMALL], new_temp_data_2[N_SMALL];

          for (unsigned int k = 0; k < N_SMALL; k++)
          {
            new_temp_data_1[k] = state_viewing_input[k] & maska[k];

            new_temp_data_2[k] = state_viewing_input[k] & (~maska[k]);
          }

          for (unsigned int k = 0; k < (N_SMALL - 1); k++)
          {
            new_temp_data_2[k] = ( (new_temp_data_2[k] >> 1) | ((new_temp_data_2[k + 1] & 0x1) << 31) ) & (~maska[k]);
          }
          new_temp_data_2[N_SMALL - 1] =  (new_temp_data_2[N_SMALL - 1] >> 1) & (~maska[N_SMALL - 1]);
          
          for (unsigned int k = 0; k < N_SMALL; k++)
          {
            state_viewing_input[k] = new_temp_data_1[k] | new_temp_data_2[k];
           }
          /***/
          for (unsigned int j = (index_in_list - offset); j < (NUMBER_TOTAL_SIGNAL_FOR_RANG_SMALL - offset); j++)
          {
            if ((j + 1) < (NUMBER_TOTAL_SIGNAL_FOR_RANG_SMALL - offset))
            {
              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION + 1][k];
            }
            else 
            {
              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = ' ';
            }
          }
          if (current_ekran.index_position >= index_in_list) position_temp--;
          
          offset++;
          index_in_list++;
        }
      }
    }
    /*************************************************************/
      
    //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
    index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

    for (i=0; i< MAX_ROW_LCD; i++)
    {
     if (index_of_ekran < ((NUMBER_TOTAL_SIGNAL_FOR_RANG_SMALL - offset) <<1))//�������� �� ��� ���������  NUMBER_TOTAL_SIGNAL_FOR_RANG_SMALL ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
     {
       if ((i & 0x1) == 0)
       {
         //� ��������� ����� ����� �������� ���������
         for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string_tmp[(index_of_ekran>>1) + NUMBER_ROW_FOR_NOTHING_INFORMATION][j];
       }
       else
       {
         //� ������� ����� ����� �������� ���� �������
         const unsigned char information[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
         {
           {"      ����      ", "      ���       "},
           {"      ����      ", "     �²��      "},
           {"      OFF       ", "       ON       "},
           {"      ъ��      ", "      ����      "}
        };
        unsigned int index_bit = index_of_ekran >> 1;
          
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = information[index_language][((state_viewing_input[index_bit >> 5] & ( 1<< (index_bit & 0x1f))) != 0)][j];
       }
     }
     else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

     index_of_ekran++;
    }
    
    const unsigned int cursor_x[MAX_NAMBER_LANGUAGE][2] = 
    {
      {5, 5},
      {5, 4},
      {5, 6},
      {5, 5}
    };

    //³���������� ������ �� �������� � ������ ������ �� ���� � ��� �� ���������
    current_ekran.position_cursor_x =  cursor_x[index_language][((state_viewing_input[position_temp >> 5] & (1 << (position_temp & 0x1f))) != 0)];
    current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
    
    //������ ����
    current_ekran.cursor_blinking_on = 1;
    //����� ����������� � ����� �����������
  }

  //�������� �������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;

#undef NUMBER_ROW_FOR_NOTHING_INFORMATION
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� ����������� ������� �� �������� �����-��������������-�-�������-����������
/*****************************************************/
void make_ekran_set_function_in_output_led_df_dt_reg(unsigned int number_ekran, unsigned int type_ekran, uint32_t temp_state[])
{
#define NUMBER_ROW_FOR_NOTHING_INFORMATION 2
  
#if (MODYFIKACIA_VERSII_PZ >= 10)
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_TOTAL_SIGNAL_FOR_RANG + (1 - N_IN_GOOSE)  + (1 - N_IN_MMS) + (1 - N_OUT_LAN) + (3  - NUMBER_UP_SIGNAL_FOR_RANG)][MAX_COL_LCD] = 
#else
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_TOTAL_SIGNAL_FOR_RANG + (3 - NUMBER_UP_SIGNAL_FOR_RANG)][MAX_COL_LCD] = 
#endif
  {
    {
      "      ���       ",
      "  ������������  ",
      NAME_RANG_RU
    },
    {
      "      ����      ",
      "   ����������   ",
      NAME_RANG_UA
    },
    {
      "       No       ",
      "  signal conf   ",
      NAME_RANG_EN
    },
    {
      "      ���       ",
      "  ������������  ",
      NAME_RANG_KZ
    }
  };
  unsigned char name_string_tmp[NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_TOTAL_SIGNAL_FOR_RANG][MAX_COL_LCD];

  int index_language = index_language_in_array(current_settings.language);
  for(int index_1 = 0; index_1 < (NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_TOTAL_SIGNAL_FOR_RANG); index_1++)
  {
    size_t index_row;
    if (index_1 < (NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_GENERAL_SIGNAL_FOR_RANG)) 
    {
#if (MODYFIKACIA_VERSII_PZ >= 10)
      if (index_1 < (NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_GENERAL_SIGNAL_FOR_RANG - (N_IN_GOOSE + N_IN_MMS + N_OUT_LAN))) 
      {
        index_row = index_1;
      }
      else if (index_1 < (NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_GENERAL_SIGNAL_FOR_RANG - (N_IN_MMS + N_OUT_LAN))) 
      {
        index_row = NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_BLOCK_IN_GOOSE1 + ((index_1 - (NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_GENERAL_SIGNAL_FOR_RANG - (N_IN_GOOSE + N_IN_MMS + N_OUT_LAN))) % 1);
      }
      else if (index_1 < (NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_GENERAL_SIGNAL_FOR_RANG - (N_OUT_LAN))) 
      {
        index_row = NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_BLOCK_IN_MMS1 + (1 - N_IN_GOOSE) + ((index_1 - (NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_GENERAL_SIGNAL_FOR_RANG - (N_IN_MMS + N_OUT_LAN))) % 1);
      }
      else
      {
        index_row = NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_BLOCK_OUT_LAN1 + (1 - N_IN_GOOSE) + (1 - N_IN_MMS) + ((index_1 - (NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_GENERAL_SIGNAL_FOR_RANG - (N_OUT_LAN))) % 1);
      }
#else
      index_row = index_1;
#endif        
    }
    else if (index_1 < (NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_BLOCK_UP1)) 
    {
      index_row = index_1
#if (MODYFIKACIA_VERSII_PZ >= 10)
                   + 1 - N_IN_GOOSE + 1 - N_IN_MMS + 1 - N_OUT_LAN
#endif        
                  ;
    }
    else if (index_1 < (NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_BLOCK_UP1 + NUMBER_UP_SIGNAL_FOR_RANG))
    {
      index_row = NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_BLOCK_UP1
#if (MODYFIKACIA_VERSII_PZ >= 10)
                   + 1 - N_IN_GOOSE + 1 - N_IN_MMS + 1 - N_OUT_LAN
#endif
                   + ((index_1 - (NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_BLOCK_UP1)) % 3);
    }
    else
    {
      index_row = index_1 
#if (MODYFIKACIA_VERSII_PZ >= 10)
                  + 1 - N_IN_GOOSE + 1 - N_IN_MMS + 1 - N_OUT_LAN
#endif        
                  + 3 - NUMBER_UP_SIGNAL_FOR_RANG;
    }
      
    for(size_t index_2 = 0; index_2 < MAX_COL_LCD; index_2++)
    {
#if (MODYFIKACIA_VERSII_PZ >= 10)
      if (
          (index_1 >= (NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_GENERAL_SIGNAL_FOR_RANG - (N_IN_GOOSE + N_IN_MMS + N_OUT_LAN)))  &&
          (index_1 <  (NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_GENERAL_SIGNAL_FOR_RANG - (N_IN_MMS + N_OUT_LAN))) &&
          (index_2 >=  index_n_In_GOOSE[index_language][(index_1 - (NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_BLOCK_IN_GOOSE1)) % 1]) &&
          (index_2 <= (index_n_In_GOOSE[index_language][(index_1 - (NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_BLOCK_IN_GOOSE1)) % 1] + 1)) 
         )   
      {
        unsigned int n = index_1 - (NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_BLOCK_IN_GOOSE1);
        if ((n + 1) < 10)
        {
          if (index_2 == index_n_In_GOOSE[index_language][n % 1])
            name_string_tmp[index_1][index_2] = 0x30 + (n + 1);
          else
            name_string_tmp[index_1][index_2] = ' ';
        }
        else
        {
          if (index_2 == index_n_In_GOOSE[index_language][n % 1])
            name_string_tmp[index_1][index_2] = 0x30 + (n / 1 + 1) / 10;
          else
            name_string_tmp[index_1][index_2] = 0x30 + (n / 1 + 1) % 10;
        }
      }
      else if (
               (index_1 >= (NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_GENERAL_SIGNAL_FOR_RANG - (N_IN_MMS + N_OUT_LAN)))  &&
               (index_1 <  (NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_GENERAL_SIGNAL_FOR_RANG - (N_OUT_LAN))) &&
               (index_2 == index_n_In_MMS[index_language][(index_1 - (NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_BLOCK_IN_MMS1)) % 1]) 
              )   
      {
        name_string_tmp[index_1][index_2] = 0x30 + ((index_1 - (NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_BLOCK_IN_MMS1)) / 1 + 1);
      }
      else if (
               (index_1 >= (NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_GENERAL_SIGNAL_FOR_RANG - (N_OUT_LAN)))  &&
               (index_1 <  (NUMBER_ROW_FOR_NOTHING_INFORMATION + NUMBER_GENERAL_SIGNAL_FOR_RANG)) &&
               (index_2 == index_n_Out_LAN[index_language][(index_1 - (NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_BLOCK_OUT_LAN1)) % 1]) 
              )   
      {
        name_string_tmp[index_1][index_2] = 0x30 + ((index_1 - (NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_BLOCK_OUT_LAN1)) / 1 + 1);
      }
      else 
#endif
      {
        if (
            (index_1 >= (NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_BLOCK_UP1))  &&
            (index_1 <  (NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_BLOCK_UP1 + NUMBER_UP_SIGNAL_FOR_RANG)) &&
            (index_2 == index_number_UP[index_language][(index_1 - (NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_BLOCK_UP1)) % 3]) 
           )   
        {
          name_string_tmp[index_1][index_2] = 0x30 + ((index_1 - (NUMBER_ROW_FOR_NOTHING_INFORMATION + RANG_BLOCK_UP1)) / 3 + 1);
        }
        else name_string_tmp[index_1][index_2] = name_string[index_language][index_row][index_2];
      }
    }
  }
  
  unsigned int state_viewing_input[N_BIG];
  for (size_t i = 0; i < N_BIG; i++ ) state_viewing_input[i] = temp_state[i];
  
  if ((current_settings.control_zz & CTR_ZZ1_TYPE) != 0)
  {
    const unsigned char name_block_zz[MAX_NAMBER_LANGUAGE][MAX_COL_LCD] = 
    {
      "    ����.��     ",
      "    ����.��     ",
      "    ����.��     ",
      "    ����.��     "
    };
    for (unsigned int index_1 = 0; index_1 < MAX_COL_LCD; index_1++)
    {
      name_string_tmp[RANG_BLOCK_NZZ + NUMBER_ROW_FOR_NOTHING_INFORMATION][index_1] = name_block_zz[index_language][index_1];
    }
  }

  if(current_ekran.edition == 0)
  {
    //�������, ���� �� ������������� ���������� ������� �� ����
    if (
        (state_viewing_input[0] == 0) && 
        (state_viewing_input[1] == 0) &&
        (state_viewing_input[2] == 0) &&
        (state_viewing_input[3] == 0) &&
        (state_viewing_input[4] == 0) &&
        (state_viewing_input[5] == 0) &&
        (state_viewing_input[6] == 0) &&
        (state_viewing_input[7] == 0) &&
        (state_viewing_input[8] == 0)
       )
    {
      //�� ������, �� �� ����� ���� ������ �� �����������
      
      //������ ������� � ������ ���������� �� ��� �������
      current_ekran.index_position = 0;
      position_in_current_level_menu[number_ekran] = 0;

      //�������  ����� � ������� �����
      for (unsigned int i=0; i< MAX_ROW_LCD; i++)
      {
        //������� � ������� ����� ����������, �� ������ �� �����������
        if (i < NUMBER_ROW_FOR_NOTHING_INFORMATION)
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string_tmp[i][j];
        else
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';
      }

      //³���������� ������� �� ��������
      current_ekran.position_cursor_y = 0;
      //������ ���������
      current_ekran.cursor_on = 0;
    }
    else
    {
      /************************************************************/
      //������� ������ �� �������, �� ������� �����������
      /************************************************************/
      unsigned int position_temp = current_ekran.index_position;
      unsigned int index_of_ekran;
      unsigned int i = 0, offset = 0;
      unsigned int state_current_bit;
      
      while ((i + offset) < NUMBER_TOTAL_SIGNAL_FOR_RANG)
      {
        state_current_bit = state_viewing_input[(i + offset)>>5] & (1<<((i + offset) & 0x1f));
          
        if (state_current_bit == 0)
        {
          for (unsigned int j = i; j < (NUMBER_TOTAL_SIGNAL_FOR_RANG - offset); j++)
          {
            if ((j + 1) < (NUMBER_TOTAL_SIGNAL_FOR_RANG - offset))
            {
              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION + 1][k];
            }
            else 
            {
              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = ' ';
            }
          }
          if (current_ekran.index_position >= ((int)(i + offset))) position_temp--;
          offset++;
          
          //������ � Watchdog
          watchdog_routine();
        }
        else i++;
      }
      /************************************************************/

      index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
      
      //�������  ����� � ������� �����
      for (i=0; i< MAX_ROW_LCD; i++)
      {
        //�������� ����� ����� ���������, �� �� ����� ���������� � ������� �����������
        if (index_of_ekran < NUMBER_TOTAL_SIGNAL_FOR_RANG)
        {
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string_tmp[index_of_ekran + NUMBER_ROW_FOR_NOTHING_INFORMATION][j];

          //ϳ������� �����, ��� �� ���� ������ ������ ������
          unsigned int iteration = 0;
          while (
                 (working_ekran[i][0] == ' ') &&
                 (working_ekran[i][1] == ' ') &&
                 (iteration < (MAX_COL_LCD - 1 - 1))
                )
          {
            for (unsigned int j = 1; j < MAX_COL_LCD; j++)
            {
              if ((j + 1) < MAX_COL_LCD)
                working_ekran[i][j] = working_ekran[i][j + 1];
              else
                working_ekran[i][j] = ' ';
            }
            iteration++;
          }
        }
        else
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

        index_of_ekran++;
      }
      //³���������� ������ �� ��������
      current_ekran.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
      //������ �������
      current_ekran.cursor_on = 1;
    }

    //������ �� ���������� ������������ �� ������ �������
    current_ekran.position_cursor_x = 0;
    //������ �� ����
    current_ekran.cursor_blinking_on = 0;
  }
  else
  {
    unsigned int position_temp = current_ekran.index_position;
    unsigned int index_of_ekran;
    unsigned int i, offset = 0;
    int min_max_number[TOTAL_NUMBER_PROTECTION][2] =
    {
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_MTZ04_SIGNAL_FOR_RANG - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_MTZ04_SIGNAL_FOR_RANG),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_MTZ04_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_MTZ04_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_MTZ04_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG + NUMBER_ZZ_SIGNAL_FOR_RANG - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_MTZ04_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG + NUMBER_ZZ_SIGNAL_FOR_RANG),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_MTZ04_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG + NUMBER_ZZ_SIGNAL_FOR_RANG + NUMBER_TZNP_SIGNAL_FOR_RANG - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_MTZ04_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG + NUMBER_ZZ_SIGNAL_FOR_RANG + NUMBER_TZNP_SIGNAL_FOR_RANG),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_MTZ04_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG + NUMBER_ZZ_SIGNAL_FOR_RANG + NUMBER_TZNP_SIGNAL_FOR_RANG + NUMBER_APV_SIGNAL_FOR_RANG - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_MTZ04_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG + NUMBER_ZZ_SIGNAL_FOR_RANG + NUMBER_TZNP_SIGNAL_FOR_RANG + NUMBER_APV_SIGNAL_FOR_RANG),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_MTZ04_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG + NUMBER_ZZ_SIGNAL_FOR_RANG + NUMBER_TZNP_SIGNAL_FOR_RANG + NUMBER_APV_SIGNAL_FOR_RANG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_MTZ04_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG + NUMBER_ZZ_SIGNAL_FOR_RANG + NUMBER_TZNP_SIGNAL_FOR_RANG + NUMBER_APV_SIGNAL_FOR_RANG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_MTZ04_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG + NUMBER_ZZ_SIGNAL_FOR_RANG + NUMBER_TZNP_SIGNAL_FOR_RANG + NUMBER_APV_SIGNAL_FOR_RANG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG  + NUMBER_UROV_SIGNAL_FOR_RANG - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_MTZ04_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG + NUMBER_ZZ_SIGNAL_FOR_RANG + NUMBER_TZNP_SIGNAL_FOR_RANG + NUMBER_APV_SIGNAL_FOR_RANG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG  + NUMBER_UROV_SIGNAL_FOR_RANG),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_MTZ04_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG + NUMBER_ZZ_SIGNAL_FOR_RANG + NUMBER_TZNP_SIGNAL_FOR_RANG + NUMBER_APV_SIGNAL_FOR_RANG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG  + NUMBER_UROV_SIGNAL_FOR_RANG + NUMBER_ZOP_SIGNAL_FOR_RANG - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_MTZ04_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG + NUMBER_ZZ_SIGNAL_FOR_RANG + NUMBER_TZNP_SIGNAL_FOR_RANG + NUMBER_APV_SIGNAL_FOR_RANG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG  + NUMBER_UROV_SIGNAL_FOR_RANG + NUMBER_ZOP_SIGNAL_FOR_RANG),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_MTZ04_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG + NUMBER_ZZ_SIGNAL_FOR_RANG + NUMBER_TZNP_SIGNAL_FOR_RANG + NUMBER_APV_SIGNAL_FOR_RANG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG  + NUMBER_UROV_SIGNAL_FOR_RANG + NUMBER_ZOP_SIGNAL_FOR_RANG + NUMBER_UMIN_SIGNAL_FOR_RANG - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_MTZ04_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG + NUMBER_ZZ_SIGNAL_FOR_RANG + NUMBER_TZNP_SIGNAL_FOR_RANG + NUMBER_APV_SIGNAL_FOR_RANG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG  + NUMBER_UROV_SIGNAL_FOR_RANG + NUMBER_ZOP_SIGNAL_FOR_RANG + NUMBER_UMIN_SIGNAL_FOR_RANG),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_MTZ04_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG + NUMBER_ZZ_SIGNAL_FOR_RANG + NUMBER_TZNP_SIGNAL_FOR_RANG + NUMBER_APV_SIGNAL_FOR_RANG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG  + NUMBER_UROV_SIGNAL_FOR_RANG + NUMBER_ZOP_SIGNAL_FOR_RANG + NUMBER_UMIN_SIGNAL_FOR_RANG + NUMBER_UMAX_SIGNAL_FOR_RANG - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_MTZ04_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG + NUMBER_ZZ_SIGNAL_FOR_RANG + NUMBER_TZNP_SIGNAL_FOR_RANG + NUMBER_APV_SIGNAL_FOR_RANG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG  + NUMBER_UROV_SIGNAL_FOR_RANG + NUMBER_ZOP_SIGNAL_FOR_RANG + NUMBER_UMIN_SIGNAL_FOR_RANG + NUMBER_UMAX_SIGNAL_FOR_RANG),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_MTZ04_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG + NUMBER_ZZ_SIGNAL_FOR_RANG + NUMBER_TZNP_SIGNAL_FOR_RANG + NUMBER_APV_SIGNAL_FOR_RANG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG  + NUMBER_UROV_SIGNAL_FOR_RANG + NUMBER_ZOP_SIGNAL_FOR_RANG + NUMBER_UMIN_SIGNAL_FOR_RANG + NUMBER_UMAX_SIGNAL_FOR_RANG + NUMBER_UP_SIGNAL_FOR_RANG - 1)
      },
      {-1,-1},
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_MTZ04_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG + NUMBER_ZZ_SIGNAL_FOR_RANG + NUMBER_TZNP_SIGNAL_FOR_RANG + NUMBER_APV_SIGNAL_FOR_RANG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG + NUMBER_UROV_SIGNAL_FOR_RANG + NUMBER_ZOP_SIGNAL_FOR_RANG + NUMBER_UMIN_SIGNAL_FOR_RANG + NUMBER_UMAX_SIGNAL_FOR_RANG + NUMBER_UP_SIGNAL_FOR_RANG + NUMBER_VMP_SIGNAL_FOR_RANG),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_MTZ04_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG + NUMBER_ZZ_SIGNAL_FOR_RANG + NUMBER_TZNP_SIGNAL_FOR_RANG + NUMBER_APV_SIGNAL_FOR_RANG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG + NUMBER_UROV_SIGNAL_FOR_RANG + NUMBER_ZOP_SIGNAL_FOR_RANG + NUMBER_UMIN_SIGNAL_FOR_RANG + NUMBER_UMAX_SIGNAL_FOR_RANG + NUMBER_UP_SIGNAL_FOR_RANG + NUMBER_VMP_SIGNAL_FOR_RANG + NUMBER_EL_SIGNAL_FOR_RANG - 1)
      }
    };
    
    /*************************************************************/
    //Գ������� �������, ���� � ����� ������������ ����������
    /*************************************************************/
    if(
       (type_ekran == INDEX_VIEWING_A_REG ) ||
       (type_ekran == INDEX_VIEWING_D_REG ) ||
       (type_ekran == INDEX_VIEWING_OFF_CB) ||
       (type_ekran == INDEX_VIEWING_ON_CB)
      )
    {
      /*************************************************************/
      //� �������, ���� ����������� ����������� ���� ����������� ���������� �� ����������� ����������, �� �������� � �������, �� �� ������ ���� ���������
      /*************************************************************/
      unsigned int index_deleted_function;
      
      if (type_ekran == INDEX_VIEWING_A_REG)
        index_deleted_function = RANG_WORK_A_REJESTRATOR;
      else if (type_ekran == INDEX_VIEWING_D_REG)
        index_deleted_function = RANG_WORK_D_REJESTRATOR;
      else if (type_ekran == INDEX_VIEWING_OFF_CB)
        index_deleted_function = RANG_WORK_BO;
      else
        index_deleted_function = RANG_WORK_BV;
      
      /*************************************************************/
      //³������� ��'� ���� ������� � ������ ���
      /*************************************************************/

      //������� ����� ��, �� �� ����� ��������� ��� ���������� ���� ����
      unsigned int maska[N_BIG] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
      for (unsigned int j = 0; j < (index_deleted_function - offset); j++) _SET_BIT(maska, j);
          
      /***/
      //������ ��� ����� ����������� ������� ����� �� �� �������
      /***/
      unsigned int new_temp_data_1[N_BIG], new_temp_data_2[N_BIG];

      for (unsigned int k = 0; k < N_BIG; k++)
      {
        new_temp_data_1[k] = state_viewing_input[k] & maska[k];

        new_temp_data_2[k] = state_viewing_input[k] & (~maska[k]);
      }

      for (unsigned int k = 0; k < (N_BIG - 1); k++)
      {
        new_temp_data_2[k] = ( (new_temp_data_2[k] >> 1) | ((new_temp_data_2[k + 1] & 0x1) << 31) ) & (~maska[k]);
      }
      new_temp_data_2[N_BIG - 1] =  (new_temp_data_2[N_BIG - 1] >> 1) & (~maska[N_BIG - 1]);
                
      for (unsigned int k = 0; k < N_BIG; k++)
      {
        state_viewing_input[k] = new_temp_data_1[k] | new_temp_data_2[k];
      }
      /***/
      for (unsigned int j = (index_deleted_function - offset); j < (NUMBER_TOTAL_SIGNAL_FOR_RANG - offset); j++)
      {
        if ((j + 1) < (NUMBER_TOTAL_SIGNAL_FOR_RANG - offset))
        {
          for (unsigned int k = 0; k<MAX_COL_LCD; k++)
            name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION + 1][k];
        }
        else 
        {
          for (unsigned int k = 0; k<MAX_COL_LCD; k++)
            name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = ' ';
        }
      }
      if (current_ekran.index_position >= ((int)index_deleted_function)) position_temp--;
      offset++;
      /*************************************************************/

      /*************************************************************/
    }
//    else if(type_ekran == INDEX_VIEWING_OUTPUT)
//    {
//      /*************************************************************/
//      //� �������, ���� ����������� ����������� ���� ������, �� �������� � �������, �� �� ������ ���� ���������� �� ���������� �����
//      /*
//      � ��:
//            "������ ��" - ���� ���� ��� � ����������� �� ���� ������ (�� ��� �� ����� ���������, ��� ���� ��������� ���� �����)
//            "������ ��" - ���� ���� ��� � ����������� �� ���� ������ (�� ��� �� ����� ���������, ��� ���� ��������� ���� �����)
//      */
//      
//      unsigned int current_number_output = number_ekran - EKRAN_RANGUVANNJA_OUTPUT_1;
//
//      for (i = 0; i < 2; i++)
//      {
//        unsigned int index_deleted_function;
//        unsigned int maska_func[N_BIG] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
//        unsigned int need_filtration = 0;
//        //��������� ������ �������, ��� ���������� ������� ����� ���� ����������� �� �������
//        //������ ��������� ������� � ������ �������
//        if (i == 0)
//        {
//          index_deleted_function = (RANG_WORK_BV > RANG_WORK_BO) ? RANG_WORK_BO : RANG_WORK_BV;
//        }
//        else
//        {
//          index_deleted_function = (RANG_WORK_BV > RANG_WORK_BO) ? RANG_WORK_BV : RANG_WORK_BO;
//        }
//        
//        //������� �����  ��� ���� �������
//        _SET_BIT(maska_func, index_deleted_function);
//        
//        unsigned int index = 0;
//        while ((need_filtration == 0) && (index < NUMBER_OUTPUTS))
//        {
//          //���������� ������� ����� ������, �� �� ����� ���� ������� �� ������������ �� ��� �����������
//          if (index != current_number_output)
//          {
//            if (
//                ((current_settings.ranguvannja_outputs[N_BIG*index    ] & maska_func[0]) != 0) ||
//                ((current_settings.ranguvannja_outputs[N_BIG*index + 1] & maska_func[1]) != 0) ||
//                ((current_settings.ranguvannja_outputs[N_BIG*index + 2] & maska_func[2]) != 0) ||
//                ((current_settings.ranguvannja_outputs[N_BIG*index + 3] & maska_func[3]) != 0) ||
//                ((current_settings.ranguvannja_outputs[N_BIG*index + 4] & maska_func[4]) != 0) ||
//                ((current_settings.ranguvannja_outputs[N_BIG*index + 5] & maska_func[5]) != 0) ||
//                ((current_settings.ranguvannja_outputs[N_BIG*index + 6] & maska_func[6]) != 0) ||
//                ((current_settings.ranguvannja_outputs[N_BIG*index + 7] & maska_func[7]) != 0) ||
//                ((current_settings.ranguvannja_outputs[N_BIG*index + 8] & maska_func[8]) != 0)
//               )
//            {
//              need_filtration = 1;
//            }
//          }
//          index++;
//        }
//        
//        //� �������, ���� ������������ �� ���� ������� ����� �������������, �� �������� ��
//        if (need_filtration != 0)
//        {
//          //������� ����� ��, �� �� ����� ��������� ��� ���������� ���� ����
//          unsigned int maska[N_BIG] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
//          for (unsigned int j = 0; j < (index_deleted_function - offset); j++) _SET_BIT(maska, j);
//          
//          /***/
//          //������ ��� ����� ����������� ������� ����� �� �� �������
//          /***/
//          unsigned int new_temp_data_1[N_BIG], new_temp_data_2[N_BIG];
//
//          for (unsigned int k = 0; k < N_BIG; k++)
//          {
//            new_temp_data_1[k] = state_viewing_input[k] & maska[k];
//
//            new_temp_data_2[k] = state_viewing_input[k] & (~maska[k]);
//          }
//
//          for (unsigned int k = 0; k < (N_BIG - 1); k++)
//          {
//            new_temp_data_2[k] = ( (new_temp_data_2[k] >> 1) | ((new_temp_data_2[k + 1] & 0x1) << 31) ) & (~maska[k]);
//          }
//          new_temp_data_2[N_BIG - 1] =  (new_temp_data_2[N_BIG - 1] >> 1) & (~maska[N_BIG - 1]);
//                
//          for (unsigned int k = 0; k < N_BIG; k++)
//          {
//            state_viewing_input[k] = new_temp_data_1[k] | new_temp_data_2[k];
//          }
//          /***/
//          for (unsigned int j = (index_deleted_function - offset); j < (max_row_ranguvannja - offset); j++)
//          {
//            if ((j + 1) < (max_row_ranguvannja - offset))
//            {
//              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
//                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION + 1][k];
//            }
//            else 
//            {
//              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
//                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = ' ';
//            }
//          }
//          if (current_ekran.index_position >= ((int)index_deleted_function)) position_temp--;
//          offset++;
//          /*************************************************************/
//        }
//      }
//      /*************************************************************/
//    }

    //������� ���������� ����������� ���������� (���� ����������� � ������� ������), ���� �������� � ������� �������
    int index_in_list = NUMBER_GENERAL_SIGNAL_FOR_RANG;
    
    for (i = 0; i < TOTAL_NUMBER_PROTECTION; i++)
    {
      
      if((current_settings.configuration & (1 << i)) != 0)
      {
        //������ ������������, ���� ������� ����������� �� ������� - ���������� ������ �� �������� �������
        //������ ������� ������� �� ��������� �������, ���� ��� ��������� ������� ������� ���� �������� �������,
        //�� ������ �� ��� ����������� �� ������ ���������� �������
        if(min_max_number[i][0] >=0)
        {
          if (
              (i == ZZ_BIT_CONFIGURATION) &&
              ((current_settings.control_zz & CTR_ZZ1_TYPE) != 0)
             )
          {
            /*
            ������� ���� �������, �� ���������� �� ��� ����� �������������
            */

            //³������� ����� ������� � ������ ��� ����� ����� � ���� �������, ���� ������� ������� � ������ ��� ���������� ��� ������ �������
            //������� ����� ��, �� �� ����� ��������� ��� ���������� ���� ����
            unsigned int maska[N_BIG] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
            unsigned int j1;
            for (j1 = 0; j1 < (min_max_number[i][0] - offset); j1++) _SET_BIT(maska, j1);
          
            //³������� ����� ������� �� ������, �� � �������
            while(index_in_list <= min_max_number[i][1])
            {
              if (
                  (index_in_list == RANG_PO_NZZ    ) ||
                  (index_in_list == RANG_NZZ       ) ||
                  (index_in_list == RANG_SECTOR_NZZ)
                 )
              {
                /***/
                //������ ��� ����� ����������� ������� ����� �� �� �������
                /***/
                unsigned int new_temp_data_1[N_BIG], new_temp_data_2[N_BIG];

                for (unsigned int k = 0; k < N_BIG; k++)
                {
                  new_temp_data_1[k] = state_viewing_input[k] & maska[k];

                  new_temp_data_2[k] = state_viewing_input[k] & (~maska[k]);
                }

                for (unsigned int k = 0; k < (N_BIG - 1); k++)
                {
                  new_temp_data_2[k] = ( (new_temp_data_2[k] >> 1) | ((new_temp_data_2[k + 1] & 0x1) << 31) ) & (~maska[k]);
                }
                new_temp_data_2[N_BIG - 1] =  (new_temp_data_2[N_BIG - 1] >> 1) & (~maska[N_BIG - 1]);
                
                for (unsigned int k = 0; k < N_BIG; k++)
                {
                  state_viewing_input[k] = new_temp_data_1[k] | new_temp_data_2[k];
                }
                /***/
                for (unsigned int j = (index_in_list - offset); j < NUMBER_TOTAL_SIGNAL_FOR_RANG; j++)
                {
                  if ((j + 1) < (NUMBER_TOTAL_SIGNAL_FOR_RANG - offset))
                  {
                    for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                      name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION + 1][k];
                  }
                  else 
                  {
                    for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                      name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = ' ';
                  }
                }
                if (current_ekran.index_position >= index_in_list) position_temp--;
          
                offset++;
              }
              else
              {
                _SET_BIT(maska, j1);
                j1++;
              }
                
              index_in_list++;
            }
          }
          else if (i == EL_BIT_CONFIGURATION)
          {
            /*
            ������� ���� ���� ������� ��������� ����� ����� �������������
            */

            //³������� ����� ������� � ������ ��� ����� ����� � ���� �������, ���� ������� ������� � ������ ��� ���������� ��� ������ �������
            //������� ����� ��, �� �� ����� ��������� ��� ���������� ���� ����
            unsigned int maska[N_BIG] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
            unsigned int j1;
            for (j1 = 0; j1 < (min_max_number[i][0] - offset); j1++) _SET_BIT(maska, j1);
          
            //³������� ����� ������� �� ������, �� � �������
            while(index_in_list <= min_max_number[i][1])
            {
              if (
                  (
                   /*
                   (
                    (index_in_list >= (int)(RANG_DF1_IN + 2*current_settings.number_defined_df)) &&
                    (index_in_list <= RANG_DF8_OUT)
                   )
                   ||
                   */
                   (
                    (type_ekran == INDEX_VIEWING_DF) &&
                    (
                     (index_in_list == (RANG_DF1_IN  + 2*(number_ekran - EKRAN_RANGUVANNJA_DF1_PLUS) / 3)) ||
                     (index_in_list == (RANG_DF1_OUT + 2*(number_ekran - EKRAN_RANGUVANNJA_DF1_PLUS) / 3))
                    )  
                   )
                  )   
                  ||  
                  (
                   /*
                   (
                    (index_in_list >= (int)(RANG_DT1_SET + 3*current_settings.number_defined_dt)) &&
                    (index_in_list <= RANG_DT4_OUT)
                   )
                   ||
                   */
                   (
                    (type_ekran == INDEX_VIEWING_DT) &&
                    (
                     (index_in_list == (RANG_DT1_SET   + 3*(number_ekran - EKRAN_RANGUVANNJA_SET_DT1_PLUS) / 4)) ||
                     (index_in_list == (RANG_DT1_RESET + 3*(number_ekran - EKRAN_RANGUVANNJA_SET_DT1_PLUS) / 4)) ||
                     (index_in_list == (RANG_DT1_OUT   + 3*(number_ekran - EKRAN_RANGUVANNJA_SET_DT1_PLUS) / 4))
                    )  
                   ) 
                  )   
                  ||  
                  (
                   /*
                   (
                    (index_in_list >= (int)(RANG_D_AND1 + current_settings.number_defined_and)) &&
                    (index_in_list <= RANG_D_AND8)
                   )   
                   ||
                   */
                   (
                    (type_ekran == INDEX_VIEWING_D_AND) &&
                    (index_in_list == (RANG_D_AND1 + (number_ekran - EKRAN_RANGUVANNJA_D_AND1)))
                   )   
                  )   
                  ||  
                  (
                   /*
                   (
                    (index_in_list >= (int)(RANG_D_OR1 + current_settings.number_defined_or)) &&
                    (index_in_list <= RANG_D_OR8)
                   )   
                   ||
                   */
                   (
                    (type_ekran == INDEX_VIEWING_D_OR) &&
                    (index_in_list == (RANG_D_OR1 + (number_ekran - EKRAN_RANGUVANNJA_D_OR1)))
                   )   
                  )   
                  ||  
                  (
                   /*
                   (
                    (index_in_list >= (int)(RANG_D_XOR1 + current_settings.number_defined_xor)) &&
                    (index_in_list <= RANG_D_XOR8)
                   )   
                   ||
                   */
                   (
                    (type_ekran == INDEX_VIEWING_D_XOR) &&
                    (index_in_list == (RANG_D_XOR1 + (number_ekran - EKRAN_RANGUVANNJA_D_XOR1)))
                   )   
                  )   
                  ||  
                  (
                   /*
                   (
                    (index_in_list >= (int)(RANG_D_NOT1 + current_settings.number_defined_not)) &&
                    (index_in_list <= RANG_D_NOT16)
                   )   
                   ||
                   */
                   (
                    (type_ekran == INDEX_VIEWING_D_NOT) &&
                    (index_in_list == (RANG_D_NOT1 + (number_ekran - EKRAN_RANGUVANNJA_D_NOT1)))
                   )   
                  )   
                 )
              {
                /***/
                //������ ��� ����� ����������� ������� ����� �� �� �������
                /***/
                unsigned int new_temp_data_1[N_BIG], new_temp_data_2[N_BIG];

                for (unsigned int k = 0; k < N_BIG; k++)
                {
                  new_temp_data_1[k] = state_viewing_input[k] & maska[k];

                  new_temp_data_2[k] = state_viewing_input[k] & (~maska[k]);
                }

                for (unsigned int k = 0; k < (N_BIG - 1); k++)
                {
                  new_temp_data_2[k] = ( (new_temp_data_2[k] >> 1) | ((new_temp_data_2[k + 1] & 0x1) << 31) ) & (~maska[k]);
                }
                new_temp_data_2[N_BIG - 1] =  (new_temp_data_2[N_BIG - 1] >> 1) & (~maska[N_BIG - 1]);
                
                for (unsigned int k = 0; k < N_BIG; k++)
                {
                  state_viewing_input[k] = new_temp_data_1[k] | new_temp_data_2[k];
                }
                /***/
                for (unsigned int j = (index_in_list - offset); j < (NUMBER_TOTAL_SIGNAL_FOR_RANG - offset); j++)
                {
                  if ((j + 1) < (NUMBER_TOTAL_SIGNAL_FOR_RANG - offset))
                  {
                    for (unsigned int k = 0; k < MAX_COL_LCD; k++)
                      name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION + 1][k];
                  }
                  else 
                  {
                    for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                      name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = ' ';
                  }
                }
                if (current_ekran.index_position >= index_in_list) position_temp--;
          
                offset++;
              }
              else
              {
                _SET_BIT(maska, j1);
                j1++;
              }
                
              index_in_list++;
            }
          }
          else
            index_in_list += ((min_max_number[i][1] - min_max_number[i][0]) + 1);
        }
      }
      else if (min_max_number[i][0] >=0)
      {
        //³������� ����� ������� � ������ ��� ����� ����� � ���� �������, ���� ������� ������� � ������ ��� ���������� ��� ������ �������
        //������� ����� ��, �� �� ����� ��������� ��� ���������� ���� ����
        unsigned int maska[N_BIG] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        for (unsigned int j = 0; j < (min_max_number[i][0] - offset); j++) _SET_BIT(maska, j);
          
        //³������� ����� ������� �� ������, �� � �������
        while(index_in_list <= min_max_number[i][1])
        {
          /***/
          //������ ��� ����� ����������� ������� ����� �� �� �������
          /***/
          unsigned int new_temp_data_1[N_BIG], new_temp_data_2[N_BIG];

          for (unsigned int k = 0; k < N_BIG; k++)
          {
            new_temp_data_1[k] = state_viewing_input[k] & maska[k];

            new_temp_data_2[k] = state_viewing_input[k] & (~maska[k]);
          }

          for (unsigned int k = 0; k < (N_BIG - 1); k++)
          {
            new_temp_data_2[k] = ( (new_temp_data_2[k] >> 1) | ((new_temp_data_2[k + 1] & 0x1) << 31) ) & (~maska[k]);
          }
          new_temp_data_2[N_BIG - 1] =  (new_temp_data_2[N_BIG - 1] >> 1) & (~maska[N_BIG - 1]);
                
          for (unsigned int k = 0; k < N_BIG; k++)
          {
            state_viewing_input[k] = new_temp_data_1[k] | new_temp_data_2[k];
          }
          /***/
          for (unsigned int j = (index_in_list - offset); j < (NUMBER_TOTAL_SIGNAL_FOR_RANG - offset); j++)
          {
            if ((j + 1) < (NUMBER_TOTAL_SIGNAL_FOR_RANG - offset))
            {
              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION + 1][k];
            }
            else 
            {
              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = ' ';
            }
          }
          if (current_ekran.index_position >= index_in_list) position_temp--;
          
          offset++;
          index_in_list++;
        }
      }
          
      //������ � Watchdog
      watchdog_routine();
    }
    /*************************************************************/

    //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
    index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

    for (i=0; i< MAX_ROW_LCD; i++)
    {
     if (index_of_ekran < ((NUMBER_TOTAL_SIGNAL_FOR_RANG - offset)<<1))//�������� �� ��� ���������  NUMBER_TOTAL_SIGNAL_FOR_RANG ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
     {
       if ((i & 0x1) == 0)
       {
         //� ��������� ����� ����� �������� ���������
         for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string_tmp[(index_of_ekran>>1) + NUMBER_ROW_FOR_NOTHING_INFORMATION][j];
       }
       else
       {
         //� ������� ����� ����� �������� ���� �������
         const unsigned char information[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
         {
           {"      ����      ", "      ���       "},
           {"      ����      ", "     �²��      "},
           {"      OFF       ", "       ON       "},
           {"      ъ��      ", "      ����      "}
         };
         unsigned int index_bit = index_of_ekran >> 1;
         
         for (unsigned int j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = information[index_language][((state_viewing_input[index_bit >> 5] & ( 1<< (index_bit & 0x1f))) != 0)][j];
       }
     }
     else
     for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

     index_of_ekran++;
    }
    
    const unsigned int cursor_x[MAX_NAMBER_LANGUAGE][2] = 
    {
      {5, 5},
      {5, 4},
      {5, 6},
      {5, 5}
    };

    //³���������� ������ �� �������� � ������ ������ �� ���� � ��� �� ��������� ������
    current_ekran.position_cursor_x =  cursor_x[index_language][((state_viewing_input[position_temp >> 5] & (1 << (position_temp & 0x1f))) != 0)];
    current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
    
    //������ ����
    current_ekran.cursor_blinking_on = 1;
    //����� ����������� � ����� �����������
  }
  

  //�������� �������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;

#undef NUMBER_ROW_FOR_NOTHING_INFORMATION
}
/*****************************************************/

/*****************************************************/
//��������, �� ������� ������ ����� �� �������, ��� �������� � ����� ������������
/*****************************************************/
void check_current_index_is_presented_in_configuration(
                                                         unsigned int* found_new_index_tmp,
                                                                  int* add_filter_point,
                                                                  /*EL_FILTER_STRUCT el_filter[],*/
                                                                  int plus_minus,
                                                                  int number_general_function,
                                                                  int number_mtz_function,
                                                                  int number_mtz04_function,
                                                                  int number_zdz_function,
                                                                  int number_zz_function,
                                                                  int number_tznp_function,
                                                                  int number_apv_function,
                                                                  int number_achr_chapv_function,
                                                                  int number_urov_function,
                                                                  int number_zop_function,
                                                                  int number_Umin_function,
                                                                  int number_Umax_function,
                                                                  int number_UP_function,
                                                                  int number_vmp_function,
                                                                  int number_el_function
                                                        )
{
  if(plus_minus == 1)
  {
    if (current_ekran.index_position < number_general_function) *found_new_index_tmp = 1;
    else
    {
      if (current_ekran.index_position < (number_general_function + number_mtz_function))
      {
        if ((current_settings.configuration & (1<<MTZ_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_mtz04_function))
      {
        if ((current_settings.configuration & (1<<MTZ04_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_mtz04_function;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function))
      {
        if ((current_settings.configuration & (1<<ZDZ_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function))
      {
        if ((current_settings.configuration & (1<<ZZ_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function))
      {
        if ((current_settings.configuration & (1<<TZNP_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function))
      {
        if ((current_settings.configuration & (1<<APV_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function))
      {
        if ((current_settings.configuration & (1<<ACHR_CHAPV_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function + number_urov_function))
      {
        if ((current_settings.configuration & (1<<UROV_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function + number_urov_function;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function + number_urov_function + number_zop_function))
      {
        if ((current_settings.configuration & (1<<ZOP_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function + number_urov_function + number_zop_function;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function))
      {
        if ((current_settings.configuration & (1<<UMIN_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function + number_Umax_function))
      {
        if ((current_settings.configuration & (1<<UMAX_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function + number_Umax_function;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function + number_Umax_function + number_UP_function))
      {
        if ((current_settings.configuration & (1<<UP_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function + number_Umax_function + number_UP_function;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function + number_Umax_function + number_UP_function + number_vmp_function))
      {
        if ((current_settings.configuration & (1<<VMP_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function + number_Umax_function + number_UP_function + number_vmp_function;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function + number_Umax_function + number_UP_function + number_vmp_function + number_el_function))
      {
        if ((current_settings.configuration & (1<<EL_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function + number_Umax_function + number_UP_function + number_vmp_function + number_el_function;
      }
    }

    if ((current_settings.control_zz & CTR_ZZ1_TYPE) != 0)  
    {
      unsigned int i = 0;
      while (
             (*found_new_index_tmp == 1) &&
             (add_filter_point[i]  >= 0)
            )
      {
        if (current_ekran.index_position == add_filter_point[i])
        {
          *found_new_index_tmp = 0;
          current_ekran.index_position++;
        }
        else i++;
      }
    }
    
//    for (unsigned int i = 0; i < NUMBER_DEFINED_ELEMENTS; i++)
//    {
//      if (
//          (el_filter[i].present != 0) &&
//          (current_ekran.index_position >= (el_filter[i].start_index + el_filter[i].number_per_index*el_filter[i].real_number)) &&
//          (current_ekran.index_position <=  el_filter[i].stop_index)
//         )
//      {
//        *found_new_index_tmp = 0;
//        current_ekran.index_position++;
//        break; //����� �� �����
//      }
//    }
  }
  else
  {
    if (current_ekran.index_position < number_general_function) *found_new_index_tmp = 1;
    else
    {
      if (current_ekran.index_position < (number_general_function + number_mtz_function))
      {
        if ((current_settings.configuration & (1<<MTZ_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function - 1;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_mtz04_function))
      {
        if ((current_settings.configuration & (1<<MTZ04_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function - 1;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function))
      {
        if ((current_settings.configuration & (1<<ZDZ_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_mtz04_function - 1;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function))
      {
        if ((current_settings.configuration & (1<<ZZ_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function - 1;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function))
      {
        if ((current_settings.configuration & (1<<TZNP_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function - 1;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function))
      {
        if ((current_settings.configuration & (1<<APV_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function - 1;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function))
      {
        if ((current_settings.configuration & (1<<ACHR_CHAPV_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + - 1;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function + number_urov_function))
      {
        if ((current_settings.configuration & (1<<UROV_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function - 1;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function + number_urov_function + number_zop_function))
      {
        if ((current_settings.configuration & (1<<ZOP_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function + number_urov_function - 1;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function))
      {
        if ((current_settings.configuration & (1<<UMIN_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function + number_urov_function + number_zop_function - 1;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function + number_Umax_function))
      {
        if ((current_settings.configuration & (1<<UMAX_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function - 1;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function + number_Umax_function + number_UP_function))
      {
        if ((current_settings.configuration & (1<<UP_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function + number_Umax_function - 1;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function + number_Umax_function + number_UP_function + number_vmp_function))
      {
        if ((current_settings.configuration & (1<<VMP_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function + number_Umax_function + number_UP_function - 1;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function + number_Umax_function + number_UP_function + number_vmp_function + number_el_function))
      {
        if ((current_settings.configuration & (1<<EL_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_mtz04_function + number_zdz_function + number_zz_function + number_tznp_function + number_apv_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function + number_Umax_function + number_UP_function + number_vmp_function - 1;
      }
    }

    if ((current_settings.control_zz & CTR_ZZ1_TYPE) != 0)
    {
      unsigned int i = 0;
      while (
             (*found_new_index_tmp == 1) &&
             (add_filter_point[i]  >= 0)
            )
      {
        if (current_ekran.index_position == add_filter_point[i])
        {
          *found_new_index_tmp = 0;
          current_ekran.index_position--;
        }
        else i++;
      }
    }
    
//    for (unsigned int i = 0; i < NUMBER_DEFINED_ELEMENTS; i++)
//    {
//      if (
//          (el_filter[i].present != 0) &&
//          (current_ekran.index_position >= (el_filter[i].start_index + el_filter[i].number_per_index*el_filter[i].real_number)) &&
//          (current_ekran.index_position <=  el_filter[i].stop_index)
//         )
//      {
//        *found_new_index_tmp = 0;
//        current_ekran.index_position--;
//        break; //����� �� �����
//      }
//    }
  }
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
