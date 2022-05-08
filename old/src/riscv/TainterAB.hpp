# ifndef _RISCV__TAINTERAB_HPP_
# define _RISCV__TAINTERAB_HPP_

# include "Types.hpp"
# include "TargetContext.hpp"
# include <map>
# include <array>

namespace riscv {

class TainterAB {
private:
    std::map<insn_t, bool> _regs;
    std::map<addr_t, bool> _mems;

private:
    bool IsTaintedRegister(insn_t reg);
    bool IsTaintedMemory(addr_t mem);
    void TaintRegister(insn_t reg);
    void TaintMemory(addr_t mem);
    void UntaintRegister(insn_t reg);
    void UntaintMemory(addr_t mem);

    void PrintTaintRegister();
    void PrintTaintMemory();

public:
    void Taint(const TargetContext &context);
    void Debug();
    
};

}

# endif