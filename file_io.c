#include <stdio.h>
#include "file_io.h"
#include "student.h" //head 사용 가능!

// #ifdef ADMIN_MODE
ShellResult save_student(const char *csv_path, Student **head)
{
    FILE *fp = fopen(csv_path, "w");
    if (fp == NULL)
    { // 습관성 체크
        return SHELL_ERR_FILE_OPEN;
    }

    fprintf(fp, "id,name,score\n");

    Student *checking = *head;
    int count = 0;

    while (checking != NULL)
    {
        ++count;
        if (fprintf(fp, "%d,%s,%d\n", checking->id, checking->name, checking->score) == 3)
        {
            checking = checking->next;
        }
        else
        {
            fclose(fp);
            return SHELL_ERR_FILE_WRITE; // 쓰는 거에 문제가 생김.
        }
    }
    printf("Saved %d students to students.csv.", count);
    fclose(fp);
    return SHELL_OK;
}
// #endif

ShellResult reload_student(const char *csv_path, Student **head)
{
    // 우선 기존 linked list 삭제.
    Student *temp = NULL;
    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
        temp = NULL;
    }

    // 시작
    FILE *fp = fopen(csv_path, "r");
    if (fp == NULL)
    { // 습관성 체크
        return SHELL_ERR_FILE_OPEN;
    }

    // 맨 위 header 처리.
    char header_trash[100];
    fgets(header_trash, sizeof header_trash, fp);

    // 본론
    int count = 0;
    char parameter[300] = {0};
    while (fgets(parameter, sizeof parameter, fp) != NULL) 
    {
        ShellResult result = handle_add(parameter, head);
        if (result != SHELL_OK)
        {
            fclose(fp);
            return result;
        }
        ++count;
    }
    printf("Reloaded %d students from %s.\n", count, csv_path);
    fclose(fp);
    return SHELL_OK;
}
