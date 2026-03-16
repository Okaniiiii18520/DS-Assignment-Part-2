#include <iostream>
#include <fstream>
#include "circular_queue.hpp"
using namespace std;

CircularQueue::CircularQueue(int size)
{
    capacity = size;
    front = 0;
    rear = -1;
    count = 0;
    arr = new Activity[capacity];
}

CircularQueue::~CircularQueue()
{
    delete[] arr;
}

void CircularQueue::enqueue(Activity a)
{
    if (count == capacity)
    {
        cout << "Log full. Oldest record overwritten.\n";
        front = (front + 1) % capacity;
        count--;
    }
    rear = (rear + 1) % capacity;
    arr[rear] = a;
    count++;
}

void CircularQueue::display()
{
    if (count == 0)
    {
        cout << "No activity logs available.\n";
        return;
    }
    int i = front;
    cout << "\nCurrent Activity Logs\n";
    cout << "----------------------------\n";
    for (int c = 0; c < count; c++)
    {
        Activity a = arr[i];
        cout << "Activity ID: " << a.activityID << endl;
        cout << "Learner ID: " << a.learnerID << endl;
        cout << "Topic: " << a.topic << endl;
        cout << "Score: " << a.score << endl;
        cout << "----------------------------\n";

        i = (i + 1) % capacity;
    }
}

void CircularQueue::filterByLearner(string learnerID)
{
    if (count == 0)
    {
        cout << "No logs available.\n";
        return;
    }
    int i = front;
    bool found = false;
    cout << "\nLogs for Learner: " << learnerID << endl;
    for (int c = 0; c < count; c++)
    {
        Activity a = arr[i];
        if (a.learnerID == learnerID)
        {
            cout << "Activity ID: " << a.activityID << endl;
            cout << "Topic: " << a.topic << endl;
            cout << "Score: " << a.score << endl;
            cout << "----------------------------\n";
            found = true;
        }
        i = (i + 1) % capacity;
    }
    if (!found)
    {
        cout << "No records found.\n";
    }
}

void CircularQueue::exportCSV(string filename)
{
    ofstream file(filename);
    if (!file)
    {
        cout << "Error opening file.\n";
        return;
    }
    file << "ActivityID;LearnerID;Topic;Score;Difficulty\n";
    int i = front;
    for (int c = 0; c < count; c++)
    {
        Activity a = arr[i];
        file << a.activityID << ";"
             << a.learnerID << ";"
             << a.topic << ";"
             << a.score << "\n";

        i = (i + 1) % capacity;
    }
    file.close();
    cout << "Logs exported successfully.\n";
}