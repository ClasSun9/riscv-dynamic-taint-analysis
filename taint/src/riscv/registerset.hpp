#ifndef _RISCV__REGISTERSET_HPP_
#define _RISCV__REGISTERSET_HPP_

#include <array>
#include "./types.hpp"

namespace riscv {

class registerset {
private:
    std::array<rlen_t, 64> _regs;
public:
    rlen_t get(insn_t);
    rlen_t operator[](insn_t id);
public:
    registerset();
    registerset(std::array<rlen_t, 64> regs);
};

}

#endif