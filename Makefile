

all: project5.o CarClass.o EventClass.o IntersectionSimulationClass.o random.o
	g++ -Wall -g -o project5 project5.o CarClass.o EventClass.o IntersectionSimulationClass.o random.o

project5.o: project5.cpp IntersectionSimulationClass.h
	g++ -Wall -g -c project5.cpp

CarClass.o: CarClass.cpp CarClass.h constants.h

EventClass.o: EventClass.cpp EventClass.h constants.h

IntersectionSimulationClass.o: IntersectionSimulationClass.cpp IntersectionSimulationClass.h random.h SortedListClass.h EventClass.h FIFOQueueClass.h CarClass.h

random.o: random.cpp random.h

clean:.
	rm -f *.o project5


