#include <stdio.h>
#include <string.h>

void strip1(char *a)
{
    strcpy(a, "123");
}

void strip2(char **a)
{
    strcpy(*a, "123");
}
int main()
{
    char a[10] = "abc";
    strip1(a);
    printf("a : %s\n", a);
    char *b = a;
    strip2(&b);
    printf("a : %s\n", a);
}