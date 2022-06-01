# ifndef _RISCV__INSTRUCTION_HPP_
# define _RISCV__INSTRUCTION_HPP_

# include <array>
# include "./types.hpp"

namespace riscv {

class instruction {
private:
    class parser;
    class matcher;
    class decoder;
    class description;
private:
    static const std::array<description, 81> descriptions;
private:
    insn_t _raw;
    insn_t _id;
    insn_t _rd;
    insn_t _rs1;
    insn_t _rs2;
    insn_t _imm;
    insn_t _shamt;
    int64_t _sign;
    int64_t _length;
public:
    insn_t raw();
    insn_t id();
    insn_t rd();
    insn_t rs1();
    insn_t rs2();
    insn_t shamt();
    int64_t  simm();
    uint64_t uimm();
    int64_t length();
public:
    instruction();
    instruction(insn_t raw);
};

}

#endif