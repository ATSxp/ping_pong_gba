#ifndef E_BLOCKS_H
#define E_BLOCKS_H

#include "gba.h"

extern GBA_Sprite block_spr, block2_spr;
extern u32 point1, point2, b2_state;

void initBlocks();
void updateBlocks();

#endif // !E_BLOCKS_H
