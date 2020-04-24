#include "ArcConvertLine.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SQUARE(n) ((n) * (n))
#define PI (3.1415926)

unsigned int isThreePointCollinear(const float points[3][XYZ_COORD])
{
    unsigned int i;
    float v10[XYZ_COORD],v20[XYZ_COORD],n[XYZ_COORD];
    float ftmp;
    float err = 1e-6;

    for(i = 0; i < XYZ_COORD; i++) {
        v10[i] = points[1][i] - points[0][i];
        v20[i] = points[2][i] - points[0][i];
    }

    cross_product(n, v10, v20);

    ftmp = sqrt(SQUARE(n[X_AXIS]) + SQUARE(n[Y_AXIS]) + SQUARE(n[Z_AXIS]));

    return (fabs(ftmp) <= err ? true : false);
}

void cross_product(float n[XYZ_COORD], const float v1[XYZ_COORD], const float v2[XYZ_COORD])
{
    assert(n);

    n[X_AXIS] =   v1[Y_AXIS] * v2[Z_AXIS] - v1[Z_AXIS] * v2[Y_AXIS];
    n[Y_AXIS] = -(v1[X_AXIS] * v2[Z_AXIS] - v1[Z_AXIS] * v2[X_AXIS]);
    n[Z_AXIS] =   v1[X_AXIS] * v2[Y_AXIS] - v1[Y_AXIS] * v2[X_AXIS];
}

void vector_unit(float v[XYZ_COORD])
{
    unsigned int i;

    float den = sqrt(SQUARE(v[X_AXIS]) + SQUARE(v[Y_AXIS]) +SQUARE(v[Z_AXIS]));
    
    for (i = 0; i < XYZ_COORD; i++)
        v[i] = v[i] / den;
}

unsigned int calc_center_and_radius(float center[XYZ_COORD], float *radius, const float points[3][XYZ_COORD])
{
    unsigned int i;
    float n[XYZ_COORD],n10[XYZ_COORD],n20[XYZ_COORD];
    float v10[XYZ_COORD],v20[XYZ_COORD];
    float c10[XYZ_COORD],c20[XYZ_COORD];
    float delta[XYZ_COORD];
    float A[2][2],A_inv[2][2];
    float B[2];
    float X[2];
    float ftmp = 0.0f;
    float err = 1e-6;

    for(i = 0; i < XYZ_COORD; i++) {
        v10[i] = points[1][i] - points[0][i];
        v20[i] = points[2][i] - points[0][i];
    }

    cross_product(n  , v10, v20);
    cross_product(n10,   n, v10);
    cross_product(n20,   n, v20);

    for(i = 0; i < XYZ_COORD; i++) {
        c10[i] = (points[1][i] + points[0][i]) / 2;
        c20[i] = (points[2][i] + points[0][i]) / 2;
    }

    A[0][0] = n10[X_AXIS]; A[0][1] = -n20[X_AXIS];
    A[1][0] = n10[Y_AXIS]; A[1][1] = -n20[Y_AXIS];

    B[0] = c20[X_AXIS] - c10[X_AXIS];
    B[1] = c20[Y_AXIS] - c10[Y_AXIS];

    ftmp = A[0][0] * A[1][1] - A[0][1] * A[1][0];
    if (fabs(ftmp) <= err)
        return false;

    A_inv[0][0] =  A[1][1] / ftmp;
    A_inv[0][1] = -A[0][1] / ftmp;
    A_inv[1][0] = -A[1][0] / ftmp;
    A_inv[1][1] =  A[0][0] / ftmp;

    X[0] = A_inv[0][0] * B[0] + A_inv[0][1] * B[1];
    X[1] = A_inv[1][0] * B[0] + A_inv[1][1] * B[1];

    center[X_AXIS] = c10[X_AXIS] + n10[X_AXIS] * X[0];
    center[Y_AXIS] = c10[Y_AXIS] + n10[Y_AXIS] * X[0];
    center[Z_AXIS] = c10[Z_AXIS] + n10[Z_AXIS] * X[0];

    delta[X_AXIS] = points[0][X_AXIS] - center[X_AXIS];
    delta[Y_AXIS] = points[0][Y_AXIS] - center[Y_AXIS];
    delta[Z_AXIS] = points[0][Z_AXIS] - center[Z_AXIS];

    *radius = sqrt(SQUARE(delta[X_AXIS]) + SQUARE(delta[Y_AXIS]) + SQUARE(delta[Z_AXIS]));

    return true;
}

