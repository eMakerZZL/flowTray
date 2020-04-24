#include "unity.h"
#include "move_frame.h"

static GraphicsInstrTbl_t* p = NULL;

void setUp(void)
{
    p = GraphicsInstrTbl_Init(X_AXIS);
    assert(p);
}

void tearDown(void)
{
    assert(p);
    free(p);
}

void test_move_frame_MoveFrameAddrWasOk(void)
{
    float v = 10.0f;
    float s[XYZ_COORD] = {1,2,3};

    GraphicsInstrTbl_AppendFrame(p, v, s);

    GraphicsInstrMoveFrame_t *q = p->frame_addr;

    TEST_ASSERT_EQUAL_FLOAT(v,q->v);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(s, q->s, XYZ_COORD);
}

void test_move_frame_AddMultFrame(void)
{
    float v = 10.0f;
    float s[XYZ_COORD] = {1,2,3};

    GraphicsInstrTbl_AppendFrame(p, v, s);
    GraphicsInstrTbl_AppendFrame(p, v, s);
    GraphicsInstrTbl_AppendFrame(p, v, s);
    GraphicsInstrTbl_AppendFrame(p, v, s);
    GraphicsInstrTbl_AppendFrame(p, v, s);
    GraphicsInstrTbl_AppendFrame(p, 20, s);

    TEST_ASSERT_EQUAL_UINT32(6, p->totle_frame_num);

    GraphicsInstrMoveFrame_t *q = p->frame_addr + p->totle_frame_num - 1;

    TEST_ASSERT_EQUAL_FLOAT(20,q->v);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(s, q->s, XYZ_COORD);
}
