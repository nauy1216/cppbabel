#ifndef BABEL_PARSER_types_H_
#define BABEL_PARSER_types_H_
#include <string>
#include <variant>
#include <vector>
#include <tuple>
#include <map>
#include <any>
#include "babel-parser/options.h"
#include "babel-parser/util_location.h"

using namespace std;
// import type { Token } from "./tokenizer/index.ts";
// import type { PlaceholderTypes } from "./plugins/placeholders.ts";
// import type { ParseError } from "./parse-error.ts";
// TODO
struct ParseError;

namespace types
{
    /*
     * If making any changes to the AST, update:
     * - This repository:
     *   - This file
     *   - `ast` directory
     * - Babel repository:
     *   - packages/babel-types/src/definitions
     *   - packages/babel-generators/src/generators
     */
    struct Node;
    struct Identifier;
    struct ObjectPattern;
    struct ArrayPattern;
    struct RestElement;
    struct AssignmentPattern;
    struct VariableDeclaration;
    struct ClassDeclaration;
    struct FunctionDeclaration;
    struct TsInterfaceDeclaration;
    struct TsTypeAliasDeclaration;
    struct TsEnumDeclaration;
    struct TsModuleDeclaration;
    struct Decorator;
    struct PatternBase;
    struct RegExpLiteral;
    struct NullLiteral;
    struct StringLiteral;
    struct BooleanLiteral;
    struct NumericLiteral;
    struct BigIntLiteral;
    struct DecimalLiteral;
    struct Token;
    struct Program;
    struct BlockStatement;
    struct ModuleDeclaration;
    struct Directive;
    struct ArrowFunctionExpression;
    struct ObjectMethod;
    struct ClassMethod;
    struct FunctionExpression;
    struct HasDecorators;
    struct TSParameterProperty;
    struct TypeParameterDeclarationBase;
    struct TypeAnnotationBase;
    struct ForInOf;
    struct ForInStatement;
    struct ForOfStatement;
    struct ObjectMember;
    struct FlowVariance;
    struct PipelineBareFunction;
    struct PipelineBareConstructor;
    struct PipelineBareAwaitedFunction;
    struct PipelineTopicExpression;
    struct FlowClassImplements;
    struct ClassMember;
    struct TsIndexSignature;
    struct ClassAccessorProperty;
    struct TSDeclareMethod;
    struct ImportDeclaration;
    struct ExportNamedDeclaration;
    struct ExportDefaultDeclaration;
    struct ExportAllDeclaration;
    struct OptTSDeclareFunction;
    struct FlowTypeAnnotation;

    /**
     * CommentBlock | CommentLine
     */
    typedef string CommentBaseType;

    struct CommentBase
    {
        CommentBaseType type;
        string value;
        int start;
        int end;
        util_location::SourceLocation *loc;
    };

    struct CommentBlock : CommentBase
    {
        string type = "CommentBlock";
    };

    struct CommentLine : CommentBase
    {
        string type = "CommentLine";
    };

    typedef variant<CommentBlock, CommentLine> Comment;

    // A whitespace containing comments
    struct CommentWhitespace
    {
        int start;
        int end;
        vector<Comment> comments;
        Node *leadingNode;
        Node *trailingNode;
        Node *containerNode;
    };

    struct NodeBase
    {
        int start;
        int end;
        util_location::SourceLocation *loc;
        tuple<int, int> range;
        vector<Comment *> *leadingComments;
        vector<Comment *> *trailingComments;
        vector<Comment *> *innerComments;
        map<string, std::any> *extra;
    };

    // Using a union type for `Node` makes type-checking too slow.
    // Instead, add an index signature to allow a Node to be treated as anything.
    // todo(flow->ts): this probably should be replaced with union
    struct Node : NodeBase
    {
        string type;
        //   [key: string]: any;
    };

    typedef Node Expression;
    typedef Node Statement;
    typedef variant<
        Identifier *,
        ObjectPattern *,
        ArrayPattern *,
        RestElement *,
        AssignmentPattern *>
        Pattern;

    typedef variant<VariableDeclaration *,
                    ClassDeclaration *,
                    FunctionDeclaration *,
                    TsInterfaceDeclaration *,
                    TsTypeAliasDeclaration *,
                    TsEnumDeclaration *,
                    TsModuleDeclaration *>
        Declaration;

    struct DeclarationBase : NodeBase
    {
        // TypeScript allows declarations to be prefixed by `declare`.
        // TODO: a FunctionDeclaration is never "declare", because it's a TSDeclareFunction instead.
        bool declare;
    };

    // TODO: Not in spec
    struct HasDecorators : NodeBase
    {
        vector<Decorator *> *decorators;
    };

    struct InterpreterDirective : NodeBase
    {
        string type = "InterpreterDirective";
        string value;
    };

    // TODO
    //  struct Identifier : PatternBase {
    struct Identifier
    {
        string type = "Identifier";
        string name;
        // @deprecated
        Identifier __clone();
        // TypeScript only. Used in case of an optional parameter.
        bool optional;
    };
    // | Placeholder<"Identifier">;

    struct PrivateName : NodeBase
    {
        string type = "PrivateName";
        Identifier *id;
    };

    // Literals
    typedef variant<RegExpLiteral *,
                    NullLiteral *,
                    StringLiteral *,
                    BooleanLiteral *,
                    NumericLiteral *,
                    BigIntLiteral *,
                    DecimalLiteral *>
        Literal;

    /**
     * "g" | "i" | "m" | "u" | "s" | "y" | "v"
     */
    typedef string RegExpFlag;

    struct RegExpLiteral : NodeBase
    {
        string type = "RegExpLiteral";
        string pattern;
        vector<RegExpFlag> *flags;
    };

    struct NullLiteral : NodeBase
    {
        string type = "NullLiteral";
    };

    struct StringLiteral : NodeBase
    {
        string type = "StringLiteral";
        string value;
    };

    struct BooleanLiteral : NodeBase
    {
        string type = "BooleanLiteral";
        bool value;
    };

    struct NumericLiteral : NodeBase
    {
        string type = "NumericLiteral";
        int value;
    };

    struct BigIntLiteral : NodeBase
    {
        string type = "BigIntLiteral";
        int value;
    };

    struct DecimalLiteral : NodeBase
    {
        string type = "DecimalLiteral";
        int value;
    };

    struct ParserOutput
    {
        vector<Comment> *comments;
        vector<ParseError> *errors;
        vector<variant<Token *, Comment *>> tokens;
    };
    // Programs

    typedef variant<Program *, BlockStatement *> BlockStatementLike;
    // export type BlockStatementLike = Program | BlockStatement;

