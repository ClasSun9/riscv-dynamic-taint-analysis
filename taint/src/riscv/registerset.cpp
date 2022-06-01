#include <array>
#include "./registerset.hpp"

using std::array;

namespace riscv {

rlen_t registerset::get(insn_t id) {
    return _regs.at(id);
}

rlen_t registerset::operator[](insn_t id) {
    return get(id);
}

registerset::registerset() { }
registerset::registerset(array<rlen_t, 64> regs) : _regs(regs) {}

}