#include <stdio.h>
#include <string.h>

int main()
{

    char c[] = "      a ls -lha   ";
    strcspn(c, " ");
    printf("%s",c);
}