#ifndef BABEL_TYPES_AST_H_
#define BABEL_TYPES_AST_H_
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <any>
#include <variant>
#include <unordered_set>
#include <rttr/registration>
#include "./ast_macro.h"

using rttr::registration;
using std::string;
using namespace std;
using std::variant;

namespace ast
{
    // Node start
    struct AnyTypeAnnotation;
    struct ArgumentPlaceholder;
    struct ArrayExpression;
    struct ArrayPattern;
    struct ArrayTypeAnnotation;
    struct ArrowFunctionExpression;
    struct AssignmentExpression;
    struct AssignmentPattern;
    struct AwaitExpression;
    struct BigIntLiteral;
    struct BinaryExpression;
    struct BindExpression;
    struct BlockStatement;
    struct BooleanLiteral;
    struct BooleanLiteralTypeAnnotation;
    struct BooleanTypeAnnotation;
    struct BreakStatement;
    struct CallExpression;
    struct CatchClause;
    struct ClassAccessorProperty;
    struct ClassBody;
    struct ClassDeclaration;
    struct ClassExpression;
    struct ClassImplements;
    struct ClassMethod;
    struct ClassPrivateMethod;
    struct ClassPrivateProperty;
    struct ClassProperty;
    struct ConditionalExpression;
    struct ContinueStatement;
    struct DebuggerStatement;
    struct DecimalLiteral;
    struct DeclareClass;
    struct DeclareExportAllDeclaration;
    struct DeclareExportDeclaration;
    struct DeclareFunction;
    struct DeclareInterface;
    struct DeclareModule;
    struct DeclareModuleExports;
    struct DeclareOpaqueType;
    struct DeclareTypeAlias;
    struct DeclareVariable;
    struct DeclaredPredicate;
    struct Decorator;
    struct Directive;
    struct DirectiveLiteral;
    struct DoExpression;
    struct DoWhileStatement;
    struct EmptyStatement;
    struct EmptyTypeAnnotation;
    struct EnumBooleanBody;
    struct EnumBooleanMember;
    struct EnumDeclaration;
    struct EnumDefaultedMember;
    struct EnumNumberBody;
    struct EnumNumberMember;
    struct EnumStringBody;
    struct EnumStringMember;
    struct EnumSymbolBody;
    struct ExistsTypeAnnotation;
    struct ExportAllDeclaration;
    struct ExportDefaultDeclaration;
    struct ExportDefaultSpecifier;
    struct ExportNamedDeclaration;
    struct ExportNamespaceSpecifier;
    struct ExportSpecifier;
    struct ExpressionStatement;
    struct File;
    struct ForInStatement;
    struct ForOfStatement;
    struct ForStatement;
    struct FunctionDeclaration;
    struct FunctionExpression;
    struct FunctionTypeAnnotation;
    struct FunctionTypeParam;
    struct GenericTypeAnnotation;
    struct Identifier;
    struct IfStatement;
    struct Import;
    struct ImportAttribute;
    struct ImportDeclaration;
    struct ImportDefaultSpecifier;
    struct ImportExpression;
    struct ImportNamespaceSpecifier;
    struct ImportSpecifier;
    struct IndexedAccessType;
    struct InferredPredicate;
    struct InterfaceDeclaration;
    struct InterfaceExtends;
    struct InterfaceTypeAnnotation;
    struct InterpreterDirective;
    struct IntersectionTypeAnnotation;
    struct JSXAttribute;
    struct JSXClosingElement;
    struct JSXClosingFragment;
    struct JSXElement;
    struct JSXEmptyExpression;
    struct JSXExpressionContainer;
    struct JSXFragment;
    struct JSXIdentifier;
    struct JSXMemberExpression;
    struct JSXNamespacedName;
    struct JSXOpeningElement;
    struct JSXOpeningFragment;
    struct JSXSpreadAttribute;
    struct JSXSpreadChild;
    struct JSXText;
    struct LabeledStatement;
    struct LogicalExpression;
    struct MemberExpression;
    struct MetaProperty;
    struct MixeDTYPEAnnotation;
    struct ModuleExpression;
    struct NewExpression;
    struct Noop;
    struct NullLiteral;
    struct NullLiteralTypeAnnotation;
    struct NullableTypeAnnotation;
    struct NumberLiteral;
    struct NumberLiteralTypeAnnotation;
    struct NumberTypeAnnotation;
    struct NumericLiteral;
    struct ObjectExpression;
    struct ObjectMethod;
    struct ObjectPattern;
    struct ObjectProperty;
    struct ObjectTypeAnnotation;
    struct ObjectTypeCallProperty;
    struct ObjectTypeIndexer;
    struct ObjectTypeInternalSlot;
    struct ObjectTypeProperty;
    struct ObjectTypeSpreadProperty;
    struct OpaqueType;
    struct OptionalCallExpression;
    struct OptionalIndexedAccessType;
    struct OptionalMemberExpression;
    struct ParenthesizedExpression;
    struct PipelineBareFunction;
    struct PipelinePrimaryTopicReference;
    struct PipelineTopicExpression;
    struct Placeholder;
    struct PrivateName;
    struct Program;
    struct QualifieDTYPEIdentifier;
    struct RecordExpression;
    struct RegExpLiteral;
    struct RegexLiteral;
    struct RestElement;
    struct RestProperty;
    struct ReturnStatement;
    struct SequenceExpression;
    struct SpreadElement;
    struct SpreadProperty;
    struct StaticBlock;
    struct StringLiteral;
    struct StringLiteralTypeAnnotation;
    struct StringTypeAnnotation;
    struct Super;
    struct SwitchCase;
    struct SwitchStatement;
    struct SymbolTypeAnnotation;
    struct TSAnyKeyword;
    struct TSArrayType;
    struct TSAsExpression;
    struct TSBigIntKeyword;
    struct TSBooleanKeyword;
    struct TSCallSignatureDeclaration;
    struct TSConditionalType;
    struct TSConstructSignatureDeclaration;
    struct TSConstructorType;
    struct TSDeclareFunction;
    struct TSDeclareMethod;
    struct TSEnumDeclaration;
    struct TSEnumMember;
    struct TSExportAssignment;
    struct TSExpressionWithTypeArguments;
    struct TSExternalModuleReference;
    struct TSFunctionType;
    struct TSImportEqualsDeclaration;
    struct TSImportType;
    struct TSIndexSignature;
    struct TSIndexedAccessType;
    struct TSInferType;
    struct TSInstantiationExpression;
    struct TSInterfaceBody;
    struct TSInterfaceDeclaration;
    struct TSIntersectionType;
    struct TSIntrinsicKeyword;
    struct TSLiteralType;
    struct TSMappeDTYPE;
    struct TSMethodSignature;
    struct TSModuleBlock;
    struct TSModuleDeclaration;
    struct TSNamedTupleMember;
    struct TSNamespaceExportDeclaration;
    struct TSNeverKeyword;
    struct TSNonNullExpression;
    struct TSNullKeyword;
    struct TSNumberKeyword;
    struct TSObjectKeyword;
    struct TSOptionalType;
    struct TSParameterProperty;
    struct TSParenthesizeDTYPE;
    struct TSPropertySignature;
    struct TSQualifiedName;
    struct TSRestType;
    struct TSSatisfiesExpression;
    struct TSStringKeyword;
    struct TSSymbolKeyword;
    struct TSThisType;
    struct TSTupleType;
    struct TSTypeAliasDeclaration;
    struct TSTypeAnnotation;
    struct TSTypeAssertion;
    struct TSTypeLiteral;
    struct TSTypeOperator;
    struct TSTypeParameter;
    struct TSTypeParameterDeclaration;
    struct TSTypeParameterInstantiation;
    struct TSTypePredicate;
    struct TSTypeQuery;
    struct TSTypeReference;
    struct TSUndefinedKeyword;
    struct TSUnionType;
    struct TSUnknownKeyword;
    struct TSVoidKeyword;
    struct TaggedTemplateExpression;
    struct TemplateElement;
    struct TemplateLiteral;
    struct ThisExpression;
    struct ThisTypeAnnotation;
    struct ThrowStatement;
    struct TopicReference;
    struct TryStatement;
    struct TupleExpression;
    struct TupleTypeAnnotation;
    struct TypeAlias;
    struct TypeAnnotation;
    struct TypeCastExpression;
    struct TypeParameter;
    struct TypeParameterDeclaration;
    struct TypeParameterInstantiation;
    struct TypeofTypeAnnotation;
    struct UnaryExpression;
    struct UnionTypeAnnotation;
    struct UpdateExpression;
    struct V8IntrinsicIdentifier;
    struct VariableDeclaration;
    struct VariableDeclarator;
    struct Variance;
    struct VoiDTYPEAnnotation;
    struct WhileStatement;
    struct WithStatement;
    struct YieldExpression;
    // Node end

