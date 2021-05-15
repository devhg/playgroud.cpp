#include <iostream>
#include "Student.h"

int main() {
    auto *s = new Student("devhg", 21);

    std::cout << s->getName() << " : " << s->getAge() << std::endl;

    s->setName("12313");
    s->setAge(233);
    std::cout << s->getName() << " : " << s->getAge() << std::endl;

    delete (s);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
