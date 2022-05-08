# ifndef _RISCV__CONTEXT_HPP_
# define _RISCV__CONTEXT_HPP_

# include "types.hpp"
# include "instruction.hpp"
# include "registerset.hpp"

namespace riscv {

class context {
private:
    addr_t _pc;
    instruction _insn;
    registerset _regs;

public:
    const instruction& instruction();
    const registerset& registerset();

public:
    context(addr_t pc, instruction insn, registerset regs);
};

}

# endif