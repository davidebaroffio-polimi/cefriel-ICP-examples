#include <stdio.h>
#include <string.h>

#define NUM_CHUNKS 10

typedef struct {
  int begin;
  int size;
} data_t;

long res=0;

data_t data[NUM_CHUNKS];

int count_lines(data_t *data) {
  FILE *fd = fopen("file.txt", "r");
  int cnt = 0;
  
  fseek(fd, data->begin, SEEK_SET);

  for (int i=0; i < data->size; i++) {
    char c = fgetc(fd);
    if (c == '\n') cnt++;
  }
  fclose(fd);
  return cnt;
}

int main() {

  // get the size of the file
  FILE *fd = fopen("file.txt", "r");
  fseek(fd, 0, SEEK_END); // seek to end of file
  long size = ftell(fd); // get current file pointer
  fseek(fd, 0, SEEK_SET); // seek back to beginning of file
  fclose(fd);

  // this is the size of each chunk
  long chunk_size = size / NUM_CHUNKS;
  long remainder = size % NUM_CHUNKS;

  // iterate over the chunks
  for (int i=0; i<NUM_CHUNKS; i++) {
    // fill the data struct
    data[i].begin = i*chunk_size;
    data[i].size = (i == NUM_CHUNKS-1) ? chunk_size + remainder : chunk_size;
    res+=count_lines(&data[i]);
  }
  printf("There are %ld lines\n", res);
}