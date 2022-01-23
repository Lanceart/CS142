CC = g++
CFLAGS = -O3 -I../c++ -mcx16 -march=native -DCILK -fcilkplus -std=c++17

all:	integral


integral:	integral.cpp
	$(CC) $(CFLAGS) -DNDEBUG integral.cpp -o integral

	
clean:
	rm -f integral
