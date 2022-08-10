#ifndef REG_INTERFACE
#define REG_INTERFACE

#include "registerSet.h"

/* NOTE:
All registers should be programed backwards, that is reg 5, 4, 3, 2, 1 and 0 in that order
*/

void setControlRegs(RegisterSet* regs);

////Reg 0:
/* 12-Bit Fractional Value (FRAC)
The 12 FRAC bits (Bits[DB14:DB3]) set the numerator of the
fraction that is input to the Σ-Δ modulator. This fraction, along
with the INT value, specifies the new frequency channel that
the synthesizer locks to, as shown in the RF Synthesizer—A
Worked Example section. FRAC values from 0 to (MOD − 1)
cover channels over a frequency range equal to the PFD reference frequency. */
void setFraction(RegisterSet* regs, uint16_t frac);


/* 16-Bit Integer Value (INT)
The 16 INT bits (Bits[DB30:DB15]) set the INT value, which
determines the integer part of the feedback division factor. The
INT value is used in Equation 1 (see the INT, FRAC, MOD, and
R Counter Relationship section). Integer values from 23 to
65,535 are allowed for the 4/5 prescaler; for the 8/9 prescaler,
the minimum integer value is 75. */
void setInteger(RegisterSet* regs, uint16_t integer);
////Reg 1:
/* 12-Bit Modulus Value (MOD)
The 12 MOD bits (Bits[DB14:DB3]) set the fractional modulus.
The fractional modulus is the ratio of the PFD frequency to the
channel step resolution on the RF output. For more information,
see the 12-Bit Programmable Modulus section. */
void setMod(RegisterSet* regs, uint16_t mod);

/* 12-Bit Phase Value
Bits[DB26:DB15] control the phase word. The phase word must
be less than the MOD value programmed in Register 1. The phase
word is used to program the RF output phase from 0° to 360°
with a resolution of 360°/MOD (see the Phase Resync section).
In most applications, the phase relationship between the RF
signal and the reference is not important. In such applications,
the phase value can be used to optimize the fractional and subfractional spur levels. For more information, see the Spur
Consistency and Fractional Spur Optimization section.
If neither the phase resync nor the spurious optimization function is used, it is recommended that the phase word be set to 1. */
void setPhaseVal(RegisterSet* regs, uint16_t phase);

/* Prescaler Value
The dual-modulus prescaler (P/P + 1), along with the INT,
FRAC, and MOD values, determines the overall division
ratio from the VCO output to the PFD input. The PR1 bit
(DB27) in Register 1 sets the prescaler value.
Operating at CML levels, the prescaler takes the clock from the
VCO output and divides it down for the counters. The prescaler
is based on a synchronous 4/5 core. When the prescaler is set to
4/5, the maximum RF frequency allowed is 3.6 GHz. Therefore,
when operating the ADF4351 above 3.6 GHz, the prescaler must
be set to 8/9. The prescaler limits the INT value as follows:
- Prescaler = 4/5: NMIN = 23
- Prescaler = 8/9: NMIN = 75 */
void setPrescalar(RegisterSet* regs, uint8_t prescalar);

/* Phase Adjust
The phase adjust bit (Bit DB28) enables adjustment of the output
phase of a given output frequency. When phase adjustment is
enabled (Bit DB28 is set to 1), the part does not perform VCO
band selection or phase resync when Register 0 is updated.
When phase adjustment is disabled (Bit DB28 is set to 0), the
part performs VCO band selection and phase resync (if phase
resync is enabled in Register 3, Bits[DB16:DB15]) when Register 0
is updated. Disabling VCO band selection is recommended only
for fixed frequency applications or for frequency deviations of
<1 MHz from the originally selected frequency. */
void setPhaseAdjust(RegisterSet* regs, uint8_t phaseAdjust);

