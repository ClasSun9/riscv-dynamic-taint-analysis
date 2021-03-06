#ifndef _RISCV__TYPES_HPP_
#define _RISCV__TYPES_HPP_

#include <cstdint>

namespace riscv {

#if __riscv_xlen == 32
    #error "only support rv64"
#endif

typedef uint32_t insn_t;
typedef uint64_t addr_t;
typedef uint64_t rlen_t;

}

#endif