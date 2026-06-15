#include <stdio.h>
#include "file_io.h"
#include "student.h"

#ifdef ADMIN_MODE
void handle_save()
{
    FILE *fp = fopen("students.csv", "w"); //"students.csv" 여기서 이걸 그대로 쓰는 게 맞는지 모르겠다.
    if (fp == NULL)
    { // 습관성 체크
        return;
    }

    fprintf(fp, "id,name,score\n");

    extern Student *head;
    Student *checking = head;
    int count = 0;

    while (checking != NULL)
    {
        ++count;
        fprintf(fp, "%d,%s,%d\n", checking->id, checking->name, checking->score);
        checking = checking->next;
    }
    printf("Saved %d students to students.csv.", count);
    fclose(fp);
}
#endif

void handle_reload()
{
    extern Student *head;
    
    //우선 기존 linked list 삭제.
    Student *temp = NULL;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
        temp = NULL;
    }

    //시작
    FILE *fp = fopen("students.csv", "r");
    if (fp == NULL)
    { // 습관성 체크
        return;
    }

    // 맨 위 header 처리.
    char header_trash[100];
    fgets(header_trash, sizeof header_trash, fp);

    // 본론
    Student read_student;

    int count = 0;
    while (fscanf(fp, "%d,%[^,],%d\n", &read_student.id, read_student.name, &read_student.score) == 3) //[^,]부분..
    {
        handle_add(read_student.id, read_student.name, read_student.score);
        ++count;
    }
    printf("Reloaded %d students from students.csv.", count);

    fclose(fp);
}
