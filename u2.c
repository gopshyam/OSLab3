#include "ucode.c"
int color;

main()
{ 
   printf("I am in Umode segment=%s\n", getcs());
   while(1);
}

