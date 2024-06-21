# Instructions for compilation:
# 
# 1. execute "make prepare" to prepare directory
# 2. execute "make" to build executable
# 3. execute "make clean" to clear temporary files and rebuild from scratch
# 

CXX := g++
CXXFLAGS := -o

TEMP := temp/
OBJECTS := $(TEMP)stream.o $(TEMP)context.o $(TEMP)semantic.o

main: main.cpp $(OBJECTS)
	$(CXX) $(CXXFLAGS) reader.exe $(OBJECTS) main.cpp

$(TEMP)stream.o: stream.cpp stream.hpp
	$(CXX) -c $(CXXFLAGS) $(TEMP)stream.o stream.cpp

$(TEMP)context.o: context.cpp context.hpp stream.hpp
	$(CXX) -c $(CXXFLAGS) $(TEMP)context.o context.cpp

$(TEMP)semantic.o: semantic.cpp semantic.hpp context.hpp stream.hpp
	$(CXX) -c $(CXXFLAGS) $(TEMP)semantic.o semantic.cpp

prepare:
	mkdir temp

clean:
	cd temp & del /q /s "*.o" & cd .. & $(MAKE) --no-print-directory main