    struct File : NodeBase, ParserOutput
    {
        string type = "File";
        Program *program;
    };

    struct Program : NodeBase
    {
        string type = "Program";
        options::SourceType sourceType = "";
        vector<Statement *, ModuleDeclaration *> body; // TODO: $ReadOnlyArray,
        vector<Directive *> *directives = nullptr;     // TODO: Not in spec,
        InterpreterDirective *interpreter = nullptr;
    };

    // Functions
    typedef variant<NormalFunction *,
                    ArrowFunctionExpression *, ObjectMethod *,
                    ClassMethod *>
        Function;

    typedef variant<FunctionDeclaration *, FunctionExpression *> NormalFunction;

    struct BodilessFunctionOrMethodBase : HasDecorators
    {
        // TODO: Remove this. Should not assign "id" to methods.
        // https://github.com/babel/babylon/issues/535
        Identifier *id;
        vector<variant<Pattern *, TSParameterProperty *>> *params;
        bool generator;
        bool async;
        // TODO: All not in spec
        bool expression;
        TypeParameterDeclarationBase *typeParameters;
        TypeAnnotationBase *returnType;
    };

    struct FunctionBase : BodilessFunctionOrMethodBase
    {
        BlockStatement *body;
    };

    // Statements

    struct ExpressionStatement : NodeBase
    {
        string type = "ExpressionStatement";
        Expression *expression;
    };

    struct BlockStatement : NodeBase
    {
        string type = "BlockStatement";
        vector<Statement *> *body; // TODO: $ReadOnlyArray,
        vector<Directive *> *directives;
    };
    // | Placeholder<"BlockStatement">;

    struct EmptyStatement : NodeBase
    {
        string type = "EmptyStatement";
    };

    struct DebuggerStatement : NodeBase
    {
        string type = "DebuggerStatement";
    };

    struct WithStatement : NodeBase
    {
        string type = "WithStatement";
        Expression *object;
        Statement *body;
    };

    struct ReturnStatement : NodeBase
    {
        string type = "ReturnStatement";
        Expression *argument;
    };

    struct LabeledStatement : NodeBase
    {
        string type = "LabeledStatement";
        Identifier *label;
        Statement *body;
    };

    struct BreakStatement : NodeBase
    {
        string type = "BreakStatement";
        Identifier *label;
    };

    struct ContinueStatement : NodeBase
    {
        string type = "ContinueStatement";
        Identifier *label;
    };

    // Choice

    struct IfStatement : NodeBase
    {
        string type = "IfStatement";
        Expression *test;
        Statement *consequent;
        Statement *alternate;
    };

    struct SwitchStatement : NodeBase
    {
        string type = "SwitchStatement";
        Expression *discriminant;
        vector<SwitchCase *> *cases;
    };

    struct SwitchCase : NodeBase
    {
        string type = "SwitchCase";
        Expression *test;
        vector<Statement *> consequent;
    };

    // Exceptions

    struct ThrowStatement : NodeBase
    {
        string type = "ThrowStatement";
        Expression *argument;
    };

    struct TryStatement : NodeBase
    {
        string type = "TryStatement";
        BlockStatement *block;
        CatchClause *handler;
        BlockStatement *finalizer;
    };

    struct CatchClause : NodeBase
    {
        string type = "CatchClause";
        Pattern *param;
        BlockStatement *body;
    };

    // Loops

    struct WhileStatement : NodeBase
    {
        string type = "WhileStatement";
        Expression *test;
        Statement *body;
    };

    struct DoWhileStatement : NodeBase
    {
        string type = "DoWhileStatement";
        Statement *body;
        Expression *test;
    };

    typedef variant<ForStatement *, ForInOf *> ForLike;
    // export type ForLike = ForStatement | ForInOf;

    struct ForStatement : NodeBase
    {
        string type = "ForStatement";
        variant<VariableDeclaration *, Expression *> *init;
        Expression *test;
        Expression *update;
        Statement *body;
    };

    typedef variant<ForInStatement *, ForOfStatement *> ForInOf;
    // export type ForInOf = ForInStatement | ForOfStatement;

    struct ForInOfBase : NodeBase
    {
        variant<VariableDeclaration *, Expression *> *left;
        Expression *right;
        Statement *body;
    };

    struct ForInStatement : ForInOfBase
    {
        string type = "ForInStatement";
        // TODO: Shouldn't be here, but have to declare it because it's assigned to a ForInOf unconditionally.
        bool await;
    };

    struct ForOfStatement : ForInOfBase
    {
        string type = "ForOfStatement";
        bool await;
    };

    // Declarations

    struct OptFunctionDeclaration : FunctionBase, DeclarationBase
    {
        string type = "FunctionDeclaration";
    };

    struct FunctionDeclaration : OptFunctionDeclaration
    {
        Identifier *id;
    };

    /**
     *  "var" | "let" | "const" | "using" | "await using"
     */
    typedef string VariableDeclarationType;
    struct VariableDeclaration : DeclarationBase, HasDecorators
    {
        string type = "VariableDeclaration";
        vector<VariableDeclarator *> *declarations;
        VariableDeclarationType kind;
    };

    struct VariableDeclarator : NodeBase
    {
        string type = "VariableDeclarator";
        Pattern *id;
        Expression *init;
        // TypeScript only:
        bool definite;
    };

    // Misc

    struct ArgumentPlaceholder : NodeBase
    {
        string type = "ArgumentPlaceholder";
    };

    struct Decorator : NodeBase
    {
        string type = "Decorator";
        Expression *expression;
        vector<Expression *, SpreadElement *> *arguments;
    };

    struct Directive : NodeBase
    {
        string type = "Directive";
        DirectiveLiteral *value;
    };

    struct DirectiveLiteral : NodeBase
    {
        string type = "DirectiveLiteral";
        string value;
    };

    struct ImportAttribute : NodeBase
    {
        string type = "ImportAttribute";
        variant<Identifier *, StringLiteral *> *key;
        StringLiteral *value;
    };

    // Expressions

    struct Super : NodeBase
    {
        string type = "Super";
    };

    struct Import : NodeBase
    {
        string type = "Import";
    };

    struct ThisExpression : NodeBase
    {
        string type = "ThisExpression";
    };

    struct ArrowFunctionExpression : BodilessFunctionOrMethodBase
    {
        string type = "ArrowFunctionExpression";
        variant<BlockStatement *, Expression *> *body;
    };

    struct YieldExpression : NodeBase
    {
        string type = "YieldExpression";
        Expression *argument;
        bool delegate;
    };

    struct AwaitExpression : NodeBase
    {
        string type = "AwaitExpression";
        Expression *argument;
    };

