
#include <cassert>
#include <iostream>
#include <string>
#include <cstddef>
#include <vector>
#include <cstring>
#include <cmath>


static const auto N = 4;

auto A = std::vector<int>();
auto B = std::vector<int>();
auto C = std::vector<int>();


void print()
{
	#ifdef _WIN32
	std::system("cls");
	#else
	std::system("clear");
	#endif

	// Todo 5.2: Print current state
	const auto tower_width = N * 2+3;
	const auto tower_height = N * 2;
	const char fill = '#';
	const char space = ' ';

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
	for (int row = 0; row < tower_height; row++)
	{
		bool is_disc_row = row % 2;
		for (auto &current_tower : towers_container)
		{
			// empty spacer row
			if (!is_disc_row)
			{
				std::cout << std::string(tower_width / 2, ' '); //TODO complete Refac
				std::cout << fill;
				std::cout << std::string(tower_width / 2 + 1, ' ');
			}
			// disc slot specified row
			else if (is_disc_row)
			{
				int disc_space = current_tower.back();
				current_tower.pop_back();
				//print space before the disc, compensate reversed order of discs
				for (int i = 0; i < tower_width/2-disc_space; i++)
				{
					std::cout << space;
				}
				//print disc
				for (int j = 0; j < disc_space*2+1; j++)
				{
					std::cout << fill;
				}
				//print space after the disc + seperator space
				for (int k = 0; k < tower_width / 2 - disc_space + 1; k++)
				{
					std::cout << space;
				}
			}
			//Tower base
			//TODO
		}
		std::cout << std::endl;
	}
	
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
