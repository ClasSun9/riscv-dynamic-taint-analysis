# ifndef _RISCV__TRACER_HPP_
# define _RISCV__TRACER_HPP_

# include "types.hpp"
# include <sys/types.h>

namespace riscv {

class tracer {
private:
    pid_t _pid;
    bool _is_open;

public:
    bool open(const char *path);
    bool close();
    bool is_open();

    
};

}

# endif