/*
 * This code merely reduces the overhead that accompanies
 * the creation of a bunch of iterators in a state machine.
 */
#ifndef SRC_COUNTERBOX_H_
#define SRC_COUNTERBOX_H_

class CounterBox {
public:
	CounterBox(int steps);
	int counter = 0;
	int step_limit = 0;
	void increment();
	bool maxed();
};

#endif /* SRC_COUNTERBOX_H_ */
