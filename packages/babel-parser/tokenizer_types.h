#ifndef BABEL_PARSER_tokenizer_types_H_
#define BABEL_PARSER_tokenizer_types_H_
#include <string>
#include <map>
#include <vector>
using namespace std;
#define TTOKEN1(attr1) \
  [] {                 \
    TokenOptions t;    \
    t.attr1 = attr1;   \
    return &t;         \
  }()

#define TTOKEN2(attr1, attr2) \
  [] {                        \
    TokenOptions t;           \
    t.attr1 = attr1;          \
    t.attr2 = attr2;          \
    return &t;                \
  }()

#define TTOKEN3(attr1, attr2, attr3) \
  [] {                               \
    TokenOptions t;                  \
    t.attr1 = attr1;                 \
    t.attr2 = attr2;                 \
    t.attr3 = attr3;                 \
    return &t;                       \
  }()

#define TTOKEN4(attr1, attr2, attr3, attr4) \
  [] {                                      \
    TokenOptions t;                         \
    t.attr1 = attr1;                        \
    t.attr2 = attr2;                        \
    t.attr4 = attr4;                        \
    return &t;                              \
  }()

#define O(StructName, ...) \
  [] {                     \
    StructName t;          \
    __VA_ARGS__            \
    return &t;             \
  }()

#define P(name, value) \
  t.name = value;

#define PNAME(name) \
  t.name = name;

namespace tokenizer_types
{
  const bool beforeExpr = true;
  const bool startsExpr = true;
  const bool isLoop = true;
  const bool isAssign = true;
  const bool prefix = true;
  const bool postfix = true;

  struct TokenOptions
  {
    string keyword;
    bool beforeExpr;
    bool startsExpr;
    bool rightAssociative;
    bool isLoop;
    bool isAssign;
    bool prefix;
    bool postfix;
    int binop;
  };

  typedef int TokenType;

  class ExportedTokenType
  {
  public:
    string label;
    string keyword;
    bool beforeExpr;
    bool startsExpr;
    bool rightAssociative;
    bool isLoop;
    bool isAssign;
    bool prefix;
    bool postfix;
    int binop;

    ExportedTokenType(string label, TokenOptions *conf)
    {
      this->label = label;
      this->keyword = (*conf).keyword;
      this->beforeExpr = (*conf).beforeExpr;
      this->startsExpr = (*conf).startsExpr;
      this->rightAssociative = (*conf).rightAssociative;
      this->isLoop = (*conf).isLoop;
      this->isAssign = (*conf).isAssign;
      this->prefix = (*conf).prefix;
      this->postfix = (*conf).postfix;
      this->binop = (*conf).binop;
    };
  };

  int tokenTypeCounter = -1;
  vector<ExportedTokenType *> *const tokenTypes;
  vector<string> *const tokenLabels;
  vector<int> *const tokenBinops;
  vector<bool> *const tokenBeforeExprs;
  vector<bool> *const tokenStartsExprs;
  vector<bool> *const tokenPrefixes;

  TokenType createToken(string name, TokenOptions *options)
  {
    ++tokenTypeCounter;

    tokenLabels->push_back(name);
    tokenBinops->push_back(options->binop ? options->binop : -1);
    tokenBeforeExprs->push_back(options->beforeExpr);
    tokenStartsExprs->push_back(options->startsExpr);
    tokenPrefixes->push_back(options->prefix);
    tokenTypes->push_back(&ExportedTokenType(name, options));

    return tokenTypeCounter;
  }

  TokenType createToken(string name)
  {
    TokenOptions *options;
    return createToken(name, options);
  }

  map<string, TokenType> *const keywords;

  TokenType createKeyword(string name, TokenOptions *options)
  {
    options->keyword = name;
    TokenType token = createToken(name, options);
    keywords->insert({name, token});
    return token;
  }

  auto createBinop(string name, int binop)
  {
    TokenOptions *option;
    option->beforeExpr = beforeExpr;
    option->binop = binop;
    return createToken(name, option);
  }

