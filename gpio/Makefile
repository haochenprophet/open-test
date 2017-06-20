
MK_TAG = $(main)_gpio

CFLAGS +=\
	-std=gnu++11 \
	-DLINUX_OS -D$(main)_gpio_TEST=1\
	-o $(MK_TAG) *.cpp \

all : 
	g++ $(CFLAGS)

clean :
	rm -f $(MK_TAG) *.o *~