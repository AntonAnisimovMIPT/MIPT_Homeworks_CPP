#include <iostream>
#include <string>

auto const max_num_les = 3;
auto const max_num_st = 2;

struct Lesson;

struct Student {

    std::string student_name{};
    Lesson** lessons = new Lesson*[max_num_les]{};

};

struct Lesson {

    std::string lesson_name{};
    Student** students = new Student*[max_num_st]{};

};


int main() {

    Student st1{.student_name = "Andrew"};
    Student st2{.student_name = "Oleg"};

    Lesson ls1{.lesson_name = "Math"};
    Lesson ls2{.lesson_name = "Bio"};
    Lesson ls3{.lesson_name = "Geo"};


    st1.lessons[0] = &ls1;
    st1.lessons[1] = &ls2;
    st1.lessons[2] = &ls3;

    st2.lessons[0] = &ls1;

    /////////////////////

    ls1.students[0] = &st1;
    ls1.students[1] = &st2;

    ls2.students[0] = &st1;

    ls3.students[0] = &st1;

    std::cout << "Student " << st1.student_name << " attend: ";
    for (auto i = 0; i < max_num_les; ++i) {
        if (st1.lessons[i]) {
            std::cout << st1.lessons[i]->lesson_name << " ";
        }
    }
    std::cout << "\n";

    std::cout << "Student " << st2.student_name << " attend: ";
    for (auto i = 0; i < max_num_les; ++i) {
        if (st2.lessons[i]) {
            std::cout << st2.lessons[i]->lesson_name << " ";
        }
    }
    std::cout << "\n\n";

    std::cout << "Lesson " << ls1.lesson_name << " attend: ";
    for (auto i = 0; i < max_num_st; ++i) {
        if (ls1.students[i]) {
            std::cout << ls1.students[i]->student_name << " ";
        }
    }
    std::cout << "\n";

    std::cout << "Lesson " << ls2.lesson_name << " attend: ";
    for (auto i = 0; i < max_num_st; ++i) {
        if (ls2.students[i]) {
            std::cout << ls2.students[i]->student_name << " ";
        }
    }
    std::cout << "\n";

    std::cout << "Lesson " << ls3.lesson_name << " attend: ";
    for (auto i = 0; i < max_num_st; ++i) {
        if (ls3.students[i]) {
            std::cout << ls3.students[i]->student_name << " ";
        }
    }
    std::cout << "\n";


}
