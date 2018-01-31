
#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 256
//��������� bit � ����� ������
#define BEGIN_ADR_BIT 50000

//�������� ������� � ����� ������
#define END_ADR_REGISTER 293
//�������� bit � ����� ������
#define END_ADR_BIT 50599

int privateACMDSmallGetReg2(int adrReg);
int privateACMDSmallGetBit2(int adrBit);

int getACMDSmallModbusRegister(int);//�������� ���������� ��������
int getACMDSmallModbusBit(int);//�������� ���������� ����
int setACMDSmallModbusRegister(int, int);//�������� �������
int setACMDSmallModbusBit(int, int);//�������� ���

void preACMDSmallReadAction(void);//action �� ������
void preACMDSmallWriteAction(void);//action �� ������
int  postACMDSmallWriteAction(void);//action ����� ������

int  cmdFunc000(int inOffset, int *outMaska, int *dvMaska, int actControl);
void loadACMDSmallActualDataBit(int cmdSwitch, int beginOffset, int endOffset);
unsigned int encoderValidN_BIGACMD(int offsetCMD, int *validCMD, int actControl);
unsigned int encoderValidN_SMALLACMD(int offsetCMD, int *validCMD);
int validBazaN_BIGACMD(unsigned short dataReg, int actControl);
int writeACMDSmallActualDataBit(int offset, int dataBit);

#define CLRACT_CONTROL  0

