#ifndef BABEL_TYPES_AST_MACRO_H_
#define BABEL_TYPES_AST_MACRO_H_
#define DTYPE(x) string type = #x;

#define D_SIMPLE_STRUCT(StructName) \
    struct StructName : BaseNode    \
    {                               \
        DTYPE(StructName);          \
    }

#define DSTRUCT(StructName) \
    struct StructName : BaseNode

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

#endif // BABEL_TYPES_AST_MACRO_H_