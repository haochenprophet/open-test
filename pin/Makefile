
MK_TAG = pin

CFLAGS +=\
	-std=gnu++11 \
	-DLINUX_OS -DPIN_TEST=1\
	-o $(MK_TAG) *.cpp \

all : 
	g++ $(CFLAGS)

clean :
	rm -f $(MK_TAG) *.o *~