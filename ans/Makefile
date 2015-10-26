all: shortest-palindrome.cc ../../common/kmp/kmp.cc
	g++ -Wall -std=c++11 shortest-palindrome.cc -c -I/home/pei/git-leetcode/
	g++ -Wall -std=c++11 ../../common/kmp/kmp.cc -c
	g++ -Wall -std=c++11 shortest-palindrome.o kmp.o -o sp

clean:
	rm *.o *~ sp
