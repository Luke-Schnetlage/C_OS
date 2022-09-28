/* Luke Schnetlage
 * CSCI 4100 Assignment 3
 * Source file for message queue implementation
 */

#include "msg_queue.h"
#include <pthread.h>

/*
The in and out variables are initialized to zero.
See the section on POSIX Threads, Locks, and Condition Variables for how to initialize the lock and condition variables.
*/
/* Initialize the message queue */
void mq_init(struct msg_queue * mq) {
  mq->in = 0;
  mq->out = 0;
  
  pthread_mutex_init(&mq->lock, NULL);
  pthread_cond_init(&mq->msg_added, NULL);
  pthread_cond_init(&mq->msg_removed, NULL);
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
  
  pthread_mutex_lock(&mq->lock); //Acquire the queue lock

  if ((&mq->in - &mq->out) > 10){ //While the queue is full, wait on the queue’s msg_removed condition variable
    pthread_cond_wait(&mq->msg_removed, &mq->lock);
  }

  //Copy the message from the mq_msg structure provided to the correct location in the queue.
  mq->messages[(&mq->in - &mq->out)%10] = *message;
  
  mq->in++; //Increment the queue’s in member variable.
  pthread_cond_signal(&mq->msg_added);//Signal the queue’s msg_added condition variable.
  pthread_mutex_unlock(&mq->lock);//Release the queue lock.
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
  pthread_mutex_lock(&mq->lock); //Acquire the queue lock

  //While the queue is empty, wait on the queue’s msg_added condition variable
  if ((&mq->in - &mq->out) < 1){ 
    pthread_cond_wait(&mq->msg_added, &mq->lock);
  }
  
  
  //Copy the message from the correct location in the queue to the mq_msg structure provided.
  *message = mq->messages[(&mq->in - &mq->out)%10];
  
  mq->out++;//Increment the queue’s out member variable.
  pthread_cond_signal(&mq->msg_removed);//Signal the queue’s msg_removed condition variable.
  pthread_mutex_unlock(&mq->lock);//Release the queue lock.
}

