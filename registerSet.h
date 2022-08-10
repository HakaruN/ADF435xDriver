#ifndef REG_SET
#define REG_SET

#include "regDefs.h"

//Collection of all the registers for the ADF435x

typedef struct RegisterSet
{
  Reg0 reg0;
  Reg1 reg1;
  Reg2 reg2;
  Reg3 reg3;
  Reg4 reg4;
  Reg5 reg5;
} RegisterSet;
#endif
