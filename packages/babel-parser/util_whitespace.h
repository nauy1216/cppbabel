#ifndef BABEL_PARSER_util_whitespace_H_
#define BABEL_PARSER_util_whitespace_H_
#include <string>
#include <unordered_set>
#include <regex>
#include "babel-parser/charcodes.h"

using namespace std;

namespace util_whitespace
{
// Matches a whole line break (where CRLF is considered a single
// line break). Used to count lines.
// export const lineBreak = /\r\n?|[\n\u2028\u2029]/;
// export const lineBreakG = new RegExp(lineBreak.source, "g");

// https://tc39.github.io/ecma262/#sec-line-terminators
bool isNewLine(int code) {
  switch (code) {
    case charcodes::lineFeed:
    case charcodes::carriageReturn:
    case charcodes::lineSeparator:
    case charcodes::paragraphSeparator:
      return true;

    default:
      return false;
  }
}

//TODO 待验证
// 空格、单行注释、多行注释
const std::regex skipWhiteSpace(R"((\s|\/\/.*|\/\*[^]*?\*\/)*)");
// export const skipWhiteSpace = /(?:\s|\/\/.*|\/\*[^]*?\*\/)*/g;

//TODO 待验证
const  std::regex skipWhiteSpaceInLine(R"((?:[^\S\n\r\u2028\u2029]|\/\/.*|\/\*.*?\*\/)*)");
// export const skipWhiteSpaceInLine =
//   /(?:[^\S\n\r\u2028\u2029]|\/\/.*|\/\*.*?\*\/)*/g;

// Skip whitespace and single-line comments, including /* no newline here */.
// After this RegExp matches, its lastIndex points to a line terminator, or
// the start of multi-line comment (which is effectively a line terminator),
// or the end of string.

//TODO
// const skipWhiteSpaceToLineBreak = new RegExp(
//   // Unfortunately JS doesn't support Perl's atomic /(?>pattern)/ or
//   // possessive quantifiers, so we use a trick to prevent backtracking
//   // when the look-ahead for line terminator fails.
//   "(?=(" +
//     // Capture the whitespace and comments that should be skipped inside
//     // a look-ahead assertion, and then re-match the group as a unit.
//     skipWhiteSpaceInLine.source +
//     "))\\1" +
//     // Look-ahead for either line terminator, start of multi-line comment,
//     // or end of string.
//     /(?=[\n\r\u2028\u2029]|\/\*(?!.*?\*\/)|$)/.source,
//   "y", // sticky
// );

// https://tc39.github.io/ecma262/#sec-white-space
bool isWhitespace(int code) {
  switch (code) {
    case 0x0009: // CHARACTER TABULATION
    case 0x000b: // LINE TABULATION
    case 0x000c: // FORM FEED
    case charcodes::space:
    case charcodes::nonBreakingSpace:
    case charcodes::oghamSpaceMark:
    case 0x2000: // EN QUAD
    case 0x2001: // EM QUAD
    case 0x2002: // EN SPACE
    case 0x2003: // EM SPACE
    case 0x2004: // THREE-PER-EM SPACE
    case 0x2005: // FOUR-PER-EM SPACE
    case 0x2006: // SIX-PER-EM SPACE
    case 0x2007: // FIGURE SPACE
    case 0x2008: // PUNCTUATION SPACE
    case 0x2009: // THIN SPACE
    case 0x200a: // HAIR SPACE
    case 0x202f: // NARROW NO-BREAK SPACE
    case 0x205f: // MEDIUM MATHEMATICAL SPACE
    case 0x3000: // IDEOGRAPHIC SPACE
    case 0xfeff: // ZERO WIDTH NO-BREAK SPACE
      return true;

    default:
      return false;
  }
}

 
}

#endif // BABEL_PARSER_util_whitespace_H_