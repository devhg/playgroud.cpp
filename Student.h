//
// Created by devhg on 2021/5/15.
//

#ifndef PLAYGROUD_CPP_STUDENT_H
#define PLAYGROUD_CPP_STUDENT_H


#include <string>

class Student {
public:
    Student(const std::string &name, int age);

    const std::string &getName() const;

    void setName(const std::string &name);

    int getAge() const;

    void setAge(int age);

    virtual ~Student();

public:
    std::string name;
private:
    int age;
};


#endif //PLAYGROUD_CPP_STUDENT_H
