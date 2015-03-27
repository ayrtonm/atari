#ifndef CPU_H
#define CPU_H
#include "common.h"

//processor status (P) flag numbers
#define C_FLAG 0
#define Z_FLAG 1
#define I_FLAG 2
#define D_FLAG 3
#define B_FLAG 4
#define U_FLAG 5
#define V_FLAG 6
#define N_FLAG 7

//registers
#define _S (A->S)
#define _P (A->P)
#define _X (A->X)
#define _Y (A->Y)
#define _A (A->A)
#define _PC (A->PC)
#define _CLK (A->CLK)

//locations in memory
#define ARG (readmem(_PC-1))
#define ARGS (readmem(_PC-2)+(ARG<<8))

//address modes
//ex: How PC works
//  [IMM(ADC)]  [0x44]  [ABS(ADC)]  [0x44]  [0x00]  [...]
//  1._PC points at instruction IMM(ADC)
//  2.cpu fetches instruction(start switch case),
//  checks for page crossing, and increments PC by 1(point to 1st operand)
//  3.increment PC by number of operands so it points to next instruction
//  4.load operand at mem[_PC-1] and/or mem[_PC-2]
#define ACC(ops) {x=_A;ops;break;}
#define IMM(ops) {_PC+=1;x=ARG;ops;break;}
#define ZP(ops) {_PC+=1;x=readmem(ARG);ops;break;}
#define ZPX(ops) {_PC+=1;x=readmem(ARG+_X);ops;break;}
#define ZPY(ops) {_PC+=1;x=readmem(ARG+_Y);ops;break;}
#define ABS(ops) {_PC+=2;x=readmem(ARGS);ops;break;}
#define ABX(ops) {_PC+=2;x=readmem(ARGS+_X);ops;break;}
#define ABY(ops) {_PC+=2;x=readmem(ARGS+_Y);ops;break;}
#define INX(ops) {_PC+=1;x=readmem(readmem(ARG+_X));ops;break;}
#define INY(ops) {_PC+=1;x=readmem(readmem(ARG)+_Y);ops;break;}

#define ABSJMP(ops) {_PC+=2;temp16=(ARGS);ops;break;}
#define INJMP(ops) {_PC+=2;temp16=readmem(ARGS);ops;break;}

//flags macros
//some instructions set C_FLAG differently
#define CTEST(x) SETX(C_FLAG,_P,((x) > 0x00FF));
#define ZTEST(x) SETX(Z_FLAG,_P,((x) == 0));
#define VTEST SETX(V_FLAG,_P,((GET(C_FLAG,_P)) ^ (GET(N_FLAG,_P))));
#define NTEST(x) SETX(N_FLAG,_P,GET(7,(x)));
#define CARRY GET(C_FLAG,_P)
#define DECIMAL GET(D_FLAG,_P)
#define NEGATIVE GET(N_FLAG,_P)
#define OVERFLOW GET(V_FLAG,_P)
#define ZERO GET(Z_FLAG,_P)

//general instructions
//use x as address mode variable
#define ADC if(DECIMAL==0){temp16=_A+x+CARRY;_A=(temp16 & 0x00FF);}\
            else {temp16=(_A & 0x0F)+(x & 0x0F)+CARRY;if(temp16>=10){temp16 =(temp16-10) | 0x10;}temp16+=(_A & 0xF0)+(x & 0xF0);}\
            NTEST(_A);ZTEST(_A);CTEST(temp16);VTEST;_CLK-=crossing;t-=crossing
#define AND _A&=x;NTEST(_A);ZTEST(_A);_CLK-=crossing;t-=crossing
#define ASL SETX(C_FLAG,_P,GET(7,x));x<<1;NTEST(x);ZTEST(x)
#define BTEST SETX(Z_FLAG,_P,((x) & _A) == 0);NTEST(x);SETX(V_FLAG,_P,GET(6,x))
#define CMP CP(_A)
#define CPX CP(_X)
#define CPY CP(_Y)
#define CP(r) SETX(C_FLAG,_P,(r >=x));ZTEST(x);NTEST(x);_CLK-=crossing;t-=crossing
#define DEC x--;NTEST(x);ZTEST(x)
#define EOR _A^=x;NTEST(x);ZTEST(x);_CLK-=crossing;t-=crossing
#define INC x++;NTEST(x);ZTEST(x)
#define LD(r) r=x;NTEST(x);ZTEST(x);_CLK-=crossing;t-=crossing
#define LDA LD(_A)
#define LDX LD(_X)
#define LDY LD(_Y)
#define LSR SETX(C_FLAG,_P,GET(0,x));x>>1;NTEST(x);ZTEST(x)
#define ORA _A|=x;NTEST(_A);ZTEST(_A);_CLK-=crossing;t-=crossing
#define ROL temp8 = CARRY;SETX(C_FLAG,_P,GET(7,x));x<<1;SETX(0,x,temp8);NTEST(x);ZTEST(x)
#define ROR temp8 = CARRY;SETX(C_FLAG,_P,GET(0,x));x>>1;SETX(7,x,temp8);NTEST(x);ZTEST(x)
#define SBC if(DECIMAL==0) {temp16=_A+CARRY-1-x;_A=(temp16 & 0x00FF);}\
            else {uint8 al,ah;temp16=_A+CARRY-1-x;al=(_A & 0x0F)-(x & 0x0F)-1+CARRY;ah=(_A>>4)+(x>>4);if(al&0x10){al-=6;ah--;}if(ah&0x10){ah-=6;}_A=(ah<<4)+(al & 0x0F);}\
            NTEST(_A);ZTEST(_A);CTEST(temp16);VTEST;_CLK-=crossing;t-=crossing
