#include <Windows.h>
#include "pch.h"


struct Student
{
    char* name;
    int age;
    double average;
    char* university;
    Student() = default;
    Student(char* name, int age, double average, char* university) :
        name(name), age(age), average(average), university(university) 
    {
        std::cout << "CREATED NEW STUDENT\n";
    }

    Student& operator=(Student&& other)
    {
        this->name = std::move(other.name);
        this->age = std::exchange(other.age, 0);
        this->average = std::exchange(other.average, 0);
        this->university = std::move(other.university);
        return *this;
    }

    ~Student()
    {
        std::cout << age;
        std::cout << "STUDENT DELETED\n";
    }
};

void init_array(Student*&students, const int& size)
{
    std::cout << "GENIUS LOG [TM] init_array entered\n";
    //delete[] students;
    //std::cout << "GENIUS LOG [TM] students deleted\n";
    //students = new Student[size];
    //std::cout << "GENIUS LOG [TM] students new\n";

    if (size == 8)
    {
        students[0] = std::move(Student((char*)"Maksym Rasakhatskyi", 20, 82, (char*)"KNU"));
        students[1] = Student((char*)"Maksym Kurochka", 100, 99.9, (char*)"Somewhere in Dnipro");
        students[2] = Student((char*)"Maksym Nedeshev", 21, 54.1, (char*)"NUBiP");
        students[3] = Student((char*)"Maksym Myskam", 111111, 22.22, (char*)"KPI");
        students[4] = Student((char*)"Maksim Moskal", 11, 12, (char*)"13");
        students[5] = Student((char*)"Maksym Ovochevyi", 21, 66.6, (char*)"NUBiP");
        students[6] = Student((char*)"Maksym Nonamesky", 33, 3.14, (char*)"KPI");
        students[7] = Student((char*)"Maksym Butolder", 42, 42, (char*)"KNU");
    }
    else
    {
        for (int i = 0; i < size; ++i)
            students[i] = Student(
                const_cast<char*>("name"),
                i,
                i / 2.0,
                const_cast<char*>("univ"));
    }

    std::cout << "GENIUS LOG [TM] students assigned\n";
}



extern "C"
{
    __declspec(dllexport) void GetStudents(Student*&students, int size)
    {
        std::cout << "GENIUS LOG [TM] GetStudents entered\n";
        init_array(students, size);
        std::cout << "GENIUS LOG [TM] GetStudents exited\n";
    }

    __declspec(dllexport) void Clear(Student* students)
    {
        delete[] students;
        students = nullptr;
    }
    __declspec(dllexport) void HelloWorld()
    {
        MessageBox(0, L"Hello World from DLL!\n", L"Hi", MB_ICONINFORMATION);
    }
    __declspec(dllexport) void ShowMe()
    {
        MessageBox(0, L"How are u?", L"Hi", MB_ICONINFORMATION);
    }
}