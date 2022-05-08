#include <game.h>

#define KEYNAME(key) \
  [AM_KEY_##key] = #key,
static const char *key_names[] = {
    AM_KEYS(KEYNAME)};

void print_key()
{
  AM_INPUT_KEYBRD_T event = {.keycode = AM_KEY_NONE};
  ioe_read(AM_INPUT_KEYBRD, &event);
  if (event.keycode != AM_KEY_NONE && event.keydown)
  {
    puts("Key pressed: ");
    puts(key_names[event.keycode]);
    puts("\r\n");
  }
}



// void test() {
//   if (strcmp(key_names[event.keycode], "W") == 0)
//     {
//       puts("pressed W \r\n");
//       if (y > 0)
//       {
//         y--;
//       }
//     }
//     else if (strcmp(key_names[event.keycode], "A") == 0)
//     {
//       puts("pressed A \r\n");
//       if (x > 0)
//       {
//         x--;
//       }
//     }
//     else if (strcmp(key_names[event.keycode], "S") == 0)
//     {
//       puts("pressed S \r\n");
//       if (y < 29)
//       {
//         y++;
//       }
//     }
//     else if (strcmp(key_names[event.keycode], "D") == 0)
//     {
//       puts("pressed D \r\n");
//       if (x < 39)
//       {
//         x++;
//       }
//     }
//     draw_tile(x * SIDE, y * SIDE, SIDE, SIDE, 0x00ff99);
// }