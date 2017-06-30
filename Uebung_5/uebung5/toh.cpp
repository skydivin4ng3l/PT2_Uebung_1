
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
	const auto tower_width = N * 3;
	const auto tower_height = N * 2 + 2;
	const char fill = '#';
	const char space = ' ';

	const std::vector<std::vector<int>> towers_container = { A,B,C };

	//Tower body
	for (int row = 0; row < tower_height; row++)
	{
		bool is_vektor_row = row % 2;
		// empty spacer row
		if (!is_vektor_row)
		{
			for (int tower = 1; tower <= 3; tower++)
			{
				for (int i = 0; i < tower_width/2; i++)
				{
					std::cout << space;
				}
				std::cout << fill;
			}
			std::cout << std::endl;
		}
		// vektor specified row
		else if (is_vektor_row)
		{
			for (auto current_tower : towers_container)
			{
				//compensate reversed order of discs
				int tower_disc_count = current_tower.size();
				//print space before the disc
				for (int i = 0; i < tower_width/2-current_tower[tower_disc_count - 1 - (row - 1)]; i++)
				{
					std::cout << space;
				}
				//print disc
				for (int j = 0; j < current_tower[tower_disc_count - 1 - (row - 1)]*2+1; j++)
				{
					std::cout << fill;
				}
				//print space after the disc + seperator space
				for (int k = 0; k < tower_width / 2 - current_tower[tower_disc_count - 1 - (row - 1)]+1; k++)
				{
					std::cout << space;
				}
			}
			std::cout << std::endl;
		}
	}
	//Tower base
	//TODO
	std::cout << std::endl << std::endl;
}

void ToH(const int n, const int a, const int b, const int c, int & moves)
{
	// Todo 5.2: Implement ToH and print
	//if (n == 1)
	//{
	//	// move disc from a directly to c (no auxiliary stack required)
	//	//std::cout << "Move " << (char)(’A’ + a) << "->" << (char)(’A’ + c) << std::endl;
	//}
	//else
	//{
	//	ToH(n - 1, a, c, b); // move n-1 stack of a to stack b
	//	moves++;
	//	ToH(1, a, b, c);   // move remaining disc of a to c
	//	moves++;
	//	ToH(n - 1, b, a, c); // move n-1 stack b to stack c
	//	moves++;
	//}
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
