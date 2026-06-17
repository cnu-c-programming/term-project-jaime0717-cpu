#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "student.h"
#include "command.h"

Student *real_head = NULL; // 원래 student 파일에 있었는데, 함수들ㅇ **head를 인자로 받는 걸 보고, 여기로 이동! ok. linked list는 sutdent에서

ShellResult add_student(int id, char *name, int score, Student **head)
{
    Student newstudent = {.id = id, .score = score, .next = NULL};
    // 이름 추가
    strcpy(newstudent.name, name);

    // 중복 id 확인.
    if (find_student(id, head) == SHELL_OK)
        return SHELL_ERR_DUPLICATE_STUDENT;

    // id 0 or 음수
    if (id < 0 || id == 0)
        return SHELL_ERR_INVALID_ARGUMENT;

    // 잘못된 이름. 빈 이름이거나 ,가 들어간 이름
    if (name[0] == '\n')
        return SHELL_ERR_INVALID_ARGUMENT;
    for (int i = 0; i < strlen(name); i++)
    {
        if (name[i] == ',')
            return SHELL_ERR_INVALID_ARGUMENT;
    }

    // score관련 예외 처리
    if (!(score >= 0 && score <= 100))
    {
        // 점수 범위 오류
        return SHELL_ERR_INVALID_SCORE;
    }

    // 인자 부족, 잘못된 점수, 잘못된 id는 handle_add에서

    Student *add_newstudent = malloc(sizeof(Student)); // 새로 추가될 주소 메모리 할당.
    *add_newstudent = newstudent;

    Student *serching = *head;

    if (*head == NULL)
    {
        *head = add_newstudent;
    }
    else
    {
        while (serching->next != NULL)
        {
            serching = serching->next;
        }
        serching->next = add_newstudent;
    }

    return SHELL_OK;
}

ShellResult delete_student(int id, Student **head)
{
    Student *searching = *head;
    Student *temp = NULL;

    if (*head == NULL)
    {
        // 없을 경우 처리
        return SHELL_ERR_STUDENT_NOT_FOUND;
    }
    else
    {
        while (searching->id != id)
        {
            if (searching->next == NULL)
            {
                // 없을 경우 처리
                return SHELL_ERR_STUDENT_NOT_FOUND;
            }
            temp = searching;
            searching = searching->next;
        }
        if ((*head)->id == id)
        {
            temp = *head;
            *head = (*head)->next;
            free(temp);
            temp = NULL;
            printf("Student deleted\n");
            return SHELL_OK;
        }
        else
        {
            temp->next = searching->next;
            free(searching);
            searching = NULL;
            printf("Student deleted\n");
            return SHELL_OK;
        }
    }
}

ShellResult update_student(int id, int score, Student **head)
{
    // score관련 예외 처리
    if (!(score >= 0 && score <= 100))
    {
        // score 범위랑 안맞음
        return SHELL_ERR_INVALID_SCORE;
    }

    // 본론
    Student *serching = *head;
    if (*head == NULL)
    {
        // 없을 경우 처리
        return SHELL_ERR_STUDENT_NOT_FOUND;
    }

    while (serching->id != id) // head가 바로면, while문 지나쳐서 바로.(위 delete와 다름)
    {
        if (serching->next == NULL)
        {
            // 없을 경우 처리
            return SHELL_ERR_STUDENT_NOT_FOUND;
        }
        serching = serching->next;
    }
    serching->score = score;
    printf("Student updated\n");
    return SHELL_OK;
}

ShellResult find_student(int id, Student **head)
{
    // id 0 or 음수
    if (id < 0 || id == 0)
        return SHELL_ERR_INVALID_ARGUMENT;

    // 본론
    Student *serching = *head;
    if (*head == NULL)
    {
        // 없을 경우 처리
        return SHELL_ERR_STUDENT_NOT_FOUND;
    }

    while (serching->id != id)
    {
        if (serching->next == NULL)
        {
            // 없을 경우 처리
            return SHELL_ERR_STUDENT_NOT_FOUND;
        }
        serching = serching->next;
    }
    printf("ID: %d\nName: %s\nScore: %d\n", serching->id, serching->name, serching->score); // 첫항이어도 똑같은 결과
    return SHELL_OK;
}

ShellResult list_student(Student **head)
{
    if (*head == NULL)
    {
        // 없을 경우 처리
        return SHELL_ERR_STUDENT_NOT_FOUND;
    }

    Student *checking = *head;

    printf("ID   Name       Score\n"); // id 3 2, name 10 1, score
    while (checking != NULL)
    {
        printf("%-3d  %-10s %d\n", checking->id, checking->name, checking->score);
        checking = checking->next;
    }
    return SHELL_OK;
}

ShellResult stats_student(Student **head)
{
    if (*head == NULL)
    {
        // 없을 경우 처리
        return SHELL_ERR_STUDENT_NOT_FOUND;
    }
    Student *checking = *head;
    int count = 0;
    int sum = 0, max = 0, min = 100;

    while (checking != NULL)
    {
        ++count;

        sum += checking->score;
        if (checking->score > max)
            max = checking->score;
        if (checking->score < min)
            min = checking->score;

        checking = checking->next;
    }

    printf("Count: %d\nAverage: %f\nMax: %d\nMin: %d\n", count, sum / (float)count, max, min);
    return SHELL_OK;
}

ShellResult help_student(void)
{
    printf("Commands:\n");

    extern Command commands[];
    Command *commands_pointer = commands;

    while (commands_pointer->usage != NULL)
    {
        printf("%-30s %s\n", commands_pointer->usage, commands_pointer->description);
        commands_pointer++;
    }
    return SHELL_OK;
}

ShellResult clear_student(void)
{
    printf("\033[2J\033[H"); // 이거 하나면 되나?
    return SHELL_OK;
}

ShellResult exit_student(Student **head)
{
    Student *temp = NULL;
    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
        temp = NULL;
    }
    printf("Goodbye.\n");
    return SHELL_EXIT;
}
