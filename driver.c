#include <stdio.h>
//#include "registerSet.h"
#include "RegInterface.h"

int main()
{
  RegisterSet dev1;

  ////////////
  ///TEMPLATE FOR ALL REGISTERS
  ///////////
    //Setup the registers
  //Reg 5
  setLockDetectPinMode(&dev1, 0x3);
  //Reg 4
  setOutputPower(&dev1, 0x3);
  setOutputEnable(&dev1, 0x1);
  setAuxOutputPower(&dev1, 0x3);
  setAuxOutputEnable(&dev1, 0x1);
  setAuxOutputSelect(&dev1, 0x1);
  setMTLD(&dev1, 0x0);
  setVCOPowerDown(&dev1, 1);
  setBSCDV(&dev1, 0xFF);
  setDividerSelect(&dev1, 0x6);
  setFeedbackSelect(&dev1, 0x1);
  //Reg 3
  setClockDiv(&dev1, 0xFFF);
  setClockDivMode(&dev1, 0x0);
  setCSR(&dev1, 0x1);
  setChargeCancel(&dev1, 0x1);
  setABP(&dev1, 0x1);
  setBandSelectClockMode(&dev1, 0x1);
  //Reg 2
  counterReset(&dev1, 0);
  setCPThreeState(&dev1, 0x1);
  setPowerDown(&dev1, 0x1);
  setPDPolarity(&dev1, 0x1);
  setLDP(&dev1, 0x1);
  setLDF(&dev1, 0x1);
  setCPCS(&dev1, 0x0);
  setDoubleBuffer(&dev1, 0x1);
  setRCounter(&dev1, 1023);
  setRdivBy2(&dev1, 0x1);
  setRefDoubler(&dev1, 0x1);
  setMuxOut(&dev1, 0x7);
  setLNAS(&dev1, 0x3);
  //Reg 1
  setMod(&dev1, 0xFFF);
  setPhaseVal(&dev1, 0xFFF);
  setPrescalar(&dev1, 0x1);
  setPhaseAdjust(&dev1, 0x1);
  //Reg 0
  setFraction(&dev1, 0xFFF);
  setInteger(&dev1, 0xFFFF);

  return 0;
}
