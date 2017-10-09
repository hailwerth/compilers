#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUF_SIZE 5
#define MAX_TRADES 10 //stop simulation after consuming MAX_TRADES
#define MAX_SBS 10
#define MAX_MMS 10

typedef struct {
  int num_shares;  //num shares 
  int tran_type;   // 0=sell, 1=buy
  char company;    //uppercase letter
  int sb_id;       //SB producing this trade
} trade;

/*globals*/
trade* trades[BUF_SIZE]; //shared trade buffer
pthread_mutex_t mutex;  //controls access to critical section
sem_t empty;  //number of empty buffer slots
sem_t full;   //number of full buffer slots


/*generate random integer between 1 and n*/
int gen_rand(int n) {
  if(n<1) {
    printf("Error: gen_rand called with nonpositive argument\n");
    exit(1);
  }
  return (rand()%n +1);
}

/*sleep for given number of seconds*/
void sleep_now(int sleeptime) { 
  if(sleeptime<0) {
    printf("ERROR: sleep_now called with negative argument\n");
    exit(1);
  }
  sleep(sleeptime); 
}

/*print a trade*/
void print_trade(trade *t) {
  if(t==NULL) {
    printf("ERROR: print_trade called with NULL argument\n");
    exit(1);
  }
  printf("trade ");
  if(t->tran_type) printf("BUY ");
  else printf("SELL ");
  printf("%d shares %c, from SB %d", t->num_shares, t->company, t->sb_id);
}

/*generate a random trade for an SB with the given id*/
trade *get_new_trade(int tid) {
  trade *t = (trade *)malloc(sizeof(trade));
  if(t==NULL) {
    printf("Error: malloc returned null pointer\n"); 
    exit(1); 
  }
  t->num_shares = gen_rand(99);
  t->tran_type = gen_rand(2) - 1;
  t->company = gen_rand(26) + 64;
  t->sb_id = tid;
  return t;
}

/* producer = stock broker thread */
void *sb(void *sb_id) {
}

/* consumer = market maker thread */
void *mm(void *mm_id) {
}

int main(int argc, char *argv[]) {
  srand((unsigned)time(0));

  //test: print 10 random trades
  int i = 0;
  for(; i<10; i++) {
    //sleep for random time, 1-4 seconds
    sleep_now(gen_rand(4));
    trade *t = get_new_trade(i);
    print_trade(t);
    printf("\n");
  }

  exit(0);
}

