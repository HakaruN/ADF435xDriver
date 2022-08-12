#include "registerSet.h"

void setControlRegs(RegisterSet* regs)
{
  regs->reg0.bits.control = 0;
  regs->reg1.bits.control = 1;
  regs->reg2.bits.control = 2;
  regs->reg3.bits.control = 3;
  regs->reg4.bits.control = 4;
  regs->reg5.bits.control = 5;
  regs->reg5.bits.reserved1 = 0b11;
}

void setFraction(RegisterSet* regs, uint16_t frac)
{
  uint16_t mod = regs->reg1.bits.modulus;
  if(frac > mod - 1)
    frac = mod - 1;

  regs->reg0.bits.fraction = frac;
}

void setInteger(RegisterSet* regs, uint16_t integer)
{
  uint8_t prescalar = regs->reg1.bits.prescalar;
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

  regs->reg0.bits.integer = integer;
}

void setMod(RegisterSet* regs, uint16_t mod)
{
  if(mod > 0xFFF)
    mod = 0xFFF;
  regs->reg1.bits.modulus = mod;
}

void setPhaseVal(RegisterSet* regs, uint16_t phase)
{
  if(phase >= regs->reg1.bits.modulus)
    phase = phase - 1;
  regs->reg1.bits.phase = phase;
}

void setPrescalar(RegisterSet* regs, uint8_t prescalar)
{
  if(prescalar)
    regs->reg1.bits.prescalar = 1;
  else
    regs->reg1.bits.prescalar = 0;
}

void setPhaseAdjust(RegisterSet* regs, uint8_t phaseAdjust)
{
  if(phaseAdjust)
    regs->reg1.bits.phaseAdjust = 1;
  else
    regs->reg1.bits.phaseAdjust = 0;
}

void setCounterReset(RegisterSet* regs, uint8_t reset)
{
  if(reset)
    regs->reg2.bits.counterReset = 1;
  else
    regs->reg2.bits.counterReset = 0;
}

void setCPThreeState(RegisterSet* regs, uint8_t CPstate)
{
  if(CPstate)
    regs->reg2.bits.CPthreeState = 1;
  else
    regs->reg2.bits.CPthreeState = 0;
}

void setPowerDown(RegisterSet* regs, uint8_t powerDown)
{
  if(powerDown)
    regs->reg2.bits.PD = 1;
  else
    regs->reg2.bits.PD = 0;
}

void setPDPolarity(RegisterSet* regs, uint8_t polarity)
{
  if(polarity)
    regs->reg2.bits.PDPolarity = 1;
  else
    regs->reg2.bits.PDPolarity = 0;
}

void setLDP(RegisterSet* regs, uint8_t precision)
{
  if(precision)
    regs->reg2.bits.LDP = 1;
  else
    regs->reg2.bits.LDP = 0;
}

void setLDF(RegisterSet* regs, uint8_t function)
{
  if(function)
    regs->reg2.bits.LDF = 1;
  else
    regs->reg2.bits.LDF = 0;
}

void setCPCS(RegisterSet* regs, uint8_t currentSetting)
{
  if(currentSetting > 0xFF)
    currentSetting = 0xFF;

  regs->reg2.bits.CPCurrentSetting = currentSetting;

}

void setDoubleBuffer(RegisterSet* regs, uint8_t doubleBuff)
{
  if(doubleBuff)
    regs->reg2.bits.doubleBuffer = 1;
  else
    regs->reg2.bits.doubleBuffer = 0;
}

void setRCounter(RegisterSet* regs, uint16_t rCounter)
{
  if(rCounter > 1023)
    rCounter = 1023;

  regs->reg2.bits.RCounter = rCounter;
}

void setRdivBy2(RegisterSet* regs, uint8_t divBy2)
{
  if(divBy2)
    regs->reg2.bits.RDiv2 = 1;
  else
    regs->reg2.bits.RDiv2 = 0;
}

void setRefDoubler(RegisterSet* regs, uint8_t refDouble)
{
  if(refDouble)
    regs->reg2.bits.refDoubler = 1;
  else
    regs->reg2.bits.refDoubler = 0;
}

