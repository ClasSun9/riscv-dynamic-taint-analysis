# include "target.hpp"
# include "specification.hpp"
# include <array>
# include <unistd.h>    
# include <sys/wait.h>
# include <sys/ptrace.h>

using std::array;
using std::string;

void target::run_to(addr_t addr) {
    insn_t peek[2] = { 0 };
    *reinterpret_cast<uint64_t*>(peek) = ptrace(PTRACE_PEEKTEXT, _pid, addr, 0);
    insn_t poke[2] = { 0x100073, peek[1] };
    ptrace(PTRACE_POKETEXT, _pid, addr, *reinterpret_cast<uint64_t*>(poke));
    ptrace(PTRACE_CONT, _pid, 0, 0);
    waitpid(_pid, NULL, 0);
    poke[0] = peek[0];
    ptrace(PTRACE_POKETEXT, _pid, addr, *reinterpret_cast<uint64_t*>(poke));
    _context = create_context();
}

context target::create_context() {
    array<xlen_t, 32> regs;
    array<xlen_t, 2> iovec = { 
        reinterpret_cast<addr_t>(regs.data()), 
        sizeof(xlen_t) * regs.size() };
    ptrace(PTRACE_GETREGSET, _pid, 1, iovec.data());
    addr_t pc = regs[0];
    insn_t raw = ptrace(PTRACE_PEEKTEXT, _pid, pc, 0);
    regs[0] = 0;
    return context(pc, instruction::decode(raw), registerset::fill(regs));
}

target* target::run(string path, addr_t entrypoint) {
    pid_t pid = fork();
    pid = fork();
    if (pid < 0) {
        return nullptr;
    }
    if (pid > 0) {
        waitpid(pid, NULL, 0);
        ptrace(PTRACE_SETOPTIONS, pid, 0, PTRACE_O_EXITKILL);
        target *target = new target(pid);
        target->_is_running = true;
        target->run_to(entrypoint);
        return target;
    }
    ptrace(PTRACE_TRACEME, 0, 0, 0);
    execvpe(path.c_str(), NULL, NULL);
    return nullptr;
}

bool target::is_running() {
    return _is_running;
}

bool target::next() {
    addr_t to = 0;
    auto insn = _context.instruction();
    auto regs = _context.registerset();
    switch (insn.opcode()) {
    case opcode::jal_: {
        break;
    }
    case opcode::jalr_: {
        break;
    }
    case opcode::beq_: {
        break;
    }
    case opcode::bne_: {
        break;
    }
    case opcode::blt_: {
        break;
    }
    case opcode::bge_: {
        break;
    }
    case opcode::bltu_: {
        break;
    }
    case opcode::bgeu_: {
        break;
    }
    default:
        to = _context.pc() + (addr_t)insn.length();
    }
    return true;
}

void target::exit() {
    if (!kill(_pid, SIGKILL)) {
        _is_running = false;
    }
}

context target::context() {
    return _context;
}