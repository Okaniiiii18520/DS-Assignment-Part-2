#pragma once
#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <iostream>
#include <string>
using namespace std;

const int MAX_QUEUE = 20;
struct Learner
{
    int id;
    string name;
};

class Queue
{
private:
    Learner arr[MAX_QUEUE];
    int front;
    int rear;
public:
    Queue();
    bool isEmpty();
    bool isFull();
    void enqueue(Learner l);
    Learner dequeue();
    void display();
};

#endif