COMPONENT_OBJ *acmdsmallcomponent;
int cmdFunc000(int inOffset, int *outMaska, int *dvMaska, int actControl)
{
  int isValid = 1;
  (*outMaska) = -1;
  switch(inOffset)//��� ������ ����� ������ modbus
  {
  case 0:
    (*outMaska) = RANG_1_GRUPA_USTAVOK;
    (*dvMaska)  = RANG_SMALL_1_GRUPA_USTAVOK;
    break;
  case 1:
    (*outMaska) = RANG_2_GRUPA_USTAVOK;
    (*dvMaska)  = RANG_SMALL_2_GRUPA_USTAVOK;
    break;
  case 2:
    (*outMaska) = RANG_3_GRUPA_USTAVOK;
    (*dvMaska)  = RANG_SMALL_3_GRUPA_USTAVOK;
    break;
  case 3:
    (*outMaska) = RANG_4_GRUPA_USTAVOK;
    (*dvMaska)  = RANG_SMALL_4_GRUPA_USTAVOK;
    break;

//  int count_bit = 3;
#define MTZ_CONFIGURATION_BEGIN 16
  case MTZ_CONFIGURATION_BEGIN:
    (*outMaska) = RANG_BLOCK_MTZ1;
    (*dvMaska) = RANG_SMALL_BLOCK_MTZ1;
    break;
  case 17:
    (*outMaska) = RANG_MTZ1;
//        (*dvMaska) =
    break;
  case 18:
    (*outMaska) = RANG_PO_MTZ1;
//        (*dvMaska) =
    break;
  case 19:
    (*outMaska) = RANG_PO_MTZPN1;
//        (*dvMaska) =
    break;
  case 20:
    (*outMaska) = RANG_PO_MTZN1_VPERED;
//        (*dvMaska) =
    break;
  case 21:
    (*outMaska) = RANG_PO_MTZN1_NAZAD;
//        (*dvMaska) =
    break;
  case 22:
    (*outMaska) = RANG_SECTOR_VPERED_MTZN1;
//        (*dvMaska) =
    break;
  case 23:
    (*outMaska) = RANG_SECTOR_NAZAD_MTZN1;
//        (*dvMaska) =
    break;
  case 24:
    (*outMaska) = RANG_PO_U_MTZPN1;
//        (*dvMaska) =
    break;

//  count_bit = 3;
  case 32:
    (*outMaska) = RANG_BLOCK_MTZ2;
    (*dvMaska) = RANG_SMALL_BLOCK_MTZ2;
    break;
  case 33:
    (*outMaska) = RANG_MTZ2;
//        (*dvMaska) =
    break;
  case 34:
    (*outMaska) = RANG_PO_MTZ2;
//        (*dvMaska) =
    break;
  case 35:
    (*outMaska) = RANG_PO_MTZPN2;
//        (*dvMaska) =
    break;
  case 36:
    (*outMaska) = RANG_PO_MTZN2_VPERED;
//        (*dvMaska) =
    break;
  case 37:
    (*outMaska) = RANG_PO_MTZN2_NAZAD;
//        (*dvMaska) =
    break;
  case 38:
    (*outMaska) = RANG_SECTOR_VPERED_MTZN2;
//        (*dvMaska) =
    break;
  case 39:
    (*outMaska) = RANG_SECTOR_NAZAD_MTZN2;
//        (*dvMaska) =
    break;
  case 40:
    (*outMaska) = RANG_PO_U_MTZPN2;
//        (*dvMaska) =
    break;
  case 41:
    (*outMaska) = RANG_BLOCK_USK_MTZ2;
    (*dvMaska) = RANG_SMALL_BLOCK_USK_MTZ2;
    break;

//  count_bit = 3;
  case 48:
    (*outMaska) = RANG_BLOCK_MTZ3;
    (*dvMaska) = RANG_SMALL_BLOCK_MTZ3;
    break;
  case 49:
    (*outMaska) = RANG_MTZ3;
//        (*dvMaska) =
    break;
  case 50:
    (*outMaska) = RANG_PO_MTZ3;
//        (*dvMaska) =
    break;
  case 51:
    (*outMaska) = RANG_PO_MTZPN3;
//        (*dvMaska) =
    break;
  case 52:
    (*outMaska) = RANG_PO_MTZN3_VPERED;
//        (*dvMaska) =
    break;
  case 53:
    (*outMaska) = RANG_PO_MTZN3_NAZAD;
//        (*dvMaska) =
    break;
  case 54:
    (*outMaska) = RANG_SECTOR_VPERED_MTZN3;
//        (*dvMaska) =
    break;
  case 55:
    (*outMaska) = RANG_SECTOR_NAZAD_MTZN3;
//        (*dvMaska) =
    break;
  case 56:
    (*outMaska) = RANG_PO_U_MTZPN3;
//        (*dvMaska) =
    break;

//  count_bit = 3;
  case 64:
    (*outMaska) = RANG_BLOCK_MTZ4;
    (*dvMaska) = RANG_SMALL_BLOCK_MTZ4;
    break;
  case 65:
    (*outMaska) = RANG_MTZ4;
//        (*dvMaska) =
    break;
  case 66:
    (*outMaska) = RANG_PO_MTZ4;
//        (*dvMaska) =
    break;
  case 67:
    (*outMaska) = RANG_PO_MTZPN1;
//        (*dvMaska) =
    break;
  case 68:
    (*outMaska) = RANG_PO_MTZN4_VPERED;
//        (*dvMaska) =
    break;
  case 69:
    (*outMaska) = RANG_PO_MTZN4_NAZAD;
//        (*dvMaska) =
    break;
  case 70:
    (*outMaska) = RANG_SECTOR_VPERED_MTZN4;
//        (*dvMaska) =
    break;
  case 71:
    (*outMaska) = RANG_SECTOR_NAZAD_MTZN4;
//        (*dvMaska) =
    break;
#define MTZ_CONFIGURATION_END 72
  case MTZ_CONFIGURATION_END:
    (*outMaska) = RANG_PO_U_MTZPN4;
//        (*dvMaska) =
    break;

//  count_bit = 3;
#define MTZ04_CONFIGURATION_BEGIN 80
  case MTZ04_CONFIGURATION_BEGIN:
    (*outMaska) = RANG_BLOCK_MTZ04_1;
    (*dvMaska) = RANG_SMALL_BLOCK_MTZ04_1;
    break;
  case 81:
    (*outMaska) = RANG_MTZ04_1;
//        (*dvMaska) =
    break;
  case 82:
    (*outMaska) = RANG_PO_MTZ04_1;
//        (*dvMaska) =
    break;
  case 83:
    (*outMaska) = RANG_BLOCK_MTZ04_2;
    (*dvMaska) = RANG_SMALL_BLOCK_MTZ04_2;
    break;
  case 84:
    (*outMaska) = RANG_MTZ04_2;
//        (*dvMaska) =
    break;
  case 85:
    (*outMaska) = RANG_PO_MTZ04_2;
//        (*dvMaska) =
    break;
#define MTZ04_CONFIGURATION_END 86
  case MTZ04_CONFIGURATION_END:
    (*outMaska) = RANG_BLOCK_USK_MTZ04_2;
    (*dvMaska) = RANG_SMALL_BLOCK_USK_MTZ04_2;
    break;


//  count_bit = 3;
#define ZDZ_CONFIGURATION_BEGIN 112
  case ZDZ_CONFIGURATION_BEGIN:
    (*outMaska) = RANG_BLOCK_ZDZ;
    (*dvMaska)  = RANG_SMALL_BLOCK_ZDZ;
    break;
  case 113:
    (*outMaska) = RANG_PUSK_ZDZ_VID_DV;
    (*dvMaska)  = RANG_SMALL_PUSK_ZDZ_VID_DV;
    break;
  case 114:
    (*outMaska) = RANG_PO_ZDZ;
//        (*dvMaska) =
    break;
  case 115:
    (*outMaska) = RANG_ZDZ;
//        (*dvMaska) =
    break;
  case 116:
    (*outMaska) = RANG_LIGHT_ZDZ_FROM_DV;
//        (*dvMaska) =
    break;
  case 117:
    (*outMaska) = RANG_LIGHT_ZDZ_FROM_OVD1;
//        (*dvMaska) =
    break;
  case 118:
    (*outMaska) = RANG_LIGHT_ZDZ_FROM_OVD2;
//        (*dvMaska) =
    break;
#define ZDZ_CONFIGURATION_END 119
  case ZDZ_CONFIGURATION_END:
    (*outMaska) = RANG_LIGHT_ZDZ_FROM_OVD3;
//        (*dvMaska) =
    break;


//  count_bit = 5;
#define ZZ_CONFIGURATION_BEGIN 128
  case ZZ_CONFIGURATION_BEGIN:
    (*outMaska) = RANG_BLOCK_NZZ;
    (*dvMaska) = RANG_SMALL_BLOCK_NZZ;
    break;
  case 129:
    (*outMaska) = RANG_PO_NZZ;
//        (*dvMaska) =
    if(edition_settings.control_zz&(1<<INDEX_ML_CTR_ZZ1_TYPE_BIT)) isValid = 0;
    break;
  case 130:
    (*outMaska) = RANG_NZZ;
//        (*dvMaska) =
    if(edition_settings.control_zz&(1<<INDEX_ML_CTR_ZZ1_TYPE_BIT)) isValid = 0;
    break;
  case 131:
    (*outMaska) = RANG_PO_3I0;
//        (*dvMaska) =
    break;
  case 132:
    (*outMaska) = RANG_3I0;
//        (*dvMaska) =
    break;

//  count_bit = 3;
  case 135:
    (*outMaska) = RANG_PO_3U0;
//        (*dvMaska) =
    break;
  case 136:
    (*outMaska) = RANG_3U0;
//        (*dvMaska) =
    break;
#define ZZ_CONFIGURATION_END 137
  case ZZ_CONFIGURATION_END:
    (*outMaska) = RANG_SECTOR_NZZ;
//        (*dvMaska) =
    if(edition_settings.control_zz&(1<<INDEX_ML_CTR_ZZ1_TYPE_BIT)) isValid = 0;
    break;

//  count_bit = 3;
#define TZNP_CONFIGURATION_BEGIN 144
  case TZNP_CONFIGURATION_BEGIN:
    (*outMaska) = RANG_BLOCK_TZNP1;
    (*dvMaska) = RANG_SMALL_BLOCK_TZNP1;
    break;
  case 145:
    (*outMaska) = RANG_PO_3I0_TZNP1_VPERED;
//        (*dvMaska) =
    break;
  case 146:
    (*outMaska) = RANG_PO_3I0_TZNP1_NAZAD;
//        (*dvMaska) =
    break;
  case 147:
    (*outMaska) = RANG_PO_3U0_TZNP1_VPERED;
//        (*dvMaska) =
    break;
  case 148:
    (*outMaska) = RANG_PO_3U0_TZNP1_NAZAD;
//        (*dvMaska) =
    break;
  case 149:
    (*outMaska) = RANG_PO_TZNP1_VPERED;
//        (*dvMaska) =
    break;
  case 150:
    (*outMaska) = RANG_PO_TZNP1_NAZAD;
//        (*dvMaska) =
    break;
  case 151:
    (*outMaska) = RANG_SECTOR_TZNP1_VPERED;
//        (*dvMaska) =
    break;
  case 152:
    (*outMaska) = RANG_SECTOR_TZNP1_NAZAD;
//        (*dvMaska) =
    break;
  case 153:
    (*outMaska) = RANG_TZNP1;
//        (*dvMaska) =
    break;
  case 154:
    (*outMaska) = RANG_BLOCK_TZNP2;
    (*dvMaska) = RANG_SMALL_BLOCK_TZNP2;
    break;
  case 155:
    (*outMaska) = RANG_PO_3I0_TZNP2_VPERED;
//        (*dvMaska) =
    break;
  case 156:
    (*outMaska) = RANG_PO_3I0_TZNP2_NAZAD;
//        (*dvMaska) =
    break;
  case 157:
    (*outMaska) = RANG_PO_3U0_TZNP2_VPERED;
//        (*dvMaska) =
    break;
  case 158:
    (*outMaska) = RANG_PO_3U0_TZNP2_NAZAD;
//        (*dvMaska) =
    break;
  case 159:
    (*outMaska) = RANG_PO_TZNP2_VPERED;
//        (*dvMaska) =
    break;
  case 160:
    (*outMaska) = RANG_PO_TZNP2_NAZAD;
//        (*dvMaska) =
    break;
  case 161:
    (*outMaska) = RANG_SECTOR_TZNP2_VPERED;
//        (*dvMaska) =
    break;
  case 162:
    (*outMaska) = RANG_SECTOR_TZNP2_NAZAD;
//        (*dvMaska) =
    break;
  case 163:
    (*outMaska) = RANG_TZNP2;
//        (*dvMaska) =
    break;
  case 164:
    (*outMaska) = RANG_BLOCK_TZNP3;
    (*dvMaska) = RANG_SMALL_BLOCK_TZNP3;
    break;
  case 165:
    (*outMaska) = RANG_PO_3I0_TZNP3_VPERED;
//        (*dvMaska) =
    break;
  case 166:
    (*outMaska) = RANG_PO_3I0_TZNP3_NAZAD;
//        (*dvMaska) =
    break;
  case 167:
    (*outMaska) = RANG_PO_3U0_TZNP3_VPERED;
//        (*dvMaska) =
    break;
  case 168:
    (*outMaska) = RANG_PO_3U0_TZNP3_NAZAD;
//        (*dvMaska) =
    break;
  case 169:
    (*outMaska) = RANG_PO_TZNP3_VPERED;
//        (*dvMaska) =
    break;
  case 170:
    (*outMaska) = RANG_PO_TZNP3_NAZAD;
//        (*dvMaska) =
    break;
  case 171:
    (*outMaska) = RANG_SECTOR_TZNP3_VPERED;
//        (*dvMaska) =
    break;
  case 172:
    (*outMaska) = RANG_SECTOR_TZNP3_NAZAD;
//        (*dvMaska) =
    break;
#define TZNP_CONFIGURATION_END 173
  case TZNP_CONFIGURATION_END:
    (*outMaska) = RANG_TZNP3;
//        (*dvMaska) =
    break;

//  count_bit = 3;
#define ZOP_CONFIGURATION_BEGIN 176
  case ZOP_CONFIGURATION_BEGIN:
    (*outMaska) = RANG_BLOCK_ZOP;
    (*dvMaska) = RANG_SMALL_BLOCK_ZOP;
    break;
  case 177:
    (*outMaska) = RANG_ZOP;
//        (*dvMaska) =
    break;
#define ZOP_CONFIGURATION_END 178
  case ZOP_CONFIGURATION_END:
    (*outMaska) = RANG_PO_ZOP;
//        (*dvMaska) =
    break;

//  count_bit = 3;
#define UMIN_CONFIGURATION_BEGIN 192
  case UMIN_CONFIGURATION_BEGIN:
    (*outMaska) = RANG_BLOCK_UMIN1;
    (*dvMaska) = RANG_SMALL_BLOCK_UMIN1;
    break;
  case 193:
    (*outMaska) = RANG_PO_UBLK_UMIN1;
//        (*dvMaska) =
    break;
  case 194:
    (*outMaska) = RANG_PO_IBLK_UMIN1;
//        (*dvMaska) =
    break;
  case 195:
    (*outMaska) = RANG_UMIN1;
//        (*dvMaska) =
    break;
  case 196:
    (*outMaska) = RANG_PO_UMIN1;
//        (*dvMaska) =
    break;
  case 197:
    (*outMaska) = RANG_BLOCK_UMIN2;
    (*dvMaska)  = RANG_SMALL_BLOCK_UMIN2;
    break;
  case 198:
    (*outMaska) = RANG_PO_UBLK_UMIN2;
//        (*dvMaska) =
    break;
  case 199:
    (*outMaska) = RANG_PO_IBLK_UMIN2;
//        (*dvMaska) =
    break;
  case 200:
    (*outMaska) = RANG_UMIN2;
//        (*dvMaska) =
    break;
  case 201:
    (*outMaska) = RANG_PO_UMIN2;
//        (*dvMaska) =
    break;
  case 202:
    (*outMaska) = RANG_START_UMIN1;
    (*dvMaska)  = RANG_SMALL_START_UMIN1;
    break;
#define UMIN_CONFIGURATION_END 203
  case UMIN_CONFIGURATION_END:
    (*outMaska) = RANG_START_UMIN2;
    (*dvMaska) = RANG_SMALL_START_UMIN2;
    break;

//  count_bit = 3;
#define UMAX_CONFIGURATION_BEGIN 208
  case UMAX_CONFIGURATION_BEGIN:
    (*outMaska) = RANG_BLOCK_UMAX1;
    (*dvMaska)  = RANG_SMALL_BLOCK_UMAX1;
    break;
  case 209:
    (*outMaska) = RANG_UMAX1;
//        (*dvMaska) =
    break;
  case 210:
    (*outMaska) = RANG_PO_UMAX1;
//        (*dvMaska) =
    break;
  case 211:
    (*outMaska) = RANG_BLOCK_UMAX2;
    (*dvMaska)  = RANG_SMALL_BLOCK_UMAX2;
    break;
  case 212:
    (*outMaska) = RANG_UMAX2;
//        (*dvMaska) =
    break;
#define UMAX_CONFIGURATION_END 213
  case UMAX_CONFIGURATION_END:
    (*outMaska) = RANG_PO_UMAX2;
//        (*dvMaska) =
    break;

//  count_bit = 3;
#define APV_CONFIGURATION_BEGIN 288
  case APV_CONFIGURATION_BEGIN:
    (*outMaska) = RANG_STAT_BLK_APV;
    (*dvMaska) = RANG_SMALL_STAT_BLK_APV;
    break;

//  count_bit = 3;
  case 290:
    (*outMaska) = RANG_APV1;
//        (*dvMaska) =
    break;
  case 291:
    (*outMaska) = RANG_APV2;
//        (*dvMaska) =
    break;
  case 292:
    (*outMaska) = RANG_APV3;
//        (*dvMaska) =
    break;
  case 293:
    (*outMaska) = RANG_APV4;
//        (*dvMaska) =
    break;
#define APV_CONFIGURATION_END 294
  case APV_CONFIGURATION_END:
    (*outMaska) = RANG_APV_WORK;
//        (*dvMaska) =
    break;

//  count_bit = 5;
#define UROV_CONFIGURATION_BEGIN 304
  case UROV_CONFIGURATION_BEGIN:
    (*outMaska) = RANG_PUSK_UROV_VID_DV;
    (*dvMaska) = RANG_SMALL_PUSK_UROV_VID_DV;
    break;
  case 305:
    (*outMaska) = RANG_UROV1;
//        (*dvMaska) =
    break;
  case 306:
    (*outMaska) = RANG_UROV2;
//        (*dvMaska) =
    break;
#define UROV_CONFIGURATION_END 307
  case UROV_CONFIGURATION_END:
    (*outMaska) = RANG_PO_UROV;
//        (*dvMaska) =
    break;

//  count_bit = 1;
#define ACHR_CHAPV_CONFIGURATION_BEGIN 368
  case ACHR_CHAPV_CONFIGURATION_BEGIN:
    (*outMaska) = RANG_ACHR_CHAPV_VID_DV;
    (*dvMaska) = RANG_SMALL_ACHR_CHAPV_VID_DV;
    break;
  case 369:
    (*outMaska) = RANG_BLOCK_ACHR1;
    (*dvMaska) = RANG_SMALL_BLOCK_ACHR1;
    break;
  case 370:
    (*outMaska) = RANG_BLOCK_ACHR2;
    (*dvMaska) = RANG_SMALL_BLOCK_ACHR2;
    break;
  case 371:
    (*outMaska) = RANG_VN_BLOCK_CHAPV;
//        (*dvMaska) =
    break;
  case 372:
    (*outMaska) = RANG_PO_ACHR1;
//        (*dvMaska) =
    break;
  case 373:
    (*outMaska) = RANG_PO_ACHR2;
//        (*dvMaska) =
    break;
  case 374:
    (*outMaska) = RANG_ACHR_CHAPV1;
//        (*dvMaska) =
    break;
  case 375:
    (*outMaska) = RANG_ACHR_CHAPV2;
//        (*dvMaska) =
    break;
  case 376:
    (*outMaska) = RANG_RAZR_CHAPV;
//        (*dvMaska) =
    break;
  case 377:
    (*outMaska) = RANG_PO_CHAPV1;
//        (*dvMaska) =
    break;
#define ACHR_CHAPV_CONFIGURATION_END 378
  case ACHR_CHAPV_CONFIGURATION_END:
    (*outMaska) = RANG_PO_CHAPV2;
//        (*dvMaska) =
    break;

//IF ������� 384-407

//  count_bit = 8;
#define EL_CONFIGURATION_BEGIN 432
  case EL_CONFIGURATION_BEGIN:
    (*outMaska) = RANG_DF1_IN;
    (*dvMaska) = RANG_SMALL_DF1_IN;
    if(actControl==1) isValid = 0;
    break;
  case 433:
    (*outMaska) = RANG_DF2_IN;
    (*dvMaska) = RANG_SMALL_DF2_IN;
    if(actControl==2) isValid = 0;
    break;
  case 434:
    (*outMaska) = RANG_DF3_IN;
    (*dvMaska) = RANG_SMALL_DF3_IN;
    if(actControl==3) isValid = 0;
    break;
  case 435:
    (*outMaska) = RANG_DF4_IN;
    (*dvMaska) = RANG_SMALL_DF4_IN;
    if(actControl==4) isValid = 0;
    break;
  case 436:
    (*outMaska) = RANG_DF5_IN;
    (*dvMaska) = RANG_SMALL_DF5_IN;
    if(actControl==5) isValid = 0;
    break;
  case 437:
    (*outMaska) = RANG_DF6_IN;
    (*dvMaska) = RANG_SMALL_DF6_IN;
    if(actControl==6) isValid = 0;
    break;
  case 438:
    (*outMaska) = RANG_DF7_IN;
    (*dvMaska) = RANG_SMALL_DF7_IN;
    if(actControl==7) isValid = 0;
    break;
  case 439:
    (*outMaska) = RANG_DF8_IN;
    (*dvMaska) = RANG_SMALL_DF8_IN;
    if(actControl==8) isValid = 0;
    break;

//  count_bit = 8;
  case 448:
    (*outMaska) = RANG_DF1_OUT;
//        (*dvMaska) =
    if(actControl==1) isValid = 0;
    break;
  case 449:
    (*outMaska) = RANG_DF2_OUT;
//        (*dvMaska) =
    if(actControl==2) isValid = 0;
    break;
  case 450:
    (*outMaska) = RANG_DF3_OUT;
//        (*dvMaska) =
    if(actControl==3) isValid = 0;
    break;
  case 451:
    (*outMaska) = RANG_DF4_OUT;
//        (*dvMaska) =
    if(actControl==4) isValid = 0;
    break;
  case 452:
    (*outMaska) = RANG_DF5_OUT;
//        (*dvMaska) =
    if(actControl==5) isValid = 0;
    break;
  case 453:
    (*outMaska) = RANG_DF6_OUT;
//        (*dvMaska) =
    if(actControl==6) isValid = 0;
    break;
  case 454:
    (*outMaska) = RANG_DF7_OUT;
//        (*dvMaska) =
    if(actControl==7) isValid = 0;
    break;
  case 455:
    (*outMaska) = RANG_DF8_OUT;
//        (*dvMaska) =
    if(actControl==8) isValid = 0;
    break;

//  count_bit = 12;
  case 464:
    (*outMaska) = RANG_DT1_SET;
    (*dvMaska) = RANG_SMALL_DT1_SET;
    if(actControl==1) isValid = 0;
    break;
  case 465:
    (*outMaska) = RANG_DT1_RESET;
    (*dvMaska) = RANG_SMALL_DT1_RESET;
    if(actControl==1) isValid = 0;
    break;
  case 466:
    (*outMaska) = RANG_DT2_SET;
    (*dvMaska) = RANG_SMALL_DT2_SET;
    if(actControl==2) isValid = 0;
    break;
  case 467:
    (*outMaska) = RANG_DT2_RESET;
    (*dvMaska) = RANG_SMALL_DT2_RESET;
    if(actControl==2) isValid = 0;
    break;
  case 468:
    (*outMaska) = RANG_DT3_SET;
    (*dvMaska) = RANG_SMALL_DT3_SET;
    if(actControl==3) isValid = 0;
    break;
  case 469:
    (*outMaska) = RANG_DT3_RESET;
    (*dvMaska) = RANG_SMALL_DT3_RESET;
    if(actControl==3) isValid = 0;
    break;
  case 470:
    (*outMaska) = RANG_DT4_SET;
    (*dvMaska) = RANG_SMALL_DT4_SET;
    if(actControl==4) isValid = 0;
    break;
  case 471:
    (*outMaska) = RANG_DT4_RESET;
    (*dvMaska) = RANG_SMALL_DT4_RESET;
    if(actControl==4) isValid = 0;
    break;
  case 472:
    (*outMaska) = RANG_DT1_OUT;
//        (*dvMaska) =
    if(actControl==1) isValid = 0;
    break;
  case 473:
    (*outMaska) = RANG_DT2_OUT;
//        (*dvMaska) =
    if(actControl==2) isValid = 0;
    break;
  case 474:
    (*outMaska) = RANG_DT3_OUT;
//        (*dvMaska) =
    if(actControl==3) isValid = 0;
    break;
  case 475:
    (*outMaska) = RANG_DT4_OUT;
//        (*dvMaska) =
    if(actControl==4) isValid = 0;
    break;

//  count_bit = 40;
  case 480:
    (*outMaska) = RANG_D_AND1;
//        (*dvMaska) =
    break;
  case 481:
    (*outMaska) = RANG_D_AND2;
//        (*dvMaska) =
    break;
  case 482:
    (*outMaska) = RANG_D_AND3;
//        (*dvMaska) =
    break;
  case 483:
    (*outMaska) = RANG_D_AND4;
//        (*dvMaska) =
    break;
  case 484:
    (*outMaska) = RANG_D_AND5;
//        (*dvMaska) =
    break;
  case 485:
    (*outMaska) = RANG_D_AND6;
//        (*dvMaska) =
    break;
  case 486:
    (*outMaska) = RANG_D_AND7;
//        (*dvMaska) =
    break;
  case 487:
    (*outMaska) = RANG_D_AND8;
//        (*dvMaska) =
    break;
  case 488:
    (*outMaska) = RANG_D_OR1;
//        (*dvMaska) =
    break;
  case 489:
    (*outMaska) = RANG_D_OR2;
//        (*dvMaska) =
    break;
  case 490:
    (*outMaska) = RANG_D_OR3;
//        (*dvMaska) =
    break;
  case 491:
    (*outMaska) = RANG_D_OR4;
//        (*dvMaska) =
    break;
  case 492:
    (*outMaska) = RANG_D_OR5;
//        (*dvMaska) =
    break;
  case 493:
    (*outMaska) = RANG_D_OR6;
//        (*dvMaska) =
    break;
  case 494:
    (*outMaska) = RANG_D_OR7;
//        (*dvMaska) =
    break;
  case 495:
    (*outMaska) = RANG_D_OR8;
//        (*dvMaska) =
    break;
  case 496:
    (*outMaska) = RANG_D_NOT1;
//        (*dvMaska) =
    break;
  case 497:
    (*outMaska) = RANG_D_NOT2;
//        (*dvMaska) =
    break;
  case 498:
    (*outMaska) = RANG_D_NOT3;
//        (*dvMaska) =
    break;
  case 499:
    (*outMaska) = RANG_D_NOT4;
//        (*dvMaska) =
    break;
  case 500:
    (*outMaska) = RANG_D_NOT5;
//        (*dvMaska) =
    break;
  case 501:
    (*outMaska) = RANG_D_NOT6;
//        (*dvMaska) =
    break;
  case 502:
    (*outMaska) = RANG_D_NOT7;
//        (*dvMaska) =
    break;
  case 503:
    (*outMaska) = RANG_D_NOT8;
//        (*dvMaska) =
    break;
  case 504:
    (*outMaska) = RANG_D_NOT9;
//        (*dvMaska) =
    break;
  case 505:
    (*outMaska) = RANG_D_NOT10;
//        (*dvMaska) =
    break;
  case 506:
    (*outMaska) = RANG_D_NOT11;
//        (*dvMaska) =
    break;
  case 507:
    (*outMaska) = RANG_D_NOT12;
//        (*dvMaska) =
    break;
  case 508:
    (*outMaska) = RANG_D_NOT13;
//        (*dvMaska) =
    break;
  case 509:
    (*outMaska) = RANG_D_NOT14;
//        (*dvMaska) =
    break;
  case 510:
    (*outMaska) = RANG_D_NOT15;
//        (*dvMaska) =
    break;
  case 511:
    (*outMaska) = RANG_D_NOT16;
//        (*dvMaska) =
    break;
  case 512:
    (*outMaska) = RANG_D_XOR1;
//        (*dvMaska) =
    break;
  case 513:
    (*outMaska) = RANG_D_XOR2;
//        (*dvMaska) =
    break;
  case 514:
    (*outMaska) = RANG_D_XOR3;
//        (*dvMaska) =
    break;
  case 515:
    (*outMaska) = RANG_D_XOR4;
//        (*dvMaska) =
    break;
  case 516:
    (*outMaska) = RANG_D_XOR5;
//        (*dvMaska) =
    break;
  case 517:
    (*outMaska) = RANG_D_XOR6;
//        (*dvMaska) =
    break;
  case 518:
    (*outMaska) = RANG_D_XOR7;
//        (*dvMaska) =
    break;
#define EL_CONFIGURATION_END 519
  case EL_CONFIGURATION_END:
    (*outMaska) = RANG_D_XOR8;
//        (*dvMaska) =
    break;

//  count_bit = 3;
  case 528:
    (*outMaska) = RANG_VKL_VV;
    (*dvMaska) = RANG_SMALL_VKL_VV;
    break;
  case 529:
    (*outMaska) = RANG_OTKL_VV;
    (*dvMaska) = RANG_SMALL_OTKL_VV;
    break;
  case 530:
    (*outMaska) = RANG_BLOCK_VKL_VV;
    (*dvMaska) = RANG_SMALL_BLOCK_VKL_VV;
    break;

//  count_bit = 15;
  case 532:
    (*outMaska) = RANG_WORK_BO;
//        (*dvMaska) =
    break;
  case 533:
    (*outMaska) = RANG_WORK_BV;
//        (*dvMaska) =
    break;
  case 534:
    (*outMaska) = RANG_STATE_VV;
    (*dvMaska) = RANG_SMALL_STATE_VV;
    break;
  case 535:
    (*outMaska) = RANG_PRYVID_VV;
//        (*dvMaska) =
    break;
  case 536:
    (*outMaska) = RANG_CTRL_VKL;
    (*dvMaska) = RANG_SMALL_CTRL_VKL;
    break;
  case 537:
    (*outMaska) = RANG_CTRL_OTKL;
    (*dvMaska) = RANG_SMALL_CTRL_OTKL;
    break;
  case 538:
    (*outMaska) = RANG_PEREVYSHCHENNJA_Inom_VYMK;
//        (*dvMaska) =
    break;
  case 539:
    (*outMaska) = RANG_KRYTYCHNYJ_RESURS_VYMYKACHA;
//        (*dvMaska) =
    break;
  case 540:
    (*outMaska) = RANG_VYCHERPANYJ_RESURS_VYMYKACHA;
//        (*dvMaska) =
    break;

//  count_bit = 12;
  case 560:
    (*outMaska) = RANG_DEFECT;
//        (*dvMaska) =
    break;
  case 561:
    (*outMaska) = RANG_AVAR_DEFECT;
//        (*dvMaska) =
    break;
  case 562:
    (*outMaska) = RANG_RESET_LEDS;
    (*dvMaska) = RANG_SMALL_RESET_LEDS;
    break;
  case 563:
    (*outMaska) = RANG_RESET_RELES;
    (*dvMaska) = RANG_SMALL_RESET_RELES;
    break;
//  case 564:
//    (*outMaska) = 0;
//        (*dvMaska) =
//    break;

//                  reset_trigger_function_from_interface |= (1 << type_interface); USB_RECUEST/RS485_RECUEST
//  case 565:
//    (*outMaska) = RANG_SETTINGS_CHANGED;
//        (*dvMaska) =
  /*
        if ((information_about_restart_counter & (1 << type_interface)) != 0)
        {
            output_array[(BIT_MA_RESET_RESURS_VYMYKACHA - BIT_MA_CURRENT_AF_BASE) >> 4] |=
            (0x1 << ((BIT_MA_RESET_RESURS_VYMYKACHA - BIT_MA_CURRENT_AF_BASE) & 0xf));
        }

        restart_counter = 0xff; //������ ��� �������� ������� ��������� � ������� �������
  */

//    break;
//  case 566:
//    (*outMaska) = 0;
//        (*dvMaska) =
//    break;
//        (*outMaska) = RANG_SETTINGS_CHANGED;
//  case 567:
//    (*outMaska) = 0;
//        (*dvMaska) =
//    break;
  /*

                    //��������� ��������� ���
                    if(type_interface == USB_RECUEST) error = set_new_settings_from_interface(2);
                    else if(type_interface ==  RS485_RECUEST) error = set_new_settings_from_interface(3);
  */
//  case 568:
//    (*outMaska) = 0;
//        (*dvMaska) =
//    break;
  /*
        unsigned int password_set_tmp;
        if (type_interface == USB_RECUEST) password_set_tmp = password_set_USB;
        else if (type_interface == RS485_RECUEST) password_set_tmp = password_set_RS485;

        if (password_set_tmp != 0)
        {
          output_array[(BIT_MA_PASSWORD_SET - BIT_MA_CURRENT_AF_BASE) >> 4] |=
            (0x1 << ((BIT_MA_PASSWORD_SET - BIT_MA_CURRENT_AF_BASE) & 0xf));
        }
  */
  case 569:
    (*outMaska) = RANG_MISCEVE_DYSTANCIJNE;
    (*dvMaska) = RANG_SMALL_MISCEVE_DYSTANCIJNE;
    break;
  case 570:
    (*outMaska) = RANG_WORK_A_REJESTRATOR;
//        (*dvMaska) =
    break;
  case 571:
    (*outMaska) = RANG_WORK_D_REJESTRATOR;
//        (*dvMaska) =
    break;

//  count_bit = 1;
  case 576:
    (*outMaska) = RANG_OTKL_VID_ZOVN_ZAHYSTIV;
    (*dvMaska)  = RANG_SMALL_OTKL_VID_ZOVN_ZAHYSTIV;
    break;
  case 577:
    (*outMaska) = RANG_ERROR_CONF_EL;
//        (*dvMaska) =
    break;

//  count_bit = 5;
  case 595:
    (*outMaska) = RANG_VIDKL_VID_ZAKHYSTIV;
//        (*dvMaska) =
    break;
  case 596:
    (*outMaska) = RANG_BLK_GRUP_USTAVOK_VID_ZACHYSTIV;
//        (*dvMaska) =
    break;
  /*
  //BIT_MA_BLK_GRUP_USTAVOK_VID_ZACHYSTIV
  //    case 565:
  //        (*outMaska) = 0;
  //        (*dvMaska) =
  //          break;
  */
//BIT_MA_INVERS_DV_GRUPA_USTAVOK

  case 597:
    (*outMaska) = RANG_INVERS_DV_GRUPA_USTAVOK;
//        (*dvMaska) =
    break;
  case 598:
    (*outMaska) = RANG_READY_TU;
//        (*dvMaska) =
    break;
  case 599:
    (*outMaska) = RANG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV;
    (*dvMaska) = RANG_SMALL_RESET_BLOCK_READY_TU_VID_ZAHYSTIV;
    break;
  }//switch
  if((*outMaska)!=-1)
  {
    if(inOffset>=MTZ_CONFIGURATION_BEGIN && inOffset<=MTZ_CONFIGURATION_END)
      if(!(edition_settings.configuration&(1<<MTZ_BIT_CONFIGURATION))) isValid = 0;

    if(inOffset>=MTZ04_CONFIGURATION_BEGIN && inOffset<=MTZ04_CONFIGURATION_END)
      if(!(edition_settings.configuration&(1<<MTZ04_BIT_CONFIGURATION))) isValid = 0;

    if(inOffset>=ZDZ_CONFIGURATION_BEGIN && inOffset<=ZDZ_CONFIGURATION_END)
      if(!(edition_settings.configuration&(1<<ZDZ_BIT_CONFIGURATION))) isValid = 0;

    if(inOffset>=ZZ_CONFIGURATION_BEGIN && inOffset<=ZZ_CONFIGURATION_END)
      if(!(edition_settings.configuration&(1<<ZZ_BIT_CONFIGURATION))) isValid = 0;

    if(inOffset>=TZNP_CONFIGURATION_BEGIN && inOffset<=TZNP_CONFIGURATION_END)
      if(!(edition_settings.configuration&(1<<TZNP_BIT_CONFIGURATION))) isValid = 0;

    if(inOffset>=ZOP_CONFIGURATION_BEGIN && inOffset<=ZOP_CONFIGURATION_END)
      if(!(edition_settings.configuration&(1<<ZOP_BIT_CONFIGURATION))) isValid = 0;

    if(inOffset>=UMIN_CONFIGURATION_BEGIN && inOffset<=UMIN_CONFIGURATION_END)
      if(!(edition_settings.configuration&(1<<UMIN_BIT_CONFIGURATION))) isValid = 0;

    if(inOffset>=UMAX_CONFIGURATION_BEGIN && inOffset<=UMAX_CONFIGURATION_END)
      if(!(edition_settings.configuration&(1<<UMAX_BIT_CONFIGURATION))) isValid = 0;

    if(inOffset>=APV_CONFIGURATION_BEGIN && inOffset<=APV_CONFIGURATION_END)
      if(!(edition_settings.configuration&(1<<APV_BIT_CONFIGURATION))) isValid = 0;

    if(inOffset>=UROV_CONFIGURATION_BEGIN && inOffset<=UROV_CONFIGURATION_END)
      if(!(edition_settings.configuration&(1<<UROV_BIT_CONFIGURATION))) isValid = 0;

    if(inOffset>=EL_CONFIGURATION_BEGIN && inOffset<=EL_CONFIGURATION_END)
      if(!(edition_settings.configuration&(1<<EL_BIT_CONFIGURATION))) isValid = 0;

    if(inOffset>=ACHR_CHAPV_CONFIGURATION_BEGIN && inOffset<=ACHR_CHAPV_CONFIGURATION_END)
      if(!(edition_settings.configuration&(1<<ACHR_CHAPV_BIT_CONFIGURATION))) isValid = 0;

  }//if((*outMaska)!=-1)

  if(inOffset>=384 && inOffset<408)
  {
    if(!(edition_settings.configuration&(1<<UP_BIT_CONFIGURATION))) isValid = 0;
    int inupOffset = inOffset-384;
    switch(inupOffset%3)
    {
    case 0:
      (*outMaska) = RANG_BLOCK_UP1 + inupOffset;
      (*dvMaska)  = RANG_SMALL_BLOCK_UP1 + (inupOffset/3);
      break;
    case 1:
      (*outMaska) = RANG_PO_UP1 +inupOffset;
//        (*dvMaska) =
      break;
    case 2:
      (*outMaska) = RANG_UP1 +inupOffset;
//        (*dvMaska) =
      break;
    }//switch
  }//if

  return isValid;
}//cmdFunc000(int inOffset, int *outMaska, int *dvMaska)

