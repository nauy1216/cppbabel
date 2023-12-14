#ifndef TEST_BABEL_base_class
#define TEST_BABEL_base_class
#include <string>
#include "gtest/gtest.h"
#include "babel-log/log.h"
#include "dbg.h"

using namespace std;

/**
1. 前置声明： 当使用前向引用声明时，只能使用被声明的符号，而不能涉及类的任何细节。
2. static
 */

namespace base_class
{
    Logger log(__FILE__);

    class A
    {
    public:
        A()
        {
            cout << "Constructing A" << endl;
            age = 12;
        }
        ~A() { cout << "Destructing A" << endl; }
        int age;
    };
    class B
    {
    public:
        B() { cout << "Constructing B" << endl; }
        ~B() { cout << "Destructing B" << endl; }
    };

    class C
    {
    public:
        C() { cout << "Constructing C" << endl; }
        ~C() { cout << "Destructing C" << endl; }
        B b;
        A a;
    };

    class D
    {
    public:
        D() { cout << "Constructing D" << endl; }
        ~D() { cout << "Destructing D" << endl; }
        B *b;
        A *a;
    };

    // 执行结果
    // Constructing B
    // Constructing A
    // Constructing C
    // Destructing C
    // Destructing A
    // Destructing B
    void test_ctor_c()
    {
        std::cout << "【test_ctor_c】" << endl;
        C c;
    };

    // 执行结果  创建D的时候， A和B不会创建
    // Constructing D
    // Constructing A
    // d.a->age12
    // Destructing A
    // Destructing D
    void test_ctor_d()
    {
        std::cout << "【test_ctor_d】" << endl;
        D d;
        A a;
        d.a = &a;
        std::cout << "d.a->age" << d.a->age << endl;
    };

    TEST(test_base_class, base_class__create)
    {
        std::cout << "【class】" << endl;
        test_ctor_c();
        test_ctor_d();
    }

    class Base
    {
    private:
        int x;

    public:
        Base(int a)
        {
            x = a;
            cout << "Base constructor x=" << x << endl;
        }
        ~Base() { cout << "Base destructor..." << endl; }
    };
    class Derived : public Base
    {
    private:
        int y;

    public:
        Derived(int a, int b) : Base(a)
        { // 派生类构造函数的初始化列表
            y = b;
            cout << "Derived constructor y=" << y << endl;
        }
        ~Derived() { cout << "Derived destructor..." << endl; }
        A a;
    };

    TEST(test_base_class, base_class__extend)
    {
        std::cout << "【class】" << endl;
        // 执行结果，构造函数的执行顺序
        // 1. 父类构造函数 2.类成员的构造函数 3. 自己的构造函数
        // Base constructor x=1
        // Constructing A
        // Derived constructor y=2
        // Derived destructor...
        // Destructing A
        // Base destructor...
        Derived d(1, 2);
    }

    class DefaultConstructor : B
    {
    public:
        int age;
    };

    TEST(test_base_class, base_class__default_constructor)
    {
        std::cout << "【class】" << endl;

        // Constructing B
        // d.age  170872912 // 内存中的历史数据
        // Destructing B
        DefaultConstructor d;
        std::cout << "d.age  " << d.age << endl;
    }

    class Point
    {
    protected:
        int x, y;

    public:
        Point(int a, int b = 0)
        {
            x = a;
            y = b;
            cout << "constructing point(" << x << "," << y << ")" << endl;
        }
    };
    class Line : public Point
    {
    protected:
        int len;

    public:
        Line(int a, int b, int l) : Point(a, b)
        { // 构造函数初始化列表
            len = l;
            cout << "Constructing Line,len ..." << len << endl;
        }
    };

    TEST(test_base_class, base_class__params)
    {
        std::cout << "【class】" << endl;
        // constructing point(1,2)
        // Constructing Line,len ...3
        Line line(1, 2, 3);
    };

    TEST(test_base_class, base_class__private_protectd_public){
        // private成员只能被该类的成员函数访问，外部无法访问。
        // protected成员可以被该类的成员函数和派生类的成员函数访问。
        // public成员可以被类的成员函数、派生类的成员函数和类的对象访问。

    };

    TEST(test_base_class, base_class__private_protectd_public_extend){
        //  private 继承: 在私有继承中，基类的公有和保护成员在派生类中都变成了私有成员，派生类的对象无法直接访问它们，而只能通过基类的公有和保护成员函数来间接访问。
        //  protected 继承：基类的公有成员在派生类中变成了保护成员，基类的保护成员在派生类中仍然是保护成员。派生类的对象可以访问这些成员，但对于外部来说，它们仍然是不可见的。
        //  public 继承：基类的公有成员在派生类中仍然是公有成员，基类的保护成员在派生类中仍然是保护成员。这是最常见的继承方式，也是 C++ 中默认的继承方式。

    };

    class DiamondA
    {
    public:
        void vf() { cout << "I come from class DiamondA" << endl; }
    };
    class DiamondB : public DiamondA
    {
    };
    class DiamondC : public DiamondA
    {
    };
    class DiamondD : public DiamondB, public DiamondC
    {
    };

