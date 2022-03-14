#include <iostream>
#include <immintrin.h>

#include"./AVX-bit-manipulation.h"


using namespace std;

// This compairs 2 __m256i registers in 4 set of 64 if any to match it exits the program
// _mm256_testnzc_si256 _mm256_testz_si256 _mm256_testnzc_si256 Ive tried all of these and the weren't reliable for me i think i missunderstand how the worn but im not sure
void Test(__m256i a, __m256i b){
	if (_mm256_extract_epi64(a, 3) != _mm256_extract_epi64(b, 3) | _mm256_extract_epi64(a, 2) != _mm256_extract_epi64(b, 2) | _mm256_extract_epi64(a, 1) != _mm256_extract_epi64(b, 1) | _mm256_extract_epi64(a, 0) != _mm256_extract_epi64(b, 0)){
		cout << "problem" << endl;
		cout << std::hex << _mm256_extract_epi64(a, 3) << " " << _mm256_extract_epi64(a, 2) << " " << _mm256_extract_epi64(a, 1) << " " << _mm256_extract_epi64(a, 0) << "\n";
		cout << std::hex << _mm256_extract_epi64(b, 3) << " " << _mm256_extract_epi64(b, 2) << " " << _mm256_extract_epi64(b, 1) << " " << _mm256_extract_epi64(b, 0) << "\n";
		exit(-1);
	}
}

int main(int argc, char const *argv[]){

	const __m256i Zero = _mm256_set_epi64x(0ULL,0ULL,0ULL,0ULL);
	const __m256i LOne = _mm256_set_epi64x(0ULL,0ULL,0ULL,1ULL);
	const __m256i ROne = _mm256_set_epi64x(1ULL,0ULL,0ULL,0ULL);
	const __m256i One4 = _mm256_set_epi64x(1ULL,1ULL,1ULL,1ULL);
	const __m256i Full = _mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF);
	const __m256i TestA = _mm256_set_epi64x(0x5555555555555555,0x5555555555555555,0x5555555555555555,0x5555555555555555);
	const __m256i TestB = _mm256_set_epi64x(0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA);
	const __m256i Test_64_0 = _mm256_set_epi64x(0ULL,0ULL,0ULL,0xFFFFFFFFFFFFFFFF);
	const __m256i Test_64_1 = _mm256_set_epi64x(0ULL,0ULL,0xFFFFFFFFFFFFFFFF,0ULL);
	const __m256i Test_64_2 = _mm256_set_epi64x(0ULL,0xFFFFFFFFFFFFFFFF,0ULL,0ULL);
	const __m256i Test_64_3 = _mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0ULL,0ULL,0ULL);




avxout(_mm256_rotl_mm256_helper(LOne,1));
avxout(ROne);
avxout(_mm256_rotl_mm256_helper(ROne,1));