  TokenType createKeywordLike(
      string name,
      TokenOptions *options)
  {
    ++tokenTypeCounter;
    keywords->insert({name, tokenTypeCounter});
    tokenLabels->push_back(name);
    tokenBinops->push_back(options->binop ? options->binop : -1);
    tokenBeforeExprs->push_back(options->beforeExpr);
    tokenStartsExprs->push_back(options->startsExpr);
    tokenPrefixes->push_back(options->prefix);
    tokenTypes->push_back(&ExportedTokenType("name", options));
    return tokenTypeCounter;
  }

  namespace tt
  {
    TokenOptions *beforeExpr_startsExpr()
    {
      TokenOptions t;
      t.beforeExpr = beforeExpr;
      t.startsExpr = startsExpr;
      return &t;
    }
    TokenOptions *beforeExpr_()
    {
      TokenOptions t;
      t.beforeExpr = beforeExpr;
      return &t;
    }

    TokenOptions *startsExpr_()
    {
      TokenOptions t;
      t.startsExpr = startsExpr;
      return &t;
    }
    TokenOptions *beforeExpr_isAssign()
    {
      TokenOptions t;
      t.beforeExpr = beforeExpr;
      t.isAssign = isAssign;
      return &t;
    }
    TokenOptions *prefix_postfix_startsExpr()
    {
      TokenOptions t;
      t.prefix = prefix;
      t.postfix = postfix;
      t.startsExpr = startsExpr;
      return &t;
    }
    TokenOptions *beforeExpr_prefix_startsExpr()
    {
      TokenOptions t;
      t.beforeExpr = prefix;
      t.postfix = postfix;
      t.startsExpr = startsExpr;
      return &t;
    }
    // Punctuation token types.
    const TokenType bracketL = createToken("[", TTOKEN2(beforeExpr, startsExpr));
    const TokenType bracketHashL = createToken("#[", TTOKEN2(beforeExpr, startsExpr));
    const TokenType bracketBarL = createToken("[|", TTOKEN2(beforeExpr, startsExpr));
    const TokenType bracketR = createToken("]");
    const TokenType bracketBarR = createToken("|]");
    const TokenType braceL = createToken("{", TTOKEN2(beforeExpr, startsExpr));
    const TokenType braceBarL = createToken("{|", TTOKEN2(beforeExpr, startsExpr));
    const TokenType braceHashL = createToken("#{", TTOKEN2(beforeExpr, startsExpr));
    const TokenType braceR = createToken("}");
    const TokenType braceBarR = createToken("|}");
    const TokenType parenL = createToken("(", TTOKEN2(beforeExpr, startsExpr));
    const TokenType parenR = createToken(")");
    const TokenType comma = createToken(",", TTOKEN1(beforeExpr));
    const TokenType semi = createToken(";", TTOKEN1(beforeExpr));
    const TokenType colon = createToken(":", TTOKEN1(beforeExpr));
    const TokenType doubleColon = createToken("::", TTOKEN1(beforeExpr));
    const TokenType dot = createToken(".");
    const TokenType question = createToken("?", TTOKEN1(beforeExpr));
    const TokenType questionDot = createToken("?.");
    const TokenType arrow = createToken("=>", TTOKEN1(beforeExpr));
    const TokenType template_ = createToken("template");
    const TokenType ellipsis = createToken("...", TTOKEN1(beforeExpr));
    const TokenType backQuote = createToken("`", TTOKEN1(startsExpr));
    const TokenType dollarBraceL = createToken("${", TTOKEN2(beforeExpr, startsExpr));
    // start: isTemplate
    const TokenType templateTail = createToken("...`", TTOKEN1(startsExpr));
    const TokenType templateNonTail = createToken("...${", TTOKEN2(beforeExpr, startsExpr));
    // end: isTemplate
    const TokenType at = createToken("@");
    const TokenType hash = createToken("#", TTOKEN1(startsExpr));

