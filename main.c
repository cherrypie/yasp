#include "frechet.h"

int main(void)
{
    size_t n = 6, m = 4, i, j;

    for(i = 2; i <= (n - 1) + (m - 1); ++i)
    {
        for(j = i > n ? i - n + 1 : 1; j < (i > m ? m : i); ++j)
        {
            printf("[%d][%d] ", j, i - j);
        }
        printf("\n");
    }

    return 0;
}
