# AVX2-bit-manipulation
This is a library that allow bit manipulation that Intrinsics don't.  

## Working Intrinsics
###	Logical Left Shift
```
__m256i _mm256_lls_mm256(__m256i n, int64_t s)
```

- This will left shift an AVX register s number of bit to the left
- The input are a __m256i and a int64_t


###	Logical Right Shift
```
__m256i _mm256_lrs_mm256(__m256i n, int64_t s)
```
- This will right shift an AVX register s number of bit to the right
- The input are a __m256i and i int int64_t


<details><summary>Backend Intrinsics</summary>
<p>
## Backend Intrinsics 
###	Logical Left Shift
```
_mm256_lls_mm256_helper(__m256i n, int64_t s)
```
- This will left shift an AVX register s number of bit upto 64 to the left
- The input are a __m256i and a int64_t

```
_mm256_lls_64(__m256i n)
```
- This will left shift an AVX register 64 bit to the left
- The input is a __m256i
```
_mm256_lls_128(__m256i n)
```
- This will left shift an AVX register 128 bit to the left
- The input is a __m256i
```
_mm256_lls_192(__m256i n)
```
- This will left shift an AVX register 192 bit to the left
- The input is a __m256i


###	Logical Right Shift
```
_mm256_lrs_mm256_helper(__m256i n, int64_t s)
```
- This will right shift an AVX register s number of bit upto 64 to the right
- The input are a __m256i and a int64_t
```
_mm256_lrs_64(__m256i n)
```
- This will right shift an AVX register 64 bit to the right
- The input is a __m256i
```
_mm256_lrs_128(__m256i n)
```
- This will right shift an AVX register 128 bit to the right
- The input is a __m256i
```	
_mm256_lrs_192(__m256i n)
```
- This will right shift an AVX register 192 bit to the right
- The input is a __m256i

</p>
</details>

Benchmarking.txt contains all the testing i did while optimizing Left Shift