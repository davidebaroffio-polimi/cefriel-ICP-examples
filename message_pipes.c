#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>

int fd[2];

void send() {
  close(fd[0]); // close the read fd


  char *buf = "Hello world!";
  printf("Sender: Sending message...\n");
  write(fd[1], buf, strlen(buf));
}

void recv() {
  char buf[1000];
  close(fd[1]); // close the write fd

  int bytes_read = read(fd[0], buf, 1000-1);
  if (bytes_read>=0) {
    buf[bytes_read] = '\0';
  }

  printf("Receiver: Received message %s\n", buf);
}

int main() {
  pipe(fd);

  pid_t pid = fork(); 
  if (pid == 0) {
    send();
  } else {
    recv();
  }

}