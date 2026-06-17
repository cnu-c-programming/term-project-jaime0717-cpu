#include <stdio.h>
#include <stdlib.h>

#include "file_io.h"
#include "student.h" //head 사용 가능!

#ifdef ADMIN_MODE
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
        if (fprintf(fp, "%d,%s,%d\n", checking->id, checking->name, checking->score) < 0)
        {
            fclose(fp);
            return SHELL_ERR_FILE_WRITE;
        } // 쓰는 거에 문제가 생김.
        else
        {
            checking = checking->next;
        }
    }
    printf("Saved %d students to students.csv.\n", count);
    fclose(fp);
    return SHELL_OK;
}
#endif

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
    ShellResult result;

    int count = 0;
    char parameter[300] = {0};
    while (fgets(parameter, sizeof parameter, fp) != NULL)
    {
        // 하..괜히 add를 써가지고..
        int id = 0, score = 0;
        char name[32];
        if (sscanf(parameter, "%d,%[^,],%d", &id, name, &score) == 3)
        {
            result = add_student(id, name, score, head); // head를 이중 포인터로 받아왔으므로 별다른 조치 x.
        }
        else
        {
            char score_char[10];
            char id_char[10];
            if (sscanf(parameter, "%d %s %s", &id, name, score_char) == 3)
                result = SHELL_ERR_INVALID_ARGUMENT; // 잘못된 점수

            if (sscanf(parameter, "%s %s %s", id_char, name, score_char) == 3)
                result = SHELL_ERR_INVALID_ARGUMENT; // id, score다 string

            if (sscanf(parameter, "%s %s %d", id_char, name, &score) == 3)
                result = SHELL_ERR_INVALID_ARGUMENT; // id string

            result = SHELL_ERR_MISSING_ARGUMENT; // 인자부족
        }

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
