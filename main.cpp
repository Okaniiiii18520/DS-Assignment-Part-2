#include "task1/queue.hpp"
#include "task1/session.hpp"
#include "task2/task2.hpp"
#include "task3/circular_queue.hpp"
#include "task4/priority_queue.hpp"
#include "task4/priority_queue.cpp"
#include "task4/risk_calculator.hpp"
#include "task4/recommendation_engine.hpp"
#include "task4/exporter.hpp"
#include <iostream>
#include <string>
#include <limits>
using namespace std;

CircularQueue activityLog(10);
LearnerProfile registeredLearners[MAX_PRIORITY_QUEUE];
int learnerCount = 0;
int findLearnerIndex(const string& learnerId)
{
    for (int i = 0; i < learnerCount; i++)
    {
        if (to_string(registeredLearners[i].id) == learnerId)
        {
            return i;
        }
    }
    return -1;
}

void updateLearnerActivity(const string& learnerId, const string& topic, int score)
{
    int idx = findLearnerIndex(learnerId);
    if (idx == -1)
    {
        return;
    }
    LearnerProfile& lp = registeredLearners[idx];
    if (lp.scoreCount < MAX_SCORES)
    {
        lp.recentScores[lp.scoreCount++] = score;
    }
    else
    {
        for (int i = 0; i < MAX_SCORES - 1; i++)
        {
            lp.recentScores[i] = lp.recentScores[i + 1];
        }
        lp.recentScores[MAX_SCORES - 1] = score;
    }
    lp.totalAttempts++;
    if (score < 50)
    {
        lp.failedAttempts++;
    }
    bool passed = (score >= 50);
    if (lp.topicCount < MAX_TOPICS)
    {
        lp.topics[lp.topicCount] = topic;
        lp.topicPassed[lp.topicCount] = passed;
        lp.topicCount++;
    }
    else
    {
        for (int i = 0; i < MAX_TOPICS - 1; i++)
        {
            lp.topics[i] = lp.topics[i + 1];
            lp.topicPassed[i] = lp.topicPassed[i + 1];
        }
        lp.topics[MAX_TOPICS - 1] = topic;
        lp.topicPassed[MAX_TOPICS - 1] = passed;
    }
    lp.activitiesCompleted++;
}

void runTask1()
{
    Queue waitingQueue;
    Session session;
    int choice;
    do
    {
        cout << "\n--- Task 1: Learner Registration & Session Management ---\n";
        cout << "1. Register Learner\n";
        cout << "2. Move Learner to Session\n";
        cout << "3. Exit Learner from Session\n";
        cout << "4. Show Waiting List\n";
        cout << "5. Show Active Session\n";
        cout << "6. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice == 1)
        {
            Learner l;
            cout << "Enter ID: ";
            cin >> l.id;
            cout << "Enter Name: ";
            cin >> l.name;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (learnerCount < MAX_PRIORITY_QUEUE)
            {
                LearnerProfile lp;
                lp.id                  = l.id;
                lp.name                = l.name;
                lp.scoreCount          = 0;
                lp.failedAttempts      = 0;
                lp.totalAttempts       = 0;
                lp.topicCount          = 0;
                lp.timeSpentMinutes    = 0;
                lp.activitiesCompleted = 0;
                lp.riskScore           = 0;
                lp.recommendation      = "No activity data yet.";
                registeredLearners[learnerCount++] = lp;
                cout << "Learner registered successfully.\n";
            }
            waitingQueue.enqueue(l);
        }
        else if (choice == 2)
        {
            if (!waitingQueue.isEmpty() && !session.isFull())
            {
                Learner l = waitingQueue.dequeue();
                session.addLearner(l);
                cout << "Learner moved to session.\n";
            }
            else
            {
                cout << "Cannot move learner (queue empty or session full).\n";
            }
        }
        else if (choice == 3)
        {
            int id;
            cout << "Enter learner ID to exit: ";
            cin >> id;
            session.removeLearner(id);
        }
        else if (choice == 4)
        {
            waitingQueue.display();
        }
        else if (choice == 5)
        {
            session.display();
        }
    }
    while (choice != 6);
}

