#include "priority_queue.hpp"

PriorityQueue::PriorityQueue()
{
    size = 0;
}

bool PriorityQueue::isEmpty()
{
    return size == 0;
}

bool PriorityQueue::isFull()
{
    return size == MAX_PRIORITY_QUEUE;
}

int PriorityQueue::getSize()
{
    return size;
}

int PriorityQueue::parent(int i)
{
    return (i - 1) / 2;
}

int PriorityQueue::leftChild(int i)
{
    return (2 * i) + 1;
}

int PriorityQueue::rightChild(int i)
{
    return (2 * i) + 2;
}

void PriorityQueue::swap(int i, int j)
{
    LearnerProfile temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

void PriorityQueue::heapifyUp(int i)
{
    while (i > 0 && heap[i].riskScore > heap[parent(i)].riskScore)
    {
        swap(i, parent(i));
        i = parent(i);
    }
}

void PriorityQueue::heapifyDown(int i)
{
    int largest = i;
    int left    = leftChild(i);
    int right   = rightChild(i);
    if (left < size && heap[left].riskScore > heap[largest].riskScore)
    {
        largest = left;
    }
    if (right < size && heap[right].riskScore > heap[largest].riskScore)
    {
        largest = right;
    }
    if (largest != i)
    {
        swap(i, largest);
        heapifyDown(largest);
    }
}

void PriorityQueue::insert(LearnerProfile lp)
{
    if (isFull())
    {
        cout << "Priority queue is full. Cannot insert learner.\n";
        return;
    }
    heap[size] = lp;
    heapifyUp(size);
    size++;
}

LearnerProfile PriorityQueue::extractMax()
{
    if (isEmpty())
    {
        cout << "Priority queue is empty.\n";
        LearnerProfile empty;
        empty.id = -1;
        return empty;
    }
    LearnerProfile top = heap[0];
    heap[0] = heap[size - 1];
    size--;              
    heapifyDown(0);
    return top;
}

LearnerProfile PriorityQueue::peekMax()
{
    if (isEmpty())
    {
        cout << "Priority queue is empty.\n";
        LearnerProfile empty;
        empty.id = -1;
        return empty;
    }
    return heap[0];
}

void PriorityQueue::display()
{
    if (isEmpty())
    {
        cout << "No at-risk learners in the system.\n";
        return;
    }
    PriorityQueue temp = *this;
    cout << "\n===============================================================\n";
    cout << "               AT-RISK LEARNER PRIORITY LIST                   \n";
    cout << "===============================================================\n";
    cout << left;
    int rank = 1;
    while (!temp.isEmpty())
    {
        LearnerProfile lp = temp.extractMax();
        cout << " Rank #" << rank++ << "\n";
        cout << "  ID          : " << lp.id << "\n";
        cout << "  Name        : " << lp.name << "\n";
        cout << "  Risk Score  : " << lp.riskScore << "\n";
        cout << "  Recommend.  : " << lp.recommendation << "\n";
        cout << "  =========================================================\n";
    }
}