#include <vector>
#include <random>
#include <chrono>

class MyRandom
{

	public:

		uint64_t timeSeed;
		std::mt19937_64 range;
	
		double randomVar;

	public:

		MyRandom()
		{}


		int GetRandom01() 
		{
			std::seed_seq ss{ uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
			timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
			range.seed(ss);
			std::uniform_real_distribution<double> unif(0, 1);
			randomVar = unif(range);

			if (randomVar >= 0.5) return 1;
			else return 0;
		}

	
};