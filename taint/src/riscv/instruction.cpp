# include "instruction.hpp"

using std::array;

namespace riscv {

template<uint8_t _v_count, uint8_t _v_shift>
insn_t instruction::parser::parse(insn_t raw) {
    return (raw >> _v_shift) & ((_v_count << _v_shift) - 1);
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

template<insn_t _v_mask, insn_t _v_match>
bool instruction::matcher::match(insn_t raw) {
    return (raw & _v_mask) == _v_match;
}

void instruction::decoder::decode_rtype(insn_t raw, instruction &insn) {
    insn._rd  = parser::parse_rd(raw);
    insn._rs1 = parser::parse_rs1(raw);
    insn._rs2 = parser::parse_rs2(raw);
}

void instruction::decoder::decode_itype(insn_t raw, instruction &insn) {
    insn._rd  = parser::parse_rd(raw);
    insn._rs1 = parser::parse_rs1(raw);
    insn._imm = parser::parse_imm_itype(raw); 
}

void instruction::decoder::decode_stype(insn_t raw, instruction &insn) {
    insn._rs1 = parser::parse_rs1(raw);
    insn._rs2 = parser::parse_rs2(raw);
    insn._imm = parser::parse_imm_stype(raw);
}

void instruction::decoder::decode_btype(insn_t raw, instruction &insn) {
    insn._rs1 = parser::parse_rs1(raw);
    insn._rs2 = parser::parse_rs2(raw);
    insn._imm = parser::parse_imm_stype(raw);
}

void instruction::decoder::decode_utype(insn_t raw, instruction &insn) {
    insn._rd  = parser::parse_rd(raw);
    insn._imm = parser::parse_imm_utype(raw);
}

void instruction::decoder::decode_jtype(insn_t raw, instruction &insn) {
    insn._rd  = parser::parse_rd(raw);
    insn._imm = parser::parse_imm_jtype(raw);
}

void instruction::decoder::decode_shifti(insn_t raw, instruction &insn) {
    insn._rd  = parser::parse_rd(raw);
    insn._rs1 = parser::parse_rs1(raw);
}

void instruction::decoder::decode_shiftiw(insn_t raw, instruction &insn) {
    insn._rd  = parser::parse_rd(raw);
    insn._rs1 = parser::parse_rs1(raw);
}

instruction instruction::decode(insn_t raw) {
    instruction insn;

    int64_t index = 0;
    while (!descriptions[index].matcher(raw)) {
        if (descriptions[index].next == 0) {
            insn._opcode = opcode::illegal;
            return insn;
        }
        index = descriptions[index].next;
    }

    ++index;
    while (!descriptions[index].matcher(raw)) {
        if (descriptions[index].opcode == opcode::illegal) {
            insn._opcode = opcode::illegal;
            return insn;
        }
        ++index;
    }

    auto description = descriptions.at(index);
    description.decoder(raw, insn);
    insn._opcode = description.opcode;
    insn._sign = description.sign;
    insn._length = description.length;
    return insn;
}

insn_t instruction::raw() {
    return _raw;
}

insn_t instruction::opcode() {
    return _opcode;
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

int64_t instruction::simm() {
    return _imm | (~((_imm >> _sign) << _sign));
}

uint64_t instruction::uimm() {
    return _imm;
}

uint64_t instruction::shamt() {
    return _shamt;
}

int64_t instruction::length() {
    return _length;
}

instruction::instruction() :
    _raw(0),
    _opcode(0),
    _rd(0),
    _rs1(0),
    _rs2(0),
    _imm(0),
    _length(0) { }

}