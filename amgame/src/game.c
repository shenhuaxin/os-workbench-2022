#include <game.h>
#include <unistd.h>
#define FPS          60
#define SIDE 4

// Operating system is a C program!
int main(const char *args)
{
  ioe_init();

  puts("mainargs = \"");
  puts(args); // make run mainargs=xxx
  puts("\"\n");

  splash();

  puts("Press any key to see its key code...\n");
  int x = 0, y = 0;
  int vy = 60;
  int vx = 0;
  while (1)
  {
    // 在每一个时间片，例如每 16.7ms (60 fps)
    wait_for_frame();
    splash();
    // 做完这一个时间片内需要完成的工作
    draw_tile(x, x, SIDE, SIDE, 0xffffff);
    x = x + vx/FPS;
    y = y + vy/FPS;
    draw_tile(x, x, SIDE, SIDE, 0xFFA500);
  }
  return 0;
}

static int gtime;

static inline int uptime_ms() {
  return io_read(AM_TIMER_UPTIME).us / 1000;
}

void wait_for_frame() {
  int cur = uptime_ms();
  while (cur - gtime < 1000 / FPS) {
    cur = uptime_ms();
  }
  gtime = cur;
}