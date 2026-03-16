#pragma once
#ifndef LEARNER_PROFILE_HPP
#define LEARNER_PROFILE_HPP
#include <iostream>
#include <string>
using namespace std;

const int MAX_SCORES = 5;
const int MAX_TOPICS = 5;
struct LearnerProfile
{
    int id;
    string name;
    int recentScores[MAX_SCORES];
    int scoreCount;
    int failedAttempts;
    int totalAttempts;
    string topics[MAX_TOPICS];
    int topicCount;
    bool topicPassed[MAX_TOPICS];
    int timeSpentMinutes;
    int activitiesCompleted;
    double riskScore;
    string recommendation;
};

#endif