//
// Created by devhg on 2021/5/15.
//

#include "Student.h"
#include <iostream>

Student::Student(const std::string &name, int age) : name(name), age(age) {}

Student::~Student() {
    std::cout << "destroy" << std::endl;
};

const std::string &Student::getName() const {
    return name;
}

void Student::setName(const std::string &name) {
    Student::name = name;
}

int Student::getAge() const {
    return age;
}

void Student::setAge(int age) {
    Student::age = age;
}