    struct SourceLocation;

    // TODO
    struct LVal;
    struct Pattern;
    struct Noop;
    struct PatternLike;
    struct Declaration;

    struct BaseComment
    {
        string value;
        int start;
        int end;
        SourceLocation *loc;
        bool ignore;
        string type;
    };

    struct Position
    {
        int line;
        int column;
        int index;
    };

    struct CommentBlock : public BaseComment
    {
        const string type = "CommentBlock";
    };

    struct CommentLine : public BaseComment
    {
        const string type = "CommentLine";
    };

    // export type Comment = CommentBlock | CommentLine;
    typedef struct BaseComment Comment;

    struct SourceLocation
    {
        Position *start;
        Position *end;
        string filename;
        string identifierName;
    };

    struct BaseNode
    {
        string type;
        std::vector<BaseComment *> *leadingComments;
        std::vector<BaseComment *> *innerComments;
        std::vector<BaseComment *> *trailingComments;
        int start = 0;
        int end = 0;
        SourceLocation *loc;
        std::tuple<int, int> *range;
        std::map<string, std::any> *extra;

        BaseNode() {
            start = 0;
            end = 0;
        }

        RTTR(BaseNode, ATTR9(BaseNode, type, leadingComments, innerComments, trailingComments, start, end, loc, range, extra))
    };

