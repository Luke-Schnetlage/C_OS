/* Nicholas Coleman
 * CSCI 4100 Assignment 3
 * This program tests a message queue by creating multiple sending and 
 * receiving threads
 */

#include <stdio.h>
#include <stdlib.h>
#include "msg_queue.h"
#include <pthread.h>

/* Structure to hold thread arguments */
struct thread_args {
  int t_id;
  int num_msgs;
  struct msg_queue * mq;
};

/* Function prototypes */
void thread_args_init(struct thread_args *args, int t_id, int num_msgs,
		      struct msg_queue * mq);
void * send_msgs(void * args);
void * receive_msgs(void * args);

/* Main function */
int main(int argc, char *argv[]) {
  /* YOUR CODE HERE */
}

/* Initialize thread_args structure */
void thread_args_init(struct thread_args *args, int t_id, int num_msgs,
		      struct msg_queue * mq) {
  /* YOUR CODE HERE */
}

/* Function for sending thread to execute */
void * send_msgs(void * args) {
  /* YOUR CODE HERE */
}

/* Function for receiving thread to execute */
void * receive_msgs(void * args) {
  /* YOUR CODE HERE */
}
