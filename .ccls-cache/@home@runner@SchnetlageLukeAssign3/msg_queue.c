/* Luke Schnetlage
 * CSCI 4100 Assignment 3
 * Source file for message queue implementation
 */

#include "msg_queue.h"
#include <pthread.h>

/* Initialize the message queue */
void mq_init(struct msg_queue *mq) {
  // The in and out variables are initialized to zero.
  mq->in = 0;
  mq->out = 0;

  // initialize lock
  pthread_mutex_init(&mq->lock, NULL);
  // initialize cond vars
  pthread_cond_init(&mq->msg_added, NULL);
  pthread_cond_init(&mq->msg_removed, NULL);
}

/* Send a message to a message queue */
void mq_send(struct msg_queue *mq, struct mq_msg *message) {
  // Acquire the queue lock
  pthread_mutex_lock(&mq->lock);

  if ((&mq->in - &mq->out) >=
      QUEUE_SIZE) { // While the queue is full, wait on the queue’s msg_removed
                    // condition variable
    pthread_cond_wait(
        &mq->msg_removed,
        &mq->lock); // this may be the wrong way to check queue full?
  }

  // Copy the message from the mq_msg structure provided to the correct location
  // in the queue.
  mq->messages[(int)&mq->in % QUEUE_SIZE].m_id = message->m_id;

  mq->messages[(int)&mq->in % QUEUE_SIZE].t_id = message->t_id;

  mq->in++; // Increment the queue’s in member variable.
  pthread_cond_signal(
      &mq->msg_added); // Signal the queue’s msg_added condition variable.
  pthread_mutex_unlock(&mq->lock); // Release the queue lock.
}

/* Receive a message from a message queue */
void mq_receive(struct msg_queue *mq, struct mq_msg *message) {
  pthread_mutex_lock(&mq->lock); // Acquire the queue lock

  // While the queue is empty, wait on the queue’s msg_added condition variable
  if (mq->in - mq->out == 0) {                        // &mq->in - &mq->out
    pthread_cond_wait(&mq->msg_added, &mq->lock); // also maybe wrong
  }

  // Copy the message from the correct location in the queue to the mq_msg
  // structure provided.
  message->m_id = mq->messages[(mq->out) % QUEUE_SIZE].m_id;

  message->t_id = mq->messages[(mq->out) % QUEUE_SIZE].t_id;

  mq->out++; // Increment the queue’s out member variable.
  pthread_cond_signal(
      &mq->msg_removed); // Signal the queue’s msg_removed condition variable.
  pthread_mutex_unlock(&mq->lock); // Release the queue lock.
}
