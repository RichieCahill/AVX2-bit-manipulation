#include <iostream>
#include <immintrin.h>

/*
It Takes about 20 clock cycles to lefts shift
*/

void avxout(__m256i a){
	std::cout << std::hex << _mm256_extract_epi64(a, 3) << "\n";
	std::cout << std::hex << _mm256_extract_epi64(a, 2) << "\n";
	std::cout << std::hex << _mm256_extract_epi64(a, 1) << "\n";
	std::cout << std::hex << _mm256_extract_epi64(a, 0) << "\n";
	std::cout << "\n";
}

/*
// Logical left shift upto 64 bit for a avx 256bit register
// this is hear to help explain with the new helper dose
// it's functionally the same thing but this isnt inlined
__m256i _mm256_lls_mm256_helper_old  (__m256i n, int32_t s){
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
*/

// Logical left shift upto 64 bit for a avx 256bit register 
__m256i _mm256_lls_mm256_helper_old  (__m256i n, int32_t s){
	if (s==0)
		return n;
	return _mm256_or_si256((n << s), _mm256_set_epi64x(((unsigned long long)_mm256_extract_epi64(n, 2) >> (64ull-s)), ((unsigned long long)_mm256_extract_epi64(n, 1) >> (64ull-s)), ((unsigned long long) _mm256_extract_epi64(n, 0) >> (64ull-s)), 0ull));
}

// Logical left shift upto 64 bit for a avx 256bit register 
// Must not be given a zero
__m256i _mm256_lls_mm256_helper  (__m256i n, int32_t s){
	return _mm256_or_si256((n << s), _mm256_set_epi64x(((unsigned long long)_mm256_extract_epi64(n, 2) >> (64ull-s)), ((unsigned long long)_mm256_extract_epi64(n, 1) >> (64ull-s)), ((unsigned long long) _mm256_extract_epi64(n, 0) >> (64ull-s)), 0ull));
}

// Logical left shift by 64 for a avx 256bit register
// this is hear to help explain with the new _mm256_lls_64 dose
// it's functionally the same thing but this isnt inlined
// __m256i _mm256_lls_64_old(__m256i n){
// 	uint64_t rail2 = _mm256_extract_epi64(n, 2), rail1 = _mm256_extract_epi64(n, 1), rail0 = _mm256_extract_epi64(n, 0);
// 	return n = _mm256_set_epi64x(rail2, rail1, rail0, 0);
// }

// Logical left shift by 64 for a avx 256bit register
__m256i _mm256_lls_64(__m256i n){
	return _mm256_set_epi64x(_mm256_extract_epi64(n, 2), _mm256_extract_epi64(n, 1), _mm256_extract_epi64(n, 0), 0);
}

// Logical left shift by 128 for a avx 256bit register
__m256i _mm256_lls_128(__m256i n){
	return _mm256_set_epi64x(_mm256_extract_epi64(n, 1), _mm256_extract_epi64(n, 0), 0, 0);
}

// Logical left shift by 128 for a avx 256bit register
__m256i _mm256_lls_128_test(__m256i n){
	return _mm256_set_m128i(_mm256_extracti128_si256(n, 0), _mm_setzero_si128 ());
}

// Logical left shift by 192 for a avx 256bit register
__m256i _mm256_lls_192(__m256i n){
	return _mm256_set_epi64x(_mm256_extract_epi64(n, 0), 0, 0, 0);
}


// Logical left shift for a avx 256bit register
// it combines the larger shift _mm256_lls_* with the _mm256_lls_mm256_helper todo the final s bits
__m256i _mm256_lls_mm256_old(__m256i n, int32_t s){
	if (s==0) {
		return n;
	} else if (s<0) {
	return n = _mm256_set_epi64x(0, 0, 0, 11ULL);
	} else if (s<=64) {
		return _mm256_lls_mm256_helper(n,s);
	} else if (s<=128){
		n = _mm256_lls_64(n);
		return _mm256_lls_mm256_helper(n,s-64);
	}	else if (s<=192){
		n = _mm256_lls_128(n);
		return _mm256_lls_mm256_helper(n,s-128);
	} else if (s<=256){
		n = _mm256_lls_192(n);
		return _mm256_lls_mm256_helper(n,s-192);
	} else if (s>256)
		return _mm256_setzero_si256();;
	return n = _mm256_set_epi64x(0, 0, 0, 9ULL);
}

// This may be a siney bit faster but i need to do mor testing
// Logical left shift for a avx 256bit register
// it combines the larger shift _mm256_lls_* with the _mm256_lls_mm256_helper todo the final s bits
__m256i _mm256_lls_mm256(__m256i n, int32_t s){
	if (s==0) {
		return n;
	} else if (s<0) {
		return _mm256_set_epi64x(0, 0, 0, 11ULL);
	} else if (s<64) {
		return _mm256_lls_mm256_helper(n,s);
	} else if (s==64) {
		return _mm256_lls_64(n);		
	} else if (s<128){
		return _mm256_lls_mm256_helper(_mm256_lls_64(n),s-64);
	}	else if (s==128) {
		return _mm256_lls_128(n);
	} else if (s<192){
		return _mm256_lls_mm256_helper(_mm256_lls_128(n),s-128);
	} else if (s==192) {
		return _mm256_lls_192(n);
	} else if (s<256){
		return _mm256_lls_mm256_helper(_mm256_lls_192(n),s-192);
	} else if (s>=256){
		return _mm256_setzero_si256();
	}	
	return n = _mm256_set_epi64x(0, 0, 0, 9ULL);
}

