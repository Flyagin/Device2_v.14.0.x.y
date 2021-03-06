#ifndef __CONSTANTS_TRANSFER_FUNCTIONS__
#define __CONSTANTS_TRANSFER_FUNCTIONS__

enum _index_ml_td
{
  EKRAN_LIST_TF_FOR_RANGUVANNJA  = (EKRAN_RANGUVANNJA_D_NOT16 + 1),
  EKRAN_LIST_SOURCE_TF1,

  _NEXT_EKRAN_AFTER_ALL_TF_EKRANS = (EKRAN_LIST_SOURCE_TF1 + NUMBER_TRANSFER_FUNCTIONS)
};

#define MAX_ROW_FOR_LIST_TF                      NUMBER_TRANSFER_FUNCTIONS/*((int)current_settings.number_defined_tf)*/

enum _index_ml_type_source_td
{
  INDEX_ML_LIST_SOURCE_INPUT_TF = 0,
  INDEX_ML_LIST_SOURCE_OUTPUT_TF,
  
  MAX_ROW_LIST_SOURCE_TF
}; 

#endif 