    // Special hashbang token.
    const TokenType interpreterDirective = createToken("#!...");

    // Operators. These carry several kinds of properties to help the
    // parser use them properly (the presence of these properties is
    // what categorizes them as operators).
    //
    // `binop`, when present, specifies that this operator is a binary
    // operator, and will refer to its precedence.
    //
    // `prefix` and `postfix` mark the operator as a prefix or postfix
    // unary operator.
    //
    // `isAssign` marks all of `=`, `+=`, `-=` etcetera, which act as
    // binary operators with a very low precedence, that should result
    // in AssignmentExpression nodes.

    // start: isAssign
    const TokenType eq = createToken("=", TTOKEN2(beforeExpr, isAssign));
    const TokenType assign = createToken("_=", TTOKEN2(beforeExpr, isAssign));
    const TokenType slashAssign = createToken("_=", TTOKEN2(beforeExpr, isAssign));
    // These are only needed to support % and ^ as a Hack-pipe topic token.
    // When the proposal settles on a token, the others can be merged with
    // tt.assign.
    const TokenType xorAssign = createToken("_=", TTOKEN2(beforeExpr, isAssign));
    const TokenType moduloAssign = createToken("_=", TTOKEN2(beforeExpr, isAssign));
    // end: isAssign

    const TokenType incDec = createToken("++/--", TTOKEN3(prefix, postfix, startsExpr));
    const TokenType bang = createToken("!", TTOKEN3(prefix, postfix, startsExpr));
    const TokenType tilde = createToken("~", TTOKEN3(beforeExpr, prefix, startsExpr));

    // More possible topic tokens.
    // When the proposal settles on a token, at least one of these may be removed.
    const TokenType doubleCaret = createToken("^^", TTOKEN1(startsExpr));
    const TokenType doubleAt = createToken("@@", TTOKEN1(startsExpr));

    // start: isBinop
    const TokenType pipeline = createBinop("|>", 0);
    const TokenType nullishCoalescing = createBinop("??", 1);
    const TokenType logicalOR = createBinop("||", 1);
    const TokenType logicalAND = createBinop("&&", 2);
    const TokenType bitwiseOR = createBinop("|", 3);
    const TokenType bitwiseXOR = createBinop("^", 4);
    const TokenType bitwiseAND = createBinop("&", 5);
    const TokenType equality = createBinop("==/!=/===/!==", 6);
    const TokenType lt = createBinop("</>/<=/>=", 7);
    const TokenType gt = createBinop("</>/<=/>=", 7);
    const TokenType relational = createBinop("</>/<=/>=", 7);
    const TokenType bitShift = createBinop("<</>>/>>>", 8);
    const TokenType bitShiftL = createBinop("<</>>/>>>", 8);
    const TokenType bitShiftR = createBinop("<</>>/>>>", 8);
    const TokenType plusMin = createToken("+/-", O(TokenOptions, PNAME(beforeExpr) P(binop, 9) PNAME(prefix) PNAME(startsExpr)));
    // startsExpr: required by v8intrinsic plugin
    const TokenType modulo = createToken("%", O(TokenOptions, P(binop, 10) PNAME(startsExpr)));
    // unset `beforeExpr` as it can be `function *`
    const TokenType star = createToken("*", O(TokenOptions, P(binop, 10)));
    const TokenType slash = createBinop("/", 10);
    const TokenType exponent = createToken("**",
                                           O(TokenOptions, PNAME(beforeExpr) P(binop, 11) P(rightAssociative, true)));

