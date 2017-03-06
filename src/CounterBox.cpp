#include "CounterBox.h"

CounterBox::CounterBox(int steps) {
	step_limit = steps;
}
void CounterBox::increment() {
	counter++;
}
bool CounterBox::maxed() {
	return counter >= step_limit;
}
