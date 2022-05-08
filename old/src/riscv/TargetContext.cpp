# include "TargetContext.hpp"

# include "Opcode.hpp"
# include <functional>
# include <cstdio>

using std::function;
using std::array;
using std::shared_ptr;
using std::make_shared;

namespace riscv {

    namespace insn {

    class Attribute {                                                                                                                                                                                     
    public:
        static constexpr uint64_t Empty  = 0x0000000000000000;
        static constexpr uint64_t Rd     = 0x0000000000000001;
        static constexpr uint64_t Rs1    = 0x0000000000000002;
        static constexpr uint64_t Rs2    = 0x0000000000000004;
        static constexpr uint64_t Immi   = 0x0000000000000010;
        static constexpr uint64_t Imms   = 0x0000000000000020;
        static constexpr uint64_t Immb   = 0x0000000000000040;
        static constexpr uint64_t Immu   = 0x0000000000000080;
        static constexpr uint64_t Immj   = 0x0000000000000100;
        static constexpr uint64_t Shamt5 = 0x0000000000001000;
        static constexpr uint64_t Shamt6 = 0x0000000000002000;
        static constexpr uint64_t Signed = 0x1000000000000000;
    };

    class Mask {
    public:
        static constexpr insn_t Lui    = 0b00000000'00000000'00000000'01111111;
        static constexpr insn_t Auipc  = 0b00000000'00000000'00000000'01111111;
        static constexpr insn_t Jal    = 0b00000000'00000000'00000000'01111111;
        static constexpr insn_t Jalr   = 0b00000000'00000000'01110000'01111111;
        static constexpr insn_t Beq    = 0b00000000'00000000'01110000'01111111;
        static constexpr insn_t Bne    = 0b00000000'00000000'01110000'01111111;
        static constexpr insn_t Blt    = 0b00000000'00000000'01110000'01111111;
        static constexpr insn_t Bge    = 0b00000000'00000000'01110000'01111111;
        static constexpr insn_t Bltu   = 0b00000000'00000000'01110000'01111111;
        static constexpr insn_t Bgeu   = 0b00000000'00000000'01110000'01111111;
        static constexpr insn_t Lb     = 0b00000000'00000000'01110000'01111111;
        static constexpr insn_t Lh     = 0b00000000'00000000'01110000'01111111;
        static constexpr insn_t Lw     = 0b00000000'00000000'01110000'01111111;
        static constexpr insn_t Ld     = 0b00000000'00000000'01110000'01111111;
        static constexpr insn_t Lbu    = 0b00000000'00000000'01110000'01111111;
        static constexpr insn_t Lhu    = 0b00000000'00000000'01110000'01111111;
        static constexpr insn_t Lwu    = 0b00000000'00000000'01110000'01111111;
        static constexpr insn_t Sb     = 0b00000000'00000000'01110000'01111111;
        static constexpr insn_t Sh     = 0b00000000'00000000'01110000'01111111;
        static constexpr insn_t Sw     = 0b00000000'00000000'01110000'01111111;
        static constexpr insn_t Sd     = 0b00000000'00000000'01110000'01111111;
        static constexpr insn_t Add    = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Addw   = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Addi   = 0b00000000'00000000'01110000'01111111;
        static constexpr insn_t Addiw  = 0b00000000'00000000'01110000'01111111;
        static constexpr insn_t Sub    = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Subw   = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Slt    = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Sltu   = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Slti   = 0b00000000'00000000'01110000'01111111;
        static constexpr insn_t Sltiu  = 0b00000000'00000000'01110000'01111111;
        static constexpr insn_t Xor    = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Xori   = 0b00000000'00000000'01110000'01111111;
        static constexpr insn_t Or     = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Ori    = 0b00000000'00000000'01110000'01111111;
        static constexpr insn_t And    = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Andi   = 0b00000000'00000000'01110000'01111111;
        static constexpr insn_t Sll    = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Sllw   = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Slli   = 0b11111100'00000000'01110000'01111111;
        static constexpr insn_t Slliw  = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Srl    = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Srlw   = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Srli   = 0b11111100'00000000'01110000'01111111;
        static constexpr insn_t Srliw  = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Sra    = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Sraw   = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Srai   = 0b11111100'00000000'01110000'01111111;
        static constexpr insn_t Sraiw  = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Mul    = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Mulw   = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Mulh   = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Mulhsu = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Mulhu  = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Div    = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Divw   = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Divu   = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Divuw  = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Rem    = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Remw   = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Remu   = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Remuw  = 0b11111110'00000000'01110000'01111111;
        static constexpr insn_t Pause  = 0b11111111'11111111'11111111'11111111;
        static constexpr insn_t Ecall  = 0b11111111'11111111'11111111'11111111;
        static constexpr insn_t Ebreak = 0b11111111'11111111'11111111'11111111;
    };

