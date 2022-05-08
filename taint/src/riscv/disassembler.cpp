# include "disassembler.hpp"
# include <array>
# include <string>
# include <cstdio>
using std::array;
using std::string;

namespace riscv {

class mnemonic {
public:
    string name;
    // d : rd
    // o : rs1
    // t : rs2
    // i : simm
    // u : uimm
    // s : shamt
    string format;
};

array<mnemonic, 67> mnemonics = {
    "lui", "d, i",
    "auipc", "d, i",
    "jal", "d, i",
    "jalr", "d, i(o)",
    "beq", "o, t, i",
    "bne", "o, t, i",
    "blt", "o, t, i",
    "bge", "o, t, i",
    "bltu", "o, t, i",
    "bgeu", "o, t, i",
    "lb", "d, i(o)",
    "lh", "d, i(o)",
    "lw", "d, i(o)",
    "ld", "d, i(o)",
    "lbu", "d, i(o)",
    "lhu", "d, i(o)",
    "lwu", "d, i(o)",
    "sb", "t, i(o)",
    "sh", "t, i(o)",
    "sw", "t, i(o)",
    "sd", "t, i(o)",
    "add", "d, o, t",
    "sub", "d, o, t",
    "sll", "d, o, t",
    "slt", "d, o, t",
    "sltu", "d, o, t",
    "xor", "d, o, t",
    "srl", "d, o, t",
    "sra", "d, o, t",
    "or", "d, o, t",
    "and", "d, o, t",
    "mul", "d, o, t",
    "mulh", "d, o, t",
    "mulhsu", "d, o, t",
    "mulhu", "d, o, t",
    "div", "d, o, t",
    "divu", "d, o, t",
    "rem", "d, o, t",
    "remu", "d, o, t",
    "addw", "d, o, t",
    "subw", "d, o, t",
    "sllw", "d, o, t",
    "srlw", "d, o, t",
    "sraw", "d, o, t",
    "mulw", "d, o, t",
    "divw", "d, o, t",
    "divuw", "d, o, t",
    "remw", "d, o, t",
    "remuw", "d, o, t",
    "addi", "d, o, i",
    "slti", "d, o, i",
    "sltiu", "d, o, u",
    "xori", "d, o, u",
    "ori", "d, o, u",
    "andi", "d, o, u",
    "slli", "d, o, s",
    "srli", "d, o, s",
    "srai", "d, o, s",
    "addiw", "d, o, i",
    "slliw", "d, o, s",
    "srliw", "d, o, s",
    "sraiw", "d, o, s",
    "fence", "",
    "fencetso", "",
    "pause", "",
    "pause", "",
    "ecall", "",
    "ebreak", "",
};

array<string, 32> register_names = {
    "zero", "ra", "sp",  "gp",
    "tp",   "t0", "t1",  "t2",
    "s0",   "s1", "a0",  "a1",
    "a2",   "a3", "a4",  "a5",
    "a6",   "a7", "s2",  "s3",
    "s4",   "s5", "s6",  "s7",
    "s8",   "s9", "s10", "s11",
    "t3",   "t4", "t5",  "t6",
};

void disassembler::print(const context &context) const {
    auto insn = context.instruction();
    auto regs = context.registerset();
    const mnemonic &mnemonic = mnemonics[insn.opcode()];
    printf("0x%016lx: ", context.pc());
    printf("%-5s ", mnemonic.name.c_str());
    for (int i = 0; i < mnemonic.format.length(); ++i) {
        if (mnemonic.format[i] == 'd') {
            printf("%s", register_names[insn.rd()].c_str());
        } else if (mnemonic.format[i] == 'o') {
            printf("%s", register_names[insn.rs1()].c_str());
        } else if (mnemonic.format[i] == 't') {
            printf("%s", register_names[insn.rs2()].c_str());
        } else if (mnemonic.format[i] == 'i') {
            printf("%ld", insn.simm());
        } else if (mnemonic.format[i] == 'u') {
            printf("%lu", insn.uimm());
        } else if (mnemonic.format[i] == 's') {
            printf("%lu", insn.shamt());
        } else {
            printf("%c", mnemonic.format[i]);
        }
    }
    puts("");
}

}