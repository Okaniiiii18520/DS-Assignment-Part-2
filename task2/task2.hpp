#pragma once
#include <iostream>
#include "../task3/circular_queue.hpp"

struct questionSet
{
	std::string question;
	std::string answer;
};

struct Node
{
	int id;
	std::string topic;
	questionSet questions[10];
	int totalQuestion = 0;
	int completed = 0;
	int score = 0;
	Node* next = nullptr;
};

class Stack
{
private:
	Node* top = nullptr;
public:
	Stack();
    ~Stack();
	void push(Node* n);
	Node* pop();
	Node* peek();
	bool load();
};

class Activities
{
private:
	Stack pre;
	Stack post;
public:
	Activities();
	int nextAct();
	bool nextQuestion(const std::string& ans);
	bool undo();
	Node* getCur();
};

void updateLearnerActivity(const std::string& learnerId, const std::string& topic, int score);

void task2Interface(CircularQueue& log, const std::string& learnerId);