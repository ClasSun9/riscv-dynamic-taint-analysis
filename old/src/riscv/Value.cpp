# include "Value.hpp"

namespace riscv {

int8_t SignedValue::As8() {
    return static_cast<int8_t>(_value);
}

int16_t SignedValue::As16() {
    return static_cast<int16_t>(_value);
}

int32_t SignedValue::As32() {
    return static_cast<int32_t>(_value);
}

int64_t SignedValue::As64() {
    return _value;
}

SignedValue::SignedValue(int64_t value) : _value(value) { }

uint8_t UnsignedValue::As8() {
    return static_cast<uint8_t>(_value);
}

uint16_t UnsignedValue::As16() {
    return static_cast<uint16_t>(_value);
}

uint32_t UnsignedValue::As32() {
    return static_cast<uint32_t>(_value);
}

uint64_t UnsignedValue::As64() {
    return _value;
}

UnsignedValue::UnsignedValue(uint64_t value) : _value(value) { }

SignedValue Value::AsSigned() {
    return SignedValue(static_cast<int64_t>(_value));
}

UnsignedValue Value::AsUnsigned() {
    return UnsignedValue(_value);
}

Value::Value(uint64_t value) : _value(value) { }

}