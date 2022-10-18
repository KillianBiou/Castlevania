#include "GameManager.h"
#include "GameMaster.h"

const int level1[] =
{
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 1  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 1  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 1  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 1  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 1  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 1  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 1, 1, 1, 1, 1, 1, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,

    1, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 1, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 1, 1, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 1  , 1, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 1, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 1, 0, 1, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 1, 0  , 1, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 1, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 1, 0, 0, 1, 0  , 0, 0, 0, 0, 0, 0, 0, 1, 0, 0  , 1, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 1, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 1, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 1, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 1, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 1, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 1, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 1, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 1, 1, 1, 1, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 1, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 1, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 1, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 1, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,

    2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
};
const int lvl1XSize = 120;
const int lvl1ySize = 24;
std::multimap<EntityType, sf::Vector2f> lvl1EntityMap{
    {PLAYER, sf::Vector2f(92, 1150)},
    {MEDUSA, sf::Vector2f(0, 100)},
    {MEDUSA, sf::Vector2f(0, 300)},
    {MEDUSA, sf::Vector2f(0, 600)},
    {MEDUSA, sf::Vector2f(0, 900)},
    {MEDUSA, sf::Vector2f(0, 1200)},
    {ZOMBIE, sf::Vector2f(500, 1080)},
    {ZOMBIE, sf::Vector2f(1000, 1080)},
    {ZOMBIE, sf::Vector2f(2000, 500)},
    {ZOMBIE, sf::Vector2f(2500, 500)},
    {ZOMBIE, sf::Vector2f(3000, 500)},
    {ZOMBIE, sf::Vector2f(3500, 500)},
    {ZOMBIE, sf::Vector2f(4000, 500)},
    {ZOMBIE, sf::Vector2f(4500, 500)},
    {ZOMBIE, sf::Vector2f(5000, 500)},
    {ZOMBIE, sf::Vector2f(5500, 500)},
    {ZOMBIE, sf::Vector2f(6000, 500)},
    {MUMMY, sf::Vector2f(6748, 800)},
};
std::string lvl1BackgroundImage = "images/Background1.png";

const int level2[] =
{
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 ,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 ,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 ,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 ,
    1, 0, 1, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 ,
    1, 0, 0, 1, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 ,
    1, 0, 0, 0, 1, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 ,
    1, 0, 0, 0, 0, 1, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 ,
    1, 0, 0, 0, 0, 0, 0, 0, 1, 1  , 1, 1, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 ,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 ,

    1, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 1, 1, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 ,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 ,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 ,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 1, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 ,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 1, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 ,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 ,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 ,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 ,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  , 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 ,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,

    2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 ,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 ,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 ,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2  , 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 ,
};
const int lvl2XSize = 30;
const int lvl2ySize = 24;
std::multimap<EntityType, sf::Vector2f> lvl2EntityMap{
    {PLAYER, sf::Vector2f(192, 1080)}
};

GameManager::GameManager(Difficulty difficulty, GameMaster* gameMaster): gameMaster(gameMaster) {
	this->camera = new Camera();
	this->entityManager = new EntityManager(this->camera, this);
    camera->setEntityManager(this->entityManager);
    this->loadLevel(LEVEL1);
    this->soundManager = new SoundManager();
	
	switch (difficulty)
	{
	case EASY:
		this->pointsToHpUp = { 200, 400, 600, 800 };
		break;
	case MEDIUM:
		this->pointsToHpUp = { 400, 800, 1200, 1600 };
		break;
	case HARD:
		this->pointsToHpUp = { 800, 1600, 2400, 3200 };
		break;
	default:
		break;
	}
}

void GameManager::update(sf::RenderTarget* renderTarget) {
    if (level) {
        this->entityManager->updateAllEntities();

        renderTarget->draw(*this->level);

        entityManager->drawAllEntities(renderTarget);

        this->camera->trackTarget(renderTarget);

        this->soundManager->update();

        if (this->entityManager->getPlayer()->getPosition().x >= (this->level->getSizeX() - 1) * 64) {
            if (this->currentLvlId == LEVEL1)
                this->loadLevel(LEVEL2);
        }
        else if (this->entityManager->getPlayer()->getPosition().x <= 64) {
            if (this->currentLvlId == LEVEL2)
                this->loadLevel(LEVEL1);
        }
    }
}

