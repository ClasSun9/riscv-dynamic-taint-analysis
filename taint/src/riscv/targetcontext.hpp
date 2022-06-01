#ifndef _RISCV__TARGETCONTEXT_HPP_
#define _RISCV__TARGETCONTEXT_HPP_
#include "./types.hpp"
#include "./instruction.hpp"
#include "./registerset.hpp"

namespace riscv {

class targetcontext {
private:
    addr_t _pc;
    instruction _insn;
    registerset _regs;
public:
    addr_t pc();
    const instruction& insn();
    const registerset& regs();
public:
    targetcontext();
    targetcontext(addr_t pc, instruction insn, registerset regs);
};

}

#endif