/*
 * =====================================================================================
 *
 *       Filename:  get_mac.c
 *
 *    Description: get mac address of nix* 
 *
 *        Version:  1.0
 *        Created:  10/05/2012 01:09:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Brad smith (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include "ruby.h"

#define MAC_STRING_LENGTH 13

// Defining a space for information and references about the module to be stored internally
VALUE RubyMac = Qnil;

// Prototype for the initialization method - Ruby calls this, not you
void Init_rubymac();

// Prototype for our method 'test1' - methods are prefixed by 'method_' here
static VALUE method_address(VALUE self, VALUE iface);

// The initialization method for this module
void Init_rubymac() {
   RubyMac = rb_define_class("RubyMac", rb_cObject);
   rb_define_method(RubyMac, "address", method_address, 1);
 }

static VALUE method_address(VALUE self, VALUE iface){
  char *ethernet = RSTRING_PTR(iface);
  char *ret = malloc(MAC_STRING_LENGTH);
  struct ifreq s;
  int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);

  strcpy(s.ifr_name, ethernet);
  if (fd >= 0 && ret && 0 == ioctl(fd, SIOCGIFHWADDR, &s))
  {
    int i;
    for (i = 0; i < 6; ++i)
      snprintf(ret+i*2,MAC_STRING_LENGTH-i*2,"%02x",(unsigned char) s.ifr_addr.sa_data[i]);
  }
  else
  {
    perror("malloc/socket/ioctl failed");
    exit(1);
  }
  return rb_str_new2(ret);
}

//VALUE method_address(VALUE self, VALUE interface) {
//  struct ifreq s;
//  int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
//
//  strcpy(s.ifr_name, interface);
//  if (0 == ioctl(fd, SIOCGIFHWADDR, &s)) {
//    int i;
//    for (i = 0; i < 6; ++i)
//      printf(" %02x", (unsigned char) s.ifr_addr.sa_data[i]);
//    puts("\n");
//    return INT2NUM(0);
//  }
//  return INT2NUM(1);
//}
