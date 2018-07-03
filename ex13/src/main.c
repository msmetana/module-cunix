#include "filler.h"

int         main()
{
	filler_t  filler;

  create_filler(&filler);
	start_game(&filler);
	destroy_filler(&filler);

	return 0;
}
