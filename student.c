#include <stdio.h>
#include "student.h" //어딘가에서 배웠었는데..

int main()
{
    Student *head = NULL;
    Student *p = head;

    static int count = 0;
}

void save()
{
}

void reload()
{
}

void add(int id, char *name, int score, Student *head)
{
    Student newstudent = {.id=id, .score = score, .next = NULL};
    int i = 0;
    while(*name != '\0') {
        newstudent.name[i] = *name;
        name++;
    }

    Student* add_newstudent;
    *add_newstudent = newstudent; 

    Student* serching = head;
    while(serching->next != NULL) {
        serching = serching->next;
    }
    serching->next = add_newstudent;
}

void delete_student(int id) // delete라는 함수가 이미 있어서 이름을 저렇게 처리.
{
}

void update(int id, int score)
{
}

void find(int id)
{
}

void list(void)
{
}

void stats(void)
{
}

void help()
{
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

void clear(void)
{
}

void exit(void)
{
}
