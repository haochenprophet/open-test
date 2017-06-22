
MK_TAG = object

CFLAGS +=\
	-std=gnu++11 \
	-DLINUX_OS -DOBJECT_TEST=1\
	-o $(MK_TAG) *.cpp \
	-lpthread \

all : 
	g++ $(CFLAGS)

clean :
	rm -f $(MK_TAG) *.o *~