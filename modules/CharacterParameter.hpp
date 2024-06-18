#if !defined CHARACTER_PARAMETER_HPP
#define CHARACTER_PARAMETER_HPP
#include "Number.hpp"

namespace kamioda {
	template<std::signed_integral I>
	class CharacterParameter : public Number<I> {
	private:
		constexpr I subtractBetweenValAndMin() const noexcept {
			return Number<I>::template get<I>() - Number<I>::m_minVal;
		}
		constexpr I subtractBetweenMaxAndMin() const noexcept {
			return Number<I>::m_maxVal - Number<I>::m_minVal;
		}
		constexpr int calcRatio() const {
			return static_cast<int>((static_cast<double>(this->subtractBetweenValAndMin()) / static_cast<double>(this->subtractBetweenMaxAndMin()) + 0.5) * 100);
		}
		constexpr int getRatioImpl() const {
			return Number<I>::m_minVal == Number<I>::m_maxVal ? 0 : this->calcRatio();
		}
		constexpr bool isMin() const noexcept {
			return Number<I>::template get<I>() == Number<I>::m_minVal;
		}
		constexpr bool isMax() const noexcept {
			return Number<I>::template get<I>() == Number<I>::m_maxVal;
		}
	public:
		constexpr CharacterParameter() noexcept : Number<I>() {}
		constexpr CharacterParameter(const I& val, const I& maxVal = std::numeric_limits<I>::max(), const I& minVal = std::numeric_limits<I>::min()) noexcept : Number<I>(val, minVal, maxVal) {}
		int getRatio() const {
			const int ratio = this->getRatioImpl();
			return ratio == 0
				? !this->isMin()
				: (ratio == 100 ? (99 + this->isMax()) : ratio);
		}
	};
}
#endif
