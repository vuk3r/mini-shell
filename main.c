#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct command
{
    char command_name[10];
    char *argv[10];
} command;

void parser_cmd(char *cmd)
{
    int max_len = strlen(cmd);
    // we gonna split into command and argv
    struct command command;

    for (int i = 0; i < max_len; i++) // remove all whitespace at the begining
    {
        if (cmd[i] != ' ')
        {
            strcpy(cmd, &cmd[i]);
            // printf("\'%s\'", cmd);
            break;
        }
    }
    strncpy(command.command_name, cmd, strcspn(cmd, " "));
    strcpy(cmd, &cmd[strcspn(cmd, " ") + 1]); // 'ls -lh -a ' -> '-lh -a '

    int i, j, len = 0;
    while (i <= max_len)
    {
        while (cmd[len] != ' ')
        {
            len += 1;
        }
        strncpy(command.argv[j], cmd, len);
        i += len;
        j += 1;
        len += 1; // ignore next ' '
    }
}

int main()
{

    while (1)
    {
        char cmd[0x100];
        memset(cmd, 0, 0x100);

        printf("\n$ ");
        scanf("%s", cmd);
        cmd[strlen(cmd)] = '\x00';
        parser_cmd(cmd);
    }
}