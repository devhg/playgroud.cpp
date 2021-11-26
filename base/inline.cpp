#include <iostream>
#include "fmt/format.h"

/**
 * 编译器对 inline 函数的处理步骤
 * 将 inline 函数体复制到 inline 函数调用点处；
 * 为所用 inline 函数中的局部变量分配内存空间；
 * 将 inline 函数的的输入参数和返回值映射到调用方法的局部变量空间中；
 * 如果 inline 函数有多个返回点，将其转变为 inline 函数代码块末尾的分支（使用 GOTO）。
 */

// 内联能提高函数效率，但并不是所有的函数都定义成内联函数！内联是以代码膨胀(复制)为代价，仅仅省去了函数调用的开销，从而提高函数的执行效率。
// 如果执行函数体内代码的时间相比于函数调用的开销较大，那么效率的收货会更少！
// 另一方面，每一处内联函数的调用都要复制代码，将使程序的总代码量增大，消耗更多的内存空间。
// 以下情况不宜用内联：
// （1）如果函数体内的代码比较长，使得内联将导致内存消耗代价比较高。
// （2）如果函数体内出现循环，那么执行函数体内代码的时间要比函数调用的开销大。

class Base {
public:
    // 虚函数可以是内联函数，但是当虚函数表现多态性的时候不能内联。
    // 内联是在编译器建议编译器内联，而虚函数的多态性在运行期，编译器无法知道运行期调用哪个代码，因此虚函数表现为多态性时（运行期）不可以内联。
    inline virtual void who() {
        fmt::print("base\n");
    }

    // 类中定义了的函数是隐式内联函数
    // 声明的函数要想成为内联函数，必须在实现处(定义处)加inline关键字。
    void Foo(int x, int y) {
        ///< 定义即隐式内联函数！
    };

    void f1(int x); ///< 声明后，要想成为内联函数，必须在定义处加inline关键字。

    virtual ~Base() {
        fmt::print("base ~\n");
    };
};

// 定义处加inline关键字，推荐这种写法！
inline void A::f1(int x) {}

class Derived : public Base {
    inline void who() override { // 不写inline时隐式内联
        fmt::print("derived\n");
    }

    ~Derived() override {
        fmt::print("derived ~\n");
    };
};

int main() {
    // 此处的虚函数 who()，是通过类（Base）的具体对象（b）来调用的，
    // 编译期间就能确定了，所以它可以是内联的，但最终是否内联取决于编译器。
    Base b;
    b.who();

    // 此处的虚函数是通过指针调用的，呈现多态性，需要在运行时期间才能确定，所以不能为内联。
    Base *ptr = new Derived();
    ptr->who();

    // 因为Base有虚析构函数（virtual ~Base() {}），
    // 所以 delete 时，会先调用派生类（Derived）析构函数，
    // 再调用基类（Base）析构函数，防止内存泄漏。
    delete ptr;
    ptr = nullptr;
    return 0;
}