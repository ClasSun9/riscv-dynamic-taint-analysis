# ifndef _RISCV__REGISTER_HPP_
# define _RISCV__REGISTER_HPP_

# include <cstdint>

namespace riscv {

class GpRegister {
public:
    static constexpr uint64_t Zero = 0;
    static constexpr uint64_t Ra   = 1;
    static constexpr uint64_t Sp   = 2;
    static constexpr uint64_t Gp   = 3;
    static constexpr uint64_t Tp   = 4;
    static constexpr uint64_t T0   = 5;
    static constexpr uint64_t T1   = 6;
    static constexpr uint64_t T2   = 7;
    static constexpr uint64_t S0   = 8;
    static constexpr uint64_t S1   = 9;
    static constexpr uint64_t A0   = 10;
    static constexpr uint64_t A1   = 11;
    static constexpr uint64_t A2   = 12;
    static constexpr uint64_t A3   = 13;
    static constexpr uint64_t A4   = 14;
    static constexpr uint64_t A5   = 15;
    static constexpr uint64_t A6   = 16;
    static constexpr uint64_t A7   = 17;
    static constexpr uint64_t S2   = 18;
    static constexpr uint64_t S3   = 19;
    static constexpr uint64_t S4   = 20;
    static constexpr uint64_t S5   = 21;
    static constexpr uint64_t S6   = 22;
    static constexpr uint64_t S7   = 23;
    static constexpr uint64_t S8   = 24;
    static constexpr uint64_t S9   = 25;
    static constexpr uint64_t S10  = 26;
    static constexpr uint64_t S11  = 27;
    static constexpr uint64_t T3   = 28;
    static constexpr uint64_t T4   = 29;
    static constexpr uint64_t T5   = 30;
    static constexpr uint64_t T6   = 31;
};

}

# endif