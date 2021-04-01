#include <stdio.h>	/* Include that here, to make sure __P gets defined */
#include <fcntl.h>	/* For open and flags */
#include <Windows.h>
#include <iostream>
#include <string>

struct Student
{
    char* name;
    int age;
    double average;
    char* university;
};

typedef void (CALLBACK* GetStudents_T)(Student* students, int size);
GetStudents_T GetStudents;    // Function pointer

//typedef void (CALLBACK* Clear_T)(Student* studens);
//Clear_T Clear;    // Function pointer

std::wstring s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

int main()
{
    std::string filename = "F:\\Code\\Apriorit\\Test DLL\\Test_dll\\x64\\Release\\my_dll.dll";

    std::wstring tmp = s2ws(filename);
    HINSTANCE hGetProcIDDLL = LoadLibrary(tmp.c_str());
    GetStudents = (GetStudents_T)GetProcAddress(hGetProcIDDLL, "GetStudents");
   /* Clear = (Clear_T)GetProcAddress(hGetProcIDDLL, "Clear");*/
    Student* students = new Student[8];
    GetStudents(students, 8);

    //Clear(students);
    for (int i = 0; i < 8; i++)
    {
        std::cout << "Name: " << students[i].name << "\n";
        std::cout << "Age : " << students[i].age << "\n";
        std::cout << "Avg : " << students[i].average << "\n";
        std::cout << "univ: " << students[i].university << "\n";
        std::cout << "\n";
    }
}