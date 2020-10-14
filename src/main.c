#include <stdio.h>
#include <load_Image/load.h>

int main(void)
{
  printf("UnRead 0.1.0\n");
  load_Image();
  int n = nb_Random();
  printf("Votre nombre est : %d", n);

  return 0;
}