void runTask2()
{
    string learnerId;
    cout << "\n--- Task 2: Activity Navigation & Session Flow ---\n";
    cout << "Enter your Learner ID: ";
    getline(cin, learnerId);
    task2Interface(activityLog, learnerId);
}

void runTask3()
{
    int choice;
    do
    {
        cout << "\n--- Task 3: Recent Activity Logging ---\n";
        cout << "1. View All Activity Logs\n";
        cout << "2. Filter Logs by Learner ID\n";
        cout << "3. Export Logs to CSV\n";
        cout << "4. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice == 1)
        {
            activityLog.display();
        }
        else if (choice == 2)
        {
            string id;
            cout << "Enter Learner ID to filter: ";
            getline(cin, id);
            activityLog.filterByLearner(id);
        }
        else if (choice == 3)
        {
            string filename;
            cout << "Enter filename (e.g. activity_log.csv): ";
            getline(cin, filename);
            activityLog.exportCSV(filename);
        }
    }
    while (choice != 4);
}

void loadRegisteredLearners(PriorityQueue &pq)
{
    if (pq.getSize() > 0)
    {
        cout << "Learners already loaded. Exit and re-enter Task 4 to refresh.\n";
        return;
    }
    else if (learnerCount == 0)
    {
        cout << "No learners registered yet. Please register learners in Task 1 first.\n";
        return;
    }
    for (int i = 0; i < learnerCount; i++)
    {
        RiskCalculator::calculate(registeredLearners[i]);
        RecommendationEngine::generateRecommendation(registeredLearners[i]);
        pq.insert(registeredLearners[i]);
    }
    cout << learnerCount << " registered learner(s) loaded into risk assessment.\n";
}

void runTask4()
{
    PriorityQueue pq;
    int choice;
    do
    {
        cout << "\n--- Task 4: At-Risk Learner Priority & Recommendation ---\n";
        cout << "1. Load registered learners\n";
        cout << "2. Display all at-risk learners\n";
        cout << "3. View highest-risk learner\n";
        cout << "4. Export at-risk list to CSV\n";
        cout << "5. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice == 1)
        {
            loadRegisteredLearners(pq);
        }   
        else if (choice == 2)
        {
            pq.display();
        }
        else if (choice == 3)
        {
            if (!pq.isEmpty())
            {
                LearnerProfile top = pq.peekMax();
                cout << "\nHighest-risk learner:\n";
                cout << "  ID         : " << top.id << "\n";
                cout << "  Name       : " << top.name << "\n";
                cout << "  Risk Score : " << top.riskScore << "\n";
                cout << "  Action     : " << top.recommendation << "\n";
            }
            else
            {
                cout << "Queue is empty.\n";
            }
        }
        else if (choice == 4)
        {
            string filename;
            cout << "Enter filename (e.g. at_risk_report.csv): ";
            getline(cin, filename);
            Exporter::exportToCSV(pq, filename);
        }
    }
    while (choice != 5);
}

int main()
{
    int choice;
    cout << "========================================================================================\n";
    cout << "Asia Pacific University (APU) - Programming Learning Analytics & Personalization (PLAPS)\n";
    cout << "========================================================================================\n";
    do
    {
        cout << "\n================== MAIN MENU ==================\n";
        cout << "Tasks\n";
        cout << "1. Learner Registration & Session Management\n";
        cout << "2. Activity Navigation & Session Flow\n";
        cout << "3. Recent Activity Logging & Performance History\n";
        cout << "4. At-Risk Learner Priority & Recommendation\n";
        cout << "5. Exit\n";
        cout << "===============================================\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice == 1)
        {
            runTask1();
        }
        else if (choice == 2)
        {
            runTask2();
        }
        else if (choice == 3)
        {
            runTask3();
        }
        else if (choice == 4)
        {
            runTask4();
        }
        else if (choice != 5)
        {
            cout << "Invalid input.\n";
        }
    }
    while (choice != 5);
    {
        cout << "\nTerminating program. Thank you for using APU's PLAPS!\n";
        return 0;
    }
}