#include <array>
#include <unistd.h>    
#include <sys/wait.h>
#include <sys/ptrace.h>
#include "./target.hpp"
#include "./opcode.hpp"

using std::array;
using std::string;

namespace riscv {

targetcontext target::create_context() {
    array<rlen_t, 64> regs;
    array<rlen_t, 2> iovec_for_gpregs = { 
        reinterpret_cast<addr_t>(regs.data()), 
        sizeof(rlen_t) * 32 };
    array<rlen_t, 2> iovec_for_fpregs = { 
        reinterpret_cast<addr_t>(regs.data() + 32),
        sizeof(rlen_t) * 32 };
    ptrace(PTRACE_GETREGSET, _pid, 1, iovec_for_gpregs.data());
    ptrace(PTRACE_GETREGSET, _pid, 2, iovec_for_fpregs.data());
    addr_t pc = regs[0];
    insn_t raw = ptrace(PTRACE_PEEKTEXT, _pid, pc, 0);
    regs[0] = 0;
    return targetcontext(pc, instruction(raw), registerset(regs));
}

targetcontext target::context() {
    return _context;
}

void target::run_until(addr_t until) {
    insn_t peek[2] = { 0 };
    *reinterpret_cast<uint64_t*>(peek) = ptrace(PTRACE_PEEKTEXT, _pid, until, 0);
    insn_t poke[2] = { 0x100073, peek[1] };
    ptrace(PTRACE_POKETEXT, _pid, until, *reinterpret_cast<uint64_t*>(poke));
    ptrace(PTRACE_CONT, _pid, 0, 0);
    waitpid(_pid, NULL, 0);
    poke[0] = peek[0];
    ptrace(PTRACE_POKETEXT, _pid, until, *reinterpret_cast<uint64_t*>(poke));
    _context = create_context();
}

void target::run_one_step() {
    instruction insn = _context.insn();
    registerset regs = _context.regs();

    addr_t base = 0;
    addr_t offset = 0;
    switch (insn.id()) {
    case opcode::jal_:
        base = _context.pc();
        offset = insn.simm();
        break;
    case opcode::jalr_:
        base = (addr_t)regs[insn.rs1()];
        offset = insn.simm();
        break;
    case opcode::beq_:
        base = _context.pc();
        offset = (int64_t)regs[insn.rs1()] == (int64_t)regs[insn.rs2()] 
            ? insn.simm() 
            : 4;
        break;
    case opcode::bne_:
        base = _context.pc();
        offset = (int64_t)regs[insn.rs1()] == (int64_t)regs[insn.rs2()] 
            ? insn.simm() 
            : 4;
        break;
    case opcode::blt_:
        base = _context.pc();
        offset = (int64_t)regs[insn.rs1()] == (int64_t)regs[insn.rs2()] 
            ? insn.simm() 
            : 4;
        break;
    case opcode::bge_:
        base = _context.pc();
        offset = (int64_t)regs[insn.rs1()] == (int64_t)regs[insn.rs2()] 
            ? insn.simm() 
            : 4;
        break;
    case opcode::bltu_:
        base = _context.pc();
        offset = (uint64_t)regs[insn.rs1()] < (uint64_t)regs[insn.rs2()] 
            ? insn.simm() 
            : 4;
        break;
    case opcode::bgeu_:
        base = _context.pc();
        offset = (uint64_t)regs[insn.rs1()] >= (uint64_t)regs[insn.rs2()] 
            ? insn.simm()
            : 4;
        break;
    default:
        base = _context.pc();
        offset = (addr_t)insn.length();
    }
    run_until(base + offset);
}

void target::exit() {
    kill(_pid, SIGKILL);
}

target::target(string path, addr_t entrypoint) {
    pid_t pid = fork();
    pid = fork();
    if (pid < 0) {
        return;
    }
    if (pid > 0) {
        waitpid(pid, NULL, 0);
        ptrace(PTRACE_SETOPTIONS, pid, 0, PTRACE_O_EXITKILL);
        run_until(entrypoint);
    } else {
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        execvpe(path.c_str(), NULL, NULL);
    }
}

}