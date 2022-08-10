#ifndef REG_DEF
#define REG_DEF
#include <stdint.h>
typedef uint32_t RegType;
//See datasheet register set for the ADF435x datasheet
//found: https://www.analog.com/media/en/technical-documentation/data-sheets/ADF4350.pdf

typedef struct Reg0
{
  RegType control:3; //Control reg bottom 3 bits - 0:2
  RegType fraction:12;//Fraction reg - 3:14
  RegType integer:16;//Integer reg - 15:30
  RegType reserved:1;//Reserved reg - 31
} Reg0;

typedef struct Reg1
{
  RegType control:3; //Control reg bottom 3 bits - 0:2
  RegType modulus:12;//Modulus reg - 3:14
  RegType phase:12;//Phase reg - 15:23
  RegType prescalar:1;//Prescalar reg - 27
  RegType phaseAdjust:1;//phase adjust reg - 28
  RegType reserved:3;//Reserved reg - 29:31
} Reg1;

typedef struct Reg2
{
  RegType control:3; //Control reg bottom 3 bits - 0:2
  RegType counterReset:1; //Counter reset - 3
  RegType CPthreeState:1; //Charge Pump three state - 4
  RegType PD:1; //PD - 5
  RegType PDPolarity:1; //Phase detect polarity - 6
  RegType LDP:1; //Lock detect precision - 7
  RegType LDF:1; //LDF - 8
  RegType CPCurrentSetting:4; //Charge Pump current setting - 9:12
  RegType doubleBuffer:1; //Double buffer - 13
  RegType RCounter:10; //R counter - 14:23
  RegType RDiv2:1; //R div by 2 - 24
  RegType refDoubler:1; //Reference doubler - 25
  RegType muxOut:3; //Multiplexer output - 26:28
  RegType LNaS:2; //Low noise and spur modes - 29:30
  RegType reserved:1;//Reserved reg - 31
} Reg2;

typedef struct Reg3
{
  RegType control:3; //Control reg bottom 3 bits - 0:2
  RegType clockDivVal:12; //Clock divider val - 3:14
  RegType clkDivMode:2; //Clock divider mode - 15:16
  RegType reserved0:1; //Reserved - 17
  RegType CSR:1; //Cycle slip reduction - 18
  RegType reserved1:2; //Reserved 19-20
  RegType chargeCancel:1; //Charge cancel - 21
  RegType ABP:1; //Antibacklash pulse - 22
  RegType BSCM:1; //Band select clock mode -23
  RegType reserved2:8;//Rerved reg - 24:31
} Reg3;

typedef struct Reg4
{
  RegType control:3; //Control reg bottom 3 bits - 0:2
  RegType outputPower:2; //Output power - 3:4
  RegType outputEnable:1; //RF output enable - 5
  RegType auxOutputPower:2; //Auxilary output power - 6:7
  RegType auxOutputEnable:1; //Auxilary output enable - 8
  RegType auxOutputSelect:1; //Auxilary output select - 9
  RegType MTLD:1; //MTLD - 10
  RegType VCOPowerDown:1; //VCO power down - 11
  RegType BSCDV:8; //Band select clock div value - 12:19
  RegType dividerSelect:3; //DBB divider select - 20:22
  RegType feedbackSelect:1; //Feedback select - 23
  RegType reserved:8; //Reserved reg - 24:32
} Reg4;

typedef struct Reg5
{
  RegType control:3; //Control reg bottom 3 bits - 0:2
  RegType reserved0:16; //Reserved reg - 3:18
  RegType reserved1:2; //Reserved reg - 19:20
  RegType reserved2:1; //Reserved reg - 21
  RegType LDPinMode:2; //LD pin mode - 22:23
  RegType reserved3:8; //Reserved reg - 24:31
} Reg5;

#endif
