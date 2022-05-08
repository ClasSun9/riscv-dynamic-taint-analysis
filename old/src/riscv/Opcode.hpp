# ifndef _RISCV__OPCODE_HPP_
# define _RISCV__OPCODE_HPP_

# include <cstdint>

namespace riscv {

class Opcode {
public:
    static constexpr uint64_t Lui    = 0;
    static constexpr uint64_t Auipc  = 1;
    static constexpr uint64_t Jal    = 2;
    static constexpr uint64_t Jalr   = 3;
    static constexpr uint64_t Beq    = 4;
    static constexpr uint64_t Bne    = 5;
    static constexpr uint64_t Blt    = 6;
    static constexpr uint64_t Bge    = 7;
    static constexpr uint64_t Bltu   = 8;
    static constexpr uint64_t Bgeu   = 9;
    static constexpr uint64_t Lb     = 10;
    static constexpr uint64_t Lh     = 11;
    static constexpr uint64_t Lw     = 12;
    static constexpr uint64_t Ld     = 13;
    static constexpr uint64_t Lbu    = 14;
    static constexpr uint64_t Lhu    = 15;
    static constexpr uint64_t Lwu    = 16;
    static constexpr uint64_t Sb     = 17;
    static constexpr uint64_t Sh     = 18;
    static constexpr uint64_t Sw     = 19;
    static constexpr uint64_t Sd     = 20;
    static constexpr uint64_t Add    = 21;
    static constexpr uint64_t Addw   = 22;
    static constexpr uint64_t Addi   = 23;
    static constexpr uint64_t Addiw  = 24;
    static constexpr uint64_t Sub    = 25;
    static constexpr uint64_t Subw   = 26;
    static constexpr uint64_t Slt    = 27;
    static constexpr uint64_t Sltu   = 28;
    static constexpr uint64_t Slti   = 29;
    static constexpr uint64_t Sltiu  = 30;
    static constexpr uint64_t Xor    = 31;
    static constexpr uint64_t Xori   = 32;
    static constexpr uint64_t Or     = 33;
    static constexpr uint64_t Ori    = 34;
    static constexpr uint64_t And    = 35;
    static constexpr uint64_t Andi   = 36;
    static constexpr uint64_t Sll    = 37;
    static constexpr uint64_t Sllw   = 38;
    static constexpr uint64_t Slli   = 39;
    static constexpr uint64_t Slliw  = 40;
    static constexpr uint64_t Srl    = 41;
    static constexpr uint64_t Srlw   = 42;
    static constexpr uint64_t Srli   = 43;
    static constexpr uint64_t Srliw  = 44;
    static constexpr uint64_t Sra    = 45;
    static constexpr uint64_t Sraw   = 46;
    static constexpr uint64_t Srai   = 47;
    static constexpr uint64_t Sraiw  = 48;
    static constexpr uint64_t Mul    = 49;
    static constexpr uint64_t Mulw   = 50;
    static constexpr uint64_t Mulh   = 51;
    static constexpr uint64_t Mulhsu = 52;
    static constexpr uint64_t Mulhu  = 53;
    static constexpr uint64_t Div    = 54;
    static constexpr uint64_t Divw   = 55;
    static constexpr uint64_t Divu   = 56;
    static constexpr uint64_t Divuw  = 57;
    static constexpr uint64_t Rem    = 58;
    static constexpr uint64_t Remw   = 59;
    static constexpr uint64_t Remu   = 60;
    static constexpr uint64_t Remuw  = 61;
    static constexpr uint64_t Pause  = 62;
    static constexpr uint64_t Ecall  = 63;
    static constexpr uint64_t Ebreak = 64;
};

}

# endif