src := $(shell ls *.cpp)
objs := $(patsubst %.cpp ,%.o , $(src) )

gpio: $(objs)
	g++ -O -o $@ $^

%.O:%.cpp
	g++ -O -c -o $@ $< 
	
clean:
	rm -f gpio *.o