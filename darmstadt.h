#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <drm.h>
#include <va/va_drm.h>
#include <va/va_drmcommon.h>
#include <xf86drm.h>
#include <xf86drmMode.h>
#include <stdexcept>
#include <string>
#include <queue>

#define DEVICE_PATH "/dev/dri/card0"

typedef std::string string;

bool operator ==(const struct timespec& l, const struct timespec& r);
bool operator >(const struct timespec& l, const struct timespec& r);
bool operator <(const struct timespec& l, const struct timespec& r);
struct timespec operator +(const struct timespec& l, const struct timespec& r);
struct timespec operator -(const struct timespec& l, const struct timespec& r);
struct timespec operator +(const struct timespec& l, const long& r);
struct timespec operator -(const struct timespec& l, const long& r);
struct timespec mkts(time_t sec, long nsec);
struct timespec stots(string s);
string tstos(struct timespec ts);
struct timespec curTime(clockid_t clockSource);

struct qFrame {
  int fd;
  unsigned int format, pitch;
  size_t objsize;
  struct timespec ts;
  qFrame(int a, unsigned int b, unsigned int c, struct timespec d): fd(a), pitch(c), objsize(b*c), ts(d) {}
  qFrame(): fd(-1), pitch(0), objsize(0), ts(mkts(0,0)) {}
};