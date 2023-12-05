#ifndef BABEL_PARSER_options_H_
#define BABEL_PARSER_options_H_
#include <string>
using namespace std;

namespace options
{
    struct PluginList;

    // A second optional argument can be given to further configure
    // the parser process. These options are recognized:

    /**
     * "script" | "module" | "unambiguous"
     */
    typedef string SourceType;

    struct Options
    {
        SourceType sourceType;
        string sourceFilename;
        int startColumn;
        int startLine;
        bool allowAwaitOutsideFunction;
        bool allowReturnOutsideFunction;
        bool allowNewTargetOutsideFunction;
        bool allowImportExportEverywhere;
        bool allowSuperOutsideMethod;
        bool allowUndeclaredExports;
        PluginList *plugins;
        bool strictMode;
        bool ranges;
        bool tokens;
        bool createImportExpressions;
        bool createParenthesizedExpressions;
        bool errorRecovery;
        bool attachComment;
        bool annexB;
    };

    const Options const defaultOptions = []()
    {
        Options o;
        // Source type ("script" or "module") for different semantics
        o.sourceType = "script";
        // Source filename.
        o.sourceFilename = "";
        // Column (0-based) from which to start counting source. Useful for
        // integration with other tools.
        o.startColumn = 0;
        // Line (1-based) from which to start counting source. Useful for
        // integration with other tools.
        o.startLine = 1;
        // When enabled, await at the top level is not considered an
        // error.
        o.allowAwaitOutsideFunction = false;
        // When enabled, a return at the top level is not considered an
        // error.
        o.allowReturnOutsideFunction = false;
        // When enabled, new.target outside a function or class is not
        // considered an error.
        o.allowNewTargetOutsideFunction = false;
        // When enabled, import/export statements are not constrained to
        // appearing at the top of the program.
        o.allowImportExportEverywhere = false;
        // TODO
        o.allowSuperOutsideMethod = false;
        // When enabled, export statements can reference undeclared variables.
        o.allowUndeclaredExports = false;
        // An array of plugins to enable
        //   o.plugins = [];
        // TODO
        o.strictMode = false;
        // Nodes have their start and end characters offsets recorded in
        // `start` and `end` properties (directly on the node, rather than
        // the `loc` object, which holds line/column data. To also add a
        // [semi-standardized][range] `range` property holding a `[start,
        // end]` array with the same numbers, set the `ranges` option to
        // `true`.
        //
        // [range]: https://bugzilla.mozilla.org/show_bug.cgi?id=745678
        o.ranges = false;
        // Adds all parsed tokens to a `tokens` property on the `File` node
        o.tokens = false;
        // Whether to create ImportExpression AST nodes (if false
        // `import(foo)` will be parsed as CallExpression(Import, [Identifier(foo)])
        o.createImportExpressions = false;
        // Whether to create ParenthesizedExpression AST nodes (if false
        // the parser sets extra.parenthesized on the expression nodes instead).
        o.createParenthesizedExpressions = false;
        // When enabled, errors are attached to the AST instead of being directly thrown.
        // Some errors will still throw, because @babel/parser can't always recover.
        o.errorRecovery = false;
        // When enabled, comments will be attached to adjacent AST nodes as one of
        // `leadingComments`, `trailingComments` and `innerComments`. The comment attachment
        // is vital to preserve comments after transform. If you don't print AST back,
        // consider set this option to `false` for performance
        o.attachComment = true;
        // When enabled, the parser will support Annex B syntax.
        // https://tc39.es/ecma262/#sec-additional-ecmascript-features-for-web-browsers
        o.annexB = true;

        return o;
    }();

    // Interpret and default an options object
    Options getOptions(Options opts)
    {
        //   if (opts == null) {
        //     return { ...defaultOptions };
        //   }
        //   if (opts.annexB != null && opts.annexB !== false) {
        //     throw new Error("The `annexB` option can only be set to `false`.");
        //   }

        //   const options: any = {};
        //   for (const key of Object.keys(defaultOptions) as (keyof Options)[]) {
        //     options[key] = opts[key] ?? defaultOptions[key];
        //   }
        Options newOption = defaultOptions;
        return newOption;
    }

}

#endif // BABEL_PARSER_options_H_