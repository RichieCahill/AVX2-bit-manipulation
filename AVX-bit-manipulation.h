#include <iostream>
#include <immintrin.h>

/*
It Takes about 20 clock cycles to lefts shift
And only can shift 64 bits

TODO
add
128 bit Suport

Make this code self testing
use git hub action
*/

void avxout(__m256i a){
std::cout << std::hex << _mm256_extract_epi64(a, 3) << std::endl;
std::cout << std::hex << _mm256_extract_epi64(a, 2) << std::endl;
std::cout << std::hex << _mm256_extract_epi64(a, 1) << std::endl;
std::cout << std::hex << _mm256_extract_epi64(a, 0) << std::endl;
std::cout << endl;
}


// Logical left shift upto 64 bit for a avx 256bit register
__m256i _mm256_lls_mm256_helper  (__m256i n, int64_t s){
	if (s==0)
		return n;
	//creats a temp __m256i  masked with the last s bits form rail 2 1 0 and seth them to the first bits in rail 3 2 1
	__m256i temp;

	uint64_t rail2 = _mm256_extract_epi64(n, 2), rail1 = _mm256_extract_epi64(n, 1), rail0 = _mm256_extract_epi64(n, 0);

	rail2 = rail2 >> (64-s);
	rail1 = rail1 >> (64-s);
	rail0 = rail0 >> (64-s);
	temp = _mm256_set_epi64x(rail2, rail1, rail0, 0);

	// left shifts the 4 64 bit ins in n then or with temp
	n = n << s;
	n = _mm256_or_si256(n, temp);
	return n;
}

// Logical left shift by 64 for a avx 256bit register
__m256i _mm256_lls_64(__m256i n){
	uint64_t rail2 = _mm256_extract_epi64(n, 2), rail1 = _mm256_extract_epi64(n, 1), rail0 = _mm256_extract_epi64(n, 0);
	return n = _mm256_set_epi64x(rail2, rail1, rail0, 0);
}

// Logical left shift by 128 for a avx 256bit register
__m256i _mm256_lls_128(__m256i n){
	uint64_t rail1 = _mm256_extract_epi64(n, 1), rail0 = _mm256_extract_epi64(n, 0);
	return n = _mm256_set_epi64x(rail1, rail0, 0, 0);
}

// Logical left shift by 192 for a avx 256bit register
__m256i _mm256_lls_192(__m256i n){
	uint64_t rail0 = _mm256_extract_epi64(n, 0);
	return n = _mm256_set_epi64x(rail0, 0, 0, 0);
}


// Logical left shift for a avx 256bit register
// it combines the larger shift _mm256_lls_* with the _mm256_lls_mm256_helper todo the final s bits
__m256i _mm256_lls_mm256(__m256i n, int64_t s){
	if (s==0)
		return n;
	if (s<=64) {
		n = _mm256_lls_mm256_helper(n,s);
		return n;
	} else if (s<=128){
		n = _mm256_lls_64(n);
		n = _mm256_lls_mm256_helper(n,s-64);
		return n;
	}	else if (s<=192){
		n = _mm256_lls_128(n);
		n = _mm256_lls_mm256_helper(n,s-128);
		return n;
	} else if (s<=256){
		n = _mm256_lls_192(n);
		n = _mm256_lls_mm256_helper(n,s-192);
		return n;
	} else if (s>256)
		return n = _mm256_setzero_si256();;
	return n = _mm256_set_epi64x(0, 0, 0, 9ULL);
}

// Logical left shift for a avx 256bit register
//Uses 1 less 64 bit register
__m256i _mm256_lls_mm256_Small (__m256i n, int64_t s){
	if (s==0)
		return n;
	if (s>64)
		return n = _mm256_setzero_si256();;
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
	t128_0 = _mm_set_epi64x(t64_0, 0);
	t128_1 = _mm256_extracti128_si256(n, 1);
	t64_0 = _mm_extract_epi64(t128_1, 0);
	t64_0 = t64_0>> (64-s);
	t128_1	= _mm_set_epi64x(t64_0, t64_1);

	//combins the 2 __m128i into a __m256i
	temp = _mm256_set_m128i(t128_1, t128_0);

	// left shifts the 4 64 bit ins in n then or with temp
	n = n << s;
	n = _mm256_or_si256(n, temp);
	return n;
}

// Rotate left for a avx 256bit register
__m256i _mm256_rotl (__m256i n, int64_t s){
	if (s==0)
		return n;
	//creats a temp __m256i  masked with the last s bits form rail 3 2 1 0 and seth them to the first bits in rail 3 2 1 0
	__m256i temp, temp2;
	uint64_t rail3 = _mm256_extract_epi64(n, 3), rail2 = _mm256_extract_epi64(n, 2), rail1 = _mm256_extract_epi64(n, 1), rail0 = _mm256_extract_epi64(n, 0);

	rail3 = rail3 >> (64-s);
	rail2 = rail2 >> (64-s);
	rail1 = rail1 >> (64-s);
	rail0 = rail0 >> (64-s);

	temp = _mm256_set_epi64x(rail2, rail1, rail0, rail3);

	// left shifts the 4 64 bit ins in n then or with temp
	n = n << s;
	n = _mm256_or_si256(n, temp);
	return n;
}

	// Logical right shift upto 64 bit for a avx 256bit register
	// this is a siple optimization the reduse the number of avx registers
	// but it less readable
