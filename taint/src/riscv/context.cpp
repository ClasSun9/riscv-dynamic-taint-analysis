# include "context.hpp"

const instruction& context::instruction() {
    return _insn;
}

const registerset& context::regisetset() {
    return _regs;
}

context::context(addr_t pc, instruction insn, registerset regs) : 
    _pc(pc),
    _insn(insn),
    _regs(regs) { }