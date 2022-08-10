#include <stdio.h>
//#include "registerSet.h"
#include "RegInterface.h"

int main()
{
  RegisterSet rfGen;
  setControlRegs(&rfGen);
  setPhaseAdjust(&rfGen, 1);
  setPrescalar(&rfGen, 1);
  setMod(&rfGen, 100);
  setPhaseVal(&rfGen, 80);
  setInteger(&rfGen, 80);
  setFraction(&rfGen, 99);

  printf("Register 0 control val: %d\n", rfGen.reg0.control);
  printf("Register 1 control val: %d\n", rfGen.reg1.control);
  printf("Register 2 control val: %d\n", rfGen.reg2.control);
  printf("Register 3 control val: %d\n", rfGen.reg3.control);
  printf("Register 4 control val: %d\n", rfGen.reg4.control);
  printf("Register 5 control val: %d\n", rfGen.reg5.control);

  printf("Sizeof reg 0: %lu (bits)\n", sizeof(rfGen.reg0)*8);
  printf("Sizeof reg 1: %lu (bits)\n", sizeof(rfGen.reg1)*8);
  printf("Sizeof reg 2: %lu (bits)\n", sizeof(rfGen.reg2)*8);
  printf("Sizeof reg 3: %lu (bits)\n", sizeof(rfGen.reg3)*8);
  printf("Sizeof reg 4: %lu (bits)\n", sizeof(rfGen.reg4)*8);
  printf("Sizeof reg 5: %lu (bits)\n", sizeof(rfGen.reg5)*8);

  return 0;
}
