#pragma once
#ifndef RISK_CALCULATOR_HPP
#define RISK_CALCULATOR_HPP
#include "learner_profile.hpp"

class RiskCalculator
{
public:
    static void calculate(LearnerProfile &lp)
    {
        double score = 0.0;
        score += componentLowScore(lp);
        score += componentFailRate(lp);
        score += componentInconsistency(lp);
        score += componentTimeVsProgress(lp);
        lp.riskScore = score;
    }
private:
    static double componentLowScore(const LearnerProfile &lp)
    {
        if (lp.scoreCount == 0)
        {
            return 40.0;
        }
        double total = 0.0;
        for (int i = 0; i < lp.scoreCount; i++)
        {
            total += lp.recentScores[i];
        }
        double avg = total / lp.scoreCount;
        double normalised = avg / 100.0;
        return (1.0 - normalised) * 40.0;
    }
    static double componentFailRate(const LearnerProfile &lp)
    {
        if (lp.totalAttempts == 0)
        {
            return 30.0;
        }
        double ratio = (double)lp.failedAttempts / lp.totalAttempts;
        return ratio * 30.0;
    }
    static double componentInconsistency(const LearnerProfile &lp)
    {
        if (lp.topicCount == 0)
        {
            return 15.0;
        }
        int failed = 0;
        for (int i = 0; i < lp.topicCount; i++)
        {
            if (!lp.topicPassed[i])
            {
                failed++;
            }
        }
        double ratio = (double)failed / lp.topicCount;
        return ratio * 15.0;
    }
    static double componentTimeVsProgress(const LearnerProfile &lp)
    {
        if (lp.activitiesCompleted == 0)
        {
            if (lp.timeSpentMinutes > 0) return 15.0;
            return 0.0;
        }
        double minsPerActivity = (double)lp.timeSpentMinutes / lp.activitiesCompleted;
        double baseline = 20.0;
        double ceiling  = 60.0;
        if (minsPerActivity <= baseline)
        {
            return 0.0;
        }
        if (minsPerActivity >= ceiling) 
        {
            return 15.0;
        }
        double ratio = (minsPerActivity - baseline) / (ceiling - baseline);
        return ratio * 15.0;
    }
};

#endif