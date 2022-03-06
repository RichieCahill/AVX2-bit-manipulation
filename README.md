# AVX2-bit-manipulation
This is a library that allow bit manipulation that Intrinsics don't. This take abut 20 clock cycles by my calculations. 


Testing.pdf was genrated with 

g++ -lprofiler -lfmt -mavx -pthread -march=native ./testing.cc
CPUPROFILE=/tmp/prof.out CPUPROFILE_FREQUENCY=100000 ./a.out
pprof --edgefraction=0.0000001 --nodefraction=0.0000001 -pdf ./a.out /tmp/prof.out > Testing.pdf
