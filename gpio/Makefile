
MK_TAG = gpio

CFLAGS +=\
	-std=gnu++11 \
	-DLINUX_OS \
	-o $(MK_TAG) *.cpp \

all : 
	g++ $(CFLAGS)

clean :
	rm -f $(MK_TAG) *.o *~