#include "build/temp/_test_move_frame.c"
#include "move_frame.h"
#include "unity.h"


static GraphicsInstrTbl_t* p = 

                              ((void *)0)

                                  ;



void setUp(void)

{

    p = GraphicsInstrTbl_Init(0);

    

   ((

   p

   ) ? (void)0 : _assert(

   "p"

   , "test/test_move_frame.c", 9))

            ;

}



void tearDown(void)

{

    

   ((

   p

   ) ? (void)0 : _assert(

   "p"

   , "test/test_move_frame.c", 14))

            ;

    free(p);

}



void test_move_frame_MoveFrameAddrWasOk(void)

{

    float v = 10.0f;

    float s[3] = {1,2,3};



    GraphicsInstrTbl_AppendFrame(p, v, s);



    GraphicsInstrMoveFrame_t *q = p->frame_addr;



    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((v)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((v))), (UNITY_FLOAT)((UNITY_FLOAT)((q->v))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(27)));

    UnityAssertEqualFloatArray((UNITY_FLOAT*)((s)), (UNITY_FLOAT*)((q->s)), (UNITY_UINT32)((3)), (

   ((void *)0)

   ), (UNITY_UINT)(28), UNITY_ARRAY_TO_ARRAY);

}



void test_move_frame_AddMultFrame(void)

{

    float v = 10.0f;

    float s[3] = {1,2,3};



    GraphicsInstrTbl_AppendFrame(p, v, s);

    GraphicsInstrTbl_AppendFrame(p, v, s);

    GraphicsInstrTbl_AppendFrame(p, v, s);

    GraphicsInstrTbl_AppendFrame(p, v, s);

    GraphicsInstrTbl_AppendFrame(p, v, s);

    GraphicsInstrTbl_AppendFrame(p, 20, s);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((6)), (UNITY_INT)(UNITY_UINT32)((p->totle_frame_num)), (

   ((void *)0)

   ), (UNITY_UINT)(43), UNITY_DISPLAY_STYLE_UINT32);



    GraphicsInstrMoveFrame_t *q = p->frame_addr + p->totle_frame_num - 1;



    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((20)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((20))), (UNITY_FLOAT)((UNITY_FLOAT)((q->v))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(47)));

    UnityAssertEqualFloatArray((UNITY_FLOAT*)((s)), (UNITY_FLOAT*)((q->s)), (UNITY_UINT32)((3)), (

   ((void *)0)

   ), (UNITY_UINT)(48), UNITY_ARRAY_TO_ARRAY);

}