    struct ArrayExpression : NodeBase
    {
        string type = "ArrayExpression";
        vector<variant<Expression *, SpreadElement *>> *elements;
    };

    struct DoExpression : NodeBase
    {
        string type = "DoExpression";
        BlockStatement *body;
        bool async;
    };

    struct TupleExpression : NodeBase
    {
        string type = "TupleExpression";
        vector<variant<Expression *, SpreadElement *>> *elements;
    };

    struct ObjectExpression : NodeBase
    {
        string type = "ObjectExpression";
        vector<variant<ObjectProperty *, ObjectMethod *, SpreadElement *>> *properties;
    };

    struct RecordExpression : NodeBase
    {
        string type = "RecordExpression";
        vector<variant<ObjectProperty *, ObjectMethod *, SpreadElement *>> *properties;
    };

    typedef variant<ClassMethod *, ClassProperty *, ObjectMember *> ObjectOrClassMember;

    typedef variant<ObjectProperty *, ObjectMethod *> ObjectMember;

    /**
     * "get" | "set" | "method"
     */
    typedef string ObjectMemberBasekind;

    struct ObjectMemberBase : NodeBase
    {
        Expression *key;
        bool computed;
        variant<Expression *, Pattern *> *value;
        vector<Decorator *> *decorators;
        ObjectMemberBasekind kind;
        bool method;                                  // TODO: Not in spec,
        TypeParameterDeclarationBase *typeParameters; // TODO: Not in spec,
        FlowVariance *variance;                       // TODO: Not in spec
    };

    struct ObjectProperty : ObjectMemberBase
    {
        string type = "ObjectProperty";
        bool shorthand;
        variant<Expression *, Pattern *> *value;
    };

    struct ObjectMethod : ObjectMemberBase, FunctionBase
    {
        string type = "ObjectMethod";
        string kind; //: "get" | "set" | "method"; // Never "constructor"
        Expression *value;
    };

    struct FunctionExpression : FunctionBase
    {
        string kind = ""; // never set,
        string type = "FunctionExpression";
    };

    // Unary operations

    struct UnaryExpression : NodeBase
    {
        string type = "UnaryExpression";
        UnaryOperator operator_;
        bool prefix;
        Expression *argument;
    };

    /**
     *| "-"
      | "+"
      | "!"
      | "~"
      | "typeof"
      | "void"
      | "delete"
      | "throw";
    */
    typedef string UnaryOperator;

    struct UpdateExpression : NodeBase
    {
        string type = "UpdateExpression";
        UpdateOperator operator_;
        Expression *argument;
        bool prefix;
    };

    /**
     * "++" | "--"
     */
    typedef string UpdateOperator;

    // Binary operations

    struct BinaryExpression : NodeBase
    {
        string type = "BinaryExpression";
        BinaryOperator operator_;
        Expression *left;
        Expression *right;
    };

    /**
     *   | "=="
      | "!="
      | "==="
      | "!=="
      | "<"
      | "<="
      | ">"
      | ">="
      | "<<"
      | ">>"
      | ">>>"
      | "+"
      | "-"
      | "*"
      | "/"
      | "%"
      | "|"
      | "^"
      | "&"
      | "in"
      | "instanceof";
    */
    typedef string BinaryOperator;

    struct AssignmentExpression : NodeBase
    {
        string type = "AssignmentExpression";
        AssignmentOperator operator_;
        variant<Pattern *, Expression *> *left;
        Expression *right;
    };

    /**
     *| "="
      | "+="
      | "-="
      | "*="
      | "/="
      | "%="
      | "<<="
      | ">>="
      | ">>>="
      | "|="
      | "^="
      | "&=";
    */
    typedef string AssignmentOperator;

    struct LogicalExpression : NodeBase
    {
        string type = "LogicalExpression";
        LogicalOperator operator_;
        Expression *left;
        Expression *right;
    };

    /**
     * "||" | "&&"
     */
    typedef string LogicalOperator;

    struct SpreadElement : NodeBase
    {
        string type = "SpreadElement";
        Expression *argument;
    };

    struct MemberExpression : NodeBase
    {
        string type = "MemberExpression";
        variant<Expression *, Super *> *object;
        Expression *property;
        bool computed;
    };

    struct OptionalMemberExpression : NodeBase
    {
        string type = "OptionalMemberExpression";
        variant<Expression *, Super *> *object;
        Expression *property;
        bool computed;
        bool optional;
    };

    struct OptionalCallExpression : CallOrNewBase
    {
        string type = "OptionalCallExpression";
        bool optional;
    };

    struct BindExpression : NodeBase
    {
        string type = "BindExpression";
        vector<Expression *> *object;
        vector<Expression *> *callee;
    };

    struct ConditionalExpression : NodeBase
    {
        string type = "ConditionalExpression";
        Expression *test;
        Expression *alternate;
        Expression *consequent;
    };

    struct CallOrNewBase : NodeBase
    {
        variant<Expression *, Super *, Import *> *callee;
        vector<Expression *, SpreadElement *> *arguments; // TODO: $ReadOnlyArray,
        TypeParameterInstantiationBase *typeArguments;
        TypeParameterInstantiationBase *typeParameters; // TODO: Not in spec
    };

    struct CallExpression : CallOrNewBase
    {
        string type = "CallExpression";
    };

    struct NewExpression : CallOrNewBase
    {
        string type = "NewExpression";
        bool optional; // TODO: Not in spec
    };

    struct ImportExpression : NodeBase
    {
        string type = "ImportExpression";
        Expression *source;
        string phase; //?: null | "source" | "defer";
        Expression *options;
    };

    struct SequenceExpression : NodeBase
    {
        string type = "SequenceExpression";
        vector<Expression *> *expressions;
    };

    struct ParenthesizedExpression : NodeBase
    {
        string type = "ParenthesizedExpression";
        Expression *expression;
    };

    // Hack pipe operator

    struct TopicReference : NodeBase
    {
        string type = "TopicReference";
    };

    // Smart-mix pipe operator

    struct PipelineBody : NodeBase
    {
        string type = "PipelineBody";
    };

    struct PipelineBareFunctionBody : NodeBase
    {
        string type = "PipelineBareFunctionBody";
        Expression *callee;
    };

    struct PipelineBareConstructorBody : NodeBase
    {
        string type = "PipelineBareConstructorBody";
        Expression *callee;
    };

    struct PipelineBareAwaitedFunctionBody : NodeBase
    {
        string type = "PipelineBareAwaitedFunctionBody";
        Expression *callee;
    };

    struct PipelineTopicBody : NodeBase
    {
        string type = "PipelineTopicBody";
        Expression *expression;
    };

