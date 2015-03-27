//general instructions
case 0xA9: IMM(LDA)
case 0xA2: IMM(LDX)
case 0xA0: IMM(LDY)
case 0xA5: ZP(LDA)
case 0xB5: ZPX(LDA)
case 0xAD: ABS(LDA)
case 0xBD: ABX(LDA)
case 0xB9: ABY(LDA)
case 0xA1: INX(LDA)
case 0xB1: INY(LDA)
case 0xA6: ZP(LDX)
case 0xB6: ZPY(LDX)
case 0xAE: ABS(LDX)
case 0xBE: ABY(LDX)
case 0xA4: ZP(LDY)
case 0xB4: ZPX(LDY)
case 0xAC: ABS(LDY)
case 0xBC: ABX(LDY)

case 0x69: IMM(ADC)
case 0x65: ZP(ADC)
case 0x75: ZPX(ADC)
case 0x6D: ABS(ADC)
case 0x7D: ABX(ADC)
case 0x79: ABY(ADC)
case 0x61: INX(ADC)
case 0x71: INY(ADC)

case 0x29: IMM(AND)
case 0x25: ZP(AND)
case 0x35: ZPX(AND)
case 0x2D: ABS(AND)
case 0x3D: ABX(AND)
case 0x39: ABY(AND)
case 0x21: INX(AND)
case 0x31: INY(AND)

case 0x0A: ACC(ASL)
case 0x06: ZP(ASL)
case 0x16: ZPX(ASL)
case 0x0E: ABS(ASL)
case 0x1E: ABX(ASL)

case 0xC6: ZP(DEC)
case 0xD6: ZPX(DEC)
case 0xCE: ABS(DEC)
case 0xDE: ABX(DEC)

case 0xE6: ZP(INC)
case 0xF6: ZPX(INC)
case 0xEE: ABS(INC)
case 0xFE: ABX(INC)

case 0x49: IMM(EOR)
case 0x45: ZP(EOR)
case 0x55: ZPX(EOR)
case 0x4D: ABS(EOR)
case 0x5D: ABX(EOR)
case 0x59: ABY(EOR)
case 0x41: INX(EOR)
case 0x51: INY(EOR)

case 0x4A: ACC(LSR)
case 0x46: ZP(LSR)
case 0x56: ZPX(LSR)
case 0x4E: ABS(LSR)
case 0x5E: ABX(LSR)

case 0x09: IMM(ORA)
case 0x05: ZP(ORA)
case 0x15: ZPX(ORA)
case 0x0D: ABS(ORA)
case 0x1D: ABX(ORA)
case 0x19: ABY(ORA)
case 0x01: INX(ORA)
case 0x11: INY(ORA)

case 0x2A: ACC(ROL)
case 0x26: ZP(ROL)
case 0x36: ZPX(ROL)
case 0x2E: ABS(ROL)
case 0x3E: ABX(ROL)

case 0x6A: ACC(ROR)
case 0x66: ZP(ROR)
case 0x76: ZPX(ROR)
case 0x6E: ABS(ROR)
case 0x7E: ABX(ROR)

case 0xE9: IMM(SBC)
case 0xE5: ZP(SBC)
case 0xF5: ZPX(SBC)
case 0xED: ABS(SBC)
case 0xFD: ABX(SBC)
case 0xF9: ABY(SBC)
case 0xE1: INX(SBC)
case 0xF1: INY(SBC)

case 0x85: ZP(STA)
case 0x95: ZPX(STA)
case 0x8D: ABS(STA)
case 0x9D: ABX(STA)
case 0x99: ABY(STA)
case 0x81: INX(STA)
case 0x91: INY(STA)
case 0x86: ZP(STX)
case 0x96: ZPY(STX)
case 0x8E: ABS(STX)
case 0x84: ZP(STY)
case 0x94: ZPX(STY)
case 0x8C: ABS(STY)

case 0x24: ZP(BTEST)
case 0x2C: ABS(BTEST)

case 0xC9: IMM(CMP)
case 0xC5: ZP(CMP)
case 0xD5: ZPX(CMP)
case 0xCD: ABS(CMP)
case 0xDD: ABX(CMP)
case 0xD9: ABY(CMP)
case 0xC1: INX(CMP)
case 0xD1: INY(CMP)

case 0xE0: IMM(CPX)
case 0xE4: ZP(CPX)
case 0xEC: ABS(CPX)

case 0xC0: IMM(CPY)
case 0xC4: ZP(CPY)
case 0xCC: ABS(CPY)

//jumps
case 0x4C: ABSJMP(JMP)
case 0x6C: INJMP(JMP)
case 0x20: ABSJMP(JSR)

//flags
case 0x18: CL(C_FLAG,_P);
case 0x38: SE(C_FLAG,_P);
case 0x58: CL(I_FLAG,_P);
case 0x78: SE(I_FLAG,_P);
case 0xB8: CL(V_FLAG,_P);
case 0xD8: CL(D_FLAG,_P);
case 0xF8: SE(D_FLAG,_P);

//implied instructions
case 0xEA: NOP
case 0xAA: TAX
case 0x8A: TXA
case 0xCA: DECX
case 0xE8: INCX
case 0xA8: TAY
case 0x98: TYA
case 0x88: DECY
case 0xC8: INCY
case 0x40: RTI
case 0x60: RTS
case 0x00: BRK

//stack instructions
case 0x9A: TXS
case 0xBA: TSX
case 0x48: PHA
case 0x68: PLA
case 0x08: PHP
case 0x28: PLP

//branches
case 0x10: BR(NFC)
case 0x30: BR(NFS)
case 0x50: BR(VFC)
case 0x70: BR(VFS)
case 0x90: BR(CFC)
case 0xB0: BR(CFS)
case 0xD0: BR(ZFC)
case 0xF0: BR(ZFS)

default: {printf("Error: Opcode 0x%x not found\n",opcode);return 0;}