    // 菱形继承的问题
    // 1. 存储了2份DiamondA，浪费存储空间
    // 2. 访问DiamondA的属性时，存在二义性问题
    TEST(test_base_class, base_class__diamond_extend)
    {
        DiamondD diamondD;
        // error: base_class::DiamondD::vf 不明确
        // diamondD.vf();
    };

    class DiamondVirtualB : virtual public DiamondA
    {
    };
    class DiamondVirtualC : virtual public DiamondA
    {
    };

    class DiamondVirtualD : public DiamondVirtualB, public DiamondVirtualC
    {
    };

    // @TODO: 虚继承
    TEST(test_base_class, base_class__diamond_virtual_extend)
    {
        DiamondVirtualD diamondD;
        // ok
        diamondD.vf();
    };

    class Figure
    {
    protected:
        double x, y;

    public:
        void set(double i, double j)
        {
            x = i;
            y = j;
        }
        // 虚函数
        virtual double getx()
        {
            cout << "Figure getx: " << x << endl;
            return x;
        }
        // 纯虚函数
        virtual void area() = 0;
    };

    class Trianle : public Figure
    {
    public:
        void area() { cout << "Trianle：" << x * y * 0.5 << endl; };
        double getx()
        {
            cout << "Trianle getx: " << x << endl;
            return x;
        };
    };
    class Rectangle : public Figure
    {
    public:
        void area() { cout << "Rectangle：" << x * y << endl; };
    };

    // @TODO: 抽象类
    TEST(test_base_class, base_class__abstract)
    {
        // 定义抽象类指针
        Figure *pF = NULL;
        // Figure f1; 抽象类不能被实例化
        Rectangle r;
        Trianle t;

        t.set(10, 20);
        t.getx();
        pF = &t;
        pF->area(); // 执行的是子类的area方法
        pF->getx(); // 如果父类的getx是虚函数，则执行的是子类的getx, 否则执行的是父类的getx方法

        r.set(10, 20);
        pF = &r;
        pF->area(); // 执行的是子类的area方法
        pF->getx(); // 执行的是父类的getx方法

        // 定义抽象类引用
        Figure &rF = t;
        rF.set(20, 20);
        rF.area();
    };

    // 基类
    class Shape
    {
    public:
        // 虚函数，用于派生类重写
        virtual void draw() const
        {
            std::cout << "Drawing a shape\n";
        }
    };

    // 派生类，重写基类的虚函数
    class Circle : public Shape
    {
    public:
        void draw() const override
        {
            std::cout << "Drawing a circle\n";
        }
    };

    // 派生类，重写基类的虚函数
    class Square : public Shape
    {
    public:
        // @Note: 必须加 override
        void draw() const override
        {
            std::cout << "Drawing a square\n";
        }
    };

    // @TODO: 虚函数
    // 虚函数（Virtual Function）是面向对象编程中的一个重要概念，它具有多态性，能够在运行时动态绑定到实际的函数实现。虚函数的主要作用包括以下几点：
    // 1. 实现多态：虚函数为多态性提供了基础。通过基类指针或引用调用虚函数时，实际调用的是指向或引用的对象的实际类型的函数实现。
    // 2. 运行时动态绑定：虚函数的一个关键特性是在运行时动态绑定。也就是说，程序在运行时根据对象的实际类型来确定调用的是哪个版本的虚函数。这与静态绑定相对，静态绑定是在编译时确定的，而虚函数能够在运行时根据对象的类型进行绑定。
    // 3. 实现抽象类和接口：虚函数可以用来定义抽象类，抽象类中包含纯虚函数，这些函数没有具体的实现，由派生类来实现。抽象类常常用于定义接口，通过派生类来提供具体的实现，从而实现接口的统一。
    TEST(test_base_class, base_class__virtual_function)
    {
        Circle circle;
        Square square;

        // 使用基类指针调用虚函数，实现多态性
        Shape *shapePtr1 = &circle;
        Shape *shapePtr2 = &square;

        shapePtr1->draw(); // 实际调用 Circle 类的 draw 函数
        shapePtr2->draw(); // 实际调用 Square 类的 draw 函数
    };

    // 基类
    class VirtualDestructorBase
    {
    public:
        // 虚析构函数
        virtual ~VirtualDestructorBase()
        {
            dbg("Base destructor\n");
        }
    };

    // 派生类
    class VirtualDestructorDerived : public VirtualDestructorBase
    {
    public:
        // 派生类的析构函数
        ~VirtualDestructorDerived() override
        {
            dbg("Derived destructor\n");
        }
    };

    // @TODO 虚析构函数
    // 当基类指针指向派生类对象并且通过这个指针删除对象时，如果基类的析构函数不是虚函数，就可能导致只调用基类的析构函数，
    // 而不调用派生类的析构函数。这可能导致资源泄漏或未正确释放派生类的资源。
    TEST(test_base_class, base_class__virtual_destructor){
        std::cout << "【virtual_destructor】" << endl;
        // 使用基类指针指向派生类对象
        VirtualDestructorBase* basePtr = new VirtualDestructorDerived;

        // 删除对象，触发虚析构函数的调用
        delete basePtr;
    };

}
#endif // TEST_BABEL_base_class