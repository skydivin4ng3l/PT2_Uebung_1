#include <iostream>
#include <cstring>
#include <ctime>
#include <random>
#include "bitmap_image.hpp"

// random number in [0,1] range
inline float frand() {
	return (float)rand() / (float)RAND_MAX;
}

struct Raster {
	Raster(int w, int h) : width(w), height(h)
	{
		data = new int[width*height];
	}

	Raster(int w, int h, float seedProbability) : width(w), height(h)
	{
		data = new int[width*height];
		memset(data,0,sizeof(*data)*width*height);	//Maybe not necessary on each computer but sometimes trouble without
		// Todo 4.1a: Fill randomly
		// Probability of value 1 is seedProbability, otherwise value is 0

		for(int i = 0; i<width*height; i++){
			data[i]=(frand()<=seedProbability)? 1 : 0;
		}

		//Idea via shuffeling but, amount is not really random
		// static std::random_device rd;
		// static std::mt19937 g(rd());
		//
		// int amountLiving = (int)(seedProbability * (float)(width * height));
		// for(int i=0; i < amountLiving; i++){
		// 	data[i]=1;
		// }
		//
		// std::shuffle(&data[0],&data[(width*height)-1],g);

	}

	Raster(const std::string &filename)
	{
		bitmap_image image(filename);

		if (!image)
		{
			std::cerr << "Could not open bitmap!" << std::endl;
		}

		height = image.height();
		width = image.width();

		data = new int[width*height];

		// Todo 4.1a: Load image by using image.get_pixel
		// A black pixel represents 1, all other values represent 0

		for (int w = 0; w < width; w++) {
			for (int h = 0; h < height; h++){
				unsigned char red;
				unsigned char green;
				unsigned char blue;

				image.get_pixel(w,h,red,green,blue);

				if (red && green && blue) //Not one is 0 -> can't be black
					data[h*width+w] = 0;
				else
					data[h*width+w] = 1;

			}
		}
	}

	void save(const std::string &filename)
	{
		// Todo 4.1a: Save image by using image.set_pixel
		// Living cells should be stored as black pixels, all other pixels are white
		bitmap_image image(width, height);

		for (int w=0; w < width; w++){
			for (int h=0; h < height; h++){

				if (data[h*width+w])
					image.set_pixel(w,h,0,0,0);
				else
					image.set_pixel(w,h,255,255,255);

			}
		}

		image.save_image(filename);
	}

	~Raster()
	{
		delete[] data;
	}

	int width;
	int height;
	int* data;
};

// This struct parses all necessary command line parameters. It is already complete and doesn't have to be modified. However - feel free to add support for additional arguments if you like.
struct CommandLineParameter
{
	CommandLineParameter(int argc, char* argv[])
		: width(0)
		, height(0)
		, invasionFactor(0)
		, isTorus(false)
		, maxIterations(20)
	{
		if (argc % 2 == 0)
		{
			std::cerr << "Missing value for " << argv[argc - 1] << std::endl;
			argc--;
		}

		for (int i = 1; i < argc; i += 2)
		{
			if (!strcmp(argv[i], "-w"))
			{
				width = atoi(argv[i + 1]);
			}
			else if (!strcmp(argv[i], "-h"))
			{
				height = atoi(argv[i + 1]);
			}
			else if (!strcmp(argv[i], "-s"))
			{
				seedProbability = static_cast<float>(atof(argv[i + 1]));
			}
			else if (!strcmp(argv[i], "-p"))
			{
				patternFilename = argv[i + 1];
			}
			else if (!strcmp(argv[i], "-o"))
			{
				outputDirectory = argv[i + 1];
			}
			else if (!strcmp(argv[i], "-iv"))
			{
				invasionFactor = static_cast<float>(atof(argv[i + 1]));
			}
			else if (!strcmp(argv[i], "-t"))
			{
				isTorus = strcmp(argv[i + 1], "0") != 0;
			}
			else if (!strcmp(argv[i], "-i"))
			{
				maxIterations = atoi(argv[i + 1]);
			}
		}

		if ((width != 0 || height != 0) && !patternFilename.empty())
		{
			std::cout << "Width and height are ignored, because pattern is defined." << std::endl;
		}

		if (width < 0 || height < 0)
		{
			std::cerr << "Width or height has a invalid value." << std::endl;
			width = 0;
			height = 0;
		}
	}

