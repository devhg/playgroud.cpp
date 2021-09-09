//
// Created by devhg on 2021/8/24.
//

#include "base.h"

#include <utility>

base::User::User(int age, std::string name) : _age(age), _name(std::move(name)) {}

int base::User::getAge() const {
    return _age;
}

void base::User::setAge(int age) {
    _age = age;
}

const std::string &base::User::getName() const {
    return _name;
}

void base::User::setName(const std::string &name) {
    _name = name;
}

/////////////////////////////////////////////////////////////