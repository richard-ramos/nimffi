#include <stdint.h>

typedef struct Buffer {
  uintptr_t len;
  const uint8_t *ptr;
} Buffer;

typedef struct Result {
  Buffer singleBuff;

  uintptr_t lenBuffArr;
  Buffer * ptrBuffArr;
} Result;

void my_func(struct Result *r);

void free_result(struct Result *r);

