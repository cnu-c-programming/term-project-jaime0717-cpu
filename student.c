#include <stdio.h>
#include <string.h>

#include "student.h"
#include "command.h"

//#ifdef ADMIN_MODE
ShellResult add_student(int id, char *name, int score, Student **head)
{
    Student newstudent = {.id = id, .score = score, .next = NULL};
    int i = 0;
    // 이름 추가
    strcpy(newstudent.name, name);

    //중복 id 확인.
    if(find_student(id, head)==SHELL_OK) return SHELL_ERR_DUPLICATE_STUDENT;

    //잘못된 이름. 빈 이름이거나 ,가 들어간 이름
    if(name[0]=='\n') return SHELL_ERR_INVALID_ARGUMENT;
    for(int i = 0; i<strlen(name); i++) {
        if(name[i]==',') return SHELL_ERR_INVALID_ARGUMENT;
    }
    
    // score관련 예외 처리
    if (!(score >= 0 && score <= 100))
    {
        // 점수 범위 오류
        return SHELL_ERR_INVALID_SCORE;
    } 

    //인자 부족, 잘못된 점수는 handle_add에서
    

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

ShellResult handle_update(int id, int score, Student **head)
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
    }

    while (serching->id != id) // head가 바로면, while문 지나쳐서 바로.(위 delete와 다름)
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
//#elif defined(ADMIN_MODE) || defined(CLIENT_MODE)

ShellResult find_student(int id, Student **head)
{
    Student *serching = *head;
    if (*head == NULL)
    {
        //없을 경우 처리
        return SHELL_ERR_STUDENT_NOT_FOUND;
    }

    while (serching->id != id)
    {
        if (serching->next == NULL)
        {
            //없을 경우 처리
            return SHELL_ERR_STUDENT_NOT_FOUND;
        }
        serching = serching->next;
    }
    printf("ID: %d\nName: %s\nScore: %d\n", serching->id, serching->name, serching->score); // 첫항이어도 똑같은 결과
    return SHELL_OK;
}

void handle_list(void)
{
    if (head == NULL)
    {
        // 없을 경우 처리
    }

    Student *checking = head;
    int count = 0;

    printf("ID   Name       Score\n"); // id 3 2, name 10 1, score
    while (checking != NULL)
    {
        printf("%-3d  %-10s %d", checking->id, checking->name, checking->score);
        checking = checking->next;
    }
}

void handle_stats(void)
{
    if (head == NULL)
    {
        // 없을 경우 처리
    }
    Student *checking = head;
    int count = 1;
    int sum = 0, max = 0, min = 0;

    while (checking != NULL)
    {
        ++count;

        sum += checking->score;
        if (checking->score > max)
            max = checking->score;
        if (checking->score > max < min)
            min = checking->score;

        checking = checking->next;
    }

    printf("Count: %d\nAverage: %f\nMax: %d\nMin: %d\n", count, sum / (float)count, max, min);
}

void handle_help(void) // 잘 작동할지 헷갈리니 무조건 테스트 해보기
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
    printf("\033[2J\033[H"); // 이거 하나면 되나?
}

void handle_exit(void)
{
    Student *temp = NULL;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
        temp = NULL;
    }
    printf("Goodbye.");
}
//#endif