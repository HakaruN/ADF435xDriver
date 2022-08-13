#include <stdio.h>
//#include "registerSet.h"
#include "RegInterface.h"
#include "enums.h"
#include <math.h>


uint8_t getRfDiv(uint32_t desiredFreq)
{
  if(desiredFreq < 68750000)
    return DIV_BY_64;
  else if(desiredFreq < 137500000)
    return DIV_BY_32;
  else if(desiredFreq < 275000000)
    return DIV_BY_16;
  else if(desiredFreq < 550000000)
    return DIV_BY_8;
  else if(desiredFreq < 1100000000)
    return DIV_BY_4;
  else if(desiredFreq < 2200000000)
    return DIV_BY_2;
  else
    return DIV_BY_1;
}

uint8_t calcBandSelectClockDiv(uint32_t pfdFreq)
{ //calculate the divider for the band select logic that will ensure the
  //band select logic never runs >125Khz
  float pfdf = (float)pfdFreq;
  float ratio = pfdf / 125000.f;
  return (uint8_t)(ceil(ratio));
}

int main()
{
  uint32_t genFreq = 2000000000;//2.4Ghz
  uint32_t refFreq = 25000000;//25Mhz
  uint32_t refDivCounter = 99;
  uint8_t refDouble = 1;
  uint8_t refDivBy2 = 1;
  uint16_t outputChannelSpacing = 2000;
  uint8_t rdDivider = 0;
  uint8_t doubleBuffer = 0;

  //pfd freq
  uint32_t pfdDenom = refDivCounter * (1 + refDivBy2);
  uint32_t pfdNum = refFreq * (1 + refDouble);
  uint32_t pfdFreq = pfdNum / pfdDenom;
  printf("Phase freq detector freq: %d\n", pfdFreq);


  uint8_t divideRatio = getRfDiv(genFreq);
  printf("divide ratio: %u\n", divideRatio);

  uint8_t feedbackSelect;
  if(divideRatio != DIV_BY_1)
    feedbackSelect = DIVIDED;
  else
    feedbackSelect = FUNDAMENTAL;

  //int
  uint32_t Ncount;
  if(feedbackSelect)
    Ncount = (genFreq / pfdFreq) * divideRatio;
  else
    Ncount = genFreq / pfdFreq;

  printf("Int: %d\n", Ncount);

  //mod and frac
  uint16_t modulus = refFreq / outputChannelSpacing;
  printf("Mod: %d\n", modulus);
  uint16_t frac = modulus * (genFreq / (pfdFreq));
  printf("Frac: %d\n", frac);

  //phase val
  uint16_t phaseVal = 1;//must be less than mod, can play with it if you want

  uint8_t phaseAdjust = 1;//unless targeting a single freq or wanting a really precise frequency deviation (<1Mhz). Keep on 1

  uint8_t prescalar;
  if(genFreq > 3600000000)
    prescalar = _8over9;
  else
    prescalar = _4over5;

  printf("Prescalar: %d\n", prescalar);

  uint8_t LNAS = LOW_NOISE;

  uint8_t muxOut = TRI_STATE;

  uint8_t chargePumpSetting = _0_31;

  uint8_t ldf = FRACTIONAL_N;

  uint8_t ldp = _10ns;

  uint8_t pdPolarity = POSITIVE;

  uint8_t powerDown = POWER_ON;

  uint8_t cpts = PUMP_NORMAL_OPERATION;

  uint8_t counterReset = COUNTER_OPERATING;

  uint8_t bandSelectClockMode;
  if(pfdFreq < 125000)
    bandSelectClockMode = LOW;
  else
    bandSelectClockMode = HIGH;

  uint8_t ABP = ABPW_6ns;

  uint8_t chargePumpCancel = NOT_CHARGE_PUMP_CANCEL;

  uint8_t csr = CSR_DISABLE;

  uint8_t clockDivMode = CLOCK_DIV_OFF;

  uint8_t VCOPowerDown = POWER_UP;

  uint8_t mtld = NO_MUTE;

  uint8_t auxOutputSelect = AUX_OUTPUT_FUNDAMENTAL;

  uint8_t auxOutputEnable = AUX_DISABLED;

  uint8_t auxOutputPower = _POS5dbm;

  uint8_t RfOutputEnable = RF_ENABLED;

  uint8_t outputPower = _POS5dbm;

  uint8_t lockDetectPinMode = LD_HIGH;

  uint8_t bandSelectClockDiv = calcBandSelectClockDiv(pfdFreq);
  printf("Band select clock div: %d\n", bandSelectClockDiv);


  RegisterSet dev1;

  ////////////
  ///TEMPLATE FOR ALL REGISTERS
  ///////////
    //Setup the registers
  //Reg 5
  setLockDetectPinMode(&dev1, lockDetectPinMode);
  //Reg 4
  setOutputPower(&dev1, outputPower);
  setOutputEnable(&dev1, RfOutputEnable);
  setAuxOutputPower(&dev1, auxOutputPower);
  setAuxOutputEnable(&dev1, auxOutputEnable);
  setAuxOutputSelect(&dev1, auxOutputSelect);
  setMTLD(&dev1, mtld);
  setVCOPowerDown(&dev1, VCOPowerDown);
  setBSCDV(&dev1, bandSelectClockDiv);
  setDividerSelect(&dev1, divideRatio);
  setFeedbackSelect(&dev1, feedbackSelect);
  //Reg 3
  setClockDiv(&dev1, 0xFFF);
  setClockDivMode(&dev1, clockDivMode);
  setCSR(&dev1, csr);
  setChargeCancel(&dev1, chargePumpCancel);
  setABP(&dev1, ABP);
  setBandSelectClockMode(&dev1, bandSelectClockMode);
  //Reg 2
  setCounterReset(&dev1, counterReset);
  setCPThreeState(&dev1, cpts);
  setPowerDown(&dev1, powerDown);
  setPDPolarity(&dev1, pdPolarity);
  setLDP(&dev1, ldp);
  setLDF(&dev1, ldf);
  setCPCS(&dev1, chargePumpSetting);
  setDoubleBuffer(&dev1, doubleBuffer);
  setRCounter(&dev1, refDivCounter);
  setRdivBy2(&dev1, refDivBy2);
  setRefDoubler(&dev1, refDouble);
  setMuxOut(&dev1, muxOut);
  setLNAS(&dev1, LNAS);
  //Reg 1
  setMod(&dev1, modulus);
  setPhaseVal(&dev1, phaseVal);
  setPrescalar(&dev1, prescalar);
  setPhaseAdjust(&dev1, phaseAdjust);
  //Reg 0
  setFraction(&dev1, frac);
  setInteger(&dev1, Ncount);

  return 0;
}
