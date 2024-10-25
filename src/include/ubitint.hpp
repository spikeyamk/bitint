#include <cstdint>
#include <limits>

template<uint8_t bits> requires (bits >= 1 && bits < std::numeric_limits<size_t>::digits)
class ubitint_t {
public:
    using storage_t = std::conditional_t<
        bits < 8, uint8_t,
        std::conditional_t<
            bits < 16, uint16_t,
            std::conditional_t<
                bits < 32, uint32_t,
                uint64_t
            >
        >
    >;
    static constexpr storage_t max_value { (1 << bits) - 1 };
private:
    storage_t value : bits { 0 };
public:
    // Constructors
    constexpr ubitint_t() = default;
    constexpr ubitint_t(const storage_t val) : value{ val } {}

    // Unwrap the value (for convenience)
    constexpr storage_t unwrap() const { return value; }

    // Arithmetic Operators
    constexpr ubitint_t operator+(const ubitint_t& other) const { return ubitint_t(value + other.value); }
    constexpr ubitint_t operator-(const ubitint_t& other) const { return ubitint_t(value - other.value); }
    constexpr ubitint_t operator*(const ubitint_t& other) const { return ubitint_t(value * other.value); }
    constexpr ubitint_t operator/(const ubitint_t& other) const { return ubitint_t(value / other.value); }
    constexpr ubitint_t operator%(const ubitint_t& other) const { return ubitint_t(value % other.value); }

    // Compound Assignment Operators
    constexpr ubitint_t& operator+=(const ubitint_t& other) { value += other.value; return *this; }
    constexpr ubitint_t& operator-=(const ubitint_t& other) { value -= other.value; return *this; }
    constexpr ubitint_t& operator*=(const ubitint_t& other) { value *= other.value; return *this; }
    constexpr ubitint_t& operator/=(const ubitint_t& other) { value /= other.value; return *this; }
    constexpr ubitint_t& operator%=(const ubitint_t& other) { value %= other.value; return *this; }

    // Bitwise Operators
    constexpr ubitint_t operator&(const ubitint_t& other) const { return ubitint_t(value & other.value); }
    constexpr ubitint_t operator|(const ubitint_t& other) const { return ubitint_t(value | other.value); }
    constexpr ubitint_t operator^(const ubitint_t& other) const { return ubitint_t(value ^ other.value); }
    constexpr ubitint_t operator~() const { return ubitint_t(~value & max_value); }

    // Compound Bitwise Assignment Operators
    constexpr ubitint_t& operator&=(const ubitint_t& other) { value &= other.value; return *this; }
    constexpr ubitint_t& operator|=(const ubitint_t& other) { value |= other.value; return *this; }
    constexpr ubitint_t& operator^=(const ubitint_t& other) { value ^= other.value; return *this; }

    // Shift Operators
    constexpr ubitint_t operator<<(const uint8_t shift) const { return ubitint_t(value << shift); }
    constexpr ubitint_t operator>>(const uint8_t shift) const { return ubitint_t(value >> shift); }

    // Compound Shift Assignment Operators
    constexpr ubitint_t& operator<<=(const uint8_t shift) { value <<= shift; return *this; }
    constexpr ubitint_t& operator>>=(const uint8_t shift) { value >>= shift; return *this; }

    // Increment and Decrement Operators
    constexpr ubitint_t& operator++() { ++value; return *this; }        // Prefix
    constexpr ubitint_t operator++(int) { ubitint_t temp = *this; ++value; return temp; } // Postfix
    constexpr ubitint_t& operator--() { --value; return *this; }        // Prefix
    constexpr ubitint_t operator--(int) { ubitint_t temp = *this; --value; return temp; } // Postfix

    // Comparison Operators
    constexpr bool operator==(const ubitint_t& other) const { return value == other.value; }
    constexpr bool operator!=(const ubitint_t& other) const { return value != other.value; }
    constexpr bool operator<(const ubitint_t& other) const { return value < other.value; }
    constexpr bool operator<=(const ubitint_t& other) const { return value <= other.value; }
    constexpr bool operator>(const ubitint_t& other) const { return value > other.value; }
    constexpr bool operator>=(const ubitint_t& other) const { return value >= other.value; }

    // Stream Insertion Operator for easy output
    friend std::ostream& operator<<(std::ostream& os, const ubitint_t& obj) {
        return os << obj.value;
    }
};