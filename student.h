#pragma once //header guard
#include "command.h"

typedef struct Student { //5
    int id;
    char name[32];
    int score;
    struct Student* next;
} Student;

extern Student* head;

ShellResult add_student(int id, char* name, int score, Student **head);

ShellResult delete_student(int id, Student **head);

ShellResult update_student(int id, int score, Student **head);

ShellResult find_student(int id, Student **head);

ShellResult list_student(Student **head);

ShellResult stats_student(Student **head);

ShellResult help_student(Student **head);

ShellResult clear_student(Student **head);

ShellResult exit_student(Student **head); 