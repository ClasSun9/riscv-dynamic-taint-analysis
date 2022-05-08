# include "Disassembler.hpp"

# include "Opcode.hpp"
# include <cstdio>
# include <array>
# include <string>
using std::array;
using std::string;

namespace riscv {

class Mnemonic {
public:
    string name;
    // d == rd
    // o == rs1
    // t == rs2
    // i == signed imm
    // u == unsigned imm
    // s == shamt
    string format;
};

array<Mnemonic, 65> mnemonics = {
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
    "addw", "d, o, t",
    "addi", "d, o, i",
    "addiw", "d, o, i",
    "sub", "d, o, t",
    "subw", "d, o, t",
    "slt", "d, o, t",
    "sltu", "d, o, t",
    "slti", "d, o, i",
    "sltiu", "d, o, u",
    "xor", "d, o, t",
    "xori", "d, o, u",
    "or", "d, o, t",
    "ori", "d, o, u",
    "and", "d, o, t",
    "andi", "d, o, u",
    "sll", "d, o, t",
    "sllw", "d, o, t",
    "slli", "d, o, s",
    "slliw", "d, o, s",
    "srl", "d, o, t",
    "srlw", "d, o, t",
    "srli", "d, o, s",
    "srliw", "d, o, s",
    "sra", "d, o, t",
    "sraw", "d, o, t",
    "srai", "d, o, s",
    "sraiw", "d, o, s",
    "mul", "d, o, t",
    "mulw", "d, o, t",
    "mulh", "d, o, t",
    "mulhsu", "d, o, t",
    "mulhu", "d, o, t",
    "div", "d, o, t",
    "divw", "d, o, t",
    "divu", "d, o, t",
    "divuw", "d, o, t",
    "rem", "d, o, t",
    "remw", "d, o, t",
    "remu", "d, o, t",
    "remuw", "d, o, t",
    "pause", "",
    "ecall", "",
    "ebreak", "",
};

array<string, 32> nameForReg = {
    "zero",
    "ra",
    "sp",
    "gp",
    "tp",
    "t0",
    "t1",
    "t2",
    "s0",
    "s1",
    "a0",
    "a1",
    "a2",
    "a3",
    "a4",
    "a5",
    "a6",
    "a7",
    "s2",
    "s3",
    "s4",
    "s5",
    "s6",
    "s7",
    "s8",
    "s9",
    "s10",
    "s11",
    "t3",
    "t4",
    "t5",
    "t6",
};

void Disassembler::Print(const TargetContext &context) const {
    const Mnemonic &mnemonic = mnemonics[context.GetOpcode()];
    printf("0x%016lx: ", context.GetPc());
    printf("%-5s ", mnemonic.name.c_str());
    for (int i = 0; i < mnemonic.format.length(); ++i) {
        if (mnemonic.format[i] == 'd') {
            printf("%s", nameForReg[context.GetRdType()].c_str());
        } else if (mnemonic.format[i] == 'o') {
            printf("%s", nameForReg[context.GetRs1Type()].c_str());
        } else if (mnemonic.format[i] == 't') {
            printf("%s", nameForReg[context.GetRs2Type()].c_str());
        } else if (mnemonic.format[i] == 'i') {
            printf("%d", context.GetImmValue().AsSigned().As32());
        } else if (mnemonic.format[i] == 'u') {
            printf("%u", context.GetImmValue().AsUnsigned().As32());
        } else if (mnemonic.format[i] == 's') {
            printf("%u", context.GetShamtValue().AsUnsigned().As32());
        } else {
            printf("%c", mnemonic.format[i]);
        }
    }
    puts("");
}

}