int getACMDSmallBeginAdr(void)
{
  return BEGIN_ADR_BIT;
}//getACMDSmallBeginAdr(void)
/**************************************/
//��������� ������� �������� � ����������� �������
/**************************************/
void constructorACMDSmallComponent(COMPONENT_OBJ *acmdcomp)
{
  acmdsmallcomponent = acmdcomp;

  acmdsmallcomponent->getModbusRegister = getACMDSmallModbusRegister;//�������� ���������� ��������
  acmdsmallcomponent->getModbusBit      = getACMDSmallModbusBit;//�������� ���������� ����
  acmdsmallcomponent->setModbusRegister = setACMDSmallModbusRegister;// ��������
  acmdsmallcomponent->setModbusBit      = setACMDSmallModbusBit;// ����

  acmdsmallcomponent->preReadAction   = preACMDSmallReadAction;//action �� ������
  acmdsmallcomponent->preWriteAction  = preACMDSmallWriteAction;//action �� ������
  acmdsmallcomponent->postWriteAction = postACMDSmallWriteAction;//action ����� ������

  acmdsmallcomponent->isActiveActualData = 0;
}//constructorDOUTSmallComponent(COMPONENT_OBJ *doutcomp)

void loadACMDSmallActualDataBit(int cmdSwitch, int beginOffset, int endOffset)
{
  //ActualData
  for(int ii=0; ii<(1+(END_ADR_BIT-BEGIN_ADR_BIT+1)/16); ii++) tempReadArray[ii] = 0;
  for(int item=0; item<(END_ADR_BIT-BEGIN_ADR_BIT+1); item++)
  {
    int value =0;
    if(item>=beginOffset && item<endOffset)
    {
      value = encoderN_BIGACMD(item);//���������� ������ modbus � ������ ���� ��� ����
      if(value==-1) value=0;
      else {
        //������ �������� ������
        if(cmdSwitch==0) {
          //ACMD
          if(active_functions[value/16] & (1<<(value%16))) value=1;
//           if(value==RANG_BLOCK_MTZ2) value=1;
        }//if(cmdSwitch==0)
        if(cmdSwitch==1) {
          //GCMD
          if(trigger_active_functions[value/16] & (1<<(value%16))) value=1;
        }//if(cmdSwitch==0)
      }
    }//if(item>=beginOffset && item<endOffset)

    int tsdata = 0;
    if(value) tsdata=1;
    tempReadArray[item/16] |= tsdata<<(item%16);
  }//for(int item=0; item<568; item++)
}//loadACMDSmallActualDataBit(int cmdSwitch, int beginOffset, int endOffset)