    typedef variant<PipelineBareFunction *,
                    PipelineBareConstructor *,
                    PipelineBareAwaitedFunction *,
                    PipelineTopicExpression *>
        PipelineStyle;

    struct PipelinePrimaryTopicReference : NodeBase
    {
        string type = "PipelinePrimaryTopicReference";
    };

    // Template Literals

    struct TemplateLiteral : NodeBase
    {
        string type = "TemplateLiteral";
        vector<TemplateElement *> *quasis;
        vector<Expression *> *expressions;
    };

    struct TaggedTemplateExpression : NodeBase
    {
        string type = "TaggedTemplateExpression";
        Expression *tag;
        TemplateLiteral *quasi;
        TypeParameterInstantiationBase *typeParameters; // TODO: Not in spec
    };

    struct TemplateElementValue
    {
        string cooked;
        string raw;
    };

    struct TemplateElement : NodeBase
    {
        string type = "TemplateElement";
        bool tail;
        TemplateElementValue *value;
    };

    struct ModuleExpression : NodeBase
    {
        string type = "ModuleExpression";
        Program *body;
    };

    // Patterns
    // TypeScript access modifiers
    /**
     * "public" | "protected" | "private"
     */
    typedef string Accessibility;

    /**
     * "in" | "out"
     */
    typedef string VarianceAnnotations;

    struct PatternBase : HasDecorators
    {
        // TODO: All not in spec
        // Flow/TypeScript only:
        TypeAnnotationBase *typeAnnotation;
    };

    struct AssignmentProperty : ObjectProperty
    {
        Pattern *value;
    };

    struct ObjectPattern : PatternBase
    {
        string type = "ObjectPattern";
        vector<variant<AssignmentProperty *, RestElement *>> *properties; // (AssignmentProperty | RestElement)[];
    };

    struct ArrayPattern : PatternBase
    {
        string type = "ArrayPattern";
        vector<Pattern *> *elements;
    };

    struct RestElement : PatternBase
    {
        string type = "RestElement";
        Pattern *argument;
    };

    struct AssignmentPattern : PatternBase
    {
        string type = "AssignmentPattern";
        Pattern *left;
        Expression *right;
    };

    // Classes
    typedef variant<ClassDeclaration, ClassExpression> Class;
    // export type Class = ClassDeclaration | ClassExpression;

    struct ClassBase : HasDecorators
    {
        Identifier *id;
        Expression *superClass;
        ClassBody *body;
        vector<Decorator *> *decorators;
        // TODO: All not in spec
        TypeParameterDeclarationBase *typeParameters;
        TypeParameterInstantiationBase *superTypeParameters;
        bool abstract;
        variant<vector<TsExpressionWithTypeArguments *>, vector<FlowClassImplements *>> implements;
    };

    struct ClassBody : NodeBase
    {
        string type = "ClassBody";
        variant<ClassMember *, StaticBlock *, TsIndexSignature *> body; // TODO: $ReadOnlyArray
    };
    // | Placeholder<"ClassBody">;

    struct ClassMemberBase : NodeBase, HasDecorators
    {
        bool static_;
        bool computed;
        // TypeScript only:
        Accessibility accessibility;
        bool override;
        bool abstract;
        bool optional;
    };

    struct StaticBlock : NodeBase
    {
        string type = "StaticBlock";
        vector<Statement *> *body;
    };

    typedef variant<ClassMethod *,
                    ClassPrivateMethod *,
                    ClassProperty *,
                    ClassPrivateProperty *,
                    ClassAccessorProperty *>
        ClassMember;

    typedef variant<ObjectMethod *,
                    FunctionExpression *,
                    ClassMethod *,
                    ClassPrivateMethod *,
                    TSDeclareMethod *>
        MethodLike;

    // export type MethodLike =
    //   | ObjectMethod
    //   | FunctionExpression
    //   | ClassMethod
    //   | ClassPrivateMethod
    //   | TSDeclareMethod;

    struct MethodBase : FunctionBase
    {
        MethodKind kind;
    };

    /**
     *  "constructor" | "method" | "get" | "set"
     */
    typedef string MethodKind;
    // export type MethodKind = "constructor" | "method" | "get" | "set";

    struct ClassMethodOrDeclareMethodCommon : ClassMemberBase
    {
        Expression *key;
        MethodKind kind;
        bool static_;
        vector<Decorator *> *decorators;
    };

    struct ClassMethod
        : MethodBase,
          ClassMethodOrDeclareMethodCommon
    {
        string type = "ClassMethod";
        FlowVariance *variance; // TODO: Not in spec
    };

    struct ClassPrivateMethod
        : NodeBase,
          ClassMethodOrDeclareMethodCommon,
          MethodBase
    {
        string type = "ClassPrivateMethod";
        PrivateName *key;
        bool computed;
        FlowVariance *variance; // TODO: Not in spec
    };

    struct ClassProperty : ClassMemberBase, DeclarationBase
    {
        string type = "ClassProperty";
        Expression *key;
        Expression *value;                  // TODO: Not in spec that this is nullable.,
        TypeAnnotationBase *typeAnnotation; // TODO: Not in spec,
                                            // Flow only:
        FlowVariance *variance;             // TODO: Not in spec,
                                            // TypeScript only: (TODO: Not in spec)
        bool readonly;
        bool definite;
    };

    struct ClassPrivateProperty : NodeBase
    {
        string type = "ClassPrivateProperty";
        PrivateName key;
        Expression *value; // TODO: Not in spec that this is nullable.,
        bool static_;
        bool computed;
        // Flow and Typescript
        TypeAnnotationBase *typeAnnotation;
        // TypeScript only
        bool optional;
        bool definite;
        bool readonly;
        bool override;
        // Flow only
        FlowVariance *variance;
    };

    struct ClassAccessorProperty
        : ClassMemberBase,
          DeclarationBase
    {
        string type = "ClassAccessorProperty";
        variant<Expression *, PrivateName *> key;
        Expression *value;
        TypeAnnotationBase *typeAnnotation; // TODO: Not in spec,
        FlowVariance *variance;             // TODO: Not in spec,
                                            // TypeScript only: (TODO: Not in spec)
        bool readonly;
        bool definite;
    };

    struct OptClassDeclaration
        : ClassBase,
          DeclarationBase,
          HasDecorators
    {
        string type = "ClassDeclaration";
        // TypeScript only
        bool abstract;
    };

    struct ClassDeclaration : OptClassDeclaration
    {
        Identifier *id;
    };

    struct ClassExpression : ClassBase
    {
        string type = "ClassExpression";
    };

