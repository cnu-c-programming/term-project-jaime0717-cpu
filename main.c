/*
 * main.c  –  Mini Student Shell
 *
 * TODO: Implement admin_shell and client_shell.
 *
 * Build:
 *   make admin   →  admin_shell  (compiled with -DADMIN_MODE)
 *   make client  →  client_shell (compiled with -DCLIENT_MODE)
 *
 * Usage:
 *   ./admin_shell [students.csv]
 *   ./admin_shell -f commands.txt [students.csv]
 *   ./client_shell [students.csv]
 *   ./client_shell -f commands.txt [students.csv]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* TODO: Add your own header includes here */
#include "student.h"
#include "file_io.h"
#include "command.h"

/* ---------------------------------------------------------------
 * TODO: Implement the interactive shell loop.
 *   - Print a prompt and read a line from stdin.
 *   - Parse the line into a command and arguments.
 *   - Dispatch to the appropriate handler function.
 *   - Loop until the user types "exit" or EOF.
 * --------------------------------------------------------------- */

void run_shell(const char *csv_path)
{ // 1.student.csv 들어옴(file io관련으로만 쓰면 될듯?), 2.각 모드에 맞는 입력 그거로 입력 받기. 3.명령어랑 나머지 분리(뒤 인자들은 각 handle에서 관리.) 4.loop로 exit이나 공백 입력 전까지? 계속
    /* TODO */
    ShellResult error;

    while (1)
    {
#ifdef ADMIN_MODE
        printf("admin>");
#elif defined(CLIENT_MODE)
        printf("client>");
#endif

        char parameter[100] = {0};
        char function[17] = {0}; // 그냥 17을 좋아해서

        char line[100] = {0};
        if (fgets(line, sizeof line, stdin) == NULL)
            return; // EOF

        int result = sscanf(line, "%s %[^\n]", function, parameter);

        if (result == 0)
        {
            continue; // 다시 받기
        }
        else
        {
            // command에 등록된 명령어인지 살펴봄, 있으면 handle이용해서 실행, 없으면 ShellResult로 오류.

            Command *commands_pointer = commands;

            while (commands_pointer->name != NULL)
            {
                if (strcmp(commands_pointer->name, function) == 0)
                    break;
                commands_pointer++;
            }
            if (commands_pointer->name == NULL)
            {
                error = SHELL_ERR_UNKNOWN_COMMAND;
            }
            else
            {
                // file_io에 정의된 save와 load의 경우 csv_path가 필요하기 때문에 따로 parameter에 넣어주기.
                if (strcmp("save", function) == 0 || strcmp("reload", function) == 0)
                {
                    error = commands_pointer->handler((char *)csv_path, &real_head); // save와 load는 다른 parameter가 필요없으므로, csv_path만 넘겨주기
                }
                else
                {
                    error = commands_pointer->handler(parameter, &real_head); // 여기서 함수 실행, error에는 함수가 정상적으로 실행됐을 경우 0(그 command에 있는 거) 반환
                }
            }

            // ShellResult로 결과 받아준 다음, 오류 있으면 관련 메시지 출력.
            switch (error)
            {
            case SHELL_OK:
                break;
            case SHELL_EXIT: // exit은 특별하게 처리.
                return;
            case SHELL_ERR_UNKNOWN_COMMAND:
                printf("Error: Unknown command or permission denied.\n");
                break;
            case SHELL_ERR_INVALID_ARGUMENT:
                printf("Error: Invalid Argument\n");
                break;
            case SHELL_ERR_MISSING_ARGUMENT:
                printf("Error: Missing Argument for Usage\n");
                break;
            case SHELL_ERR_FILE_OPEN:
                printf("Error: While File Opening\n");
                break;
            case SHELL_ERR_FILE_WRITE:
                printf("Error: While File Writing\n");
                break;
            case SHELL_ERR_STUDENT_NOT_FOUND:
                printf("Error: student not found\n");
                break;
            case SHELL_ERR_DUPLICATE_STUDENT:
                printf("Error: Duplicate Student\n");
                break;
            case SHELL_ERR_INVALID_SCORE:
                printf("Error: Invalid Score\n");
                break;
            }
        }
    }
}

/* ---------------------------------------------------------------
 * TODO: Implement batch mode – read commands from a file.
 *   - Open cmd_file for reading.
 *   - Execute each line as a command (same logic as run_shell).
 *   - Close the file when done.
 * --------------------------------------------------------------- */
