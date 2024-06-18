#include <iutest/iutest.hpp>
#include "CharacterParameter.hpp"

template<std::signed_integral I>
struct CharacterParameterTest : public ::iutest::Test {};
IUTEST_TYPED_TEST_CASE(CharacterParameterTest, ::iutest::Types<short, int, long, long long>);

IUTEST_TYPED_TEST(CharacterParameterTest, Constructor) {
	using CharacterParameter = kamioda::CharacterParameter<TypeParam>;
	CharacterParameter num(1, 0, 200);
	IUTEST_ASSERT_EQ(num, 1);
	IUTEST_ASSERT_EQ(num.getRatio(), 1);
	CharacterParameter num2(199, 0, 200);
	IUTEST_ASSERT_EQ(num2, 199);
	IUTEST_ASSERT_EQ(num2.getRatio(), 99);
	CharacterParameter num3(0, 0, 200);
	IUTEST_ASSERT_EQ(num3, 0);
	IUTEST_ASSERT_EQ(num3.getRatio(), 0);
	CharacterParameter num4(200, 0, 200);
	IUTEST_ASSERT_EQ(num4, 200);
	IUTEST_ASSERT_EQ(num4.getRatio(), 100);
}
