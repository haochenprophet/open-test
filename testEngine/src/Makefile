src := $(shell ls *.cpp)
objs := $(patsubst %.cpp ,%.o , $(src) )

testEngine : $(objs)
	g++ -o $@ $^

%.O:%.cpp
	g++ -c -o $@ $<
	
clean:
	rm -f testEngine *.o