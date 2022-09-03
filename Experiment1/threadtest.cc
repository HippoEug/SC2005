// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"

//----------------------------------------------------------------------
// SimpleThread
// 	Loop 3 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

void
SimpleThread(_int which) // 'which' tells you which thread, for debugging
{
    int num;
    
    // function does nothing but prints a status line thrice
    for (num = 0; num < 3; num++) {
	printf("*** thread %d looped %d times\n", (int) which, num);
        currentThread->Yield(); // causes current thread to give up CPU
    }
}

//----------------------------------------------------------------------
// ThreadTest
// 	Set up a ping-pong between two threads, by forking a thread 
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------

void
ThreadTest()
{
    DEBUG('t', "Entering SimpleTest");
    
    // Fork(function, arg, join)
    // "function": the procedure to be executed concurrently, ie SimpleThread
    // "arg": thread id
    // "join": flag that indicates whether thread can be joined (not important)
    Thread *t1 = new Thread("child1"); // thread constructor does minimial initialization
    t1->Fork(SimpleThread, 1, 0); // allows thread to be able to be scheduled & excuted by CPU
    Thread *t2 = new Thread("child2");
    t2->Fork(SimpleThread, 2, 0);
    SimpleThread(0); // call function after executing 2 new threads
}

