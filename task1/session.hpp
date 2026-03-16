#pragma once
#ifndef SESSION_HPP
#define SESSION_HPP
#include "queue.hpp"

const int SESSION_SIZE = 5;
class Session
{
private:
    Learner learners[SESSION_SIZE];
    int count;
public:
    Session();
    bool isFull();
    bool isEmpty();
    void addLearner(Learner l);
    void removeLearner(int id);
    void display();
};

#endif