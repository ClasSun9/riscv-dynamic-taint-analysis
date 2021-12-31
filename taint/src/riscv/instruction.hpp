# ifndef _RISCV__INSTRUCTION_HPP_
# define _RISCV__INSTRUCTION_HPP_

# include "types.hpp"
# include "specification.hpp"
# include <array>

namespace riscv {

class instruction {
private:
    
    class descriptor;

    class parser {
    public:
        template<uint8_t _v_count, uint8_t _v_shift>
        static inline insn_t parse(insn_t raw);
        static inline insn_t parse_rd(insn_t raw);
        static inline insn_t parse_rs1(insn_t raw);
        static inline insn_t parse_rs2(insn_t raw);
        static inline insn_t parse_imm_itype(insn_t raw);
        static inline insn_t parse_imm_stype(insn_t raw);
        static inline insn_t parse_imm_btype(insn_t raw);
        static inline insn_t parse_imm_utype(insn_t raw);
        static inline insn_t parse_imm_jtype(insn_t raw);
        static inline insn_t parse_imm_shifti(insn_t raw);
        static inline insn_t parse_imm_shiftiw(insn_t raw);
    };

    class matcher {
    public:
        template<insn_t _v_mask, insn_t _v_match>
        static bool match(insn_t raw);
    };

    class decoder {
    public:
        static void decode_null(insn_t raw, instruction &insn);
        static void decode_rtype(insn_t raw, instruction &insn);
        static void decode_itype(insn_t raw, instruction &insn);
        static void decode_stype(insn_t raw, instruction &insn);
        static void decode_btype(insn_t raw, instruction &insn);
        static void decode_utype(insn_t raw, instruction &insn);
        static void decode_jtype(insn_t raw, instruction &insn);
        static void decode_shifti(insn_t raw, instruction &insn);
        static void decode_shiftiw(insn_t raw, instruction &insn);
    };

    class descriptor {
    public:
        insn_t opcode;

        bool (*matcher)(insn_t);
        void (*decoder)(insn_t, instruction &insn);

