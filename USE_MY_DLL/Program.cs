using System;
using System.Runtime.InteropServices;

namespace USE_MY_DLL
{
    class Program
    {
        const string path = @"F:\Code\Apriorit\USE_MY_DLL\x64\Release\my_dll.dll";

        [StructLayout(LayoutKind.Sequential)]
        public struct Student
        {
            public string name;
            public int age;
            public double average;
            public string university;
        };


        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void HelloWorld();

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void ShowMe();


        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void GetStudents(
            IntPtr pointArray,
            int size);


        static void Main(string[] args)
        {
            int size = 8;
            Student[] students = new Student[size];
            IntPtr ptr = Marshal.AllocHGlobal(Marshal.SizeOf(students[0]) * size);

            long intPtr = ptr.ToInt64(); // Must work both on x86 and x64
            for (int i = 0; i < students.Length; i++)
            {
                IntPtr RectPtr = new IntPtr(intPtr);
                Marshal.StructureToPtr(students[i], RectPtr, false);
                intPtr += Marshal.SizeOf(typeof(Student));
            }
            var p = new IntPtr(intPtr);
            GetStudents(p, size);

            //var stud2 = Marshal.PtrToStructure<Student[]>(ptr);

            foreach (var student in students)
            {
                Console.WriteLine($"Name: {student.name}\nAge: {student.age}\nAverage: {student.average}\nUniversity: {student.university}\n\n");
            }
        }
    }
}


//int size = 8;
//Student[] students = new Student[size];
//IntPtr ptr = Marshal.AllocHGlobal(Marshal.SizeOf(students[0]) * size);

//long intPtr = ptr.ToInt64(); // Must work both on x86 and x64
//for (int i = 0; i < students.Length; i++)
//{
//    IntPtr RectPtr = new IntPtr(intPtr);
//    Marshal.StructureToPtr(students[i], RectPtr, false);
//    intPtr += Marshal.SizeOf(typeof(Student));
//}

//GetStudents(intPtr, size);

//var stud2 = Marshal.PtrToStructure<Student[]>(ptr);

//foreach (var student in stud2)
//{
//    Console.WriteLine($"Name: {student.name}\nAge: {student.age}\nAverage: {student.average}\nUniversity: {student.university}\n\n");
//}