////Reg 2
/* Counter Reset
The DB3 bit is the reset bit for the R counter and the N counter
of the ADF4351. When this bit is set to 1, the RF synthesizer
N counter and R counter are held in reset. For normal operation, this bit should be set to 0. */
void counterReset(RegisterSet* regs);

/* Charge Pump Three-State
Setting the DB4 bit to 1 puts the charge pump into three-state
mode. This bit should be set to 0 for normal operation. */
void setCPThreeState(RegisterSet* regs, uint8_t CPstate);
/* Power-Down (PD)
The DB5 bit provides the programmable power-down mode.
Setting this bit to 1 performs a power-down. Setting this bit to 0
returns the synthesizer to normal operation. In software powerdown mode, the part retains all information in its registers. The
register contents are lost only if the supply voltages are removed.
When power-down is activated, the following events occur:
- Synthesizer counters are forced to their load state conditions.
- VCO is powered down.
- Charge pump is forced into three-state mode.
- Digital lock detect circuitry is reset.
- RFOUT buffers are disabled.
- Input registers remain active and capable of loading and
latching data.
*/
void setPowerDown(RegisterSet* regs, uint8_t powerDown);

/* Phase Detector Polarity
The DB6 bit sets the phase detector polarity. When a passive
loop filter or a noninverting active loop filter is used, this bit
should be set to 1. If an active filter with an inverting characteristic is used, this bit should be set to 0. */
void setPDPolarity(RegisterSet* regs, uint8_t polarity);

/* Lock Detect Precision (LDP)
The lock detect precision bit (Bit DB7) sets the comparison
window in the lock detect circuit. When DB7 is set to 0, the
comparison window is 10 ns; when DB7 is set to 1, the window
is 6 ns. The lock detect circuit goes high when n consecutive
PFD cycles are less than the comparison window value; n is set
by the LDF bit (DB8). For example, with DB8 = 0 and DB7 = 0,
40 consecutive PFD cycles of 10 ns or less must occur before
digital lock detect goes high.
For fractional-N applications, the recommended setting for
Bits[DB8:DB7] is 00; for integer-N applications, the recommended setting for Bits[DB8:DB7] is 11. */
void setLDP(RegisterSet* regs, uint8_t precision);

/* Lock Detect Function (LDF)
The DB8 bit configures the lock detect function (LDF). The LDF
controls the number of PFD cycles monitored by the lock detect
circuit to ascertain whether lock has been achieved. When DB8 is
set to 0, the number of PFD cycles monitored is 40. When DB8
is set to 1, the number of PFD cycles monitored is 5. It is recommended that the DB8 bit be set to 0 for fractional-N mode and
to 1 for integer-N mode. */
void setLDF(RegisterSet* regs, uint8_t function);

/* Charge Pump Current Setting
Bits[DB12:DB9] set the charge pump current. This value should
be set to the charge pump current that the loop filter is designed
with (see Figure 26). */
void setCPCS(RegisterSet* regs, uint8_t currentSetting);

/* Double Buffer
The DB13 bit enables or disables double buffering of
Bits[DB22:DB20] in Register 4. For information about how
double buffering works, see the Program Modes section. */
void setDoubleBuffer(RegisterSet* regs, uint8_t doubleBuff);

/* 10-Bit R Counter
The 10-bit R counter (Bits[DB23:DB14]) allows the input reference
frequency (REFIN) to be divided down to produce the reference
clock to the PFD. Division ratios from 1 to 1023 are allowed. */
void setRCounter(RegisterSet* regs, uint16_t rCounter);

/* RDIV2
Setting the DB24 bit to 1 inserts a divide-by-2 toggle flip-flop
between the R counter and the PFD, which extends the maximum
REFIN input rate. This function allows a 50% duty cycle signal to
appear at the PFD input, which is necessary for cycle slip reduction. */
void setRdivBy2(RegisterSet* regs, uint8_t divBy2);