    struct MetaProperty : NodeBase
    {
        string type = "MetaProperty";
        Identifier *meta;
        Identifier *property;
    };

    // Modules
    typedef variant<AnyImport *, AnyExport *> ModuleDeclaration;
    // export type ModuleDeclaration = AnyImport | AnyExport;

    typedef variant<ImportDeclaration *, TsImportEqualsDeclaration *> AnyImport;
    // export type AnyImport = ImportDeclaration | TsImportEqualsDeclaration;

    typedef variant<ExportNamedDeclaration *,
                    ExportDefaultDeclaration *,
                    ExportAllDeclaration *,
                    TsExportAssignment *,
                    TsImportEqualsDeclaration *,
                    TsNamespaceExportDeclaration *>
        AnyExport;
    // export type AnyExport =
    //   | ExportNamedDeclaration
    //   | ExportDefaultDeclaration
    //   | ExportAllDeclaration
    //   | TsExportAssignment
    //   | TsImportEqualsDeclaration
    //   | TsNamespaceExportDeclaration;

    struct ModuleSpecifier : NodeBase
    {
        Identifier *local;
    };

    // Imports

    struct ImportDeclaration : NodeBase
    {
        string type = "ImportDeclaration";
        // TODO: $ReadOnlyArray
        vector<variant<ImportSpecifier *, ImportDefaultSpecifier *, ImportNamespaceSpecifier *>> specifiers;
        //   specifiers: Array<
        //     ImportSpecifier | ImportDefaultSpecifier | ImportNamespaceSpecifier
        //   >;

        Literal *source;
        /**
         * "type" | "typeof" | "value"
         */
        string importKind; // TODO: Not in spec,

        /**
         * null | "source" | "defer"
         */
        string phase;
        vector<ImportAttribute *> *attributes;
        // @deprecated
        vector<ImportAttribute *> *assertions;
        bool module;
    };

    struct ImportSpecifier : ModuleSpecifier
    {
        string type = "ImportSpecifier";
        variant<Identifier *, StringLiteral *> *imported;
        /**
         * "type" | "value"
         */
        string importKind;
    };

    struct ImportDefaultSpecifier : ModuleSpecifier
    {
        string type = "ImportDefaultSpecifier";
    };

    struct ImportNamespaceSpecifier : ModuleSpecifier
    {
        string type = "ImportNamespaceSpecifier";
    };

    // Exports

    struct ExportNamedDeclaration : NodeBase
    {
        string type = "ExportNamedDeclaration";
        Declaration *declaration;
        vector<ExportSpecifier *, ExportDefaultSpecifier *> *specifiers;
        Literal *source;
        /**
         * "type" | "value"
         */
        string exportKind; // TODO: Not in spec,
        vector<ImportAttribute *> *attributes;
        // @deprecated
        vector<ImportAttribute *> *assertions;
    };

    struct ExportSpecifier : NodeBase
    {
        string type = "ExportSpecifier";
        variant<Identifier *, StringLiteral *> exported;
        Identifier *local;
        /**
         * "type" | "value"
         */
        string exportKind;
    };

    struct ExportDefaultSpecifier : NodeBase
    {
        string type = "ExportDefaultSpecifier";
        Identifier *exported;
    };

    struct ExportDefaultDeclaration : NodeBase
    {
        string type = "ExportDefaultDeclaration";
        variant<OptFunctionDeclaration *, OptTSDeclareFunction *, OptClassDeclaration *, Expression *> *declaration;
    };

    struct ExportAllDeclaration : NodeBase
    {
        string type = "ExportAllDeclaration";
        Literal *source;
        /**
         * "type" | "value"
         */
        string exportKind; // TODO: Not in spec,
        vector<ImportAttribute *> *assertions;
    };

    struct PipelineTopicExpression : NodeBase
    {
        string type = "PipelineTopicExpression";
        Expression *expression;
    };

    struct PipelineBareFunction : NodeBase
    {
        string type = "PipelineBareFunction";
        Expression *callee;
    };

    // JSX (TODO: Not in spec)
    typedef Node JSXIdentifier;
    typedef Node JSXNamespacedName;
    typedef Node JSXMemberExpression;
    typedef Node JSXEmptyExpression;
    typedef Node JSXSpreadChild;
    typedef Node JSXExpressionContainer;
    typedef Node JSXAttribute;

    struct JSXOpeningElement : NodeBase
    {
        string type = "JSXOpeningElement";
        variant<JSXNamespacedName *, JSXMemberExpression *> name;
        TypeParameterInstantiationBase *typeParameters; // TODO: Not in spec,
        vector<JSXAttribute *> *attributes;
        bool selfClosing;
    };

    typedef Node JSXClosingElement;
    typedef Node JSXElement;
    typedef Node JSXOpeningFragment;
    typedef Node JSXClosingFragment;
    typedef Node JSXFragment;

    // Flow/TypeScript common (TODO: Not in spec)

    struct TypeAnnotationBase : NodeBase
    {
        Node *typeAnnotation;
    };

    struct TypeAnnotation : NodeBase
    {
        string type = "TypeAnnotation";
        FlowTypeAnnotation *typeAnnotation;
    };

    struct TsTypeAnnotation : NodeBase
    {
        string type = "TSTypeAnnotation";
        TsType typeAnnotation;
    };

    struct TypeParameterDeclarationBase : NodeBase
    {
        vector<variant<TypeParameter *, TsTypeParameter *>> params;
    };

    struct TypeParameterDeclaration : TypeParameterDeclarationBase
    {
        string type = "TypeParameterDeclaration";
        vector<TypeParameter *> *params;
    };

    struct TsTypeParameterDeclaration
        : TypeParameterDeclarationBase
    {
        string type = "TSTypeParameterDeclaration";
        vector<TsTypeParameter *> *params;
    };

    struct TypeParameter : NodeBase
    {
        string type = "TypeParameter";
        string name;
        TypeAnnotation *default_;
    };

    struct TsTypeParameter : NodeBase
    {
        string type = "TSTypeParameter";
        // TODO(Babel 8): remove string type support
        variant<string, Identifier *> name;
        bool in;
        bool out;
        bool const_;
        TsType constraint;
        TsType default_;
    };

    struct TypeParameterInstantiationBase : NodeBase
    {
        vector<Node *> *params;
    };

    struct TypeParameterInstantiation
        : TypeParameterInstantiationBase
    {
        string type = "TypeParameterInstantiation";
        vector<FlowType> params;
    };

    struct TsTypeParameterInstantiation
        : TypeParameterInstantiationBase
    {
        string type = "TSTypeParameterInstantiation";
        vector<FlowType> params;
    };

