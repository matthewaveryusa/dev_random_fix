#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>

typedef int (*real_open_t)(const char *pathname, int flags);

int open(const char *pathname, int flags) {
  char a[] = "/dev/random";
  real_open_t real_open;
  real_open = (real_open_t)dlsym(RTLD_NEXT,"open");
  if(strcmp(pathname,a) == 0) {
    return real_open("/dev/urandom", flags);
  } else {
    return real_open(pathname, flags);
  }
}
