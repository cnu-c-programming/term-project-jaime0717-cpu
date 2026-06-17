#include <stdio.h>

#include "command.h"
#include "file_io.h"
#include "student.h"

#ifdef ADMIN_MODE
ShellResult handle_add(char *args, Student **head)
{ // 인자 부족, 잘못된 점수는 handle_add에서
    // args를 통해서 add 명령어 뒤에 있는 문자열 통으로 읽어오기
    // 이 아래에는 args 나눠서 ShellResult add_student(int id, char *name, int score, Student **head)에 넣어주기.
    int id = 0, score = 0;
    char name[32];
    ShellResult result;
    if (sscanf(args, "%d %s %d", &id, name, &score) == 3)
    { 
        result = add_student(id, name, score, head); // head를 이중 포인터로 받아왔으므로 별다른 조치 x.
        if(result == SHELL_OK) printf("Student added\n");
        return result;
    }
    else
    {
        char score_char[10];
        char id_char[10];
        if (sscanf(args, "%d %s %s", &id, name, score_char) == 3)
            return SHELL_ERR_INVALID_ARGUMENT; // 잘못된 점수

        if (sscanf(args, "%s %s %s", id_char, name, score_char) == 3)
            return SHELL_ERR_INVALID_ARGUMENT; // id, score다 string

        if (sscanf(args, "%s %s %d", id_char, name, &score) == 3)
            return SHELL_ERR_INVALID_ARGUMENT; // id string

        return SHELL_ERR_MISSING_ARGUMENT; // 인자부족
    }
}

ShellResult handle_delete(char *args, Student **head)
{
    int id = 0;
    if (sscanf(args, "%d", &id) == 1)
        return delete_student(id, head);

    char id_char[5];
    if (sscanf(args, "%s", id_char) == 1)
        return SHELL_ERR_INVALID_ARGUMENT; // id가 string임.

    return SHELL_ERR_MISSING_ARGUMENT; // 아무것도 못읽으면 인자 x.
}

ShellResult handle_update(char *args, Student **head) // 학생 없음, 점수 범위 오류는 update_student에서
{
    int id = 0, score = 0;

    if (sscanf(args, "%d %d", &id, &score) == 2)
    {
        return update_student(id, score, head); // head를 이중 포인터로 받아왔으므로 별다른 조치 x.
    }
    else
    {
        char score_char[10];
        char id_char[10];
        if (sscanf(args, "%d %s", &id, score_char) == 2)
            return SHELL_ERR_INVALID_ARGUMENT; // 잘못된 점수

        if (sscanf(args, "%s %s", id_char, score_char) == 2)
            return SHELL_ERR_INVALID_ARGUMENT; // id, score다 string

        if (sscanf(args, "%s %d", id_char, &score) == 2)
            return SHELL_ERR_INVALID_ARGUMENT; // id string

        return SHELL_ERR_MISSING_ARGUMENT; // 인자부족
    }
}

ShellResult handle_save(char *args, Student **head)
{
    return save_student(args,head);
}
#endif


ShellResult handle_find(char *args, Student **head)
{
    int id = 0;
    if (sscanf(args, "%d", &id) == 1)
    {
        return find_student(id, head);
    }

    // id가 string
    char id_char[10];
    if (sscanf(args, "%s", id_char) == 1)
    {
        return SHELL_ERR_INVALID_ARGUMENT;
    }
    return SHELL_ERR_MISSING_ARGUMENT; // 인자부족
}

ShellResult handle_list(char *args, Student **head)
{
    (void)args;
    return list_student(head);
}

ShellResult handle_stats(char *args, Student **head)
{
    (void)args;
    return stats_student(head);
}

ShellResult handle_help(char *args, Student **head)
{
    (void)args;
    (void)head;

    return help_student();
}

ShellResult handle_clear(char *args, Student **head)
{
    (void)args;
    (void)head;

    return clear_student();
}

ShellResult handle_exit(char *args, Student **head)
{
    (void)args;
    (void)head;

    return exit_student(head);
}

ShellResult handle_reload(char *args, Student **head)
{
    return reload_student(args,head);
}

#ifdef ADMIN_MODE // 11
Command commands[] = {
    {"save", handle_save, "save", "Save students to CSV"},
    {"reload", handle_reload, "reload", "Reload students from CSV"},
    {"add", handle_add, "add <id> <name> <score>", "Add a student"},
    {"delete", handle_delete, "delete <id>", "Delete a student"},
    {"update", handle_update, "update <id> <score>", "Update student score"},
    {"find", handle_find, "find <id>", "Find student"},
    {"list", handle_list, "list", "List students"},
    {"stats", handle_stats, "stats", "Show statistics"},
    {"help", handle_help, "help", "Show help"},
    {"clear", handle_clear, "clear", "Clear screen"},
    {"exit", handle_exit, "exit", "Exit shell"},
    {NULL}}; // 뒤 코드들 편하게 작성하기 위함. or 몇칸인지 계산하는 코드 넣었어야 함.

#endif

#ifdef CLIENT_MODE // 7
Command commands[] = {
    {"reload", handle_reload, "reload", "Reload students from CSV"},
    {"find", handle_find, "find <id>", "Find student"},
    {"list", handle_list, "list", "List students"},
    {"stats", handle_stats, "stats", "Show statistics"},
    {"help", handle_help, "help", "Show help"},
    {"clear", handle_clear, "clear", "Clear screen"},
    {"exit", handle_exit, "exit", "Exit shell"},
    {NULL}}; // 뒤 코드들 편하게 작성하기 위함.
#endif
