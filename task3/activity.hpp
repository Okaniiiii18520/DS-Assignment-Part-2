#ifndef ACTIVITY_HPP
#define ACTIVITY_HPP
#pragma once
#include <string>

struct Activity
{
    int activityID;
    std::string learnerID;
    std::string topic;
    int score;
    Activity()
    {
        activityID = 0;
        learnerID = "";
        topic = "";
        score = 0;
    }
    Activity(int id, std::string learner, std::string t, int s)
    {
        activityID = id;
        learnerID = learner;
        topic = t;
        score = s;
    }
};

#endif