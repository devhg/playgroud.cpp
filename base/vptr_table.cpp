#include <iostream>
#include "fmt/format.h"

using namespace std;

// 函数指针
typedef void (*Fun)();

class Base {
public:
    Base() = default;;

    virtual void fun1() {
        cout << "Base::fun1()" << endl;
    }

    virtual void fun2() {
        cout << "Base::fun2()" << endl;
    }

    virtual void fun3() {}

    ~Base() = default;
};

class Derived : public Base {
public:
    Derived() = default;;

    void fun1() override {
        cout << "Derived::fun1()" << endl;
    }

    void fun2() override {
        cout << "Derived::fun2()" << endl;
    }

    ~Derived() = default;;
};

// 获取vptr地址与func地址,vptr指向的是一块内存，这块内存存放的是虚函数地址，这块内存就是我们所说的虚表
Fun getAddr(void *obj, unsigned int offset) {
    cout << "=======================" << endl;
    // 64位操作系统，占8字节，通过*(unsigned long *)obj取出前8字节，即vptr指针
    void *vptr_addr = (void *) *(unsigned long *) obj;
    printf("vptr_addr:%p\n", vptr_addr);

    // 通过vptr指针访问virtual table，因为虚表中每个元素(虚函数指针)在64位编译器下是8个字节，
    // 因此通过*(unsigned long *)vptr_addr取出前8字节，后面加上偏移量就是每个函数的地址！
    void *func_addr = (void *) *((unsigned long *) vptr_addr + offset);
    printf("func_addr:%p\n", func_addr);
    return (Fun) func_addr;
}

int main() {
    Base    ptr;
    Derived d;
    Base    &pp = ptr; // 基类引用指向基类实例
    Base    *pt = new Derived(); // 基类指针指向派生类实例
    Base    &p  = d; // 基类引用指向派生类实例

    cout << "基类对象直接调用" << endl;
    ptr.fun1();
    cout << "基类对象调用基类实例" << endl;
    pp.fun1();
    cout << "基类指针指向派生类实例并调用虚函数" << endl;
    pt->fun1();
    cout << "基类引用指向派生类实例并调用虚函数" << endl;
    p.fun1();

    // 手动查找vptr 和 vtable
    Fun f1 = getAddr(pt, 0);
    (*f1)();
    Fun f2 = getAddr(pt, 1);
    (*f2)();
    delete pt;
    return 0;
}