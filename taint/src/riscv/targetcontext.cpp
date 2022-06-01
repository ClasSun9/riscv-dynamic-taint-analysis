#include "./targetcontext.hpp"

namespace riscv {

addr_t targetcontext::pc() {
    return _pc;
}

const instruction& targetcontext::insn() {
    return _insn;
}

const registerset& targetcontext::regs() {
    return _regs;
}

targetcontext::targetcontext() { }
targetcontext::targetcontext(addr_t pc, instruction insn, registerset regs) 
    : _pc(pc)
    , _insn(insn)
    , _regs(regs) { }

}