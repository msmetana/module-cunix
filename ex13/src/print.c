#include <stdio.h>
#include <stdlib.h>
#include "filler.h"

void print_pos(pos_t p)
{
	dprintf(1, "%d %d", p.x, p.y);
}
