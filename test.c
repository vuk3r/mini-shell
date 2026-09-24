#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd = open("./abc", O_RDONLY);
    if (fd == -1)
    {
        fprintf(stderr, "Không mở được '%s': %s\n",
                "./abc", strerror(errno));
        perror("error");
    }
}