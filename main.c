#include "bitcpy.h"

#include <stdlib.h>
#include <stdio.h>


void output_array(const char * name, void *source, size_t num_bytes)
{
   unsigned char * sourceptr = source;

   printf("%20s: ", name);

   for (size_t i = 0; i < num_bytes; ++i)
   {
      for (unsigned int bit_mask = 1 << 7; bit_mask > 0; bit_mask /= 2)
      {
         (sourceptr[i] & bit_mask) ? printf("1") : printf("0");
      }
      printf(" ");
   }
   printf("\n");
}

void print_usage(const char * executable_name)
{
   printf("usage:\n");
   printf("%s <destination number> <source number> <number of bits to copy>\n", executable_name);
   printf("Wrapper to test the bitcpy function.\n");
   printf("Source and destination should be no larger than unsigned long long format\n");
   printf("Number of bits to copy should not exceed 64 (number of bits in an unsigned long long\n");

   exit(1);
}


int main(int argc, char *argv[])
{
   if (argc < 4)
   {
      print_usage(argv[0]);
   }

   char * endptr;

   unsigned long long destination = strtoull(argv[1], &endptr, 0);
   if (*endptr != '\0')
   {
      print_usage(argv[0]);
   }

   unsigned long long source = strtoull(argv[2], &endptr, 0);
   if (*endptr != '\0')
   {
      print_usage(argv[0]);
   }

   unsigned long bits_to_copy = strtoul(argv[3], &endptr, 0);
   if (*endptr != '\0' || bits_to_copy > 64)
   {
      print_usage(argv[0]);
   }


   unsigned char *sourceptr = (unsigned char *)&source;
   unsigned char *destinationptr =(unsigned char *)&destination;

   const size_t total_length = sizeof(unsigned long long);

   output_array("source before", sourceptr, total_length);
   output_array("destinatino before", destinationptr, total_length);

   bitcpy(destinationptr, sourceptr, bits_to_copy);

   output_array("source after", sourceptr, total_length);
   output_array("destination after", destinationptr, total_length);

   return 0;
}
