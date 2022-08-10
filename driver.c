#include <stdio.h>
#include "registerSet.h"

int main()
{
  RegisterSet rfGen;
  rfGen.reg0.control = 0;
  rfGen.reg1.control = 1;
  rfGen.reg2.control = 2;

  printf("Register 0 control val: %d", rfGen.reg0.control);
  printf("Register 1 control val: %d", rfGen.reg1.control);

  return 0;
}
git@github.com:HakaruN/ADF435xDriver.git
