#include <gtest/gtest.h>
#include "long_number.hpp"

using namespace ypa;  // замените на ваше пространство имен

class LongNumberTests : public testing::Test {
public:
    ypa::LongNumber zero = ypa::LongNumber("0");
    ypa::LongNumber one = ypa::LongNumber("1");
    ypa::LongNumber one_neg = ypa::LongNumber("-1");
    ypa::LongNumber two = ypa::LongNumber("2");
    ypa::LongNumber two_neg = ypa::LongNumber("-2");
    ypa::LongNumber three = ypa::LongNumber("3");
    ypa::LongNumber three_neg = ypa::LongNumber("-3");
    ypa::LongNumber four = ypa::LongNumber("4");
    ypa::LongNumber four_neg = ypa::LongNumber("-4");
    ypa::LongNumber five = ypa::LongNumber("5");
    ypa::LongNumber five_neg = ypa::LongNumber("-5");
    ypa::LongNumber six = ypa::LongNumber("6");
    ypa::LongNumber six_neg = ypa::LongNumber("-6");
    ypa::LongNumber seven = ypa::LongNumber("7");
    ypa::LongNumber seven_neg = ypa::LongNumber("-7");
    ypa::LongNumber eight = ypa::LongNumber("8");
    ypa::LongNumber eight_neg = ypa::LongNumber("-8");
    ypa::LongNumber nine = ypa::LongNumber("9");
    ypa::LongNumber nine_neg = ypa::LongNumber("-9");
    ypa::LongNumber ten = ypa::LongNumber("10");
    ypa::LongNumber ten_neg = ypa::LongNumber("-10");
    ypa::LongNumber eleven = ypa::LongNumber("11");
    ypa::LongNumber twelve = ypa::LongNumber("12");
    ypa::LongNumber twelve_neg = ypa::LongNumber("-12");
    ypa::LongNumber fifteen = ypa::LongNumber("15");
    ypa::LongNumber fifteen_neg = ypa::LongNumber("-15");
    ypa::LongNumber twenty = ypa::LongNumber("20");
    ypa::LongNumber twenty_neg = ypa::LongNumber("-20");
    ypa::LongNumber twenty_five = ypa::LongNumber("25");
    ypa::LongNumber twenty_five_neg = ypa::LongNumber("-25");
    ypa::LongNumber thirty = ypa::LongNumber("30");
    ypa::LongNumber thirty_neg = ypa::LongNumber("-30");
    ypa::LongNumber fifty = ypa::LongNumber("50");
    ypa::LongNumber fifty_neg = ypa::LongNumber("-50");
    ypa::LongNumber hundred = ypa::LongNumber("100");
    ypa::LongNumber hundred_neg = ypa::LongNumber("-100");

    ypa::LongNumber num123 = ypa::LongNumber("123");
    ypa::LongNumber num123_neg = ypa::LongNumber("-123");
    ypa::LongNumber num456 = ypa::LongNumber("456");
    ypa::LongNumber num456_neg = ypa::LongNumber("-456");
    ypa::LongNumber num789 = ypa::LongNumber("789");
    ypa::LongNumber num789_neg = ypa::LongNumber("-789");
    ypa::LongNumber num1001 = ypa::LongNumber("1001");
    ypa::LongNumber num1001_neg = ypa::LongNumber("-1001");
    ypa::LongNumber num12345 = ypa::LongNumber("12345");
    ypa::LongNumber num12345_neg = ypa::LongNumber("-12345");
    ypa::LongNumber num99999 = ypa::LongNumber("99999");
    ypa::LongNumber num99999_neg = ypa::LongNumber("-99999");
    ypa::LongNumber num333 = ypa::LongNumber("333");
    ypa::LongNumber num333_neg = ypa::LongNumber("-333");
    ypa::LongNumber num579 = ypa::LongNumber("579");
    ypa::LongNumber num579_neg = ypa::LongNumber("-579");
    ypa::LongNumber num56088 = ypa::LongNumber("56088");
    ypa::LongNumber num97047 = ypa::LongNumber("97047");
    ypa::LongNumber num15241578750190521 = ypa::LongNumber("15241578750190521");
    ypa::LongNumber div1 = ypa::LongNumber("1122");
};

