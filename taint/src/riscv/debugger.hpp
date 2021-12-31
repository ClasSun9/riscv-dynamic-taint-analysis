# ifndef _RISCV__DEBUGGER_HPP_
# define _RISCV__DEBUGGER_HPP_

# include "types.hpp"
# include <array>
# include <sys/types.h>

namespace riscv {

class debugger {
private:
    pid_t _pid;

    bool _is_open;

public:
    bool open(const char *path);
    bool close();
    bool is_open();

    addr_t get_program_counter();
    insn_t get_raw_instruction();
    void get_gpregisters(std::array<xlen_t, 32> registers);
    void get_fpregisters(std::array<flen_t, 32> registers);

};

}

# endif