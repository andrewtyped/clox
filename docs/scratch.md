disassemble int into bits:

```c
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

int main() {
    int foo = 198278;
    uint8_t p1 = ((unsigned)foo & 0x00ff0000) >> 16;
    uint8_t p2 = ((unsigned)foo & 0x0000ff00) >> 8;
    uint8_t p3 = (unsigned)foo & 0x000000ff;
    uint32_t bar = 0x000000ff;
    uint32_t bat = (unsigned)foo & 0x0000ff00;
  printf("p1: %d\n",p1);
  printf("p2: %d\n",p2);
  printf("p3: %d\n",p3);
  printf("bar: %u\n",bar);
  printf("bat: %u\n",bat);

  int reassembled = p1 * 256 * 256 + p2 * 256 + p3;

  printf("reassembled: %d\n",reassembled);
}
  
```