/* Reference Doubler
Setting the DB25 bit to 0 disables the doubler and feeds the REFIN
signal directly into the 10-bit R counter. Setting this bit to 1 multiplies the REFIN frequency by a factor of 2 before feeding it into
the 10-bit R counter. When the doubler is disabled, the REFIN
falling edge is the active edge at the PFD input to the fractional
synthesizer. When the doubler is enabled, both the rising and
falling edges of REFIN become active edges at the PFD input.
When the doubler is enabled and the low spur mode is selected,
the in-band phase noise performance is sensitive to the REFIN duty
cycle. The phase noise degradation can be as much as 5 dB for
REFIN duty cycles outside a 45% to 55% range. The phase noise
is insensitive to the REFIN duty cycle in the low noise mode and
when the doubler is disabled.
The maximum allowable REFIN frequency when the doubler is
enabled is 30 MHz. */
void setRefDoubler(RegisterSet* regs, uint8_t refDouble);

/* MUXOUT
The on-chip multiplexer is controlled by Bits[DB28:DB26]
(see Figure 26). Note that N counter output must be disabled
for VCO band selection to operate correctly. */
void setMuxOut(RegisterSet* regs, uint8_t muxOut);
/* Low Noise and Low Spur Modes
The noise mode on the ADF4351 is controlled by setting
Bits[DB30:DB29] in Register 2 (see Figure 26). The noise mode
allows the user to optimize a design either for improved spurious
performance or for improved phase noise performance.
When the low spur mode is selected, dither is enabled. Dither
randomizes the fractional quantization noise so that it resembles
white noise rather than spurious noise. As a result, the part is
optimized for improved spurious performance. Low spur mode
is normally used for fast-locking applications when the PLL
closed-loop bandwidth is wide. Wide loop bandwidth is a loop
bandwidth greater than 1/10 of the RFOUT channel step resolution (fRES). A wide loop filter does not attenuate the spurs to the
same level as a narrow loop bandwidth.
For best noise performance, use the low noise mode option.
When the low noise mode is selected, dither is disabled. This
mode ensures that the charge pump operates in an optimum
region for noise performance. Low noise mode is extremely
useful when a narrow loop filter bandwidth is available. The
synthesizer ensures extremely low noise, and the filter attenuates
the spurs. Figure 10 through Figure 12 show the trade-offs in a
typical W-CDMA setup for different noise and spur settings. */

void setLNAS(RegisterSet* regs, uint8_t lnas);

////Reg 3
/* 12-Bit Clock Divider Value
Bits[DB14:DB3] set the 12-bit clock divider value. This value
is the timeout counter for activation of phase resync (see the
Phase Resync section). The clock divider value also sets the
timeout counter for fast lock (see the Fast Lock Timer and
Register Sequences section). */
void setClockDiv(RegisterSet* regs, uint16_t divVal);

/* Clock Divider Mode
Bits[DB16:DB15] must be set to 10 to activate phase resync
(see the Phase Resync section). These bits must be set to 01
to activate fast lock (see the Fast Lock Timer and Register
Sequences section). Setting Bits[DB16:DB15] to 00 disables
the clock divider (see Figure 27). */
void setClockDivMode(RegisterSet* regs, uint8_t divMode);

/* CSR Enable
Setting the DB18 bit to 1 enables cycle slip reduction. CSR is
a method for improving lock times. Note that the signal at the
phase frequency detector (PFD) must have a 50% duty cycle for
cycle slip reduction to work. The charge pump current setting
must also be set to a minimum. For more information, see the
Cycle Slip Reduction for Faster Lock Times section. */
void setCSR(RegisterSet* regs, uint8_t csr);

/* Charge Cancelation
   Setting the DB21 bit to 1 enables charge pump charge cancelation. This has the effect of reducing PFD spurs in integer */
void setChargeCancel(RegisterSet* regs, uint8_t chargeCancel);

