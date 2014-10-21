#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

struct point{
    double x;
    double y;
};

double dist(struct point a, struct point b);
uint8_t distFartherEps(struct point a, struct point b, double eps);
uint8_t distCloserEps(struct point a, struct point b, double eps);

struct chain{
    size_t n;
    struct point * p;
};