    // Keywords
    // Don't forget to update packages/babel-helper-validator-identifier/src/keyword.js
    // when new keywords are added
    // start: isLiteralPropertyName
    // start: isKeyword
    const TokenType _in = createKeyword("in", O(TokenOptions, PNAME(beforeExpr) P(binop, 7)));
    const TokenType _instanceof = createKeyword("instanceof", O(TokenOptions, PNAME(beforeExpr) P(binop, 7)));
    // end: isBinop
    const TokenType _break = createKeyword("break", O(TokenOptions));
    const TokenType _case = createKeyword("case", O(TokenOptions, PNAME(beforeExpr)));
    const TokenType _catch = createKeyword("catch", O(TokenOptions));
    const TokenType _continue = createKeyword("continue", O(TokenOptions));
    const TokenType _debugger = createKeyword("debugger", O(TokenOptions));
    const TokenType _default = createKeyword("default", O(TokenOptions, PNAME(beforeExpr)));
    const TokenType _else = createKeyword("else", O(TokenOptions, PNAME(beforeExpr)));
    const TokenType _finally = createKeyword("finally", O(TokenOptions));
    const TokenType _function = createKeyword("function", O(TokenOptions, PNAME(startsExpr)));
    const TokenType _if = createKeyword("if", O(TokenOptions));
    const TokenType _return = createKeyword("return", O(TokenOptions, PNAME(beforeExpr)));
    const TokenType _switch = createKeyword("switch", O(TokenOptions));
    const TokenType _throw = createKeyword("throw", TTOKEN3(beforeExpr, prefix, startsExpr));
    const TokenType _try = createKeyword("try", O(TokenOptions));
    const TokenType _var = createKeyword("var", O(TokenOptions));
    const TokenType _const = createKeyword("const", O(TokenOptions));
    const TokenType _with = createKeyword("with", O(TokenOptions));
    const TokenType _new = createKeyword("new", TTOKEN2(beforeExpr, startsExpr));
    const TokenType _this = createKeyword("this", TTOKEN1(startsExpr));
    const TokenType _super = createKeyword("super", TTOKEN1(startsExpr));
    const TokenType _class = createKeyword("class", TTOKEN1(startsExpr));
    const TokenType _extends = createKeyword("extends", TTOKEN1(beforeExpr));
    const TokenType _export = createKeyword("export", O(TokenOptions));
    const TokenType _import = createKeyword("import", TTOKEN1(startsExpr));
    const TokenType _null = createKeyword("null", TTOKEN1(startsExpr));
    const TokenType _true = createKeyword("true", TTOKEN1(startsExpr));
    const TokenType _false = createKeyword("false", TTOKEN1(startsExpr));
    const TokenType _typeof = createKeyword("typeof", TTOKEN3(beforeExpr, prefix, startsExpr));
    const TokenType _void = createKeyword("void", TTOKEN3(beforeExpr, prefix, startsExpr));
    const TokenType _delete = createKeyword("delete", TTOKEN3(beforeExpr, prefix, startsExpr));
    // start: isLoop
    const TokenType _do = createKeyword("do", TTOKEN2(isLoop, beforeExpr));
    const TokenType _for = createKeyword("for", TTOKEN1(isLoop));
    const TokenType _while = createKeyword("while", TTOKEN1(isLoop));
    // end: isLoop
    // end: isKeyword

    // Primary literals
    // start: isIdentifier
    const TokenType _as = createKeywordLike("as", TTOKEN1(startsExpr));
    const TokenType _assert = createKeywordLike("assert", TTOKEN1(startsExpr));
    const TokenType _async = createKeywordLike("async", TTOKEN1(startsExpr));
    const TokenType _await = createKeywordLike("await", TTOKEN1(startsExpr));
    const TokenType _defer = createKeywordLike("defer", TTOKEN1(startsExpr));
    const TokenType _from = createKeywordLike("from", TTOKEN1(startsExpr));
    const TokenType _get = createKeywordLike("get", TTOKEN1(startsExpr));
    const TokenType _let = createKeywordLike("let", TTOKEN1(startsExpr));
    const TokenType _meta = createKeywordLike("meta", TTOKEN1(startsExpr));
    const TokenType _of = createKeywordLike("of", TTOKEN1(startsExpr));
    const TokenType _sent = createKeywordLike("sent", TTOKEN1(startsExpr));
    const TokenType _set = createKeywordLike("set", TTOKEN1(startsExpr));
    const TokenType _source = createKeywordLike("source", TTOKEN1(startsExpr));
    const TokenType _static = createKeywordLike("static", TTOKEN1(startsExpr));
    const TokenType _using = createKeywordLike("using", TTOKEN1(startsExpr));
    const TokenType _yield = createKeywordLike("yield", TTOKEN1(startsExpr));

