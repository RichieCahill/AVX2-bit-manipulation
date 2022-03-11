#include <iostream>
#include <immintrin.h>
#include <random>

#include"./AVX-bit-manipulation.h"

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
  uniform_int_distribution<mt19937::result_type> dist65(0,64);

int main(int argc, char const *argv[]){

  // uint64_t total = 1000, avr=0;

  // for (uint64_t i = 0; i < total; i++){
	
  uint64_t shift=dist257(rng);
  
  clock_t t0 = clock();
  __m256i	temp = _mm256_lrs_mm256(_mm256_set_epi64x(0, 0, 0, 1ull),shift);  
	clock_t t1 = clock();
	// cout << (t1-t0) << endl;
  
  // avr+=(t1-t0);
  // __m256i	temp = _mm256_lls_mm256(_mm256_set_epi64x(0, 0, 0, 1ull),dist257(rng));
  // }
  // cout << avr << endl;
  // cout << avr/total << endl;
	return 0;
}

