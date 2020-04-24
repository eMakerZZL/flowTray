#ifndef _ARCCONVERTLINE_H
#define _ARCCONVERTLINE_H

#include <stdbool.h>
#include <math.h>

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

#define XYZ_COORD 3

unsigned int isThreePointCollinear(const float points[3][XYZ_COORD]);
void cross_product(float n[XYZ_COORD], const float v1[XYZ_COORD], const float v2[XYZ_COORD]);
unsigned int calc_center_and_radius(float center[XYZ_COORD], float *radius, const float points[3][XYZ_COORD]);
unsigned int calc_center_and_radius_2D(float center[XYZ_COORD],float *radius, const float points[3][XYZ_COORD],const unsigned int parallel_axis);
unsigned int ArcBreakToLine(const float points[3][XYZ_COORD]);
unsigned int is2DGraphics(const float points[3][XYZ_COORD], unsigned int* parallel_axis);
void vector_unit(float v[XYZ_COORD]);

#endif // _ARCCONVERTLINE_H