    // Flow (TODO: Not in spec)

    struct TypeCastExpressionBase : NodeBase
    {
        Expression *expression;
        TypeAnnotationBase *typeAnnotation;
    };

    struct TypeCastExpression : NodeBase
    {
        string type = "TypeCastExpression";
        Expression *expression;
        TypeAnnotation *typeAnnotation;
    };

    struct TsTypeCastExpression : NodeBase
    {
        string type = "TSTypeCastExpression";
        Expression *expression;
        TsTypeAnnotation *typeAnnotation;
    };

    typedef Node FlowType;
    typedef Node FlowPredicate;
    typedef Node FlowDeclare;
    typedef Node FlowDeclareClass;
    typedef Node FlowDeclareExportDeclaration;
    typedef Node FlowDeclareFunction;
    typedef Node FlowDeclareVariable;
    typedef Node FlowDeclareModule;
    typedef Node FlowDeclareModuleExports;
    typedef Node FlowDeclareTypeAlias;
    typedef Node FlowDeclareOpaqueType;
    typedef Node FlowDeclareInterface;
    typedef Node FlowInterface;
    typedef Node FlowInterfaceExtends;
    typedef Node FlowTypeAlias;
    typedef Node FlowOpaqueType;
    typedef Node FlowObjectTypeIndexer;
    typedef Node FlowObjectTypeInternalSlot;
    typedef Node FlowFunctionTypeAnnotation;
    typedef Node FlowObjectTypeProperty;
    typedef Node FlowObjectTypeSpreadProperty;
    typedef Node FlowObjectTypeCallProperty;
    typedef Node FlowObjectTypeAnnotation;
    typedef Node FlowQualifiedTypeIdentifier;
    typedef Node FlowGenericTypeAnnotation;
    typedef Node FlowTypeofTypeAnnotation;
    typedef Node FlowTupleTypeAnnotation;
    typedef Node FlowFunctionTypeParam;
    typedef Node FlowTypeAnnotation;
    typedef Node FlowVariance;
    typedef Node FlowClassImplements;

    struct FlowInterfaceType : NodeBase
    {
        string type = "InterfaceTypeAnnotation";
        vector<FlowInterfaceExtends *> *extends;
        FlowObjectTypeAnnotation *body;
    };

    struct FlowIndexedAccessType : NodeBase
    {
        string type = "IndexedAccessType";
        FlowType objectType;
        FlowType indexType;
    };

    struct FlowOptionalIndexedAccessType : NodeBase
    {
        string type = "OptionalIndexedAccessType";
        FlowType objectType;
        FlowType indexType;
        bool optional;
    };

    struct StringLiteralTypeAnnotation : NodeBase
    {
        string type = "StringLiteralTypeAnnotation";
        string value;
    };

    struct BooleanLiteralTypeAnnotation : NodeBase
    {
        string type = "BooleanLiteralTypeAnnotation";
        bool value;
    };

    struct NumberLiteralTypeAnnotation : NodeBase
    {
        string type = "NumberLiteralTypeAnnotation";
        int value;
    };

    struct BigIntLiteralTypeAnnotation : NodeBase
    {
        string type = "BigIntLiteralTypeAnnotation";
        // todo(flow): use bigint when Flow supports BigInt
        int value;
    };

    // ESTree
    struct EstreeLiteral : NodeBase
    {
        string type = "Literal";
        any value;
    };

    struct EstreeRegExpLiteralRegex
    {
        string pattern;
        string flags;
    };

    struct EstreeRegExpLiteral : EstreeLiteral
    {
        EstreeRegExpLiteralRegex *regex;
    };

    struct EstreeBigIntLiteral : EstreeLiteral
    {
        int value;
        string bigint;
    };

    struct EstreeProperty : NodeBase
    {
        string type = "Property";
        bool shorthand;
        Expression *key;
        bool computed;
        Expression *value;
        vector<Decorator *> *decorators;
        /**
         * "get" | "set" | "init"
         */
        string kind;
        FlowVariance *variance;
    };

    struct EstreeMethodDefinition : NodeBase
    {
        string type = "MethodDefinition";
        bool static_;
        Expression *key;
        bool computed;
        Expression *value;
        vector<Decorator *> *decorators;
        /**
         * "get" | "set" | "method"
         */
        string kind;
        FlowVariance *variance;
    };

    struct EstreeImportExpression : NodeBase
    {
        string type = "ImportExpression";
        Expression *source;
        Expression *options;
        /**
         * @deprecated Use options instead
         */
        Expression *attributes;
    };

    struct EstreePrivateIdentifier : NodeBase
    {
        string type = "PrivateIdentifier";
        string name;
    };

    struct EstreePropertyDefinition : NodeBase
    {
        string type = "PropertyDefinition";
        bool static_;
        variant<Expression *, EstreePrivateIdentifier *> key;
        bool computed;
        Expression *value;
    };

    // === === === ===
    // TypeScript
    // === === === ===

    // Note: A type named `TsFoo` is based on TypeScript's `FooNode` type,
    // defined in https://github.com/Microsoft/TypeScript/blob/master/src/compiler/types.ts
    // Differences:
    // * Change `NodeArray<T>` to just `$T[]`.
    // * Don't give nodes a "modifiers" list; use boolean flags instead,
    //   and only allow modifiers that are not considered errors.
    // * A property named `type` must be renamed to `typeAnnotation` to avoid conflict with the node's type.
    // * Sometimes TypeScript allows to parse something which will be a grammar error later;
    //   in @babel/parser these cause exceptions, so the AST format is stricter.

    // ================
    // Misc
    // ================

    struct TSParameterProperty : HasDecorators
    {
        // Note: This has decorators instead of its parameter.
        string type = "TSParameterProperty";
        // At least one of `accessibility` or `readonly` must be set.
        Accessibility accessibility;
        bool readonly;
        bool override;
        variant<Identifier *, AssignmentPattern *> *parameter;
    };

    struct OptTSDeclareFunction : FunctionBase, DeclarationBase
    {
        string type = "TSDeclareFunction";
    };

    struct TSDeclareFunction : OptTSDeclareFunction
    {
        Identifier id;
    };

    struct TSDeclareMethod
        : FunctionBase,
          ClassMethodOrDeclareMethodCommon
    {
        string type = "TSDeclareMethod";
        MethodKind kind;
    };

    struct TsQualifiedName : NodeBase
    {
        string type = "TSQualifiedName";
        TsEntityName *left;
        Identifier *right;
    };

    typedef variant<Identifier *, TsQualifiedName *> TsEntityName;
    // export type TsEntityName = Identifier | TsQualifiedName;

