#include <game.h>
#include <unistd.h>
#define FPS          60
#define SIDE 16

// Operating system is a C program!
int main(const char *args)
{
  ioe_init();

  puts("mainargs = \"");
  puts(args); // make run mainargs=xxx
  puts("\"\n");

  splash();

  puts("Press any key to see its key code...\n");
  while (1)
  {
    // 在每一个时间片，例如每 16.7ms (60 fps)
    wait_for_frame();

    // 做完这一个时间片内需要完成的工作
    int scanlines = 262;
    while (scanlines-- > 0)
    {
      splash();
      // 计算球的位置
      draw_tile(0, 0, SIDE, SIDE, 0xFFA500);
      // ppu_cycle();      // 更新游戏图像
      // psg_detect_key(); // 读取按键，更新游戏逻辑
    }
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