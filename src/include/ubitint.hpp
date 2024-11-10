#pragma once

#include <iostream>
#include <cstdint>
#include <limits>
#include <type_traits>

namespace bitint {
namespace detail {
    template<uint8_t bits, bool is_signed>
    requires ((bits >= 1) && ((bits % 8) != 0) && (bits < std::numeric_limits<size_t>::digits))
    class bitint {
    public:
        using storage = std::conditional_t<
            bits < 8, std::conditional_t<is_signed, int8_t, uint8_t>,
            std::conditional_t<
                bits < 16, std::conditional_t<is_signed, int16_t, uint16_t>,
                std::conditional_t<
                    bits < 32, std::conditional_t<is_signed, int32_t, uint32_t>,
                    std::conditional_t<is_signed, int64_t, uint64_t>
                >
            >
        >;

        static constexpr storage max_value = is_signed
            ? ((1 << (bits - 1)) - 1)
            : ((1 << bits) - 1);
        static constexpr storage min_value = is_signed
            ? -(1 << (bits - 1))
            : 0;

        storage value : bits { 0 };

    public:
        constexpr bitint() = default;
        constexpr bitint(const storage val) : value{ val } {}

        constexpr storage unwrap() const { return value; }

        constexpr bitint operator+(const bitint& other) const { return bitint(value + other.value); }
        constexpr bitint operator-(const bitint& other) const { return bitint(value - other.value); }
        constexpr bitint operator*(const bitint& other) const { return bitint(value * other.value); }
        constexpr bitint operator/(const bitint& other) const { return bitint(value / other.value); }
        constexpr bitint operator%(const bitint& other) const { return bitint(value % other.value); }

        constexpr bitint& operator+=(const bitint& other) { value += other.value; return *this; }
        constexpr bitint& operator-=(const bitint& other) { value -= other.value; return *this; }
        constexpr bitint& operator*=(const bitint& other) { value *= other.value; return *this; }
        constexpr bitint& operator/=(const bitint& other) { value /= other.value; return *this; }
        constexpr bitint& operator%=(const bitint& other) { value %= other.value; return *this; }

        constexpr bitint operator&(const bitint& other) const { return bitint(value & other.value); }
        constexpr bitint operator|(const bitint& other) const { return bitint(value | other.value); }
        constexpr bitint operator^(const bitint& other) const { return bitint(value ^ other.value); }
        constexpr bitint operator~() const { return bitint(~value & max_value); }

        constexpr bitint& operator&=(const bitint& other) { value &= other.value; return *this; }
        constexpr bitint& operator|=(const bitint& other) { value |= other.value; return *this; }
        constexpr bitint& operator^=(const bitint& other) { value ^= other.value; return *this; }

        constexpr bitint operator<<(const uint8_t shift) const { return bitint(value << shift); }
        constexpr bitint operator>>(const uint8_t shift) const {
            return bitint(value >> shift);
        }

        constexpr bitint& operator<<=(const uint8_t shift) { value <<= shift; return *this; }
        constexpr bitint& operator>>=(const uint8_t shift) { value >>= shift; return *this; }

        constexpr bitint& operator++() { ++value; return *this; }
        constexpr bitint operator++(int) { bitint temp = *this; ++value; return temp; }
        constexpr bitint& operator--() { --value; return *this; }
        constexpr bitint operator--(int) { bitint temp = *this; --value; return temp; }

        constexpr bool operator==(const bitint& other) const { return value == other.value; }
        constexpr bool operator!=(const bitint& other) const { return value != other.value; }
        constexpr bool operator<(const bitint& other) const { return value < other.value; }
        constexpr bool operator<=(const bitint& other) const { return value <= other.value; }
        constexpr bool operator>(const bitint& other) const { return value > other.value; }
        constexpr bool operator>=(const bitint& other) const { return value >= other.value; }

        friend std::ostream& operator<<(std::ostream& os, const bitint& obj) {
            return os << obj.value;
        }
    };
}
    template<uint8_t bits>
    using bitint = detail::bitint<bits, true>;

    template<uint8_t bits>
    using ubitint = detail::bitint<bits, false>;
}