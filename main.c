#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
struct command
{
    char *argv[10]; // toi da 1 cau lenh co 9 tham so
    char argc;
    // void cmd = argv[0]; // phan tu dau tien
} command;
char current_work_dirrectory[255];
char previous_work_dirrectory[255];

struct command command;
void ls() // ls <-lha> <file>
{
    printf("ls called !\n");
    char ls_option[3] = {'l', 'h', 'a'}; //
    char default_path[5] = ".";

    DIR *dir = opendir(default_path);
    if (dir == NULL)
    {
        perror("NULL");
        return;
    }
    else
    {

        while (readdir(dir)->d_name != NULL)
        {
            printf("%s", readdir(dir)->d_name);
            // }
        }
    }
}
void pwd() // pwd
{
    memset(current_work_dirrectory, 0, 100);
    getcwd(current_work_dirrectory, 100);
}
void cd() // cd <LOCALTION>
{
    char location[255];
    strcpy(location, command.argv[1]);

    if (!strcmp(location, "-"))
    {
        memset(current_work_dirrectory, 0, 100);
        strcpy(current_work_dirrectory, previous_work_dirrectory);
        getcwd(previous_work_dirrectory, 100);
        chdir(current_work_dirrectory);
    }

    else
    {
        memset(previous_work_dirrectory, 0, 100);
        getcwd(previous_work_dirrectory, 100);
        int check = chdir(location);
        if (check == -1)
        {
            printf("The location doesn't existed !\n");
        }
        else
        {
            memset(current_work_dirrectory, 0, 100);
            getcwd(current_work_dirrectory, 100);
            printf("changed to %s", current_work_dirrectory);
        }
    }
}
void cat()
{
    int fd = open(command.argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("error");
        return;
    }
    char buf[0x1000];
    while (read(fd, buf, 0x1000))
    {
        write(0, buf, strlen(buf));
    }
    close(fd);
}
char check_if_command_option(char *command_option_list)
{
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
void help()
{
    printf("pwd : pwd\n");
    printf("cd : cd <dir> || cd -\n");
    printf("echo : echo <something>\n");
    printf("ls : ls <dir> <option>\n");
    printf("cat : cat <file>\n");
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
        pwd();
        printf("\n%s$ ", current_work_dirrectory);
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
            printf("%s", current_work_dirrectory);
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
        else if (!strcmp(command.argv[0], "help"))
        {
            help();
        }
    }
}