    // export type CommentTypeShorthand = "leading" | "inner" | "trailing";

    // 所有的Node，需要用到的地方使用类型转换
    typedef BaseNode Node;

    DSTRUCT(Expression){};

    DSTRUCT(Statement){};

    struct ArrayExpression : public BaseNode
    {
        DTYPE(ArrayExpression);
        std::vector<std::variant<Expression *, SpreadElement *>> *elements;
        RTTR(ArrayExpression, ATTR3(ArrayExpression, type, elements, start))
    };

    struct SpreadElement
    {
    };

    struct AssignmentExpression : public Expression
    {
        DTYPE(AssignmentExpression);
        string operator_;
        std::variant<LVal *, OptionalMemberExpression *> *left;
        Expression *right;
    };

    struct BinaryExpression : public Expression
    {
        DTYPE(BinaryExpression);
        string operator_; // TODO 约束
        std::variant<Expression *, PrivateName *> *left;
        Expression *right;
    };

    // struct OptionalMemberExpression : public Expression
    // {
    //     const string type = "OptionalMemberExpression";
    //     Expression object;
    //     std::variant<Expression> property; // Expression | Identifier;
    //     bool computed;
    //     bool optional;
    // };

    struct InterpreterDirective : public BaseNode
    {
        DTYPE(InterpreterDirective);
        string value;
    };

    struct DirectiveLiteral : public BaseNode
    {
        DTYPE(DirectiveLiteral);
        string value;
    };

    struct Directive : public BaseNode
    {
        DTYPE(Directive);
        DirectiveLiteral *value;
    };

    struct BlockStatement : public BaseNode
    {
        DTYPE(BlockStatement);
        std::vector<Statement> *body;
        std::vector<Directive> *directives;
    };

    struct BreakStatement : public BaseNode
    {
        DTYPE(BreakStatement);
        Identifier *label;
    };

    struct CallExpression : public BaseNode
    {
        DTYPE(CallExpression);
        std::variant<Expression *, Super *, V8IntrinsicIdentifier *> *callee;
        std::vector<std::variant<Expression *, SpreadElement *, JSXNamespacedName *, ArgumentPlaceholder *>> arguments;
        bool optional;
        TypeParameterInstantiation *typeArguments;
        TSTypeParameterInstantiation *typeParameters;
    };

    struct CatchClause : public BaseNode
    {
        DTYPE(CatchClause);
        std::variant<Identifier *, ArrayPattern *, ObjectPattern *> param;
        BlockStatement *body;
    };

    struct ConditionalExpression : public BaseNode
    {
        DTYPE(ConditionalExpression);
        Expression *test;
        Expression *consequent;
        Expression *alternate;
    };

    struct ContinueStatement : public Statement
    {
        const string type = "ConditionalExpression";
        Identifier *label;
    };

    struct DebuggerStatement : public Statement
    {
        const string type = "DebuggerStatement";
    };

    struct DoWhileStatement : public Statement
    {
        const string type = "DoWhileStatement";
        Expression *test;
        Statement *body;
    };
    struct EmptyStatement : public Statement
    {
        const string type = "EmptyStatement";
    };

