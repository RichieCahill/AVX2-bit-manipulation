#include <iostream>
#include <immintrin.h>
#include <fstream>
#include <string>
#include <vector>
#include <thread>

#include"AVX-bit-manipulation.h"

using namespace std;

const string output = "/dev/null";

void test(char num, uint64_t total){
		// 
		// cout << c << endl;
		// file += c;
	ofstream Output(output, ios::out | ios::binary);

string time1 = "/mnt/temp/time1_";
time1 += num;
string time2 = "/mnt/temp/time2_";
time2 += num;
string time3 = "/mnt/temp/time3_";
time3 += num;


	ofstream Time1(time1);
	for (uint64_t j = 0; j < 100; j++){
	}
	clock_t t0 = clock();
	for (uint64_t i = 0; i < total; i++){
		__m256i 	temp = _mm256_set_epi64x(0, 0, 0, 1ull);
  	temp = _mm256_lls_mm256_helper1(temp,17);
		Output.write ((char*)&temp, sizeof (temp));
	}
	clock_t t1 = clock();
  Time1 << (t1-t0) * 1e-6 << '\n';	/* code */
	Time1.close();

	ofstream Time2(time2);
	t0 = clock();
	for (uint64_t i = 0; i < total; i++){
		__m256i 	temp = _mm256_set_epi64x(0, 0, 0, 1ull);
  	temp = _mm256_lls_mm256_helper2(temp,17);
		Output.write ((char*)&temp, sizeof (temp));
	}
	t1 = clock();
  Time2 << (t1-t0) * 1e-6 << '\n';	/* code */
	Time2.close();

	ofstream Time3(time3);
	t0 = clock();
	for (uint64_t i = 0; i < total; i++){
		__m256i 	temp = _mm256_set_epi64x(0, 0, 0, 1ull);
  	temp = _mm256_lls_mm256_Small(temp,17);
		Output.write ((char*)&temp, sizeof (temp));
	}
	t1 = clock();
  Time3 << (t1-t0) * 1e-6 << '\n';	/* code */
	Time3.close();


Output.close();
}





int main(int argc, char const *argv[]){

	// const auto processor_count = thread::hardware_concurrency();
	constexpr uint64_t processor_count = 12;



	vector<thread> t;

	//creat threads till the processor_count
	//alice helped with the for loop that create the threads
	for(int i = 0; i < processor_count; i++){
		char c = i+65;
		test(c, 10000000);
	}
	
	
	
	
	
	
	


	return 0;
}

