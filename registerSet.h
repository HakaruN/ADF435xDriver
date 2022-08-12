#ifndef REG_SET
#define REG_SET

#include "regDefs.h"

//Collection of all the registers for the ADF435x

//The union allows the reg to be accessed either of as a whole word or as it's individual bits
//or as a series of 4 bytes. The bits are used to write individual fields into a reg, the reg (word)
//is used to wipe/initialise the entire reg with a single val and the byte array is used to read the
//reg one byte at a time used for transmitting over a serial interface that operates on a byte-by-byte basis
typedef union Reg0
{
  Reg0bits bits;
  RegType reg;
  Byte bytes [4];
} Reg0;

typedef union Reg1
{
  Reg1bits bits;
  RegType reg;
  Byte bytes [4];
} Reg1;

typedef union Reg2
{
  Reg2bits bits;
  RegType reg;
  Byte bytes [4];
} Reg2;

typedef union Reg3
{
  Reg3bits bits;
  RegType reg;
  Byte bytes [4];
} Reg3;

typedef union Reg4
{
  Reg4bits bits;
  RegType reg;
  Byte bytes [4];
} Reg4;

typedef union Reg5
{
  Reg5bits bits;
  RegType reg;
  Byte bytes [4];
} Reg5;

typedef struct RegisterSet
{
  //The registers are aranged decending so in memory the
  //first register to write is at the begining, this is because
  //when writing I do a memcpy of the struct and run through
  //sending the bytes straight over spi
  Reg5 reg5;
  Reg4 reg4;
  Reg3 reg3;
  Reg2 reg2;
  Reg1 reg1;
  Reg0 reg0;
} RegisterSet;
#endif
