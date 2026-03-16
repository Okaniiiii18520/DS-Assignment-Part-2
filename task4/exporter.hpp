#pragma once
#ifndef EXPORTER_HPP
#define EXPORTER_HPP
#include <fstream>
#include "priority_queue.hpp"

class Exporter
{
public:
    static bool exportToCSV(PriorityQueue pq, const string &filename)
    {
        ofstream file(filename);
        if (!file.is_open())
        {
            cout << "Error: Could not open file \"" << filename << "\" for writing.\n";
            return false;
        }
        file << "Rank,LearnerID,Name,RiskScore,FailedAttempts,TotalAttempts,AvgScore,Recommendation\n";
        int rank = 1;
        while (!pq.isEmpty())
        {
            LearnerProfile lp = pq.extractMax();
            double avg = 0.0;
            if (lp.scoreCount > 0)
            {
                double total = 0.0;
                for (int i = 0; i < lp.scoreCount; i++)
                {
                    total += lp.recentScores[i];
                }
                avg = total / lp.scoreCount;
            }
            file << rank++ << ","
                 << lp.id << ","
                 << lp.name << ","
                 << lp.riskScore << ","
                 << lp.failedAttempts << ","
                 << lp.totalAttempts << ","
                 << avg << ","
                 << "\"" << lp.recommendation << "\"\n";
        }
        file.close();
        cout << "Export successful. File saved as: " << filename << "\n";
        return true;
    }
};

#endif