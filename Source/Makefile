
OBJS	= Amijo.o gradient.o InverseDecay.o main.o vector.o ExponentialDecay.o
SOURCE	= Amijo.cpp gradient.cpp InverseDecay.cpp main.cpp vector.cpp ExponentialDecay.cpp
HEADER	= Amijo.hpp gradient.hpp InverseDecay.hpp Method.hpp UpdateRule.hpp vector.hpp ExponentialDecay.hpp
OUT	= main
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = -lm


all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)


# create/compile the individual files >>separately<<
Amijo.o: Amijo.cpp
	$(CC) $(FLAGS) Amijo.cpp -std=c++17

gradient.o: gradient.cpp
	$(CC) $(FLAGS) gradient.cpp -std=c++17

InverseDecay.o: InverseDecay.cpp
	$(CC) $(FLAGS) InverseDecay.cpp -std=c++17

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -std=c++17

vector.o: vector.cpp
	$(CC) $(FLAGS) vector.cpp -std=c++17

ExponentialDecay.o: ExponentialDecay.cpp
	$(CC) $(FLAGS) ExponentialDecay.cpp -std=c++17


# clean house
clean:
	rm -f $(OBJS) $(OUT)