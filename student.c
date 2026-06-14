#include <stdio.h>
#include <string.h>

#include "student.h"
#include "command.h"

int main()
{
    Student *head = NULL;

    static int count = 0;
}

void handle_add(int id, char *name, int score)
{
    Student newstudent = {.id = id, .score = score, .next = NULL};
    int i = 0;
    // 이름 추가
    strcpy(newstudent.name, name);

    Student *add_newstudent = malloc(sizeof(Student)); // 새로 추가될 주소 메모리 할당.
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
    Student *serching = head;
    Student *temp = NULL;

    if (head == NULL)
    {
        // 없을 경우 처리
    }
    else
    {
        while (serching->id != id)
        {
            if (serching->next == NULL)
            {
                // 없을 경우 처리
            }
            temp = serching;
            serching = serching->next;
        }
        if (head->id == id)
        {
            temp = head;
            head = head->next;
            free(temp);
            printf("Student deleted");
            return;
        }
        else
        {
            temp->next = serching->next;
            free(serching);
            printf("Student deleted");
            return;
        }
    }
}

void handle_update(int id, int score)
{
    // score관련 예외 처리
    if (!(score >= 0 && score <= 100))
    {
        // score 범위랑 안맞음
    }

    // 본론
    Student *serching = head;
    if (head == NULL)
    {
        // 없을 경우 처리
    }

    while (serching->id != id) //head가 바로면, while문 지나쳐서 바로.(위 delete와 다름)
    {
        if (serching->next == NULL)
        {
            // 없을 경우 처리
        }
        serching = serching->next;
    }
        serching->score = score;
        printf("Student updated");
        return;
    
}

void handle_find(int id)
{
    Student *serching = head;
    if (head == NULL)
    {
        // 없을 경우 처리
    }

    while (serching->id != id)
    {
        if (serching->next == NULL)
        {
            // 없을 경우 처리
        }
        serching = serching->next;
    } 
        printf("ID: %d\nName: %s\nScore: %d", serching->id, serching->name, serching->score); //첫항이어도 똑같은 결과
        return;
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
