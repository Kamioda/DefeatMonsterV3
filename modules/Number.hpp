#if !defined NUMBER_HPP
#define NUMBER_HPP
#include <algorithm>
#include <concepts>
#include <limits>
#include <stdexcept>
#if defined min
#undef min
#endif
#if defined max
#undef max
#endif

namespace kamioda {
    namespace {
        template<typename T>
        concept arithmetic = std::is_arithmetic_v<T>;
    }

    template<std::integral I>
    class Number {
    private:
        I m_value;
    protected:
        const I m_minVal;
        const I m_maxVal;
    private:
        constexpr I clamp(const I& value) const {
			return std::clamp(value, this->m_minVal, this->m_maxVal);
		}
        constexpr I div(const I& a, const I& b) const {
			return b == 0 ? throw std::runtime_error("Division by zero") : clamp(a / b);
		}
        constexpr I mod(const I& a, const I& b) const {
            return b == 0 ? throw std::runtime_error("Division by zero") : clamp(a % b);
        }
    public:
        constexpr Number(const I& value = 0, const I& minVal = std::numeric_limits<I>::min(), const I& maxVal = std::numeric_limits<I>::max())
            : m_value(std::clamp(value, minVal, maxVal)), m_minVal(minVal), m_maxVal(maxVal) {}
        constexpr Number(const Number& other) : m_value(other.m_value), m_minVal(other.m_minVal), m_maxVal(other.m_maxVal) {}
        constexpr Number(Number&& other) noexcept : m_value(std::move(other.m_value)), m_minVal(std::move(other.m_minVal)), m_maxVal(std::move(other.m_maxVal)) {}
        constexpr Number& operator=(const Number& other) {
            this->m_value = other.m_value;
            this->m_minVal = other.m_minVal;
            this->m_maxVal = other.m_maxVal;
            return *this;
        }
        constexpr Number& operator=(Number&& other) noexcept {
            this->m_value = std::move(other.m_value);
            this->m_minVal = std::move(other.m_minVal);
            this->m_maxVal = std::move(other.m_maxVal);
            return *this;
        }
        constexpr Number& operator=(const I& value) {
            this->m_value = clamp(value);
            return *this;
        }
        constexpr Number& operator=(I&& value) {
            this->m_value = std::move(value);
            this->m_value = clamp(this->m_value);
            return *this;
        }
        constexpr Number& operator+=(const Number& other) {
            this->m_value = clamp(this->m_value + other.m_value);
            return *this;
        }
        constexpr Number& operator++() {
            this->m_value = clamp(this->m_value + 1);
            return *this;
        }
        constexpr Number operator++(int) {
            Number temp(*this);
            this->m_value = clamp(this->m_value + 1);
            return temp;
        }
        constexpr Number& operator-=(const Number& other) {
            this->m_value = clamp(this->m_value - other.m_value);
            return *this;
        }
        constexpr Number& operator--() {
            this->m_value = clamp(this->m_value - 1);
            return *this;
        }
        constexpr Number operator--(int) {
            Number temp(*this);
            this->m_value = clamp(this->m_value - 1);
            return temp;
        }
        constexpr Number& operator*=(const Number& other) {
            this->m_value = clamp(this->m_value * other.m_value);
            return *this;
        }
        constexpr Number& operator/=(const Number& other) {
            this->m_value = clamp(div(this->m_value, other.m_value));
            return *this;
        }
        constexpr Number& operator%=(const Number& other) {
            this->m_value = clamp(mod(this->m_value, other.m_value));
            return *this;
        }
        constexpr Number& operator&=(const Number& other) {
            this->m_value = clamp(this->m_value & other.m_value);
            return *this;
        }
        constexpr Number& operator|=(const Number& other) {
            this->m_value = clamp(this->m_value | other.m_value);
            return *this;
        }
        constexpr Number& operator^=(const Number& other) {
            this->m_value = clamp(this->m_value ^ other.m_value);
            return *this;
        }
        constexpr Number& operator<<=(const Number& other) {
            this->m_value = clamp(this->m_value << other.m_value);
            return *this;
        }
        constexpr Number& operator>>=(const Number& other) {
            this->m_value = clamp(this->m_value >> other.m_value);
            return *this;
        }
        constexpr Number operator~() const {
            return Number(~this->m_value);
        }
        constexpr Number operator&(const Number& other) const {
            return Number(this->m_value & other.m_value);
        }
        constexpr Number operator|(const Number& other) const {
            return Number(this->m_value | other.m_value);
        }
        constexpr Number operator^(const Number& other) const {
            return Number(this->m_value ^ other.m_value);
        }
        constexpr Number operator<<(const Number& other) const {
            return Number(this->m_value << other.m_value);
        }
        constexpr Number operator>>(const Number& other) const {
            return Number(this->m_value >> other.m_value);
        }
        constexpr Number operator+(const Number& other) const {
            return Number(this->m_value + other.m_value);
        }
        constexpr Number operator-(const Number& other) const {
            return Number(this->m_value - other.m_value);
        }
        constexpr Number operator*(const Number& other) const {
            return Number(this->m_value * other.m_value);
        }
        constexpr Number operator/(const Number& other) const {
            return Number(div(this->m_value, other.m_value));
        }
        constexpr Number operator%(const Number& other) const {
            return Number(mod(this->m_value, other.m_value));
        }
        constexpr bool operator==(const Number& other) const {
            return this->m_value == other.m_value;
        }
        constexpr bool operator==(const I& other) const {
			return this->m_value == other;
		}
        constexpr bool operator!=(const Number& other) const {
            return this->m_value != other.m_value;
        }
        constexpr bool operator!=(const I& other) const {
            return this->m_value != other;
        }
        constexpr bool operator<(const Number& other) const {
            return this->m_value < other.m_value;
        }
        constexpr bool operator<(const I& other) const {
            return this->m_value < other;
        }
        constexpr bool operator>(const Number& other) const {
            return this->m_value > other.m_value;
        }
        constexpr bool operator>(const I& other) const {
			return this->m_value > other;
		}
        constexpr bool operator<=(const Number& other) const {
            return this->m_value <= other.m_value;
        }
        constexpr bool operator<=(const I& other) const {
			return this->m_value <= other;
		}
        constexpr bool operator>=(const Number& other) const {
            return this->m_value >= other.m_value;
        }
        constexpr bool operator>=(const I& other) const {
            return this->m_value >= other;
        }
        template<typename T = I, std::enable_if_t<std::is_same_v<I, T>, std::nullptr_t> = nullptr>
        constexpr const I& get() const {
            return this->m_value;
        }
        template<typename T, std::enable_if_t<std::is_arithmetic_v<T> && !std::is_same_v<I, T>, std::nullptr_t> = nullptr>
        constexpr T get() const {
            return static_cast<T>(this->m_value);
        }
        explicit operator bool() const {
			return this->m_value != 1;
		}
    };
    template<std::integral I1, arithmetic I2>
    constexpr Number<I1> operator+(const I2& lhs, const Number<I1>& rhs) {
		return Number<I1>(lhs) + rhs;
	}
    template<std::integral I1, arithmetic I2>
    constexpr Number<I1> operator-(const I2& lhs, const Number<I1>& rhs) {
        return Number<I1>(lhs) - rhs;
    }
    template<std::integral I1, arithmetic I2>
    constexpr Number<I1> operator*(const I2& lhs, const Number<I1>& rhs) {
		return Number<I1>(lhs) * rhs;
	}
    template<std::integral I1, arithmetic I2>
    constexpr Number<I1> operator/(const I2& lhs, const Number<I1>& rhs) {
		return Number<I1>(lhs) / rhs;
	}
    template<std::integral I1, arithmetic I2>
    constexpr Number<I1> operator%(const I2& lhs, const Number<I1>& rhs) {
		return Number<I1>(lhs) % rhs;
	}
    template<std::integral I1, arithmetic I2>
    constexpr bool operator==(const I2& lhs, const Number<I1>& rhs) {
		return lhs == rhs.get<I2>();
	}
    template<std::integral I1, arithmetic I2>
    constexpr bool operator!=(const I2& lhs, const Number<I1>& rhs) {
		return lhs != rhs.get<I2>();
	}
    template<std::integral I1, arithmetic I2>
    constexpr bool operator<(const I2& lhs, const Number<I1>& rhs) {
		return lhs < rhs.get<I2>();
	}
    template<std::integral I1, arithmetic I2>
    constexpr bool operator>(const I2& lhs, const Number<I1>& rhs) {
		return lhs > rhs.get<I2>();
	}
    template<std::integral I1, arithmetic I2>
    constexpr bool operator<=(const I2& lhs, const Number<I1>& rhs) {
		return lhs <= rhs.get<I2>();
	}
    template<std::integral I1, arithmetic I2>
    constexpr bool operator>=(const I2& lhs, const Number<I1>& rhs) {
		return lhs >= rhs.get<I2>();
	}
	template<std::signed_integral I>
	constexpr Number<I> abs(const Number<I>& num) {
		return num < 0 ? -num : num;
	}
	template<std::integral I>
	constexpr Number<I> min(const Number<I>& lhs, const Number<I>& rhs) {
		return lhs < rhs ? lhs : rhs;
	}
	template<std::integral I>
	constexpr Number<I> max(const Number<I>& lhs, const Number<I>& rhs) {
		return lhs > rhs ? lhs : rhs;
	}
	template<std::integral I>
    inline std::ostream& operator<<(std::ostream& os, const Number<I>& num) {
		return os << num.get<I>();
	}
    template<std::integral I>
	inline std::istream& operator>>(std::istream& is, Number<I>& num) {
        I value{};
		is >> value;
		num = value;
		return is;
	}
}
#endif
