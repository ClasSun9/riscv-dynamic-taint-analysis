#include "./instruction.hpp"
#include "./opcode.hpp"

using std::array;

namespace riscv {

class instruction::parser {
public:
    template<uint8_t v_count, uint8_t v_shift>
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

class instruction::matcher {
public:
    template<insn_t v_mask, insn_t v_match>
    static bool match(insn_t raw);
};

class instruction::decoder {
public:
    static void decode_null(insn_t rasw, instruction& insn);
    static void decode_rtype(insn_t raw, instruction& insn);
    static void decode_itype(insn_t raw, instruction& insn);
    static void decode_stype(insn_t raw, instruction& insn);
    static void decode_btype(insn_t raw, instruction& insn);
    static void decode_utype(insn_t raw, instruction& insn);
    static void decode_jtype(insn_t raw, instruction& insn);
    static void decode_shifti(insn_t raw, instruction& insn);
    static void decode_shiftiw(insn_t raw, instruction& insn);
};

class instruction::description {
public:
    insn_t id;
    bool (*matcher)(insn_t);
    void (*decoder)(insn_t, instruction&);
    int64_t length;
    int64_t sign;
    int64_t next;
};

const array<instruction::description, 81> instruction::descriptions = {
    // 0110111
    opcode::illegal_,  matcher::match<0x0000007f, 0x00000037>, nullptr,                 4, 0,  2,
    opcode::lui_,      matcher::match<0x0000007f, 0x00000037>, decoder::decode_utype,   4, 31, 0,
    // 0010111
    opcode::illegal_,  matcher::match<0x0000007f, 0x00000017>, nullptr,                 4, 0,  4,
    opcode::auipc_,    matcher::match<0x0000007f, 0x00000017>, decoder::decode_utype,   4, 31, 0,
    // 1101111
    opcode::illegal_,  matcher::match<0x0000007f, 0x0000006f>, nullptr,                 4, 0,  6,
    opcode::jal_,      matcher::match<0x0000007f, 0x0000006f>, decoder::decode_jtype,   4, 20, 0,
    // 1100111
    opcode::illegal_,  matcher::match<0x0000007f, 0x00000067>, nullptr,                 4, 0,  8,
    opcode::jalr_,     matcher::match<0x0000707f, 0x00000067>, decoder::decode_itype,   4, 11, 0,
    // 1100011
    opcode::illegal_,  matcher::match<0x0000007f, 0x00000063>, nullptr,                 4, 0,  15,
    opcode::beq_,      matcher::match<0x0000707f, 0x00000063>, decoder::decode_btype,   4, 12, 0,
    opcode::bne_,      matcher::match<0x0000707f, 0x00001063>, decoder::decode_btype,   4, 12, 0,
    opcode::blt_,      matcher::match<0x0000707f, 0x00004063>, decoder::decode_btype,   4, 12, 0,
    opcode::bge_,      matcher::match<0x0000707f, 0x00005063>, decoder::decode_btype,   4, 12, 0,
    opcode::bltu_,     matcher::match<0x0000707f, 0x00006063>, decoder::decode_btype,   4, 12, 0,
    opcode::bgeu_,     matcher::match<0x0000707f, 0x00007063>, decoder::decode_btype,   4, 12, 0,
    // 0000011
    opcode::illegal_,  matcher::match<0x0000007f, 0x00000003>, nullptr,                 4, 0,  23,
    opcode::lb_,       matcher::match<0x0000707f, 0x00000003>, decoder::decode_itype,   4, 11, 0,
    opcode::lh_,       matcher::match<0x0000707f, 0x00001003>, decoder::decode_itype,   4, 11, 0,
    opcode::lw_,       matcher::match<0x0000707f, 0x00002003>, decoder::decode_itype,   4, 11, 0,
    opcode::ld_,       matcher::match<0x0000707f, 0x00003003>, decoder::decode_itype,   4, 11, 0,
    opcode::lbu_,      matcher::match<0x0000707f, 0x00004003>, decoder::decode_itype,   4, 11, 0,
    opcode::lhu_,      matcher::match<0x0000707f, 0x00005003>, decoder::decode_itype,   4, 11, 0,
    opcode::lwu_,      matcher::match<0x0000707f, 0x00006003>, decoder::decode_itype,   4, 11, 0,
    // 0100011
    opcode::illegal_,  matcher::match<0x0000007f, 0x00000023>, nullptr,                 4, 0,  28,
    opcode::sb_,       matcher::match<0x0000707f, 0x00000023>, decoder::decode_stype,   4, 11, 0,
    opcode::sh_,       matcher::match<0x0000707f, 0x00001023>, decoder::decode_stype,   4, 11, 0,
    opcode::sw_,       matcher::match<0x0000707f, 0x00002023>, decoder::decode_stype,   4, 11, 0,
    opcode::sd_,       matcher::match<0x0000707f, 0x00003023>, decoder::decode_stype,   4, 11, 0,
    // 0110011
    opcode::illegal_,  matcher::match<0x0000007f, 0x00000023>, nullptr,                 4, 0,  47,
    opcode::add_,      matcher::match<0xfe00707f, 0x00000033>, decoder::decode_rtype,   4, 0,  0,
    opcode::sub_,      matcher::match<0xfe00707f, 0x40000033>, decoder::decode_rtype,   4, 0,  0,
    opcode::sll_,      matcher::match<0xfe00707f, 0x00001033>, decoder::decode_rtype,   4, 0,  0,
    opcode::slt_,      matcher::match<0xfe00707f, 0x00002033>, decoder::decode_rtype,   4, 0,  0,
    opcode::sltu_,     matcher::match<0xfe00707f, 0x00003033>, decoder::decode_rtype,   4, 0,  0,
    opcode::xor_,      matcher::match<0xfe00707f, 0x00004033>, decoder::decode_rtype,   4, 0,  0,
    opcode::srl_,      matcher::match<0xfe00707f, 0x00005033>, decoder::decode_rtype,   4, 0,  0,
    opcode::sra_,      matcher::match<0xfe00707f, 0x40005033>, decoder::decode_rtype,   4, 0,  0,
    opcode::or_,       matcher::match<0xfe00707f, 0x00006033>, decoder::decode_rtype,   4, 0,  0,
    opcode::and_,      matcher::match<0xfe00707f, 0x00007033>, decoder::decode_rtype,   4, 0,  0,
    opcode::mul_,      matcher::match<0xfe00707f, 0x02000033>, decoder::decode_rtype,   4, 0,  0,
    opcode::mulh_,     matcher::match<0xfe00707f, 0x02001033>, decoder::decode_rtype,   4, 0,  0,
    opcode::mulhsu_,   matcher::match<0xfe00707f, 0x02002033>, decoder::decode_rtype,   4, 0,  0,
    opcode::mulhu_,    matcher::match<0xfe00707f, 0x02003033>, decoder::decode_rtype,   4, 0,  0,
    opcode::div_,      matcher::match<0xfe00707f, 0x02004033>, decoder::decode_rtype,   4, 0,  0,
    opcode::divu_,     matcher::match<0xfe00707f, 0x02005033>, decoder::decode_rtype,   4, 0,  0,
    opcode::rem_,      matcher::match<0xfe00707f, 0x02006033>, decoder::decode_rtype,   4, 0,  0,
    opcode::remu_,     matcher::match<0xfe00707f, 0x02007033>, decoder::decode_rtype,   4, 0,  0,
    // 0111011
    opcode::illegal_,  matcher::match<0x0000007f, 0x0000003b>, nullptr,                 4, 0,  58,
    opcode::addw_,     matcher::match<0xfe00707f, 0x0000003b>, decoder::decode_rtype,   4, 0,  0,
    opcode::subw_,     matcher::match<0xfe00707f, 0x4000003b>, decoder::decode_rtype,   4, 0,  0,
    opcode::sllw_,     matcher::match<0xfe00707f, 0x0000103b>, decoder::decode_rtype,   4, 0,  0,
    opcode::srlw_,     matcher::match<0xfe00707f, 0x0000503b>, decoder::decode_rtype,   4, 0,  0,
    opcode::sraw_,     matcher::match<0xfe00707f, 0x4000503b>, decoder::decode_rtype,   4, 0,  0,
    opcode::mulw_,     matcher::match<0xfe00707f, 0x0200003b>, decoder::decode_rtype,   4, 0,  0,
    opcode::divw_,     matcher::match<0xfe00707f, 0x0200403b>, decoder::decode_rtype,   4, 0,  0,
    opcode::divuw_,    matcher::match<0xfe00707f, 0x0200503b>, decoder::decode_rtype,   4, 0,  0,
    opcode::remw_,     matcher::match<0xfe00707f, 0x0200603b>, decoder::decode_rtype,   4, 0,  0,
    opcode::remuw_,    matcher::match<0xfe00707f, 0x0200703b>, decoder::decode_rtype,   4, 0,  0,
    // 0010011
    opcode::illegal_,  matcher::match<0x0000007f, 0x00000013>, nullptr,                 4, 0,  68,
    opcode::addi_,     matcher::match<0x0000707f, 0x00000013>, decoder::decode_itype,   4, 11, 0,
    opcode::slti_,     matcher::match<0x0000707f, 0x00002013>, decoder::decode_itype,   4, 11, 0,
    opcode::sltiu_,    matcher::match<0x0000707f, 0x00003013>, decoder::decode_itype,   4, 11, 0,
    opcode::xori_,     matcher::match<0x0000707f, 0x00004013>, decoder::decode_itype,   4, 11, 0,
    opcode::ori_,      matcher::match<0x0000707f, 0x00006013>, decoder::decode_itype,   4, 11, 0,
    opcode::andi_,     matcher::match<0x0000707f, 0x00007013>, decoder::decode_itype,   4, 11, 0,
    opcode::slli_,     matcher::match<0xfc00707f, 0x00001013>, decoder::decode_shifti,  4, 0,  0,
    opcode::srli_,     matcher::match<0xfc00707f, 0x00005013>, decoder::decode_shifti,  4, 0,  0,
    opcode::srai_,     matcher::match<0xfc00707f, 0x40005013>, decoder::decode_shifti,  4, 0,  0,
    // 0011011
    opcode::illegal_,  matcher::match<0x0000007f, 0x0000001b>, nullptr,                 4, 0,  73,
    opcode::addiw_,    matcher::match<0x0000707f, 0x0000001b>, decoder::decode_itype,   4, 11, 0,
    opcode::slliw_,    matcher::match<0xfe00707f, 0x0000101b>, decoder::decode_shiftiw, 4, 0,  0,
    opcode::srliw_,    matcher::match<0xfe00707f, 0x0000501b>, decoder::decode_shiftiw, 4, 0,  0,
    opcode::sraiw_,    matcher::match<0xfe00707f, 0x4000501b>, decoder::decode_shiftiw, 4, 0,  0,
    // 0001111
    opcode::illegal_,  matcher::match<0x0000007f, 0x0000000f>, nullptr,                 4, 0,  77,
    opcode::fence_,    matcher::match<0x0000707f, 0x0000000f>, decoder::decode_null,    4, 0,  0,
    opcode::fencetso_, matcher::match<0xffffffff, 0x8330000f>, decoder::decode_null,    4, 0,  0,
    opcode::pause_,    matcher::match<0xffffffff, 0x0100000f>, decoder::decode_null,    4, 0,  0,
    // 1110011
    opcode::illegal_,  matcher::match<0x0000007f, 0x00000073>, nullptr,                 4, 0,  80,
    opcode::ecall_,    matcher::match<0xffffffff, 0x00000073>, decoder::decode_null,    4, 0,  0,
    opcode::ebreak_,   matcher::match<0xffffffff, 0x00100073>, decoder::decode_null,    4, 0,  0,
    // null
    opcode::illegal_,  matcher::match<0xffffffff, 0x00000000>, nullptr,                 0, 0,  0,
};

template<uint8_t v_count, uint8_t v_shift>
insn_t instruction::parser::parse(insn_t raw) {
    return (raw >> v_shift) & ((v_count << v_shift) - 1);
}

insn_t instruction::parser::parse_rd(insn_t raw) {
    return parse<0x05, 0x07>(raw);
}

insn_t instruction::parser::parse_rs1(insn_t raw) {
    return parse<0x05, 0x0f>(raw);
}

insn_t instruction::parser::parse_rs2(insn_t raw) {
    return parse<0x0f, 0x14>(raw);
}

insn_t instruction::parser::parse_imm_itype(insn_t raw) {
    return parse<0x0c, 0x14>(raw);
}

insn_t instruction::parser::parse_imm_stype(insn_t raw) {
    return 
        parse<0x05, 0x07>(raw) << 0x00 |
        parse<0x07, 0x19>(raw) << 0x05;
}

insn_t instruction::parser::parse_imm_btype(insn_t raw) {
    return
        parse<0x04, 0x08>(raw) << 0x01 |
        parse<0x06, 0x19>(raw) << 0x05 |
        parse<0x01, 0x07>(raw) << 0x0b |
        parse<0x01, 0x0d>(raw) << 0x0c;
}

insn_t instruction::parser::parse_imm_utype(insn_t raw) {
    return parse<0x14, 0x0c>(raw) << 0x0c;
}

insn_t instruction::parser::parse_imm_jtype(insn_t raw) {
    return
        parse<0x0a, 0x15>(raw) << 0x01 |
        parse<0x01, 0x14>(raw) << 0x0b |
        parse<0x08, 0x0c>(raw) << 0x0c |
        parse<0x01, 0x1f>(raw) << 0x14;
}

insn_t instruction::parser::parse_imm_shifti(insn_t raw) {
    return parse<0x06, 0x14>(raw);
}

insn_t instruction::parser::parse_imm_shiftiw(insn_t raw) {
    return parse<0x05, 0x14>(raw);
}

template<insn_t v_mask, insn_t v_match>
bool instruction::matcher::match(insn_t raw) {
    return (raw & v_mask) == v_match;
}

void instruction::decoder::decode_null(insn_t raw, instruction& insn) {

}

void instruction::decoder::decode_rtype(insn_t raw, instruction& insn) {
    insn._rd  = parser::parse_rd(raw);
    insn._rs1 = parser::parse_rs1(raw);
    insn._rs2 = parser::parse_rs2(raw);
}

void instruction::decoder::decode_itype(insn_t raw, instruction& insn) {
    insn._rd  = parser::parse_rd(raw);
    insn._rs1 = parser::parse_rs1(raw);
    insn._imm = parser::parse_imm_itype(raw); 
}

void instruction::decoder::decode_stype(insn_t raw, instruction& insn) {
    insn._rs1 = parser::parse_rs1(raw);
    insn._rs2 = parser::parse_rs2(raw);
    insn._imm = parser::parse_imm_stype(raw);
}

void instruction::decoder::decode_btype(insn_t raw, instruction& insn) {
    insn._rs1 = parser::parse_rs1(raw);
    insn._rs2 = parser::parse_rs2(raw);
    insn._imm = parser::parse_imm_stype(raw);
}

void instruction::decoder::decode_utype(insn_t raw, instruction& insn) {
    insn._rd  = parser::parse_rd(raw);
    insn._imm = parser::parse_imm_utype(raw);
}

void instruction::decoder::decode_jtype(insn_t raw, instruction& insn) {
    insn._rd  = parser::parse_rd(raw);
    insn._imm = parser::parse_imm_jtype(raw);
}

void instruction::decoder::decode_shifti(insn_t raw, instruction& insn) {
    insn._rd  = parser::parse_rd(raw);
    insn._rs1 = parser::parse_rs1(raw);
}

void instruction::decoder::decode_shiftiw(insn_t raw, instruction& insn) {
    insn._rd  = parser::parse_rd(raw);
    insn._rs1 = parser::parse_rs1(raw);
}

insn_t instruction::raw() {
    return _raw;
}

insn_t instruction::id() {
    return _id;
}

insn_t instruction::rd() {
    return _rd;
}

insn_t instruction::rs1() {
    return _rs1;
}

insn_t instruction::rs2() {
    return _rs2;
}

insn_t instruction::shamt() {
    return _shamt;
}

int64_t instruction::simm() {
    return _imm | (~((_imm >> _sign) << _sign));
}

uint64_t instruction::uimm() {
    return _imm;
}

int64_t instruction::length() {
    return _length;
}

instruction::instruction() { }
instruction::instruction(insn_t raw) {
    instruction insn;

    int64_t index = 0;
    while (!descriptions[index].matcher(raw)) {
        if (descriptions[index].next == 0) {
            insn._id = opcode::illegal_;
            return;
        }
        index = descriptions[index].next;
    }

    ++index;
    while (!descriptions[index].matcher(raw)) {
        if (descriptions[index].id == opcode::illegal_) {
            insn._id = opcode::illegal_;
            return;
        }
        ++index;
    }

    auto description = descriptions.at(index);
    description.decoder(raw, insn);
    insn._id = description.id;
    insn._sign = description.sign;
    insn._length = description.length;
}

}