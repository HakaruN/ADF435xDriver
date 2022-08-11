#include "registerSet.h"

void setControlRegs(RegisterSet* regs)
{
  regs->reg0.control = 0;
  regs->reg1.control = 1;
  regs->reg2.control = 2;
  regs->reg3.control = 3;
  regs->reg4.control = 4;
  regs->reg5.control = 5;
  regs->reg5.reserved1 = 0b11;
}

void setFraction(RegisterSet* regs, uint16_t frac)
{
  uint16_t mod = regs->reg1.modulus;
  if(frac > mod - 1)
    frac = mod - 1;

  regs->reg0.fraction = frac;
}

void setInteger(RegisterSet* regs, uint16_t integer)
{
  uint8_t prescalar = regs->reg1.prescalar;
  if(prescalar)//prescalar = 8/9
    {
      if(integer < 75)
	{
	  integer = 75;
	}
    }
  else//prescalr 4/5
    if(integer < 23)
      integer = 23;

  regs->reg0.integer = integer;
}

void setMod(RegisterSet* regs, uint16_t mod)
{
  if(mod > 0xFFF)
    mod = 0xFFF;
  regs->reg1.modulus = mod;
}

void setPhaseVal(RegisterSet* regs, uint16_t phase)
{
  if(phase >= regs->reg1.modulus)
    phase = phase - 1;
  regs->reg1.phase = phase;
}

void setPrescalar(RegisterSet* regs, uint8_t prescalar)
{
  if(prescalar)
    regs->reg1.prescalar = 1;
  else
    regs->reg1.prescalar = 0;
}

void setPhaseAdjust(RegisterSet* regs, uint8_t phaseAdjust)
{
  if(phaseAdjust)
    regs->reg1.phaseAdjust = 1;
  else
    regs->reg1.phaseAdjust = 0;
}

void counterReset(RegisterSet* regs, uint8_t reset)
{
  if(reset)
    regs->reg2.counterReset = 1;
  else
    regs->reg2.counterReset = 0;
}

void setCPThreeState(RegisterSet* regs, uint8_t CPstate)
{
  if(CPstate)
    regs->reg2.CPthreeState = 1;
  else
    regs->reg2.CPthreeState = 0;
}

void setPowerDown(RegisterSet* regs, uint8_t powerDown)
{
  if(powerDown)
    regs->reg2.PD = 1;
  else
    regs->reg2.PD = 0;
}

void setPDPolarity(RegisterSet* regs, uint8_t polarity)
{
  if(polarity)
    regs->reg2.PDPolarity = 1;
  else
    regs->reg2.PDPolarity = 0;
}

void setLDP(RegisterSet* regs, uint8_t precision)
{
  if(precision)
    regs->reg2.LDP = 1;
  else
    regs->reg2.LDP = 0;
}

void setLDF(RegisterSet* regs, uint8_t function)
{
  if(function)
    regs->reg2.LDF = 1;
  else
    regs->reg2.LDF = 0;
}

void setCPCS(RegisterSet* regs, uint8_t currentSetting)
{
  if(currentSetting > 0xFF)
    currentSetting = 0xFF;

  regs->reg2.CPCurrentSetting = currentSetting;

}

void setDoubleBuffer(RegisterSet* regs, uint8_t doubleBuff)
{
  if(doubleBuff)
    regs->reg2.doubleBuffer = 1;
  else
    regs->reg2.doubleBuffer = 0;
}

void setRCounter(RegisterSet* regs, uint16_t rCounter)
{
  if(rCounter > 1023)
    rCounter = 1023;

  regs->reg2.RCounter = rCounter;
}

void setRdivBy2(RegisterSet* regs, uint8_t divBy2)
{
  if(divBy2)
    regs->reg2.RDiv2 = 1;
  else
    regs->reg2.RDiv2 = 0;
}

void setRefDoubler(RegisterSet* regs, uint8_t refDouble)
{
  if(refDouble)
    regs->reg2.refDoubler = 1;
  else
    regs->reg2.refDoubler = 0;
}