    // Flow and TypeScript Keywordlike
    const TokenType _asserts = createKeywordLike("asserts", TTOKEN1(startsExpr));
    const TokenType _checks = createKeywordLike("checks", TTOKEN1(startsExpr));
    const TokenType _exports = createKeywordLike("exports", TTOKEN1(startsExpr));
    const TokenType _global = createKeywordLike("global", TTOKEN1(startsExpr));
    const TokenType _implements = createKeywordLike("implements", TTOKEN1(startsExpr));
    const TokenType _intrinsic = createKeywordLike("intrinsic", TTOKEN1(startsExpr));
    const TokenType _infer = createKeywordLike("infer", TTOKEN1(startsExpr));
    const TokenType _is = createKeywordLike("is", TTOKEN1(startsExpr));
    const TokenType _mixins = createKeywordLike("mixins", TTOKEN1(startsExpr));
    const TokenType _proto = createKeywordLike("proto", TTOKEN1(startsExpr));
    const TokenType _require = createKeywordLike("require", TTOKEN1(startsExpr));
    const TokenType _satisfies = createKeywordLike("satisfies", TTOKEN1(startsExpr));
    // start: isTSTypeOperator
    const TokenType _keyof = createKeywordLike("keyof", TTOKEN1(startsExpr));
    const TokenType _readonly = createKeywordLike("readonly", TTOKEN1(startsExpr));
    const TokenType _unique = createKeywordLike("unique", TTOKEN1(startsExpr));
    // end: isTSTypeOperator
    // start: isTSDeclarationStart
    const TokenType _abstract = createKeywordLike("abstract", TTOKEN1(startsExpr));
    const TokenType _declare = createKeywordLike("declare", TTOKEN1(startsExpr));
    const TokenType _enum = createKeywordLike("enum", TTOKEN1(startsExpr));
    const TokenType _module = createKeywordLike("module", TTOKEN1(startsExpr));
    const TokenType _namespace = createKeywordLike("namespace", TTOKEN1(startsExpr));
    // start: isFlowInterfaceOrTypeOrOpaque
    const TokenType _interface = createKeywordLike("interface", TTOKEN1(startsExpr));
    const TokenType _type = createKeywordLike("type", TTOKEN1(startsExpr));
    // end: isTSDeclarationStart
    const TokenType _opaque = createKeywordLike("opaque", TTOKEN1(startsExpr));
    // end: isFlowInterfaceOrTypeOrOpaque
    const TokenType name = createToken("name", TTOKEN1(startsExpr));
    // end: isIdentifier

    const TokenType string = createToken("string", TTOKEN1(startsExpr));
    const TokenType num = createToken("num", TTOKEN1(startsExpr));
    const TokenType bigint = createToken("bigint", TTOKEN1(startsExpr));
    const TokenType decimal = createToken("decimal", TTOKEN1(startsExpr));
    // end: isLiteralPropertyName
    const TokenType regexp = createToken("regexp", TTOKEN1(startsExpr));
    const TokenType privateName = createToken("#name", TTOKEN1(startsExpr));
    const TokenType eof = createToken("eof");

    // jsx plugin
    const TokenType jsxName = createToken("jsxName");
    const TokenType jsxText = createToken("jsxText", O(TokenOptions, P(beforeExpr, true)));
    const TokenType jsxTagStart = createToken("jsxTagStart", O(TokenOptions, P(startsExpr, true)));
    const TokenType jsxTagEnd = createToken("jsxTagEnd");

    // placeholder plugin
    const TokenType placeholder = createToken("%%", O(TokenOptions, P(startsExpr, true)));
  };

}
#endif //BABEL_PARSER_tokenizer_types_H_