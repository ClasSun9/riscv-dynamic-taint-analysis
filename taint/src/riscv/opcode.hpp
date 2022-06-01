#ifndef _RISCV__OPCODE_HPP_
#define _RISCV__OPCODE_HPP_

#include "./types.hpp"

namespace riscv {

class opcode {
public:
    static constexpr insn_t illegal_  = 0xffffffff;
    // 0110111
    static constexpr insn_t lui_      = 0;
    // 0010111 
    static constexpr insn_t auipc_    = 1;
    // 1101111 
    static constexpr insn_t jal_      = 2;
    // 1100111 
    static constexpr insn_t jalr_     = 3;
    // 1100011 
    static constexpr insn_t beq_      = 4;
    static constexpr insn_t bne_      = 5;
    static constexpr insn_t blt_      = 6;
    static constexpr insn_t bge_      = 7;
    static constexpr insn_t bltu_     = 8;
    static constexpr insn_t bgeu_     = 9;
    // 0000011 
    static constexpr insn_t lb_       = 10;
    static constexpr insn_t lh_       = 11;
    static constexpr insn_t lw_       = 12;
    static constexpr insn_t ld_       = 13;
    static constexpr insn_t lbu_      = 14;
    static constexpr insn_t lhu_      = 15;
    static constexpr insn_t lwu_      = 16;
    // 0100011 
    static constexpr insn_t sb_       = 17;
    static constexpr insn_t sh_       = 18;
    static constexpr insn_t sw_       = 19;
    static constexpr insn_t sd_       = 20;
    // 0110011 
    static constexpr insn_t add_      = 21;
    static constexpr insn_t sub_      = 22;
    static constexpr insn_t sll_      = 23;
    static constexpr insn_t slt_      = 24;
    static constexpr insn_t sltu_     = 25;
    static constexpr insn_t xor_      = 26;
    static constexpr insn_t srl_      = 27;
    static constexpr insn_t sra_      = 28;
    static constexpr insn_t or_       = 29;
    static constexpr insn_t and_      = 30;
    static constexpr insn_t mul_      = 31;
    static constexpr insn_t mulh_     = 32;
    static constexpr insn_t mulhsu_   = 33;
    static constexpr insn_t mulhu_    = 34;
    static constexpr insn_t div_      = 35;
    static constexpr insn_t divu_     = 36;
    static constexpr insn_t rem_      = 37;
    static constexpr insn_t remu_     = 38;
    // 0111011 
    static constexpr insn_t addw_     = 39;
    static constexpr insn_t subw_     = 40;
    static constexpr insn_t sllw_     = 41;
    static constexpr insn_t srlw_     = 42;
    static constexpr insn_t sraw_     = 43;
    static constexpr insn_t mulw_     = 44;
    static constexpr insn_t divw_     = 45;
    static constexpr insn_t divuw_    = 46;
    static constexpr insn_t remw_     = 47;
    static constexpr insn_t remuw_    = 48;
    // 0010011 
    static constexpr insn_t addi_     = 49;
    static constexpr insn_t slti_     = 50;
    static constexpr insn_t sltiu_    = 51;
    static constexpr insn_t xori_     = 52;
    static constexpr insn_t ori_      = 53;
    static constexpr insn_t andi_     = 54;
    static constexpr insn_t slli_     = 55;
    static constexpr insn_t srli_     = 56;
    static constexpr insn_t srai_     = 57;
    // 0011011 
    static constexpr insn_t addiw_    = 58;
    static constexpr insn_t slliw_    = 59;
    static constexpr insn_t srliw_    = 60;
    static constexpr insn_t sraiw_    = 61;
    // 0001111
    static constexpr insn_t fence_    = 62;
    static constexpr insn_t fencetso_ = 63;
    static constexpr insn_t pause_    = 64;
    // 1110011
    static constexpr insn_t ecall_    = 65;
    static constexpr insn_t ebreak_   = 66;
};

}

#endif