    class Match {
    public:
        static constexpr insn_t Lui    = 0b00000000'00000000'00000000'00110111;
        static constexpr insn_t Auipc  = 0b00000000'00000000'00000000'00010111;
        static constexpr insn_t Jal    = 0b00000000'00000000'00000000'01101111;
        static constexpr insn_t Jalr   = 0b00000000'00000000'00000000'01100111;
        static constexpr insn_t Beq    = 0b00000000'00000000'00000000'01100011;
        static constexpr insn_t Bne    = 0b00000000'00000000'00010000'01100011;
        static constexpr insn_t Blt    = 0b00000000'00000000'01000000'01100011;
        static constexpr insn_t Bge    = 0b00000000'00000000'01010000'01100011;
        static constexpr insn_t Bltu   = 0b00000000'00000000'01100000'01100011;
        static constexpr insn_t Bgeu   = 0b00000000'00000000'01110000'01100011;
        static constexpr insn_t Lb     = 0b00000000'00000000'00000000'00000011;
        static constexpr insn_t Lh     = 0b00000000'00000000'00010000'00000011;
        static constexpr insn_t Lw     = 0b00000000'00000000'00100000'00000011;
        static constexpr insn_t Ld     = 0b00000000'00000000'00110000'00000011;
        static constexpr insn_t Lbu    = 0b00000000'00000000'01000000'00000011;
        static constexpr insn_t Lhu    = 0b00000000'00000000'01010000'00000011;
        static constexpr insn_t Lwu    = 0b00000000'00000000'01100000'00000011;
        static constexpr insn_t Sb     = 0b00000000'00000000'00000000'00100011;
        static constexpr insn_t Sh     = 0b00000000'00000000'00010000'00100011;
        static constexpr insn_t Sw     = 0b00000000'00000000'00100000'00100011;
        static constexpr insn_t Sd     = 0b00000000'00000000'00110000'00100011;
        static constexpr insn_t Add    = 0b00000000'00000000'00000000'00110011;
        static constexpr insn_t Addw   = 0b00000000'00000000'00000000'00111011;
        static constexpr insn_t Addi   = 0b00000000'00000000'00000000'00010011;
        static constexpr insn_t Addiw  = 0b00000000'00000000'00000000'00011011;
        static constexpr insn_t Sub    = 0b01000000'00000000'00000000'00110011;
        static constexpr insn_t Subw   = 0b01000000'00000000'00000000'00111011;
        static constexpr insn_t Slt    = 0b00000000'00000000'00100000'00110011;
        static constexpr insn_t Sltu   = 0b00000000'00000000'00110000'00110011;
        static constexpr insn_t Slti   = 0b00000000'00000000'00100000'00010011;
        static constexpr insn_t Sltiu  = 0b00000000'00000000'00110000'00010011;
        static constexpr insn_t Xor    = 0b00000000'00000000'01000000'00110011;
        static constexpr insn_t Xori   = 0b00000000'00000000'01000000'00010011;
        static constexpr insn_t Or     = 0b00000000'00000000'01100000'00110011;
        static constexpr insn_t Ori    = 0b00000000'00000000'01100000'00010011;
        static constexpr insn_t And    = 0b00000000'00000000'01110000'00110011;
        static constexpr insn_t Andi   = 0b00000000'00000000'01110000'00010011;
        static constexpr insn_t Sll    = 0b00000000'00000000'00010000'00110011;
        static constexpr insn_t Sllw   = 0b00000000'00000000'00010000'00111011;
        static constexpr insn_t Slli   = 0b00000000'00000000'00010000'00010011;
        static constexpr insn_t Slliw  = 0b00000000'00000000'00010000'00011011;
        static constexpr insn_t Srl    = 0b00000000'00000000'01010000'00110011;
        static constexpr insn_t Srlw   = 0b00000000'00000000'01010000'00111011;
        static constexpr insn_t Srli   = 0b00000000'00000000'01010000'00010011;
        static constexpr insn_t Srliw  = 0b00000000'00000000'01010000'00011011;
        static constexpr insn_t Sra    = 0b01000000'00000000'01010000'00110011;
        static constexpr insn_t Sraw   = 0b01000000'00000000'01010000'00111011;
        static constexpr insn_t Srai   = 0b01000000'00000000'01010000'00010011;
        static constexpr insn_t Sraiw  = 0b01000000'00000000'01010000'00011011;
        static constexpr insn_t Mul    = 0b00000010'00000000'00000000'00110011;
        static constexpr insn_t Mulw   = 0b00000010'00000000'00000000'00111011;
        static constexpr insn_t Mulh   = 0b00000010'00000000'00010000'00110011;
        static constexpr insn_t Mulhsu = 0b00000010'00000000'00100000'00110011;
        static constexpr insn_t Mulhu  = 0b00000010'00000000'00110000'00110011;
        static constexpr insn_t Div    = 0b00000010'00000000'01000000'00110011;
        static constexpr insn_t Divw   = 0b00000010'00000000'01000000'00111011;
        static constexpr insn_t Divu   = 0b00000010'00000000'01010000'00110011;
        static constexpr insn_t Divuw  = 0b00000010'00000000'01010000'00111011;
        static constexpr insn_t Rem    = 0b00000010'00000000'01100000'00110011;
        static constexpr insn_t Remw   = 0b00000010'00000000'01100000'00111011;
        static constexpr insn_t Remu   = 0b00000010'00000000'01110000'00110011;
        static constexpr insn_t Remuw  = 0b00000010'00000000'01110000'00111011;
        static constexpr insn_t Pause  = 0b00000001'00000000'00000000'00001111;
        static constexpr insn_t Ecall  = 0b00000000'00000000'00000000'01110011;
        static constexpr insn_t Ebreak = 0b00000000'00010000'00000000'01110011;
    };

