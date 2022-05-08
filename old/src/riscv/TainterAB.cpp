# include "TainterAB.hpp"

# include "Opcode.hpp"
# include "Register.hpp"
# include <array>
# include <string>
# include <cstdio>
using std::array;
using std::string;
using std::map;

namespace riscv {

bool TainterAB::IsTaintedRegister(insn_t reg) {
    if (reg == GpRegister::Zero) {
        return false;
    }
    auto iterator = _regs.find(reg);
    if (iterator == _regs.end()) { 
        return false;
    }
    return iterator->second;
}

bool TainterAB::IsTaintedMemory(addr_t mem) {
    auto iterator = _mems.find(mem);
    if (iterator == _mems.end()) {
        return false;
    }
    return iterator->second;
}

void TainterAB::TaintRegister(insn_t reg) {
    if (reg == GpRegister::Zero) {
        return;
    }
    _regs[reg] = true;
}

void TainterAB::TaintMemory(addr_t mem) {
    _mems[mem] = true;
}

void TainterAB::UntaintRegister(insn_t reg) {
    if (reg == GpRegister::Zero) {
        return;
    }
    _regs[reg] = false;
}

void TainterAB::UntaintMemory(addr_t mem) {
    _mems[mem] = false;
}

void TainterAB::PrintTaintRegister() {
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

    int64_t newline = 0;
    for (int64_t i = 0; i < 32; ++i) {
        char state = '\0';

        auto reg = _regs.find(i);
        if (reg == _regs.end()) {
            state = '-';
        } else {
            state = reg->second
                ? 'O'
                : 'X';
        }
        printf("%4s: %c ", abi[i].c_str(), state);
        if (++newline == 4) {
            newline = 0;
            printf("\n");
        }
    }
}

void TainterAB::PrintTaintMemory() {
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

void TainterAB::Taint(const TargetContext &context) {
    switch (context.GetOpcode()) {
    case Opcode::Lui: 
    case Opcode::Auipc: {
        UntaintRegister(context.GetRdType());
        break;
    }
    case Opcode::Jal: 
    case Opcode::Jalr: {
        UntaintRegister(context.GetRdType());
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
        addr_t mem = 
            context.GetRs1Value().AsUnsigned().As64() +
            context.GetImmValue().AsSigned().As32();
        if (IsTaintedMemory(mem)) {
            TaintRegister(context.GetRdType());
        } else {
            UntaintRegister(context.GetRdType());
        }
        break;
    }
    case Opcode::Lh: 
    case Opcode::Lhu: {
        insn_t rd = context.GetRdType();
        addr_t mem = 
            context.GetRs1Value().AsUnsigned().As64() +
            context.GetImmValue().AsSigned().As32();
        if (IsTaintedMemory(mem) || 
            IsTaintedMemory(mem + 1)) {
            TaintRegister(rd);
        } else {
            UntaintRegister(rd);
        }
        break;
    }
    case Opcode::Lw: 
    case Opcode::Lwu: {
        addr_t mem = 
            context.GetRs1Value().AsUnsigned().As64() +
            context.GetImmValue().AsSigned().As32();
        if (IsTaintedMemory(mem) ||
            IsTaintedMemory(mem + 1) ||
            IsTaintedMemory(mem + 2) ||
            IsTaintedMemory(mem + 3)) {
            TaintRegister(context.GetRdType());
        } else {
            UntaintRegister(context.GetRdType());
        }
        break;
    }
    case Opcode::Ld: {
        addr_t mem = 
            context.GetRs1Value().AsUnsigned().As64() +
            context.GetImmValue().AsSigned().As32();
        if (IsTaintedMemory(mem) ||
            IsTaintedMemory(mem + 1) ||
            IsTaintedMemory(mem + 2) ||
            IsTaintedMemory(mem + 3) ||
            IsTaintedMemory(mem + 4) ||
            IsTaintedMemory(mem + 5) ||
            IsTaintedMemory(mem + 6) ||
            IsTaintedMemory(mem + 7)) {
            TaintRegister(context.GetRdType());
        } else {
            UntaintRegister(context.GetRdType());
        }
        break;
    }
    case Opcode::Sb: {
        insn_t rs2 = context.GetRs2Type();
        addr_t mem = 
            context.GetRs1Value().AsUnsigned().As64() +
            context.GetImmValue().AsSigned().As32();
        if (IsTaintedRegister(rs2)) {
            TaintMemory(mem);
        } else {
            UntaintMemory(mem);
        }
        break;
    }
    case Opcode::Sh: {
        insn_t rs2 = context.GetRs2Type();
        addr_t mem = 
            context.GetRs1Value().AsUnsigned().As64() +
            context.GetImmValue().AsSigned().As32();
        if (IsTaintedRegister(rs2)) {
            TaintMemory(mem);
            TaintMemory(mem + 1);
        } else {
            UntaintMemory(mem);
            UntaintMemory(mem + 1);
        }
        break;
    }
    case Opcode::Sw: {
        insn_t rs2 = context.GetRs2Type();
        addr_t mem = 
            context.GetRs1Value().AsUnsigned().As64() +
            context.GetImmValue().AsSigned().As32();
        if (IsTaintedRegister(rs2)) {
            TaintMemory(mem);
            TaintMemory(mem + 1);
            TaintMemory(mem + 2);
            TaintMemory(mem + 3);
        } else {
            UntaintMemory(mem);
            UntaintMemory(mem + 1);
            UntaintMemory(mem + 2);
            UntaintMemory(mem + 3);
        }
        break;
    }
    case Opcode::Sd: {
        insn_t rs2 = context.GetRs2Type();
        addr_t mem = 
            context.GetRs1Value().AsUnsigned().As64() +
            context.GetImmValue().AsSigned().As32();
        if (IsTaintedRegister(rs2)) {
            TaintMemory(mem);
            TaintMemory(mem + 1);
            TaintMemory(mem + 2);
            TaintMemory(mem + 3);
            TaintMemory(mem + 4);
            TaintMemory(mem + 5);
            TaintMemory(mem + 6);
            TaintMemory(mem + 7);
        } else {
            UntaintMemory(mem);
            UntaintMemory(mem + 1);
            UntaintMemory(mem + 2);
            UntaintMemory(mem + 3);
            UntaintMemory(mem + 4);
            UntaintMemory(mem + 5);
            UntaintMemory(mem + 6);
            UntaintMemory(mem + 7);
        }
        break;
    }
    case Opcode::Add:
    case Opcode::Addw: {
        insn_t rd = context.GetRdType();
        insn_t rs1 = context.GetRs1Type();
        insn_t rs2 = context.GetRs2Type();
        if (IsTaintedRegister(rs1) || IsTaintedRegister(rs2)) {
            TaintRegister(rd);
        } else {
            UntaintRegister(rd);
        }
        break;
    }
    case Opcode::Addi:
    case Opcode::Addiw: {
        insn_t rd = context.GetRdType();
        insn_t rs1 = context.GetRs1Type();
        if (IsTaintedRegister(rs1)) {
            TaintRegister(rd);
        } else {
            UntaintRegister(rd);
        }
        break;
    }
    case Opcode::Sub:
    case Opcode::Subw: {
        insn_t rd = context.GetRdType();
        insn_t rs1 = context.GetRs1Type();
        insn_t rs2 = context.GetRs2Type();
        if (IsTaintedRegister(rs1) || IsTaintedRegister(rs2)) {
            TaintRegister(rd);
        } else {
            UntaintRegister(rd);
        }
        break;
    }
    case Opcode::Slt:
    case Opcode::Sltu: {
        insn_t rd = context.GetRdType();
        insn_t rs1 = context.GetRs1Type();
        insn_t rs2 = context.GetRs2Type();
        if (IsTaintedRegister(rs1) || IsTaintedRegister(rs2)) {
            TaintRegister(rd);
        } else {
            UntaintRegister(rd);
        }
        break;
    }
    case Opcode::Slti:
    case Opcode::Sltiu: {
        insn_t rd = context.GetRdType();
        insn_t rs1 = context.GetRs1Type();
        if (IsTaintedRegister(rs1)) {
            TaintRegister(rd);
        } else {
            UntaintRegister(rd);
        }
        break;
    }
    case Opcode::Xor: {
        insn_t rd = context.GetRdType();
        insn_t rs1 = context.GetRs1Type();
        insn_t rs2 = context.GetRs2Type();
        if (IsTaintedRegister(rs1) && IsTaintedRegister(rs2)) {
            if (rs1 == rs2) {
                UntaintRegister(rd);
            } else {
                TaintRegister(rd);
            }
        } else {
            UntaintRegister(rd);
        }
        break;
    }
    case Opcode::Xori: {
        insn_t rd = context.GetRdType();
        insn_t rs1 = context.GetRs1Type();
        if (IsTaintedRegister(rs1)) {
            TaintRegister(rd);
        } else {
            UntaintRegister(rd);
        }
        break;
    }
    case Opcode::Or: {
        insn_t rd = context.GetRdType();
        insn_t rs1 = context.GetRs1Type();
        insn_t rs2 = context.GetRs2Type();

        bool isTaintedRs1 = IsTaintedRegister(rs1);
        bool isTaintedRs2 = IsTaintedRegister(rs2);

        if (isTaintedRs1 && isTaintedRs2) {
            TaintRegister(rd);
        } else if (!isTaintedRs1 && isTaintedRs2) {
            uint64_t rs1Value = context.GetRs1Value().AsUnsigned().As64();
            if (rs1Value == 0xffffffffffffffff) {
                UntaintRegister(rd);
            } else {
                TaintRegister(rd);
            }
        } else if (isTaintedRs1 && !isTaintedRs2) {
            uint64_t rs2Value = context.GetRs2Value().AsUnsigned().As64();
            if (rs2Value = 0xffffffffffffffff) {
                UntaintRegister(rd);
            } else {
                TaintRegister(rd);
            }
        } else {
            UntaintRegister(rd);
        }
        break;
    }
    case Opcode::Ori: {
        insn_t rd = context.GetRdType();
        insn_t rs1 = context.GetRs1Type();
        uint32_t imm = context.GetImmValue().AsUnsigned().As32();
        if (IsTaintedRegister(rs1)) {
            if (imm == 0xfff) {
                UntaintRegister(rd);
            } else {
                TaintRegister(rd);
            }
        } else {
            UntaintRegister(rd);
        }
        break;
    }
    case Opcode::And: {
        insn_t rd = context.GetRdType();
        insn_t rs1 = context.GetRs1Type();
        insn_t rs2 = context.GetRs2Type();

        bool isTaintedRs1 = IsTaintedRegister(rs1);
        bool isTaintedRs2 = IsTaintedRegister(rs2);

        if (isTaintedRs1 && isTaintedRs2) {
            TaintRegister(rd);
        } else if (!isTaintedRs1 && isTaintedRs2) {
            uint64_t rs1Value = context.GetRs1Value().AsUnsigned().As64();
            if (rs1Value == 0) {
                UntaintRegister(rd);
            } else {
                TaintRegister(rd);
            }
        } else if (isTaintedRs1 && isTaintedRs2) {
            uint64_t rs2Value = context.GetRs2Value().AsUnsigned().As64();
            if (rs2Value == 0) {
                UntaintRegister(rd);
            } else {
                TaintRegister(rd);
            }
        } else {
            UntaintRegister(rd);
        }
        break;
    }
    case Opcode::Andi: {
        insn_t rd = context.GetRdType();
        insn_t rs1 = context.GetRs1Type();
        uint32_t imm = context.GetImmValue().AsUnsigned().As32();
        if (IsTaintedRegister(rs1)) {
            if (imm == 0) {
                UntaintRegister(rd);
            } else {
                TaintRegister(rd);
            }
        } else {
            UntaintRegister(rd);
        }
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

void TainterAB::Debug() {
    PrintTaintRegister();
    PrintTaintMemory();
}

}