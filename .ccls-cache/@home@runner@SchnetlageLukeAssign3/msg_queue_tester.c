/* Luke Schnetlage
 * CSCI 4100 Assignment 3
 * This program tests a message queue by creating multiple sending and
 * receiving threads
 */

#include "msg_queue.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// 36 messages total
#define THREAD_COUNT 6
#define MESSAGES 6

/* Structure to hold thread arguments */
struct thread_args {
  int t_id;             // id number for the thread
  int num_msgs;         // number of messages for the thread to send or receive
  struct msg_queue *mq; // pointer to the queue that the thread will use to send
                        // or receive messages
};

/* Function prototypes */
void thread_args_init(struct thread_args *args, int t_id, int num_msgs,struct msg_queue *mq);
void *send_msgs(void *args);
void *receive_msgs(void *args);

/* Main function */
int main(int argc, char *argv[]) {
  // Declare a pthread_t variable for each of the sending and receiving threads
  pthread_t s_thread[THREAD_COUNT]; // send threads
  pthread_t r_thread[THREAD_COUNT]; // receive threads

  // Declare a msg_queue structure and initialize it using mq_init.
  struct msg_queue queue;
  mq_init(&queue);

  // Declare a thread_args structure for each of the sending and receiving
  // threads
  struct thread_args s_args[THREAD_COUNT];
  struct thread_args r_args[THREAD_COUNT];

  // initialize them using thread_args_init
  for (int i = 0; i < MESSAGES; i++) {
    thread_args_init(&s_args[i], i, MESSAGES, &queue);
    thread_args_init(&r_args[i], i, MESSAGES, &queue);
  }

  for (int i = 0; i < THREAD_COUNT; i++) {
    /* 
    Start each of the sending threads using pthread_create, the send_msgs
    functions, and the appropriate thread_args structure.
    */
    pthread_create(&s_thread[i], NULL, send_msgs, &s_args[i]);
    /*
    Start each of the receiving threads using pthread_create, the
    receive_msgs function, and the appropriate thread_args structure.
    */
    pthread_create(&r_thread[i], NULL, receive_msgs, &r_args[i]);
  }

  for (int i = 0; i < THREAD_COUNT; i++) {
    // Wait for each of the sending and receiving threads to complete using pthread_join.
    pthread_join(s_thread[i], NULL);
    pthread_join(r_thread[i], NULL);
  }
}

/* Initialize thread_args structure */
void thread_args_init(struct thread_args *args, int t_id, int num_msgs,struct msg_queue *mq) {
  args->t_id = t_id;
  args->num_msgs = num_msgs;
  args->mq = mq;
}

/* Function for sending thread to execute */
void *send_msgs(void *args) {
  // Cast the void pointer args to a pointer to a thread_args structure
  struct thread_args *real_args = (struct thread_args *)args;

  // Declare a mq_msg structure
  struct mq_msg s_message;

  // Send the number of messages specified in the thread_args structure by
  // repeatedly doing the following:
  for (int i = 0; i < real_args->num_msgs; i++) {
    // Initialize the mq_msg structure with the appropriate thread id and
    // message id.
    s_message.t_id = real_args->mq->messages[i].t_id;
    s_message.m_id = real_args->mq->messages[i].m_id;

    // Send the message to the queue in the thread_args structure using mq_send.
    mq_send(real_args->mq, &s_message);
  }

  // Return NULL
  return NULL;
}

/* Function for receiving thread to execute */
void *receive_msgs(void *args) {
  // Cast the void pointer args to a pointer to a thread_args structure.
  struct thread_args *real_args = (struct thread_args *)args;

  // Declare a mq_msg structure.
  struct mq_msg r_message;

  // Receive the number of messages specified in the thread_args structure by
  // repeatedly doing the following:
  for (int i = 0; i < real_args->num_msgs; i++) {
    // Receive the message from the queue in the thread_args structure using
    // mq_receive.
    mq_receive(real_args->mq, &r_message);

    // Display the message along with the receiver thread id from the
    // thread_args structure.
    printf("[Sender: %d, Message id: %d, Receiver: %d]\n", r_message.t_id,r_message.m_id,real_args->t_id); 
  }

  // Return NULL
  return NULL;
}

// gcc -o mqt msg_queue_tester.c msg_queue.c -lpthread
// gdb mqt