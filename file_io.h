#pragma once
#include "student.h"

#ifdef ADMIN_MODE
ShellResult save_student(const char *csv_path, Student **head);
#endif

ShellResult reload_student(const char *csv_path, Student **head);
