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

void strip(char *cmd);
void parser_cmd(char *cmd);
void ls();
void pwd();
void cd();
void echo(struct command command);

void cat();

struct command command;

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
        parser_cmd(cmd);
        memset(cmd, 0, 0x100);

        strcpy(cmd, command.argv[0]);
        for (int i = 0; i < command.argc; i++)
        {
            printf("argv[%d] %s\n", i, command.argv[i]);
        }

        if (!strcmp(cmd, "ls"))
        {
            ls();
        }
        else if (strcmp(cmd, "pwd"))
        {
            pwd();
        }
        else if (strcmp(cmd, "cd"))
        {
            cd();
        }
        else if (strcmp(cmd, "echo"))
        {
            echo(command);
        }
        else if (strcmp(cmd, "cat"))
        {
            cat();
        }
    }
}
void ls()
{
    printf("ls called !");
}
void cd()
{
}
void pwd()
{
}
void cat()
{
}
void echo(struct command command)
{
}
void strip(char *cmd)
{
    int start_idx = 0;
    int len_cmd = strlen(cmd); // just idx
    int end_idx = len_cmd - 1;
    while (cmd[start_idx] == ' ' || cmd[end_idx] == ' ')
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
    cmd[strlen(cmd)] = '\x00'; // input: 'ls -lh -a'
    int len_cmd = strlen(cmd);
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
}