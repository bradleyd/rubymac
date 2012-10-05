/*
 * =====================================================================================
 *
 *       Filename:  rubymac.c
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

//TODO: mac address pairs need colons :

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
  /* Create pointer to iface */
  char *ethernet = RSTRING_PTR(iface);

  /* Allocate space for the mac address */
  char *ret = malloc(MAC_STRING_LENGTH);
  if(ret == NULL){
    perror("out of memory when creating mac addr *p\n");
    exit(1);
  }
  
  /* coutner for addres */
  int i;

  struct ifreq s;
  int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
  
  /* TODO: allow empty parameter for iface */
  if(RSTRING_LEN(iface) == 0) {
    perror("Please pass ethernet device name ex.[eth0]");
    return rb_str_new2("Please pass ethernet device name ex.[eth0]");
  }

  /* Copy iface into structure  */
  strcpy(s.ifr_name, ethernet);
  if (fd >= 0 && ret && 0 == ioctl(fd, SIOCGIFHWADDR, &s))
  {
    for (i = 0; i < 6; ++i)
      /* Copy mac address to memory one pair at a time */
      snprintf(ret+i*2,MAC_STRING_LENGTH-i*2,"%02x",(unsigned char) s.ifr_addr.sa_data[i]);
  }
  else
  {
    /*  Could not find ehternet address  */
    perror("socket/ioctl failed");
    return Qfalse;
  }

  /* Return mac address */
  return rb_str_new2(ret);
}