//сравнение
TEST_F(LongNumberTests, EqualityTest) {
    EXPECT_TRUE(one == ypa::LongNumber("1"));
    EXPECT_TRUE(one_neg == ypa::LongNumber("-1"));
    EXPECT_FALSE(one == one_neg);
    EXPECT_TRUE(num123 == ypa::LongNumber("123"));
    EXPECT_FALSE(num123 == num456);
}

TEST_F(LongNumberTests, InequalityTest) {
    EXPECT_TRUE(one != one_neg);
    EXPECT_TRUE(num123 != num456);
    EXPECT_FALSE(one != ypa::LongNumber("1"));
    EXPECT_FALSE(one_neg != ypa::LongNumber("-1"));
}

TEST_F(LongNumberTests, GreaterThanTest) {
    //+
    EXPECT_TRUE(five > three);
    EXPECT_TRUE(hundred > fifty);
    EXPECT_TRUE(num456 > num123);
    EXPECT_FALSE(three > five);
    
    //-
    EXPECT_TRUE(three_neg > five_neg);  // -3 > -5
    EXPECT_TRUE(five_neg > ten_neg);    // -5 > -10
    EXPECT_FALSE(five_neg > three_neg); // -5 > -3
    
    //+ -
    EXPECT_TRUE(one > one_neg);         // 1 > -1
    EXPECT_TRUE(zero > one_neg);        // 0 > -1
    EXPECT_FALSE(one_neg > one);        // -1 > 1 
    EXPECT_FALSE(one_neg > zero);       // -1 > 0 
}

TEST_F(LongNumberTests, LessThanTest) {
    //+
    EXPECT_TRUE(three < five);
    EXPECT_TRUE(fifty < hundred);
    EXPECT_TRUE(num123 < num456);
    EXPECT_FALSE(five < three);
    
    //-
    EXPECT_TRUE(five_neg < three_neg);  // -5 < -3
    EXPECT_TRUE(ten_neg < five_neg);    // -10 < -5
    EXPECT_FALSE(three_neg < five_neg); // -3 < -5
    
    //+ -
    EXPECT_TRUE(one_neg < one);         // -1 < 1
    EXPECT_TRUE(one_neg < zero);        // -1 < 0
    EXPECT_FALSE(one < one_neg);        // 1 < -1 
    EXPECT_FALSE(zero < one_neg);       // 0 < -1 
}

//сложение
TEST_F(LongNumberTests, AdditionTest) {
    //обычное
    EXPECT_EQ(eight, three + five);           // 3 + 5 = 8
    EXPECT_EQ(twelve, five + seven);          // 5 + 7 = 12
    EXPECT_EQ(twenty_five, ten + fifteen);    // 10 + 15 = 25
    EXPECT_EQ(hundred, fifty + fifty);        // 50 + 50 = 100
    
    //ноль
    EXPECT_EQ(five, five + zero);
    EXPECT_EQ(five_neg, five_neg + zero);
    
    //-
    EXPECT_EQ(eight_neg, three_neg + five_neg);     // -3 + -5 = -8
    EXPECT_EQ(twelve_neg, five_neg + seven_neg);    // -5 + -7 = -12
    EXPECT_EQ(twenty_five_neg, ten_neg + fifteen_neg); // -10 + -15 = -25
    
    //разное
    EXPECT_EQ(two, five + three_neg);          // 5 + -3 = 2
    EXPECT_EQ(two_neg, three + five_neg);      // 3 + -5 = -2
    EXPECT_EQ(five, eight + three_neg);        // 8 + -3 = 5
    EXPECT_EQ(five_neg, three + eight_neg);    // 3 + -8 = -5
    
    //ещё 
    EXPECT_EQ(num579, num123 + num456);        // 123 + 456 = 579
    EXPECT_EQ(num579_neg, num123_neg + num456_neg); // -123 + -456 = -579
    EXPECT_EQ(num333, num456 + num123_neg);    // 456 + -123 = 333
    EXPECT_EQ(num333_neg, num123 + num456_neg); // 123 + -456 = -333
}

