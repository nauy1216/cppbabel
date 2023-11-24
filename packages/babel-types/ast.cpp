#ifndef BABEL_TYPES_AST_TYPES
#define BABEL_TYPES_AST_TYPES
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <any>
#include <variant>
#include <unordered_set>
#include <rttr/registration>
#include "./ast.h"

using rttr::registration;
using std::string;
using namespace std;
using std::variant;

namespace ast
{
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
        int start;
        int end;
        SourceLocation *loc;
        std::tuple<int, int> *range;
        std::map<string, std::any> *extra;
        RTTR(BaseNode, ATTR9(BaseNode, type, leadingComments, innerComments, trailingComments, start, end, loc, range, extra))
    };

    // export type CommentTypeShorthand = "leading" | "inner" | "trailing";

    // 所有的Node，需要用到的地方使用类型转换
    typedef BaseNode Node;

    DSTRUCT(Expression){};

    DSTRUCT(Statement){};

    struct SpreadElement
    {
    };

    struct ArrayExpression : public BaseNode
    {
        DTYPE(ArrayExpression);
        std::vector<std::variant<Expression *, SpreadElement *>> *elements;
        RTTR(ArrayExpression, ATTR3(ArrayExpression, type, elements, start))
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

};
#endif // BABEL_TYPES_AST_TYPES