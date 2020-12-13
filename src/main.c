
#include "image/set.h"

int main(void)
{

  enum sp_error error = SP_SUCCESS;

  struct s_set set = st_import("test/dataset/train-images-idx3-ubyte",
                               "test/dataset/train-labels-idx1-ubyte",
                               &error);

  if (error)
  {
    printf("cant create set : %i\n", error);
    return error;
  }

  st_print(&set);

  st_destructor(&set);
  return 0;
}
