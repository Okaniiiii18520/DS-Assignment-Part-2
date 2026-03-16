#include "queue.hpp"

Queue::Queue()
{
    front = -1;
    rear = -1;
}

bool Queue::isEmpty()
{
    return (front == -1);
}

bool Queue::isFull()
{
    return (rear == MAX_QUEUE - 1);
}

void Queue::enqueue(Learner l)
{
    if (isFull())
    {
        cout << "Registration queue is full!\n";
        return;
    }
    if (isEmpty())
    {
        front = 0;
    }
    arr[++rear] = l;
}

Learner Queue::dequeue()
{
    Learner l = arr[front];
    if (front == rear)
    {
        front = rear = -1;
    }
    else
    {
        front++;
    }
    return l;
}

void Queue::display()
{
    if (isEmpty())
    {
        cout << "No learners waiting.\n";
        return;
    }
    for (int i = front; i <= rear; i++)
    {
        cout << arr[i].id << " - " << arr[i].name << endl;
    }
}