    struct ExpressionStatement : public BaseNode
    {
        const string type = "EmptyStatement";
        Expression *expression;
    };

    struct File : public BaseNode
    {
        const string type = "File";
        Program *program;
        std::vector<std::variant<CommentBlock *, CommentLine *>> *comments; //  Array<CommentBlock | CommentLine> | null
        std::vector<std::any> *tokens;
    };

    struct ForInStatement : public BaseNode
    {
        const string type = "ForInStatement";
        variant<VariableDeclaration *, LVal *> *left;
        Expression *right;
        Statement *body;
    };

    struct ForStatement : public BaseNode
    {
        const string type = "ForStatement";
        variant<VariableDeclaration *, Expression *> init;
        Expression *test;
        Expression *update;
        Statement *body;
    };

    struct FunctionDeclaration : public BaseNode
    {
        const string type = "FunctionDeclaration";
        Identifier *id;
        variant<Identifier *, Pattern *, RestElement *> *params;
        BlockStatement *body;
        bool generator;
        bool async;
        bool declare;
        vector<DeclaredPredicate *, InferredPredicate *> *predicate;
        variant<TypeAnnotation *, TSTypeAnnotation *, Noop *> returnType;
        variant<TypeParameterDeclaration *, TSTypeParameterDeclaration *, Noop *> typeParameters;
    };

    struct FunctionExpression : public BaseNode
    {
        const string type = "FunctionExpression";
        Identifier *id;
        vector<variant<Identifier *, Pattern *, RestElement *>> params;
        BlockStatement *body;
        bool generator;
        bool async;
        variant<DeclaredPredicate *, InferredPredicate *> predicate;
        variant<TypeAnnotation *, TSTypeAnnotation *, Noop *> returnType;
        variant<TypeParameterDeclaration *, TSTypeParameterDeclaration *, Noop *> typeParameters;
    };

    struct Identifier : public BaseNode
    {
        const string type = "Identifier";
        string name;
        vector<Decorator *> decorators;
        bool optional;
        variant<TypeAnnotation *, TSTypeAnnotation *, Noop *> typeAnnotation;
    };

    struct IfStatement : public BaseNode
    {
        const string type = "IfStatement";
        Expression *test;
        Statement *consequent;
        Statement *alternate;
    };

    struct LabeledStatement : BaseNode
    {
        const string type = "LabeledStatement";
        Identifier label;
        Statement body;
    };

    struct StringLiteral : BaseNode
    {
        const string type = "StringLiteral";
        string value;
    };

    struct NumericLiteral : BaseNode
    {
        const string type = "NumericLiteral";
        int value;
    };

    /**
     * @deprecated Use `NumericLiteral`
     */
    struct NumberLiteral : BaseNode
    {
        DTYPE(NumberLiteral);
        int value;
    };

    D_SIMPLE_STRUCT(NullLiteral);

    struct BooleanLiteral : BaseNode
    {
        DTYPE(BooleanLiteral);
        bool value;
    };

    struct RegExpLiteral : BaseNode
    {
        DTYPE(RegExpLiteral);
        string pattern;
        string flags;
    };

    /**
     * @deprecated Use `RegExpLiteral`
     */
    struct RegexLiteral : BaseNode
    {
        DTYPE(RegexLiteral);
        string pattern;
        string flags;

        RegexLiteral() {
       this->flags = "www";
            
        }
    };

    struct LogicalExpression : BaseNode
    {
        DTYPE(LogicalExpression);
        string operator_; // "||" | "&&" | "??";
        // 允许的operator_取值
        unordered_set<std::string> allowed_operator_ = {"||", "&&", "??"};
        Expression *left;
        Expression *right;
    };

    struct MemberExpression : BaseNode
    {
        DTYPE(MemberExpression);
        variant<Expression *, Super *> object;
        variant<Expression *, Identifier *, PrivateName *> property;
        bool computed;
        bool optional;
    };

    struct NewExpression : BaseNode
    {
        DTYPE(NewExpression);
        variant<Expression *, Super *, V8IntrinsicIdentifier *> *callee;
        vector<variant<Expression *, SpreadElement *, JSXNamespacedName *, ArgumentPlaceholder *>> *arguments;
        bool optional;
        TypeParameterInstantiation *typeArguments;
        TSTypeParameterInstantiation *typeParameters;
    };