/*]
// Rotate left for a avx 256bit register
// this is hear to help explain with the new helper dose
// it's functionally the same thing but this isnt inlined
__m256i _mm256_rotl_mm256_old (__m256i n, int32_t s){
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
*/

//  Rotate left upto 64 bit for a avx 256bit register
__m256i _mm256_rotl_mm256_helper  (__m256i n, int32_t s){
	if (s==0)
		return n;
	return _mm256_or_si256((n << s), _mm256_set_epi64x(((unsigned long long)_mm256_extract_epi64(n, 2) >> (64ull-s)), ((unsigned long long)_mm256_extract_epi64(n, 1) >> (64ull-s)), ((unsigned long long) _mm256_extract_epi64(n, 0) >> (64ull-s)), ((unsigned long long)_mm256_extract_epi64(n, 3) >> (64ull-s))));
}

// Rotate left by 64 for a avx 256bit register
__m256i _mm256_rotl_64(__m256i n){
	return _mm256_set_epi64x(_mm256_extract_epi64(n, 2), _mm256_extract_epi64(n, 1), _mm256_extract_epi64(n, 0), _mm256_extract_epi64(n, 3));
}

// Rotate left by 128 for a avx 256bit register
__m256i _mm256_rotl_128(__m256i n){
	return _mm256_set_m128i(_mm256_extracti128_si256(n, 0), _mm256_extracti128_si256(n, 1));
}

// Rotate left by 192 for a avx 256bit register
__m256i _mm256_rotl_192(__m256i n){
	return _mm256_set_epi64x(_mm256_extract_epi64(n, 0), _mm256_extract_epi64(n, 3), _mm256_extract_epi64(n, 2), _mm256_extract_epi64(n, 1));
}

// this combines the larger shift _mm256_rotl_* with the _mm256_rotl_mm256_helper todo the final s bits
__m256i _mm256_rotl_mm256(__m256i n, int32_t s){
	if (s==0) {
		return n;
	} else if (s<0) {
	return n = _mm256_set_epi64x(0, 0, 0, 11ULL);
	} else if (s<=64) {
		return _mm256_rotl_mm256_helper(n,s);
	} else if (s<=128){
		n = _mm256_rotl_64(n);
		return _mm256_rotl_mm256_helper(n,s-64);
	}	else if (s<=192){
		n = _mm256_rotl_128(n);
		return _mm256_rotl_mm256_helper(n,s-128);
	} else if (s<=256){
		n = _mm256_rotl_192(n);
		return _mm256_rotl_mm256_helper(n,s-192);
	} else if (s>256)
		return _mm256_setzero_si256();;
	return n = _mm256_set_epi64x(0, 0, 0, 9ULL);
}

/*
// Logical right shift upto 64 bit for a avx 256bit register
// this is hear to help explain with the new helper dose
// it's functionally the same thing but this isnt inlined
__m256i _mm256_lrs_mm256_helper_old  (__m256i n, int32_t s){
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
*/

// Logical right shift upto 64 bit for a avx 256bit register
__m256i _mm256_lrs_mm256_helper  (__m256i n, int32_t s){
	if (s==0)
		return n;
	return  _mm256_or_si256(_mm256_srlv_epi64 (n , _mm256_set_epi64x(s, s, s, s)), _mm256_set_epi64x( 0, _mm256_extract_epi64(n, 3) << (64-s), _mm256_extract_epi64(n, 2) << (64-s), _mm256_extract_epi64(n, 1) << (64-s)));
}

// Logical Right shift by 64 for a avx 256bit register
__m256i _mm256_lrs_64(__m256i n){
	return _mm256_set_epi64x(0, _mm256_extract_epi64(n, 3), _mm256_extract_epi64(n, 2), _mm256_extract_epi64(n, 1));
}

// Logical Right shift by 128 for a avx 256bit register
__m256i _mm256_lrs_128(__m256i n){
	return _mm256_set_epi64x(0, 0, _mm256_extract_epi64(n, 3), _mm256_extract_epi64(n, 2));
}

// Logical Right shift by 192 for a avx 256bit register
__m256i _mm256_lrs_192(__m256i n){
	return _mm256_set_epi64x(0, 0, 0, _mm256_extract_epi64(n, 3));
}


// Logical Right shift for a avx 256bit register
// it combines the larger shift _mm256_lrs_* with the _mm256_lrs_mm256_helper todo the final s bits
__m256i _mm256_lrs_mm256(__m256i n, int32_t s){
	if (s==0) {
		return n;
	} else if (s<0) {
	return n = _mm256_set_epi64x(0, 0, 0, 11ULL);
	} else if (s<=64) {	return _mm256_lrs_mm256_helper(n,s);
	} else if (s<=128){
		n = _mm256_lrs_64(n);
		return _mm256_lrs_mm256_helper(n,s-64);
	}	else if (s<=192){
		n = _mm256_lrs_128(n);
		return _mm256_lrs_mm256_helper(n,s-128);
	} else if (s<=256){
		n = _mm256_lrs_192(n);
		return _mm256_lrs_mm256_helper(n,s-192);
	} else if (s>256)
		return _mm256_setzero_si256();
	return n = _mm256_set_epi64x(0, 0, 0, 9ULL);
}

// Rotate left for a avx 256bit register
__m256i _mm256_rotr (__m256i n, int32_t s){
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