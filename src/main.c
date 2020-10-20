#include <stdio.h>
#include <load_Image/load.h>

int main(int argc, char **argv)
{
  printf("UnRead 0.1.0\n");
  if(create_window(argc, argv) != 0){
      printf("GTK doesn't work.\n");
  }

  return 0;
}
