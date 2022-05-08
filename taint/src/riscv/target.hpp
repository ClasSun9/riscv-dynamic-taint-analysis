# ifndef _RISCV__TARGET_HPP_
# define _RISCV__TARGET_HPP_

# include "types.hpp"
# include "context.hpp"
# include <string>
# include <sys/types.h>

namespace riscv {

class target {
private:
    pid_t _pid;
    bool _is_running;

    context _context;

private:
    void run_to(addr_t addr);
    context create_context();

private:
    target(pid_t pid);

public:
    static target* run(std::string path, addr_t entrypoint);

    bool is_running();
    bool next();
    void exit();

    context context();
};

}

# endif