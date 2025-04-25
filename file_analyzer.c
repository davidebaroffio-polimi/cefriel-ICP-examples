#include <stdio.h>
#include <string.h>

#define NUM_CHUNKS 10

long res=0;

void count_lines(FILE *fd, int begin, int size) {
  fseek(fd, begin, SEEK_SET);

  for (int i=0; i < size; i++) {
    char c = fgetc(fd);
    if (c == '\n') res++;
  }
}

int main() {
  FILE *fd = fopen("file.txt", "r");
  fseek(fd, 0, SEEK_END); // seek to end of file
  long size = ftell(fd); // get current file pointer
  fseek(fd, 0, SEEK_SET); // seek back to beginning of file

  long chunk_size = size / NUM_CHUNKS;
  long remainder = size % NUM_CHUNKS;
  for (int i=0; i<NUM_CHUNKS-1; i++) {
    count_lines(fd, i*chunk_size, chunk_size);
  }
  count_lines(fd, (NUM_CHUNKS-1)*chunk_size, chunk_size + remainder);
  printf("There are %ld lines\n", res);
}