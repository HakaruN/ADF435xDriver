#ifndef ADF4351_ENUMS
#define ADF4351_ENUMS


////REG 1
//Reg 1 prescalar vals
enum PRESCALAR { _4over5, _8over9 };

////REG 2
enum LOW_NOISE_LOW_SPUR {LOW_NOISE = 0b00, LOW_SPUR = 0b11};
enum MUX_OUT {
  TRI_STATE, DV, D_GND,
  R_COUNTER, N_DIVIDER,
  ANALOG_LOCK_DETECT,
  DIGITAL_LOCK_DETECT
};

enum CHARGE_PUMP_CURRENT_SETTING {
  _0_31, _0_63, _0_94, _1_25,
  _1_56, _1_88, _2_19, _2_50,
  _2_81, _3_13, _3_44, _3_75,
  _4_06, _4_38, _4_69, _5_00
};

enum LOCK_DETECT_FUNCTION {
  FRACTIONAL_N,//not specificaly fractional n but is recomended for that. Really it makes the lock-detect hardware wait for 40 cycles before determining a lock.
  INTEGER_N//not specifically for integer n but is recomended for that. It really just means the lock-detector waits only 5 cycles before detecting a lock.
};

enum LOCK_DETECT_POLARITY {
  _10ns,
  _6ns
};

enum PD_POLARITY {
  NEGATIVE,
  POSITIVE
};

enum POWER_DOWN {
  POWER_ON, POWER_OFF
};

enum CHARGE_PUMP_TRISTATE_STATE {
  PUMP_NORMAL_OPERATION,
  CHARGE_PUMP_IN_TRISTATE
};

enum COUNTER_RESET {
  COUNTER_OPERATING,
  R_N_COUNTER_RESET
};
////REG 3
enum BAND_SELECT_CLOCK_MODE {
  LOW, HIGH //LOW recomended for pfd freq < 125Khz, HIGH needs band select clock div <=254
};

enum ABP_PULSE_WIDTH {
  ABPW_6ns, ABPW_3ns //6ns for frac-n, 3 improves noise and spur good for int-n, not recomended for frac-n
};

enum CHARGE_CANCELATION {
  NOT_CHARGE_PUMP_CANCEL, //should be used in frac-n
  CHARGE_PUMP_CANCEL //reducdes PDF spurs in int-n
};

enum CYLCE_SLIP_REDUCTION {
  CSR_ENABLE, //improves lock time, note signal at pfd should have 50% duty cycle for CSR to work, the charge pump current should be minimum
  CSR_DISABLE
};

enum CLOCK_DIV_MODE {
  CLOCK_DIV_OFF,
  FAST_LOCK_ENABLE,
  RESYNC_ENABLE
};

////REG 4
enum FEEDBACK_SELECT {
  DIVIDED, //VCO output goes through output dividers then to N counter. Divide ratio set in with next enum
  FUNDAMENTAL //VCO output goes directly to the N counter
};

enum RF_DIVIDE_SELECT {
  DIV_BY_1,
  DIV_BY_2,
  DIV_BY_4,
  DIV_BY_8,
  DIV_BY_16,
  DIV_BY_32,
  DIV_BY_64
};


enum VCO_POWER_DOWN {
  POWER_UP,
  POWER_DOWN
};

enum MTLD {
  NO_MUTE,
  MUTE
};

enum AUX_OUTPUT_SELECT {
  AUX_OUTPUT_DIVIDED,
  AUX_OUTPUT_FUNDAMENTAL
};

enum AUX_OUTPUT_ENABLE {
  AUX_DISABLED,
  AUX_ENABLED
};

enum AUX_OUTPUT_POWER {
  _NEG4dbm, _NEG1dbm,
  _POS2dbm, _POS5dbm
};

enum RF_OUTPUT_ENABLE {
  RF_DISABLED,
  RF_ENABLED
};

////REG 5
enum LD_PIN_MODE {
  LD_LOW, LD_DIGITAL_LOCK_EVENT,
  LD_HIGH = 3
};









#endif