int validN_BIGACMD(unsigned short dataReg)
{
  return validBazaN_BIGACMD(dataReg, CLRACT_CONTROL);
}//validN_BIGACMD(unsigned short dataReg)
int validBazaN_BIGACMD(unsigned short dataReg, int actControl)
{
//����������� �������� ������ ������� for rele
  if(dataReg!=0)
  {
    int validCMD=0;
    if(((int)encoderValidN_BIGACMD(dataReg-getACMDSmallBeginAdr(), &validCMD, actControl))<0) return MARKER_ERRORPERIMETR; //���������� ������ modbus � ������ ���� ��� ����
    if(!validCMD) return MARKER_ERRORPERIMETR; //�� ������ ���������
  }//if(dataReg!=0)

  return 0;
}//validBazaN_BIGACMD(unsigned short dataReg, int actControl)
int validN_SMALLACMD(unsigned short dataReg)
{
//����������� �������� ������ ������� for dv
  if(dataReg!=0)
  {
    int validCMD=0;
    if(((int)encoderValidN_SMALLACMD(dataReg-getACMDSmallBeginAdr(), &validCMD))<0) return MARKER_ERRORPERIMETR; //���������� ������ modbus � ������ ���� ��� ����
    if(!validCMD) return MARKER_ERRORPERIMETR; //�� ������ ���������
  }//if(dataReg!=0)

  return 0;
}//validN_SMALLACMD(int dataReg)
unsigned int encoderN_BIGACMD(int offsetCMD)
{
  int validCMD=0;
  return encoderValidN_BIGACMD(offsetCMD, &validCMD, CLRACT_CONTROL);
}//encoderN_BIGACMD(int adrCMD)
unsigned int encoderValidN_BIGACMD(int offsetCMD, int *validCMD, int actControl)
{
//���������� ������ modbus � ������ ���� ��� ����
  int outMaska=-1;
  int dvMaska=-1;
  (*validCMD) = cmdFunc000(offsetCMD, &outMaska, &dvMaska, actControl);
  return outMaska;
}//encoderValidN_BIGACMD(int offsetCMD, int *validCMD)
unsigned int encoderN_SMALLACMD(int offsetCMD)
{
  int validCMD=0;
  return encoderValidN_SMALLACMD(offsetCMD, &validCMD);
}//encoderN_SMALLACMD(int adrCMD)
unsigned int encoderValidN_SMALLACMD(int offsetCMD, int *validCMD)
{
//���������� ������ modbus � ������ ���� ��� ��
  int outMaska=-1;
  int dvMaska=-1;
  (*validCMD) = cmdFunc000(offsetCMD, &outMaska, &dvMaska, CLRACT_CONTROL);
  return dvMaska;
}//encoderValidN_SMALLACMD(int offsetCMD, int *validCMD)