    class Parser {
    private:
        static constexpr insn_t RdMask      = 0b00000000'00000000'00001111'10000000;
        static constexpr insn_t RdShift     = 7;
        static constexpr insn_t Rs1Mask     = 0b00000000'00001111'10000000'00000000;
        static constexpr insn_t Rs1Shift    = 15;
        static constexpr insn_t Rs2Mask     = 0b00000001'11110000'00000000'00000000;
        static constexpr insn_t Rs2Shift    = 20;
        static constexpr insn_t Shamt5Mask  = 0b00000001'11110000'00000000'00000000;
        static constexpr insn_t Shamt5Shift = 20;
        static constexpr insn_t Shamt6Mask  = 0b00000011'11110000'00000000'00000000;
        static constexpr insn_t Shamt6Shift = 20;

        static constexpr insn_t Immi11Mask  = 0b11111111'11110000'00000000'00000000;
        static constexpr insn_t Immi11Shift = 20;

        static constexpr insn_t Imms4Mask   = 0b00000000'00000000'00001111'10000000;
        static constexpr insn_t Imms4Shift  = 7;
        static constexpr insn_t Imms11Mask  = 0b11111110'00000000'00000000'00000000;
        static constexpr insn_t Imms11Shift = 20;

        static constexpr insn_t Immb4Mask   = 0b00000000'00000000'00001111'00000000;
        static constexpr insn_t Immb4Shift  = 7;
        static constexpr insn_t Immb10Mask  = 0b01111110'00000000'00000000'00000000;
        static constexpr insn_t Immb10Shift = 20;
        static constexpr insn_t Immb11Mask  = 0b00000000'00000000'00000000'10000000;
        static constexpr insn_t Immb11Shift = 4;
        static constexpr insn_t Immb12Mask  = 0b10000000'00000000'00000000'00000000;
        static constexpr insn_t Immb12Shift = 19;

        static constexpr insn_t Immu31Mask  = 0b11111111'11111111'11110000'00000000;
        static constexpr insn_t Immu31Shift = 0;

