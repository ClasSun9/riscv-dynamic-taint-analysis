#ifndef _RISCV__TARGET_HPP_
#define _RISCV__TARGET_HPP_

#include <string>
#include <sys/types.h>
#include "./types.hpp"
#include "./targetcontext.hpp"

namespace riscv {

class target {
private:
    pid_t _pid;
    targetcontext _context;
private:
    targetcontext create_context();
public:
    targetcontext context();
    void run_until(addr_t until);
    void run_one_step();
    void exit();
public:
    target(std::string path, addr_t entrypoint);
};

}

#endif