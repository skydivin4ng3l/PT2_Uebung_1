
#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>
#include <string>


struct Interval
{
	Interval(const int i, const int start, const int length)
	: index(i)
	, start(start)
	, end(start + length - 1)
	{
	}

	int index;
	int start;
	int end;
};

const static int MaxEnd = 74;
const static int MaxDuration = 10;

const static int N = 20;

std::ostream & operator<<(std::ostream & os, const std::vector<Interval> & I)
{
	// Todo 5.3: Implement a nice print function
	//blocks
	char free_slot = '"';
	char blocked_slot = '#';

	for (auto current_interval : I)
	{
		std::string index = (current_interval.index < 10 ? std::to_string(current_interval.index) + " " 
														 : std::to_string(current_interval.index) );
		os << "Interval: " << index << " [";
		//until start
		for (int slot = 0; slot < current_interval.start; slot++)
		{
			os << free_slot;
		}

		//until end
		for (int slot = current_interval.start; slot < current_interval.end; slot++)
		{
			os << blocked_slot;
		}

		//until MaxEnd
		for (int slot = current_interval.end; slot < MaxEnd; slot++)
		{
			os << free_slot;
		}

		os << "]" << std::endl;
	}
	os << I.size() << std::endl;
	return os;
}

// creates random data
void randomize(std::vector<Interval> & intervals)
{
	intervals.clear();
	srand(static_cast<unsigned int>(time(0)));

	for (int i = 0; i < N; i++)
	{
		int duration = rand() % MaxDuration + 1;
		int start = rand() % (MaxEnd - duration + 2);

		intervals.push_back(Interval(i, start, duration));
	}
}

void schedule(const std::vector<Interval> & intervals)
{
	std::cout << std::endl << "intervals (randomized):" << std::endl << intervals;


	// Todo 5.3: Sort intervals
	auto sorted = intervals;
	std::sort(sorted.begin(), sorted.end(), [](Interval& first_interval, Interval& second_interval) {return first_interval.end < second_interval.end; });

	std::cout << std::endl << "intervals (sorted):" << std::endl << sorted;

	// Todo 5.3: Implement greedy scheduling
	auto scheduled = std::vector<Interval>();

	//add the interval with the earliest end time, first interval of sorted will be added anyway
	Interval last_added_interval = sorted.front();
	sorted.push_back(sorted.front());

	for (auto current_interval :sorted)
	{
		// then check for other valid intervals and skip first
		if (current_interval.start > last_added_interval.end)
		{
			scheduled.push_back(current_interval);
			last_added_interval = current_interval;
		}
	}

	std::cout << std::endl << "intervals (scheduled, " << scheduled.size() << " of " << sorted.size() << " possible)"
		<< std::endl << scheduled << std::endl;
}

int main(int argc, char** argv) {

	auto intervals = std::vector<Interval>();

	randomize(intervals);
	schedule(intervals);

	return 0;
}
