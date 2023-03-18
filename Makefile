all: 
	creditrating

creditrating: 
	g++ *.cpp -std=c++11 -o creditrating.bin

clean: 
	rm creditrating.bin