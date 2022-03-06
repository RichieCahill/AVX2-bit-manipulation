#include <iostream>
#include <immintrin.h>
#include <fstream>
#include <string>
#include <vector>
#include <thread>

#include"AVX-bit-manipulation.h"
#include"Benchmark.h"

using namespace std;

const string output = "/dev/null";

void test(char num, uint64_t total){


	string time1 = "/mnt/temp/time1_";
	time1 += num;
	string time2 = "/mnt/temp/time2_";
	time2 += num;
	string time3 = "/mnt/temp/time3_";
	time3 += num;


	ofstream Time1(time1);
	string test = CBenchmark::benchmark("helper1",total,[](){
	__m256i temp = _mm256_set_epi64x(0, 0, 0, 1ull);
	temp = _mm256_lls_mm256_helper1(temp,17);
	__asm__ ( " " );
	});
	Time1 << test;
	Time1.close();

	ofstream Time2(time2);
	test = CBenchmark::benchmark("helper2",total,[](){
	__m256i temp = _mm256_set_epi64x(0, 0, 0, 1ull);
	temp = _mm256_lls_mm256_helper2(temp,17);
	__asm__ ( " " );
	});
	Time2 << test;
	Time2.close();

	ofstream Time3(time3);
	test = CBenchmark::benchmark("small",total,[](){
	__m256i temp = _mm256_set_epi64x(0, 0, 0, 1ull);
	temp = _mm256_lls_mm256_Small(temp,17);
	__asm__ ( " " );
	});
	Time3 << test;
	Time3.close();
}





int main(int argc, char const *argv[]){

	uint64_t num=100, total=1000000000;

	string time1 = "/mnt/temp/time1_";
	time1 += num;
	string time2 = "/mnt/temp/time2_";
	time2 += num;
	string time3 = "/mnt/temp/time3_";
	time3 += num;
	string time4 = "/mnt/temp/time4_";
	time3 += num;

	ofstream Time1(time1);
	string temp1 = CBenchmark::benchmark("helper1",total,[](){
	__m256i temp = _mm256_set_epi64x(0, 0, 0, 1ull);
	temp = _mm256_lls_mm256_helper1(temp,17);
	__asm__ ( " " );
	});
	Time1 << temp1;
	Time1.close();

	ofstream Time2(time2);
	temp1 = CBenchmark::benchmark("helper2",total,[](){
	__m256i temp = _mm256_set_epi64x(0, 0, 0, 1ull);
	temp = _mm256_lls_mm256_helper2(temp,17);
	__asm__ ( " " );
	});
	Time2 << temp1;
	Time2.close();

	ofstream Time3(time3);
	temp1 = CBenchmark::benchmark("helper3",total,[](){
	__m256i temp = _mm256_set_epi64x(0, 0, 0, 1ull);
	temp = _mm256_lls_mm256_helper3(temp,17);
	__asm__ ( " " );
	});
	Time3 << temp1;
	Time3.close();


	ofstream Time4(time4);
	temp1 = CBenchmark::benchmark("small",total,[](){
	__m256i temp = _mm256_set_epi64x(0, 0, 0, 1ull);
	temp = _mm256_lls_mm256_Small(temp,17);
	__asm__ ( " " );
	});
	Time4 << temp1;
	Time4.close();
	// const auto processor_count = thread::hardware_concurrency();

	// vector<thread> t;

	//creat threads till the processor_count
	//alice helped with the for loop that create the threads
	// test('c', 1000000000);
	// for(int i = 0; i < processor_count; i++){
		// char c = i+65;
		// t.emplace_back(test, c, 1000000000);
	// }

	// for(auto&& e: t){
  	// e.join();
	// } 

	return 0;
}

