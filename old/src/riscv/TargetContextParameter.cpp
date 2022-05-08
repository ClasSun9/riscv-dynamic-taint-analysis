# include "TargetContextParameter.hpp"

using std::array;

namespace riscv {

TargetContextParameter& TargetContextParameter::SetPc(addr_t pc) {
    _pc = pc;
    return *this;
}

TargetContextParameter& TargetContextParameter::SetInstruction(insn_t insn) {
    _insn = insn;
    return *this;
}

TargetContextParameter& TargetContextParameter::SetGpRegister(array<xlen_t, 32> gpr) {
    _gpr = gpr;
    return *this;
}

TargetContextParameter& TargetContextParameter::SetFpRegister(array<flen_t, 32> fpr) {
    _fpr = fpr;
    return *this;
}

addr_t TargetContextParameter::GetPc() {
    return _pc;
}

insn_t TargetContextParameter::GetInstruction() {
    return _insn;
}

array<xlen_t, 32> TargetContextParameter::GetGpRegister() {
    return _gpr;
}

array<flen_t, 32> TargetContextParameter::GetFpRegister() {
    return _fpr;
}

}