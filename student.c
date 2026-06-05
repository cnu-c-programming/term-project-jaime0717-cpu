#include <stdio.h>
#include <string.h>

#include "student.h"
#include "command.h"

int main()
{
    Student *head = NULL;
    Student *p = head;

    static int count = 0;
}

void handle_add(int id, char *name, int score)
{
    Student newstudent = {.id = id, .score = score, .next = NULL};
    int i = 0;
    while (*name != '\0')
    {
        newstudent.name[i] = *name;
        i++;
        name++;
    }
    newstudent.name[i] = '\0';

    Student *add_newstudent;
    *add_newstudent = newstudent;

    Student *serching = head;

    if (head == NULL)
    {
        head = add_newstudent;
    }
    else
    {
        while (serching->next != NULL)
        {
            serching = serching->next;
        }
        serching->next = add_newstudent;
    }
}

void handle_delete(int id)
{
}

void handle_update(int id, int score)
{
}

void handle_find(int id)
{
    Student *serching = head;
    while (serching->next != NULL)
    {
        if (serching->id == id)
        {
            printf("ID: %d\nName: %s\nScore: %d", serching->id, serching->name, serching->score);
            return 0;
        }
    }
}

void handle_list(void)
{
}

void handle_stats(void)
{
}

void handle_help(void)
{
    printf("Commands:\n");


    extern Command commands[];
    Command *commands_pointer = commands;


    while (commands_pointer->usage != NULL)
    {
        printf("%-30s %s", commands_pointer->usage, commands_pointer->description);
        commands_pointer++;
    }
}

void handle_clear(void)
{
}

void handle_exit(void)
{
}
