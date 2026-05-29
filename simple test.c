#include <stdio.h>

int main() {
    printf("Commands:\n");
    printf("save                         Save students to CSV\n");
    printf("reload                       Reload students from CSV\n");
    printf("add <id> <name> <score>      Add a student\n");
    printf("delete <id>                  Delete a student\n");
    printf("update <id> <score>          Update student score\n");
    printf("find <id>                    Find student by ID\n");
    printf("list                         List all students\n");
    printf("stats                        Show statistics\n");
    printf("clear                        Clear screen\n");
    printf("exit                         Exit program");
}