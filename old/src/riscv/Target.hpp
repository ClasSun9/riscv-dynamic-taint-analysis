# ifndef _RISCV__TARGET_HPP_
# define _RISCV__TARGET_HPP_

# include "Types.hpp"
# include "TargetContext.hpp"
# include <tuple>
# include <array>
# include <string>
# include <memory>
# include <cstdint>
# include <sys/types.h>

namespace riscv {

class Target {
private:
    pid_t _targetId;
    bool _isRunning;

    TargetContext _context;

private:
    TargetContext CreateContext();

public:
    bool IsRunning();
    void Run(std::string &path);
    void RunTo(addr_t addr);
    void RunOneStep();
    void Exit();

    TargetContext GetContext();

public:
    Target();
};

}

# endif