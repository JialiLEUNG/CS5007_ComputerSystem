///*
// * test_thread.c
// *
// * This file illustrates the use of pthreads in C.
// *
// *  Created on: Apr 8, 2018
// *      Author: philip Gust
// */
//
//#include <stdlib.h>
//#include <stdio.h>
//#include <pthread.h>
//
///** data shared by the thread */
//int sum;
//
///**
// * Thread will begin control in this function,
// * which computes the sum of the integers between
// * 1 and the value of the input parameter. Stores its
// * result in global sum.
// *
// * @param param the integer pointed to by param
// * @return pointer to result value (unused)
// */
//void *runner(void *param) { //
//	sum = 0;  // initialize global
//	int upper = *(int*)param; // cast a void * to an int *
//
//	for (int i = 1; i <= upper; i++) {
//		sum += i;
//	}
//
//	pthread_t tid = pthread_self();
//
//
//	printf("runner() [thread %lu]: sum is %d\n", (unsigned long)tid, sum);
//
//	// return pointer to sum that pthread_join can retrieve
//	pthread_exit(&sum);  // or use function return value
//}
//
///**
// * This function reads a non-negative value parameter
// * and runs a thread that sets global sum to the sum of
// * numbers between 1 and that value.
// */
//int main(int argc, char *argv[]) {
//	if (argc != 2) { //argc there is always a one?
//		fprintf(stderr, "usage: %s max_value\n", argv[0]);
//		return EXIT_FAILURE;
//	}
//	int maxval = atoi(argv[1]);
//	if (maxval < 0) {
//		fprintf(stderr, "%d must be >= 0\n", maxval);
//		return EXIT_FAILURE;
//	}
//
//	// initialize thread attributes
//    pthread_attr_t attr; // STRUCT
//	pthread_attr_init(&attr); // & means takes the address (pass by reference, pointer?)
//
//	// create the thread
//	pthread_t tid;
//	printf("main(): running thread to compute sum from 1 to %d\n", maxval);
//	int status = pthread_create(&tid, &attr, runner, &maxval); // functions are pointers
//	            // pthread not only create, but also run the thread.
//	if (status != 0) {
//		fprintf(stderr, "thread not created: error=%d", status);
//		return EXIT_FAILURE;
//	}
//	pthread_t main_tid = pthread_self(); // it's like get_pid()
//	printf("main(%lu): created thread %lu: waiting for it to exit\n",
//			(unsigned long)main_tid, (unsigned long)tid);
//	// unsigned/signed char, int, long, longlong. (no guarantee to be as long as "longlong"
//	// in python and java, they have virtual machine, there is a guarantee to be some bytes.
//
//
//	// wait for thread to exit
//	void *sumptr; //check void *?
//	status = pthread_join(tid, &sumptr);  // result also returned here
//	if (status != 0) {
//		fprintf(stderr, "thread exited with status %d\n", status);
//		return EXIT_FAILURE;
//	}
//
//	// report sum
//	printf("main(): thread %lu exited normally\n", (unsigned long)tid);
//	printf("global sum = %d\n", sum);
//	if (sumptr != NULL) {
//		printf("thread returned sum = %d\n", *(int*)sumptr); // ask to return a pointer
//		                                    // cast a void * to an int *.
//		                                    // treated as a pointer to an integer.
//		                                    // and then fetching the value of sumptr.s
//	}
//
//	return EXIT_SUCCESS;
//}
