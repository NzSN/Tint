// Copyright 2020 The Tint Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "src/tint/reader/wgsl/lexer.h"

#include <limits>
#include <tuple>
#include <vector>

#include "gtest/gtest.h"
#include "src/tint/number.h"

namespace tint::reader::wgsl {
namespace {

using LexerTest = testing::Test;

// Blankspace constants. These are macros on purpose to be able to easily build
// up string literals with them.
//
// Same line code points
#define kSpace " "
#define kHTab "\t"
#define kL2R "\xE2\x80\x8E"
#define kR2L "\xE2\x80\x8F"
// Line break code points
#define kCR "\r"
#define kLF "\n"
#define kVTab "\x0B"
#define kFF "\x0C"
#define kNL "\xC2\x85"
#define kLS "\xE2\x80\xA8"
#define kPS "\xE2\x80\xA9"

TEST_F(LexerTest, Empty) {
    Source::File file("", "");
    Lexer l(&file);
    auto t = l.next();
    EXPECT_TRUE(t.IsEof());
}

TEST_F(LexerTest, Skips_Blankspace_Basic) {
    Source::File file("", "\t\r\n\t    ident\t\n\t  \r ");
    Lexer l(&file);

    auto t = l.next();
    EXPECT_TRUE(t.IsIdentifier());
    EXPECT_EQ(t.source().range.begin.line, 2u);
    EXPECT_EQ(t.source().range.begin.column, 6u);
    EXPECT_EQ(t.source().range.end.line, 2u);
    EXPECT_EQ(t.source().range.end.column, 11u);
    EXPECT_EQ(t.to_str(), "ident");

    t = l.next();
    EXPECT_TRUE(t.IsEof());
}

TEST_F(LexerTest, Skips_Blankspace_Exotic) {
    Source::File file("",                              //
                      kVTab kFF kNL kLS kPS kL2R kR2L  //
                      "ident"                          //
                      kVTab kFF kNL kLS kPS kL2R kR2L);
    Lexer l(&file);

    auto t = l.next();
    EXPECT_TRUE(t.IsIdentifier());
    EXPECT_EQ(t.source().range.begin.line, 6u);
    EXPECT_EQ(t.source().range.begin.column, 7u);
    EXPECT_EQ(t.source().range.end.line, 6u);
    EXPECT_EQ(t.source().range.end.column, 12u);
    EXPECT_EQ(t.to_str(), "ident");

    t = l.next();
    EXPECT_TRUE(t.IsEof());
}

TEST_F(LexerTest, Skips_Comments_Line) {
    Source::File file("", R"(//starts with comment
ident1 //ends with comment
// blank line
 ident2)");
    Lexer l(&file);

    auto t = l.next();
    EXPECT_TRUE(t.IsIdentifier());
    EXPECT_EQ(t.source().range.begin.line, 2u);
    EXPECT_EQ(t.source().range.begin.column, 1u);
    EXPECT_EQ(t.source().range.end.line, 2u);
    EXPECT_EQ(t.source().range.end.column, 7u);
    EXPECT_EQ(t.to_str(), "ident1");

    t = l.next();
    EXPECT_TRUE(t.IsIdentifier());
    EXPECT_EQ(t.source().range.begin.line, 4u);
    EXPECT_EQ(t.source().range.begin.column, 2u);
    EXPECT_EQ(t.source().range.end.line, 4u);
    EXPECT_EQ(t.source().range.end.column, 8u);
    EXPECT_EQ(t.to_str(), "ident2");

    t = l.next();
    EXPECT_TRUE(t.IsEof());
}

TEST_F(LexerTest, Skips_Comments_Unicode) {
    Source::File file("", R"(// starts with 🙂🙂🙂
ident1 //ends with 🙂🙂🙂
// blank line
 ident2)");
    Lexer l(&file);

    auto t = l.next();
    EXPECT_TRUE(t.IsIdentifier());
    EXPECT_EQ(t.source().range.begin.line, 2u);
    EXPECT_EQ(t.source().range.begin.column, 1u);
    EXPECT_EQ(t.source().range.end.line, 2u);
    EXPECT_EQ(t.source().range.end.column, 7u);
    EXPECT_EQ(t.to_str(), "ident1");

    t = l.next();
    EXPECT_TRUE(t.IsIdentifier());
    EXPECT_EQ(t.source().range.begin.line, 4u);
    EXPECT_EQ(t.source().range.begin.column, 2u);
    EXPECT_EQ(t.source().range.end.line, 4u);
    EXPECT_EQ(t.source().range.end.column, 8u);
    EXPECT_EQ(t.to_str(), "ident2");

    t = l.next();
    EXPECT_TRUE(t.IsEof());
}

using LineCommentTerminatorTest = testing::TestWithParam<const char*>;
TEST_P(LineCommentTerminatorTest, Terminators) {
    // Test that line comments are ended by blankspace characters other than
    // space, horizontal tab, left-to-right mark, and right-to-left mark.
    auto* c = GetParam();
    std::string src = "let// This is a comment";
    src += c;
    src += "ident";
    Source::File file("", src);
    Lexer l(&file);

    auto t = l.next();
    EXPECT_TRUE(t.Is(Token::Type::kLet));
    EXPECT_EQ(t.source().range.begin.line, 1u);
    EXPECT_EQ(t.source().range.begin.column, 1u);
    EXPECT_EQ(t.source().range.end.line, 1u);
    EXPECT_EQ(t.source().range.end.column, 4u);

    auto is_same_line = [](std::string_view v) {
        return v == kSpace || v == kHTab || v == kL2R || v == kR2L;
    };

    if (!is_same_line(c)) {
        size_t line = is_same_line(c) ? 1u : 2u;
        size_t col = is_same_line(c) ? 25u : 1u;
        t = l.next();
        EXPECT_TRUE(t.IsIdentifier());
        EXPECT_EQ(t.source().range.begin.line, line);
        EXPECT_EQ(t.source().range.begin.column, col);
        EXPECT_EQ(t.source().range.end.line, line);
        EXPECT_EQ(t.source().range.end.column, col + 5);
        EXPECT_EQ(t.to_str(), "ident");
    }

    t = l.next();
    EXPECT_TRUE(t.IsEof());
}
INSTANTIATE_TEST_SUITE_P(LexerTest,
                         LineCommentTerminatorTest,
                         testing::Values(
                             // same line
                             kSpace,
                             kHTab,
                             kCR,
                             kL2R,
                             kR2L,
                             // line break
                             kLF,
                             kVTab,
                             kFF,
                             kNL,
                             kLS,
                             kPS));

TEST_F(LexerTest, Skips_Comments_Block) {
    Source::File file("", R"(/* comment
text */ident)");
    Lexer l(&file);

    auto t = l.next();
    EXPECT_TRUE(t.IsIdentifier());
    EXPECT_EQ(t.source().range.begin.line, 2u);
    EXPECT_EQ(t.source().range.begin.column, 8u);
    EXPECT_EQ(t.source().range.end.line, 2u);
    EXPECT_EQ(t.source().range.end.column, 13u);
    EXPECT_EQ(t.to_str(), "ident");

    t = l.next();
    EXPECT_TRUE(t.IsEof());
}

TEST_F(LexerTest, Skips_Comments_Block_Nested) {
    Source::File file("", R"(/* comment
text // nested line comments are ignored /* more text
/////**/ */*/ident)");
    Lexer l(&file);

    auto t = l.next();
    EXPECT_TRUE(t.IsIdentifier());
    EXPECT_EQ(t.source().range.begin.line, 3u);
    EXPECT_EQ(t.source().range.begin.column, 14u);
    EXPECT_EQ(t.source().range.end.line, 3u);
    EXPECT_EQ(t.source().range.end.column, 19u);
    EXPECT_EQ(t.to_str(), "ident");

    t = l.next();
    EXPECT_TRUE(t.IsEof());
}

TEST_F(LexerTest, Skips_Comments_Block_Unterminated) {
    // I had to break up the /* because otherwise the clang readability check
    // errored out saying it could not find the end of a multi-line comment.
    Source::File file("", R"(
  /)"
                          R"(*
abcd)");
    Lexer l(&file);

    auto t = l.next();
    ASSERT_TRUE(t.Is(Token::Type::kError));
    EXPECT_EQ(t.to_str(), "unterminated block comment");
    EXPECT_EQ(t.source().range.begin.line, 2u);
    EXPECT_EQ(t.source().range.begin.column, 3u);
    EXPECT_EQ(t.source().range.end.line, 2u);
    EXPECT_EQ(t.source().range.end.column, 4u);
}

TEST_F(LexerTest, Null_InBlankspace_IsError) {
    Source::File file("", std::string{' ', 0, ' '});
    Lexer l(&file);

    auto t = l.next();
    EXPECT_TRUE(t.IsError());
    EXPECT_EQ(t.source().range.begin.line, 1u);
    EXPECT_EQ(t.source().range.begin.column, 2u);
    EXPECT_EQ(t.source().range.end.line, 1u);
    EXPECT_EQ(t.source().range.end.column, 2u);
    EXPECT_EQ(t.to_str(), "null character found");
}

TEST_F(LexerTest, Null_InLineComment_IsError) {
    Source::File file("", std::string{'/', '/', ' ', 0, ' '});
    Lexer l(&file);

    auto t = l.next();
    EXPECT_TRUE(t.IsError());
    EXPECT_EQ(t.source().range.begin.line, 1u);
    EXPECT_EQ(t.source().range.begin.column, 4u);
    EXPECT_EQ(t.source().range.end.line, 1u);
    EXPECT_EQ(t.source().range.end.column, 4u);
    EXPECT_EQ(t.to_str(), "null character found");
}

TEST_F(LexerTest, Null_InBlockComment_IsError) {
    Source::File file("", std::string{'/', '*', ' ', 0, '*', '/'});
    Lexer l(&file);

    auto t = l.next();
    EXPECT_TRUE(t.IsError());
    EXPECT_EQ(t.source().range.begin.line, 1u);
    EXPECT_EQ(t.source().range.begin.column, 4u);
    EXPECT_EQ(t.source().range.end.line, 1u);
    EXPECT_EQ(t.source().range.end.column, 4u);
    EXPECT_EQ(t.to_str(), "null character found");
}

TEST_F(LexerTest, Null_InIdentifier_IsError) {
    // Try inserting a null in an identifier. Other valid token
    // kinds will behave similarly, so use the identifier case
    // as a representative.
    Source::File file("", std::string{'a', 0, 'c'});
    Lexer l(&file);

    auto t = l.next();
    EXPECT_TRUE(t.IsIdentifier());
    EXPECT_EQ(t.to_str(), "a");
    t = l.next();
    EXPECT_TRUE(t.IsError());
    EXPECT_EQ(t.source().range.begin.line, 1u);
    EXPECT_EQ(t.source().range.begin.column, 2u);
    EXPECT_EQ(t.source().range.end.line, 1u);
    EXPECT_EQ(t.source().range.end.column, 2u);
    EXPECT_EQ(t.to_str(), "null character found");
}

struct FloatData {
    const char* input;
    double result;
};
inline std::ostream& operator<<(std::ostream& out, FloatData data) {
    out << std::string(data.input);
    return out;
}
using FloatTest = testing::TestWithParam<FloatData>;
TEST_P(FloatTest, Parse) {
    auto params = GetParam();
    Source::File file("", params.input);
    Lexer l(&file);

    auto t = l.next();
    if (std::string(params.input).back() == 'f') {
        EXPECT_TRUE(t.Is(Token::Type::kFloatLiteral_F));
    } else if (std::string(params.input).back() == 'h') {
        EXPECT_TRUE(t.Is(Token::Type::kFloatLiteral_H));
    } else {
        EXPECT_TRUE(t.Is(Token::Type::kFloatLiteral));
    }
    EXPECT_EQ(t.to_f64(), params.result);
    EXPECT_EQ(t.source().range.begin.line, 1u);
    EXPECT_EQ(t.source().range.begin.column, 1u);
    EXPECT_EQ(t.source().range.end.line, 1u);
    EXPECT_EQ(t.source().range.end.column, 1u + strlen(params.input));

    t = l.next();
    EXPECT_TRUE(t.IsEof());
}
INSTANTIATE_TEST_SUITE_P(LexerTest,
                         FloatTest,
                         testing::Values(
                             // No decimal, with 'f' suffix
                             FloatData{"0f", 0.0},
                             FloatData{"1f", 1.0},
                             FloatData{"-0f", 0.0},
                             FloatData{"-1f", -1.0},
                             // No decimal, with 'h' suffix
                             FloatData{"0h", 0.0},
                             FloatData{"1h", 1.0},
                             FloatData{"-0h", 0.0},
                             FloatData{"-1h", -1.0},

                             // Zero, with decimal.
                             FloatData{"0.0", 0.0},
                             FloatData{"0.", 0.0},
                             FloatData{".0", 0.0},
                             FloatData{"-0.0", 0.0},
                             FloatData{"-0.", 0.0},
                             FloatData{"-.0", 0.0},
                             // Zero, with decimal and 'f' suffix
                             FloatData{"0.0f", 0.0},
                             FloatData{"0.f", 0.0},
                             FloatData{".0f", 0.0},
                             FloatData{"-0.0f", 0.0},
                             FloatData{"-0.f", 0.0},
                             FloatData{"-.0f", 0.0},
                             // Zero, with decimal and 'h' suffix
                             FloatData{"0.0h", 0.0},
                             FloatData{"0.h", 0.0},
                             FloatData{".0h", 0.0},
                             FloatData{"-0.0h", 0.0},
                             FloatData{"-0.h", 0.0},
                             FloatData{"-.0h", 0.0},

                             // Non-zero with decimal
                             FloatData{"5.7", 5.7},
                             FloatData{"5.", 5.},
                             FloatData{".7", .7},
                             FloatData{"-5.7", -5.7},
                             FloatData{"-5.", -5.},
                             FloatData{"-.7", -.7},
                             // Non-zero with decimal and 'f' suffix
                             FloatData{"5.7f", static_cast<double>(5.7f)},
                             FloatData{"5.f", static_cast<double>(5.f)},
                             FloatData{".7f", static_cast<double>(.7f)},
                             FloatData{"-5.7f", static_cast<double>(-5.7f)},
                             FloatData{"-5.f", static_cast<double>(-5.f)},
                             FloatData{"-.7f", static_cast<double>(-.7f)},
                             // Non-zero with decimal and 'h' suffix
                             FloatData{"5.7h", static_cast<double>(f16::Quantize(5.7f))},
                             FloatData{"5.h", static_cast<double>(f16::Quantize(5.f))},
                             FloatData{".7h", static_cast<double>(f16::Quantize(.7f))},
                             FloatData{"-5.7h", static_cast<double>(f16::Quantize(-5.7f))},
                             FloatData{"-5.h", static_cast<double>(f16::Quantize(-5.f))},
                             FloatData{"-.7h", static_cast<double>(f16::Quantize(-.7f))},

                             // No decimal, with exponent
                             FloatData{"1e5", 1e5},
                             FloatData{"1E5", 1e5},
                             FloatData{"1e-5", 1e-5},
                             FloatData{"1E-5", 1e-5},
                             // No decimal, with exponent and 'f' suffix
                             FloatData{"1e5f", static_cast<double>(1e5f)},
                             FloatData{"1E5f", static_cast<double>(1e5f)},
                             FloatData{"1e-5f", static_cast<double>(1e-5f)},
                             FloatData{"1E-5f", static_cast<double>(1e-5f)},
                             // No decimal, with exponent and 'h' suffix
                             FloatData{"6e4h", static_cast<double>(f16::Quantize(6e4f))},
                             FloatData{"6E4h", static_cast<double>(f16::Quantize(6e4f))},
                             FloatData{"1e-5h", static_cast<double>(f16::Quantize(1e-5f))},
                             FloatData{"1E-5h", static_cast<double>(f16::Quantize(1e-5f))},
                             // With decimal and exponents
                             FloatData{"0.2e+12", 0.2e12},
                             FloatData{"1.2e-5", 1.2e-5},
                             FloatData{"2.57e23", 2.57e23},
                             FloatData{"2.5e+0", 2.5},
                             FloatData{"2.5e-0", 2.5},
                             // With decimal and exponents and 'f' suffix
                             FloatData{"0.2e+12f", static_cast<double>(0.2e12f)},
                             FloatData{"1.2e-5f", static_cast<double>(1.2e-5f)},
                             FloatData{"2.57e23f", static_cast<double>(2.57e23f)},
                             FloatData{"2.5e+0f", static_cast<double>(2.5f)},
                             FloatData{"2.5e-0f", static_cast<double>(2.5f)},
                             // With decimal and exponents and 'h' suffix
                             FloatData{"0.2e+5h", static_cast<double>(f16::Quantize(0.2e5f))},
                             FloatData{"1.2e-5h", static_cast<double>(f16::Quantize(1.2e-5f))},
                             FloatData{"6.55e4h", static_cast<double>(f16::Quantize(6.55e4f))},
                             FloatData{"2.5e+0h", static_cast<double>(f16::Quantize(2.5f))},
                             FloatData{"2.5e-0h", static_cast<double>(f16::Quantize(2.5f))},
                             // Quantization
                             FloatData{"3.141592653589793", 3.141592653589793},  // no quantization
                             FloatData{"3.141592653589793f", 3.1415927410125732},  // f32 quantized
                             FloatData{"3.141592653589793h", 3.140625}             // f16 quantized
                             ));

using FloatTest_Invalid = testing::TestWithParam<const char*>;
TEST_P(FloatTest_Invalid, Handles) {
    Source::File file("", GetParam());
    Lexer l(&file);

    auto t = l.next();
    EXPECT_FALSE(t.Is(Token::Type::kFloatLiteral) || t.Is(Token::Type::kFloatLiteral_F) ||
                 t.Is(Token::Type::kFloatLiteral_H));
}
INSTANTIATE_TEST_SUITE_P(LexerTest,
                         FloatTest_Invalid,
                         testing::Values(".",
                                         "-.",
                                         // Need a mantissa digit
                                         ".e5",
                                         ".E5",
                                         // Need exponent digits
                                         ".e",
                                         ".e+",
                                         ".e-",
                                         ".E",
                                         ".e+",
                                         ".e-",
                                         // Overflow
                                         "2.5e+256f",
                                         "-2.5e+127f",
                                         "6.5520e+4h",
                                         "-6.5e+12h",
                                         // Decimal exponent must immediately
                                         // follow the 'e'.
                                         "2.5e 12",
                                         "2.5e +12",
                                         "2.5e -12",
                                         "2.5e+ 123",
                                         "2.5e- 123",
                                         "2.5E 12",
                                         "2.5E +12",
                                         "2.5E -12",
                                         "2.5E+ 123",
                                         "2.5E- 123"));

using AsciiIdentifierTest = testing::TestWithParam<const char*>;
TEST_P(AsciiIdentifierTest, Parse) {
    Source::File file("", GetParam());
    Lexer l(&file);

    auto t = l.next();
    EXPECT_TRUE(t.IsIdentifier());
    EXPECT_EQ(t.source().range.begin.line, 1u);
    EXPECT_EQ(t.source().range.begin.column, 1u);
    EXPECT_EQ(t.source().range.end.line, 1u);
    EXPECT_EQ(t.source().range.end.column, 1u + strlen(GetParam()));
    EXPECT_EQ(t.to_str(), GetParam());
}
INSTANTIATE_TEST_SUITE_P(LexerTest,
                         AsciiIdentifierTest,
                         testing::Values("a",
                                         "test",
                                         "test01",
                                         "test_",
                                         "_test",
                                         "test_01",
                                         "ALLCAPS",
                                         "MiXeD_CaSe",
                                         "abcdefghijklmnopqrstuvwxyz",
                                         "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
                                         "alldigits_0123456789"));

struct UnicodeCase {
    const char* utf8;
    size_t count;
};

using ValidUnicodeIdentifierTest = testing::TestWithParam<UnicodeCase>;
TEST_P(ValidUnicodeIdentifierTest, Parse) {
    Source::File file("", GetParam().utf8);
    Lexer l(&file);

    auto t = l.next();
    EXPECT_TRUE(t.IsIdentifier());
    EXPECT_EQ(t.source().range.begin.line, 1u);
    EXPECT_EQ(t.source().range.begin.column, 1u);
    EXPECT_EQ(t.source().range.end.line, 1u);
    EXPECT_EQ(t.source().range.end.column, 1u + GetParam().count);
    EXPECT_EQ(t.to_str(), GetParam().utf8);
}
INSTANTIATE_TEST_SUITE_P(
    LexerTest,
    ValidUnicodeIdentifierTest,
    testing::ValuesIn({
        UnicodeCase{// "𝐢𝐝𝐞𝐧𝐭𝐢𝐟𝐢𝐞𝐫"
                    "\xf0\x9d\x90\xa2\xf0\x9d\x90\x9d\xf0\x9d\x90\x9e\xf0\x9d"
                    "\x90\xa7\xf0\x9d\x90\xad\xf0\x9d\x90\xa2\xf0\x9d\x90\x9f"
                    "\xf0\x9d\x90\xa2\xf0\x9d\x90\x9e\xf0\x9d\x90\xab",
                    40},
        UnicodeCase{// "𝑖𝑑𝑒𝑛𝑡𝑖𝑓𝑖𝑒𝑟"
                    "\xf0\x9d\x91\x96\xf0\x9d\x91\x91\xf0\x9d\x91\x92\xf0\x9d"
                    "\x91\x9b\xf0\x9d\x91\xa1\xf0\x9d\x91\x96\xf0\x9d\x91\x93"
                    "\xf0\x9d\x91\x96\xf0\x9d\x91\x92\xf0\x9d\x91\x9f",
                    40},
        UnicodeCase{// "ｉｄｅｎｔｉｆｉｅｒ"
                    "\xef\xbd\x89\xef\xbd\x84\xef\xbd\x85\xef\xbd\x8e\xef\xbd\x94\xef"
                    "\xbd\x89\xef\xbd\x86\xef\xbd\x89\xef\xbd\x85\xef\xbd\x92",
                    30},
        UnicodeCase{// "𝕚𝕕𝕖𝕟𝕥𝕚𝕗𝕚𝕖𝕣𝟙𝟚𝟛"
                    "\xf0\x9d\x95\x9a\xf0\x9d\x95\x95\xf0\x9d\x95\x96\xf0\x9d"
                    "\x95\x9f\xf0\x9d\x95\xa5\xf0\x9d\x95\x9a\xf0\x9d\x95\x97"
                    "\xf0\x9d\x95\x9a\xf0\x9d\x95\x96\xf0\x9d\x95\xa3\xf0\x9d"
                    "\x9f\x99\xf0\x9d\x9f\x9a\xf0\x9d\x9f\x9b",
                    52},
        UnicodeCase{// "𝖎𝖉𝖊𝖓𝖙𝖎𝖋𝖎𝖊𝖗123"
                    "\xf0\x9d\x96\x8e\xf0\x9d\x96\x89\xf0\x9d\x96\x8a\xf0\x9d\x96\x93"
                    "\xf0\x9d\x96\x99\xf0\x9d\x96\x8e\xf0\x9d\x96\x8b\xf0\x9d\x96\x8e"
                    "\xf0\x9d\x96\x8a\xf0\x9d\x96\x97\x31\x32\x33",
                    43},
    }));

using InvalidUnicodeIdentifierTest = testing::TestWithParam<const char*>;
TEST_P(InvalidUnicodeIdentifierTest, Parse) {
    Source::File file("", GetParam());
    Lexer l(&file);

    auto t = l.next();
    EXPECT_TRUE(t.IsError());
    EXPECT_EQ(t.source().range.begin.line, 1u);
    EXPECT_EQ(t.source().range.begin.column, 1u);
    EXPECT_EQ(t.source().range.end.line, 1u);
    EXPECT_EQ(t.source().range.end.column, 1u);
    EXPECT_EQ(t.to_str(), "invalid UTF-8");
}
INSTANTIATE_TEST_SUITE_P(LexerTest,
                         InvalidUnicodeIdentifierTest,
                         testing::ValuesIn({
                             "\x80\x80\x80\x80",  // 10000000
                             "\x81\x80\x80\x80",  // 10000001
                             "\x8f\x80\x80\x80",  // 10001111
                             "\x90\x80\x80\x80",  // 10010000
                             "\x91\x80\x80\x80",  // 10010001
                             "\x9f\x80\x80\x80",  // 10011111
                             "\xa0\x80\x80\x80",  // 10100000
                             "\xa1\x80\x80\x80",  // 10100001
                             "\xaf\x80\x80\x80",  // 10101111
                             "\xb0\x80\x80\x80",  // 10110000
                             "\xb1\x80\x80\x80",  // 10110001
                             "\xbf\x80\x80\x80",  // 10111111
                             "\xc0\x80\x80\x80",  // 11000000
                             "\xc1\x80\x80\x80",  // 11000001
                             "\xf5\x80\x80\x80",  // 11110101
                             "\xf6\x80\x80\x80",  // 11110110
                             "\xf7\x80\x80\x80",  // 11110111
                             "\xf8\x80\x80\x80",  // 11111000
                             "\xfe\x80\x80\x80",  // 11111110
                             "\xff\x80\x80\x80",  // 11111111

                             "\xd0",          // 2-bytes, missing second byte
                             "\xe8\x8f",      // 3-bytes, missing third byte
                             "\xf4\x8f\x8f",  // 4-bytes, missing fourth byte

                             "\xd0\x7f",          // 2-bytes, second byte MSB unset
                             "\xe8\x7f\x8f",      // 3-bytes, second byte MSB unset
                             "\xe8\x8f\x7f",      // 3-bytes, third byte MSB unset
                             "\xf4\x7f\x8f\x8f",  // 4-bytes, second byte MSB unset
                             "\xf4\x8f\x7f\x8f",  // 4-bytes, third byte MSB unset
                             "\xf4\x8f\x8f\x7f",  // 4-bytes, fourth byte MSB unset
                         }));

TEST_F(LexerTest, IdentifierTest_SingleUnderscoreDoesNotMatch) {
    Source::File file("", "_");
    Lexer l(&file);

    auto t = l.next();
    EXPECT_FALSE(t.IsIdentifier());
}

TEST_F(LexerTest, IdentifierTest_DoesNotStartWithDoubleUnderscore) {
    Source::File file("", "__test");
    Lexer l(&file);

    auto t = l.next();
    EXPECT_FALSE(t.IsIdentifier());
}

TEST_F(LexerTest, IdentifierTest_DoesNotStartWithNumber) {
    Source::File file("", "01test");
    Lexer l(&file);

    auto t = l.next();
    EXPECT_FALSE(t.IsIdentifier());
}

////////////////////////////////////////////////////////////////////////////////
// ParseIntegerTest
////////////////////////////////////////////////////////////////////////////////
struct ParseIntegerCase {
    const char* input;
    int64_t result;
};

inline std::ostream& operator<<(std::ostream& out, ParseIntegerCase data) {
    out << std::string(data.input);
    return out;
}

using ParseIntegerTest = testing::TestWithParam<std::tuple<char, ParseIntegerCase>>;
TEST_P(ParseIntegerTest, Parse) {
    auto suffix = std::get<0>(GetParam());
    auto params = std::get<1>(GetParam());
    Source::File file("", params.input);

    auto t = Lexer(&file).next();
    switch (suffix) {
        case 'i':
            EXPECT_TRUE(t.Is(Token::Type::kIntLiteral_I));
            break;
        case 'u':
            EXPECT_TRUE(t.Is(Token::Type::kIntLiteral_U));
            break;
        case 0:
            EXPECT_TRUE(t.Is(Token::Type::kIntLiteral));
            break;
    }
    EXPECT_EQ(t.source().range.begin.line, 1u);
    EXPECT_EQ(t.source().range.begin.column, 1u);
    EXPECT_EQ(t.source().range.end.line, 1u);
    EXPECT_EQ(t.source().range.end.column, 1u + strlen(params.input));
    ASSERT_FALSE(t.IsError()) << t.to_str();
    EXPECT_EQ(t.to_i64(), params.result);
}

INSTANTIATE_TEST_SUITE_P(Dec_AInt,
                         ParseIntegerTest,
                         testing::Combine(testing::Values('\0'),  // No suffix
                                          testing::ValuesIn(std::vector<ParseIntegerCase>{
                                              {"0", 0},
                                              {"-2", -2},
                                              {"2", 2},
                                              {"123", 123},
                                              {"2147483647", 2147483647},
                                              {"-2147483648", -2147483648LL},
                                              {"-9223372036854775808", -9223372036854775807LL - 1},
                                          })));

INSTANTIATE_TEST_SUITE_P(Dec_u32,
                         ParseIntegerTest,
                         testing::Combine(testing::Values('u'),  // Suffix
                                          testing::ValuesIn(std::vector<ParseIntegerCase>{
                                              {"0u", 0},
                                              {"123u", 123},
                                              {"4294967295u", 4294967295ll},
                                          })));

INSTANTIATE_TEST_SUITE_P(Dec_i32,
                         ParseIntegerTest,
                         testing::Combine(testing::Values('i'),  // Suffix
                                          testing::ValuesIn(std::vector<ParseIntegerCase>{
                                              {"0i", 0u},
                                              {"-0i", 0u},
                                              {"123i", 123},
                                              {"-123i", -123},
                                              {"2147483647i", 2147483647},
                                              {"-2147483647i", -2147483647ll},
                                          })));

INSTANTIATE_TEST_SUITE_P(Hex_AInt,
                         ParseIntegerTest,
                         testing::Combine(testing::Values('\0'),  // No suffix
                                          testing::ValuesIn(std::vector<ParseIntegerCase>{
                                              {"0x0", 0},
                                              {"0X0", 0},
                                              {"0x42", 66},
                                              {"0X42", 66},
                                              {"-0x42", -66},
                                              {"-0X42", -66},
                                              {"0xeF1Abc9", 0xeF1Abc9},
                                              {"0XeF1Abc9", 0xeF1Abc9},
                                              {"-0xeF1Abc9", -0xeF1Abc9},
                                              {"-0XeF1Abc9", -0xeF1Abc9},
                                              {"0x80000000", 0x80000000},
                                              {"0X80000000", 0X80000000},
                                              {"-0x80000000", -0x80000000ll},
                                              {"-0X80000000", -0X80000000ll},
                                              {"0x7FFFFFFF", 0x7fffffff},
                                              {"0X7FFFFFFF", 0x7fffffff},
                                              {"0x7fffffff", 0x7fffffff},
                                              {"0x7fffffff", 0x7fffffff},
                                              {"0x7FfFfFfF", 0x7fffffff},
                                              {"0X7FfFfFfF", 0x7fffffff},
                                              {"0x7fffffffffffffff", 0x7fffffffffffffffll},
                                              {"-0x7fffffffffffffff", -0x7fffffffffffffffll},
                                          })));

INSTANTIATE_TEST_SUITE_P(Hex_u32,
                         ParseIntegerTest,
                         testing::Combine(testing::Values('u'),  // Suffix
                                          testing::ValuesIn(std::vector<ParseIntegerCase>{
                                              {"0x0u", 0},
                                              {"0x42u", 66},
                                              {"0xeF1Abc9u", 250719177},
                                              {"0xFFFFFFFFu", 0xffffffff},
                                              {"0XFFFFFFFFu", 0xffffffff},
                                              {"0xffffffffu", 0xffffffff},
                                              {"0Xffffffffu", 0xffffffff},
                                              {"0xfFfFfFfFu", 0xffffffff},
                                              {"0XfFfFfFfFu", 0xffffffff},
                                          })));

INSTANTIATE_TEST_SUITE_P(Hex_i32,
                         ParseIntegerTest,
                         testing::Combine(testing::Values('i'),  // Suffix
                                          testing::ValuesIn(std::vector<ParseIntegerCase>{
                                              {"0x0i", 0},
                                              {"0x42i", 66},
                                              {"-0x0i", 0},
                                              {"-0x42i", -66},
                                              {"0xeF1Abc9i", 250719177},
                                              {"-0xeF1Abc9i", -250719177},
                                              {"0x7FFFFFFFi", 0x7fffffff},
                                              {"-0x7FFFFFFFi", -0x7fffffff},
                                              {"0X7FFFFFFFi", 0x7fffffff},
                                              {"-0X7FFFFFFFi", -0x7fffffff},
                                              {"0x7fffffffi", 0x7fffffff},
                                              {"-0x7fffffffi", -0x7fffffff},
                                              {"0X7fffffffi", 0x7fffffff},
                                              {"-0X7fffffffi", -0x7fffffff},
                                              {"0x7FfFfFfFi", 0x7fffffff},
                                              {"-0x7FfFfFfFi", -0x7fffffff},
                                              {"0X7FfFfFfFi", 0x7fffffff},
                                              {"-0X7FfFfFfFi", -0x7fffffff},
                                          })));
////////////////////////////////////////////////////////////////////////////////
// ParseIntegerTest_CannotBeRepresented
////////////////////////////////////////////////////////////////////////////////
using ParseIntegerTest_CannotBeRepresented =
    testing::TestWithParam<std::tuple<const char*, const char*>>;
TEST_P(ParseIntegerTest_CannotBeRepresented, Parse) {
    auto type = std::get<0>(GetParam());
    auto source = std::get<1>(GetParam());
    Source::File file("", source);
    auto t = Lexer(&file).next();
    EXPECT_TRUE(t.Is(Token::Type::kError));
    auto expect = "value cannot be represented as '" + std::string(type) + "'";
    EXPECT_EQ(t.to_str(), expect);
}
INSTANTIATE_TEST_SUITE_P(AbstractInt,
                         ParseIntegerTest_CannotBeRepresented,
                         testing::Combine(testing::Values("abstract-int"),
                                          testing::Values("9223372036854775808",
                                                          "0xFFFFFFFFFFFFFFFF",
                                                          "0xffffffffffffffff",
                                                          "0x8000000000000000")));

INSTANTIATE_TEST_SUITE_P(i32,
                         ParseIntegerTest_CannotBeRepresented,
                         testing::Combine(testing::Values("i32"),  // type
                                          testing::Values("2147483648i")));

INSTANTIATE_TEST_SUITE_P(u32,
                         ParseIntegerTest_CannotBeRepresented,
                         testing::Combine(testing::Values("u32"),         // type
                                          testing::Values("4294967296u",  //
                                                          "-1u")));

////////////////////////////////////////////////////////////////////////////////
// ParseIntegerTest_LeadingZeros
////////////////////////////////////////////////////////////////////////////////
using ParseIntegerTest_LeadingZeros = testing::TestWithParam<const char*>;
TEST_P(ParseIntegerTest_LeadingZeros, Parse) {
    Source::File file("", GetParam());
    auto t = Lexer(&file).next();
    EXPECT_TRUE(t.Is(Token::Type::kError));
    EXPECT_EQ(t.to_str(), "integer literal cannot have leading 0s");
}

INSTANTIATE_TEST_SUITE_P(LeadingZero,
                         ParseIntegerTest_LeadingZeros,
                         testing::Values("01234", "0000", "-00", "00u"));

////////////////////////////////////////////////////////////////////////////////
// ParseIntegerTest_NoSignificantDigits
////////////////////////////////////////////////////////////////////////////////
using ParseIntegerTest_NoSignificantDigits = testing::TestWithParam<const char*>;
TEST_P(ParseIntegerTest_NoSignificantDigits, Parse) {
    Source::File file("", GetParam());
    auto t = Lexer(&file).next();
    EXPECT_TRUE(t.Is(Token::Type::kError));
    EXPECT_EQ(t.to_str(), "integer or float hex literal has no significant digits");
}

INSTANTIATE_TEST_SUITE_P(LeadingZero,
                         ParseIntegerTest_NoSignificantDigits,
                         testing::Values("0x",
                                         "0X",
                                         "-0x",
                                         "-0X",
                                         "0xu",
                                         "0Xu",
                                         "-0xu",
                                         "-0Xu",
                                         "0xi",
                                         "0Xi",
                                         "-0xi",
                                         "-0Xi"));

struct TokenData {
    const char* input;
    Token::Type type;
};
inline std::ostream& operator<<(std::ostream& out, TokenData data) {
    out << std::string(data.input);
    return out;
}
using PunctuationTest = testing::TestWithParam<TokenData>;
TEST_P(PunctuationTest, Parses) {
    auto params = GetParam();
    Source::File file("", params.input);
    Lexer l(&file);

    auto t = l.next();
    EXPECT_TRUE(t.Is(params.type));
    EXPECT_EQ(t.source().range.begin.line, 1u);
    EXPECT_EQ(t.source().range.begin.column, 1u);
    EXPECT_EQ(t.source().range.end.line, 1u);
    EXPECT_EQ(t.source().range.end.column, 1u + strlen(params.input));

    t = l.next();
    EXPECT_EQ(t.source().range.begin.column, 1 + std::string(params.input).size());
}
INSTANTIATE_TEST_SUITE_P(LexerTest,
                         PunctuationTest,
                         testing::Values(TokenData{"&", Token::Type::kAnd},
                                         TokenData{"&&", Token::Type::kAndAnd},
                                         TokenData{"->", Token::Type::kArrow},
                                         TokenData{"@", Token::Type::kAttr},
                                         TokenData{"/", Token::Type::kForwardSlash},
                                         TokenData{"!", Token::Type::kBang},
                                         TokenData{"[", Token::Type::kBracketLeft},
                                         TokenData{"]", Token::Type::kBracketRight},
                                         TokenData{"{", Token::Type::kBraceLeft},
                                         TokenData{"}", Token::Type::kBraceRight},
                                         TokenData{":", Token::Type::kColon},
                                         TokenData{",", Token::Type::kComma},
                                         TokenData{"=", Token::Type::kEqual},
                                         TokenData{"==", Token::Type::kEqualEqual},
                                         TokenData{">", Token::Type::kGreaterThan},
                                         TokenData{">=", Token::Type::kGreaterThanEqual},
                                         TokenData{">>", Token::Type::kShiftRight},
                                         TokenData{"<", Token::Type::kLessThan},
                                         TokenData{"<=", Token::Type::kLessThanEqual},
                                         TokenData{"<<", Token::Type::kShiftLeft},
                                         TokenData{"%", Token::Type::kMod},
                                         TokenData{"!=", Token::Type::kNotEqual},
                                         TokenData{"-", Token::Type::kMinus},
                                         TokenData{"--", Token::Type::kMinusMinus},
                                         TokenData{".", Token::Type::kPeriod},
                                         TokenData{"+", Token::Type::kPlus},
                                         TokenData{"++", Token::Type::kPlusPlus},
                                         TokenData{"|", Token::Type::kOr},
                                         TokenData{"||", Token::Type::kOrOr},
                                         TokenData{"(", Token::Type::kParenLeft},
                                         TokenData{")", Token::Type::kParenRight},
                                         TokenData{";", Token::Type::kSemicolon},
                                         TokenData{"*", Token::Type::kStar},
                                         TokenData{"~", Token::Type::kTilde},
                                         TokenData{"_", Token::Type::kUnderscore},
                                         TokenData{"^", Token::Type::kXor},
                                         TokenData{"+=", Token::Type::kPlusEqual},
                                         TokenData{"-=", Token::Type::kMinusEqual},
                                         TokenData{"*=", Token::Type::kTimesEqual},
                                         TokenData{"/=", Token::Type::kDivisionEqual},
                                         TokenData{"%=", Token::Type::kModuloEqual},
                                         TokenData{"&=", Token::Type::kAndEqual},
                                         TokenData{"|=", Token::Type::kOrEqual},
                                         TokenData{"^=", Token::Type::kXorEqual}));

using KeywordTest = testing::TestWithParam<TokenData>;
TEST_P(KeywordTest, Parses) {
    auto params = GetParam();
    Source::File file("", params.input);
    Lexer l(&file);

    auto t = l.next();
    EXPECT_TRUE(t.Is(params.type)) << params.input;
    EXPECT_EQ(t.source().range.begin.line, 1u);
    EXPECT_EQ(t.source().range.begin.column, 1u);
    EXPECT_EQ(t.source().range.end.line, 1u);
    EXPECT_EQ(t.source().range.end.column, 1u + strlen(params.input));

    t = l.next();
    EXPECT_EQ(t.source().range.begin.column, 1 + std::string(params.input).size());
}
INSTANTIATE_TEST_SUITE_P(
    LexerTest,
    KeywordTest,
    testing::Values(TokenData{"array", Token::Type::kArray},
                    TokenData{"bitcast", Token::Type::kBitcast},
                    TokenData{"bool", Token::Type::kBool},
                    TokenData{"break", Token::Type::kBreak},
                    TokenData{"case", Token::Type::kCase},
                    TokenData{"continue", Token::Type::kContinue},
                    TokenData{"continuing", Token::Type::kContinuing},
                    TokenData{"default", Token::Type::kDefault},
                    TokenData{"discard", Token::Type::kDiscard},
                    TokenData{"else", Token::Type::kElse},
                    TokenData{"f32", Token::Type::kF32},
                    TokenData{"fallthrough", Token::Type::kFallthrough},
                    TokenData{"false", Token::Type::kFalse},
                    TokenData{"fn", Token::Type::kFn},
                    TokenData{"for", Token::Type::kFor},
                    TokenData{"function", Token::Type::kFunction},
                    TokenData{"i32", Token::Type::kI32},
                    TokenData{"if", Token::Type::kIf},
                    TokenData{"import", Token::Type::kImport},
                    TokenData{"let", Token::Type::kLet},
                    TokenData{"loop", Token::Type::kLoop},
                    TokenData{"mat2x2", Token::Type::kMat2x2},
                    TokenData{"mat2x3", Token::Type::kMat2x3},
                    TokenData{"mat2x4", Token::Type::kMat2x4},
                    TokenData{"mat3x2", Token::Type::kMat3x2},
                    TokenData{"mat3x3", Token::Type::kMat3x3},
                    TokenData{"mat3x4", Token::Type::kMat3x4},
                    TokenData{"mat4x2", Token::Type::kMat4x2},
                    TokenData{"mat4x3", Token::Type::kMat4x3},
                    TokenData{"mat4x4", Token::Type::kMat4x4},
                    TokenData{"override", Token::Type::kOverride},
                    TokenData{"private", Token::Type::kPrivate},
                    TokenData{"ptr", Token::Type::kPtr},
                    TokenData{"return", Token::Type::kReturn},
                    TokenData{"sampler", Token::Type::kSampler},
                    TokenData{"sampler_comparison", Token::Type::kComparisonSampler},
                    TokenData{"storage", Token::Type::kStorage},
                    TokenData{"storage_buffer", Token::Type::kStorage},
                    TokenData{"struct", Token::Type::kStruct},
                    TokenData{"switch", Token::Type::kSwitch},
                    TokenData{"texture_1d", Token::Type::kTextureSampled1d},
                    TokenData{"texture_2d", Token::Type::kTextureSampled2d},
                    TokenData{"texture_2d_array", Token::Type::kTextureSampled2dArray},
                    TokenData{"texture_3d", Token::Type::kTextureSampled3d},
                    TokenData{"texture_cube", Token::Type::kTextureSampledCube},
                    TokenData{"texture_cube_array", Token::Type::kTextureSampledCubeArray},
                    TokenData{"texture_depth_2d", Token::Type::kTextureDepth2d},
                    TokenData{"texture_depth_2d_array", Token::Type::kTextureDepth2dArray},
                    TokenData{"texture_depth_cube", Token::Type::kTextureDepthCube},
                    TokenData{"texture_depth_cube_array", Token::Type::kTextureDepthCubeArray},
                    TokenData{"texture_depth_multisampled_2d",
                              Token::Type::kTextureDepthMultisampled2d},
                    TokenData{"texture_multisampled_2d", Token::Type::kTextureMultisampled2d},
                    TokenData{"texture_storage_1d", Token::Type::kTextureStorage1d},
                    TokenData{"texture_storage_2d", Token::Type::kTextureStorage2d},
                    TokenData{"texture_storage_2d_array", Token::Type::kTextureStorage2dArray},
                    TokenData{"texture_storage_3d", Token::Type::kTextureStorage3d},
                    TokenData{"true", Token::Type::kTrue},
                    TokenData{"type", Token::Type::kType},
                    TokenData{"u32", Token::Type::kU32},
                    TokenData{"uniform", Token::Type::kUniform},
                    TokenData{"var", Token::Type::kVar},
                    TokenData{"vec2", Token::Type::kVec2},
                    TokenData{"vec3", Token::Type::kVec3},
                    TokenData{"vec4", Token::Type::kVec4},
                    TokenData{"while", Token::Type::kWhile},
                    TokenData{"workgroup", Token::Type::kWorkgroup}));

}  // namespace
}  // namespace tint::reader::wgsl
