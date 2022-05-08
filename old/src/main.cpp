# include "riscv/Opcode.hpp"
# include "riscv/Register.hpp"
# include "riscv/Types.hpp"
# include "riscv/Target.hpp"
# include "riscv/TargetContext.hpp"
# include "riscv/Disassembler.hpp"
# include "riscv/TainterAB.hpp"
# include "riscv/TainterBB.hpp"
using namespace riscv;

# include <cstdio>
# include <string>
# include <array>
# include <memory>
# include <utility>
using std::string;
using std::array;
using std::shared_ptr;
using std::make_shared;

int main(int argc, const char *argv[], const char *envp[]) {
    if (argc < 4) {
        printf("[*] Usage : taint path begin_address end_address\n");
        return 1;
    }

    string path(argv[1]);
    addr_t beginAddr =  std::strtoull(argv[2], NULL, 16);
    addr_t endAddr = std::strtoull(argv[3], NULL, 16);

    Disassembler disas;
    TainterAB tainterAB;
    TainterBB tainterBB;

    // TestCase1 - AB
    {
        Target target;
        target.Run(path);
        target.RunTo(beginAddr);

        TargetContext context = target.GetContext();
        while (context.GetPc() <= endAddr) {
            disas.Print(context);
            tainterAB.Taint(context);
            target.RunOneStep();
            context = target.GetContext();
        }
        printf("\n");
        tainterAB.Debug();
        printf("\n");
        target.Exit();
    }
    
    // TestCase 2 - BB
    /*
    {
        Target target;
        target.Run(path);
        target.RunTo(0x100e4);

        TargetContext context = target.GetContext();
        while (context.GetPc() <= 0x1010c) {
            disas.Print(context);
            tainterBB.Taint(context);
            target.RunOneStep();
            context = target.GetContext();
        }
        tainterBB.Debug();
        target.Exit();
    }
    */

    return 0;
}