int decoderN_BIGACMD(int idxBit)
{
//������������ ������� ���� � ����� modbus  ��� ����
  for(int item=0; item<(END_ADR_BIT-BEGIN_ADR_BIT+1); item++)
  {
    int outMaska=-1;
    int dvMaska=-1;
    cmdFunc000(item, &outMaska, &dvMaska, CLRACT_CONTROL);
    if(outMaska==idxBit) return item;
  }//for(int item=0; item<568; item++)
  return -1;
}//decoderN_BIGACMD(int idxBit)
int decoderN_SMALLACMD(int idxBit)
{
//������������ ������� ���� � ����� modbus  ��� ��
  for(int item=0; item<(END_ADR_BIT-BEGIN_ADR_BIT+1); item++)
  {
    int outMaska=-1;
    int dvMaska=-1;
    cmdFunc000(item, &outMaska, &dvMaska, CLRACT_CONTROL);
    if(dvMaska==idxBit) return item;
  }//for(int item=0; item<568; item++)
  return -1;
}//decoderN_SMALLACMD(int idxBit)
int getSequenceN_BIGIndexActiveBit(int propusk, unsigned int *array)
{
//������ ��������� ���� N_BIG
  int bit=0;
  unsigned int arrayData = 0;
  for(; bit<N_BIG*32; bit++)
  {
    arrayData = array[bit/32];
    if(arrayData==0) {
      bit+=31;
      continue;
    }
    unsigned int data = arrayData&(1<<(bit%32));
    if(data!=0&&propusk==0) break;
    if(data!=0&&propusk!=0) propusk--;
  }//for
  if(bit!=N_BIG*32) return bit;
  return -1;
}//getSequenceN_BIGIndexActiveBit(int propusk, unsigned int *array)

