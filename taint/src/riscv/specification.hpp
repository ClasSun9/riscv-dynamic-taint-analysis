# ifndef _RISCV__SPECIFICATION_HPP_
# define _RISCV__SPECIFICATION_HPP_

# include "types.hpp"

namespace riscv {

class opcode {
public:

    static constexpr insn_t illegal = 0xffffffff;

    // 0110111
    static constexpr insn_t lui     = 0;
    // 0010111 
    static constexpr insn_t auipc   = 1;
    // 1101111 
    static constexpr insn_t jal     = 2;
    // 1100111 
    static constexpr insn_t jalr    = 3;
    // 1100011 
    static constexpr insn_t beq     = 4;
    static constexpr insn_t bne     = 5;
    static constexpr insn_t blt     = 6;
    static constexpr insn_t bge     = 7;
    static constexpr insn_t bltu    = 8;
    static constexpr insn_t bgeu    = 9;
    // 0000011 
    static constexpr insn_t lb      = 10;
    static constexpr insn_t lh      = 11;
    static constexpr insn_t lw      = 12;
    static constexpr insn_t ld      = 13;
    static constexpr insn_t lbu     = 14;
    static constexpr insn_t lhu     = 15;
    static constexpr insn_t lwu     = 16;
    // 0100011 
    static constexpr insn_t sb      = 17;
    static constexpr insn_t sh      = 18;
    static constexpr insn_t sw      = 19;
    static constexpr insn_t sd      = 20;
    // 0110011 
    static constexpr insn_t add     = 21;
    static constexpr insn_t sub     = 22;
    static constexpr insn_t sll     = 23;
    static constexpr insn_t slt     = 24;
    static constexpr insn_t sltu    = 25;
    static constexpr insn_t xor_    = 26;
    static constexpr insn_t srl     = 27;
    static constexpr insn_t sra     = 28;
    static constexpr insn_t or_     = 29;
    static constexpr insn_t and_    = 30;
    static constexpr insn_t mul     = 31;
    static constexpr insn_t mulh    = 32;
    static constexpr insn_t mulhsu  = 33;
    static constexpr insn_t mulhu   = 34;
    static constexpr insn_t div     = 35;
    static constexpr insn_t divu    = 36;
    static constexpr insn_t rem     = 37;
    static constexpr insn_t remu    = 38;
    // 0111011 
    static constexpr insn_t addw    = 39;
    static constexpr insn_t subw    = 40;
    static constexpr insn_t sllw    = 41;
    static constexpr insn_t srlw    = 42;
    static constexpr insn_t sraw    = 43;
    static constexpr insn_t mulw    = 44;
    static constexpr insn_t divw    = 45;
    static constexpr insn_t divuw   = 46;
    static constexpr insn_t remw    = 47;
    static constexpr insn_t remuw   = 48;
    // 0010011 
    static constexpr insn_t addi    = 49;
    static constexpr insn_t slti    = 50;
    static constexpr insn_t sltiu   = 51;
    static constexpr insn_t xori    = 52;
    static constexpr insn_t ori     = 53;
    static constexpr insn_t andi    = 54;
    static constexpr insn_t slli    = 55;
    static constexpr insn_t srli    = 56;
    static constexpr insn_t srai    = 57;
    // 0011011 
    static constexpr insn_t addiw   = 58;
    static constexpr insn_t slliw   = 59;
    static constexpr insn_t srliw   = 60;
    static constexpr insn_t sraiw   = 61;
    // 0001111
    static constexpr insn_t fence    = 62;
    static constexpr insn_t fencetso = 63;
    static constexpr insn_t pause    = 64;
    // 1110011
    static constexpr insn_t ecall    = 65;
    static constexpr insn_t ebreak   = 66;
};

class gpregister {
public:

    class numeric {
    public:
        static constexpr insn_t x0  = 0;
        static constexpr insn_t x1  = 1;
        static constexpr insn_t x2  = 2;
        static constexpr insn_t x3  = 3;
        static constexpr insn_t x4  = 4;
        static constexpr insn_t x5  = 5;
        static constexpr insn_t x6  = 6;
        static constexpr insn_t x7  = 7;
        static constexpr insn_t x8  = 8;
        static constexpr insn_t x9  = 9;
        static constexpr insn_t x10 = 10;
        static constexpr insn_t x11 = 11;
        static constexpr insn_t x12 = 12;
        static constexpr insn_t x13 = 13;
        static constexpr insn_t x14 = 14;
        static constexpr insn_t x15 = 15;
        static constexpr insn_t x16 = 16;
        static constexpr insn_t x17 = 17;
        static constexpr insn_t x18 = 18;
        static constexpr insn_t x19 = 19;
        static constexpr insn_t x20 = 20;
        static constexpr insn_t x21 = 21;
        static constexpr insn_t x22 = 22;
        static constexpr insn_t x23 = 23;
        static constexpr insn_t x24 = 24;
        static constexpr insn_t x25 = 25;
        static constexpr insn_t x26 = 26;
        static constexpr insn_t x27 = 27;
        static constexpr insn_t x28 = 28;
        static constexpr insn_t x29 = 29;
        static constexpr insn_t x30 = 30;
        static constexpr insn_t x31 = 31;

        static constexpr char *name[] = {
            "x0",  "x1",  "x2",  "x3",
            "x4",  "x5",  "x6",  "x7",
            "x8",  "x9",  "x10", "x11",
            "x12", "x13", "x14", "x15",
            "x16", "x17", "x18", "x19",
            "x20", "x21", "x22", "x23",
            "x24", "x25", "x26", "x27",
            "x28", "x29", "x30", "x31"
        };
    };

    class abi {
    public:
        static constexpr insn_t zero = 0;
        static constexpr insn_t ra   = 1;
        static constexpr insn_t sp   = 2;
        static constexpr insn_t gp   = 3;
        static constexpr insn_t tp   = 4;
        static constexpr insn_t t0   = 5;
        static constexpr insn_t t1   = 6;
        static constexpr insn_t t2   = 7;
        static constexpr insn_t s0   = 8;
        static constexpr insn_t s1   = 9;
        static constexpr insn_t a0   = 10;
        static constexpr insn_t a1   = 11;
        static constexpr insn_t a2   = 12;
        static constexpr insn_t a3   = 13;
        static constexpr insn_t a4   = 14;
        static constexpr insn_t a5   = 15;
        static constexpr insn_t a6   = 16;
        static constexpr insn_t a7   = 17;
        static constexpr insn_t s2   = 18;
        static constexpr insn_t s3   = 19;
        static constexpr insn_t s4   = 20;
        static constexpr insn_t s5   = 21;
        static constexpr insn_t s6   = 22;
        static constexpr insn_t s7   = 23;
        static constexpr insn_t s8   = 24;
        static constexpr insn_t s9   = 25;
        static constexpr insn_t s10  = 26;
        static constexpr insn_t s11  = 27;
        static constexpr insn_t t3   = 28;
        static constexpr insn_t t4   = 29;
        static constexpr insn_t t5   = 30;
        static constexpr insn_t t6   = 31;

        static constexpr char *name[] = {
            "zero", "ra", "sp",  "gp",
            "tp",   "t0", "t1",  "t2",
            "s0",   "s1", "a0",  "a1",
            "a2",   "a3", "a4",  "a5",
            "a6",   "a7", "s2",  "s3",
            "s4",   "s5", "s6",  "s7",
            "s8",   "s9", "s10", "s11",
            "t3",   "t4", "t5",  "t6"
        };
    };
};

class fpregister {
public:

    class numeric {
    public:
        static constexpr insn_t f0  = 0;
        static constexpr insn_t f1  = 1;
        static constexpr insn_t f2  = 2;
        static constexpr insn_t f3  = 3;
        static constexpr insn_t f4  = 4;
        static constexpr insn_t f5  = 5;
        static constexpr insn_t f6  = 6;
        static constexpr insn_t f7  = 7;
        static constexpr insn_t f8  = 8;
        static constexpr insn_t f9  = 9;
        static constexpr insn_t f10 = 10;
        static constexpr insn_t f11 = 11;
        static constexpr insn_t f12 = 12;
        static constexpr insn_t f13 = 13;
        static constexpr insn_t f14 = 14;
        static constexpr insn_t f15 = 15;
        static constexpr insn_t f16 = 16;
        static constexpr insn_t f17 = 17;
        static constexpr insn_t f18 = 18;
        static constexpr insn_t f19 = 19;
        static constexpr insn_t f20 = 20;
        static constexpr insn_t f21 = 21;
        static constexpr insn_t f22 = 22;
        static constexpr insn_t f23 = 23;
        static constexpr insn_t f24 = 24;
        static constexpr insn_t f25 = 25;
        static constexpr insn_t f26 = 26;
        static constexpr insn_t f27 = 27;
        static constexpr insn_t f28 = 28;
        static constexpr insn_t f29 = 29;
        static constexpr insn_t f30 = 30;
        static constexpr insn_t f31 = 31;

        static constexpr char *name[] = {
            "f0",  "f1",  "f2",  "f3",
            "f4",  "f5",  "f6",  "f7",
            "f8",  "f9",  "f10", "f11",
            "f12", "f13", "f14", "f15",
            "f16", "f17", "f18", "f19",
            "f20", "f21", "f22", "f23",
            "f24", "f25", "f26", "f27",
            "f28", "f29", "f30", "f31"
        };
    };

    class abi {
    public:
        static constexpr insn_t ft0  = 0;
        static constexpr insn_t ft1  = 1;
        static constexpr insn_t ft2  = 2;
        static constexpr insn_t ft3  = 3;
        static constexpr insn_t ft4  = 4;
        static constexpr insn_t ft5  = 5;
        static constexpr insn_t ft6  = 6;
        static constexpr insn_t ft7  = 7;
        static constexpr insn_t fs0  = 8;
        static constexpr insn_t fs1  = 9;
        static constexpr insn_t fa0  = 10;
        static constexpr insn_t fa1  = 11;
        static constexpr insn_t fa2  = 12;
        static constexpr insn_t fa3  = 13;
        static constexpr insn_t fa4  = 14;
        static constexpr insn_t fa5  = 15;
        static constexpr insn_t fa6  = 16;
        static constexpr insn_t fa7  = 17;
        static constexpr insn_t fs2  = 18;
        static constexpr insn_t fs3  = 19;
        static constexpr insn_t fs4  = 20;
        static constexpr insn_t fs5  = 21;
        static constexpr insn_t fs6  = 22;
        static constexpr insn_t fs7  = 23;
        static constexpr insn_t fs8  = 24;
        static constexpr insn_t fs9  = 25;
        static constexpr insn_t fs10 = 26;
        static constexpr insn_t fs11 = 27;
        static constexpr insn_t ft8  = 28;
        static constexpr insn_t ft9  = 29;
        static constexpr insn_t ft10 = 30;
        static constexpr insn_t ft11 = 31;

        static constexpr char *name[] = {
            "ft0", "ft1", "ft2",  "ft3",
            "ft4", "ft5", "ft6",  "ft7",
            "fs0", "fs1", "fa0",  "fa1",
            "fa2", "fa3", "fa4",  "fa5",
            "fa6", "fa7", "fs2",  "fs3",
            "fs4", "fs5", "fs6",  "fs7",
            "fs8", "fs9", "fs10", "fs11",
            "ft8", "ft9", "ft10", "ft11"
        };
    };
};



}

# endif