        uint64_t length;
        uint64_t sign;
        uint64_t next;
    };

private:
    static constexpr std::array<descriptor, 81> descriptors = {
        // 0110111
        opcode::illegal,  matcher::match<0x0000007f, 0x00000037>, nullptr,                 4, 0, 2,
        opcode::lui,      matcher::match<0x0000007f, 0x00000037>, decoder::decode_itype,   4, 0, 0,
        // 0010111
        opcode::illegal,  matcher::match<0x0000007f, 0x00000017>, nullptr,                 4, 0, 4,
        opcode::auipc,    matcher::match<0x0000007f, 0x00000017>, decoder::decode_itype,   4, 0, 0,
        // 1101111
        opcode::illegal,  matcher::match<0x0000007f, 0x0000006f>, nullptr,                 4, 0, 6,
        opcode::jal,      matcher::match<0x0000007f, 0x0000006f>, decoder::decode_jtype,   4, 0, 0,
        // 1100111
        opcode::illegal,  matcher::match<0x0000007f, 0x00000067>, nullptr,                 4, 0, 8,
        opcode::jalr,     matcher::match<0x0000707f, 0x00000067>, decoder::decode_itype,   4, 0, 0,
        // 1100011
        opcode::illegal,  matcher::match<0x0000007f, 0x00000063>, nullptr,                 4, 0, 15,
        opcode::beq,      matcher::match<0x0000707f, 0x00000063>, decoder::decode_btype,   4, 0, 0,
        opcode::bne,      matcher::match<0x0000707f, 0x00001063>, decoder::decode_btype,   4, 0, 0,
        opcode::blt,      matcher::match<0x0000707f, 0x00004063>, decoder::decode_btype,   4, 0, 0,
        opcode::bge,      matcher::match<0x0000707f, 0x00005063>, decoder::decode_btype,   4, 0, 0,
        opcode::bltu,     matcher::match<0x0000707f, 0x00006063>, decoder::decode_btype,   4, 0, 0,
        opcode::bgeu,     matcher::match<0x0000707f, 0x00007063>, decoder::decode_btype,   4, 0, 0,
        // 0000011
        opcode::illegal,  matcher::match<0x0000007f, 0x00000003>, nullptr,                 4, 0, 23,
        opcode::lb,       matcher::match<0x0000707f, 0x00000003>, decoder::decode_itype,   4, 0, 0,
        opcode::lh,       matcher::match<0x0000707f, 0x00001003>, decoder::decode_itype,   4, 0, 0,
        opcode::lw,       matcher::match<0x0000707f, 0x00002003>, decoder::decode_itype,   4, 0, 0,
        opcode::ld,       matcher::match<0x0000707f, 0x00003003>, decoder::decode_itype,   4, 0, 0,
        opcode::lbu,      matcher::match<0x0000707f, 0x00004003>, decoder::decode_itype,   4, 0, 0,
        opcode::lhu,      matcher::match<0x0000707f, 0x00005003>, decoder::decode_itype,   4, 0, 0,
        opcode::lwu,      matcher::match<0x0000707f, 0x00006003>, decoder::decode_itype,   4, 0, 0,
        // 0100011
        opcode::illegal,  matcher::match<0x0000007f, 0x00000023>, nullptr,                 4, 0, 28,
        opcode::sb,       matcher::match<0x0000707f, 0x00000023>, decoder::decode_stype,   4, 0, 0,
        opcode::sh,       matcher::match<0x0000707f, 0x00001023>, decoder::decode_stype,   4, 0, 0,
        opcode::sw,       matcher::match<0x0000707f, 0x00002023>, decoder::decode_stype,   4, 0, 0,
        opcode::sd,       matcher::match<0x0000707f, 0x00003023>, decoder::decode_stype,   4, 0, 0,
        // 0110011
        opcode::illegal,  matcher::match<0x0000007f, 0x00000023>, nullptr,                 4, 0, 47,
        opcode::add,      matcher::match<0xfe00707f, 0x00000033>, decoder::decode_rtype,   4, 0, 0,
        opcode::sub,      matcher::match<0xfe00707f, 0x40000033>, decoder::decode_rtype,   4, 0, 0,
        opcode::sll,      matcher::match<0xfe00707f, 0x00001033>, decoder::decode_rtype,   4, 0, 0,
        opcode::slt,      matcher::match<0xfe00707f, 0x00002033>, decoder::decode_rtype,   4, 0, 0,
        opcode::sltu,     matcher::match<0xfe00707f, 0x00003033>, decoder::decode_rtype,   4, 0, 0,
        opcode::xor_,     matcher::match<0xfe00707f, 0x00004033>, decoder::decode_rtype,   4, 0, 0,
        opcode::srl,      matcher::match<0xfe00707f, 0x00005033>, decoder::decode_rtype,   4, 0, 0,
        opcode::sra,      matcher::match<0xfe00707f, 0x40005033>, decoder::decode_rtype,   4, 0, 0,
        opcode::or_,      matcher::match<0xfe00707f, 0x00006033>, decoder::decode_rtype,   4, 0, 0,
        opcode::and_,     matcher::match<0xfe00707f, 0x00007033>, decoder::decode_rtype,   4, 0, 0,
        opcode::mul,      matcher::match<0xfe00707f, 0x02000033>, decoder::decode_rtype,   4, 0, 0,
        opcode::mulh,     matcher::match<0xfe00707f, 0x02001033>, decoder::decode_rtype,   4, 0, 0,
        opcode::mulhsu,   matcher::match<0xfe00707f, 0x02002033>, decoder::decode_rtype,   4, 0, 0,
        opcode::mulhu,    matcher::match<0xfe00707f, 0x02003033>, decoder::decode_rtype,   4, 0, 0,
        opcode::div,      matcher::match<0xfe00707f, 0x02004033>, decoder::decode_rtype,   4, 0, 0,
        opcode::divu,     matcher::match<0xfe00707f, 0x02005033>, decoder::decode_rtype,   4, 0, 0,
        opcode::rem,      matcher::match<0xfe00707f, 0x02006033>, decoder::decode_rtype,   4, 0, 0,
        opcode::remu,     matcher::match<0xfe00707f, 0x02007033>, decoder::decode_rtype,   4, 0, 0,
        // 0111011
        opcode::illegal,  matcher::match<0x0000007f, 0x0000003b>, nullptr,                 4, 0, 58,
        opcode::addw,     matcher::match<0xfe00707f, 0x0000003b>, decoder::decode_rtype,   4, 0, 0,
        opcode::subw,     matcher::match<0xfe00707f, 0x4000003b>, decoder::decode_rtype,   4, 0, 0,
        opcode::sllw,     matcher::match<0xfe00707f, 0x0000103b>, decoder::decode_rtype,   4, 0, 0,
        opcode::srlw,     matcher::match<0xfe00707f, 0x0000503b>, decoder::decode_rtype,   4, 0, 0,
        opcode::sraw,     matcher::match<0xfe00707f, 0x4000503b>, decoder::decode_rtype,   4, 0, 0,
        opcode::mulw,     matcher::match<0xfe00707f, 0x0200003b>, decoder::decode_rtype,   4, 0, 0,
        opcode::divw,     matcher::match<0xfe00707f, 0x0200403b>, decoder::decode_rtype,   4, 0, 0,
        opcode::divuw,    matcher::match<0xfe00707f, 0x0200503b>, decoder::decode_rtype,   4, 0, 0,
        opcode::remw,     matcher::match<0xfe00707f, 0x0200603b>, decoder::decode_rtype,   4, 0, 0,
        opcode::remuw,    matcher::match<0xfe00707f, 0x0200703b>, decoder::decode_rtype,   4, 0, 0,
        // 0010011
        opcode::illegal,  matcher::match<0x0000007f, 0x00000013>, nullptr,                 4, 0, 68,
        opcode::addi,     matcher::match<0x0000707f, 0x00000013>, decoder::decode_itype,   4, 0, 0,
        opcode::slti,     matcher::match<0x0000707f, 0x00002013>, decoder::decode_itype,   4, 0, 0,
        opcode::sltiu,    matcher::match<0x0000707f, 0x00003013>, decoder::decode_itype,   4, 0, 0,
        opcode::xori,     matcher::match<0x0000707f, 0x00004013>, decoder::decode_itype,   4, 0, 0,
        opcode::ori,      matcher::match<0x0000707f, 0x00006013>, decoder::decode_itype,   4, 0, 0,
        opcode::andi,     matcher::match<0x0000707f, 0x00007013>, decoder::decode_itype,   4, 0, 0,
        opcode::slli,     matcher::match<0xfc00707f, 0x00001013>, decoder::decode_shifti,  4, 0, 0,
        opcode::srli,     matcher::match<0xfc00707f, 0x00005013>, decoder::decode_shifti,  4, 0, 0,
        opcode::srai,     matcher::match<0xfc00707f, 0x40005013>, decoder::decode_shifti,  4, 0, 0,
        // 0011011
        opcode::illegal,  matcher::match<0x0000007f, 0x0000001b>, nullptr,                 4, 0, 73,
        opcode::addiw,    matcher::match<0x0000707f, 0x0000001b>, decoder::decode_itype,   4, 0, 0,
        opcode::slliw,    matcher::match<0xfe00707f, 0x0000101b>, decoder::decode_shiftiw, 4, 0, 0,
        opcode::srliw,    matcher::match<0xfe00707f, 0x0000501b>, decoder::decode_shiftiw, 4, 0, 0,
        opcode::sraiw,    matcher::match<0xfe00707f, 0x4000501b>, decoder::decode_shiftiw, 4, 0, 0,
        // 0001111
        opcode::illegal,  matcher::match<0x0000007f, 0x0000000f>, nullptr,                 4, 0, 77,
        opcode::fence,    matcher::match<0x0000707f, 0x0000000f>, decoder::decode_null,    4, 0, 0,
        opcode::fencetso, matcher::match<0xffffffff, 0x8330000f>, decoder::decode_null,    4, 0, 0,
        opcode::pause,    matcher::match<0xffffffff, 0x0100000f>, decoder::decode_null,    4, 0, 0,
        // 1110011
        opcode::illegal,  matcher::match<0x0000007f, 0x00000073>, nullptr,                 4, 0, 80,
        opcode::ecall,    matcher::match<0xffffffff, 0x00000073>, decoder::decode_null,    4, 0, 0,
        opcode::ebreak,   matcher::match<0xffffffff, 0x00100073>, decoder::decode_null,    4, 0, 0,
        // null
        opcode::illegal,  matcher::match<0xffffffff, 0x00000000>, nullptr,                 0, 0, 0,
    };

private:
    insn_t _raw;
    insn_t _opcode;
    insn_t _rd;
    insn_t _rs1;
    insn_t _rs2;
    insn_t _imm;
    uint64_t _sign;
    uint64_t _length;

public:
    static instruction decode(insn_t raw);

    insn_t get_raw();
    insn_t get_opcode();
    insn_t get_rd();
    insn_t get_rs1();
    insn_t get_rs2();
    int32_t get_imm_signed();
    uint32_t get_imm_unsigned();
    uint64_t get_length();

public:
    instruction();
};

}

# endif