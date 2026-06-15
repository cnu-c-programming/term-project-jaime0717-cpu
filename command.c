#include "command.h"
#include "file_io.h"

ShellResult handle_add(char *args, Student **head) {  //인자 부족, 잘못된 점수는 handle_add에서
//args를 통해서 add 명령어 뒤에 있는 문자열 통으로 읽어오기
//이 아래에는 args 나눠서 ShellResult add_student(int id, char *name, int score, Student **head)에 넣어주기.
//이 과정에서 인자 부족, 잘못된 점수는 따로 처리.
//return add_student(int id, char *name, int score, Student **head);
}

#ifdef ADMIN_MODE //11
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
    {"exit", handle_exit, "exit", "Exit shell"}};
#endif

#ifdef CLIENT_MODE //7
Command commands[] = {
    {"reload", handle_reload, "reload", "Reload students from CSV"},
    {"find", handle_find, "find <id>", "Find student"},
    {"list", handle_list, "list", "List students"},
    {"stats", handle_stats, "stats", "Show statistics"},
    {"help", handle_help, "help", "Show help"},
    {"clear", handle_clear, "clear", "Clear screen"},
    {"exit", handle_exit, "exit", "Exit shell"}};
#endif
