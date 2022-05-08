# include "Target.hpp"

# include "Opcode.hpp"
# include "TargetContextParameter.hpp"
# include <unistd.h>    
# include <sys/wait.h>
# include <sys/ptrace.h>

using std::array;
using std::string;

namespace riscv {

TargetContext Target::CreateContext() {
    array<xlen_t, 32> regs;
    array<xlen_t, 2> iovec = { reinterpret_cast<addr_t>(regs.data()), sizeof(xlen_t) * regs.size() };
    ptrace(PTRACE_GETREGSET, _targetId, 1, iovec.data());

    addr_t pc = regs[0];
    insn_t insn = ptrace(PTRACE_PEEKTEXT, _targetId, pc, 0);

    regs[0] = 0;

    TargetContextParameter parameter;
    parameter 
        .SetPc(pc)
        .SetInstruction(insn)
        .SetGpRegister(regs);

    return TargetContext::Create(parameter);
}

bool Target::IsRunning() {
    return _isRunning;
}

void Target::Run(string &path) {
    if (IsRunning()) {
        return;
    }

    _targetId = fork();
    if (_targetId < 0) {
        return;
    }
    if (_targetId == 0) {
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        execvpe(path.c_str(), NULL, NULL);
    } else {
        _isRunning = true;
        waitpid(_targetId, NULL, 0);
        ptrace(PTRACE_SETOPTIONS, _targetId, 0, PTRACE_O_EXITKILL);
    }
}

void Target::RunTo(addr_t addr) {
    if(!IsRunning()) {
        return;
    }

    insn_t peek[2] = { 0 };
    *reinterpret_cast<uint64_t*>(peek) = ptrace(PTRACE_PEEKTEXT, _targetId, addr, 0);
    insn_t poke[2] = { 0x100073, peek[1] };
    ptrace(PTRACE_POKETEXT, _targetId, addr, *reinterpret_cast<uint64_t*>(poke));
    ptrace(PTRACE_CONT, _targetId, 0, 0);
    waitpid(_targetId, NULL, 0);
    poke[0] = peek[0];
    ptrace(PTRACE_POKETEXT, _targetId, addr, *reinterpret_cast<uint64_t*>(poke));
    _context = CreateContext();
}

void Target::RunOneStep() {
    if (!IsRunning()) {
        return;
    }

    addr_t to = 0;
    switch (_context.GetOpcode()) {
    case Opcode::Jal: {
        int32_t imm = _context.GetImmValue().AsSigned().As32();
        to = _context.GetPc() + imm;
        break;
    }
    case Opcode::Jalr: {
        uint64_t rs1 = _context.GetRs1Value().AsUnsigned().As64();
        int32_t imm = _context.GetImmValue().AsSigned().As32();
        to = rs1 + imm;
        break;
    }
    case Opcode::Beq: {
        int64_t rs1 = _context.GetRs1Value().AsSigned().As64();
        int64_t rs2 = _context.GetRs2Value().AsSigned().As64();
        int32_t imm = _context.GetImmValue().AsSigned().As32();
        to = _context.GetPc() + (rs1 == rs2 ? imm : 4);
        break;
    }
    case Opcode::Bne: {
        int64_t rs1 = _context.GetRs1Value().AsSigned().As64();
        int64_t rs2 = _context.GetRs2Value().AsSigned().As64();
        int32_t imm = _context.GetImmValue().AsSigned().As32();
        to = _context.GetPc() + (rs1 != rs2 ? imm : 4);
        break;
    }
    case Opcode::Blt: {
        int64_t rs1 = _context.GetRs1Value().AsSigned().As64();
        int64_t rs2 = _context.GetRs2Value().AsSigned().As64();
        int32_t imm = _context.GetImmValue().AsSigned().As32();
        to = _context.GetPc() + (rs1 < rs2 ? imm : 4);
        break;
    }
    case Opcode::Bge: {
        int64_t rs1 = _context.GetRs1Value().AsSigned().As64();
        int64_t rs2 = _context.GetRs2Value().AsSigned().As64();
        int32_t imm = _context.GetImmValue().AsSigned().As32();
        to = _context.GetPc() + (rs1 > rs2 ? imm : 4);
        break;
    }
    case Opcode::Bltu: {
        uint64_t rs1 = _context.GetRs1Value().AsUnsigned().As64();
        uint64_t rs2 = _context.GetRs2Value().AsUnsigned().As64();
        int32_t imm = _context.GetImmValue().AsSigned().As32();
        to = _context.GetPc() + (rs1 < rs2 ? imm : 4);
        break;
    }
    case Opcode::Bgeu: {
        uint64_t rs1 = _context.GetRs1Value().AsUnsigned().As64();
        uint64_t rs2 = _context.GetRs2Value().AsUnsigned().As64();
        int32_t imm = _context.GetImmValue().AsSigned().As32();
        to = _context.GetPc() + (rs1 > rs2 ? imm : 4);
        break;
    }
    default:
        to = _context.GetPc() + 4;
    }
    RunTo(to);
}

void Target::Exit() {
    if (!IsRunning()) {
        return;
    }
    if (!kill(_targetId, SIGKILL)) {
        _isRunning = false;
    }
}


TargetContext Target::GetContext() {
    return _context;
}

Target::Target() : 
    _targetId(0), 
    _isRunning(false) {
}

}