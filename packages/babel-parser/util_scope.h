#ifndef BABEL_PARSER_util_scope_H_
#define BABEL_PARSER_util_scope_H_
#include <string>
#include <variant>
#include <set>
#include <map>
#include <vector>
#include "babel-parser/util_scopeflags.h"
#include "babel-parser/util_location.h"

using namespace std;
using namespace util_scopeflags;

struct Tokenizer;

namespace util_scope
{
    // import { ScopeFlag, BindingFlag, type BindingTypes } from "./scopeflags.ts";
    // import type { Position } from "./location.ts";
    // import type * as N from "../types.ts";
    // import { Errors } from "../parse-error.ts";
    // import type Tokenizer from "../tokenizer/index.ts";

    // Start an AST node, attaching a start offset.
    class Scope
    {
    public:
        util_scopeflags::ScopeFlag flags;
        // A set of var-declared names in the current lexical scope
        set<string> var;
        // A set of lexically-declared names in the current lexical scope
        set<string> lexical;
        // A set of lexically-declared FunctionDeclaration names in the current lexical scope
        set<string> functions;

        Scope(util_scopeflags::ScopeFlag flags)
        {
            this->flags = flags;
        };
    };

    // template <typename IScope>
    class ScopeHandler
    {
    public:
        Tokenizer *parser;
        vector<Scope &> scopeStack;
        bool inModule;
        map<string, util_location::Position *> undefinedExports;

        ScopeHandler(Tokenizer *parser, bool inModule)
        {
            this->parser = parser;
            this->inModule = inModule;
        };

        Scope createScope(ScopeFlag flags)
        {
            Scope scope(flags);
            return scope;
        };

        void enter(ScopeFlag flags)
        {
            Scope scope = this->createScope(flags);
            this->scopeStack.push_back(&scope);
        };

        ScopeFlag exit()
        {
            Scope &scope = this->scopeStack.back();
            // TODO 删除最后一项？？
            return scope.flags;
        };

        // The spec says:
        // > At the top level of a function, or script, function declarations are
        // > treated like var declarations rather than like lexical declarations.
        bool treatFunctionsAsVarInScope(Scope scope)
        {
            // return !!(
            //     scope.flags & (ScopeFlag::FUNCTION | ScopeFlag::STATIC_BLOCK) ||
            //     (!(this->parser->inModule) && scope.flags & ScopeFlag::PROGRAM));
            return false;
        };

        Scope currentScope()
        {
            return this->scopeStack.back();
        };

        ScopeFlag currentVarScopeFlags()
        {
            for (auto it = this->scopeStack.begin(); it != this->scopeStack.end(); ++it)
            {
                if ((it->flags) & ScopeFlag::VAR)
                {
                    return it->flags;
                };
            };
        };

        ScopeFlag currentThisScopeFlags()
        {
            for (auto it = this->scopeStack.begin(); it != this->scopeStack.end(); ++it)
            {
                if (it->flags & (ScopeFlag::VAR | ScopeFlag::CLASS) && !(it->flags & ScopeFlag::ARROW))
                {
                    return it->flags;
                };
            };
        };
    };
};

#endif // BABEL_PARSER_util_scope_H_