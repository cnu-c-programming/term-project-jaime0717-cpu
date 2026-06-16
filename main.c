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
    (void)csv_path;

    ShellResult error;

    char *parameter, function;
    while (1)
    {
#ifdef ADMIN_MODE
        printf("admin>");
#elif defined(CLIENT_MODE)
        printf("client>");
#endif
        // 빈 공백은 특별하게 처리.
        char line[100];
        fgets(line, sizeof line, stdin);
        int result = sscanf(line, "%s %[^\n]", function, parameter);
        if (result == 0 || result == EOF)
        {
            return; // 0이나 공백이면 loop 끝
        }
        else
        {

            /*if (result == 1) //사실 이건 handle로 처리할 떄 어떻게 해도 될 듯.
            {
                // parameter 부족 오류.
            }*/

            // command에 등록된 명령어인지 살펴봄, 있으면 handle이용해서 실행, 없으면 ShellResult로 오류.
            extern Command commands[];
            Command *commands_pointer = commands;

            while (commands_pointer != NULL)
            {
                if (strcmp(commands_pointer->name, function) ==0)
                    break;
                commands_pointer++;
            }
            if (commands_pointer == NULL)
            {
                error = SHELL_ERR_UNKNOWN_COMMAND;
            } else{
                error = commands_pointer->handler(parameter, &head); //여기서 함수 실행, error에는 함수가 정상적으로 실행됐을 경우 0(그 command에 있는 거) 반환
            }

            // ShellResult로 결과 받아준 다음, 오류 있으면 관련 메시지 출력.

            // exit은 특별하게 처리.
        }
    }
}

/* ---------------------------------------------------------------
 * TODO: Implement batch mode – read commands from a file.
 *   - Open cmd_file for reading.
 *   - Execute each line as a command (same logic as run_shell).
 *   - Close the file when done.
 * --------------------------------------------------------------- */
void run_command_file(const char *cmd_file, const char *csv_path)
{
    /* TODO */
    (void)cmd_file;
    (void)csv_path;
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
    (void)argc;
    (void)argv;
    
    Student* head = NULL; //원래 student 파일에 있었는데, 함수들ㅇ **head를 인자로 받는 걸 보고, 여기로 이동!


// 2.csv 파일에서 학생 정보 읽어오기
#ifdef ADMIN_MODE
    printf("[Admin Program]");
#elif defined(CLIENT_MODE)
    printf("[Client Program]");
#endif

    // 준비, file_io에 있는 reload 재활용
    FILE *fp = fopen(csv_path, "r");
    if (fp == NULL)
    { // 습관성 체크
        return;
    }

    // 맨 위 header 처리.
    char header_trash[100];
    fgets(header_trash, sizeof header_trash, fp);

    // 파일 읽어주기
    Student read_student;

    int count = 0;
    while (fscanf(fp, "%d,%[^,],%d\n", &read_student.id, read_student.name, &read_student.score) == 3) //[^,]부분..
    {
        handle_add(read_student.id, read_student.name, read_student.score); // 3.저장.
        ++count;
    }
    printf("Loaded %d students from %s.", count, csv_path);

    fclose(fp);

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
