#ifndef REG_SET
#define REG_SET

#include "regDefs.h"

//Collection of all the registers for the ADF435x

typedef struct RegisterSet
{
  //The registers are aranged decending so in memory the
  //first register to write is at the begining, this is because
  //when writing I do a memcpy of the struct and run through
  //sending the bytes straight over spi
  Reg5 reg5;
  Reg4 reg4;
  Reg3 reg3;
  Reg2 reg2;
  Reg1 reg1;
  Reg0 reg0;
} RegisterSet;
#endif
