#include "frechet.h"

double dist(struct point a, struct point b)
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

uint8_t distCloserEps(struct point a, struct point b, double eps)
{
    return dist(a, b) <= eps ? 1 : 0;
}

uint8_t distFartherEps(struct point a, struct point b, double eps)
{
    return dist(a, b) > eps ? 1 : 0;
}
