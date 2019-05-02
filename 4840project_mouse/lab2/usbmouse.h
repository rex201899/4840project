#ifndef _USBMOUSE_H
#define _USBMOUSE_H

#include <libusb-1.0/libusb.h>

#define USB_HID_MOUSE_PROTOCOL 2

// /* Modifier bits */
// #define USB_LCTRL  (1 << 0)
// #define USB_LSHIFT (1 << 1)
// #define USB_LALT   (1 << 2)
// #define USB_LGUI   (1 << 3)
// #define USB_RCTRL  (1 << 4)
// #define USB_RSHIFT (1 << 5)
// #define USB_RALT   (1 << 6) 
// #define USB_RGUI   (1 << 7)

/* Modifier bits */
#define USB_LCTRL  (1 << 0)

struct usb_mouse_packet {
  // uint8_t modifiers;
  // uint8_t reserved;
  // uint8_t keycode[6];
  uint8_t modifiers;
  uint8_t pos_x;
  uint8_t pos_y;
};

/* Find and open a USB keyboard device.  Argument should point to
   space to store an endpoint address.  Returns NULL if no keyboard
   device was found. */
extern struct libusb_device_handle *openmouse(uint8_t *);

#endif