unsigned int CreateLinePoints(const float center[XYZ_COORD], const float radius, const float points[3][XYZ_COORD])
{
    unsigned int i;
    unsigned int cnt;
    float alpha = 0.0f;
    float h = 0.2;
    float k = (2 * radius - h) * h;
    float l = 2 * k;
    float delta_radian = asin(l / (2 * radius));
    float coord[XYZ_COORD];

    float v10[XYZ_COORD],v20[XYZ_COORD];
    float n[XYZ_COORD];
    float a[XYZ_COORD],b[XYZ_COORD];

    for(i = 0; i < XYZ_COORD; i++) {
        v10[i] = points[1][i] - points[0][i];
        v20[i] = points[2][i] - points[0][i];
    }
    cross_product(n, v10, v20);

    for (i = 0; i < XYZ_COORD; i++)
        a[i] = points[0][i] - center[i];

    cross_product(b,a,n);

    vector_unit(a);
    vector_unit(b);

    cnt = 0;
    while(alpha <= 2 * PI) {
        for (i = X_AXIS; i < XYZ_COORD; i++)
            coord[i] = center[i] + radius * cos(alpha) * a[i] + radius * sin(alpha) * b[i];
        alpha += delta_radian;
        cnt += 1;
    }

    if ((alpha - delta_radian) < (2 * PI)) {
        alpha = 2 * PI;
        for (i = X_AXIS; i < XYZ_COORD; i++)
            coord[i] = center[i] + radius * cos(alpha) * a[i] + radius * sin(alpha) * b[i];
        cnt += 1;
    }

    return cnt;
}

unsigned int CreateLinePoints_2D(const float center[XYZ_COORD], const float radius, const float points[3][XYZ_COORD], const unsigned parallel_axis)
{
    unsigned int cnt;
    float alpha = 0.0f;
    float h = 0.2;
    float k = (2 * radius - h) * h;
    float l = 2 * k;
    float delta_radian = asin(l / (2 * radius));
    float coord[XYZ_COORD];

    cnt = 0;
    while(alpha <= 2 * PI) {
        switch(parallel_axis){
            case X_AXIS:
                coord[X_AXIS] = center[X_AXIS];
                coord[Y_AXIS] = center[Y_AXIS] + radius * cos(alpha);
                coord[Z_AXIS] = center[Z_AXIS] + radius * sin(alpha);
                break;
            case Y_AXIS:
                coord[X_AXIS] = center[X_AXIS] + radius * cos(alpha);
                coord[Y_AXIS] = center[Y_AXIS];
                coord[Z_AXIS] = center[Z_AXIS] + radius * sin(alpha);
                break;
            case Z_AXIS:
                coord[X_AXIS] = center[X_AXIS] + radius * cos(alpha);
                coord[Y_AXIS] = center[Y_AXIS] + radius * sin(alpha);
                coord[Z_AXIS] = center[Z_AXIS];
                break;
        }

        alpha += delta_radian;
        cnt += 1;
    }

    if ((alpha - delta_radian) < (2 * PI)) {
        alpha = 2 * PI;
        switch(parallel_axis){
            case X_AXIS:
                coord[X_AXIS] = center[X_AXIS];
                coord[Y_AXIS] = center[Y_AXIS] + radius * cos(alpha);
                coord[Z_AXIS] = center[Z_AXIS] + radius * sin(alpha);
                break;
            case Y_AXIS:
                coord[X_AXIS] = center[X_AXIS] + radius * cos(alpha);
                coord[Y_AXIS] = center[Y_AXIS];
                coord[Z_AXIS] = center[Z_AXIS] + radius * sin(alpha);
                break;
            case Z_AXIS:
                coord[X_AXIS] = center[X_AXIS] + radius * cos(alpha);
                coord[Y_AXIS] = center[Y_AXIS] + radius * sin(alpha);
                coord[Z_AXIS] = center[Z_AXIS];
                break;
        }
        cnt += 1;
    }

    return cnt;
}

unsigned int is2DGraphics(const float points[3][XYZ_COORD], unsigned int* parallel_axis)
{
    unsigned int i;
    float v10[XYZ_COORD],v20[XYZ_COORD];
    float n[XYZ_COORD];
    float err = 1e-6;

    for(i = 0; i < XYZ_COORD; i++) {
        v10[i] = points[1][i] - points[0][i];
        v20[i] = points[2][i] - points[0][i];
    }
    cross_product(n, v10, v20);

    vector_unit(n);

    for(i = 0; i < XYZ_COORD; i++) {
        if (fabs(n[i] - 1.0f) <= err) {
            *parallel_axis = i;
            return true;
        }
    }

    return false;
}