	int width;
	int height;
	float seedProbability;
	std::string patternFilename;
	std::string outputDirectory;
	float invasionFactor;
	bool isTorus;
	int maxIterations;
};

int isAlive(const Raster &raster, int w, int h, bool isTorus){
	if(isTorus){
		w = w % raster.width;
		h = h % raster.height;

		if (w<0)
			w = w + raster.width;
		if (h<0)
			h = h + raster.height;
	}
	else if(w<0 || w>=raster.width || h<0 || h>=raster.height)
		return 0;

	return raster.data[h*raster.width+w];
}

int neighborValue(const Raster &raster, int x, int y, bool isTorus)
{
	// Todo 4.1b: Return number of living neighbors.
	// In case isTorus is false and (x, y) is outside of raster, return 0
	// In case isTorus is true and (x, y) is outside of raster use value of matching cell of opposite side

	int count = 0;

	for(int h=y-1; h<=y+1; h++){
		for(int w=x-1; w<=x+1; w++){

			if(!(w==x && h==y)){ //don't look at the cell itself
				count+= isAlive(raster, w, h, isTorus);
			}
		//	std::cout << "w " << w << " h " << h << " count " << count << std::endl;
		}
	}

	return count;
}

void simulateInvasion(Raster &raster, float invasionFactor)
{
	if (invasionFactor <= 0)
	{
		return;
	}

	// Todo 4.1c: Flip random some cells (probability to flip for each cell is invasionFactor)

	for(int i = 0; i<raster.width*raster.height; i++){
		if(frand() <= invasionFactor)
			raster.data[i] = !raster.data[i] ;

	}
}

void simulateNextState(Raster &raster, bool isTorus)
{
	// Todo 4.1b: Play one iteration of Game of Life
	// for(int h=0; h<raster.height; h++){
	// 	for(int w=0;w<raster.width; w++){
	// 		std::cout << raster.data[h*raster.width+w] << " ";
	// 	}
	// 	std::cout << std::endl;
	// }


	int newData[raster.width*raster.height];
	std::memcpy(&newData, raster.data, sizeof(newData));

	for(int h=0; h<raster.height; h++){
		for(int w=0;w<raster.width; w++){

			int count = neighborValue(raster, w, h, isTorus);
			int current = h*raster.width+w;

			if ((count == 2 || count == 3) && raster.data[current]==1)
				newData[current]=1;
			else
				newData[current]=0;

			if (raster.data[current]==0 && count==3)
				newData[current]=1;

		}
	}

	std::memcpy(raster.data, &newData, sizeof(newData));

}

int main(int argc, char* argv[])
{
	Raster* raster = nullptr;

	// Todo 4.1a: Initialize random seed
	srand(static_cast<unsigned int>(time(0)));
	srand(time(NULL));


	CommandLineParameter cmd(argc, argv);
	if (!cmd.patternFilename.empty())
	{
		raster = new Raster(cmd.patternFilename);
	}
	else
	{
		raster = new Raster(cmd.width, cmd.height, cmd.seedProbability);
	}

	for (int iteration = 0; iteration <= cmd.maxIterations; iteration++)
	{
		raster->save(cmd.outputDirectory + "game_of_life_" + std::to_string(iteration) + ".bmp");
		simulateInvasion(*raster, cmd.invasionFactor);
		simulateNextState(*raster, cmd.isTorus);
	}

	delete raster;

	return 0;
}
