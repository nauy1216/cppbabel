#ifndef TEST_utils_struct
#define TEST_utils_struct
#include <string>

using namespace std;

namespace utils_struct
{
    struct Student
    {
    public:
        int age;
        string name;
        Student(int age, string name) : age(age), name(name){};
    };
}
#endif // TEST_utils_struct