#include "thread.h"

Thread::Thread()
{
    stopped = false;
}

void Thread::run(){
    while(!stopped){

    }
    stopped = false;
}

void Thread::stop(){
    stopped = true;
}
