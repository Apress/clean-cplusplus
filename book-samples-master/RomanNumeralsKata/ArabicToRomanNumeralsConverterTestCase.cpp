#include <gtest/gtest.h>
#include <string>
#include <array>

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

struct ArabicToRomanMapping {
  unsigned int arabicNumber;
  std::string romanNumeral;
};

const std::size_t numberOfMappings { 13 };
using ArabicToRomanMappings = std::array<ArabicToRomanMapping, numberOfMappings>;

const ArabicToRomanMappings arabicToRomanMappings = { {
    { 1000, "M"  },
    {  900, "CM" },
    {  500, "D"  },
    {  400, "CD" },
    {  100, "C"  },
    {   90, "XC" },
    {   50, "L"  },
    {   40, "XL" },
    {   10, "X"  },
    {    9, "IX" },
    {    5, "V"  },
    {    4, "IV" },
    {    1, "I"  }
} };

std::string convertArabicNumberToRomanNumeral(unsigned int arabicNumber) {
  std::string romanNumeral;
  for (auto mapping : arabicToRomanMappings) {
    while (arabicNumber >= mapping.arabicNumber) {
      romanNumeral += mapping.romanNumeral;
      arabicNumber -= mapping.arabicNumber;
    }
  }
  return romanNumeral;
}

// Test code starts here...

class RomanNumeralAssert {
public:
  RomanNumeralAssert() = delete;
  explicit RomanNumeralAssert(const unsigned int arabicNumber) :
      arabicNumberToConvert(arabicNumber) { }
  void isConvertedToRomanNumeral(const std::string& expectedRomanNumeral) const {
    ASSERT_EQ(expectedRomanNumeral, convertArabicNumberToRomanNumeral(arabicNumberToConvert));
  }

private:
  const unsigned int arabicNumberToConvert;
};

RomanNumeralAssert assertThat(const unsigned int arabicNumber) {
  RomanNumeralAssert assert { arabicNumber };
  return assert;
}

TEST(ArabicToRomanNumeralsConverterTestCase, conversionOfArabicNumbersToRomanNumerals_Works) {
  assertThat(1).isConvertedToRomanNumeral("I");
  assertThat(2).isConvertedToRomanNumeral("II");
  assertThat(3).isConvertedToRomanNumeral("III");
  assertThat(4).isConvertedToRomanNumeral("IV");
  assertThat(5).isConvertedToRomanNumeral("V");
  assertThat(6).isConvertedToRomanNumeral("VI");
  assertThat(9).isConvertedToRomanNumeral("IX");
  assertThat(10).isConvertedToRomanNumeral("X");
  assertThat(20).isConvertedToRomanNumeral("XX");
  assertThat(30).isConvertedToRomanNumeral("XXX");
  assertThat(33).isConvertedToRomanNumeral("XXXIII");
  assertThat(37).isConvertedToRomanNumeral("XXXVII");
  assertThat(50).isConvertedToRomanNumeral("L");
  assertThat(99).isConvertedToRomanNumeral("XCIX");
  assertThat(100).isConvertedToRomanNumeral("C");
  assertThat(200).isConvertedToRomanNumeral("CC");
  assertThat(300).isConvertedToRomanNumeral("CCC");
  assertThat(499).isConvertedToRomanNumeral("CDXCIX");
  assertThat(500).isConvertedToRomanNumeral("D");
  assertThat(1000).isConvertedToRomanNumeral("M");
  assertThat(2000).isConvertedToRomanNumeral("MM");
  assertThat(2017).isConvertedToRomanNumeral("MMXVII");
  assertThat(3000).isConvertedToRomanNumeral("MMM");
  assertThat(3333).isConvertedToRomanNumeral("MMMCCCXXXIII");
  assertThat(3999).isConvertedToRomanNumeral("MMMCMXCIX");
}
