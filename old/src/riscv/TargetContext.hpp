# ifndef _RISCV__TARGETCONTEXT_HPP_
# define _RISCV__TARGETCONTEXT_HPP_

# include "Types.hpp"
# include "Value.hpp"
# include "TargetContextParameter.hpp"
# include <array>
# include <memory>

namespace riscv {

class TargetContext {
private:
    addr_t _pc;
    insn_t _insn;

    uint64_t _opcode;
    uint64_t _length;

    insn_t _rd;
    insn_t _rs1;
    insn_t _rs2;
    insn_t _imm;
    insn_t _shamt;

    std::array<xlen_t, 32> _gpr;
    std::array<flen_t, 32> _fpr;

public:
    static TargetContext Create(TargetContextParameter &parameter);

public:
    addr_t GetPc() const;
    insn_t GetInstruction() const;

    uint64_t GetOpcode() const;
    uint64_t GetLength() const;

    insn_t GetRdType() const;
    insn_t GetRs1Type() const;
    insn_t GetRs2Type() const;

    Value GetImmValue() const;
    Value GetRdValue() const;
    Value GetRs1Value() const;
    Value GetRs2Value() const;
    Value GetRegValue(uint64_t _reg) const;
    Value GetShamtValue() const;
};

}

# endif