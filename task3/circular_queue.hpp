#ifndef CIRCULAR_QUEUE_HPP
#define CIRCULAR_QUEUE_HPP
#pragma once
#include "activity.hpp"
#include <string>

class CircularQueue
{
    private:
        int front;
        int rear;
        int count;
        int capacity;
        Activity *arr;
    public:
        CircularQueue(int size);
        ~CircularQueue();
        void enqueue(Activity a);
        void display();
        void filterByLearner(std::string learnerID);
        void exportCSV(std::string filename);
};

#endif