void setMuxOut(RegisterSet* regs, uint8_t muxOut)
{
  if(muxOut > 0x6)
    muxOut = 0;

  regs->reg2.bits.muxOut = muxOut;
}

void setLNAS(RegisterSet* regs, uint8_t lnas)
{
  if(lnas == 0x0 || lnas == 0x03)//check if valid option
    regs->reg2.bits.LNaS = lnas;
  else
    regs->reg2.bits.LNaS = 0x0;//default to low nois
}

void setClockDiv(RegisterSet* regs, uint16_t divVal)
{
  if(divVal > 0xFFF)
    divVal = 0xFFF;
  regs->reg3.bits.clockDivVal = divVal;
}

void setClockDivMode(RegisterSet* regs, uint8_t divMode)
{
  if(divMode > 0x2)
    divMode = 0x1;//default to fast loclkDivMk
  regs->reg3.bits.clkDivMode = divMode;
}

void setCSR(RegisterSet* regs, uint8_t csr)
{
  if(csr)
    regs->reg3.bits.CSR = 1;
  else
    regs->reg3.bits.CSR = 0;
}

void setChargeCancel(RegisterSet* regs, uint8_t chargeCancel)
{
  if(chargeCancel)
    regs->reg3.bits.chargeCancel = 1;
  else
    regs->reg3.bits.chargeCancel = 0;
}

void setABP(RegisterSet* regs, uint8_t ABP)
{
  if(ABP)
    regs->reg3.bits.ABP = 1;
  else
    regs->reg3.bits.ABP = 0;
}

void setBandSelectClockMode(RegisterSet* regs, uint8_t mode)
{
  if(mode)
    regs->reg3.bits.BSCM = 1;
  else
    regs->reg3.bits.BSCM = 0;
}

void setOutputPower(RegisterSet* regs, uint8_t power)
{
  if(power > 0x3)
    power = 0x3;
  regs->reg4.bits.outputPower = power;
}

void setOutputEnable(RegisterSet* regs, uint8_t enable)
{
  if(enable)
    regs->reg4.bits.outputEnable = 1;
  else
    regs->reg4.bits.outputEnable = 0;
}

void setAuxOutputPower(RegisterSet* regs, uint8_t power)
{
  if(power > 0x3)
      power = 0x3;
    regs->reg4.bits.auxOutputPower = power;
}

void setAuxOutputEnable(RegisterSet* regs, uint8_t enable)
{
  if(enable)
    regs->reg4.bits.auxOutputEnable = 1;
  else
    regs->reg4.bits.auxOutputEnable = 0;
}

void setAuxOutputSelect(RegisterSet* regs, uint8_t select)
{
  if(select)
    regs->reg4.bits.auxOutputSelect = 1;
  else
    regs->reg4.bits.auxOutputSelect = 0;
}

void setMTLD(RegisterSet* regs, uint8_t mtld)
{
  if(mtld)
    regs->reg4.bits.MTLD = 1;
  else
    regs->reg4.bits.MTLD = 0;
}

void setVCOPowerDown(RegisterSet* regs, uint8_t powerDown)
{
  if(powerDown)
    regs->reg4.bits.VCOPowerDown = 1;
  else
    regs->reg4.bits.VCOPowerDown = 0;
}

void setBSCDV(RegisterSet* regs, uint8_t bscdVal)
{
  regs->reg4.bits.BSCDV = bscdVal;
}

void setDividerSelect(RegisterSet* regs, uint8_t divSelect)
{
  if(divSelect > 0x6)
    divSelect = 0x6;

  regs->reg4.bits.dividerSelect = divSelect;
}

void setFeedbackSelect(RegisterSet* regs, uint8_t select)
{
  if(select)
    regs->reg4.bits.feedbackSelect = 1;
  else
    regs->reg4.bits.feedbackSelect = 0;
}

void setLockDetectPinMode(RegisterSet* regs, uint8_t pinMode)
{
  if(pinMode > 0x3)
    pinMode = 0x3;

  regs->reg5.bits.LDPinMode = pinMode;
}
