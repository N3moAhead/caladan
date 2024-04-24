#include <stdlib.h>
#include "util/sdl.h"
#include "component/homescreen.h"

int main()
{
  init_sdl();
  // Moving to the homescreen main loop
  homescreen();
  return EXIT_SUCCESS;
}
