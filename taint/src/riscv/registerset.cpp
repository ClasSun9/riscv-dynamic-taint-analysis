# include "registerset.hpp"
# include "specification.hpp"

registerset registerset::fill(std::array<xlen_t, 32> regs) {
    _regs = regs;
}

xlen_t registerset::operator[](insn_t id) {
    return _regs[id];
}

xlen_t registerset::zero() {
    return _regs[gpregister::zero_];
}

xlen_t registerset::ra() {
    return _regs[gpregister::ra_];
}

xlen_t registerset::sp() {
    return _regs[gpregister::sp_];
}

xlen_t registerset::gp() {
    return _regs[gpregister::gp_];
}

xlen_t registerset::tp() {
    return _regs[gpregister::tp_];
}

xlen_t registerset::t0() {
    return _regs[gpregister::t0_];
}

xlen_t registerset::t1() {
    return _regs[gpregister::t1_];
}

xlen_t registerset::t2() {
    return _regs[gpregister::t2_];
}

xlen_t registerset::s0() {
    return _regs[gpregister::s0_];
}

xlen_t registerset::s1() {
    return _regs[gpregister::s1_];
}

xlen_t registerset::a0() {
    return _regs[gpregister::a0_];
}

xlen_t registerset::a1() {
    return _regs[gpregister::a1_];
}

xlen_t registerset::a2() {
    return _regs[gpregister::a2_];
}

xlen_t registerset::a3() {
    return _regs[gpregister::a3_];
}

xlen_t registerset::a4() {
    return _regs[gpregister::a4_];
}

xlen_t registerset::a5() {
    return _regs[gpregister::a5_];
}

xlen_t registerset::a6() {
    return _regs[gpregister::a6_];
}

xlen_t registerset::a7() {
    return _regs[gpregister::a7_];
}

xlen_t registerset::s2() {
    return _regs[gpregister::s2_];
}

xlen_t registerset::s3() {
    return _regs[gpregister::s3_];
}

xlen_t registerset::s4() {
    return _regs[gpregister::s4_];
}

xlen_t registerset::s5() {
    return _regs[gpregister::s5_];
}

xlen_t registerset::s6() {
    return _regs[gpregister::s6_];
}

xlen_t registerset::s7() {
    return _regs[gpregister::s7_];
}

xlen_t registerset::s8() {
    return _regs[gpregister::s8_];
}

xlen_t registerset::s9() {
    return _regs[gpregister::s9_];
}

xlen_t registerset::s10() {
    return _regs[gpregister::s10_];
}

xlen_t registerset::s11() {
    return _regs[gpregister::s11_];
}

xlen_t registerset::t3() {
    return _regs[gpregister::t3_];
}

xlen_t registerset::t4() {
    return _regs[gpregister::t4_];
}

xlen_t registerset::t5() {
    return _regs[gpregister::t5_];
}

xlen_t registerset::t6() {
    return _regs[gpregister::t6_];
}