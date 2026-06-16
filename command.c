#include "command.h"
#include "file_io.h"

ShellResult handle_add(char *args, Student **head)
{ // 인자 부족, 잘못된 점수는 handle_add에서
    // args를 통해서 add 명령어 뒤에 있는 문자열 통으로 읽어오기
    // 이 아래에는 args 나눠서 ShellResult add_student(int id, char *name, int score, Student **head)에 넣어주기.
    int id, score;
    char name[32];
    if (sscanf(args, "%d %s %d", &id, name, &score) == 3)
    {
        return add_student(id, name, score, head); // head를 이중 포인터로 받아왔으므로 별다른 조치 x.
    }
    else
    {
        char score_char[10];
        if (sscanf(args, "%d %s %s", &id, name, score_char) == 3)
            return SHELL_ERR_INVALID_ARGUMENT; // 잘못된 점수

        return SHELL_ERR_MISSING_ARGUMENT; // 인자부족
    }
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
