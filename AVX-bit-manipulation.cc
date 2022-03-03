#include <iostream>
#include <immintrin.h>

/*
It Takes about 20 clock cycles to lefts shift

TODO
make this into a library

add
Logical Right Shift
Rotate Right
128 bit Suport

Make this code self testing
use git hub action
*/


// Logical left shift for a avx 256bit register
__m256i _mm256_sll_mm256  (__m256i n, int64_t s){
	//creats a temp __m256i  masked with the last s bits form rail 2 1 0 and seth them to the first bits in rail 3 2 1
	__m256i temp;

	uint64_t rail2 = _mm256_extract_epi64(n, 2), rail1 = _mm256_extract_epi64(n, 1), rail0 = _mm256_extract_epi64(n, 0);

	rail2 = rail2 >> (64-s);
	rail1 = rail1 >> (64-s);
	rail0 = rail0 >> (64-s);

	temp = _mm256_set_epi64x(rail2, rail1, rail0, 0X0000000000000000);

	// left shit the 4 64 bit ins in n then or with temp
	n = n << s;
	n = _mm256_or_si256(n, temp);
	return n;
}


// Logical left shift for a avx 256bit register
// Is faster if leftshifting 8 a lot
__m256i _mm256_sll_mm256_8x (__m256i n, int s){
	__m256i temp;

	//specal case for 8 that faster by 3 to 5 clock cycles
	//masks temp with the last s bits form rail 1 and seth them to the first bits in rail 2
	if (s==8){
		uint64_t rail1 = _mm256_extract_epi64(n, 1);

		rail1 = rail1 >> (64-s);

		temp = _mm256_set_epi64x(0X0000000000000000, rail1, 0X0000000000000000, 0X0000000000000000);

		n = _mm256_or_si256(_mm256_slli_si256(n,1), temp);

		return n;
	}

	//masks temp with the last s bits form rail 2 1 0 and seth them to the first bits in rail 3 2 1
	uint64_t rail2 = _mm256_extract_epi64(n, 2), rail1 = _mm256_extract_epi64(n, 1), rail0 = _mm256_extract_epi64(n, 0);

	rail2 = rail2 >> (64-s);
	rail1 = rail1 >> (64-s);
	rail0 = rail0 >> (64-s);


	temp = _mm256_set_epi64x(rail2, rail1, rail0, 0X0000000000000000);

	// left shit the 4 64 bit ins in n then or with temp
	n = n << s;
	n = _mm256_or_si256(n, temp);
	return n;
}

// Logical left shift for a avx 256bit register
//Uses 1 less 64 bit register
__m256i _mm256_sll_mm256_Small (__m256i n, int64_t s){
		//creates a temp __m256i  masked with the last s bits form rail 2 1 0 and seth them to the first bits in rail 3 2 1
	__m256i temp;
	__m128i t128_0, t128_1;
	uint64_t t64_0, t64_1;

	//pulls the avx register apart and left shits stor the out put in a __m128i
	t128_0 =	_mm256_extracti128_si256(n, 0);
	t64_0 = _mm_extract_epi64(t128_0, 0);
	t64_0 = t64_0>> (64-s);
	t64_1 = _mm_extract_epi64(t128_0, 1);
	t64_1 = t64_1>> (64-s);
	t128_0 = _mm_set_epi64x(t64_0, 0X0000000000000000);
	t128_1 = _mm256_extracti128_si256(n, 1);
	t64_0 = _mm_extract_epi64(t128_1, 0);
	t64_0 = t64_0>> (64-s);
	t128_1	= _mm_set_epi64x(t64_0, t64_1);

	//combins the 2 __m128i into a __m256i
	temp = _mm256_set_m128i(t128_1, t128_0);

	// left shit the 4 64 bit ins in n then or with temp
	n = n << s;
	n = _mm256_or_si256(n, temp);
	return n;
}

// Rotate left for a avx 256bit register
__m256i _mm256_rotl (__m256i n, int64_t s){

	//creats a temp __m256i  masked with the last s bits form rail 3 2 1 0 and seth them to the first bits in rail 3 2 1 0
	__m256i temp;
	uint64_t rail3 = _mm256_extract_epi64(n, 3), rail2 = _mm256_extract_epi64(n, 2), rail1 = _mm256_extract_epi64(n, 1), rail0 = _mm256_extract_epi64(n, 0);

	rail3 = rail3 >> (64-s);
	rail2 = rail2 >> (64-s);
	rail1 = rail1 >> (64-s);
	rail0 = rail0 >> (64-s);

	temp = _mm256_set_epi64x(rail2, rail1, rail0, rail3);

	// left shit the 4 64 bit ins in n then or with temp
	n = n << s;
	n = _mm256_or_si256(n, temp);
	return n;
}


int main(int argc, char const *argv[]){

	return 0;
}