void GameManager::loadLevel(LevelId id) {
    switch (id) {
    case LEVEL1:
        delete this->level;
        this->currentLvlId = LEVEL1;
        this->level = new Level(level1, lvl1XSize, lvl1ySize, lvl1EntityMap, lvl1BackgroundImage);
        break;
    case LEVEL2:
        delete this->level;
        this->currentLvlId = LEVEL2;
        this->level = new Level(level2, lvl2XSize, lvl2ySize, lvl2EntityMap, lvl1BackgroundImage);
        break;
    }
    this->entityManager->clear();
    this->loadEntities();
}

void GameManager::loadEntities() {
    EntityFactory tempFactory(this->level, this->entityManager, this->camera->getView());

    for (std::pair<EntityType, sf::Vector2f> entry : *this->level->getEntityMap()) {
        tempFactory.createEntity(entry.first, entry.second);
    }
    this->camera->setTarget(this->entityManager->getPlayer());
    this->camera->teleport();
    this->camera->getHealthBar()->setEntity(this->entityManager->getPlayer());
    this->camera->getManaBar()->setPlayer(this->entityManager->getPlayer());
}

void GameManager::startGame() {
    this->soundManager->setCanPlay(true);
    this->soundManager->playMusic(0);
}

const void GameManager::processInput(sf::Event event, sf::RenderTarget* target) {
    switch (event.type) {
    case sf::Event::Closed:
        ((sf::RenderWindow*)target)->close();
        break;
    case sf::Event::Resized:
        break;
    case sf::Event::KeyPressed:
        switch (event.key.code) {
        case sf::Keyboard::Q:
            this->entityManager->getPlayer()->setHorizontalMovement(LEFT);
            this->leftHeld = true;
            break;
        case sf::Keyboard::S:
            break;
        case sf::Keyboard::D:
            this->rightHeld = true;
            this->entityManager->getPlayer()->setHorizontalMovement(RIGHT);
            break;
        case sf::Keyboard::Space:
            this->entityManager->getPlayer()->jump();
            break;
        case sf::Keyboard::E:
            this->entityManager->getPlayer()->attack(false);
            break;
        case sf::Keyboard::Num1:
            this->entityManager->getPlayer()->specialOne();
            break;
        case sf::Keyboard::Num2:
            this->entityManager->getPlayer()->specialTwo();
            break;
        case sf::Keyboard::Num3:
            this->loadLevel(LEVEL1);
            break;
        case sf::Keyboard::Num4:
            this->loadLevel(LEVEL2);
            break;
        }
        break;

    case sf::Event::KeyReleased:
        switch (event.key.code) {
        case sf::Keyboard::Q:
            this->leftHeld = false;
            if (rightHeld) {
                this->entityManager->getPlayer()->setHorizontalMovement(RIGHT);
            }
            else {
                this->entityManager->getPlayer()->setHorizontalMovement(NONE);
            }
            break;
        case sf::Keyboard::S:
            break;
        case sf::Keyboard::D:
            this->rightHeld = false;
            if (leftHeld) {
                this->entityManager->getPlayer()->setHorizontalMovement(LEFT);
            }
            else {
                this->entityManager->getPlayer()->setHorizontalMovement(NONE);
            }
            break;
        }
        break;
    }
}


bool GameManager::isNextBuffReached(int score) {
	if (this->pointsToHpUp.size() != 0 && score >= this->pointsToHpUp.at(0)) {
		this->pointsToHpUp.erase(this->pointsToHpUp.begin());
		return true;
	}
	return false;
}

Level* GameManager::getLevel() {
	return this->level;
}

Camera* GameManager::getCamera() {
    return this->camera;
}

SoundManager* GameManager::getSoundManager() {
    return this->soundManager;
}

EntityManager* GameManager::getEntityManager() {
    return this->entityManager;
}