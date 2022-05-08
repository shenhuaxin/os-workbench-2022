#include <game.h>
#include <unistd.h>
#define FPS          60

// Operating system is a C program!
int main(const char *args)
{
  ioe_init();

  puts("mainargs = \"");
  puts(args); // make run mainargs=xxx
  puts("\"\n");

  splash();

  puts("Press any key to see its key code...\n");
  uint32_t color = 0x00ff00;
  while (1)
  {
    // 在每一个时间片，例如每 16.7ms (60 fps)
    wait_for_frame();

    // 做完这一个时间片内需要完成的工作
    // int scanlines = 262;
    // while (scanlines-- > 0)
    // {
    //   ppu_cycle();      // 更新游戏图像
    //   psg_detect_key(); // 读取按键，更新游戏逻辑
    // }
    color = color + 100;
    splash_color(color);
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