#include <stdio.h>

int main(int argc, char *argv[])
    {
        printf("%s \n", __FILE__);
        printf("%d \n", __LINE__);
        printf("%s \n", __DATE__);
        printf("%s \n", __TIME__);
        printf("%d \n", __linux__);
        return 0;
    }