int getSequenceN_SMALLIndexActiveBit(int propusk, unsigned int *array)
{
//������ ��������� ���� N_SMALL
  int bit=0;
  unsigned int arrayData = 0;
  for(; bit<N_SMALL*32; bit++)
  {
    arrayData = array[bit/32];
    if(arrayData==0) {
      bit+=31;
      continue;
    }
    unsigned int data = arrayData&(1<<(bit%32));
    if(data!=0&&propusk==0) break;
    if(data!=0&&propusk!=0) propusk--;
  }//for
  if(bit!=N_SMALL*32) return bit;
  return -1;
}//getSequenceN_SMALLIndexActiveBit(int propusk, unsigned int *array)
int getRangN_BIGModbusRegister(unsigned int *ranguvannja, int countItem, int offset )
{
//����� ��������� ����
  int bit = getSequenceN_BIGIndexActiveBit(offset%countItem, &ranguvannja[N_BIG*offset/countItem]);//������ ��������� ����
  if(bit!=-1)
  {
    int adr = decoderN_BIGACMD(bit);
    return adr<0? 0: adr+getACMDSmallBeginAdr();//������������ ������� ���� � ����� modbus  ��� rele
  }//if(bit!=-1)
  return 0;
}//getRangN_BIGModbusRegister(unsigned int *ranguvannja, int countItem, int offset )
int getRangN_SMALLModbusRegister(unsigned int *ranguvannja, int countItem, int offset )
{
//����� ��������� ����
  int bit = getSequenceN_SMALLIndexActiveBit(offset%countItem, &ranguvannja[N_SMALL*offset/countItem]);//������ ��������� ����
  if(bit!=-1)
  {
    int adr = decoderN_SMALLACMD(bit);
    return adr<0? 0: adr+getACMDSmallBeginAdr();//������������ ������� ���� � ����� modbus  ��� rele
  }//if(bit!=-1)
  return 0;
}//getRangN_SMALLModbusRegister(unsigned int *ranguvannja, int countItem, int offset )
void writeRangN_BIGModbusRegister(unsigned int *ranguvannja, int countItem, int beginAdr,
                                  int countAdr, int begin_adr_register)
{
  int offsetTempWriteArray = superFindTempWriteArrayOffset(begin_adr_register);//����� �������� TempWriteArray
  unsigned int tmp[N_BIG];//��� ���� ������������
  int idxObjOld=-1;//������ ��� ������ old
  //������ ������
  for(int i=0; i<countAdr; i++)
  {
    int offset = beginAdr-begin_adr_register+i;

    int idxObj = offset/countItem;//������ ��� ������
    unsigned int *ranguvannja_d = &ranguvannja[N_BIG*idxObj]; //����������
    if(idxObj!=idxObjOld) {
      idxObjOld = idxObj;
      for(int dx=0; dx<N_BIG; dx++) tmp[dx]=ranguvannja_d[dx];//���� ������ ����
    }//if

    int bitOld = getSequenceN_BIGIndexActiveBit(offset%countItem, tmp);//������ ��������� ����
    if(bitOld!=-1) {
      ranguvannja_d[bitOld/32] &= ~(1<<(bitOld%32));
    }//if
  }//for
  //�������� �����
  for(int i=0; i<countAdr; i++)
  {
    unsigned int adr = (unsigned short)tempWriteArray[offsetTempWriteArray+i];//����� ��������
    if(adr==0) continue;
    int offset = beginAdr-begin_adr_register+i;

    int idxObj = offset/countItem;//������ ��� ������
    unsigned int *ranguvannja_d = &ranguvannja[N_BIG*idxObj]; //����������
    int bit = encoderN_BIGACMD(adr-getACMDSmallBeginAdr()); //���������� ������ modbus � ������ ���� ��� ����
    if(bit!=-1) {
      ranguvannja_d[bit/32] |= (1<<(bit%32));
    }//if
  }//for
}//writeRangN_BIGModbusRegister(unsigned int *ranguvannja, int countItem, int beginAdr, int countAdr,
void writeRangN_SMALLModbusRegister(unsigned int *ranguvannja, int countItem, int beginAdr,
                                    int countAdr, int begin_adr_register)
{
  int offsetTempWriteArray = superFindTempWriteArrayOffset(begin_adr_register);//����� �������� TempWriteArray
  unsigned int tmp[N_SMALL];//��� ���� ������������
  int idxObjOld=-1;//������ ��� ������ old
  //������ ������
  for(int i=0; i<countAdr; i++)
  {
    int offset = beginAdr-begin_adr_register+i;

    int idxObj = offset/countItem;//������ ��� ������
    unsigned int *ranguvannja_d = &ranguvannja[N_SMALL*idxObj]; //����������
    if(idxObj!=idxObjOld) {
      idxObjOld = idxObj;
      for(int dx=0; dx<N_SMALL; dx++) tmp[dx]=ranguvannja_d[dx];//���� ������ ����
    }//if

    int bitOld = getSequenceN_SMALLIndexActiveBit(offset%countItem, tmp);//������ ��������� ����
    if(bitOld!=-1) {
      ranguvannja_d[bitOld/32] &= ~(1<<(bitOld%32));
    }//if
  }//for
  //�������� �����
  for(int i=0; i<countAdr; i++)
  {
    unsigned int adr = (unsigned short)tempWriteArray[offsetTempWriteArray+i];//����� ��������
    if(adr==0) continue;
    int offset = beginAdr-begin_adr_register+i;

    int idxObj = offset/countItem;//������ ��� ������
    unsigned int *ranguvannja_d = &ranguvannja[N_SMALL*idxObj]; //����������
    int bit = encoderN_SMALLACMD(adr-getACMDSmallBeginAdr()); //���������� ������ modbus � ������ ���� ��� dv
    if(bit!=-1) {
      ranguvannja_d[bit/32] |= (1<<(bit%32));
    }//if
  }//for
}//writeRangN_SMALLModbusRegister(unsigned int *ranguvannja, int countItem, int beginAdr, int countAdr,

