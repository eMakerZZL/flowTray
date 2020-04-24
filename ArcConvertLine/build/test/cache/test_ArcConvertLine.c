#include "build/temp/_test_ArcConvertLine.c"
#include "ArcConvertLine.h"
#include "unity.h"




void setUp(void)

{

}



void tearDown(void)

{

}



void test_ArcConvertLine_ThreeSameCoordPointsWasFalse(void)

{

    float p[3][3] = {

        {0,0,0},

        {0,0,0},

        {0,0,0},

    };



    if ((isThreePointCollinear(p))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(21)));};

}



void test_ArcConvertLine_TowPointsSameWasFalse(void)

{

    float p[3][3] = {

        {0,0,0},

        {0,0,0},

        {1,0,0},

    };



    if ((isThreePointCollinear(p))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(32)));};

}



void test_ArcConvertLine_ThreePointsNotColllinear(void)

{

    float p[3][3] = {

        {1,3,0},

        {3,0,0},

        {1,5,0},

    };



    if (!(isThreePointCollinear(p))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(43)));};

}



void test_ArcConvertLine_Cross(void)

{

    const float v1[3] = {1,0,0};

    const float v2[3] = {0,1,0};

    const float v3[3] = {0,0,1};



    float res[3];



    cross_product(res,v1,v2);



    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((res[0])) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((res[0]))), (UNITY_FLOAT)((UNITY_FLOAT)((v3[0]))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(56)));

    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((res[1])) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((res[1]))), (UNITY_FLOAT)((UNITY_FLOAT)((v3[1]))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(57)));

    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((res[2])) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((res[2]))), (UNITY_FLOAT)((UNITY_FLOAT)((v3[2]))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(58)));

}



void test_ArcConvertLine_Cross1(void)

{

    const float v1[3] = {1,1,1};

    const float v2[3] = {2,3,1};

    const float v3[3] = {-2,1,1};



    float res[3];



    cross_product(res,v1,v2);



    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((v3[0])) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((v3[0]))), (UNITY_FLOAT)((UNITY_FLOAT)((res[0]))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(71)));

    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((v3[1])) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((v3[1]))), (UNITY_FLOAT)((UNITY_FLOAT)((res[1]))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(72)));

    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((v3[2])) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((v3[2]))), (UNITY_FLOAT)((UNITY_FLOAT)((res[2]))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(73)));



}



void test_ArcConvertLine_AccordingPointsGetCenterAndRadius(void)

{

    const float p[3][3] = {

        {1,0,0},

        {0,1,0},

        {0,0,1},

    };



    float res[3];

    float radius;



    if ((calc_center_and_radius(res,&radius,p))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(88)));};

    UnityAssertFloatsWithin((UNITY_FLOAT)((0.8165)), (UNITY_FLOAT)((radius)), (UNITY_FLOAT)((1e-4)), (

   ((void *)0)

   ), (UNITY_UINT)(89));

    UnityAssertFloatsWithin((UNITY_FLOAT)((0.3333)), (UNITY_FLOAT)((res[0])), (UNITY_FLOAT)((1e-4)), (

   ((void *)0)

   ), (UNITY_UINT)(90));

    UnityAssertFloatsWithin((UNITY_FLOAT)((0.3333)), (UNITY_FLOAT)((res[1])), (UNITY_FLOAT)((1e-4)), (

   ((void *)0)

   ), (UNITY_UINT)(91));

    UnityAssertFloatsWithin((UNITY_FLOAT)((0.3333)), (UNITY_FLOAT)((res[2])), (UNITY_FLOAT)((1e-4)), (

   ((void *)0)

   ), (UNITY_UINT)(92));

}



void test_ArcConvertLine_CreatePoints(void)

{

    const float p[3][3] = {

        {1,0,0},

        {0,1,0},

        {0,0,1},

    };



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((19)), (UNITY_INT)(UNITY_UINT32)((ArcBreakToLine(p))), (

   ((void *)0)

   ), (UNITY_UINT)(103), UNITY_DISPLAY_STYLE_UINT32);

}



void test_ArcConvertLine_2DPointsXEqual(void)

{

    const float p[3][3] = {

        {0,0,0},

        {0,1,0},

        {0,0,1},

    };



    const float res_radius = sqrt(2.0f);

    const float res_center[3] = {0.0f,0.5f,0.5f};



    float res[3];

    float radius;



    if ((calc_center_and_radius_2D(res,&radius,p,0))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(120)));};

    UnityAssertFloatsWithin((UNITY_FLOAT)((res_radius)), (UNITY_FLOAT)((radius)), (UNITY_FLOAT)((0.0001)), (

   ((void *)0)

   ), (UNITY_UINT)(121));

    for (unsigned int i = 0; i < 3; i++)

        UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((res_center[i])) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((res_center[i]))), (UNITY_FLOAT)((UNITY_FLOAT)((res[i]))), ((

       ((void *)0)

       )), (UNITY_UINT)((UNITY_UINT)(123)));

}



void test_ArcConvertLine_2DPointsYEqual(void)

{

    const float p[3][3] = {

        {1,0,0},

        {0,0,0},

        {0,0,1},

    };



    const float res_radius = sqrt(2.0f);

    const float res_center[3] = {0.5f,0.0f,0.5f};



    float res[3];

    float radius;



    if ((calc_center_and_radius_2D(res,&radius,p,1))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(140)));};

    UnityAssertFloatsWithin((UNITY_FLOAT)((res_radius)), (UNITY_FLOAT)((radius)), (UNITY_FLOAT)((0.0001)), (

   ((void *)0)

   ), (UNITY_UINT)(141));

    for (unsigned int i = 0; i < 3; i++)

        UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((res_center[i])) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((res_center[i]))), (UNITY_FLOAT)((UNITY_FLOAT)((res[i]))), ((

       ((void *)0)

       )), (UNITY_UINT)((UNITY_UINT)(143)));

}



void test_ArcConvertLine_2DPointsZEqual(void)

{

    const float p[3][3] = {

        {0,0,0},

        {1,0,0},

        {0,1,0},

    };



    const float res_radius = sqrt(2.0f);

    const float res_center[3] = {0.5f,0.5f,0.0f};



    float res[3];

    float radius;



    if ((calc_center_and_radius_2D(res,&radius,p,2))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(160)));};

    UnityAssertFloatsWithin((UNITY_FLOAT)((res_radius)), (UNITY_FLOAT)((radius)), (UNITY_FLOAT)((0.0001)), (

   ((void *)0)

   ), (UNITY_UINT)(161));

    for (unsigned int i = 0; i < 3; i++)

        UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((res_center[i])) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((res_center[i]))), (UNITY_FLOAT)((UNITY_FLOAT)((res[i]))), ((

       ((void *)0)

       )), (UNITY_UINT)((UNITY_UINT)(163)));

}



void test_ArcConvertLine_JudgeGraphaIs2DOrNot(void)

{

    const float p[3][3] = {

        {0,0,0},

        {0,1,0},

        {0,0,1},

    };



    unsigned int parallel_axis;

    if ((is2DGraphics(p,&parallel_axis))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(175)));};



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((parallel_axis)), (

   ((void *)0)

   ), (UNITY_UINT)(177), UNITY_DISPLAY_STYLE_UINT32);

}



void test_ArcConvertLine_Create2DGraphics(void)

{

    const float p[3][3] = {

        {0,0,0},

        {0,1,0},

        {0,0,1},

    };



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((19)), (UNITY_INT)(UNITY_UINT32)((ArcBreakToLine(p))), (

   ((void *)0)

   ), (UNITY_UINT)(188), UNITY_DISPLAY_STYLE_UINT32);

}
