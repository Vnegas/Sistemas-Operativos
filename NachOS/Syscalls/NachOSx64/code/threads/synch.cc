// synch.cc 
//	Routines for synchronizing threads.  Three kinds of
//	synchronization routines are defined here: semaphores, locks 
//   	and condition variables (the implementation of the last two
//	are left to the reader).
//
// Any implementation of a synchronization routine needs some
// primitive atomic operation.  We assume Nachos is running on
// a uniprocessor, and thus atomicity can be provided by
// turning off interrupts.  While interrupts are disabled, no
// context switch can occur, and thus the current thread is guaranteed
// to hold the CPU throughout, until interrupts are reenabled.
//
// Because some of these routines might be called with interrupts
// already disabled (Semaphore::V for one), instead of turning
// on interrupts at the end of the atomic operation, we always simply
// re-set the interrupt state back to its original value (whether
// that be disabled or enabled).
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "synch.h"
#include "system.h"

//----------------------------------------------------------------------
// Semaphore::Semaphore
// 	Initialize a semaphore, so that it can be used for synchronization.
//
//	"debugName" is an arbitrary name, useful for debugging.
//	"initialValue" is the initial value of the semaphore.
//----------------------------------------------------------------------

Semaphore::Semaphore(const char* debugName, int initialValue)
{
    name = (char *)debugName;
    value = initialValue;
    queue = new List<Thread*>;
}

//----------------------------------------------------------------------
// Semaphore::Semaphore
// 	De-allocate semaphore, when no longer needed.  Assume no one
//	is still waiting on the semaphore!
//----------------------------------------------------------------------

Semaphore::~Semaphore()
{
    delete queue;
}

//----------------------------------------------------------------------
// Semaphore::P
// 	Wait until semaphore value > 0, then decrement.  Checking the
//	value and decrementing must be done atomically, so we
//	need to disable interrupts before checking the value.
//
//	Note that Thread::Sleep assumes that interrupts are disabled
//	when it is called.
//----------------------------------------------------------------------

void
Semaphore::P()
{
    IntStatus oldLevel = interrupt->SetLevel(IntOff);	// disable interrupts
    
    while (value == 0) { 			// semaphore not available
	queue->Append(currentThread);		// so go to sleep
	currentThread->Sleep();
    } 
    value--; 					// semaphore available, 
						// consume its value
    
    interrupt->SetLevel(oldLevel);		// re-enable interrupts
}

//----------------------------------------------------------------------
// Semaphore::V
// 	Increment semaphore value, waking up a waiter if necessary.
//	As with P(), this operation must be atomic, so we need to disable
//	interrupts.  Scheduler::ReadyToRun() assumes that threads
//	are disabled when it is called.
//----------------------------------------------------------------------

void
Semaphore::V()
{
    Thread *thread;
    IntStatus oldLevel = interrupt->SetLevel(IntOff); // disable interrupts

    thread = queue->Remove();
    if (thread != NULL)	   // make thread ready, consuming the V immediately
	scheduler->ReadyToRun(thread);
    value++;
    interrupt->SetLevel(oldLevel); // re-enable interrupts
}

#ifdef USER_PROGRAM
//----------------------------------------------------------------------
// Semaphore::Destroy
// 	Destroy the semaphore, freeing the waiting threads
//	This is used to destroy a user semaphore
//----------------------------------------------------------------------

void
Semaphore::Destroy()
{
    Thread *thread;
    IntStatus oldLevel = interrupt->SetLevel(IntOff);

    while ( (thread = queue->Remove() ) != NULL )	// make thread ready
	scheduler->ReadyToRun(thread);

    interrupt->SetLevel(oldLevel);
}

#endif


// Dummy functions -- so we can compile our later assignments 
// Note -- without a correct implementation of Condition::Wait(), 
// the test case in the network assignment won't work!
Lock::Lock(const char* debugName) {
    this->name = const_cast<char*>(debugName);
    this->owner = NULL;
    this->sem = new Semaphore(debugName, 1);

}


Lock::~Lock() {
    delete this->sem;
}


void Lock::Acquire() {  
    this->sem->P();
    this->owner = currentThread;
}


void Lock::Release() {
    this->owner = NULL;
    this->sem->V();
}


bool Lock::isHeldByCurrentThread() {
   return this->owner == currentThread;
}


Condition::Condition(const char* debugName) {
    this->name = const_cast<char*>(debugName);
    this->queue = new List<Thread*>;
    this->lock = nullptr;
}



Condition::~Condition() {
    delete this->queue;
}


void Condition::Wait( Lock * conditionLock ) {
    if (!conditionLock->isHeldByCurrentThread()) {
        return;
    }
    IntStatus oldLevel = interrupt->SetLevel(IntOff); // disable interrupts
    conditionLock->Release();
    queue->Append(currentThread);
    currentThread->Sleep();
    conditionLock->Acquire();
    interrupt->SetLevel(oldLevel); // re-enable interrupts

}


void Condition::Signal( Lock * conditionLock ) {
    if (!conditionLock->isHeldByCurrentThread()) {
        return;
    }
    IntStatus oldLevel = interrupt->SetLevel(IntOff); // disable interrupts
    Thread *thread;
    thread = queue->Remove();
    if (thread != NULL)	   // make thread ready, consuming the V immediately
    scheduler->ReadyToRun(thread);
    interrupt->SetLevel(oldLevel); // re-enable interrupts
}


void Condition::Broadcast( Lock * conditionLock ) {
    // Clear the queue
   while (!queue->IsEmpty()) {
       Signal(conditionLock);
   }
}


// Mutex class
Mutex::Mutex( const char * debugName ) {
    this->name = const_cast<char*>(debugName);
    this->owner = NULL;
    this->sem = new Semaphore(debugName, 1);
}

Mutex::~Mutex() {
    this->owner = NULL;
    delete this->sem;
}

void Mutex::Lock() {
    this->sem->P();
    this->owner = currentThread;
}

void Mutex::Unlock() {
    this->owner = NULL;
    this->sem->V();
}


// Barrier class
Barrier::Barrier( const char * debugName, int numThreads ) {
    this->name = const_cast<char*>(debugName);
    this->count = numThreads;
    this->sem = new Semaphore(debugName, 0);
    this->mutex = new Semaphore(debugName, 1);
    this->arrived = 0;
}

Barrier::~Barrier() {
    delete this->sem;
    delete this->mutex;
}

void Barrier::Wait() {
    this->mutex->P();
    this->arrived++;
    if (this->arrived == this->count) {
        this->sem->V();
    }
    this->mutex->V();
    this->sem->P();
}