void setMuxOut(RegisterSet* regs, uint8_t muxOut)
{
  if(muxOut > 0x6)
    muxOut = 0;

  regs->reg2.muxOut = muxOut;
}

void setLNAS(RegisterSet* regs, uint8_t lnas)
{
  if(lnas == 0x0 || lnas == 0x03)//check if valid option
    regs->reg2.LNaS = lnas;
  else
    regs->reg2.LNaS = 0x0;//default to low nois
}

void setClockDiv(RegisterSet* regs, uint16_t divVal)
{
  if(divVal > 0xFFF)
    divVal = 0xFFF;
  regs->reg3.clockDivVal = divVal;
}

void setClockDivMode(RegisterSet* regs, uint8_t divMode)
{
  if(divMode > 0x2)
    divMode = 0x1;//default to fast loclkDivMk
  regs->reg3.clkDivMode = divMode;
}

void setCSR(RegisterSet* regs, uint8_t csr)
{
  if(csr)
    regs->reg3.CSR = 1;
  else
    regs->reg3.CSR = 0;
}

void setChargeCancel(RegisterSet* regs, uint8_t chargeCancel)
{
  if(chargeCancel)
    regs->reg3.chargeCancel = 1;
  else
    regs->reg3.chargeCancel = 0;
}

void setABP(RegisterSet* regs, uint8_t ABP)
{
  if(ABP)
    regs->reg3.ABP = 1;
  else
    regs->reg3.ABP = 0;
}

void setBandSelectClockMode(RegisterSet* regs, uint8_t mode)
{
  if(mode)
    regs->reg3.BSCM = 1;
  else
    regs->reg3.BSCM = 0;
}

void setOutputPower(RegisterSet* regs, uint8_t power)
{
  if(power > 0x3)
    power = 0x3;
  regs->reg4.outputPower = power;
}

void setOutputEnable(RegisterSet* regs, uint8_t enable)
{
  if(enable)
    regs->reg4.outputEnable = 1;
  else
    regs->reg4.outputEnable = 0;
}

void setAuxOutputPower(RegisterSet* regs, uint8_t power)
{
  if(power > 0x3)
      power = 0x3;
    regs->reg4.auxOutputPower = power;
}

void setAuxOutputEnable(RegisterSet* regs, uint8_t enable)
{
  if(enable)
    regs->reg4.auxOutputEnable = 1;
  else
    regs->reg4.auxOutputEnable = 0;
}

void setAuxOutputSelect(RegisterSet* regs, uint8_t select)
{
  if(select)
    regs->reg4.auxOutputSelect = 1;
  else
    regs->reg4.auxOutputSelect = 0;
}

void setMTLD(RegisterSet* regs, uint8_t mtld)
{
  if(mtld)
    regs->reg4.MTLD = 1;
  else
    regs->reg4.MTLD = 0;
}

void setVCOPowerDown(RegisterSet* regs, uint8_t powerDown)
{
  if(powerDown)
    regs->reg4.VCOPowerDown = 1;
  else
    regs->reg4.VCOPowerDown = 0;
}

void setBSCDV(RegisterSet* regs, uint8_t bscdVal)
{
  regs->reg4.BSCDV = bscdVal;
}

void setDividerSelect(RegisterSet* regs, uint8_t divSelect)
{
  if(divSelect > 0x6)
    divSelect = 0x6;

  regs->reg4.dividerSelect = divSelect;
}

void setFeedbackSelect(RegisterSet* regs, uint8_t select)
{
  if(select)
    regs->reg4.feedbackSelect = 1;
  else
    regs->reg4.feedbackSelect = 0;
}

void setLockDetectPinMode(RegisterSet* regs, uint8_t pinMode)
{
  if(pinMode > 0x3)
    pinMode = 0x3;

  regs->reg5.LDPinMode = pinMode;
}
