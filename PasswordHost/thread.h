#ifndef THREAD_H
#define THREAD_H

#include <QThread>

class Thread:public QThread
{
    Q_OBJECT
public:
    Thread();
    void stop();

protected:
    void run();

private:
    volatile bool stopped;
};

#endif // THREAD_H
