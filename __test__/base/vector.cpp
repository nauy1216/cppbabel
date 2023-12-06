#ifndef TEST_base_vector
#define TEST_base_vector

#include "gtest/gtest.h"
#include <vector>
#include <iostream>
#include "babel-log/log.h"

using namespace std;

namespace base_vector
{
    Logger log(__FILE__);

    struct Student
    {
    public:
        int age;
        string name;
        Student(int age, string name) : age(age), name(name){};
    };

    void printVector(vector<Student> &v)
    {
        log.Info("printVector");
        for (auto it = v.begin(); it != v.end(); ++it)
        {
            log.Info(" age => ");
            log.Info(it->age);
        };
        log.Endl(__LINE__);
    };

    TEST(TEST_base_vector_test, base_vector_)
    {

        Student s1(18, "s1");

        vector<Student> v = {s1};
        v.push_back(Student(20, "s2"));

        printVector(v);
    }
}
#endif // TEST_base_vector