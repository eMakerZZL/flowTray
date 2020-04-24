#include "unity.h"
#include "ArcConvertLine.h"


void setUp(void)
{
}

void tearDown(void)
{
}

void test_ArcConvertLine_ThreeSameCoordPointsWasFalse(void)
{
    float p[3][XYZ_COORD] = {
        {0,0,0},
        {0,0,0},
        {0,0,0},
    };

    TEST_ASSERT_TRUE(isThreePointCollinear(p));
}

void test_ArcConvertLine_TowPointsSameWasFalse(void)
{
    float p[3][XYZ_COORD] = {
        {0,0,0},
        {0,0,0},
        {1,0,0},
    };

    TEST_ASSERT_TRUE(isThreePointCollinear(p));
}

void test_ArcConvertLine_ThreePointsNotColllinear(void)
{
    float p[3][XYZ_COORD] = {
        {1,3,0},
        {3,0,0},
        {1,5,0},
    };

    TEST_ASSERT_FALSE(isThreePointCollinear(p));
}

void test_ArcConvertLine_Cross(void)
{
    const float v1[XYZ_COORD] = {1,0,0};
    const float v2[XYZ_COORD] = {0,1,0};
    const float v3[XYZ_COORD] = {0,0,1};

    float res[XYZ_COORD];

    cross_product(res,v1,v2);

    TEST_ASSERT_EQUAL_FLOAT(res[0],v3[0]);
    TEST_ASSERT_EQUAL_FLOAT(res[1],v3[1]);
    TEST_ASSERT_EQUAL_FLOAT(res[2],v3[2]);
}

void test_ArcConvertLine_Cross1(void)
{
    const float v1[XYZ_COORD] = {1,1,1};
    const float v2[XYZ_COORD] = {2,3,1};
    const float v3[XYZ_COORD] = {-2,1,1};

    float res[XYZ_COORD];

    cross_product(res,v1,v2);

    TEST_ASSERT_EQUAL_FLOAT(v3[0],res[0]);
    TEST_ASSERT_EQUAL_FLOAT(v3[1],res[1]);
    TEST_ASSERT_EQUAL_FLOAT(v3[2],res[2]);

}

void test_ArcConvertLine_AccordingPointsGetCenterAndRadius(void)
{
    const float p[3][XYZ_COORD] = {
        {1,0,0},
        {0,1,0},
        {0,0,1},
    };

    float res[XYZ_COORD];
    float radius;

    TEST_ASSERT_TRUE(calc_center_and_radius(res,&radius,p));
    TEST_ASSERT_FLOAT_WITHIN(0.8165, radius, 1e-4);
    TEST_ASSERT_FLOAT_WITHIN(0.3333, res[X_AXIS], 1e-4);
    TEST_ASSERT_FLOAT_WITHIN(0.3333, res[Y_AXIS], 1e-4);
    TEST_ASSERT_FLOAT_WITHIN(0.3333, res[Z_AXIS], 1e-4);
}

void test_ArcConvertLine_CreatePoints(void)
{
    const float p[3][XYZ_COORD] = {
        {1,0,0},
        {0,1,0},
        {0,0,1},
    };

    TEST_ASSERT_EQUAL_UINT32(19,ArcBreakToLine(p));
}

void test_ArcConvertLine_2DPointsXEqual(void)
{
    const float p[3][XYZ_COORD] = {
        {0,0,0},
        {0,1,0},
        {0,0,1},
    };

    const float res_radius = sqrt(2.0f);
    const float res_center[XYZ_COORD] = {0.0f,0.5f,0.5f};

    float res[XYZ_COORD];
    float radius;

    TEST_ASSERT_TRUE(calc_center_and_radius_2D(res,&radius,p,X_AXIS));
    TEST_ASSERT_FLOAT_WITHIN(res_radius, radius, 0.0001);
    for (unsigned int i = 0; i < XYZ_COORD; i++)
        TEST_ASSERT_EQUAL_FLOAT(res_center[i], res[i]);
}

void test_ArcConvertLine_2DPointsYEqual(void)
{
    const float p[3][XYZ_COORD] = {
        {1,0,0},
        {0,0,0},
        {0,0,1},
    };

    const float res_radius = sqrt(2.0f);
    const float res_center[XYZ_COORD] = {0.5f,0.0f,0.5f};

    float res[XYZ_COORD];
    float radius;

    TEST_ASSERT_TRUE(calc_center_and_radius_2D(res,&radius,p,Y_AXIS));
    TEST_ASSERT_FLOAT_WITHIN(res_radius, radius, 0.0001);
    for (unsigned int i = 0; i < XYZ_COORD; i++)
        TEST_ASSERT_EQUAL_FLOAT(res_center[i], res[i]);
}

void test_ArcConvertLine_2DPointsZEqual(void)
{
    const float p[3][XYZ_COORD] = {
        {0,0,0},
        {1,0,0},
        {0,1,0},
    };

    const float res_radius = sqrt(2.0f);
    const float res_center[XYZ_COORD] = {0.5f,0.5f,0.0f};

    float res[XYZ_COORD];
    float radius;

    TEST_ASSERT_TRUE(calc_center_and_radius_2D(res,&radius,p,Z_AXIS));
    TEST_ASSERT_FLOAT_WITHIN(res_radius, radius, 0.0001);
    for (unsigned int i = 0; i < XYZ_COORD; i++)
        TEST_ASSERT_EQUAL_FLOAT(res_center[i], res[i]);
}

void test_ArcConvertLine_JudgeGraphaIs2DOrNot(void)
{
    const float p[3][XYZ_COORD] = {
        {0,0,0},
        {0,1,0},
        {0,0,1},
    };

    unsigned int parallel_axis;
    TEST_ASSERT_TRUE(is2DGraphics(p,&parallel_axis));

    TEST_ASSERT_EQUAL_UINT32(X_AXIS, parallel_axis);
}

void test_ArcConvertLine_Create2DGraphics(void)
{
    const float p[3][XYZ_COORD] = {
        {0,0,0},
        {0,1,0},
        {0,0,1},
    };

    TEST_ASSERT_EQUAL_UINT32(19,ArcBreakToLine(p));
}
