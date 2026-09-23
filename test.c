#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main()
{
    char buf[50];
    getcwd(buf, 255);
    printf("pwd : %s\n", buf);
    printf("%d", chdir("abc"));
}