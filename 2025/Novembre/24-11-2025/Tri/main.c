#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int test;
    scanf("%d", &test);

    for(int t = 0; t < test; ++t)
    {
        int size;
        scanf("%d", &size);

        int *buffer = (int *)malloc(sizeof(int) * size);

        if(buffer == NULL)
            continue;

        printf(">> ");
        for(int s = 0; s < size; ++s)
        {
            int current;
            scanf("%d", &current);
            buffer[s] = current;
            printf("%d ", buffer[s]);
        }
        printf("\n");

        /*
            Buffer :
                Is an array T of N elements
                the x elements are all different
                and all are in the interval 0 <= x < N.

            Objective:
                Reorganise the array so that T[i] becomes T[T[i]].
                This reorganisation must be done with a space complexity of O(1).
                This reorganisation must be done with a time complexity
                    - in O(n) in the best case.
                    - in O(3n) on average.
                    - in O(n^2) in the worst case.

            Example :
                - 9 0 1 2 3 4 5 6 7 8 → 56 iterations in reverse order → O(n*n-n)
                - 9 8 7 6 5 0 4 3 2 1 → 35 iteration with a centred pivot → O((n+1)*(n/2))
                - 1 2 3 4 5 6 7 8 9 0 → 19 iteration when elements ce follow → O(1+n)
        */

        


        printf("<< ");
        for(int i = 0; i < size; ++i)
            printf("%d ", buffer[i]);
        printf("\n");

        printf("-------\n");

        free(buffer);
    }
}