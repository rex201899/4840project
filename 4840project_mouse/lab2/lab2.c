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
  // struct sockaddr_in serv_addr;
  int px = 320;
  int py = 240;
  int numx, numy;

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
    libusb_interrupt_transfer(mouse, endpoint_address,
			      (unsigned char *) &packet, sizeof(packet),
			      &transferred, 0);
    // printf("%d\n", flg1);

    if (transferred == sizeof(packet)) {
      if (packet.pos_x > 0x88) {
        numx = -(0xFF - packet.pos_x + 1);
      }
      else { numx = packet.pos_x;}

      if (packet.pos_y > 0x88) {
        numy = -(0xFF - packet.pos_y + 1);
      }
      else { numy = packet.pos_y;}

      if (px < 1) { px = 1}
      else if (px > 0 && px < 640) { px = px + numx; }
      else if (px > 639) { px = 639}
      else {px = 320}

      if (py < 1) { py = 1}
      else if (py > 0 && py < 480) { py = py + numy; }
      else if (py > 479) { px = 479}
      else {py = 240}

      printf("position of x, y are: %d %d\n",px,py);
      sprintf(keystate, "%02x %02x %02x", packet.modifiers, packet.pos_x,
	      packet.pos_y);
      // printf("%s\n", keystate);
      if (packet.pos_y == 0x29) { /* ESC pressed? */
	       break;
      }
    }
  }

  return 0;
}
