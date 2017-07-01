
#include <cassert>
#include <iostream>
#include <string>
#include <cstddef>
#include <vector>
#include <cstring>
#include <cmath>

#define SPACE ' '
#define FILL '#'

static const auto N = 4;
static const auto tower_width = N * 2 + 3;
static const auto tower_height = N * 2;

auto A = std::vector<int>();
auto B = std::vector<int>();
auto C = std::vector<int>();

void print_tower_row(int disc_size = 0, char mid_fill = FILL, char side_fill = SPACE)
{
	std::cout << std::string(tower_width / 2 - disc_size, side_fill);
	//disc row
	if (disc_size > 0)	{
		//base special case
		if (mid_fill != FILL) {
			std::cout << std::string(disc_size, SPACE) << mid_fill << std::string(disc_size, SPACE);
		}
		else {
			std::cout << std::string(disc_size * 2 + 1, mid_fill);
		}
	}
	//space row
	else {
		std::cout << mid_fill;
	}
	std::cout << std::string(tower_width / 2 - disc_size + 1, side_fill);
}

void print()
{
	#ifdef _WIN32
	std::system("cls");
	#else
	std::system("clear");
	#endif

	// Todo 5.2: Print current state

	std::vector<std::vector<int>> towers_container = { A,B,C };

	//copied tower containers filled with zeros up to size N for better print handeling
	for (auto &current_tower : towers_container)
	{
		while (current_tower.size() < N)
		{
			current_tower.push_back(0);
		}
	}

	//Tower body
	for (int row = 0; row <= tower_height; row++)
	{
		bool is_disc_row = row % 2;
		for (auto &current_tower : towers_container)
		{
			// empty spacer row
			if (!is_disc_row)
			{
				print_tower_row();
			}
			// disc slot specified row
			else if (is_disc_row)
			{
				int disc_size = current_tower.back();
				current_tower.pop_back();
				print_tower_row(disc_size);
			}
		}
		std::cout << std::endl;
	}

	//Tower base
	std::cout << std::string((tower_width + 1) *3, FILL) << std::endl;
	//Tower signatur
	print_tower_row(1, 'A', '#');
	print_tower_row(1, 'B', '#');
	print_tower_row(1, 'C', '#');

	std::cout << std::endl << std::endl;
}

void ToH(const int n, const int a, const int b, const int c, int & moves)
{
	static std::vector<int>* towers[] = { &A,&B,&C };
	// Todo 5.2: Implement ToH and print
	if (n == 1)
	{
		// move disc from a directly to c (no auxiliary stack required)
		//std::cout << "Move " << (char)(’A’ + a) << "->" << (char)(’A’ + c) << std::endl;
		towers[c]->push_back(towers[a]->back());
		towers[a]->pop_back();
		moves++;
		print();
		getchar();
		
	}
	else
	{
		ToH(n - 1, a, c, b, moves); // move n-1 stack of a to stack b
		ToH(1, a, b, c, moves);   // move remaining disc of a to c
		ToH(n - 1, b, a, c, moves); // move n-1 stack b to stack c
	}
}

int main(int argc, char ** argv)
{
	int moves = 0;

	for (int i = N; i > 0; --i)
		A.push_back(i);

	print();
	getchar();
	ToH(N, 0, 1, 2, moves);
	std::cout << "minimal number of moves: " << moves << std::endl;

	getchar();
	return 0;
}
