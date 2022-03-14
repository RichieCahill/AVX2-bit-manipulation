test.bin: testing.cc
	g++ -mavx -march=native ./testing.cc -o test.bin