    typedef variant<TsCallSignatureDeclaration *,
                    TsConstructSignatureDeclaration *,
                    TsMethodSignature *,
                    TsFunctionType *,
                    TsConstructorType *>
        TsSignatureDeclaration;

    struct TsSignatureDeclarationOrIndexSignatureBase : NodeBase
    {
        // Not using TypeScript's "ParameterDeclaration" here, since it's inconsistent with regular functions.
        vector<variant<Identifier *, RestElement *, ObjectPattern *, ArrayPattern *>> params;
        TsTypeAnnotation *returnType;
        // TODO(Babel 8): Remove
        vector<variant<Identifier *, RestElement *, ObjectPattern *, ArrayPattern *>> parameters; //: Array<Identifier | RestElement | ObjectPattern | ArrayPattern>;
        TsTypeAnnotation *typeAnnotation;
    };

    struct TsSignatureDeclarationBase
        : TsSignatureDeclarationOrIndexSignatureBase
    {
        TsTypeParameterDeclaration *typeParameters;
    };

    // ================
    // TypeScript type members (for type literal / interface / class)
    // ================

    typedef variant<TsCallSignatureDeclaration *,
                    TsConstructSignatureDeclaration *,
                    TsPropertySignature *,
                    TsMethodSignature *,
                    TsIndexSignature *>
        TsTypeElement;

    struct TsCallSignatureDeclaration : TsSignatureDeclarationBase
    {
        string type = "TSCallSignatureDeclaration";
    };

    struct TsConstructSignatureDeclaration
        : TsSignatureDeclarationBase
    {
        string type = "TSConstructSignatureDeclaration";
    };

    struct TsNamedTypeElementBase : NodeBase
    {
        // Not using TypeScript's `PropertyName` here since we don't have a `ComputedPropertyName` node type.
        // This is usually an Identifier but may be e.g. `Symbol.iterator` if `computed` is true.
        Expression *key;
        bool computed;
        bool optional;
    };

    struct TsPropertySignature : TsNamedTypeElementBase
    {
        string type = "TSPropertySignature";
        bool readonly;
        TsTypeAnnotation *typeAnnotation;
        Expression *initializer;
    };

    struct TsMethodSignature
        : TsSignatureDeclarationBase,
          TsNamedTypeElementBase
    {
        string type = "TSMethodSignature";
        /**
         * "method" | "get" | "set"
         */
        string kind;
    };

    // *Not* a ClassMemberBase: Can't have accessibility, can't be abstract, can't be optional.
    struct TsIndexSignature
        : TsSignatureDeclarationOrIndexSignatureBase
    {
        bool readonly;
        bool static_;
        string type = "TSIndexSignature";
        // Note: parameters.length must be 1.
    };

    // ================
    // TypeScript types
    // ================

    typedef variant<TsKeywordType *,
                    TsThisType *,
                    TsFunctionOrConstructorType *,
                    TsTypeReference *,
                    TsTypeQuery *,
                    TsTypeLiteral *,
                    TsArrayType *,
                    TsTupleType *,
                    TsOptionalType *,
                    TsRestType *,
                    TsUnionOrIntersectionType *,
                    TsConditionalType *,
                    TsInferType *,
                    TsParenthesizedType *,
                    TsTypeOperator *,
                    TsIndexedAccessType *,
                    TsMappedType *,
                    TsLiteralType *, // TODO: This probably shouldn't be included here.
                    TsImportType *,
                    TsTypePredicate *>
        TsType;

    typedef NodeBase TsTypeBase;

    /**
     *| "TSAnyKeyword"
      | "TSUnknownKeyword"
      | "TSNumberKeyword"
      | "TSObjectKeyword"
      | "TSBooleanKeyword"
      | "TSBigIntKeyword"
      | "TSStringKeyword"
      | "TSSymbolKeyword"
      | "TSVoidKeyword"
      | "TSUndefinedKeyword"
      | "TSNullKeyword"
      | "TSNeverKeyword"
      | "TSIntrinsicKeyword";
    */
    typedef string TsKeywordTypeType;

    struct TsKeywordType : TsTypeBase
    {
        TsKeywordTypeType type;
    };

    struct TsThisType : TsTypeBase
    {
        string type = "TSThisType";
    };

    typedef variant<TsFunctionType *, TsConstructorType *> TsFunctionOrConstructorType;
    // export type TsFunctionOrConstructorType = TsFunctionType | TsConstructorType;

    struct TsFunctionType : TsTypeBase, TsSignatureDeclarationBase
    {
        string type = "TSFunctionType";
        TsTypeAnnotation *typeAnnotation; // not optional
    };

    struct TsConstructorType
        : TsTypeBase,
          TsSignatureDeclarationBase
    {
        string type = "TSConstructorType";
        TsTypeAnnotation *typeAnnotation;
        bool abstract;
    };

    struct TsTypeReference : TsTypeBase
    {
        string type = "TSTypeReference";
        TsEntityName *typeName;
        TsTypeParameterInstantiation *typeParameters;
    };

    struct TsTypePredicate : TsTypeBase
    {
        string type = "TSTypePredicate";
        variant<Identifier *, TsThisType *> *parameterName;
        TsTypeAnnotation *typeAnnotation;
        bool asserts;
    };

    // `typeof` operator
    struct TsTypeQuery : TsTypeBase
    {
        string type = "TSTypeQuery";
        variant<TsEntityName *, TsImportType *> *exprName;
        TsTypeParameterInstantiation *typeParameters;
    };

    struct TsTypeLiteral : TsTypeBase
    {
        string type = "TSTypeLiteral";
        vector<TsTypeElement *> *members;
    };

    struct TsArrayType : TsTypeBase
    {
        string type = "TSArrayType";
        TsType elementType;
    };

    struct TsTupleType : TsTypeBase
    {
        string type = "TSTupleType";
        variant<variant<TsType, TsNamedTupleMember>> *elementTypes;
    };

    struct TsNamedTupleMember : TsTypeBase
    {
        string type = "TSNamedTupleMember";
        Identifier *label;
        bool optional;
        TsType elementType;
    };

    struct TsOptionalType : TsTypeBase
    {
        string type = "TSOptionalType";
        TsType typeAnnotation;
    };

    struct TsRestType : TsTypeBase
    {
        string type = "TSRestType";
        variant<TsType, TsNamedTupleMember> *typeAnnotation;
    };

    typedef variant<TsUnionType, TsIntersectionType> TsUnionOrIntersectionType;

    struct TsUnionOrIntersectionTypeBase : TsTypeBase
    {
        vector<TsType> types;
    };