#define ST(r) writemem(r,x)
#define STA ST(_A)
#define STX ST(_X)
#define STY ST(_Y)

//jumps
#define JMP _PC=temp16
#define JSR mem[readmem(STACK)]=(((_PC+2)&0xFF00)>>8);mem[readmem(STACK)-1]=((_PC+2)&0x00FF);_S-=2;_PC=temp16

//implied instructions
#define RTI {_S++;_P=mem[readmem(STACK)];_S+=2;_PC=mem[readmem(STACK)-1]+(mem[readmem(STACK)]<<8);break;}
#define RTS {_S+=2;_PC=mem[readmem(STACK)]+(mem[readmem(STACK)-1]<<8)+1;break;}
#define NOP {break;}
#define CL(n,x) {CLEAR(n,x);break;}
#define SE(n,x) {SET(n,x);break;}
#define BRK {break;}

//general implied instructions
#define TAX {_X=_A;NTEST(_X);ZTEST(_X);break;}
#define TXA {_A=_X;NTEST(_A);ZTEST(_A);break;}
#define DECX {_X--;NTEST(_X);ZTEST(_X);break;}
#define INCX {_X++;NTEST(_X);ZTEST(_X);break;}
#define TAY {_Y=_A;NTEST(_Y);ZTEST(_Y);break;}
#define TYA {_A=_Y;NTEST(_A);ZTEST(_A);break;}
#define DECY {_Y--;NTEST(_Y);ZTEST(_Y);break;}
#define INCY {_Y++;NTEST(_Y);ZTEST(_Y);break;}

//readmem(STACK) instructions
#define TXS {_S=_X;break;}
#define TSX {_X=_S;break;}
#define PHA {mem[readmem(STACK)]=_A;_S--;break;}
#define PHP {SET(B_FLAG,_P);SET(U_FLAG,_P);mem[readmem(STACK)]=_P;_S--;break;}
#define PLA {_S++;_A=mem[readmem(STACK)];NTEST(_A);ZTEST(_A);break;}
#define PLP {_S++;_P=mem[readmem(STACK)];break;}

//branch
#define BR(condition) {_PC+=1;if (condition)\
                         {_CLK-=(1+crossing);t-=(1+crossing);\
                          if(GET(7,ARG)==0){_PC+=ARG;break;}\
                          if(ARG==0x80){_PC-=0x80;break;}\
                          else{_PC-=COMPLEMENT(ARG);break;}}\
                       else {break;}}
#define NFC (NEGATIVE == 0)
#define NFS (NEGATIVE == 1)
#define VFC (OVERFLOW == 0)
#define VFS (OVERFLOW == 1)
#define CFC (CARRY == 0)
#define CFS (CARRY == 1)
#define ZFC (ZERO == 0)
#define ZFS (ZERO == 1)

typedef struct cpu
{
  uint8 A,X,Y,S,P;
  int PC,CLK;
  int running;
} cpu;
static const uint8 cycles[0x0100] =
{
  7,6,0,0,0,2,5,0,3,2,2,0,0,4,6,0,
  2,5,0,0,0,3,6,0,2,4,0,0,0,4,7,0,
  6,6,0,0,3,2,5,0,4,2,2,0,4,4,6,0,
  2,5,0,0,0,3,6,0,2,4,0,0,0,4,7,0,
  6,6,0,0,0,3,5,0,3,2,2,0,3,4,6,0,
  2,5,0,0,0,4,6,0,2,4,0,0,0,4,7,0,
  6,6,0,0,0,3,5,0,4,2,2,0,5,4,6,0,
  2,5,0,0,0,4,6,0,2,4,0,0,0,4,7,0,
  0,6,0,0,3,3,3,0,2,0,2,0,4,4,4,0,
  2,6,0,0,4,4,4,0,2,5,2,0,0,5,0,0,
  2,6,2,0,3,3,3,0,2,2,2,0,4,4,4,0,
  2,5,0,0,4,4,4,0,2,4,2,0,4,4,4,0,
  2,6,0,0,3,3,5,0,2,2,2,0,4,4,6,0,
  2,5,0,0,0,4,6,0,2,4,0,0,0,4,7,0,
  2,6,0,0,3,3,5,0,2,2,2,0,4,4,6,0,
  2,5,0,0,0,4,6,0,2,4,0,0,0,4,7,0
};

uint8 x;

extern cpu * initialize_cpu(void);
extern int emulate_cpu(cpu *);
#endif