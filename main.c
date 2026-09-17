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
void echo();
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
        cmd[strlen(cmd) - 1] = '\x00'; // ' ls -lh -a \n'
        parser_cmd(cmd);
        memset(cmd, 0, 0x100);

        strcpy(cmd, command.argv[0]);
        for (int i = 0; i < command.argc; i++)
        {
            printf(" %s\n", command.argv[i]);
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
            echo();
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
void echo()
{
    // echo 'abc xyz'
}
void strip(char *cmd)
{
    int start_idx = 0;
    int len_cmd = strlen(cmd) - 1; // just idx
    int end_idx = len_cmd;
    while (cmd[start_idx] == ' ' || cmd[end_idx] == ' ')
    {
        if (cmd[start_idx] == ' ')
            start_idx++;
        if (cmd[end_idx] == ' ')
            end_idx--;
    }
    char tmp_str[len_cmd];
    memset(tmp_str, 0, len_cmd);
    // printf("start-end : %d-%d\n", start_idx, end_idx);
    strncpy(tmp_str, &cmd[start_idx], end_idx - start_idx + 1);
    // printf("tmp : <%s>\n", tmp_str);
    memset(cmd, 0, 0x100);
    strncpy(cmd, tmp_str, strlen(tmp_str));
}
void parser_cmd(char *cmd)
{
    for (int i = 0; i < 10; i++)
    {
        command.argv[i] = malloc(0x10);
    }
    // printf("cmd : <%s>\n", cmd);
    strip(cmd);
    // printf("cmd : <%s>\n", cmd);
    int len_cmd = strlen(cmd);
    int count = 0;
    command.argc = 0;
    char tmp[len_cmd];
    memset(tmp, 0, len_cmd);

    for (int i = 0; i < len_cmd; i++) // 'ls '
    {

        if (cmd[i] == ' ') // 'ls -lh -a'
        {
            printf("tmp : %s\n", tmp);
            strncpy(command.argv[command.argc], tmp, strlen(tmp));
            printf("command.argv[%d] : %s\n", command.argc, command.argv[command.argc]);
            command.argc++;
            memset(tmp, 0, len_cmd);
            continue;
        }
        else
        {
            if (i == len_cmd - 1)
            {
                char c = cmd[i];
                strncat(tmp, &c, 1);
                printf("tmp : %s\n", tmp);
                strncpy(command.argv[command.argc], tmp, strlen(tmp));
                printf("command.argv[%d] : %s\n", command.argc, command.argv[command.argc]);
                command.argc++;
                break;
            }
            char c = cmd[i];
            strncat(tmp, &c, 1);
            // printf("tmp : %s\n", tmp);
        }
    }
}