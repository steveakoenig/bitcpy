#ifndef BITCPY_H
#define BITCPY_H

#include <stdio.h>
/*
 * Bitwise variant of memcpy. Instead of giving the number of bytes to copy from src to dest 
 * bitcpy copies that number of bits. When partial bytes are being copied the bits outside the
 * range to be copied will be left unchanged.
 * This is thread safe, and not safe to use when memory areas overlap. (see man 3 memcpy)
 * On a little endian system this results in the most significant bits in the partial bytes to 
 * be overridden first. To change this simply reverse the shifts of the keeper and update bitmasks
 */
void bitcpy(void *dest, const void *src, size_t n)
{
   size_t num_whole_bytes = n / 8;
   size_t num_extra_bits = n % 8;

   unsigned char *whole_destinations = dest;
   const unsigned char *whole_sources = src;

   // overwrite the whole bytes first
   for (int i = 0; i < num_whole_bytes; ++i)
   {
      whole_destinations[i] = whole_sources[i];
   }

   if (num_extra_bits == 0)
   {
      // nothing would be changed, so just
      return;
   }

   unsigned char *partial_destination = whole_destinations + num_whole_bytes;
   const unsigned char *partial_source = whole_sources + num_whole_bytes;

   // bit mask with the bits being kept set to 1
   // use left shift here to update the LSB first 
   unsigned char keeper_bit_mask = 0xFF;
   keeper_bit_mask >>= num_extra_bits;

   // bit mask with the bits being copied set to 1
   // use right shift here to update the LSB first 
   unsigned char update_bit_mask = 0xFF;
   update_bit_mask <<= (8 - num_extra_bits);


   // set the bits we will copy over to 0
   *partial_destination &= keeper_bit_mask;

   // update those bits from the partial source byte
   *partial_destination |= (update_bit_mask & *partial_source);
}

#endif // BITCPY_H
