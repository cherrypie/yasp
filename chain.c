#include "frechet.h"

uint8_t chainEpsRecogn(struct chain a, struct chain b, double eps,
                 uint8_t (*q)(struct point a, struct point b, double eps))
/*
 * q returns 1 if the (a, b) pair is permitted, and 0 otherwise
*/
{
    size_t i, j;
    uint8_t res;

    uint8_t ** table = malloc(a.n * sizeof(uint8_t *));
    for(i = 0; i < a.n; ++i)
    {
        table[i] = calloc(b.n, sizeof(uint8_t));
    }

    if(dist(*a.p, *b.p) > eps)
    {
        return 0;
    }

    table[0][1] = q(a.p[0], b.p[1], eps);
    table[1][0] = q(a.p[1], b.p[0], eps);

    for(i = 1; i < a.n; ++i)
    {
        table[i][0] = table[i - 1][0] & q(a.p[i], b.p[0], eps);
    }

    for(i = 1; i < b.n; ++i)
    {
        table[0][i] = table[0][i - 1] & q(a.p[0], b.p[i], eps);
    }

    for(i = 2; i <= (a.n - 1) + (b.n - 1); ++i)
    {
        for(j = i > a.n ? i - a.n + 1 : 1; j < (i > b.n ? b.n : i); ++j)
        {
            table[j][i - j] = q(a.p[j], b.p[i - j], eps) & (
                    table[j - 1][i - j] |
                    table[j][i - j - 1] |
                    table[j - 1][i - j - 1]
                    );
        }
    }

    res = table[a.n - 1][b.n - 1];

    for(i = 0; i < a.n; ++i)
        free(table[i]);
    free(table);

    return res;
}

double chainEpsComp(struct chain a, struct chain b, double eps,
                 uint8_t (*q)(struct point a, struct point b, double eps))
/*
 * q returns 1 if the (a, b) pair is permitted, and 0 otherwise
*/
{
    size_t i, j;
    double res;

    double ** table = malloc(a.n * sizeof(double *));
    for(i = 0; i < a.n; ++i)
    {
        table[i] = calloc(b.n, sizeof(double));
    }

    if(dist(*a.p, *b.p) > eps)
    {
        return 0;
    }

    table[0][1] = q(a.p[0], b.p[1], eps);
    table[1][0] = q(a.p[1], b.p[0], eps);

    for(i = 1; i < a.n; ++i)
    {
        table[i][0] = fmax(table[i - 1][0], q(a.p[i], b.p[0], eps));
    }

    for(i = 1; i < b.n; ++i)
    {
        table[0][i] = fmax(table[0][i - 1], q(a.p[0], b.p[i], eps));
    }

    for(i = 2; i <= (a.n - 1) + (b.n - 1); ++i)
    {
        for(j = i > a.n ? i - a.n + 1 : 1; j < (i > b.n ? b.n : i); ++j)
        {
            table[j][i - j] = fmax(q(a.p[j], b.p[i - j], eps), fmin(
                    table[j - 1][i - j], fmin(
                    table[j][i - j - 1],
                    table[j - 1][i - j - 1]
                    )));
        }
    }

    res = table[a.n - 1][b.n - 1];

    for(i = 0; i < a.n; ++i)
        free(table[i]);
    free(table);

    return res;
}
