CFLAGS = -Wall

OBJECTS = lab2.o usbmouse.o

TARFILES = Makefile lab2.c \
	usbmouse.h usbmouse.c \
	chat_server.py

lab2 : $(OBJECTS)
	cc $(CFLAGS) -o lab2 $(OBJECTS) -lusb-1.0 -pthread

lab2.tar.gz : $(TARFILES)
	rm -rf lab2
	mkdir lab2
	ln $(TARFILES) lab2
	tar zcf lab2.tar.gz lab2
	rm -rf lab2

lab2.o : lab2.c usbmouse.h
usbmouse.o : usbmouse.c usbmouse.h

.PHONY : clean
clean :
	rm -rf *.o lab2
