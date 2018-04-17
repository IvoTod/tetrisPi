#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <ali_colors.h>
    
struct Block {
    Block() {}
    unsigned int bgColor = ALI_BLUE;
    unsigned int borderColor = ALI_WHITE;
};

#endif
