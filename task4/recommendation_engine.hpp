#pragma once
#ifndef RECOMMENDATION_ENGINE_HPP
#define RECOMMENDATION_ENGINE_HPP
#include "learner_profile.hpp"

class RecommendationEngine
{
public:
    static void generateRecommendation(LearnerProfile &lp)
    {
        if (averageScore(lp) < 40.0)
        {
            lp.recommendation = "Scores are critically low. Restart foundational activities and seek tutor support immediately.";
            return;
        }
        if (lp.totalAttempts > 0 && (double)lp.failedAttempts / lp.totalAttempts >= 0.60)
        {
            lp.recommendation = "Too many failed attempts. Attempt easier difficulty activities before progressing.";
            return;
        }
        if (failedTopicCount(lp) >= 3)
        {
            lp.recommendation = "Struggling across multiple topics. Follow the structured learning path and do not skip ahead.";
            return;
        }
        if (lp.activitiesCompleted > 0 && (double)lp.timeSpentMinutes / lp.activitiesCompleted > 40.0)
        {
            lp.recommendation = "Taking too long per activity. Schedule a one-on-one tutor session to address pacing.";
            return;
        }
        if (averageScore(lp) < 60.0)
        {
            lp.recommendation = "Below average performance. Review recent topic materials and retry activities.";
            return;
        }
        if (lp.riskScore >= 30.0)
        {
            lp.recommendation = "Showing early signs of struggle. Monitor closely and check in with the learner.";
            return;
        }
        else
        {
            lp.recommendation = "Performing adequately. Continue current learning path.";
        }
    }
private:
    static double averageScore(const LearnerProfile &lp)
    {
        if (lp.scoreCount == 0)
        {
            return 0.0;
        }
        double total = 0.0;
        for (int i = 0; i < lp.scoreCount; i++)
        {
            total += lp.recentScores[i];
        }
        return total / lp.scoreCount;
    }
    static int failedTopicCount(const LearnerProfile &lp)
    {
        int count = 0;
        for (int i = 0; i < lp.topicCount; i++)
        {
            if (!lp.topicPassed[i]) count++;
        }
        return count;
    }
};

#endif