CXX = g++
CXXFLAGS = -O3 -std=c++11

OBJS = main.o init.o partition.o linear.o timestep.o output.o

all: antsontable

antsontable: $(OBJS)
	$(CXX) $(CXXFLAGS) -o antsontable $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o antsontable ants.txt

