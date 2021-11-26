/**
 * 拷贝，移动构造
 */
#include <iostream>
#include <algorithm>
#include <set>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

class Person {
public:
    explicit Person(std::string _name = "", int _age = 0) : name(std::move(_name)), age(_age) {
        std::cout << "constructor" << std::endl;
    };

    Person(const char *a) {
        name = a;
        printf("constructor const char *\n");
    }

    Person(const Person &p) {
        std::cout << "&copy constructor" << std::endl;
    }

    Person &operator=(const Person &p) {
        printf("&move constructor new=%p, temp=%p ", this, &p);
        return *this;
    }


    Person(const Person &&p) noexcept {
        std::cout << "&&move constructor" << std::endl;
    }

    Person &operator=(Person &&p) noexcept {
        printf("&&move constructor new=%p, temp=%p ", this, &p);
        return *this;
    }

    ~Person() {
        printf(" | dieObj=%p [%s %d destructor]\n", this, name.c_str(), age);
    }

private:
    int         age{};
    std::string name;
};

int main() {
    cout << "---------------普通构造--------------" << endl;
    Person b1("a", 1);
    Person b11 = Person("a", 11);

    cout << "---------------普通-右值引用构造----------(先普通构造临时对象，再移动构造)" << endl;
    b1        = Person("b", 2);

    // auto ps   = vector<Person>();
    // ps.emplace_back("1", 2);
    // ps.emplace_back("2", 2);
    // ps.emplace_back("3", 2);
    // ps.emplace_back("4", 2);

    cout << "---------------拷贝构造--------------" << endl;
    // Person(const Person &b) 拷贝构造
    Person b2(b1);
    Person b3 = b1;

    cout << "---------------移动构造--------------" << endl;
    // Person &operator=(const Person &b) 移动构造
    b3 = b2;

    cout << "\n---------------自定义构造--------------" << endl;
    // Person(const char *a)
    Person b4("Asdad");

    cout << "---------------普通-右值引用构造--------------" << endl;
    // 1. Person(const char *a)
    // 2. Person &operator=(const Person &&b)
    b4 = "qeqeqee"; // 应该禁止，存在歧义，拒绝隐式类型转换

    cout << "---------------shared_ptr--------------" << endl;
    std::shared_ptr<Person> p3  = std::make_shared<Person>("21", 10);

    // 调用拷贝构造函数
    std::shared_ptr<Person> p4(p3);
    // 或者
    std::shared_ptr<Person> p44 = p3;

    // 调用移动构造函数
    // std::shared_ptr<Person> p5(std::move(b4));
    // 或者
    std::shared_ptr<Person> p55 = std::move(p4);

    cout << "---------------die--------------" << endl;
    return 0;
}


/*#include <iostream>
#include "vector"

class A {
public:
    int *pointer;

    A() : pointer(new int(1)) {
        std::cout << "构造" << pointer << std::endl;
    }

    A(A &a) : pointer(new int(*a.pointer)) {
        std::cout << "拷贝" << pointer << std::endl;
    } // 无意义的对象拷贝

    A(A &&a)  noexcept : pointer(a.pointer) {
        a.pointer = nullptr;
        std::cout << "移动" << pointer << std::endl;
    }

    ~A() {
        std::cout << "析构" << pointer << std::endl;
        delete pointer;
    }
};

// 防止编译器优化
A return_rvalue(bool test) {
    A a, b;
    A c(a);
    if (test) return a; // 等价于 static_cast<A&&>(a);
    else return b;     // 等价于 static_cast<A&&>(b);
}

int main() {
    A obj = return_rvalue(false);
    std::cout << "obj:" << std::endl;
    std::cout << obj.pointer << std::endl;
    std::cout << *obj.pointer << std::endl;
    return 0;
}*/