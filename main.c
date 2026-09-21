#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct command
{
    char *argv[10]; // toi da 1 cau lenh co 9 tham so
    char argc;
    // void cmd = argv[0]; // phan tu dau tien
} command;

struct command command;
void ls()
{
    printf("ls called !\n");
    char ls_option[3] = {'l', 'h', 'a'}; //
    // char option = check_if_command_option(ls_option); // 1 2 4 compile
}
void cd()
{
}
void pwd()
{
    char current_work_dirrectory[100];
    memset(current_work_dirrectory, 0, 100);
    getcwd(current_work_dirrectory, 100);
    printf("%s", current_work_dirrectory);
}
void cat()
{
}
char check_if_command_option(char *command_option_list)
{
    // nhan vao 1 list argv: a -a -l -lha
    /* CHECK IF EXIST */
    // char full_option[100];
    // char tmp[100];
    // for (int i = 1; i < command.argc; i++)
    // {
    //     memset(tmp, 0, 100);
    //     char *check = strstr(command.argv[i], "-");
    //     if (!check)
    //     {
    //         printf("option not found !\n");
    //         break;
    //     }
    // }
    /* TURN ON BIT FLAGS */
}
void echo(char *cmd) // format : echo [STRINGS]
{
    printf("%s", cmd + 5);
}
void strip(char *cmd)
{
    int start_idx = 0;
    int len_cmd = strlen(cmd); // just idx
    int end_idx = len_cmd - 1;
    while (cmd[start_idx] == ' ' || cmd[end_idx] == ' ' || cmd[end_idx] == '\n')
    {
        if (cmd[start_idx] == ' ')
            start_idx++;
        if (cmd[end_idx] == ' ' || cmd[end_idx] == '\n')
            end_idx--;
    }
    char tmp_str[len_cmd];
    memset(tmp_str, 0, len_cmd);
    strncpy(tmp_str, &cmd[start_idx], end_idx - start_idx + 1);
    tmp_str[len_cmd] = '\x00';

    memset(cmd, 0, 0x100);
    strncpy(cmd, tmp_str, strlen(tmp_str));
    cmd[strlen(tmp_str)] = '\x00';
}
void parser_cmd(char *cmd) //' ls -lh -a \n'
{
    for (int i = 0; i < 10; i++)
    {
        command.argv[i] = malloc(0x10);
    }
    strip(cmd);
    int len_cmd = strlen(cmd);
    cmd[len_cmd] = '\x00'; // input: 'ls -lh -a'
    int count = 0;
    command.argc = 0;
    char tmp[len_cmd];
    memset(tmp, 0, len_cmd);

    for (int i = 0; i <= len_cmd; i++) // 'ls '
    {

        if (cmd[i] == ' ' || cmd[i] == '\x00') // 'ls -lh -a\x00'
        {
            tmp[strlen(tmp)];
            strncpy(command.argv[command.argc], tmp, strlen(tmp));
            command.argc++;
            memset(tmp, 0, len_cmd);
            continue;
        }
        else
        {
            char c = cmd[i];
            strncat(tmp, &c, 1);
        }
    }
    // printf("cmd :<%s>", command.argv[0]);
}
int main()
{

    while (1)
    {
        char cmd[0x100];
        memset(cmd, 0, 0x100);

        for (int i = 0; i < command.argc; i++)
        {
            memset(command.argv[i], 0, 10);
        }
        printf("\n$ ");
        fflush(stdout);
        read(0, cmd, 100);
        char echo_cmd[strlen(cmd)];
        strcpy(echo_cmd, cmd);
        parser_cmd(cmd);
        if (!strcmp(command.argv[0], "ls"))
        {
            ls();
        }
        else if (!strcmp(command.argv[0], "pwd"))
        {
            pwd();
        }
        else if (!strcmp(command.argv[0], "cd"))
        {
            cd();
        }
        else if (!strcmp(command.argv[0], "echo"))
        {
            echo(echo_cmd);
        }
        else if (!strcmp(command.argv[0], "cat"))
        {
            cat();
        }
    }
}
