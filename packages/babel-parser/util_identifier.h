#ifndef BABEL_PARSER_util_identifier_H_
#define BABEL_PARSER_util_identifier_H_
#include <string>
#include <unordered_set>
#include "babel-parser/charcodes.h"

using namespace std;

namespace util_identifier
{
    // import * as charCodes from "charcodes";
    // import { isIdentifierStart } from "@babel/helper-validator-identifier";

    // export {
    //   isIdentifierStart,
    //   isIdentifierChar,
    //   isReservedWord,
    //   isStrictBindOnlyReservedWord,
    //   isStrictBindReservedWord,
    //   isStrictReservedWord,
    //   isKeyword,
    // } from "@babel/helper-validator-identifier";

    // export const keywordRelationalOperator = /^in(stanceof)?$/;

    // Test whether a current state character code and next character code is @

    bool isIteratorStart(
        int current,
        int next,
        int next2)
    {
        return (
            current == charcodes::atSign &&
            next == charcodes::atSign &&
            isIdentifierStart(next2));
    };

    // This is the comprehensive set of JavaScript reserved words
    // If a word is in this set, it could be a reserved word,
    // depending on sourceType/strictMode/binding info. In other words
    // if a word is not in this set, it is not a reserved word under
    // any circumstance.
    unordered_set<string> reservedWordLikeSet = {
        "break",
        "case",
        "catch",
        "continue",
        "debugger",
        "default",
        "do",
        "else",
        "finally",
        "for",
        "function",
        "if",
        "return",
        "switch",
        "throw",
        "try",
        "var",
        "const",
        "while",
        "with",
        "new",
        "this",
        "super",
        "class",
        "extends",
        "export",
        "import",
        "null",
        "true",
        "false",
        "in",
        "instanceof",
        "typeof",
        "void",
        "delete",
        // strict
        "implements",
        "interface",
        "let",
        "package",
        "private",
        "protected",
        "public",
        "static",
        "yield",
        // strictBind
        "eval",
        "arguments",
        // reservedWorkLike
        "enum",
        "await",
    };

    bool canBeReservedWord(string word)
    {
        auto it = reservedWordLikeSet.find(word);

        if (it != reservedWordLikeSet.end())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

}

#endif // BABEL_PARSER_util_identifier_H_