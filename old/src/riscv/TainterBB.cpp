# include "TainterBB.hpp"

# include "Opcode.hpp"
# include "Register.hpp"
# include <map>
# include <array>
# include <string>
# include <cstdio>
using std::map;
using std::array;
using std::string;

namespace riscv {

bool TainterBB::IsTaintRegister(insn_t reg, int64_t byte) {
    if (reg == GpRegister::Zero) {
        return false;
    }
    auto iterator = _regs.find(reg + byte);
    if (iterator == _regs.end()) { 
        return false;
    }
    return iterator->second;
}

bool TainterBB::IsTaintMemory(addr_t mem) {
    auto iterator = _mems.find(mem);
    if (iterator == _mems.end()) {
        return false;
    }
    return iterator->second;
}

void TainterBB::TaintRegister(insn_t reg, int64_t byte) {
    if (reg == GpRegister::Zero) {
        return;
    }
    _regs[reg + byte] = true;
}

void TainterBB::TaintMemory(addr_t mem) {
    _mems[mem] = true;
}

void TainterBB::UntaintRegister(insn_t reg, int64_t byte) {
    if (reg == GpRegister::Zero) {
        return;
    }
    _regs[reg + byte] = false;
}

void TainterBB::UntaintMemory(addr_t mem) {
    _mems[mem] = false;
}

void TainterBB::PrintTaintRegister() {
    array<string, 32> abi = {
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

    for (int64_t i = 0; i < 32; ++i) {
        printf("%4s: ", abi[i].c_str());
        for (int64_t j = 0; j < 8; ++j) {
            char state = '\0';
            
            auto reg = _regs.find(i + j);
            if (reg == _regs.end()) {
                state = '-';
            } else {
                state = reg->second
                    ? 'O'
                    : 'X';
            }
            printf("%c ", state);
        }
        printf("\n");
    }
}

void TainterBB::PrintTaintMemory() {
    map<addr_t, char> alignments;
    for (auto &i : _mems) {
        auto alignment = alignments.find(i.first);
        if (alignment == alignments.end()) {
            addr_t b = i.first & ~0b1111;
            addr_t e = i.first | 0b1111;
            for (addr_t i = b; i <= e; ++i) {
                auto mem = _mems.find(i);
                if (mem == _mems.end()) {
                    alignments[i] = '-';
                } else if (mem->second) {
                    alignments[i] = 'O';
                } else {
                    alignments[i] = 'X';
                }
            }
        }
    }

    int64_t newline = 0;
    for (auto &i : alignments) {
        if (newline == 0) {
            printf("0x%016lx: ", i.first);
        }
        printf("%c ", i.second);

        if (++newline == 16) {
            newline = 0;
            printf("\n");
        }
    }
}

void TainterBB::Taint(const TargetContext &context) {
    switch (context.GetOpcode()) {
    case Opcode::Lui: 
    case Opcode::Auipc: {
        break;
    }
    case Opcode::Jal: 
    case Opcode::Jalr: {
        break;
    }
    case Opcode::Beq: 
    case Opcode::Bne:
    case Opcode::Blt:
    case Opcode::Bge:
    case Opcode::Bltu:
    case Opcode::Bgeu: {
        break;
    }
    case Opcode::Lb: 
    case Opcode::Lbu: {
        break;
    }
    case Opcode::Lh: 
    case Opcode::Lhu: {
    }
    case Opcode::Lw: 
    case Opcode::Lwu: {
        break;
    }
    case Opcode::Ld: {
        break;
    }
    case Opcode::Sb: {
        break;
    }
    case Opcode::Sh: {
        break;
    }
    case Opcode::Sw: {
        break;
    }
    case Opcode::Sd: {
        break;
    }
    case Opcode::Add:
    case Opcode::Addw: {
        break;
    }
    case Opcode::Addi:
    case Opcode::Addiw: {
        break;
    }
    case Opcode::Sub:
    case Opcode::Subw: {
        break;
    }
    case Opcode::Slt:
    case Opcode::Sltu: {
        break;
    }
    case Opcode::Slti:
    case Opcode::Sltiu: {
        break;
    }
    case Opcode::Xor: {
        break;
    }
    case Opcode::Xori: {
        break;
    }
    case Opcode::Or: {
        break;
    }
    case Opcode::Ori: {
        break;
    }
    case Opcode::And: {
        break;
    }
    case Opcode::Andi: {
        break;
    }
    case Opcode::Sll: {
        break;
    }
    case Opcode::Sllw: {
        break;
    }
    case Opcode::Slli: {
        break;
    }
    case Opcode::Slliw: {
        break;
    }
    case Opcode::Srl: {
        break;
    }
    case Opcode::Srlw: {
        break;
    }
    case Opcode::Srli: {
        break;
    }
    case Opcode::Srliw: {
        break;
    }
    case Opcode::Sra: {
        break;
    }
    case Opcode::Sraw: {
        break;
    }
    case Opcode::Srai: {
        break;
    }
    case Opcode::Sraiw: {
        break;
    }
    case Opcode::Mul: {
        break;
    }
    case Opcode::Mulw: {
        break;
    }
    case Opcode::Mulh: {
        break;
    }
    case Opcode::Mulhsu: {
        break;
    }
    case Opcode::Mulhu: {
        break;
    }
    case Opcode::Div: {
        break;
    }
    case Opcode::Divw: {
        break;
    }
    case Opcode::Divu: {
        break;
    }
    case Opcode::Divuw: {
        break;
    }
    case Opcode::Rem: {
        break;
    }
    case Opcode::Remw: {
        break;
    }
    case Opcode::Remu: {
        break;
    }
    case Opcode::Remuw: {
        break;
    }
    case Opcode::Pause: {
        break;
    }
    case Opcode::Ecall: {
        uint64_t a0 = context.GetRegValue(GpRegister::A0).AsUnsigned().As64();
        uint64_t a1 = context.GetRegValue(GpRegister::A1).AsUnsigned().As64();
        uint64_t a2 = context.GetRegValue(GpRegister::A2).AsUnsigned().As64();
        uint64_t a7 = context.GetRegValue(GpRegister::A7).AsUnsigned().As64();
        if (a7 == 63) {
            for (addr_t i = 0; i < a2; ++i) {
                TaintMemory(a1 + i);
            }
        }
        break;
    }
    case Opcode::Ebreak: {
        break;
    }
    }
}

void TainterBB::Debug() {

}

}