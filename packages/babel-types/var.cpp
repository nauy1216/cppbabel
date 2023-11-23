#ifndef BABEL_TYPES_VAR
#define BABEL_TYPES_VAR

#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <any>
#include <variant>
#include "./ast.cpp"

namespace var
{
    enum VarType
    {
        AnyTypeAnnotation = 1,
        ArgumentPlaceholder,
        ArrayExpression,
        ArrayPattern,
        ArrayTypeAnnotation,
        ArrowFunctionExpression,
        AssignmentExpression,
        AssignmentPattern,
        AwaitExpression,
        BigIntLiteral,
        BinaryExpression,
        BindExpression,
        BlockStatement,
        BooleanLiteral,
        BooleanLiteralTypeAnnotation,
        BooleanTypeAnnotation,
        BreakStatement,
        CallExpression,
        CatchClause,
        ClassAccessorProperty,
        ClassBody,
        ClassDeclaration,
        ClassExpression,
        ClassImplements,
        ClassMethod,
        ClassPrivateMethod,
        ClassPrivateProperty,
        ClassProperty,
        ConditionalExpression,
        ContinueStatement,
        DebuggerStatement,
        DecimalLiteral,
        DeclareClass,
        DeclareExportAllDeclaration,
        DeclareExportDeclaration,
        DeclareFunction,
        DeclareInterface,
        DeclareModule,
        DeclareModuleExports,
        DeclareOpaqueType,
        DeclareTypeAlias,
        DeclareVariable,
        DeclaredPredicate,
        Decorator,
        Directive,
        DirectiveLiteral,
        DoExpression,
        DoWhileStatement,
        EmptyStatement,
        EmptyTypeAnnotation,
        EnumBooleanBody,
        EnumBooleanMember,
        EnumDeclaration,
        EnumDefaultedMember,
        EnumNumberBody,
        EnumNumberMember,
        EnumStringBody,
        EnumStringMember,
        EnumSymbolBody,
        ExistsTypeAnnotation,
        ExportAllDeclaration,
        ExportDefaultDeclaration,
        ExportDefaultSpecifier,
        ExportNamedDeclaration,
        ExportNamespaceSpecifier,
        ExportSpecifier,
        ExpressionStatement,
        File,
        ForInStatement,
        ForOfStatement,
        ForStatement,
        FunctionDeclaration,
        FunctionExpression,
        FunctionTypeAnnotation,
        FunctionTypeParam,
        GenericTypeAnnotation,
        Identifier,
        IfStatement,
        Import,
        ImportAttribute,
        ImportDeclaration,
        ImportDefaultSpecifier,
        ImportExpression,
        ImportNamespaceSpecifier,
        ImportSpecifier,
        IndexedAccessType,
        InferredPredicate,
        InterfaceDeclaration,
        InterfaceExtends,
        InterfaceTypeAnnotation,
        InterpreterDirective,
        IntersectionTypeAnnotation,
        JSXAttribute,
        JSXClosingElement,
        JSXClosingFragment,
        JSXElement,
        JSXEmptyExpression,
        JSXExpressionContainer,
        JSXFragment,
        JSXIdentifier,
        JSXMemberExpression,
        JSXNamespacedName,
        JSXOpeningElement,
        JSXOpeningFragment,
        JSXSpreadAttribute,
        JSXSpreadChild,
        JSXText,
        LabeledStatement,
        LogicalExpression,
        MemberExpression,
        MetaProperty,
        MixedTypeAnnotation,
        ModuleExpression,
        NewExpression,
        Noop,
        NullLiteral,
        NullLiteralTypeAnnotation,
        NullableTypeAnnotation,
        NumberLiteral,
        NumberLiteralTypeAnnotation,
        NumberTypeAnnotation,
        NumericLiteral,
        ObjectExpression,
        ObjectMethod,
        ObjectPattern,
        ObjectProperty,
        ObjectTypeAnnotation,
        ObjectTypeCallProperty,
        ObjectTypeIndexer,
        ObjectTypeInternalSlot,
        ObjectTypeProperty,
        ObjectTypeSpreadProperty,
        OpaqueType,
        OptionalCallExpression,
        OptionalIndexedAccessType,
        OptionalMemberExpression,
        ParenthesizedExpression,
        PipelineBareFunction,
        PipelinePrimaryTopicReference,
        PipelineTopicExpression,
        Placeholder,
        PrivateName,
        Program,
        QualifiedTypeIdentifier,
        RecordExpression,
        RegExpLiteral,
        RegexLiteral,
        RestElement,
        RestProperty,
        ReturnStatement,
        SequenceExpression,
        SpreadElement,
        SpreadProperty,
        StaticBlock,
        StringLiteral,
        StringLiteralTypeAnnotation,
        StringTypeAnnotation,
        Super,
        SwitchCase,
        SwitchStatement,
        SymbolTypeAnnotation,
        TSAnyKeyword,
        TSArrayType,
        TSAsExpression,
        TSBigIntKeyword,
        TSBooleanKeyword,
        TSCallSignatureDeclaration,
        TSConditionalType,
        TSConstructSignatureDeclaration,
        TSConstructorType,
        TSDeclareFunction,
        TSDeclareMethod,
        TSEnumDeclaration,
        TSEnumMember,
        TSExportAssignment,
        TSExpressionWithTypeArguments,
        TSExternalModuleReference,
        TSFunctionType,
        TSImportEqualsDeclaration,
        TSImportType,
        TSIndexSignature,
        TSIndexedAccessType,
        TSInferType,
        TSInstantiationExpression,
        TSInterfaceBody,
        TSInterfaceDeclaration,
        TSIntersectionType,
        TSIntrinsicKeyword,
        TSLiteralType,
        TSMappedType,
        TSMethodSignature,
        TSModuleBlock,
        TSModuleDeclaration,
        TSNamedTupleMember,
        TSNamespaceExportDeclaration,
        TSNeverKeyword,
        TSNonNullExpression,
        TSNullKeyword,
        TSNumberKeyword,
        TSObjectKeyword,
        TSOptionalType,
        TSParameterProperty,
        TSParenthesizedType,
        TSPropertySignature,
        TSQualifiedName,
        TSRestType,
        TSSatisfiesExpression,
        TSStringKeyword,
        TSSymbolKeyword,
        TSThisType,
        TSTupleType,
        TSTypeAliasDeclaration,
        TSTypeAnnotation,
        TSTypeAssertion,
        TSTypeLiteral,
        TSTypeOperator,
        TSTypeParameter,
        TSTypeParameterDeclaration,
        TSTypeParameterInstantiation,
        TSTypePredicate,
        TSTypeQuery,
        TSTypeReference,
        TSUndefinedKeyword,
        TSUnionType,
        TSUnknownKeyword,
        TSVoidKeyword,
        TaggedTemplateExpression,
        TemplateElement,
        TemplateLiteral,
        ThisExpression,
        ThisTypeAnnotation,
        ThrowStatement,
        TopicReference,
        TryStatement,
        TupleExpression,
        TupleTypeAnnotation,
        TypeAlias,
        TypeAnnotation,
        TypeCastExpression,
        TypeParameter,
        TypeParameterDeclaration,
        TypeParameterInstantiation,
        TypeofTypeAnnotation,
        UnaryExpression,
        UnionTypeAnnotation,
        UpdateExpression,
        V8IntrinsicIdentifier,
        VariableDeclaration,
        VariableDeclarator,
        Variance,
        VoidTypeAnnotation,
        WhileStatement,
        WithStatement,
        YieldExpression
    };

    class Var
    {
    private:
        VarType type;
        std::any _value;

    public:
        /**
         * 取值
         */
        template <typename T>
        T value()
        {
            return std::any_cast<T>(_value);
        };

        /**
         * 赋值
         */
        void value(VarType type, std::any value)
        {
            this->type = type;
            this->_value = value;
        };
    };

    class Any
    {
    private:
        std::string _type;
        std::any _value;

    public:
        /**
         * 取值
         */
        template <typename T>
        T value()
        {
            return std::any_cast<T>(_value);
        };

        /**
         * 赋值
         */
        void value(std::string type, std::any value)
        {
            this->_type = type;
            this->_value = value;
        };

        std::string type()
        {
            return _type;
        };
    };

    class AnyNode
    {
    private:
        std::string _type;
        ast::BaseNode* _value;

    public:
        /**
         * 取值
         */
        template <typename T>
        T value()
        {
            return dynamic_cast<T>(_value);
        };

        /**
         * 赋值
         */
        void value(ast::BaseNode *value)
        {
            this->_type = value -> type;
            this->_value = value;
        };

        std::string type()
        {
            return _type;
        };
    };
};

#endif // BABEL_TYPES_VAR
