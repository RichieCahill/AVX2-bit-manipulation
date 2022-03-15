#include <iostream>
#include <immintrin.h>

#include"./AVX-bit-manipulation.h"


using namespace std;

// This compairs 2 __m256i registers in 4 set of 64 if any to match it exits the program
// _mm256_testnzc_si256 _mm256_testz_si256 _mm256_testnzc_si256 Ive tried all of these and the weren't reliable for me i think i missunderstand how the worn but im not sure
void Test_256(__m256i a, __m256i b){
	if (_mm256_extract_epi64(a, 3) != _mm256_extract_epi64(b, 3) | _mm256_extract_epi64(a, 2) != _mm256_extract_epi64(b, 2) | _mm256_extract_epi64(a, 1) != _mm256_extract_epi64(b, 1) | _mm256_extract_epi64(a, 0) != _mm256_extract_epi64(b, 0)){
		cout << "problem" << endl;
		cout << std::hex << _mm256_extract_epi64(a, 3) << " " << _mm256_extract_epi64(a, 2) << " " << _mm256_extract_epi64(a, 1) << " " << _mm256_extract_epi64(a, 0) << "\n";
		cout << std::hex << _mm256_extract_epi64(b, 3) << " " << _mm256_extract_epi64(b, 2) << " " << _mm256_extract_epi64(b, 1) << " " << _mm256_extract_epi64(b, 0) << "\n";
		exit(-1);
	}
}

void Test_128(__m128i a, __m128i b){
	if ( _mm_extract_epi64(a, 1) != _mm_extract_epi64(b, 1) | _mm_extract_epi64(a, 0) != _mm_extract_epi64(b, 0)){
		cout << "problem" << endl;
		cout << std::hex << _mm_extract_epi64(a, 1) << " " << _mm_extract_epi64(a, 0) << "\n";
		cout << std::hex << _mm_extract_epi64(b, 1) << " " << _mm_extract_epi64(b, 0) << "\n";
		exit(-1);
	}
}

int main(int argc, char const *argv[]){
// 256bit testing
	const __m256i Zero_256 = _mm256_set_epi64x(0ULL,0ULL,0ULL,0ULL);
	const __m256i LOne_256 = _mm256_set_epi64x(0ULL,0ULL,0ULL,1ULL);
	const __m256i ROne_256 = _mm256_set_epi64x(1ULL,0ULL,0ULL,0ULL);
	const __m256i One4_256 = _mm256_set_epi64x(1ULL,1ULL,1ULL,1ULL);
	const __m256i Full_256 = _mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF);
	const __m256i TestA_256 = _mm256_set_epi64x(0x5555555555555555,0x5555555555555555,0x5555555555555555,0x5555555555555555);
	const __m256i TestB_256 = _mm256_set_epi64x(0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA);
	const __m256i Test_64_0_256 = _mm256_set_epi64x(0ULL,0ULL,0ULL,0xFFFFFFFFFFFFFFFF);
	const __m256i Test_64_1_256 = _mm256_set_epi64x(0ULL,0ULL,0xFFFFFFFFFFFFFFFF,0ULL);
	const __m256i Test_64_2_256 = _mm256_set_epi64x(0ULL,0xFFFFFFFFFFFFFFFF,0ULL,0ULL);
	const __m256i Test_64_3_256 = _mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0ULL,0ULL,0ULL);