        static constexpr insn_t Immj10Mask  = 0b01111111'11100000'00000000'00000000;
        static constexpr insn_t Immj10Shift = 20;
        static constexpr insn_t Immj11Mask  = 0b00000000'00010000'00000000'00000000;
        static constexpr insn_t Immj11Shift = 9;
        static constexpr insn_t Immj19Mask  = 0b00000000'00001111'11110000'00000000;
        static constexpr insn_t Immj19Shift = 0;
        static constexpr insn_t Immj20Mask  = 0b10000000'00000000'00000000'00000000;
        static constexpr insn_t Immj20Shift = 11;

    public:
        static insn_t ParseRd(insn_t insn) {
            return (insn & RdMask) >> RdShift;
        }

        static insn_t ParseRs1(insn_t insn) {
            return (insn & Rs1Mask) >> Rs1Shift;
        }

        static insn_t ParseRs2(insn_t insn) {
            return (insn & Rs2Mask) >> Rs2Shift;
        }

        static insn_t ParseShamt5(insn_t insn) {
            return (insn & Shamt5Mask) >> Shamt5Shift;
        }

        static insn_t ParseShamt6(insn_t insn) {
            return (insn & Shamt6Mask) >> Shamt6Shift;
        }

        static insn_t ParseImmiAsSigned(insn_t insn) {
            uint32_t immi = ParseImmiAsUnsigned(insn);
            return (immi & 0b00000000'00000000'00001000'00000000) != 0
                ? immi | 0b11111111'11111111'11110000'00000000
                : immi;
        }

        static insn_t ParseImmiAsUnsigned(insn_t insn) {
            return (insn & Immi11Mask) >> Immi11Shift;
        }

        static insn_t ParseImmsAsSigned(insn_t insn) {
            uint32_t imms = ParseImmsAsUnsigned(insn);
            return (imms & 0b00000000'00000000'00001000'00000000) != 0
                ? imms | 0b11111111'11111111'11110000'00000000
                : imms;
        }

        static insn_t ParseImmsAsUnsigned(insn_t insn) {
            uint32_t imm4  = (insn & Imms4Mask) >> Imms4Shift;
            uint32_t imm11 = (insn & Imms11Mask) >> Imms11Shift;
            return imm4 | imm11;
        }

        static insn_t ParseImmbAsSigned(insn_t insn) {
            uint32_t immb = ParseImmbAsUnsigned(insn);
            return (immb & 0b00000000'00000000'00010000'00000000) != 0
                ? immb | 0b11111111'11111111'11100000'00000000
                : immb;
        }

        static insn_t ParseImmbAsUnsigned(insn_t insn) {
            insn_t imm4  = (insn & Immb4Mask) >> Immb4Shift;
            insn_t imm10 = (insn & Immb10Mask) >> Immb10Shift;
            insn_t imm11 = (insn & Immb11Mask) << Immb11Shift;
            insn_t imm12 = (insn & Immb12Mask) >> Immb12Shift;
            return imm4 | imm10 | imm11 | imm12;
        }

        static insn_t ParseImmuAsSigned(insn_t insn) {
            return ParseImmuAsUnsigned(insn);
        }

        static insn_t ParseImmuAsUnsigned(insn_t insn) {
            return (insn & Immu31Mask) >> Immu31Shift;
        }

        static insn_t ParseImmjAsSigned(insn_t insn) {
            uint32_t immj = ParseImmjAsUnsigned(insn);
            return (immj & 0b00000000'00010000'00000000'00000000) != 0
                ? immj | 0b11111111'11100000'00000000'00000000
                : immj;
        }

        static insn_t ParseImmjAsUnsigned(insn_t insn) {
            insn_t imm10 = (insn & Immj10Mask) >> Immj10Shift;
            insn_t imm11 = (insn & Immj11Mask) >> Immj11Shift;
            insn_t imm19 = (insn & Immj19Mask) >> Immj19Shift;
            insn_t imm20 = (insn & Immj20Mask) >> Immj20Shift;
            return imm10 | imm11 | imm19 | imm20;
        }
    };

    class Descriptor {
    public:
        uint64_t opcode;
        uint64_t length;

        insn_t mask;
        insn_t match;
        function<bool(insn_t, Descriptor&)> matcher;    

        uint64_t attributes;
    };

    class Matcher {
    public:
        static bool Match(insn_t insn, Descriptor &descriptor) {
            return (insn & descriptor.mask) == descriptor.match;
        }
    };

    array<Descriptor, 65> descriptors = {
        Opcode::Lui,    32, Mask::Lui,    Match::Lui,    Matcher::Match, (Attribute::Rd  | Attribute::Immu | Attribute::Signed),
        Opcode::Auipc,  32, Mask::Auipc,  Match::Auipc,  Matcher::Match, (Attribute::Rd  | Attribute::Immu | Attribute::Signed),
        Opcode::Jal,    32, Mask::Jal,    Match::Jal,    Matcher::Match, (Attribute::Rd  | Attribute::Immj | Attribute::Signed),
        Opcode::Jalr,   32, Mask::Jalr,   Match::Jalr,   Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Immi | Attribute::Signed),
        Opcode::Beq,    32, Mask::Beq,    Match::Beq,    Matcher::Match, (Attribute::Rs1 | Attribute::Rs2  | Attribute::Immb | Attribute::Signed),
        Opcode::Bne,    32, Mask::Bne,    Match::Bne,    Matcher::Match, (Attribute::Rs1 | Attribute::Rs2  | Attribute::Immb | Attribute::Signed),
        Opcode::Blt,    32, Mask::Blt,    Match::Blt,    Matcher::Match, (Attribute::Rs1 | Attribute::Rs2  | Attribute::Immb | Attribute::Signed),
        Opcode::Bge,    32, Mask::Bge,    Match::Bge,    Matcher::Match, (Attribute::Rs1 | Attribute::Rs2  | Attribute::Immb | Attribute::Signed),
        Opcode::Bltu,   32, Mask::Bltu,   Match::Bltu,   Matcher::Match, (Attribute::Rs1 | Attribute::Rs2  | Attribute::Immb | Attribute::Signed),
        Opcode::Bgeu,   32, Mask::Bgeu,   Match::Bgeu,   Matcher::Match, (Attribute::Rs1 | Attribute::Rs2  | Attribute::Immb | Attribute::Signed),
        Opcode::Lb,     32, Mask::Lb,     Match::Lb,     Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Immi | Attribute::Signed),
        Opcode::Lh,     32, Mask::Lh,     Match::Lh,     Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Immi | Attribute::Signed),
        Opcode::Lw,     32, Mask::Lw,     Match::Lw,     Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Immi | Attribute::Signed),
        Opcode::Ld,     32, Mask::Ld,     Match::Ld,     Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Immi | Attribute::Signed),
        Opcode::Lbu,    32, Mask::Lbu,    Match::Lbu,    Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Immi | Attribute::Signed),
        Opcode::Lhu,    32, Mask::Lhu,    Match::Lhu,    Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Immi | Attribute::Signed),
        Opcode::Lwu,    32, Mask::Lwu,    Match::Lwu,    Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Immi | Attribute::Signed),
        Opcode::Sb,     32, Mask::Sb,     Match::Sb,     Matcher::Match, (Attribute::Rs1 | Attribute::Rs2  | Attribute::Imms | Attribute::Signed),
        Opcode::Sh,     32, Mask::Sh,     Match::Sh,     Matcher::Match, (Attribute::Rs1 | Attribute::Rs2  | Attribute::Imms | Attribute::Signed),
        Opcode::Sw,     32, Mask::Sw,     Match::Sw,     Matcher::Match, (Attribute::Rs1 | Attribute::Rs2  | Attribute::Imms | Attribute::Signed),
        Opcode::Sd,     32, Mask::Sd,     Match::Sd,     Matcher::Match, (Attribute::Rs1 | Attribute::Rs2  | Attribute::Imms | Attribute::Signed),
        Opcode::Add,    32, Mask::Add,    Match::Add,    Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Rs2),
        Opcode::Addw,   32, Mask::Addw,   Match::Addw,   Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Rs2),
        Opcode::Addi,   32, Mask::Addi,   Match::Addi,   Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Immi | Attribute::Signed),
        Opcode::Addiw,  32, Mask::Addiw,  Match::Addiw,  Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Immi | Attribute::Signed),
        Opcode::Sub,    32, Mask::Sub,    Match::Sub,    Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Rs2),
        Opcode::Subw,   32, Mask::Subw,   Match::Subw,   Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Rs2),
        Opcode::Slt,    32, Mask::Slt,    Match::Slt,    Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Rs2),
        Opcode::Sltu,   32, Mask::Sltu,   Match::Sltu,   Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Rs2),
        Opcode::Slti,   32, Mask::Slti,   Match::Slti,   Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Immi | Attribute::Signed),
        Opcode::Sltiu,  32, Mask::Sltiu,  Match::Sltiu,  Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Immi),
        Opcode::Xor,    32, Mask::Xor,    Match::Xor,    Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Rs2),
        Opcode::Xori,   32, Mask::Xori,   Match::Xori,   Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Immi),
        Opcode::Or,     32, Mask::Or,     Match::Or,     Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Rs2),
        Opcode::Ori,    32, Mask::Ori,    Match::Ori,    Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Immi),
        Opcode::And,    32, Mask::And,    Match::And,    Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Rs2),
        Opcode::Andi,   32, Mask::Andi,   Match::Andi,   Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Immi),
        Opcode::Sll,    32, Mask::Sll,    Match::Sll,    Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Rs2),
        Opcode::Sllw,   32, Mask::Sllw,   Match::Sllw,   Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Rs2),
        Opcode::Slli,   32, Mask::Slli,   Match::Slli,   Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Shamt6),
        Opcode::Slliw,  32, Mask::Slliw,  Match::Slliw,  Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Shamt5),
        Opcode::Srl,    32, Mask::Srl,    Match::Srl,    Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Rs2),
        Opcode::Srlw,   32, Mask::Srlw,   Match::Srlw,   Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Rs2),
        Opcode::Srli,   32, Mask::Srli,   Match::Srli,   Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Shamt6),
        Opcode::Srliw,  32, Mask::Srliw,  Match::Srliw,  Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Shamt5),
        Opcode::Sra,    32, Mask::Sra,    Match::Sra,    Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Rs2),
        Opcode::Sraw,   32, Mask::Sraw,   Match::Sraw,   Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Rs2),
        Opcode::Srai,   32, Mask::Srai,   Match::Srai,   Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Shamt6),
        Opcode::Sraiw,  32, Mask::Sraiw,  Match::Sraiw,  Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Shamt5),
        Opcode::Mul,    32, Mask::Mul,    Match::Mul,    Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Rs2),
        Opcode::Mulw,   32, Mask::Mulw,   Match::Mulw,   Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Rs2),
        Opcode::Mulh,   32, Mask::Mulh,   Match::Mulh,   Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Rs2),
        Opcode::Mulhsu, 32, Mask::Mulhsu, Match::Mulhsu, Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Rs2),
        Opcode::Mulhu,  32, Mask::Mulhu,  Match::Mulhu,  Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Rs2),
        Opcode::Div,    32, Mask::Div,    Match::Div,    Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Rs2),
        Opcode::Divw,   32, Mask::Divw,   Match::Divw,   Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Rs2),
        Opcode::Divu,   32, Mask::Divu,   Match::Divu,   Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Rs2),
        Opcode::Divuw,  32, Mask::Divuw,  Match::Divuw,  Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Rs2),
        Opcode::Rem,    32, Mask::Rem,    Match::Rem,    Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Rs2),
        Opcode::Remw,   32, Mask::Remw,   Match::Remw,   Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Rs2),
        Opcode::Remu,   32, Mask::Remu,   Match::Remu,   Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Rs2),
        Opcode::Remuw,  32, Mask::Remuw,  Match::Remuw,  Matcher::Match, (Attribute::Rd  | Attribute::Rs1  | Attribute::Rs2),
        Opcode::Pause,  32, Mask::Pause,  Match::Pause,  Matcher::Match, (Attribute::Empty),
        Opcode::Ecall,  32, Mask::Ecall,  Match::Ecall,  Matcher::Match, (Attribute::Empty),
        Opcode::Ebreak, 32, Mask::Ebreak, Match::Ebreak, Matcher::Match, (Attribute::Empty),
    };

    }

