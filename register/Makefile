MK_TAG = register

CFLAGS +=\
	-std=gnu++11 \
	-DLINUX_OS -DREGISTER_TEST=1\
	-o $(MK_TAG) *.cpp \

all : 
	g++ $(CFLAGS)

clean :
	rm -f $(MK_TAG) *.o *~