// Tests for Logical left shift
	// Test the 64 bit shifts
	Test(_mm256_lls_mm256(Test_64_0,64),Test_64_1);
	Test(_mm256_lls_mm256(Test_64_0,128),Test_64_2);
	Test(_mm256_lls_mm256(Test_64_0,192),Test_64_3);
	Test(_mm256_lls_mm256(Test_64_0,256),Zero);

	Test(_mm256_lls_mm256(Test_64_1,64),Test_64_2);
	Test(_mm256_lls_mm256(Test_64_1,128),Test_64_3);
	Test(_mm256_lls_mm256(Test_64_1,192),Zero);

	Test(_mm256_lls_mm256(Test_64_2,64),Test_64_3);
	Test(_mm256_lls_mm256(Test_64_2,128),Zero);

	Test(_mm256_lls_mm256(Test_64_3,64),Zero);

	// Test for the 1 bit shifts
	// Test for pattern A Left Shifting 1 to 256
	for (int32_t i = 1; i < 64; i++){
		if (i%2==0){
			Test(_mm256_lls_mm256(TestA,i),_mm256_set_epi64x(0x5555555555555555,0x5555555555555555,0x5555555555555555,(0x5555555555555555<<i)));
		} else {
			Test(_mm256_lls_mm256(TestA,i),_mm256_set_epi64x(0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,(0x5555555555555555<<i)));
		}
	}

	for (int32_t i = 65; i < 128; i++){
					if (i%2==0){
			Test(_mm256_lls_mm256(TestA,i),_mm256_set_epi64x(0x5555555555555555,0x5555555555555555,(0x5555555555555555<<i),0ULL));
		} else {
			Test(_mm256_lls_mm256(TestA,i),_mm256_set_epi64x(0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,(0x5555555555555555<<i),0ULL));
		}
	}

	for (int32_t i = 129; i < 192; i++){
					if (i%2==0){
			Test(_mm256_lls_mm256(TestA,i),_mm256_set_epi64x(0x5555555555555555,(0x5555555555555555<<i),0ULL,0ULL));
		} else {
			Test(_mm256_lls_mm256(TestA,i),_mm256_set_epi64x(0xAAAAAAAAAAAAAAAA,(0x5555555555555555<<i),0ULL,0ULL));
		}
	}

	for (int32_t i = 193; i < 256; i++){
					if (i%2==0){
			Test(_mm256_lls_mm256(TestA,i),_mm256_set_epi64x((0x5555555555555555<<i),0ULL,0ULL,0ULL));
		} else {
			Test(_mm256_lls_mm256(TestA,i),_mm256_set_epi64x((0x5555555555555555<<i),0ULL,0ULL,0ULL));
		}
	}



	// Test for pattern B Left Shifting 1 to 256
	for (int32_t i = 1; i < 64; i++){
		if (i%2==0){
			Test(_mm256_lls_mm256(TestB,i),_mm256_set_epi64x(0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,(0xAAAAAAAAAAAAAAAA<<i)));
		} else {
			Test(_mm256_lls_mm256(TestB,i),_mm256_set_epi64x(0x5555555555555555,0x5555555555555555,0x5555555555555555,(0xAAAAAAAAAAAAAAAA<<i)));
		}
	}


	for (int32_t i = 65; i < 128; i++){
					if (i%2==0){
			Test(_mm256_lls_mm256(TestB,i),_mm256_set_epi64x(0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,(0xAAAAAAAAAAAAAAAA<<i),0ULL));
		} else {
			Test(_mm256_lls_mm256(TestB,i),_mm256_set_epi64x(0x5555555555555555,0x5555555555555555,(0xAAAAAAAAAAAAAAAA<<i),0ULL));
		}
	}

	for (int32_t i = 129; i < 192; i++){
					if (i%2==0){
			Test(_mm256_lls_mm256(TestB,i),_mm256_set_epi64x(0xAAAAAAAAAAAAAAAA,(0xAAAAAAAAAAAAAAAA<<i),0ULL,0ULL));
		} else {
			Test(_mm256_lls_mm256(TestB,i),_mm256_set_epi64x(0x5555555555555555,(0xAAAAAAAAAAAAAAAA<<i),0ULL,0ULL));
		}
	}

	for (int32_t i = 193; i < 256; i++){
					if (i%2==0){
			Test(_mm256_lls_mm256(TestB,i),_mm256_set_epi64x((0xAAAAAAAAAAAAAAAA<<i),0ULL,0ULL,0ULL));
		} else {
			Test(_mm256_lls_mm256(TestB,i),_mm256_set_epi64x((0xAAAAAAAAAAAAAAAA<<i),0ULL,0ULL,0ULL));
		}
	}


	// Test Full avx register Left Shifting 1 to 256
	for (int32_t i = 1; i < 64; i++){
			Test(_mm256_lls_mm256(Full,i),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,(0xFFFFFFFFFFFFFFFF<<i)));
	}

	for (int32_t i = 65; i < 128; i++){
			Test(_mm256_lls_mm256(Full,i),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,(0xFFFFFFFFFFFFFFFF<<i),0ULL));
	}

	for (int32_t i = 129; i < 192; i++){
			Test(_mm256_lls_mm256(Full,i),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,(0xFFFFFFFFFFFFFFFF<<i),0ULL,0ULL));
	}

	for (int32_t i = 193; i < 256; i++){
			Test(_mm256_lls_mm256(Full,i),_mm256_set_epi64x((0xFFFFFFFFFFFFFFFF<<i),0ULL,0ULL,0ULL));
	}

	// Tests Number 256 to 10000000
	for (int32_t i = 265; i < 10000000; i++){
		Test(_mm256_lls_mm256(Full,i),Zero);
	}
	Test(_mm256_lls_mm256(Full,10000000),Zero);
	Test(_mm256_lls_mm256(Full,100000000),Zero);
	Test(_mm256_lls_mm256(Full,999999999),Zero);
	Test(_mm256_lls_mm256(Full,1073741823),Zero);
	Test(_mm256_lls_mm256(Full,0x7FFFFFFF),Zero);

	// Tests negtiv number
	Test(_mm256_lls_mm256(Full,0xFFFFFFFF),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test(_mm256_lls_mm256(Full,-265),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test(_mm256_lls_mm256(Full,-1000),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test(_mm256_lls_mm256(Full,-10000),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test(_mm256_lls_mm256(Full,-100000),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test(_mm256_lls_mm256(Full,-1000000),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test(_mm256_lls_mm256(Full,-999999999),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test(_mm256_lls_mm256(Full,-999999999),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));


	// Back end Test
	Test(_mm256_lls_64(Full),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0ULL));
	Test(_mm256_lls_128(Full),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0ULL,0ULL));
	Test(_mm256_lls_192(Full),_mm256_set_epi64x(0xFFFFFFFFFFFFFFFF,0ULL,0ULL,0ULL));

	Test(_mm256_lls_64(TestA),_mm256_set_epi64x(0x5555555555555555,0x5555555555555555,0x5555555555555555,0ULL));
	Test(_mm256_lls_128(TestA),_mm256_set_epi64x(0x5555555555555555,0x5555555555555555,0ULL,0ULL));
	Test(_mm256_lls_192(TestA),_mm256_set_epi64x(0x5555555555555555,0ULL,0ULL,0ULL));

	Test(_mm256_lls_64(TestB),_mm256_set_epi64x(0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0ULL));
	Test(_mm256_lls_128(TestB),_mm256_set_epi64x(0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0ULL,0ULL));
	Test(_mm256_lls_192(TestB),_mm256_set_epi64x(0xAAAAAAAAAAAAAAAA,0ULL,0ULL,0ULL));


	Test(_mm256_lls_64(LOne),_mm256_set_epi64x(0ULL,0ULL,1ULL,0ULL));
	Test(_mm256_lls_128(LOne),_mm256_set_epi64x(0ULL,1ULL,0ULL,0ULL));
	Test(_mm256_lls_192(LOne),_mm256_set_epi64x(1ULL,0ULL,0ULL,0ULL));

	Test(_mm256_lls_64(One4),_mm256_set_epi64x(1ULL,1ULL,1ULL,0ULL));
	Test(_mm256_lls_128(One4),_mm256_set_epi64x(1ULL,1ULL,0ULL,0ULL));
	Test(_mm256_lls_192(One4),_mm256_set_epi64x(1ULL,0ULL,0ULL,0ULL));
	cout << "LLS Passed" << endl;

	// Tests for Logical Right shift
	// Test the 64 bit shifts

	Test(_mm256_lrs_mm256(Test_64_3,64),Test_64_2);
	Test(_mm256_lrs_mm256(Test_64_3,128),Test_64_1);
	Test(_mm256_lrs_mm256(Test_64_3,192),Test_64_0);
	Test(_mm256_lrs_mm256(Test_64_3,256),Zero);

	Test(_mm256_lrs_mm256(Test_64_2,64),Test_64_1);
	Test(_mm256_lrs_mm256(Test_64_2,128),Test_64_0);
	Test(_mm256_lrs_mm256(Test_64_2,192),Zero);

	Test(_mm256_lrs_mm256(Test_64_1,64),Test_64_0);
	Test(_mm256_lrs_mm256(Test_64_1,128),Zero);

	Test(_mm256_lrs_mm256(Test_64_0,64),Zero);

	// Test for the 1 bit shifts
	// Test for pattern A Right Shifting 1 to 256
	for (int32_t i = 1; i < 64; i++){
					if (i%2==0){
			Test(_mm256_lrs_mm256(TestA,i),_mm256_set_epi64x((0x5555555555555555>>i),0x5555555555555555,0x5555555555555555,0x5555555555555555));
		} else {
			Test(_mm256_lrs_mm256(TestA,i),_mm256_set_epi64x((0x5555555555555555>>i),0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA));
		}
	}

	for (int32_t i = 65; i < 128; i++){
					if (i%2==0){
			Test(_mm256_lrs_mm256(TestA,i),_mm256_set_epi64x(0ULL,(0x5555555555555555>>i),0x5555555555555555,0x5555555555555555));
		} else {
			Test(_mm256_lrs_mm256(TestA,i),_mm256_set_epi64x(0ULL,(0x5555555555555555>>i),0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA));
		}
	}

	for (int32_t i = 129; i < 192; i++){
					if (i%2==0){
			Test(_mm256_lrs_mm256(TestA,i),_mm256_set_epi64x(0ULL,0ULL,(0x5555555555555555>>i),0x5555555555555555));
		} else {
			Test(_mm256_lrs_mm256(TestA,i),_mm256_set_epi64x(0ULL,0ULL,(0x5555555555555555>>i),0xAAAAAAAAAAAAAAAA));
		}
	}

	for (int32_t i = 193; i < 256; i++){
		if (i%2==0){
			Test(_mm256_lrs_mm256(TestA,i),_mm256_set_epi64x(0ULL,0ULL,0ULL,(0x5555555555555555>>i)));
		} else {
			Test(_mm256_lrs_mm256(TestA,i),_mm256_set_epi64x(0ULL,0ULL,0ULL,(0x5555555555555555>>i)));
		}
	}


	// Test for pattern B Right Shifting 1 to 256
	for (int32_t i = 1; i < 64; i++){
					if (i%2==0){
			Test(_mm256_lrs_mm256(TestB,i),_mm256_set_epi64x((0xAAAAAAAAAAAAAAAA>>i),0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA));
		} else {
			Test(_mm256_lrs_mm256(TestB,i),_mm256_set_epi64x((0xAAAAAAAAAAAAAAAA>>i),0x5555555555555555,0x5555555555555555,0x5555555555555555));
		}
	}

	for (int32_t i = 65; i < 128; i++){
					if (i%2==0){
			Test(_mm256_lrs_mm256(TestB,i),_mm256_set_epi64x(0ULL,(0xAAAAAAAAAAAAAAAA>>i),0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA));
		} else {
			Test(_mm256_lrs_mm256(TestB,i),_mm256_set_epi64x(0ULL,(0xAAAAAAAAAAAAAAAA>>i),0x5555555555555555,0x5555555555555555));
		}
	}

	for (int32_t i = 129; i < 192; i++){
					if (i%2==0){
			Test(_mm256_lrs_mm256(TestB,i),_mm256_set_epi64x(0ULL,0ULL,(0xAAAAAAAAAAAAAAAA>>i),0xAAAAAAAAAAAAAAAA));
		} else {
			Test(_mm256_lrs_mm256(TestB,i),_mm256_set_epi64x(0ULL,0ULL,(0xAAAAAAAAAAAAAAAA>>i),0x5555555555555555));
		}
	}

	for (int32_t i = 193; i < 256; i++){
		if (i%2==0){
			Test(_mm256_lrs_mm256(TestB,i),_mm256_set_epi64x(0ULL,0ULL,0ULL,(0xAAAAAAAAAAAAAAAA>>i)));
		} else {
			Test(_mm256_lrs_mm256(TestB,i),_mm256_set_epi64x(0ULL,0ULL,0ULL,(0xAAAAAAAAAAAAAAAA>>i)));
		}
	}


	// Test Full avx register Right Shifting 1 to 256
	for (int32_t i = 1; i < 64; i++){
		Test(_mm256_lrs_mm256(Full,i),_mm256_set_epi64x((0xFFFFFFFFFFFFFFFF>>i),0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	}

	for (int32_t i = 65; i < 128; i++){
		Test(_mm256_lrs_mm256(Full,i),_mm256_set_epi64x(0ULL,(0xFFFFFFFFFFFFFFFF>>i),0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	}

	for (int32_t i = 129; i < 192; i++){
		Test(_mm256_lrs_mm256(Full,i),_mm256_set_epi64x(0ULL,0ULL,(0xFFFFFFFFFFFFFFFF>>i),0xFFFFFFFFFFFFFFFF));
	}
	for (int32_t i = 193; i < 256; i++){
			Test(_mm256_lrs_mm256(Full,i),_mm256_set_epi64x(0ULL,0ULL,0ULL,(0xFFFFFFFFFFFFFFFF>>i)));
	}


	// Tests Number 256 to 10000000
	for (int32_t i = 265; i < 10000000; i++){
		Test(_mm256_lrs_mm256(Full,i),Zero);
	}
	Test(_mm256_lrs_mm256(Full,10000000),Zero);
	Test(_mm256_lrs_mm256(Full,100000000),Zero);
	Test(_mm256_lrs_mm256(Full,999999999),Zero);
	Test(_mm256_lrs_mm256(Full,1073741823),Zero);
	Test(_mm256_lrs_mm256(Full,0x7FFFFFFF),Zero);


	Test(_mm256_lrs_mm256(Full,0xFFFFFFFF),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test(_mm256_lrs_mm256(Full,-265),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test(_mm256_lrs_mm256(Full,-1000),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test(_mm256_lrs_mm256(Full,-10000),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test(_mm256_lrs_mm256(Full,-100000),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test(_mm256_lrs_mm256(Full,-1000000),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));
	Test(_mm256_lrs_mm256(Full,-999999999),_mm256_set_epi64x(0ULL,0ULL,0ULL,11ULL));


	// Back end Test
	Test(_mm256_lrs_64(Full),_mm256_set_epi64x(0ULL,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_128(Full),_mm256_set_epi64x(0ULL,0ULL,0xFFFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF));
	Test(_mm256_lrs_192(Full),_mm256_set_epi64x(0ULL,0ULL,0ULL,0xFFFFFFFFFFFFFFFF));

	Test(_mm256_lrs_64(TestA),_mm256_set_epi64x(0ULL,0x5555555555555555,0x5555555555555555,0x5555555555555555));
	Test(_mm256_lrs_128(TestA),_mm256_set_epi64x(0ULL,0ULL,0x5555555555555555,0x5555555555555555));
	Test(_mm256_lrs_192(TestA),_mm256_set_epi64x(0ULL,0ULL,0ULL,0x5555555555555555));

	Test(_mm256_lrs_64(TestB),_mm256_set_epi64x(0ULL,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA));
	Test(_mm256_lrs_128(TestB),_mm256_set_epi64x(0ULL,0ULL,0xAAAAAAAAAAAAAAAA,0xAAAAAAAAAAAAAAAA));
	Test(_mm256_lrs_192(TestB),_mm256_set_epi64x(0ULL,0ULL,0ULL,0xAAAAAAAAAAAAAAAA));

	Test(_mm256_lrs_64(ROne),_mm256_set_epi64x(0ULL,1ULL,0ULL,0ULL));
	Test(_mm256_lrs_128(ROne),_mm256_set_epi64x(0ULL,0ULL,1ULL,0ULL));
	Test(_mm256_lrs_192(ROne),_mm256_set_epi64x(0ULL,0ULL,0ULL,1ULL));

	Test(_mm256_lrs_64(One4),_mm256_set_epi64x(0ULL,1ULL,1ULL,1ULL));
	Test(_mm256_lrs_128(One4),_mm256_set_epi64x(0ULL,0ULL,1ULL,1ULL));
	Test(_mm256_lrs_192(One4),_mm256_set_epi64x(0ULL,0ULL,0ULL,1ULL));


	cout << "LRS Passed" << endl;

	return 0;
}