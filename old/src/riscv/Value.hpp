# ifndef _RISCV__VALUE_HPP_
# define _RISCV__VALUE_HPP_

# include <cstdint>

namespace riscv {

class SignedValue {
private:
    int64_t _value;

public:
    int8_t As8();
    int16_t As16();
    int32_t As32();
    int64_t As64();

public:
    SignedValue(int64_t value);
};

class UnsignedValue {
private:
    uint64_t _value;

public:
    uint8_t As8();
    uint16_t As16();
    uint32_t As32();
    uint64_t As64();

public:
    UnsignedValue(uint64_t value);
};

class Value {
private:
    uint64_t _value;

public:
    SignedValue AsSigned();
    UnsignedValue AsUnsigned();

public:
    Value(uint64_t value);
};

}

# endif