int getACMDSmallModbusRegister(int adrReg)
{
  extern int globalcntReg;//�-�� reg ��� ������
  extern int globalbeginAdrReg;//����� ��� reg
  //�������� ���������� ��������
  if(privateACMDSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(acmdsmallcomponent->isActiveActualData)
  {
    int begin = globalbeginAdrReg-BEGIN_ADR_REGISTER;
    if(begin<0) globalcntReg += begin;

    int beginOffset = (adrReg-BEGIN_ADR_REGISTER)*16;
    int endOffset   = beginOffset +globalcntReg*16;// + beginOffset;

    loadACMDSmallActualDataBit(0, beginOffset, endOffset); //ActualData
  }//if(acmdsmallcomponent->isActiveActualData)
  acmdsmallcomponent->isActiveActualData = 0;

  return tempReadArray[adrReg-BEGIN_ADR_REGISTER];
}//getDOUTModbusRegister(int adrReg)
int getACMDSmallModbusBit(int adrBit)
{
  extern int globalcntBit;//�-�� ��� ��� ������
  extern int globalbeginAdrBit;//����� ��� ���
  //�������� ���������� bit

  if(privateACMDSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  int beginOffset = adrBit-BEGIN_ADR_BIT;
  if(acmdsmallcomponent->isActiveActualData)
  {
    int begin = globalbeginAdrBit-BEGIN_ADR_BIT;
    if(begin<0) globalcntBit += begin;

    int endOffset   = beginOffset +globalcntBit;

    loadACMDSmallActualDataBit(0, beginOffset, endOffset); //ActualData
  }//if(acmdsmallcomponent->isActiveActualData)
  acmdsmallcomponent->isActiveActualData = 0;

  short tmp   = tempReadArray[beginOffset/16];
  short maska = 1<<(beginOffset%16);
  if(tmp&maska) return 1;
  return 0;
}//getDOUTModbusBit(int adrReg)
int setACMDSmallModbusRegister(int adrReg, int dataReg)
{
  if(privateACMDSmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  int beginOffset = (adrReg-BEGIN_ADR_REGISTER)*16;
  int endOffset   = beginOffset+16;// + beginOffset;
  for(int offset=beginOffset; offset<endOffset; offset++)
  {
    if(!(dataReg & (1<<(offset%16)))) continue;
    if(writeACMDSmallActualDataBit(offset, 0)!=0) return MARKER_ERRORPERIMETR;
  }//for

  return 0;
}//getDOUTModbusRegister(int adrReg)
int setACMDSmallModbusBit(int adrBit, int dataBit)
{
  //�������� ���������� bit
  if(privateACMDSmallGetBit2(adrBit)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  superSetOperativMarker(acmdsmallcomponent, adrBit);
  superSetTempWriteArray(dataBit);//�������� � �����
  if(adrBit!=50567)//��������� ������������
  {
    if(dataBit==0) return MARKER_ERRORPERIMETR;
  }//if(adrBit!=50567)
  else return 0;
  if(writeACMDSmallActualDataBit(adrBit-BEGIN_ADR_BIT, 0)!=0) return MARKER_ERRORPERIMETR;

  return 0;
}//getDOUTModbusRegister(int adrReg)

int writeACMDSmallActualDataBit(int inOffset, int dataBit)
{
  int actControl = 0;
  if(inOffset<0)
  {
    inOffset = -inOffset;
    actControl = 1;
  }//if(offset<0)
  switch(inOffset)
  {
  case 432://OF
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DF1_IN);
      mutex_interface = false;
    }//if(action)
    return 0;
  case 433://OF
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DF2_IN);
      mutex_interface = false;
    }//if(action)
    return 0;
  case 434://OF
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DF3_IN);
      mutex_interface = false;
    }//if(action)
    return 0;
  case 435://OF
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DF4_IN);
      mutex_interface = false;
    }//if(action)
    return 0;
  case 436://OF
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DF5_IN);
      mutex_interface = false;
    }//if(action)
    return 0;
  case 437://OF
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DF6_IN);
      mutex_interface = false;
    }//if(action)
    return 0;
  case 438://OF
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DF7_IN);
      mutex_interface = false;
    }//if(action)
    return 0;
  case 439://OF
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DF8_IN);
      mutex_interface = false;
    }//if(action)
    return 0;

  case 464://DTR
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DT1_SET);
      mutex_interface = false;
    }//if(action)
    return 0;
  case 465://DTR
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DT1_RESET);
      mutex_interface = false;
    }//if(action)
    return 0;
  case 466://DTR
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DT2_SET);
      mutex_interface = false;
    }//if(action)
    return 0;
  case 467://DTR
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DT2_RESET);
      mutex_interface = false;
    }//if(action)
    return 0;
  case 468://DTR
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DT3_SET);
      mutex_interface = false;
    }//if(action)
    return 0;
  case 469://DTR
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DT3_RESET);
      mutex_interface = false;
    }//if(action)
    return 0;
  case 470://DTR
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DT4_SET);
      mutex_interface = false;
    }//if(action)
    return 0;
  case 471://DTR
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_DT4_RESET);
      mutex_interface = false;
    }//if(action)
    return 0;

  case 528://
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_VKL_VV); //���.  �����������
      mutex_interface = false;
    }//if(action)
    return 0;
  case 529://
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_OTKL_VV); //����. �����������
      mutex_interface = false;
    }//if(action)
    return 0;

  case 562://
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_RESET_LEDS);//�������� ���������
      mutex_interface = false;
    }//if(action)
    return 0;
  case 563://
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_RESET_RELES); //�������� ����
      mutex_interface = false;
    }//if(action)
    return 0;
  case 564://
    if(actControl&&dataBit)
    {
      //�������� ��������� �������
      unsigned int type_interface = USB_RECUEST;
      reset_trigger_function_from_interface |= (1 << type_interface);
    }//if(action)
    return 0;
  case 565://
    if(actControl&&dataBit)
    {
      restart_counter = 0xff; //������ ��� �������� ������� ��������� � ������� �������
    }//if(action)
    return 0;

  case 567://����������� ������������
    if(actControl)
    {
      if(dataBit)
      {
        //��������� ��������� ���
        if(set_new_settings_from_interface(2))//2-USB
        {
        type_of_settings_changed = 0;
        _CLEAR_BIT(active_functions, RANG_SETTINGS_CHANGED);
          return ERROR_VALID3;//������
        }//if
      }//if
      else//�����������
      {
        //³���� ��������� ���
        current_settings_interfaces = current_settings;
      }
        type_of_settings_changed = 0;
        _CLEAR_BIT(active_functions, RANG_SETTINGS_CHANGED);
    }//if(action)
    return 0;

  case 599://
    if(actControl&&dataBit)
    {
      mutex_interface = true;
      _SET_BIT(activation_function_from_interface, RANG_SMALL_RESET_BLOCK_READY_TU_VID_ZAHYSTIV); //�������� ���������� ��������� �� �� �������
      mutex_interface = false;
    }//if(action)
    return 0;
  }//switch
  return MARKER_ERRORPERIMETR;
}//writeACMDSmallActualDataBit(int offset)

