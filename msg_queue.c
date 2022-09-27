/* Luke Schnetlage
 * CSCI 4100 Assignment 3
 * Source file for message queue implementation
 */

#include "msg_queue.h"
#include <pthread.h>
/* Initialize the message queue */
void mq_init(struct msg_queue * mq) {
  /* YOUR CODE HERE */
}

/*
Acquire the queue lock.
While the queue is full, wait on the queue’s msg_removed condition variable.
Copy the message from the mq_msg structure provided to the correct location in the queue.
Increment the queue’s in member variable.
Signal the queue’s msg_added condition variable.
Release the queue lock.
*/
/* Send a message to a message queue */
void mq_send(struct msg_queue * mq, struct mq_msg * message) {
  /* YOUR CODE HERE */
}

/*
Acquire the queue lock.
While the queue is empty, wait on the queue’s msg_added condition variable
Copy the message from the correct location in the queue to the mq_msg structure provided.
Increment the queue’s out member variable.
Signal the queue’s msg_removed condition variable.
Release the queue lock.
*/
/* Receive a message from a message queue */
void mq_receive(struct msg_queue *mq, struct mq_msg * message) {
  /* YOUR CODE HERE */
}