    struct TsUnionType : TsUnionOrIntersectionTypeBase
    {
        string type = "TSUnionType";
    };

    struct TsIntersectionType : TsUnionOrIntersectionTypeBase
    {
        string type = "TSIntersectionType";
    };

    struct TsConditionalType : TsTypeBase
    {
        string type = "TSConditionalType";
        TsType checkType;
        TsType extendsType;
        TsType trueType;
        TsType falseType;
    };

    struct TsInferType : TsTypeBase
    {
        string type = "TSInferType";
        TsTypeParameter typeParameter;
    };

    struct TsParenthesizedType : TsTypeBase
    {
        string type = "TSParenthesizedType";
        TsType typeAnnotation;
    };

    struct TsTypeOperator : TsTypeBase
    {
        string type = "TSTypeOperator";

        /**
         * "keyof" | "unique" | "readonly"
         */
        string operator_;
        TsType typeAnnotation;
    };

    struct TsIndexedAccessType : TsTypeBase
    {
        string type = "TSIndexedAccessType";
        TsType objectType;
        TsType indexType;
    };

    struct TsMappedType : TsTypeBase
    {
        string type = "TSMappedType";
        /**
         * true | "+" | "-"
         */
        string readonly;
        TsTypeParameter typeParameter;

        /**
         * true | "+" | "-"
         */
        string optional;

        TsType typeAnnotation;
        TsType nameType;
    };

    struct TsLiteralType : TsTypeBase
    {
        string type = "TSLiteralType";
        variant<NumericLiteral *, StringLiteral *, BooleanLiteral *, TemplateLiteral *> *literal;
    };

    struct TsImportType : TsTypeBase
    {
        string type = "TSImportType";
        StringLiteral *argument;
        TsEntityName *qualifier;
        TsTypeParameterInstantiation *typeParameters;
    };

    // ================
    // TypeScript declarations
    // ================

    struct TsInterfaceDeclaration : DeclarationBase
    {
        string type = "TSInterfaceDeclaration";
        Identifier *id;
        TsTypeParameterDeclaration *typeParameters;
        // TS uses "heritageClauses", but want this to resemble ClassBase.
        vector<TsExpressionWithTypeArguments *> *extends;
        TSInterfaceBody *body;
    };

    struct TSInterfaceBody : NodeBase
    {
        string type = "TSInterfaceBody";
        vector<TsTypeElement *> *body;
    };

    struct TsExpressionWithTypeArguments : TsTypeBase
    {
        string type = "TSExpressionWithTypeArguments";
        TsEntityName expression;
        TsTypeParameterInstantiation typeParameters;
    };

    struct TsTypeAliasDeclaration : DeclarationBase
    {
        string type = "TSTypeAliasDeclaration";
        Identifier *id;
        TsTypeParameterDeclaration *typeParameters;
        TsType *typeAnnotation;
    };

    struct TsEnumDeclaration : DeclarationBase
    {
        string type = "TSEnumDeclaration";
        bool const_;
        Identifier *id;
        vector<TsEnumMember> *members;
    };

    struct TsEnumMember : NodeBase
    {
        string type = "TSEnumMember";
        variant<Identifier *, StringLiteral *> id;
        Expression *initializer;
    };

    struct TsModuleDeclaration : DeclarationBase
    {
        string type = "TSModuleDeclaration";
        bool global; // In TypeScript, this is only available through `node.flags`.,
        TsModuleName *id;
        TsNamespaceBody *body;
    };

    // `namespace A.B { }` is a namespace named `A` with another TsNamespaceDeclaration as its body.
    typedef variant<TsModuleBlock *, TsNamespaceDeclaration *> TsNamespaceBody;
    // export type TsNamespaceBody = TsModuleBlock | TsNamespaceDeclaration;

    struct TsModuleBlock : NodeBase
    {
        string type = "TSModuleBlock";
        vector<Statement *> *body;
    };

    struct TsNamespaceDeclaration : TsModuleDeclaration
    {
        Identifier *id;
        TsNamespaceBody *body;
    };

    typedef variant<Identifier *, StringLiteral *> TsModuleName;
    // export type TsModuleName = Identifier | StringLiteral;

    struct TsImportEqualsDeclaration : NodeBase
    {
        string type = "TSImportEqualsDeclaration";
        bool isExport;
        Identifier *id;
        /**
         * "type" | "value"
         */
        string importKind;

        TsModuleReference *moduleReference;
    };

    typedef variant<TsEntityName *, TsExternalModuleReference *> TsModuleReference;
    // export type TsModuleReference = TsEntityName | TsExternalModuleReference;

    struct TsExternalModuleReference : NodeBase
    {
        string type = "TSExternalModuleReference";
        StringLiteral *expression;
    };

    // TypeScript's own parser uses ExportAssignment for both `export default` and `export =`.
    // But for @babel/parser, `export default` is an ExportDefaultDeclaration,
    // so a TsExportAssignment is always `export =`.
    struct TsExportAssignment : NodeBase
    {
        string type = "TSExportAssignment";
        Expression *expression;
    };

    struct TsNamespaceExportDeclaration : NodeBase
    {
        string type = "TSNamespaceExportDeclaration";
        Identifier *id;
    };

    // ================
    // TypeScript expressions
    // ================

    struct TsTypeAssertionLikeBase : NodeBase
    {
        Expression *expression;
        TsType *typeAnnotation;
    };

    struct TsAsExpression : TsTypeAssertionLikeBase
    {
        string type = "TSAsExpression";
    };

    struct TsTypeAssertion : TsTypeAssertionLikeBase
    {
        string type = "TSTypeAssertion";
    };

    // export type TsSatisfiesExpression = TsTypeAssertionLikeBase & {
    //   type: "TSSatisfiesExpression";
    // };

    struct TsNonNullExpression : NodeBase
    {
        string type = "TSNonNullExpression";
        Expression *expression;
    };

    struct TsInstantiationExpression : NodeBase
    {
        string type = "TSInstantiationExpression";
        Expression *expression;
        TsTypeParameterInstantiation *typeParameters;
    };

    // ================
    // Babel placeholders %%foo%%
    // ================

    // struct Placeholder<N extends PlaceholderTypes = PlaceholderTypes>
    //   : NodeBase {
    //   type: "Placeholder";
    //   id: Identifier;
    //   expectedNode: N;
    // }

    // ================
    // Other
    // ================

    struct ParseSubscriptState
    {
        bool optionalChainMember;
        bool maybeAsyncArrow;
        bool stop;
    };

    struct ParseClassMemberState
    {
        bool hadConstructor;
        bool hadSuperClass;
    };
}
#endif BABEL_PARSER_types_H_