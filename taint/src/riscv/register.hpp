#ifndef _RISCV__REGISTER_HPP_
#define _RISCV__REGISTER_HPP_

#include "./types.hpp"

namespace riscv {

class register {
public:
    static constexpr insn_t zero_ = 0;
    static constexpr insn_t ra_   = 1;
    static constexpr insn_t sp_   = 2;
    static constexpr insn_t gp_   = 3;
    static constexpr insn_t tp_   = 4;
    static constexpr insn_t t0_   = 5;
    static constexpr insn_t t1_   = 6;
    static constexpr insn_t t2_   = 7;
    static constexpr insn_t s0_   = 8;
    static constexpr insn_t s1_   = 9;
    static constexpr insn_t a0_   = 10;
    static constexpr insn_t a1_   = 11;
    static constexpr insn_t a2_   = 12;
    static constexpr insn_t a3_   = 13;
    static constexpr insn_t a4_   = 14;
    static constexpr insn_t a5_   = 15;
    static constexpr insn_t a6_   = 16;
    static constexpr insn_t a7_   = 17;
    static constexpr insn_t s2_   = 18;
    static constexpr insn_t s3_   = 19;
    static constexpr insn_t s4_   = 20;
    static constexpr insn_t s5_   = 21;
    static constexpr insn_t s6_   = 22;
    static constexpr insn_t s7_   = 23;
    static constexpr insn_t s8_   = 24;
    static constexpr insn_t s9_   = 25;
    static constexpr insn_t s10_  = 26;
    static constexpr insn_t s11_  = 27;
    static constexpr insn_t t3_   = 28;
    static constexpr insn_t t4_   = 29;
    static constexpr insn_t t5_   = 30;
    static constexpr insn_t t6_   = 31;

    static constexpr insn_t ft0_  = 32;
    static constexpr insn_t ft1_  = 33;
    static constexpr insn_t ft2_  = 34;
    static constexpr insn_t ft3_  = 35;
    static constexpr insn_t ft4_  = 36;
    static constexpr insn_t ft5_  = 37;
    static constexpr insn_t ft6_  = 38;
    static constexpr insn_t ft7_  = 39;
    static constexpr insn_t fs0_  = 40;
    static constexpr insn_t fs1_  = 41;
    static constexpr insn_t fa0_  = 42;
    static constexpr insn_t fa1_  = 43;
    static constexpr insn_t fa2_  = 44;
    static constexpr insn_t fa3_  = 45;
    static constexpr insn_t fa4_  = 46;
    static constexpr insn_t fa5_  = 47;
    static constexpr insn_t fa6_  = 48;
    static constexpr insn_t fa7_  = 49;
    static constexpr insn_t fs2_  = 50;
    static constexpr insn_t fs3_  = 51;
    static constexpr insn_t fs4_  = 52;
    static constexpr insn_t fs5_  = 53;
    static constexpr insn_t fs6_  = 54;
    static constexpr insn_t fs7_  = 55;
    static constexpr insn_t fs8_  = 56;
    static constexpr insn_t fs9_  = 57;
    static constexpr insn_t fs10_ = 58;
    static constexpr insn_t fs11_ = 59;
    static constexpr insn_t ft8_  = 60;
    static constexpr insn_t ft9_  = 61;
    static constexpr insn_t ft10_ = 62;
    static constexpr insn_t ft11_ = 63;
};

}

#endif