# ifndef _RISCV__DISASSEMBLER_HPP_
# define _RISCV__DISASSEMBLER_HPP_

# include "TargetContext.hpp"

namespace riscv {

class Disassembler {
public:
    void Print(const TargetContext &context) const;
};

}

# endif