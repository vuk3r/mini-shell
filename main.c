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

    for (int i = 0; i < len_cmd; i++)
    {

        if (cmd[i] == ' ') // ' ls -lh -a '
        {
            strncpy(command.argv[command.argc], tmp, strlen(tmp));
            command.argc++;
            memset(tmp, 0, len_cmd);
            continue;
        }
        else
        {
            if (i == len_cmd - 1)
            {
                strncpy(command.argv[command.argc], tmp, strlen(tmp));
                command.argc++;
                break;
            }
            char c = cmd[i];
            strncat(tmp, &c, 1);
            // printf("tmp : %s\n", tmp);
        }
    }
    for (int i = 0; i < command.argc; i++)
    {
        printf("aaa %s\n", command.argv[i]);
    }
}

int main()
{

    while (1)
    {
        char cmd[0x100];
        memset(cmd, 0, 0x100);

        printf("\n$ ");
        fflush(stdout);
        read(0, cmd, 100);
        cmd[strlen(cmd) - 1] = '\x00'; // ' ls -lh -a \n'
        parser_cmd(cmd);
    }
}