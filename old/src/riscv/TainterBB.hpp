# ifndef _RISCV__TAINTERBB_HPP_
# define _RISCV__TAINTERBB_HPP_

# include "Types.hpp"
# include "TargetContext.hpp"
# include <map>
# include <array>

namespace riscv {

class TainterBB {
private:
    std::map<insn_t, bool> _regs;
    std::map<addr_t, bool> _mems;

private:
    bool IsTaintRegister(insn_t reg, int64_t byte);
    bool IsTaintMemory(addr_t mem);
    void TaintRegister(insn_t reg, int64_t byte);
    void TaintMemory(addr_t mem);
    void UntaintRegister(insn_t reg, int64_t byte);
    void UntaintMemory(addr_t mem);

    void PrintTaintRegister();
    void PrintTaintMemory();

public:
    void Taint(const TargetContext &context);
    void Debug();
};

}

# endif