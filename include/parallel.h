/*
 * File:   parallel.h
 * Author: dihong
 *
 * Created on September 22, 2013, 4:46 PM
 */

#ifndef PARALLEL_H
#define	PARALLEL_H
#include<vector>
#include <pthread.h>
#include <cstring>
#include "common.h"
#include "database.h"

typedef struct{
    int start_row;  //start index of this section in model_matrix
    int end_row;  //end index of this section in model_matrix
    const vector<float*>& features;  //features to be encodeded, global
    int row_features;  //total number of feature

     float*  pMax_coss;  //[out] max cosine value of all features in terms of current thread section, size: row_queries
     int* pLine_nums;  //line number in matrix model , max cosine value of all features in terms of current thread section, size: row_queries

    DB* db;

} PARALLEL_THREAD_PARAM;


class ARG_EXE_THREAD{
public:
    void* param;
    void (*func)(void*);
};

class Parallel{
    ARG_EXE_THREAD* args;
    int nw; //number of worker threads.
    pthread_t* tid;
	static void* execute_thread(void* arg);
public:
	void Run(void (*f)(void*),std::vector<void*>& param);
	Parallel(){args = 0; tid = 0;}
    ~Parallel();
};
#endif	/* PARALLEL_H */