void preACMDSmallReadAction(void)
{
//action �� ������
  acmdsmallcomponent->isActiveActualData = 1;
}//
void preACMDSmallWriteAction(void)
{
//action �� ������
  acmdsmallcomponent->operativMarker[0] = -1;
  acmdsmallcomponent->operativMarker[1] = -1;//����������� ������
  acmdsmallcomponent->isActiveActualData = 1;
}//
int postACMDSmallWriteAction(void)
{
//action ����� ������
  int beginAdr = acmdsmallcomponent->operativMarker[0];
  if(beginAdr<0) return 0;//�� ���� ������
  int endAdr   = acmdsmallcomponent->operativMarker[1];
  int countAdr = endAdr-beginAdr+1;
  if(endAdr<0) countAdr = 1;

  if(beginAdr>=BEGIN_ADR_BIT)
  {
    //������ � ������
    int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_BIT);//����� �������� TempWriteArray

    for(int i=0; i<countAdr; i++) {
      int offset = i+beginAdr-BEGIN_ADR_BIT;
      uint32_t value = tempWriteArray[offsetTempWriteArray+i];
      writeACMDSmallActualDataBit(-offset, value);//action
    }//for
  }//if(beginAdr>=BEGIN_ADR_BIT)
  else
  {
    //������ � ����������
    int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray
    for(int i=0; i<countAdr; i++) {
      int offset = i+beginAdr-BEGIN_ADR_REGISTER;
      for(int bit=0; bit<16; bit++)
      {
        uint32_t value = tempWriteArray[offsetTempWriteArray+i];
        int temp = 0;
        if(value&(1<<bit)) temp = 1;
        writeACMDSmallActualDataBit(-(offset*16+bit), temp);//action
      }//for
    }//for
  }//else

  return 0;
}//

int privateACMDSmallGetReg2(int adrReg)
{
  //��������� ������� ��������
  int count_register = END_ADR_REGISTER-BEGIN_ADR_REGISTER+1;
  if(adrReg>=BEGIN_ADR_REGISTER && adrReg<(BEGIN_ADR_REGISTER+count_register)) return 0;
  return MARKER_OUTPERIMETR;
}//privateGetReg2(int adrReg)

int privateACMDSmallGetBit2(int adrBit)
{
  //��������� ������� ��������
  return controlPerimetr(adrBit, BEGIN_ADR_BIT, END_ADR_BIT);
}//privateGetReg2(int adrReg)