#pragma once
#include "student.h"

ShellResult save_student(const char *csv_path, Student **head);

ShellResult reload_student(const char *csv_path, Student **head);
