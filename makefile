map: mapDriver.o 
	g++ -o map mapDriver.o

mapDriver.o: mapDriver.cpp Map.h
	g++ -c mapDriver.cpp

rm: 
	rm Map.o