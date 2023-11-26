#ifndef BABEL_PARSER_tokenizer_context_H_
#define BABEL_PARSER_tokenizer_context_H_

#include <string>
using namespace std;

namespace tokenizer_context
{
  class TokContext
  {
  public:
    string token;
    bool preserveSpace;
    TokContext(string token, bool preserveSpace)
    {
      this->token = token;
      this->preserveSpace = preserveSpace;
    };
    static TokContext *create(string token, bool preserveSpace)
    {
      TokContext t(token, preserveSpace);
      return &t;
    };
  };

  namespace types
  {
    TokContext *brace = TokContext::create("{", false);               // normal JavaScript expression
    TokContext *j_oTag = TokContext::create("<tag", false);           // JSX opening tag
    TokContext *j_cTag = TokContext::create("</tag", false);          // JSX closing tag
    TokContext *j_expr = TokContext::create("<tag>...</tag>", false); // JSX expressions
  }
}

#endif // BABEL_PARSER_tokenizer_context_H_