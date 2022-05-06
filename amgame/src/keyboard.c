#include <game.h>

#define KEYNAME(key) \
  [AM_KEY_##key] = #key,
static const char *key_names[] = {
  AM_KEYS(KEYNAME)
};

static int x, y = 0;

void print_key() {
  int SIDE = 16;
  AM_INPUT_KEYBRD_T event = { .keycode = AM_KEY_NONE };
  ioe_read(AM_INPUT_KEYBRD, &event);
  if (event.keycode != AM_KEY_NONE && event.keydown) {
    puts("Key pressed: ");
    puts(key_names[event.keycode]);
    puts("\n");
    // if (strcmp(key_names[event.keycode], "W") == 0)
    // {
    //   if (y > 0)
    //   {
    //     y--;
    //   }
    // }
    // if (strcmp(key_names[event.keycode], "A") == 0)
    // {
    //   if (x > 0)
    //   {
    //     x--;
    //   }
    // }
    // if (strcmp(key_names[event.keycode], "S") == 0)
    // {
    //   if (y < 30)
    //   {
    //     y++;
    //   }
    // }
    // if (strcmp(key_names[event.keycode], "D") == 0)
    // {
    //   if (x < 40)
    //   {
    //     x++;
    //   }
    // }
    draw_tile(x*SIDE, y*SIDE, SIDE, SIDE, 0x00ff99);
  }
}
