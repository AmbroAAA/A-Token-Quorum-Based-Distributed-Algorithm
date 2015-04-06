#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include <pthread.h>
#include <list>

using namespace std;

template <typename T> class messageQueue
{
    list<T> msg_queue;
    pthread_mutex_t msg_mutex;
    pthread_cond_t msg_condv;

public:
    messageQueue()
    {
        pthread_mutex_init(&msg_mutex,NULL);
        pthread_cond_init(&msg_condv,NULL);
    }
    ~messageQueue()
    {
        pthread_mutex_destroy(&msg_mutex);
        pthread_cond_destroy(&msg_condv);
    }
    void add(T item)
    {
       pthread_mutex_lock(&msg_mutex);
       msg_queue.push_back(item);
       pthread_cond_signal(&msg_condv);
       pthread_mutex_unlock(&msg_mutex);
    }
    T remove()
    {
        pthread_mutex_lock(&msg_mutex);
        while(msg_queue.size() == 0)
        {
            pthread_cond_wait(&msg_condv,&msg_mutex);   /*!!!!!!!*/
        }
        T item = msg_queue.front();
        msg_queue.pop_front();
        pthread_mutex_unlock(&msg_mutex);
        return item;
    }
    int size()
    {
        pthread_mutex_lock(&msg_mutex);
        int size = msg_queue.size();
        pthread_mutex_unlock(&msg_mutex);
        return size;
    }
};

#endif // MESSAGEQUEUE_H
