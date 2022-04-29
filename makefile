#variables
COMPILE = g++
FLAGS = 
OBJS = region.o state.o county.o day.o date.o supportLib.o pbPlots.o
OUT = source

#targets
all: main.cpp $(OBJS)
	$(COMPILE) $(FLAGS) -o $(OUT) main.cpp $(OBJS)
region.o: region.h region.cpp
	$(COMPILE) $(FLAGS) -c region.cpp
state.o: state.h state.cpp
	$(COMPILE) $(FLAGS) -c state.cpp
county.o: county.h county.cpp
	$(COMPILE) $(FLAGS) -c county.cpp
day.o: day.h day.cpp
	$(COMPILE) $(FLAGS) -c day.cpp
date.o: date.h date.cpp
	$(COMPILE) $(FLAGS) -c date.cpp
supportLib.o: supportLib.hpp supportLib.cpp
	$(COMPILE) $(FLAGS) -c supportLib.cpp
pbPlots.o: pbPlots.hpp pbPlots.cpp
	$(COMPILE) $(FLAGS) -c pbPlots.cpp
clean:
	rm -rf *.o $(OUT)
