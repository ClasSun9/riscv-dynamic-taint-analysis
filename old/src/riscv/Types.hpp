# ifndef _RISCV__TYPES_HPP_
# define _RISCV__TYPES_HPP_

# include <cstdint>

namespace riscv {

# if __riscv_xlen == 32
    # error "Only supported RV64"
# endif

typedef uint32_t insn_t;
typedef uint64_t addr_t;
typedef uint64_t xlen_t;
typedef uint64_t flen_t;

}

# endif