__m256i _mm256_lrs_mm256_helper2  (__m256i n, int64_t s){
	if (s==0)
		return n;
	if (s>64)
		return n = _mm256_setzero_si256();
	//creats a temp __m256i  masked with the first s bits form rail 3 2 1 and seth them to the last bits in rail 2 1
	__m256i  temp;

	uint64_t rail3 = _mm256_extract_epi64(n, 3), rail2 = _mm256_extract_epi64(n, 2), rail1 = _mm256_extract_epi64(n, 1);

	rail3 = rail3 << (64-s);
	rail2 = rail2 << (64-s);
	rail1 = rail1 << (64-s);
	
	// right shifts the 4 64 bit ins in n then or with temp
	temp = _mm256_set_epi64x(s, s, s, s);
	n = _mm256_srlv_epi64 (n , temp);
	
	temp = _mm256_set_epi64x( 0, rail3, rail2, rail1);

	n = _mm256_or_si256(n, temp);
	return n;
}


	// Logical right shift upto 64 bit for a avx 256bit register
__m256i _mm256_lrs_mm256_helper  (__m256i n, int64_t s){
	if (s==0)
		return n;
	if (s>64)
		return n = _mm256_setzero_si256();
	//creats a temp __m256i  masked with the first s bits form rail 3 2 1 and seth them to the last bits in rail 2 1
	__m256i  temp, temp2;

	uint64_t rail3 = _mm256_extract_epi64(n, 3), rail2 = _mm256_extract_epi64(n, 2), rail1 = _mm256_extract_epi64(n, 1);

	rail3 = rail3 << (64-s);
	rail2 = rail2 << (64-s);
	rail1 = rail1 << (64-s);
	
	temp = _mm256_set_epi64x( 0, rail3, rail2, rail1);

	// right shifts the 4 64 bit ins in n then or with temp
	temp2 = _mm256_set_epi64x(s, s, s, s);
	n = _mm256_srlv_epi64 (n , temp2);

	n = _mm256_or_si256(n, temp);
	return n;
}

// Logical Right shift by 64 for a avx 256bit register
__m256i _mm256_lrs_64(__m256i n){
	uint64_t rail3 = _mm256_extract_epi64(n, 3), rail2 = _mm256_extract_epi64(n, 2), rail1 = _mm256_extract_epi64(n, 1);
	return n = _mm256_set_epi64x(0, rail3, rail2, rail1);
}

// Logical Right shift by 128 for a avx 256bit register
__m256i _mm256_lrs_128(__m256i n){
	uint64_t rail3 = _mm256_extract_epi64(n, 3), rail2 = _mm256_extract_epi64(n, 2);
	return n = _mm256_set_epi64x(0, 0, rail3, rail2);
}

// Logical Right shift by 192 for a avx 256bit register
__m256i _mm256_lrs_192(__m256i n){
	uint64_t rail3 = _mm256_extract_epi64(n, 3);
	return n = _mm256_set_epi64x(0, 0, 0, rail3);
}


// Logical Right shift for a avx 256bit register
// it combines the larger shift _mm256_lrs_* with the _mm256_lrs_mm256_helper todo the final s bits
__m256i _mm256_lrs_mm256(__m256i n, int64_t s){
	if (s==0)
		return n;
	if (s<=64) {
		n = _mm256_lrs_mm256_helper(n,s);
		return n;
	} else if (s<=128){
		n = _mm256_lrs_64(n);
		n = _mm256_lrs_mm256_helper(n,s-64);
		return n;
	}	else if (s<=192){
		n = _mm256_lrs_128(n);
		n = _mm256_lrs_mm256_helper(n,s-128);
		return n;
	} else if (s<=256){
		n = _mm256_lrs_192(n);
		n = _mm256_lrs_mm256_helper(n,s-192);
		return n;
	} else if (s>256)
		return n = _mm256_setzero_si256();;
	return n = _mm256_set_epi64x(0, 0, 0, 9ULL);
}

// Rotate left for a avx 256bit register
__m256i _mm256_rotr (__m256i n, int64_t s){
	if (s==0)
		return n;
	if (s>64)
		return n = _mm256_setzero_si256();;
	//creats a temp __m256i  masked with the first s bits form rail 3 2 1 0 and seth them to the last bits in rail 3 2 1 0
	__m256i temp;
	uint64_t rail3 = _mm256_extract_epi64(n, 3), rail2 = _mm256_extract_epi64(n, 2), rail1 = _mm256_extract_epi64(n, 1), rail0 = _mm256_extract_epi64(n, 0);

	rail3 = rail3 << (64-s);
	rail2 = rail2 << (64-s);
	rail1 = rail1 << (64-s);
	rail0 = rail0 << (64-s);

	temp = _mm256_set_epi64x(rail0, rail3 ,rail2, rail1);

	// right shifts the 4 64 bit ins in n then or with temp
	n = n >> s;
	n = _mm256_or_si256(n, temp);
	return n;
}