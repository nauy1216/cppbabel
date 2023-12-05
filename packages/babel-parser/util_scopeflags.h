#ifndef BABEL_PARSER_util_scopeflags_H_
#define BABEL_PARSER_util_scopeflags_H_
#include <string>
#include <variant>

using namespace std;

namespace util_scopeflags
{
    // Each scope gets a bitset that may contain these flags
    /* eslint-disable prettier/prettier */
    /* prettier-ignore */
    const enum ScopeFlag {
        OTHER        = 0b000000000,
        PROGRAM      = 0b000000001,
        FUNCTION     = 0b000000010,
        ARROW        = 0b000000100,
        SIMPLE_CATCH = 0b000001000,
        SUPER        = 0b000010000,
        DIRECT_SUPER = 0b000100000,
        CLASS        = 0b001000000,
        STATIC_BLOCK = 0b010000000,
        TS_MODULE    = 0b100000000,
        VAR          = PROGRAM | FUNCTION | STATIC_BLOCK | TS_MODULE
    };

    /* prettier-ignore */
    const enum BindingFlag {
        // These flags are meant to be _only_ used inside the Scope class (or subclasses).
        KIND_VALUE             = 0b0000000000001,
        KIND_TYPE              = 0b0000000000010,
        // Used in checkLVal and declareName to determine the type of a binding
        SCOPE_VAR              = 0b0000000000100, // Var-style binding
        SCOPE_LEXICAL          = 0b0000000001000, // Let- or const-style binding
        SCOPE_FUNCTION         = 0b0000000010000, // Function declaration
        SCOPE_OUTSIDE          = 0b0000000100000, // Special case for function names as
        // bound inside the function
        // Misc flags
        FLAG_NONE              = 0b00000001000000,
        FLAG_CLASS             = 0b00000010000000,
        FLAG_TS_ENUM           = 0b00000100000000,
        FLAG_TS_CONST_ENUM     = 0b00001000000000,
        FLAG_TS_EXPORT_ONLY    = 0b00010000000000,
        FLAG_FLOW_DECLARE_FN   = 0b00100000000000,
        FLAG_TS_IMPORT         = 0b01000000000000,
        // Whether "let" should be allowed in bound names in sloppy mode
        FLAG_NO_LET_IN_LEXICAL = 0b10000000000000,

        // These flags are meant to be _only_ used by Scope consumers
        /* prettier-ignore */
        /*                   = is value?  | is type?  |      scope     |    misc flags    */
        TYPE_CLASS           = KIND_VALUE | KIND_TYPE | SCOPE_LEXICAL  | FLAG_CLASS|FLAG_NO_LET_IN_LEXICAL,
        TYPE_LEXICAL         = KIND_VALUE | 0         | SCOPE_LEXICAL  | FLAG_NO_LET_IN_LEXICAL,
        TYPE_CATCH_PARAM     = KIND_VALUE | 0         | SCOPE_LEXICAL  | 0,
        TYPE_VAR             = KIND_VALUE | 0         | SCOPE_VAR      | 0,
        TYPE_FUNCTION        = KIND_VALUE | 0         | SCOPE_FUNCTION | 0,
        TYPE_TS_INTERFACE    = 0          | KIND_TYPE | 0              | FLAG_CLASS,
        TYPE_TS_TYPE         = 0          | KIND_TYPE | 0              | 0,
        TYPE_TS_ENUM         = KIND_VALUE | KIND_TYPE | SCOPE_LEXICAL  | FLAG_TS_ENUM|FLAG_NO_LET_IN_LEXICAL,
        TYPE_TS_AMBIENT      = 0          | 0         | 0              | FLAG_TS_EXPORT_ONLY,
        // These bindings don't introduce anything in the scope. They are used for assignments and
        // function expressions IDs.
        TYPE_NONE            = 0          | 0         | 0              | FLAG_NONE,
        TYPE_OUTSIDE         = KIND_VALUE | 0         | 0              | FLAG_NONE,
        TYPE_TS_CONST_ENUM   = TYPE_TS_ENUM | FLAG_TS_CONST_ENUM,
        TYPE_TS_NAMESPACE    = 0          | 0         | 0              | FLAG_TS_EXPORT_ONLY,
        TYPE_TS_TYPE_IMPORT  = 0          | KIND_TYPE | 0              | FLAG_TS_IMPORT,
        TYPE_TS_VALUE_IMPORT = 0          | 0         | 0              | FLAG_TS_IMPORT,
        TYPE_FLOW_DECLARE_FN = 0          | 0         | 0              | FLAG_FLOW_DECLARE_FN
    };


    /**
     *  | BindingFlag.TYPE_NONE
        | BindingFlag.TYPE_OUTSIDE
        | BindingFlag.TYPE_VAR
        | BindingFlag.TYPE_LEXICAL
        | BindingFlag.TYPE_CLASS
        | BindingFlag.TYPE_CATCH_PARAM
        | BindingFlag.TYPE_FUNCTION
        | BindingFlag.TYPE_TS_INTERFACE
        | BindingFlag.TYPE_TS_TYPE
        | BindingFlag.TYPE_TS_TYPE_IMPORT
        | BindingFlag.TYPE_TS_VALUE_IMPORT
        | BindingFlag.TYPE_TS_ENUM
        | BindingFlag.TYPE_TS_AMBIENT
        | BindingFlag.TYPE_TS_NAMESPACE
        | BindingFlag.TYPE_TS_CONST_ENUM
        | BindingFlag.TYPE_FLOW_DECLARE_FN;
    */
    typedef BindingFlag BindingTypes;


    const enum ClassElementType {
        OTHER           = 0,
        FLAG_STATIC     = 0b100,
        KIND_GETTER     = 0b010,
        KIND_SETTER     = 0b001,
        KIND_ACCESSOR   = KIND_GETTER | KIND_SETTER,

        STATIC_GETTER   = FLAG_STATIC | KIND_GETTER,
        STATIC_SETTER   = FLAG_STATIC | KIND_SETTER,
        INSTANCE_GETTER = KIND_GETTER,
        INSTANCE_SETTER = KIND_SETTER,
    };

}

#endif // BABEL_PARSER_util_scopeflags_H_