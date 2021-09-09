//
// Created by devhg on 2021/8/24.
//

#ifndef PLAYGROUND_CPP_BASE_H
#define PLAYGROUND_CPP_BASE_H


#include <string>
#include <iostream>

namespace base {
    class User {
    public:
        User(int age, std::string name);

        int getAge() const;

        void setAge(int age);

        const std::string &getName() const;

        void setName(const std::string &name);

    private:
        int _age;
        std::string _name;
    };

    template<class T, size_t size>
    class MArray {
    public:
        MArray(const std::initializer_list<T> &data) : _data(data) {
            for (auto i : data) {
                std::cout << i << std::endl;
            }
        }

        void Travel();

    private:
        std::vector<T> _data;
    };

    template<class T, size_t size>
    void MArray<T, size>::Travel() {
        for (int i = 0; i < size; ++i) {
            std::cout << _data[i] << std::endl;
        }

        for (auto ele : _data) {
            std::cout << ele << std::endl;
        }
    }
}
#endif //PLAYGROUND_CPP_BASE_H
