/*
 *
 * CSEE 4840 project mouse for 2019
 *
 * Zhongtai Ren, zr2208
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "usbmouse.h"


#define BUFFER_SIZE 128

struct libusb_device_handle *mouse;
uint8_t endpoint_address;

int main()
{
  int err, col;
  int flg1;
  // struct sockaddr_in serv_addr;

  struct usb_mouse_packet packet;
  int transferred;
  char keystate[12];

  /* Open the mouse */
  if ( (mouse = openmouse(&endpoint_address)) == NULL ) {
    fprintf(stderr, "Did not find a mouse\n");
    exit(1);
  }
    

  for (;;) 
  {
    flg1 = libusb_interrupt_transfer(mouse, endpoint_address,
			      (unsigned char *) &packet, sizeof(packet),
			      &transferred, 0);
    // printf("%d\n", flg1);
    

    if (transferred == sizeof(packet)) {
      sprintf(keystate, "%02x %02x %02x", packet.modifiers, packet.pos_x,
	      packet.pos_y);
      printf("%s\n", keystate);
      if (packet.pos_y == 0x29) { /* ESC pressed? */
	       break;
      }
    }
  }

  return 0;
}
