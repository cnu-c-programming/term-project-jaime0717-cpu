#pragma once //header guard
#include "command.h"

typedef struct Student { //5
    int id;
    char name[32];
    int score;
    struct Student* next;
} Student;

extern Student *real_head; // 원래 student 파일에 있었는데, 함수들ㅇ **head를 인자로 받는 걸 보고, 여기로 이동! ok. linked list는 sutdent에서


ShellResult add_student(int id, char* name, int score, Student **head);

ShellResult delete_student(int id, Student **head);

ShellResult update_student(int id, int score, Student **head);

ShellResult find_student(int id, Student **head);

ShellResult list_student(Student **head);

ShellResult stats_student(Student **head);

ShellResult help_student(void);

ShellResult clear_student(void);

ShellResult exit_student(Student **head); 