TargetContext TargetContext::Create(TargetContextParameter &parameter) {
    TargetContext newTargetContext;
    newTargetContext._pc = parameter.GetPc();
    newTargetContext._insn = parameter.GetInstruction();
    newTargetContext._gpr = parameter.GetGpRegister();

    insn::Descriptor descriptor;
    for (auto &i : insn::descriptors) {
        if (i.matcher(newTargetContext._insn, i)) {
            descriptor = i;
            break;
        }   
    }

    newTargetContext._opcode = descriptor.opcode;
    newTargetContext._length = descriptor.length;

    if ((descriptor.attributes & insn::Attribute::Rd) != 0) {
        newTargetContext._rd = insn::Parser::ParseRd(newTargetContext._insn);
    }
    if ((descriptor.attributes & insn::Attribute::Rs1) != 0) {
        newTargetContext._rs1 = insn::Parser::ParseRs1(newTargetContext._insn);
    }
    if ((descriptor.attributes & insn::Attribute::Rs2) != 0) {
        newTargetContext._rs2 = insn::Parser::ParseRs2(newTargetContext._insn);
    }

    uint64_t shamt = 
        (descriptor.attributes & insn::Attribute::Shamt5) |
        (descriptor.attributes & insn::Attribute::Shamt6);

    switch (shamt) {
    case insn::Attribute::Shamt5:
        newTargetContext._shamt = insn::Parser::ParseShamt5(newTargetContext._insn);
        break;
    case insn::Attribute::Shamt6:
        newTargetContext._shamt = insn::Parser::ParseShamt6(newTargetContext._insn);
        break;
    }

    uint64_t imm =
        (descriptor.attributes & insn::Attribute::Immi) |
        (descriptor.attributes & insn::Attribute::Imms) |
        (descriptor.attributes & insn::Attribute::Immb) |
        (descriptor.attributes & insn::Attribute::Immu) |
        (descriptor.attributes & insn::Attribute::Immj);

    switch (imm) {
    case insn::Attribute::Immi:
        newTargetContext._imm = (descriptor.attributes & insn::Attribute::Signed) 
            ? insn::Parser::ParseImmiAsSigned(newTargetContext._insn)
            : insn::Parser::ParseImmiAsUnsigned(newTargetContext._insn);
        break;
    case insn::Attribute::Imms:
        newTargetContext._imm = (descriptor.attributes & insn::Attribute::Signed) 
            ? insn::Parser::ParseImmsAsSigned(newTargetContext._insn)
            : insn::Parser::ParseImmsAsUnsigned(newTargetContext._insn);
        break;
    case insn::Attribute::Immb:
        newTargetContext._imm = (descriptor.attributes & insn::Attribute::Signed) 
            ? insn::Parser::ParseImmbAsSigned(newTargetContext._insn)
            : insn::Parser::ParseImmbAsUnsigned(newTargetContext._insn);
        break;
    case insn::Attribute::Immu:
        newTargetContext._imm = (descriptor.attributes & insn::Attribute::Signed) 
            ? insn::Parser::ParseImmuAsSigned(newTargetContext._insn)
            : insn::Parser::ParseImmuAsUnsigned(newTargetContext._insn);
        break;
    case insn::Attribute::Immj:
        newTargetContext._imm = (descriptor.attributes & insn::Attribute::Signed) 
            ? insn::Parser::ParseImmjAsSigned(newTargetContext._insn)
            : insn::Parser::ParseImmjAsUnsigned(newTargetContext._insn);
        break;
    }

    return newTargetContext;
}

addr_t TargetContext::GetPc() const {
    return _pc;
}

insn_t TargetContext::GetInstruction() const {
    return _insn;
}

uint64_t TargetContext::GetOpcode() const {
    return _opcode;
}

uint64_t TargetContext::GetLength() const {
    return _length;
}

insn_t TargetContext::GetRdType() const {
    return _rd;
}

insn_t TargetContext::GetRs1Type() const {
    return _rs1;
}

insn_t TargetContext::GetRs2Type() const {
    return _rs2;
}

Value TargetContext::GetImmValue() const {
    return Value(_imm);
}

Value TargetContext::GetRdValue() const {
    return Value(_gpr[_rd]);
}

Value TargetContext::GetRs1Value() const {
    return Value(_gpr[_rs1]);
}

Value TargetContext::GetRs2Value() const {
    return Value(_gpr[_rs2]);
}

Value TargetContext::GetRegValue(uint64_t _reg) const {
    return Value(_gpr[_reg]);
}

Value TargetContext::GetShamtValue() const {
    return Value(_shamt);
}

}