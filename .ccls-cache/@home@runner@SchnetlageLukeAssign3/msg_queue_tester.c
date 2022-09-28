/* Luke Schnetlage
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
/*
1. Declare a pthread_t variable for each of the sending and receiving threads.
2. Declare a msg_queue structure and initialize it using mq_init.
3. Declare a thread_args structure for each of the sending and receiving threads and initialize them using thread_args_init.
4. Start each of the sending threads using pthread_create, the send_msgs functions, and the appropriate thread_args structure.
5. Start each of the receiving threads using pthread_create, the receive_msgs function, and the appropriate thread_args structure.
6. Wait for each of the sending and receiving threads to complete using pthread_join.
*/
int main(int argc, char *argv[]) {
  /* YOUR CODE HERE */
}

/* Initialize thread_args structure */
void thread_args_init(struct thread_args *args, int t_id, int num_msgs,
		      struct msg_queue * mq) {
  /* YOUR CODE HERE */
}


/* Function for sending thread to execute */
/*
1.Cast the void pointer args to a pointer to a thread_args structure using the following statement:
  struct thread_args * real_args = (struct thread_args *) args;
2. Declare a mq_msg structure.
3. Send the number of messages specified in the thread_args structure by repeatedly doing the following:
  a. Initialize the mq_msg structure with the appropriate thread id and message id.
  b. Send the message to the queue in the thread_args structure using mq_send.
4. Return NULL.
*/
void * send_msgs(void * args) {
  /* YOUR CODE HERE */
}


/* Function for receiving thread to execute */
/*
1. Cast the void pointer args to a pointer to a thread_args structure.
2. Declare a mq_msg structure.
3. Receive the number of messages specified in the thread_args structure by repeatedly doing the following:
  a. Receive the message from the queue in the thread_args structure using mq_receive.
  b. Display the message along with the receiver thread id from the thread_args structure.
4. Return NULL
*/
void * receive_msgs(void * args) {
  /* YOUR CODE HERE */
}
