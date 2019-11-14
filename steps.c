

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include <pigpiod_if2.h>

#define PHASE1  14
#define PHASE2  15
#define PHASE3  17
#define PHASE4  18

#define OFF     0
#define ON      1

#define NUM_OF_STEPS 4096



bool half_Step_Sequence[8][4] = {{0,0,1,0},
			       {0,1,1,0},
			       {0,1,0,0},
			       {1,1,0,0},
			       {1,0,0,0},
			       {1,0,0,1},
			       {0,0,0,1},			       
			       {0,0,1,1}};
int phases[4] = {PHASE1, PHASE2, PHASE3, PHASE4};

void oneCycle(int fd) {
  int i,j;
  for (i=0;i<8;i++) {
    for (j=0;j<4;j++) 
      gpio_write(fd, phases[j],half_Step_Sequence[i][j]);
    time_sleep(0.0020);
  }
}

int main(int argc, char ** argv) {
  int i,Ekoo;
  int fd=-1;
  
  if ((fd=pigpio_start(NULL,NULL)) < 0) {
    printf("Could not open connection to pigpiod\n");
    printf("%s\n",pigpio_error(fd));
    return -1;
  }
  
  printf("Message: The Connection to pigpiod has been opened successfully\n");

  for (i=0;i<4;i++) {
    if ((Ekoo=set_mode(fd,phases[i],PI_OUTPUT)) < 0) {
      printf("Could not set phase to the output\n",i);
      printf("%s\n",pigpio_error(Ekoo));
      return -1;
    }
  }

  for (i=0;i<NUM_OF_STEPS/8;i++) 
    oneCycle(fd);  
  return 0;
}