    struct Program : BaseNode
    {
        DTYPE(Program);
        vector<Statement *> *body;
        vector<Directive *> *directives;
        string sourceType; // "script" | "module";
        InterpreterDirective *interpreter;
        string sourceFile;
    };

    struct ObjectExpression : BaseNode
    {
        DTYPE(ObjectExpression);
        vector<variant<ObjectMethod *, ObjectProperty *, SpreadElement *>> *properties;
    };

    struct ObjectMethod : BaseNode
    {
        DTYPE(ObjectExpression);
        string kind; // "method" | "get" | "set";
        variant<Expression *, Identifier *, StringLiteral *, NumericLiteral *, BigIntLiteral *> *key;
        vector<variant<Identifier *, Pattern *, RestElement *>> *params;
        BlockStatement *body;
        bool computed;
        bool generator;
        bool async;
        vector<Decorator *> *decorators;
        variant<TypeAnnotation *, TSTypeAnnotation *, Noop> *returnType;
        variant<TypeParameterDeclaration *, TSTypeParameterDeclaration *, Noop> *typeParameters;
    };

    struct ObjectProperty : BaseNode
    {
        DTYPE(ObjectProperty);
        variant<Expression *, Identifier *, StringLiteral *, NumericLiteral *, BigIntLiteral *, DecimalLiteral *, PrivateName *> *key;
        variant<Expression *, PatternLike *> *value;
        bool computed;
        bool shorthand;
        vector<Decorator> *decorators;
    };

    struct RestElement : BaseNode
    {
        DTYPE(RestElement);
        LVal *argument;
        vector<Decorator *> *decorators;
        bool optional;
        variant<TypeAnnotation *, TSTypeAnnotation *, Noop *> *typeAnnotation;
    };

    /**
     * @deprecated Use `RestElement`
     */
    DSTRUCT(RestProperty)
    {
        DTYPE(RestProperty);
        LVal *argument;
        vector<Decorator *> *decorators;
        bool optional;
        variant<TypeAnnotation *, TSTypeAnnotation *, Noop *> *typeAnnotation;
    };

    DSTRUCT(ReturnStatement)
    {
        DTYPE(ReturnStatement);
        Expression *argument;
    };

    DSTRUCT(SequenceExpression)
    {
        DTYPE(SequenceExpression);
        vector<Expression *> *expressions;
    };

    DSTRUCT(ParenthesizedExpression)
    {
        DTYPE(ParenthesizedExpression);
        Expression *expression;
    };

    // DSTRUCT(SwitchCase)
    // {
    //     DTYPE(SwitchCase);
    //     Expression test;
    //     vector<Statement *> *consequent;
    // };

    // DSTRUCT(SwitchStatement)
    // {
    //     DTYPE(SwitchStatement);
    //     Expression *discriminant;
    //     vector<SwitchCase *> *cases;
    // };

    // DSTRUCT(ThisExpression)
    // {
    //     DTYPE(ThisExpression);
    // };

    // struct ThrowStatement : BaseNode
    // {
    //     string type = "ThrowStatement";
    //     Expression argument;
    // };

    // struct TryStatement : BaseNode
    // {
    //     string type = "TryStatement";
    //     BlockStatement block;
    //     CatchClause handler;
    //     BlockStatement finalizer;
    // };

    // struct UnaryExpression : BaseNode
    // {
    //     string type = "UnaryExpression";
    //     string operator_; //"void" , "throw" , "delete" , "!" , "+" , "-" , "~" , "typeof"
    //     Expression argument;
    //     bool prefix;
    // };

    // struct UpdateExpression : BaseNode
    // {
    //     string type = "UpdateExpression";
    //     string operator_; //"++" , "--"
    //     Expression argument;
    //     bool prefix;
    // };

    // struct VariableDeclaration : BaseNode
    // {
    //     string type = "VariableDeclaration";
    //     string kind; // "var" , "let" , "const" , "using" , "await using"
    //     vector<VariableDeclarator> declarations;
    //     bool declare;
    // };

    // struct VariableDeclarator : BaseNode
    // {
    //     string type = "VariableDeclarator";
    //     LVal *id;
    //     Expression init;
    //     bool definite;
    // };

    // struct WhileStatement : BaseNode
    // {
    //     string type = "WhileStatement";
    //     Expression test;
    //     Statement body;
    // };

    // struct WithStatement : BaseNode
    // {
    //     string type = "WithStatement";
    //     Expression object;
    //     Statement body;
    // };