/* Antibacklash Pulse Width (ABP)
Bit DB22 sets the PFD antibacklash pulse width. When Bit DB22
is set to 0, the PFD antibacklash pulse width is 6 ns. This setting is
recommended for fractional-N use. When Bit DB22 is set to 1,
the PFD antibacklash pulse width is 3 ns, which results in phase
noise and spur improvements in integer-N operation. For
fractional-N operation, the 3 ns setting is not recommended. */
void setABP(RegisterSet* regs, uint8_t ABP);

/* Band Select Clock Mode
Setting the DB23 bit to 1 selects a faster logic sequence of band
selection, which is suitable for high PFD frequencies and is
necessary for fast lock applications. Setting the DB23 bit to 0 is
recommended for low PFD (<125 kHz) values. For the faster
band select logic modes (DB23 set to 1), the value of the band
select clock divider must be less than or equal to 254. */
void setBandSelectClockMode(RegisterSet* regs, uint8_t mode);

////Reg 4
/* Output Power
Bits[DB4:DB3] set the value of the primary RF output power
level (see Figure 28). */
void setOutputPower(RegisterSet* regs, uint8_t power);

/* RF Output Enable
The DB5 bit enables or disables the primary RF output. If DB5
is set to 0, the primary RF output is disabled; if DB5 is set to 1,
the primary RF output is enabled. */
void setOutputEnable(RegisterSet* regs, uint8_t enable);

/* AUX Output Power
Bits[DB7:DB6] set the value of the auxiliary RF output power
level (see Figure 28) */
void setAuxOutputPower(RegisterSet* regs, uint8_t power);

/* AUX Output Enable
The DB8 bit enables or disables the auxiliary RF output. If DB8
is set to 0, the auxiliary RF output is disabled; if DB8 is set to 1,
the auxiliary RF output is enabled. */
void setAuxOutputEnable(RegisterSet* regs, uint8_t enable);

/* AUX Output Select
The DB9 bit sets the auxiliary RF output. If DB9 is set to 0, the
auxiliary RF output is the output of the RF dividers; if DB9 is set
to 1, the auxiliary RF output is the fundamental VCO frequency. */
void setAuxOutputSelect(RegisterSet* regs, uint8_t select);

/*Mute Till Lock Detect (MTLD)
When the DB10 bit is set to 1, the supply current to the RF output
stage is shut down until the part achieves lock, as measured by
the digital lock detect circuitry */
void setMTLD(RegisterSet* regs, uint8_t mtld);

/* VCO Power-Down
Setting the DB11 bit to 0 powers the VCO up; setting this bit to 1
powers the VCO down */
void setVCOPowerDown(RegisterSet* regs, uint8_t powerDown);

/* Band Select Clock Divider Value
Bits[DB19:DB12] set a divider for the band select logic clock input.
By default, the output of the R counter is the value used to clock
the band select logic, but, if this value is too high (>125 kHz), a
divider can be switched on to divide the R counter output to a
smaller value (see Figure 28). */
void setBSCDV(RegisterSet* regs, uint8_t bscdVal);

/* RF Divider Select
Bits[DB22:DB20] select the value of the RF output divider (see
Figure 28). */
void setDividerSelect(RegisterSet* regs, uint8_t divSelect);

/* Feedback Select
The DB23 bit selects the feedback from the VCO output to the
N counter. When this bit is set to 1, the signal is taken directly
from the VCO. When this bit is set to 0, the signal is taken from
the output of the output dividers. The dividers enable coverage
of the wide frequency band (34.375 MHz to 4.4 GHz). When
the dividers are enabled and the feedback signal is taken from
the output, the RF output signals of two separately configured
PLLs are in phase. This is useful in some applications where the
positive interference of signals is required to increase the power */
void setFeedbackSelect(RegisterSet* regs, uint8_t select);

////Reg 5
/* Lock Detect Pin Operation
Bits[DB23:DB22] set the operation of the lock detect (LD) pin
(see Figure 29). */
void setLockDetectPinMode(RegisterSet* regs, uint8_t pinMode);



#endif
