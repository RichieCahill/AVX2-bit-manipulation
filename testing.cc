#include <iostream>
#include <immintrin.h>
#include <random>

#include"AVX-bit-manipulation.h"

// #include"Benchmark.h"
// #include <fstream>
// #include <string>
// #include <vector>
// #include <thread>


using namespace std;

const string output = "/dev/null";

  random_device dev;
  mt19937 rng(dev());
  uniform_int_distribution<mt19937::result_type> dist257(0,256);

int main(int argc, char const *argv[]){

for (size_t i = 0; i < 1000000000; i++){

__m256i	temp = _mm256_lls_mm256(_mm256_set_epi64x(0, 0, 0, 1ull),dist257(rng));
}

	return 0;
}