// Tests for Logical left shift
	// Test the 64 bit shifts
	Test_256(_mm256_lls_mm256(Test_64_0_256,64),Test_64_1_256);
	Test_256(_mm256_lls_mm256(Test_64_0_256,128),Test_64_2_256);
	Test_256(_mm256_lls_mm256(Test_64_0_256,192),Test_64_3_256);
	Test_256(_mm256_lls_mm256(Test_64_0_256,256),Zero_256);

	Test_256(_mm256_lls_mm256(Test_64_1_256,64),Test_64_2_256);
	Test_256(_mm256_lls_mm256(Test_64_1_256,128),Test_64_3_256);
	Test_256(_mm256_lls_mm256(Test_64_1_256,192),Zero_256);

	Test_256(_mm256_lls_mm256(Test_64_2_256,64),Test_64_3_256);
	Test_256(_mm256_lls_mm256(Test_64_2_256,128),Zero_256);

	Test_256(_mm256_lls_mm256(Test_64_3_256,64),Zero_256);

	// Test for the 1 bit shifts
	// Test for pattern A Left Shifting 1 to 256
	for (int32_t i = 1; i < 64; i++){
		if (i%2==0){
			Test_256(_mm256_lls_mm256(TestA_256,i),_mm256_set_epi64x(0x5555555555555555,0x5555555555555555,0x5555555555555555,(0x5555555555555555<<i)));
		} else {
			Test_256(_mm256_lls_mm256(TestA_256,i),_mm256_set_epi64x(0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,(0x5555555555555555<<i)));
		}
	}

	for (int32_t i = 65; i < 128; i++){
					if (i%2==0){
			Test_256(_mm256_lls_mm256(TestA_256,i),_mm256_set_epi64x(0x5555555555555555,0x5555555555555555,(0x5555555555555555<<i),0ULL));
		} else {
			Test_256(_mm256_lls_mm256(TestA_256,i),_mm256_set_epi64x(0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,(0x5555555555555555<<i),0ULL));
		}
	}

	for (int32_t i = 129; i < 192; i++){
					if (i%2==0){
			Test_256(_mm256_lls_mm256(TestA_256,i),_mm256_set_epi64x(0x5555555555555555,(0x5555555555555555<<i),0ULL,0ULL));
		} else {
			Test_256(_mm256_lls_mm256(TestA_256,i),_mm256_set_epi64x(0xAAAAAAAAAAAAAAAA,(0x5555555555555555<<i),0ULL,0ULL));
		}
	}

	for (int32_t i = 193; i < 256; i++){
					if (i%2==0){
			Test_256(_mm256_lls_mm256(TestA_256,i),_mm256_set_epi64x((0x5555555555555555<<i),0ULL,0ULL,0ULL));
		} else {
			Test_256(_mm256_lls_mm256(TestA_256,i),_mm256_set_epi64x((0x5555555555555555<<i),0ULL,0ULL,0ULL));
		}
	}



	// Test for pattern B Left Shifting 1 to 256
	for (int32_t i = 1; i < 64; i++){
		if (i%2==0){
			Test_256(_mm256_lls_mm256(TestB_256,i),_mm256_set_epi64x(0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,(0xAAAAAAAAAAAAAAAA<<i)));
		} else {
			Test_256(_mm256_lls_mm256(TestB_256,i),_mm256_set_epi64x(0x5555555555555555,0x5555555555555555,0x5555555555555555,(0xAAAAAAAAAAAAAAAA<<i)));
		}
	}


	for (int32_t i = 65; i < 128; i++){
					if (i%2==0){
			Test_256(_mm256_lls_mm256(TestB_256,i),_mm256_set_epi64x(0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,(0xAAAAAAAAAAAAAAAA<<i),0ULL));
		} else {
			Test_256(_mm256_lls_mm256(TestB_256,i),_mm256_set_epi64x(0x5555555555555555,0x5555555555555555,(0xAAAAAAAAAAAAAAAA<<i),0ULL));
		}
	}

	for (int32_t i = 129; i < 192; i++){
					if (i%2==0){
			Test_256(_mm256_lls_mm256(TestB_256,i),_mm256_set_epi64x(0xAAAAAAAAAAAAAAAA,(0xAAAAAAAAAAAAAAAA<<i),0ULL,0ULL));
		} else {
			Test_256(_mm256_lls_mm256(TestB_256,i),_mm256_set_epi64x(0x5555555555555555,(0xAAAAAAAAAAAAAAAA<<i),0ULL,0ULL));
		}
	}

	for (int32_t i = 193; i < 256; i++){
					if (i%2==0){
			Test_256(_mm256_lls_mm256(TestB_256,i),_mm256_set_epi64x((0xAAAAAAAAAAAAAAAA<<i),0ULL,0ULL,0ULL));
		} else {
			Test_256(_mm256_lls_mm256(TestB_256,i),_mm256_set_epi64x((0xAAAAAAAAAAAAAAAA<<i),0ULL,0ULL,0ULL));
		}
	}


	// Test Full_256 avx register Left Shifting 1 to 256
	for (int32_t i = 1; i < 64; i++){
			Test_256(_mm256_lls_mm256(Full_256,i),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,(0xFFFFFFFFFFFFFFFF<<i)));
	}

	for (int32_t i = 65; i < 128; i++){
			Test_256(_mm256_lls_mm256(Full_256,i),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,(0xFFFFFFFFFFFFFFFF<<i),0ULL));
	}

	for (int32_t i = 129; i < 192; i++){
			Test_256(_mm256_lls_mm256(Full_256,i),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,(0xFFFFFFFFFFFFFFFF<<i),0ULL,0ULL));
	}

	for (int32_t i = 193; i < 256; i++){
			Test_256(_mm256_lls_mm256(Full_256,i),_mm256_set_epi64x((0xFFFFFFFFFFFFFFFF<<i),0ULL,0ULL,0ULL));
	}

	// Tests Number 256 to 10000000
	for (int32_t i = 265; i < 10000000; i++){
		Test_256(_mm256_lls_mm256(Full_256,i),Zero_256);
	}
	Test_256(_mm256_lls_mm256(Full_256,10000000),Zero_256);
	Test_256(_mm256_lls_mm256(Full_256,100000000),Zero_256);
	Test_256(_mm256_lls_mm256(Full_256,999999999),Zero_256);
	Test_256(_mm256_lls_mm256(Full_256,1073741823),Zero_256);
	Test_256(_mm256_lls_mm256(Full_256,0x7FFFFFFF),Zero_256);

	// Tests negtiv number
	Test_256(_mm256_lls_mm256(Full_256,0xFFFFFFFF),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test_256(_mm256_lls_mm256(Full_256,-265),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test_256(_mm256_lls_mm256(Full_256,-1000),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test_256(_mm256_lls_mm256(Full_256,-10000),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test_256(_mm256_lls_mm256(Full_256,-100000),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test_256(_mm256_lls_mm256(Full_256,-1000000),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test_256(_mm256_lls_mm256(Full_256,-999999999),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test_256(_mm256_lls_mm256(Full_256,-999999999),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));


	// Back end Test
	Test_256(_mm256_lls_64(Full_256),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0ULL));
	Test_256(_mm256_lls_128(Full_256),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0ULL,0ULL));
	Test_256(_mm256_lls_192(Full_256),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0ULL,0ULL,0ULL));

	Test_256(_mm256_lls_64(TestA_256),_mm256_set_epi64x(0x5555555555555555,0x5555555555555555,0x5555555555555555,0ULL));
	Test_256(_mm256_lls_128(TestA_256),_mm256_set_epi64x(0x5555555555555555,0x5555555555555555,0ULL,0ULL));
	Test_256(_mm256_lls_192(TestA_256),_mm256_set_epi64x(0x5555555555555555,0ULL,0ULL,0ULL));

	Test_256(_mm256_lls_64(TestB_256),_mm256_set_epi64x(0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0ULL));
	Test_256(_mm256_lls_128(TestB_256),_mm256_set_epi64x(0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0ULL,0ULL));
	Test_256(_mm256_lls_192(TestB_256),_mm256_set_epi64x(0xAAAAAAAAAAAAAAAA,0ULL,0ULL,0ULL));


	Test_256(_mm256_lls_64(LOne_256),_mm256_set_epi64x(0ULL,0ULL,1ULL,0ULL));
	Test_256(_mm256_lls_128(LOne_256),_mm256_set_epi64x(0ULL,1ULL,0ULL,0ULL));
	Test_256(_mm256_lls_192(LOne_256),_mm256_set_epi64x(1ULL,0ULL,0ULL,0ULL));

	Test_256(_mm256_lls_64(One4_256),_mm256_set_epi64x(1ULL,1ULL,1ULL,0ULL));
	Test_256(_mm256_lls_128(One4_256),_mm256_set_epi64x(1ULL,1ULL,0ULL,0ULL));
	Test_256(_mm256_lls_192(One4_256),_mm256_set_epi64x(1ULL,0ULL,0ULL,0ULL));
	cout << "LLS_256 Passed" << endl;

	// Tests for Logical Right shift
	// Test the 64 bit shifts

	Test_256(_mm256_lrs_mm256(Test_64_3_256,64),Test_64_2_256);
	Test_256(_mm256_lrs_mm256(Test_64_3_256,128),Test_64_1_256);
	Test_256(_mm256_lrs_mm256(Test_64_3_256,192),Test_64_0_256);
	Test_256(_mm256_lrs_mm256(Test_64_3_256,256),Zero_256);

	Test_256(_mm256_lrs_mm256(Test_64_2_256,64),Test_64_1_256);
	Test_256(_mm256_lrs_mm256(Test_64_2_256,128),Test_64_0_256);
	Test_256(_mm256_lrs_mm256(Test_64_2_256,192),Zero_256);

	Test_256(_mm256_lrs_mm256(Test_64_1_256,64),Test_64_0_256);
	Test_256(_mm256_lrs_mm256(Test_64_1_256,128),Zero_256);

	Test_256(_mm256_lrs_mm256(Test_64_0_256,64),Zero_256);

	// Test for the 1 bit shifts
	// Test for pattern A Right Shifting 1 to 256
	for (int32_t i = 1; i < 64; i++){
					if (i%2==0){
			Test_256(_mm256_lrs_mm256(TestA_256,i),_mm256_set_epi64x((0x5555555555555555>>i),0x5555555555555555,0x5555555555555555,0x5555555555555555));
		} else {
			Test_256(_mm256_lrs_mm256(TestA_256,i),_mm256_set_epi64x((0x5555555555555555>>i),0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA));
		}
	}

	for (int32_t i = 65; i < 128; i++){
					if (i%2==0){
			Test_256(_mm256_lrs_mm256(TestA_256,i),_mm256_set_epi64x(0ULL,(0x5555555555555555>>i),0x5555555555555555,0x5555555555555555));
		} else {
			Test_256(_mm256_lrs_mm256(TestA_256,i),_mm256_set_epi64x(0ULL,(0x5555555555555555>>i),0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA));
		}
	}

	for (int32_t i = 129; i < 192; i++){
					if (i%2==0){
			Test_256(_mm256_lrs_mm256(TestA_256,i),_mm256_set_epi64x(0ULL,0ULL,(0x5555555555555555>>i),0x5555555555555555));
		} else {
			Test_256(_mm256_lrs_mm256(TestA_256,i),_mm256_set_epi64x(0ULL,0ULL,(0x5555555555555555>>i),0xAAAAAAAAAAAAAAAA));
		}
	}

	for (int32_t i = 193; i < 256; i++){
		if (i%2==0){
			Test_256(_mm256_lrs_mm256(TestA_256,i),_mm256_set_epi64x(0ULL,0ULL,0ULL,(0x5555555555555555>>i)));
		} else {
			Test_256(_mm256_lrs_mm256(TestA_256,i),_mm256_set_epi64x(0ULL,0ULL,0ULL,(0x5555555555555555>>i)));
		}
	}


	// Test for pattern B Right Shifting 1 to 256
	for (int32_t i = 1; i < 64; i++){
					if (i%2==0){
			Test_256(_mm256_lrs_mm256(TestB_256,i),_mm256_set_epi64x((0xAAAAAAAAAAAAAAAA>>i),0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA));
		} else {
			Test_256(_mm256_lrs_mm256(TestB_256,i),_mm256_set_epi64x((0xAAAAAAAAAAAAAAAA>>i),0x5555555555555555,0x5555555555555555,0x5555555555555555));
		}
	}

	for (int32_t i = 65; i < 128; i++){
					if (i%2==0){
			Test_256(_mm256_lrs_mm256(TestB_256,i),_mm256_set_epi64x(0ULL,(0xAAAAAAAAAAAAAAAA>>i),0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA));
		} else {
			Test_256(_mm256_lrs_mm256(TestB_256,i),_mm256_set_epi64x(0ULL,(0xAAAAAAAAAAAAAAAA>>i),0x5555555555555555,0x5555555555555555));
		}
	}

	for (int32_t i = 129; i < 192; i++){
					if (i%2==0){
			Test_256(_mm256_lrs_mm256(TestB_256,i),_mm256_set_epi64x(0ULL,0ULL,(0xAAAAAAAAAAAAAAAA>>i),0xAAAAAAAAAAAAAAAA));
		} else {
			Test_256(_mm256_lrs_mm256(TestB_256,i),_mm256_set_epi64x(0ULL,0ULL,(0xAAAAAAAAAAAAAAAA>>i),0x5555555555555555));
		}
	}

	for (int32_t i = 193; i < 256; i++){
		if (i%2==0){
			Test_256(_mm256_lrs_mm256(TestB_256,i),_mm256_set_epi64x(0ULL,0ULL,0ULL,(0xAAAAAAAAAAAAAAAA>>i)));
		} else {
			Test_256(_mm256_lrs_mm256(TestB_256,i),_mm256_set_epi64x(0ULL,0ULL,0ULL,(0xAAAAAAAAAAAAAAAA>>i)));
		}
	}


	// Test Full_256 avx register Right Shifting 1 to 256
	for (int32_t i = 1; i < 64; i++){
		int32_t a=i+64,b=i+128,c=i+192;
		Test_256(_mm256_lrs_mm256(Full_256,i),_mm256_set_epi64x((0xFFFFFFFFFFFFFFFF>>i),0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	}

	for (int32_t i = 65; i < 128; i++){
		Test_256(_mm256_lrs_mm256(Full_256,i),_mm256_set_epi64x(0ULL,(0xFFFFFFFFFFFFFFFF>>i),0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	}

	for (int32_t i = 129; i < 192; i++){
		Test_256(_mm256_lrs_mm256(Full_256,i),_mm256_set_epi64x(0ULL,0ULL,(0xFFFFFFFFFFFFFFFF>>i),0xFFFFFFFFFFFFFFFF));
	}
	for (int32_t i = 193; i < 256; i++){
			Test_256(_mm256_lrs_mm256(Full_256,i),_mm256_set_epi64x(0ULL,0ULL,0ULL,(0xFFFFFFFFFFFFFFFF>>i)));
	}


	// Tests Number 256 to 10000000
	for (int32_t i = 265; i < 10000000; i++){
		Test_256(_mm256_lrs_mm256(Full_256,i),Zero_256);
	}
	Test_256(_mm256_lrs_mm256(Full_256,10000000),Zero_256);
	Test_256(_mm256_lrs_mm256(Full_256,100000000),Zero_256);
	Test_256(_mm256_lrs_mm256(Full_256,999999999),Zero_256);
	Test_256(_mm256_lrs_mm256(Full_256,1073741823),Zero_256);
	Test_256(_mm256_lrs_mm256(Full_256,0x7FFFFFFF),Zero_256);

	// Tests negtiv number
	Test_256(_mm256_lrs_mm256(Full_256,0xFFFFFFFF),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test_256(_mm256_lrs_mm256(Full_256,-265),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test_256(_mm256_lrs_mm256(Full_256,-1000),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test_256(_mm256_lrs_mm256(Full_256,-10000),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test_256(_mm256_lrs_mm256(Full_256,-100000),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test_256(_mm256_lrs_mm256(Full_256,-1000000),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test_256(_mm256_lrs_mm256(Full_256,-999999999),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));


	// Back end Test
	Test_256(_mm256_lrs_64(Full_256),_mm256_set_epi64x(0ULL,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test_256(_mm256_lrs_128(Full_256),_mm256_set_epi64x(0ULL,0ULL,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test_256(_mm256_lrs_192(Full_256),_mm256_set_epi64x(0ULL,0ULL,0ULL,0xFFFFFFFFFFFFFFFF));

	Test_256(_mm256_lrs_64(TestA_256),_mm256_set_epi64x(0ULL,0x5555555555555555,0x5555555555555555,0x5555555555555555));
	Test_256(_mm256_lrs_128(TestA_256),_mm256_set_epi64x(0ULL,0ULL,0x5555555555555555,0x5555555555555555));
	Test_256(_mm256_lrs_192(TestA_256),_mm256_set_epi64x(0ULL,0ULL,0ULL,0x5555555555555555));

	Test_256(_mm256_lrs_64(TestB_256),_mm256_set_epi64x(0ULL,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA));
	Test_256(_mm256_lrs_128(TestB_256),_mm256_set_epi64x(0ULL,0ULL,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA));
	Test_256(_mm256_lrs_192(TestB_256),_mm256_set_epi64x(0ULL,0ULL,0ULL,0xAAAAAAAAAAAAAAAA));

	Test_256(_mm256_lrs_64(ROne_256),_mm256_set_epi64x(0ULL,1ULL,0ULL,0ULL));
	Test_256(_mm256_lrs_128(ROne_256),_mm256_set_epi64x(0ULL,0ULL,1ULL,0ULL));
	Test_256(_mm256_lrs_192(ROne_256),_mm256_set_epi64x(0ULL,0ULL,0ULL,1ULL));

	Test_256(_mm256_lrs_64(One4_256),_mm256_set_epi64x(0ULL,1ULL,1ULL,1ULL));
	Test_256(_mm256_lrs_128(One4_256),_mm256_set_epi64x(0ULL,0ULL,1ULL,1ULL));
	Test_256(_mm256_lrs_192(One4_256),_mm256_set_epi64x(0ULL,0ULL,0ULL,1ULL));


	cout << "LRS_256 Passed" << endl;

	// Tests for Rotate left
	// Test the 64 bit Rotate
	Test_256(_mm256_rotl_mm256(Test_64_0_256,64),Test_64_1_256);
	Test_256(_mm256_rotl_mm256(Test_64_0_256,128),Test_64_2_256);
	Test_256(_mm256_rotl_mm256(Test_64_0_256,192),Test_64_3_256);

	Test_256(_mm256_rotl_mm256(Test_64_1_256,64),Test_64_2_256);
	Test_256(_mm256_rotl_mm256(Test_64_1_256,128),Test_64_3_256);
	Test_256(_mm256_rotl_mm256(Test_64_1_256,192),Test_64_0_256);

	Test_256(_mm256_rotl_mm256(Test_64_2_256,64),Test_64_3_256);
	Test_256(_mm256_rotl_mm256(Test_64_2_256,128),Test_64_0_256);
	Test_256(_mm256_rotl_mm256(Test_64_2_256,192),Test_64_1_256);

	Test_256(_mm256_rotl_mm256(Test_64_3_256,64),Test_64_0_256);
	Test_256(_mm256_rotl_mm256(Test_64_3_256,128),Test_64_1_256);
	Test_256(_mm256_rotl_mm256(Test_64_3_256,192),Test_64_2_256);


	for (int32_t i = 1; i <= 255; i++){
		Test_256(_mm256_rotl_mm256(Full_256,i),Full_256);
	}

	// Test for pattern A Rotate left 1 to 256
	for (int32_t i = 1; i <= 255; i++){
			if (i%2==0){
			Test_256(_mm256_rotl_mm256(TestA_256,i),TestA_256);
	} else {
			Test_256(_mm256_rotl_mm256(TestA_256,i),TestB_256);
		}
	}

	// Test for pattern B Rotate left 1 to 256
	for (int32_t i = 1; i <= 255; i++){
			if (i%2==0){
			Test_256(_mm256_rotl_mm256(TestB_256,i),TestB_256);
		} else {
			Test_256(_mm256_rotl_mm256(TestB_256,i),TestA_256);
		}
	}

	// Test for patern One4_256 Rotate left 1 to 256
	for (int32_t i = 1; i <= 64; i++){
		int32_t a=i+64,b=i+128,c=i+192;
		Test_256(_mm256_rotl_mm256(One4_256,i),_mm256_set_epi64x((1ULL<<i),(1ULL<<i),(1ULL<<i),(1ULL<<i)));
		Test_256(_mm256_rotl_mm256(One4_256,a),_mm256_set_epi64x((1ULL<<i),(1ULL<<i),(1ULL<<i),(1ULL<<i)));
		Test_256(_mm256_rotl_mm256(One4_256,b),_mm256_set_epi64x((1ULL<<i),(1ULL<<i),(1ULL<<i),(1ULL<<i)));
		Test_256(_mm256_rotl_mm256(One4_256,b),_mm256_set_epi64x((1ULL<<i),(1ULL<<i),(1ULL<<i),(1ULL<<i)));

	}

	// Test for patern One4_256 Rotate left 1 to 256
	for (int32_t i = 1; i <= 64; i++){
		int32_t a=i+64,b=i+128,c=i+192;
		Test_256(_mm256_rotl_mm256(One4_256,i),_mm256_set_epi64x((1ULL<<i),(1ULL<<i),(1ULL<<i),(1ULL<<i)));
		Test_256(_mm256_rotl_mm256(One4_256,a),_mm256_set_epi64x((1ULL<<i),(1ULL<<i),(1ULL<<i),(1ULL<<i)));
		Test_256(_mm256_rotl_mm256(One4_256,b),_mm256_set_epi64x((1ULL<<i),(1ULL<<i),(1ULL<<i),(1ULL<<i)));
		Test_256(_mm256_rotl_mm256(One4_256,b),_mm256_set_epi64x((1ULL<<i),(1ULL<<i),(1ULL<<i),(1ULL<<i)));

	}

	// Test for patern LOne_256 Rotate left 1 to 256
	for (int32_t i = 1; i <= 63; i++){
		int32_t a=i+64,b=i+128,c=i+192;
		Test_256(_mm256_rotl_mm256(LOne_256,i),_mm256_set_epi64x(0ULL,0ULL,0ULL,(1ULL<<i)));
		Test_256(_mm256_rotl_mm256(LOne_256,a),_mm256_set_epi64x(0ULL,0ULL,(1ULL<<i),0ULL));
		Test_256(_mm256_rotl_mm256(LOne_256,b),_mm256_set_epi64x(0ULL,(1ULL<<i),0ULL,0ULL));
		Test_256(_mm256_rotl_mm256(LOne_256,c),_mm256_set_epi64x((1ULL<<i),0ULL,0ULL,0ULL));
	}


	// Test for patern ROne_256 Rotate left 1 to 256
	for (int32_t i = 1; i <= 63; i++){
		int32_t a=i+64,b=i+128,c=i+192;
		Test_256(_mm256_rotl_mm256(ROne_256,i),_mm256_set_epi64x((1ULL<<i),0ULL,0ULL,0ULL));
		Test_256(_mm256_rotl_mm256(ROne_256,a),_mm256_set_epi64x(0ULL,0ULL,0ULL,(1ULL<<i)));
		Test_256(_mm256_rotl_mm256(ROne_256,b),_mm256_set_epi64x(0ULL,0ULL,(1ULL<<i),0ULL));
		Test_256(_mm256_rotl_mm256(ROne_256,c),_mm256_set_epi64x(0ULL,(1ULL<<i),0ULL,0ULL));
	}

		// Tests Number 256 to 10000000
	for (int32_t i = 265; i < 10000000; i++){
		Test_256(_mm256_rotl_mm256(Full_256,i),Zero_256);
	}
	Test_256(_mm256_rotl_mm256(Full_256,10000000),Zero_256);
	Test_256(_mm256_rotl_mm256(Full_256,100000000),Zero_256);
	Test_256(_mm256_rotl_mm256(Full_256,999999999),Zero_256);
	Test_256(_mm256_rotl_mm256(Full_256,1073741823),Zero_256);
	Test_256(_mm256_rotl_mm256(Full_256,0x7FFFFFFF),Zero_256);

	// Tests negtiv number

	Test_256(_mm256_rotl_mm256(Full_256,0xFFFFFFFF),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test_256(_mm256_rotl_mm256(Full_256,-265),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test_256(_mm256_rotl_mm256(Full_256,-1000),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test_256(_mm256_rotl_mm256(Full_256,-10000),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test_256(_mm256_rotl_mm256(Full_256,-100000),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test_256(_mm256_rotl_mm256(Full_256,-1000000),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test_256(_mm256_rotl_mm256(Full_256,-999999999),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	
	// Back end Test
	Test_256(_mm256_rotl_64(Full_256),Full_256);
	Test_256(_mm256_rotl_128(Full_256),Full_256);
	Test_256(_mm256_rotl_192(Full_256),Full_256);

	Test_256(_mm256_rotl_64(TestA_256),TestA_256);
	Test_256(_mm256_rotl_128(TestA_256),TestA_256);
	Test_256(_mm256_rotl_192(TestA_256),TestA_256);

	Test_256(_mm256_rotl_64(TestB_256),TestB_256);
	Test_256(_mm256_rotl_128(TestB_256),TestB_256);
	Test_256(_mm256_rotl_192(TestB_256),TestB_256);

	Test_256(_mm256_rotl_64(Test_64_0_256),Test_64_1_256);
	Test_256(_mm256_rotl_128(Test_64_0_256),Test_64_2_256);
	Test_256(_mm256_rotl_192(Test_64_0_256),Test_64_3_256);

	Test_256(_mm256_rotl_64(Test_64_1_256),Test_64_2_256);
	Test_256(_mm256_rotl_128(Test_64_1_256),Test_64_3_256);
	Test_256(_mm256_rotl_192(Test_64_1_256),Test_64_0_256);

	Test_256(_mm256_rotl_64(Test_64_2_256),Test_64_3_256);
	Test_256(_mm256_rotl_128(Test_64_2_256),Test_64_0_256);
	Test_256(_mm256_rotl_192(Test_64_2_256),Test_64_1_256);

	Test_256(_mm256_rotl_64(Test_64_3_256),Test_64_0_256);
	Test_256(_mm256_rotl_128(Test_64_3_256),Test_64_1_256);
	Test_256(_mm256_rotl_192(Test_64_3_256),Test_64_2_256);
	cout << "ROTL_256 Passed" << endl;


// 128bit testing
	const __m128i Zero_128 = _mm_set_epi64x(0ULL,0ULL);
	const __m128i LOne_128 = _mm_set_epi64x(0ULL,1ULL);
	const __m128i ROne_128 = _mm_set_epi64x(1ULL,0ULL);
	const __m128i One2_128 = _mm_set_epi64x(1ULL,1ULL);
	const __m128i Full_128 = _mm_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF);
	const __m128i TestA_128 = _mm_set_epi64x(0x5555555555555555,0x5555555555555555);
	const __m128i TestB_128 = _mm_set_epi64x(0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA);
	const __m128i Test_64_0_128 = _mm_set_epi64x(0ULL,0xFFFFFFFFFFFFFFFF);
	const __m128i Test_64_1_128 = _mm_set_epi64x(0xFFFFFFFFFFFFFFFF,0ULL);
	
	
// Tests for Logical left shift
	// Test the 64 bit shifts
	Test_128(_mm_lls_si128(Test_64_0_128,64),Test_64_1_128);
	Test_128(_mm_lls_si128(Test_64_0_128,128),Zero_128);

	Test_128(_mm_lls_si128(Test_64_1_128,64),Zero_128);

	// Test for pattern A Left Shifting 1 to 128
	for (int32_t i = 0; i < 64; i++){
			int32_t a=i+64;
			if (i%2==0){
			Test_128(_mm_lls_si128(TestA_128,i),_mm_set_epi64x(0x5555555555555555,(0x5555555555555555<<i)));
			Test_128(_mm_lls_si128(TestA_128,a),_mm_set_epi64x((0x5555555555555555<<i),0ULL));
			} else {
			Test_128(_mm_lls_si128(TestA_128,i),_mm_set_epi64x(0xAAAAAAAAAAAAAAAA,(0x5555555555555555<<i)));
			Test_128(_mm_lls_si128(TestA_128,a),_mm_set_epi64x((0x5555555555555555<<i),0ULL));
		}
	}

	// Test for pattern B Left Shifting 1 to 128
	for (int32_t i = 0; i < 64; i++){
			int32_t a=i+64;
			if (i%2==0){
			Test_128(_mm_lls_si128(TestB_128,i),_mm_set_epi64x(0xAAAAAAAAAAAAAAAA,(0xAAAAAAAAAAAAAAAA<<i)));
			Test_128(_mm_lls_si128(TestB_128,a),_mm_set_epi64x((0xAAAAAAAAAAAAAAAA<<i),0ULL));
			} else {
			Test_128(_mm_lls_si128(TestB_128,i),_mm_set_epi64x(0x5555555555555555,(0xAAAAAAAAAAAAAAAA<<i)));
			Test_128(_mm_lls_si128(TestB_128,a),_mm_set_epi64x((0xAAAAAAAAAAAAAAAA<<i),0ULL));
		}
	}


	for (int32_t i = 0; i < 64; i++){
		int32_t a=i+64;
		Test_128(_mm_lls_si128(One2_128,i),_mm_set_epi64x((1ULL<<i),(1ULL<<i)));
		Test_128(_mm_lls_si128(One2_128,a),_mm_set_epi64x((1ULL<<i),0ULL));
	}

	for (int32_t i = 0; i < 64; i++){
		int32_t a=i+64;
		Test_128(_mm_lls_si128(Full_128,i),_mm_set_epi64x(0xFFFFFFFFFFFFFFFF,(0xFFFFFFFFFFFFFFFF<<i)));
		Test_128(_mm_lls_si128(Full_128,a),_mm_set_epi64x((0xFFFFFFFFFFFFFFFF<<i),0ULL));
	}

	// Tests Number 256 to 10000000
	for (int32_t i = 265; i < 10000000; i++){
		Test_128(_mm_lls_si128(Full_128,i),Zero_128);
	}
	Test_128(_mm_lls_si128(Full_128,10000000),Zero_128);
	Test_128(_mm_lls_si128(Full_128,100000000),Zero_128);
	Test_128(_mm_lls_si128(Full_128,999999999),Zero_128);
	Test_128(_mm_lls_si128(Full_128,1073741823),Zero_128);
	Test_128(_mm_lls_si128(Full_128,0x7FFFFFFF),Zero_128);

	// Tests negtiv number
	Test_128(_mm_lls_si128(Full_128,0xFFFFFFFF),_mm_set_epi64x(0ULL,11ULL));
	Test_128(_mm_lls_si128(Full_128,-265),_mm_set_epi64x(0ULL,11ULL));
	Test_128(_mm_lls_si128(Full_128,-1000),_mm_set_epi64x(0ULL,11ULL));
	Test_128(_mm_lls_si128(Full_128,-10000),_mm_set_epi64x(0ULL,11ULL));
	Test_128(_mm_lls_si128(Full_128,-100000),_mm_set_epi64x(0ULL,11ULL));
	Test_128(_mm_lls_si128(Full_128,-1000000),_mm_set_epi64x(0ULL,11ULL));
	Test_128(_mm_lls_si128(Full_128,-999999999),_mm_set_epi64x(0ULL,11ULL));
	Test_128(_mm_lls_si128(Full_128,-999999999),_mm_set_epi64x(0ULL,11ULL));



	// Back end Test
	Test_128(_mm_lls_64(Full_128),_mm_set_epi64x(0xFFFFFFFFFFFFFFFF,0ULL));
	Test_128(_mm_lls_64(TestA_128),_mm_set_epi64x(0x5555555555555555,0ULL));
	Test_128(_mm_lls_64(TestB_128),_mm_set_epi64x(0xAAAAAAAAAAAAAAAA,0ULL));
	Test_128(_mm_lls_64(LOne_128),_mm_set_epi64x(1ULL,0ULL));
	Test_128(_mm_lls_64(One2_128),_mm_set_epi64x(1ULL,0ULL));
	Test_128(_mm_lls_64(Test_64_1_128),Zero_128);

	cout << "LLS_128 Passed" << endl;


	return 0;
}