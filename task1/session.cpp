#include "session.hpp"
#include <iostream>
using namespace std;

Session::Session()
{
    count = 0;
}

bool Session::isFull()
{
    return count == SESSION_SIZE;
}

bool Session::isEmpty()
{
    return count == 0;
}

void Session::addLearner(Learner l)
{
    if (isFull())
    {
        cout << "Session is full!\n"; return;
    }
    learners[count++] = l;
}

void Session::removeLearner(int id)
{
    int index = -1;
    for (int i = 0; i < count; i++)
    {
        if (learners[i].id == id)
        {
            index = i; break;
        }
    }
    if (index == -1)
    {
        cout << "Learner not found.\n"; return;
    }
    for (int i = index; i < count - 1; i++)
    {
        learners[i] = learners[i + 1];
    }
    count--;
    cout << "Learner removed from session.\n";
}

void Session::display()
{
    if (isEmpty())
    { 
        cout << "No learners in session.\n"; return;
    }
    for (int i = 0; i < count; i++)
    {
        cout << learners[i].id << " - " << learners[i].name << endl;
    }
}