    // struct AssignmentPattern : BaseNode
    // {
    //     string type = "AssignmentPattern";
    //     variant<Identifier, ObjectPattern, ArrayPattern, MemberExpression, TSAsExpression, TSSatisfiesExpression, TSTypeAssertion, TSNonNullExpression> left;
    //     Expression right;
    //     vector<Decorator> decorators;
    //     bool optional_;
    //     variant<TypeAnnotation, TSTypeAnnotation, Noop> typeAnnotation;
    // };

    // struct ArrayPattern : BaseNode
    // {
    //     string type = "ArrayPattern";
    //     vector<PatternLike, LVal *> elements;
    //     vector<Decorator> decorators;
    //     bool optional;
    //     variant<TypeAnnotation, TSTypeAnnotation, Noop> typeAnnotation;
    // };

    // struct ArrowFunctionExpression : BaseNode
    // {
    //     string type = "ArrowFunctionExpression";
    //     vector<variant<Identifier, Pattern, RestElement *>> params;
    //     variant<BlockStatement, Expression> body;
    //     bool async;
    //     bool expression;
    //     bool generator;
    //     variant<DeclaredPredicate, InferredPredicate> predicate;
    //     variant<TypeAnnotation, TSTypeAnnotation, Noop> returnType;
    //     variant<TypeParameterDeclaration, TSTypeParameterDeclaration, Noop> typeParameters;
    // };

    // struct ClassBody : BaseNode
    // {
    //     string type = "ClassBody";
    //     vector<variant<ClassMethod, ClassPrivateMethod, ClassProperty, ClassPrivateProperty, ClassAccessorProperty, TSDeclareMethod, TSIndexSignature, StaticBlock>> body;
    // };

    // struct ClassExpression : BaseNode
    // {
    //     string type = "ClassExpression";
    //     Identifier id;
    //     Expression superClass;
    //     ClassBody body;
    //     vector<Decorator> decorators;
    //     vector<TSExpressionWithTypeArguments, ClassImplements> implements;
    //     InterfaceExtends *mixins;
    //     variant<TypeParameterInstantiation, TSTypeParameterInstantiation> superTypeParameters;
    //     variant<TypeParameterDeclaration, TSTypeParameterDeclaration, Noop> typeParameters;
    // };

    // struct ClassDeclaration : BaseNode
    // {
    //     string type = "ClassDeclaration";
    //     Identifier id;
    //     Expression superClass;
    //     ClassBody body;
    //     vector<Decorator> decorators;
    //     bool abstract;
    //     bool declare;
    //     vector<TSExpressionWithTypeArguments, ClassImplements> implements;
    //     InterfaceExtends *mixins;
    //     variant<TypeParameterInstantiation, TSTypeParameterInstantiation> superTypeParameters;
    //     variant<TypeParameterDeclaration, TSTypeParameterDeclaration, Noop> typeParameters;
    // };

    // struct ExportAllDeclaration : BaseNode
    // {
    //     string type = "ExportAllDeclaration";
    //     StringLiteral source;
    //     vector<ImportAttribute> assertions;
    //     vector<ImportAttribute> attributes;
    //     string exportKind; // "type" , "value"
    // };

    // struct ExportDefaultDeclaration : BaseNode
    // {
    //     string type = "ExportDefaultDeclaration";
    //     variant<TSDeclareFunction, FunctionDeclaration, ClassDeclaration, Expression> declaration;
    //     string exportKind; //"value"
    // };

    // struct ExportNamedDeclaration : BaseNode
    // {
    //     string type = "ExportNamedDeclaration";
    //     Declaration *declaration;
    //     vector<variant<ExportSpecifier, ExportDefaultSpecifier, ExportNamespaceSpecifier>> specifiers;
    //     StringLiteral source;
    //     vector<ImportAttribute> assertions;
    //     vector<ImportAttribute> attributes;
    //     string exportKind; //"type" , "value"
    // };

    // struct ExportSpecifier : BaseNode
    // {
    //     string type = "ExportSpecifier";
    //     Identifier local;
    //     variant<Identifier, StringLiteral> exported;
    //     string exportKind; // "type" , "value"
    // };

    // struct ForOfStatement : BaseNode
    // {
    //     string type = "ForOfStatement";
    //     variant<VariableDeclaration, LVal *> left;
    //     Expression right;
    //     Statement body;
    //     bool await;
    // };
};
#endif // BABEL_TYPES_AST_H_