void run_command_file(const char *cmd_file, const char *csv_path) // 끝나면 끝인걸로.
{
    ShellResult error;
    int count = 0;

    /* TODO */

    // 준비, file_io에 있는 reload 재활용
    FILE *fp = fopen(cmd_file, "r");
    if (fp == NULL)
    { // 습관성 체크
        printf("Error: While File Opening\n");
        return run_shell(csv_path); // 없으면 run_shell이나 돌려라
    }
    else
    {
        char line[100] = {0};

        while (fgets(line, sizeof line, fp) != NULL) // while문으로 끝날 때까지 돌려라 exit 없이 끝나면 run_shell로 가자.
        {
            char parameter[100] = {0};
            char function[17] = {0}; // 그냥 17을 좋아해서

            int result = sscanf(line, "%s %[^\n]", function, parameter);

            if (result == 0 || function[0] == '#' || result == EOF) //EOF관련 골치아팠다.
            {
                continue; // 공백 처리, #주석 처리
            }
            else
            {
                ++count; // 몇번째 라인 읽어주는지 확인하기 위해서.

                // command에 등록된 명령어인지 살펴봄, 있으면 handle이용해서 실행, 없으면 ShellResult로 오류.

                Command *commands_pointer = commands;

                while (commands_pointer->name != NULL)
                {
                    if (strcmp(commands_pointer->name, function) == 0)
                        break;
                    commands_pointer++;
                }
                if (commands_pointer->name == NULL)
                {
                    error = SHELL_ERR_UNKNOWN_COMMAND;
                }
                else
                {
                    // file_io에 정의된 save와 load의 경우 csv_path가 필요하기 때문에 따로 parameter에 넣어주기.
                    if (strcmp("save", function) == 0 || strcmp("reload", function) == 0)
                    {
                        printf("[command file:%d] ", count);
                        printf("%s", line);
                        error = commands_pointer->handler((char *)csv_path, &real_head); // save와 load는 다른 parameter가 필요없으므로, csv_path만 넘겨주기
                    }
                    else
                    {
                        printf("[command file:%d] ", count);
                        printf("%s", line);
                        error = commands_pointer->handler(parameter, &real_head); // 여기서 함수 실행, error에는 함수가 정상적으로 실행됐을 경우 0(그 command에 있는 거) 반환
                    }
                }

                // ShellResult로 결과 받아준 다음, 오류 있으면 관련 메시지 출력.
                switch (error)
                {
                case SHELL_OK:
                    break;
                case SHELL_EXIT: // exit은 특별하게 처리.
                    fclose(fp);
                    return; // exit 해주면 끝
                case SHELL_ERR_UNKNOWN_COMMAND:
                    printf("Error: Unknown command or permission denied.\n");
                    break;
                case SHELL_ERR_INVALID_ARGUMENT:
                    printf("Error: Invalid Argument\n");
                    break;
                case SHELL_ERR_MISSING_ARGUMENT:
                    printf("Error: Missing Argument for Usage\n");
                    break;
                case SHELL_ERR_FILE_OPEN:
                    printf("Error: While File Opening\n");
                    break;
                case SHELL_ERR_FILE_WRITE:
                    printf("Error: While File Writing\n");
                    break;
                case SHELL_ERR_STUDENT_NOT_FOUND:
                    printf("Error: student not found\n");
                    break;
                case SHELL_ERR_DUPLICATE_STUDENT:
                    printf("Error: Duplicate Student\n");
                    break;
                case SHELL_ERR_INVALID_SCORE:
                    printf("Error: Invalid Score\n");
                    break;
                }
            }
        }
        fclose(fp);
    }
    return; // 다 읽음. 끝
}

int main(int argc, char *argv[])
{
    const char *csv_path = "students.csv"; /* default CSV file */
    const char *cmd_file = NULL;           /* -f <file> argument */

    /* TODO: Parse command-line arguments.
     *   Supported flags:
     *     -f <file>   run commands from <file> instead of stdin
     *   Remaining positional argument (if any): path to students CSV.
     *
     *   Example parsing skeleton:
     *
     *   for (int i = 1; i < argc; i++) {
     *       if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
     *           cmd_file = argv[++i];
     *       } else {
     *           csv_path = argv[i];
     *       }
     *   }
     */
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-f") == 0 && i + 1 < argc)
        {
            cmd_file = argv[++i];
        }
        else
        {
            csv_path = argv[i];
        }
    }

// 2.csv 파일에서 학생 정보 읽어오기
#ifdef ADMIN_MODE
    printf("[Admin Program]\n");
#elif defined(CLIENT_MODE)
    printf("[Client Program]\n");
#endif

    // 준비, file_io에 있는 reload 재활용
    FILE *fp = fopen(csv_path, "r");
    if (fp == NULL)
    { // 습관성 체크
        printf("Error: While File Opening\n");
    }
    else
    {
        // 맨 위 header 처리.
        char header_trash[100];
        if (fgets(header_trash, sizeof header_trash, fp) == NULL)
        {
            printf("Error: While File Opening\n");
        }
        else
        {
            // 파일 읽어주기
            Student read_student;

            int count = 0;
            char line[300] = {0};
            // char formatted_line[300] = {0};
            while (fgets(line, sizeof line, fp) != NULL) //[^,]부분.. fscanf(line, "%d,%[^,],%d\n", &read_student.id, read_student.name, &read_student.score) == 3
            {
                if (sscanf(line, "%d,%[^,],%d\n", &read_student.id, read_student.name, &read_student.score) == 3)
                {
                    // sprintf(formatted_line, "%d %s %d", read_student.id, read_student.name, read_student.score);
                    //  저장. client모드에서도 똑바로 돼야함.. handle 가져옴.
                    add_student(read_student.id, read_student.name, read_student.score, &real_head); // 3.저장.
                    ++count;
                }
                else
                {
                    break;
                }
            }
            printf("Loaded %d students from %s.\n", count, csv_path);

            fclose(fp);
        }
    }

#ifdef ADMIN_MODE
    /* Admin shell: supports add, delete, update, save, load, sort, list, find, help, exit */
    if (cmd_file)
    {
        run_command_file(cmd_file, csv_path);
    }
    else
    {
        run_shell(csv_path);
    }

#elif defined(CLIENT_MODE)
    /* Client shell: supports find, list, help, exit  (read-only) */
    if (cmd_file)
    {
        run_command_file(cmd_file, csv_path);
    }
    else
    {
        run_shell(csv_path);
    }

#else
// #error "Define either -DADMIN_MODE or -DCLIENT_MODE when compiling."
#endif

    return 0;
}
