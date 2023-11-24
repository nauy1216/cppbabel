#ifndef BABEL_TYPES_AST_H_
#define BABEL_TYPES_AST_H_
#define DTYPE(x) string type = #x;

#define D_SIMPLE_STRUCT(StructName) \
    struct StructName : BaseNode    \
    {                               \
        DTYPE(StructName);          \
    }

#define DSTRUCT(StructName) \
    struct StructName : BaseNode

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
};

/**
 * 注意: rttr不能反射const属性
 */
#define RTTR(sn, attrs)               \
    static void registerRttr()        \
    {                                 \
        registration::class_<sn>(#sn) \
            .constructor<>()          \
                attrs;                \
    }

#define ATTR9(sn, p1, p2, p3, p4, p5, p6, p7, p8, p9) \
    .property(#p1, &sn::p1)                           \
        .property(#p2, &sn::p2)                       \
        .property(#p3, &sn::p3)                       \
        .property(#p4, &sn::p4)                       \
        .property(#p5, &sn::p5)                       \
        .property(#p6, &sn::p6)                       \
        .property(#p7, &sn::p7)                       \
        .property(#p8, &sn::p8)                       \
        .property(#p9, &sn::p9)

#define ATTR8(sn, p1, p2, p3, p4, p5, p6, p7, p8) \
    .property(#p1, &sn::p1)                       \
        .property(#p2, &sn::p2)                   \
        .property(#p3, &sn::p3)                   \
        .property(#p4, &sn::p4)                   \
        .property(#p5, &sn::p5)                   \
        .property(#p6, &sn::p6)                   \
        .property(#p7, &sn::p7)                   \
        .property(#p8, &sn::p8)

#define ATTR7(sn, p1, p2, p3, p4, p5, p6, p7) \
    .property(#p1, &sn::p1)                   \
        .property(#p2, &sn::p2)               \
        .property(#p3, &sn::p3)               \
        .property(#p4, &sn::p4)               \
        .property(#p5, &sn::p5)               \
        .property(#p6, &sn::p6)               \
        .property(#p7, &sn::p7)

#define ATTR6(sn, p1, p2, p3, p4, p5, p6) \
    .property(#p1, &sn::p1)               \
        .property(#p2, &sn::p2)           \
        .property(#p3, &sn::p3)           \
        .property(#p4, &sn::p4)           \
        .property(#p5, &sn::p5)           \
        .property(#p6, &sn::p6)

#define ATTR5(sn, p1, p2, p3, p4, p5) \
    .property(#p1, &sn::p1)           \
        .property(#p2, &sn::p2)       \
        .property(#p3, &sn::p3)       \
        .property(#p4, &sn::p4)       \
        .property(#p5, &sn::p5)

#define ATTR4(sn, p1, p2, p3, p4) \
    .property(#p1, &sn::p1)       \
        .property(#p2, &sn::p2)   \
        .property(#p3, &sn::p3)   \
        .property(#p4, &sn::p4)

#define ATTR3(sn, p1, p2, p3)   \
    .property(#p1, &sn::p1)     \
        .property(#p2, &sn::p2) \
        .property(#p3, &sn::p3)

#define ATTR2(sn, p1, p2)   \
    .property(#p1, &sn::p1) \
        .property(#p2, &sn::p2)

#define ATTR1(sn, p1) \
    .property(#p1, &sn::p1)

#endif // BABEL_TYPES_AST_H_