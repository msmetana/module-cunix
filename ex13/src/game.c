#include <stdio.h>
#include <stdlib.h>
#include "filler.h"
#include "my_string.h"

void timeout_reset(struct timeval *timer)
{
	timer->tv_sec = 1;
	timer->tv_usec = 0;
}

void 			start_game(filler_t *filler)
{
	struct timeval 	timeout;
	req_t 		*req;
	fd_set 		rfds;
	fd_set 		wfds;
	pos_t 		p;
	int 		ret;

  req = (req_t*) malloc(sizeof(req_t));
	set_nonblocking(0);

	while(1){
		FD_ZERO(&rfds);
		FD_ZERO(&wfds);

		switch(filler->status){
			case 1:
				FD_SET(1, &wfds);
				break;
			case 0:
				FD_SET(0, &rfds);
				break;
		}
		timeout_reset(&timeout);

		ret = select(2, &rfds, &wfds, NULL, &timeout);

		if(ret < 0){
      //ERROR
		}

		if(FD_ISSET(0, &rfds)){
			req = read_request(filler);

			if(req != NULL){
				p = play(req);
				filler->status = 1;
			}
		}

		if(FD_ISSET(1, &wfds)){
			print_pos(p);

			filler->status = 0;
			string_destroy(filler->current_stream);
			filler->current_stream = NULL;
		}
	}

  free(req);
	req = NULL;
}

