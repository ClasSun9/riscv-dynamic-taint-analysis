# ifndef _RISCV__TARGETCONTEXTPARAMETER_HPP_
# define _RISCV__TARGETCONTEXTPARAMETER_HPP_

# include "Types.hpp"
# include <array>

namespace riscv {

class TargetContextParameter {
private:
    addr_t _pc;
    insn_t _insn;
    std::array<xlen_t, 32> _gpr;
    std::array<flen_t, 32> _fpr;

public:
    TargetContextParameter& SetPc(addr_t pc);
    TargetContextParameter& SetInstruction(insn_t insn);
    TargetContextParameter& SetGpRegister(std::array<xlen_t, 32> gpr);
    TargetContextParameter& SetFpRegister(std::array<flen_t, 32> fpr);

    addr_t GetPc();
    insn_t GetInstruction();
    std::array<xlen_t, 32> GetGpRegister();
    std::array<flen_t, 32> GetFpRegister();
};

}

# endif