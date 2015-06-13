/* State machine with 2 event and 2 state.
 *   reference: http://johnsantic.com/comp/state.html
 */

#include <stdio.h>
#include <stdlib.h>

typedef void (state_machine) (void);

enum state {
	STATE_1,
	STATE_2,
	MAX_STATE
}current_state;

enum events {
	EVENT_1,
	EVENT_2,
	MAX_EVENT
}current_event;


void state1_event1 (void) {
	printf ("state1_event1 called...\n");
}

void state1_event2 (void) {
	printf ("state1_event2 called...\n");
}

void state2_event1 (void) {
	printf ("state2_event1 called...\n");
}

void state2_event2 (void) {
	printf ("state2_event2 called...\n");
}

static state_machine *
state_machine_call[MAX_STATE][MAX_EVENT] = {
	{state1_event1, state1_event2},
	{state2_event1, state2_event2},
};


int main ()
{
	state_machine   *call = NULL;
	
	printf ("state machine begins...\n");


	call = state_machine_call[STATE_1][EVENT_1];

	call ();
	
	call = state_machine_call[STATE_1][EVENT_2];

	call ();
	
	
	return 0;
}
