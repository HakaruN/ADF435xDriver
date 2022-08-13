#include "RegInterface.h"
#include "enums.h"
#include <math.h>

//#define SERIAL_PRINT // - for use when printing with an arduino (device side)
#define CONSOLE_PRINT // - for use when printing to the console (host side)
#define PRINT_LOCK // - enables the printing of the lock status from the RF gen board in the loop
//#define IS_ARDUINO
#ifdef IS_ARDUINO
#include<SPI.h>
#endif
#ifndef IS_ARDUINO
#include <stdio.h>
#endif

//Registers for the ADF4351
RegisterSet dev1;

#define REGISTERS_SIZE_BYTES 6 * 4 //6 regs, 4 bytes each
uint8_t regBuffer[REGISTERS_SIZE_BYTES] ;/*= {
  0x00, 0x58, 0x00, 0x05,
  0x00, 0x8C, 0x80, 0x3C,
  0x00, 0x00, 0x04, 0xB3,
  0x00, 0x00, 0x4E, 0x42,
  0x08, 0x00, 0x80, 0x11,
  0x00, 0x32, 0x00, 0x00,
};//buffer to store all of the bytes of all of the registers - known good
*/

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


#ifdef IS_ARDUINO
void setup() {
  //SPI setup
  Serial.begin(19200);
  pinMode(SS, OUTPUT);
  digitalWrite(SS, HIGH); // disable Slave Select
  SPI.begin();
  //SPI.setClockDivider(SPI_CLOCK_DIV8);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  //Check for lock detect
  pinMode(3, INPUT);

#else
  int main() {
#endif

  uint32_t genFreq = 1000000000;
  #ifdef SERIAL_PRINT
  Serial.print("Generating freq: "); Serial.print(genFreq/1000000); Serial.print("Mhz\n");//print the genFreq
  #endif
  #ifdef CONSOLE_PRINT
  printf("Generating freq: %dMhz\n", genFreq/1000000);
  #endif


  uint32_t refFreq = 25000000;//25Mhz
  uint32_t refDivCounter = genFreq / 10000000;//R counter
  #ifdef SERIAL_PRINT
  Serial.print("Reference div counter: "); Serial.print(refDivCounter); Serial.print("\n");//print the genFreq
  #endif
  #ifdef CONSOLE_PRINT
  printf("Reference div counter: %d\n", refDivCounter);
  #endif

  uint8_t refDouble = 0;
  uint8_t refDivBy2 = 0;
  ///Channel spacing
  uint16_t outputChannelSpacing = 2800;
  #ifdef SERIAL_PRINT
  Serial.print("Output channel spacing: "); Serial.print(outputChannelSpacing); Serial.print("hz\n");//print the genFreq
  #endif
  #ifdef CONSOLE_PRINT
  printf("Output channel spacing: %dhz\n", outputChannelSpacing);
  #endif
  uint8_t rdDivider = 0;
  uint8_t doubleBuffer = 0;

  //pfd freq
  uint32_t pfdDenom = refDivCounter * (1 + refDivBy2);
  uint32_t pfdNum = refFreq * (1 + refDouble);
  uint32_t pfdFreq = pfdNum / pfdDenom;
  #ifdef SERIAL_PRINT
  Serial.print("PDF freq: "); Serial.print(pfdFreq/1000); Serial.print("Khz\n");//print the pfd
  #endif
  #ifdef CONSOLE_PRINT
  printf("Phase freq detector freq: %d\n", pfdFreq);
  #endif

  uint8_t divideRatio = getRfDiv(genFreq);
  #ifdef SERIAL_PRINT
  Serial.print("divide ratio: "); Serial.print(divideRatio); Serial.print('\n');//print the RF divide ratio
  #endif
  #ifdef CONSOLE_PRINT
  printf("divide ratio: %u\n", divideRatio);
  #endif

  uint8_t feedbackSelect;
  if(divideRatio != DIV_BY_1)
    feedbackSelect = DIVIDED;
  else
    feedbackSelect = FUNDAMENTAL;

  //int
  uint32_t Ncount;
  if(feedbackSelect == FUNDAMENTAL) //feedback from the VCO output to the N counter
    Ncount = genFreq / pfdFreq;
  else //signal is taken from the output of the output dividers
    Ncount = (genFreq / pfdFreq) * divideRatio;

  #ifdef SERIAL_PRINT
  Serial.print("N count: "); Serial.print(Ncount); Serial.print('\n');//print the Ncount
  #endif
  #ifdef CONSOLE_PRINT
  printf("Int: %d\n", Ncount);
  #endif

  //mod and frac
  uint16_t modulus = refFreq / outputChannelSpacing;
  //printf("Mod: %d\n", modulus);
  uint16_t frac = modulus * (genFreq / (pfdFreq));
  //printf("Frac: %d\n", frac);

  //phase val
  uint16_t phaseVal = 1;//must be less than mod, can play with it if you want

  uint8_t phaseAdjust = 1;//unless targeting a single freq or wanting a really precise frequency deviation (<1Mhz). Keep on 1

  uint8_t prescalar;
  if(genFreq > 3600000000)
    prescalar = _8over9;
  else
    prescalar = _4over5;

  //printf("Prescalar: %d\n", prescalar);

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
    bandSelectClockMode = BSCM_LOW;
  else
    bandSelectClockMode = BSCM_HIGH;

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
  #ifdef SERIAL_PRINT
  Serial.print("Band select clock div: "); Serial.print(bandSelectClockDiv); Serial.print('\n');//print the bandSelectClockDiv
  #endif
  #ifdef CONSOLE_PRINT
  printf("Band select clock div: %d\n", bandSelectClockDiv);
  #endif

  //new line
  #ifdef SERIAL_PRINT
  Serial.print("\n");
  #endif
  #ifdef CONSOLE_PRINT
  printf("\n");
  #endif
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

  #ifndef IS_ARDUINO
  return 0;
  #endif
}


#ifdef IS_ARDUINO
void loop() {

 sendRegs(&dev1);
 delay(1000);

 #ifdef PRINT_LOCK
 if(digitalRead(3))
  Serial.print("Locked\n");
 else
  Serial.print("No Locked\n");
  #endif

  #ifdef PRINT_BUFF
  for (int reg = 0; reg < 6; reg++)
  {
    //find the byte
    for (int _byte = 0; _byte < 4; _byte++)
    {
       Serial.print(regBuffer[(reg * 4) + _byte], HEX);//print the byte
       //Serial.print(' ');
    }
    Serial.print(',');
  }
  Serial.print('\n');
  delay(1000);
  #endif

}

void sendRegs(RegisterSet* regs)
{
  memcpy(regBuffer, &dev1,REGISTERS_SIZE_BYTES);//copy the reg's contents into the buffer
  //find the reg
  for (int reg = 0; reg < 6; reg++)
  {
    //prepare to send the reg:
    digitalWrite(SS, LOW);//prepare for sending
    delayMicroseconds(1);//delay

    //find the byte
    for (int _byte = 3; _byte >= 0; _byte--)
    {
      SPI.transfer(regBuffer[(reg * 4) + _byte]);//send the byte
    }

    //recover from sending the reg
    digitalWrite(SS, HIGH);
    delayMicroseconds(1);//delay
  }
}
#endif
