#include "flight/mixer.h"

float Mixer::mixer[4][4] = {
#if (MIXER == 0) // nothin'
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},

#elif (MIXER == 1) // quad
    {+1,-1,-1,-1}, // back  right (cw)
    {+1,-1,+1,+1}, // front right (ccw)
    {+1,+1,-1,+1}, // back  left  (ccw)
    {+1,+1,+1,-1}, // front left  (cw)

#elif (MIXER == 2) // plane (TAER)
    {1,0,0,0}, // thr
    {0,1,0,0}, // ail
    {0,0,1,0}, // ele
    {0,0,0,1}, // rud

#elif (MIXER == 3) // plane (AETR)
    {0,1,0,0}, // thr
    {0,0,1,0}, // ail
    {1,0,0,0}, // ele
    {0,0,0,1}, // rud

#elif (MIXER == 4) // elevon (TLR)
    {1,0,0,0},   // thr
    {0,+1,1,0}, // left
    {0,-1,1,0}, // right
    {0,0,0,0},
#endif
};
