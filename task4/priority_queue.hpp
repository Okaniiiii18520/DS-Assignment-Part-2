#pragma once
#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP
#include "learner_profile.hpp"

const int MAX_PRIORITY_QUEUE = 50;
class PriorityQueue
{
private:
    LearnerProfile heap[MAX_PRIORITY_QUEUE];
    int size;
    int parent(int i);
    int leftChild(int i);
    int rightChild(int i);
    void swap(int i, int j);
    void heapifyUp(int i);
    void heapifyDown(int i);
public:
    PriorityQueue();
    bool isEmpty();
    bool isFull();
    int getSize();
    void insert(LearnerProfile lp);
    LearnerProfile extractMax();
    LearnerProfile peekMax();
    void display();
};

#endif