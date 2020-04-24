#ifndef _MOVE_FRAME_H
#define _MOVE_FRAME_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define X_AXIS  0
#define Y_AXIS  1
#define Z_AXIS  2
#define XYZ_COORD 3

#define TRUE    1
#define FALSE   0

typedef struct _GraphicsInstrMoveFrame {
    float v;
    float s[XYZ_COORD];
} GraphicsInstrMoveFrame_t;

typedef struct _GraphicsInstrTbl {
    unsigned int totle_frame_num;
    GraphicsInstrMoveFrame_t *frame_addr;
} GraphicsInstrTbl_t;

GraphicsInstrTbl_t* GraphicsInstrTbl_Init(unsigned int parallel_axis);
unsigned int GraphicsInstrTbl_AppendFrame(GraphicsInstrTbl_t* p, const float v, const float s[XYZ_COORD]);

#endif // _MOVE_FRAME_H
