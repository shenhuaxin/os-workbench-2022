#include <game.h>

#define KEYNAME(key) \
  [AM_KEY_##key] = #key,
// static const char *key_names[] = {
//   AM_KEYS(KEYNAME)
// };

void print_key() {
  int SIDE = 16;
  AM_INPUT_KEYBRD_T event = { .keycode = AM_KEY_NONE };
  ioe_read(AM_INPUT_KEYBRD, &event);
  if (event.keycode != AM_KEY_NONE && event.keydown) {
    // puts("Key pressed: ");
    // puts(key_names[event.keycode]);
    // puts("\n");
    draw_tile(0*SIDE, 0*SIDE, SIDE, SIDE, 0x00ff99);
  }
}
