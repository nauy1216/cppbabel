#ifndef BABEL_PARSER_tokenizer_state_H_
#define BABEL_PARSER_tokenizer_state_H_
#include <string>
#include <vector>
#include "babel-parser/options.h"
#include "babel-parser/util_location.h"
#include "babel-parser/types.h"
#include "babel-parser/tokenizer_types.h"
#include "babel-parser/tokenizer_context.h"
using namespace std;
using namespace tokenizer_types;

struct ParseError;
struct CommentWhitespace;

namespace tokenizer_state
{
    // import type { Options } from "../options.ts";
    // import type * as N from "../types.ts";
    // import type { CommentWhitespace } from "../parser/comments";
    // import { Position } from "../util/location.ts";

    // import { types as ct, type TokContext } from "./context.ts";
    // import { tt, type TokenType } from "./types.ts";
    // import type { Errors } from "../parse-error.ts";
    // import type { ParseError } from "../parse-error.ts";

    // export type DeferredStrictError =
    //   | typeof Errors.StrictNumericEscape
    //   | typeof Errors.StrictOctalLiteral;

    struct TopicContextState
    {
        // When a topic binding has been currently established,
        // then this is 1. Otherwise, it is 0. This is forwards compatible
        // with a future plugin for multiple lexical topics.
        int maxNumOfResolvableTopics;
        // When a topic binding has been currently established, and if that binding
        // has been used as a topic reference `#`, then this is 0. Otherwise, it is
        // `null`. This is forwards compatible with a future plugin for multiple
        // lexical topics.
        // null | 0
        int maxTopicIndex;
    };

    class State
    {
    public:
        bool strict;
        int curLine;
        int lineStart;

        // And, if locations are used, the {line, column} object
        // corresponding to those offsets
        util_location::Position *startLoc;
        util_location::Position *endLoc;

        void init(options::Options &o)
        {
            this->strict =
                o.strictMode == false
                    ? false
                : o.strictMode == true
                    ? true
                    : o.sourceType == "module";

            this->curLine = o.startLine;
            this->lineStart = -o.startColumn;

            util_location::Position pos(o.startLine, o.startColumn, 0);

            this->startLoc = this->endLoc = &pos;
        }

        vector<ParseError> *errors;

        // Used to signify the start of a potential arrow function
        int potentialArrowAt = -1;

        // Used to signify the start of an expression which looks like a
        // typed arrow function, but it isn't
        // e.g. a ? (b) : c => d
        //          ^
        vector<int> noArrowAt;

        // Used to signify the start of an expression whose params, if it looks like
        // an arrow function, shouldn't be converted to assignable nodes.
        // This is used to defer the validation of typed arrow functions inside
        // conditional expressions.
        // e.g. a ? (b) : c => d
        //          ^
        vector<int> noArrowParamsConversionAt;

        // Flags to track
        bool maybeInArrowParameters = false;
        bool inType = false;
        bool noAnonFunctionType = false;
        bool hasFlowComment = false;
        bool isAmbientContext = false;
        bool inAbstractClass = false;
        bool inDisallowConditionalTypesContext = false;

        // For the Hack-style pipelines plugin
        //   topicContext: TopicContextState = {
        //     maxNumOfResolvableTopics: 0,
        //     maxTopicIndex: null,
        //   };

        // For the F#-style pipelines plugin
        bool soloAwait = false;
        bool inFSharpPipelineDirectBody = false;

        // Labels in scope.
        //   labels: Array<{
        //     kind: "loop" | "switch" | undefined | null;
        //     name?: string | null;
        //     statementStart?: number;
        //   }> = [];

        // Comment store for Program.comments
        vector<types::Comment> comments;

        // Comment attachment store
        vector<CommentWhitespace> commentStack;

        // The current position of the tokenizer in the input.
        int pos = 0;

        // Properties of the current token:
        // Its type
        tokenizer_types::TokenType type = tt::eof;

        // For tokens that include more information than their type, the value
        any value;

        // Its start and end offset
        int start = 0;
        int end = 0;

        // Position information for the previous token
        // this is initialized when generating the second token.
        util_location::Position *lastTokEndLoc;
        // this is initialized when generating the second token.
        util_location::Position *lastTokStartLoc;

        int lastTokStart;

        // The context stack is used to track whether the apostrophe "`" starts
        // or ends a string template
        vector<tokenizer_context::TokContext> context; //: Array<TokContext> = [ct.brace];
                                                       // Used to track whether a JSX element is allowed to form
        bool canStartJSXElement = true;

        // Used to signal to callers of `readWord1` whether the word
        // contained any escape sequences. This is needed because words with
        // escape sequences must not be interpreted as keywords.
        bool containsEsc = false;

        // Used to track invalid escape sequences in template literals,
        // that must be reported if the template is not tagged.
        util_location::Position *firstInvalidTemplateEscapePos;

        // This property is used to track the following errors
        // - StrictNumericEscape
        // - StrictOctalLiteral
        //
        // in a literal that occurs prior to/immediately after a "use strict" directive.

        // todo(JLHwung): set strictErrors to null and avoid recording string errors
        // after a non-directive is parsed
        //   strictErrors: Map<number, [DeferredStrictError, Position]> = new Map();

        // Tokens length in token store
        int tokensLength = 0;

        util_location::Position curPosition()
        {
            util_location::Position p(this->curLine, this->pos - this->lineStart, this->pos);
            return p;
        };

        State clone(bool skipArrays)
        {
            // const state = new State();
            // const keys = Object.keys(this) as (keyof State)[];
            // for (let i = 0, length = keys.length; i < length; i++) {
            //   const key = keys[i];
            //   let val = this[key];

            //   if (!skipArrays && Array.isArray(val)) {
            //     val = val.slice();
            //   }

            //   // @ts-expect-error val must conform to S[key]
            //   state[key] = val;
            // }
            State state;
            return state;
        };
    };

    typedef int (*TypeCurPosition)(int, double);

    struct LookaheadState
    {
        int pos;
        any value;
        TokenType type;
        int start;
        int end;
        vector<tokenizer_context::TokContext> context;
        util_location::Position *startLoc;
        util_location::Position *lastTokEndLoc;
        int curLine;
        int lineStart;
        TypeCurPosition curPosition;
        /* Used only in readToken_mult_modulo */
        int inType;
        // These boolean properties are not initialized in createLookaheadState()
        // instead they will only be set by the tokenizer
        int containsEsc;
    };
}

#endif // BABEL_PARSER_tokenizer_context_H_