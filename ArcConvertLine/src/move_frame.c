#include "move_frame.h"

#define MAX_FRAME_NUM 1000

GraphicsInstrTbl_t* GraphicsInstrTbl_Init(unsigned int parallel_axis)
{
    GraphicsInstrTbl_t* p = (GraphicsInstrTbl_t*)malloc(sizeof(GraphicsInstrTbl_t) + sizeof(GraphicsInstrMoveFrame_t) * MAX_FRAME_NUM);
    assert(p);

    p->totle_frame_num = 0;
    p->frame_addr = &p->frame_addr;
    p->frame_addr = (GraphicsInstrMoveFrame_t *)((unsigned int*)p->frame_addr + 1);
}

unsigned int GraphicsInstrTbl_AppendFrame(GraphicsInstrTbl_t* p, const float v, const float s[XYZ_COORD])
{
    assert(p);
    if (p->totle_frame_num <= MAX_FRAME_NUM - 1) {
        GraphicsInstrMoveFrame_t* q = p->frame_addr + p->totle_frame_num;

        q->v = v;
        memcpy(q->s, s, sizeof(float) * XYZ_COORD);

        p->totle_frame_num += 1;

        return TRUE;
    }
    return FALSE;
}

