# ifndef _RISCV__DISASSEMBLER_HPP_
# define _RISCV__DISASSEMBLER_HPP_

# include "context.hpp"

namespace riscv {

class disassembler {
public:
    static void print(const context &context) const;

public:
    disassembler() = delete;
};

}

# endif