unsigned int calc_center_and_radius_2D(float center[XYZ_COORD],float *radius, const float points[3][XYZ_COORD],const unsigned int parallel_axis)
{
    unsigned int i;

    float A[2][2],B[2],C[2];
    float t_mat_a[2][2];
    float a,b,ftmp;
    float err = 1e-6;
    float delta[XYZ_COORD];

    if(parallel_axis >= XYZ_COORD)
        return false;

    center[parallel_axis] = points[0][parallel_axis];

    switch(parallel_axis) {
        case X_AXIS:
            t_mat_a[0][0] = points[0][Y_AXIS] - points[2][Y_AXIS];
            t_mat_a[0][1] = points[0][Z_AXIS] - points[2][Z_AXIS];
            t_mat_a[1][0] = points[1][Y_AXIS] - points[2][Y_AXIS];
            t_mat_a[1][1] = points[1][Z_AXIS] - points[2][Z_AXIS];

            B[0] = ((SQUARE(points[0][Y_AXIS]) - SQUARE(points[2][Y_AXIS])) + 
                    (SQUARE(points[0][Z_AXIS]) - SQUARE(points[2][Z_AXIS]))) / 2;
            B[1] = ((SQUARE(points[1][Y_AXIS]) - SQUARE(points[2][Y_AXIS])) + 
                    (SQUARE(points[1][Z_AXIS]) - SQUARE(points[2][Z_AXIS]))) / 2;
            break;
        case Y_AXIS:
            t_mat_a[0][0] = points[0][X_AXIS] - points[2][X_AXIS];
            t_mat_a[0][1] = points[0][Z_AXIS] - points[2][Z_AXIS];
            t_mat_a[1][0] = points[1][X_AXIS] - points[2][X_AXIS];
            t_mat_a[1][1] = points[1][Z_AXIS] - points[2][Z_AXIS];

            B[0] = ((SQUARE(points[0][X_AXIS]) - SQUARE(points[2][X_AXIS])) + 
                    (SQUARE(points[0][Z_AXIS]) - SQUARE(points[2][Z_AXIS]))) / 2;
            B[1] = ((SQUARE(points[1][X_AXIS]) - SQUARE(points[2][X_AXIS])) + 
                    (SQUARE(points[1][Z_AXIS]) - SQUARE(points[2][Z_AXIS]))) / 2;
            break;
        case Z_AXIS:
            t_mat_a[0][0] = points[0][X_AXIS] - points[2][X_AXIS];
            t_mat_a[0][1] = points[0][Y_AXIS] - points[2][Y_AXIS];
            t_mat_a[1][0] = points[1][X_AXIS] - points[2][X_AXIS];
            t_mat_a[1][1] = points[1][Y_AXIS] - points[2][Y_AXIS];

            B[0] = ((SQUARE(points[0][X_AXIS]) - SQUARE(points[2][X_AXIS])) + 
                    (SQUARE(points[0][Y_AXIS]) - SQUARE(points[2][Y_AXIS]))) / 2;
            B[1] = ((SQUARE(points[1][X_AXIS]) - SQUARE(points[2][X_AXIS])) + 
                    (SQUARE(points[1][Y_AXIS]) - SQUARE(points[2][Y_AXIS]))) / 2;
            break;
    }

    a = t_mat_a[0][0] * t_mat_a[1][1];
    b = t_mat_a[0][1] * t_mat_a[1][0];

    ftmp = a - b;
    if (fabs(ftmp) < err) 
        return false;

    A[0][0] =  t_mat_a[1][1] / ftmp;
    A[0][1] = -t_mat_a[0][1] / ftmp;
    A[1][0] = -t_mat_a[1][0] / ftmp;
    A[1][1] =  t_mat_a[0][0] / ftmp;

    C[0] = A[0][0] * B[0] + A[0][1] * B[1];
    C[1] = A[1][0] * B[0] + A[1][1] * B[1];

    switch(parallel_axis) {
        case X_AXIS:
            center[Y_AXIS] = C[0];
            center[Z_AXIS] = C[1];
            break;
        case Y_AXIS:
            center[X_AXIS] = C[0];
            center[Z_AXIS] = C[1];
            break;
        case Z_AXIS:
            center[X_AXIS] = C[0];
            center[Y_AXIS] = C[1];
            break;
    }

    for (i = 0; i < XYZ_COORD; i++)
        delta[i] = points[0][i] - center[i];

    *radius = sqrt(SQUARE(delta[X_AXIS]) + SQUARE(delta[Y_AXIS]) + SQUARE(delta[Z_AXIS]));

    return true;
}

unsigned int ArcBreakToLine(const float points[3][XYZ_COORD])
{
    assert(points);
    assert(points[0] && points[1] && points[2]);

    unsigned int i;
    unsigned int parallel_axis;
    float center[XYZ_COORD];
    float radius;

    unsigned int cnt_points = 0;

    if (isThreePointCollinear(points)){
        return cnt_points ;
    }

    if (is2DGraphics(points,&parallel_axis)) {
        if(calc_center_and_radius_2D(center,&radius, points, parallel_axis) == false)
            return cnt_points;

        cnt_points = CreateLinePoints_2D(center, radius, points, parallel_axis);
    } else {
        if(calc_center_and_radius(center, &radius, points) == false)
            return cnt_points ;

        cnt_points = CreateLinePoints(center, radius, points);
    }

    return cnt_points ;
}
