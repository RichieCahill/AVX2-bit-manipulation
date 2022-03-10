# AVX2-bit-manipulation
This is a library that allow bit manipulation that Intrinsics don't.

## Working Intrinsics
###	Logical Left Shift
```
__m256i _mm256_lls_mm256(__m256i n, int64_t s)
```

- This left shifts an AVX register n by s number of bits
- The input are a __m256i and a int64_t


###	Logical Right Shift
```
__m256i _mm256_lrs_mm256(__m256i n, int64_t s)
```
- This right shift an AVX register n by s number of bits
- The input are a __m256i and i int int64_t


<details><summary>Backend Intrinsics</summary>

## Backend Intrinsics
###	Logical Left Shift
```
_mm256_lls_mm256_helper(__m256i n, int64_t s)
```
- This left shifts an AVX register n by s number of bits up to 64
- The input are a __m256i and a int64_t

```
_mm256_lls_64(__m256i n)
```
- This left shifts an AVX register n by 64 bits
- The input is a __m256i
```
_mm256_lls_128(__m256i n)
```
- This left shifts an AVX register n by 128 bits
- The input is a __m256i
```
_mm256_lls_192(__m256i n)
```
- This left shifts an AVX register n by 192 bits
- The input is a __m256i


###	Logical Right Shift
```
_mm256_lrs_mm256_helper(__m256i n, int64_t s)
```
- This right shifts an AVX register n by s number of bits up to 64
- The input are a __m256i and a int64_t
```
_mm256_lrs_64(__m256i n)
```
- This right shifts an AVX register n by 64 bits
- The input is a __m256i
```
_mm256_lrs_128(__m256i n)
```
- This right shifts an AVX register n by 128 bits
- The input is a __m256i
```
_mm256_lrs_192(__m256i n)
```
- This right shifts an AVX register n by 192 bits
- The input is a __m256i
</details>
Benchmarking.txt contains all the testing i did while optimizing Left Shift