//вычитание
TEST_F(LongNumberTests, SubtractionTest) {
    //обычное
    EXPECT_EQ(two, five - three);           // 5 - 3 = 2
    EXPECT_EQ(five, eight - three);         // 8 - 3 = 5
    EXPECT_EQ(fifty, hundred - fifty);      // 100 - 50 = 50
    
    //ноль
    EXPECT_EQ(five, five - zero);
    EXPECT_EQ(five_neg, five_neg - zero);
    
    //-
    EXPECT_EQ(two_neg, five_neg - three_neg);    // -5 - -3 = -2
    EXPECT_EQ(five, three_neg - eight_neg);      // -3 - -8 = 5
    EXPECT_EQ(three, five_neg - eight_neg);      // -5 - -8 = 3
    
    //знаки
    EXPECT_EQ(eight, five - three_neg);          // 5 - -3 = 8
    EXPECT_EQ(eight_neg, five_neg - three);      // -5 - 3 = -8
    EXPECT_EQ(two, three_neg - five_neg);        // -3 - -5 = 2
    
    //разное
    EXPECT_EQ(num333, num456 - num123);          // 456 - 123 = 333
    EXPECT_EQ(num333_neg, num123 - num456);      // 123 - 456 = -333
    EXPECT_EQ(num579, num123 - num456_neg);      // 123 - -456 = 579
    EXPECT_EQ(num579_neg, num123_neg - num456);  // -123 - 456 = -579
}

// умножение
TEST_F(LongNumberTests, MultiplicationTest) {
    //обычное
    EXPECT_EQ(fifteen, three * five);          // 3 * 5 = 15
    EXPECT_EQ(twenty, four * five);            // 4 * 5 = 20
    EXPECT_EQ(twenty_five, five * five);       // 5 * 5 = 25
    EXPECT_EQ(thirty, five * six);             // 5 * 6 = 30
    EXPECT_EQ(five, five * one);
    EXPECT_EQ(five_neg, five_neg * one);
    
    //-
    EXPECT_EQ(fifteen, three_neg * five_neg);      // -3 * -5 = 15
    EXPECT_EQ(fifteen_neg, three_neg * five);      // -3 * 5 = -15
    EXPECT_EQ(fifteen_neg, three * five_neg);      // 3 * -5 = -15
    
    //разное
    ypa::LongNumber mul1 = ypa::LongNumber("56088");
    EXPECT_EQ(mul1, num123 * num456);           // 123 * 456 = 56088
    
    ypa::LongNumber mul2 = ypa::LongNumber("97047");
    EXPECT_EQ(mul2, num123 * num789);           // 123 * 789 = 97047
    
    ypa::LongNumber mul3 = ypa::LongNumber("152399025");
    EXPECT_EQ(mul3, num12345 * num12345);       // 12345 * 12345
}

//деление
TEST_F(LongNumberTests, DivisionTest) {
    //обычное
    EXPECT_EQ(three, fifteen / five);           // 15 / 5 = 3
    EXPECT_EQ(five, twenty_five / five);        // 25 / 5 = 5
    EXPECT_EQ(two, thirty / fifteen);           // 30 / 15 = 2
    
    //1
    EXPECT_EQ(five, five / one);
    EXPECT_EQ(five_neg, five_neg / one);
    
    // -
    EXPECT_EQ(three, fifteen_neg / five_neg);   // -15 / -5 = 3
    EXPECT_EQ(three_neg, fifteen_neg / five);   // -15 / 5 = -3
    EXPECT_EQ(three_neg, fifteen / five_neg);   // 15 / -5 = -3
    
    //разное
    EXPECT_EQ(num456, num56088 / num123);       // 56088 / 123 = 456
    EXPECT_EQ(num123, num56088 / num456);       // 56088 / 456 = 123
    ypa::LongNumber div1 = ypa::LongNumber("1122");
    EXPECT_EQ(div1, num12345 / eleven);         // 12345 / 11 = 1122

}

//%
TEST_F(LongNumberTests, RemainderTest) {
    //обычн
    EXPECT_EQ(two, five % three);                // 5 % 3 = 2
    EXPECT_EQ(one, ten % three);                 // 10 % 3 = 1
    EXPECT_EQ(three, fifteen % twelve);          // 15 % 12 = 3
    EXPECT_EQ(nine, num12345 % twelve);         // 12345 % 12 = 9
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}