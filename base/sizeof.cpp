#include <iostream>
#include "fmt/format.h"

// 首先来个总结，然后下面给出实际例子，实战！
//
// 1. 空类的大小为1字节
// 2. 一个类中，虚函数本身、成员函数（包括静态与非静态）和静态数据成员都是不占用类对象的存储空间。
// 3. 对于包含虚函数的类，不管有多少个虚函数，只有一个虚函数表指针,vptr的大小=8。
// 4. 普通继承，派生类继承了所有基类的函数与成员，要按照义工的字节对齐来计算大小
// 5. 虚函数继承，不管是单继承还是多继承，都是继承了基类的vptr。(32位操作系统4字节，64位操作系统 8字节)！
// 6. 虚继承,继承多个基类的vptr，派生类虚继承多个虚函数，会继承所有虚函数的vptr

class A {
};

class B {
public:
    char       a = 'a';
    static int b;
    static int c;

    virtual void who() {};

    void hi() {};
};

class C {
public:
    virtual void fun() = 0;

    virtual void fun1() = 0;

    virtual void fun2() = 0;

    virtual void fun3() {};
};

class D {
public:
    char a; // 1
    int  b; // 4
};

/**
 * @brief 此时E按照顺序：
 * char a
 * int b
 * short a
 * long b
 * 根据字节对齐4+4=8+8+8=24
 */
class E : D {
public:
    short a; // 2
    long  b; // 8
};

class D1 {
    virtual void fun() {}
};

class E1 : public D1 {
};

class AA {
    virtual void fun() = 0;
};

class BB {
    virtual void fun2() = 0;
};

// 派生类虚继承多个虚函数，会继承所有虚函数的vptr
class CC : virtual public AA, virtual public BB {
public:
    virtual void fun() {}

    virtual void fun2() {}

    virtual void fun3() {}
};


int main() {
    std::cout << sizeof(A) << std::endl; // 规则1

    // 16 字节对齐、静态变量不影响类的大小、vptr指针=8
    std::cout << sizeof(B) << std::endl; // 规则2

    // 8 字节对齐、静态变量不影响类的大小、vptr指针=8
    std::cout << sizeof(C) << std::endl; // 规则3

    std::cout << sizeof(E) << std::endl; // 规则4
    std::cout << sizeof(E1) << std::endl; // 规则5

    // 8 8 16  派生类虚继承多个虚函数，会继承所有虚函数的vptr
    std::cout << sizeof(CC) << std::endl; // 规则6
    return 0;
}