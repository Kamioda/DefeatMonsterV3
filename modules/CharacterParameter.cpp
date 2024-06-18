#include <iutest.hpp>
#include "CharacterParameter.hpp"

template<std::signed_integral I>
struct CharacterParameterTest : public ::iutest::Test {};
IUTEST_TYPED_TEST_CASE(CharacterParameterTest, ::iutest::Types<short, int, long, long long>);

IUTEST_TYPED_TEST(CharacterParameterTest, Constructor) {
	using CharacterParameter = kamioda::CharacterParameter<TypeParam>;
	CharacterParameter num(1, 200, 0);
	IUTEST_ASSERT_EQ(1, num);
	IUTEST_ASSERT_EQ(1, num.getRatio());
	CharacterParameter num2(199, 200, 0);
	IUTEST_ASSERT_EQ(199, num2);
	IUTEST_ASSERT_EQ(99, num2.getRatio());
	CharacterParameter num3(0, 200, 0);
	IUTEST_ASSERT_EQ(0, num3);
	IUTEST_ASSERT_EQ(0, num3.getRatio());
	CharacterParameter num4(200, 200, 0);
	IUTEST_ASSERT_EQ(200, num4);
	IUTEST_ASSERT_EQ(100, num4.getRatio());
}
