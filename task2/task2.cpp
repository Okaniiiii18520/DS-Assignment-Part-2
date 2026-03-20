#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include "task2.hpp"
#include "../task3/circular_queue.hpp"
#include <limits>
using namespace std;

Stack::Stack() = default;
Stack::~Stack()
{
	Node* cur = top;
	while (cur)
	{
		Node* next = cur->next;
		delete cur;
		cur = next;
	}
}

void Stack::push(Node* n)
{
	n->next = top;
	top = n;
}

Node* Stack::pop()
{
	if (top)
	{
		Node* cur = top;
		top = cur->next;
		cur->next = nullptr;
		return cur;
	}
	else
	{
		return nullptr;
	}
}

Node* Stack::peek()
{
	if (top)
	{
		return top;
	}
	else
	{
		return nullptr;
	}
}

bool Stack::load()
{
	ifstream file("data/data.csv");
	if (!file.is_open())
	{
		cout << "Error: Could not read file " << endl;
		return false;
	}
	string line;
	getline(file, line);
	int temp = -1, qIndex = 0;
	int id;
	string topic;
	Node* n;
	questionSet questions[10];
	while (getline(file, line))
	{
		if (line.empty())
		{
			continue;
		}
		stringstream str2(line);
		string segmt, question, ans;
		getline(str2, segmt, ';');
		if (segmt.empty())
		{
			continue;
		}
		id = stoi(segmt);
		getline(str2, topic, ';');
		getline(str2, question, ';');
		getline(str2, ans);
		if (!ans.empty() && ans.back() == '\r')
		{
			ans.pop_back();
		}
		if (id != temp)
		{
			n = new Node{id, topic};
			temp = id;
			qIndex = 0;
			n->questions[qIndex] = questionSet{question, ans};
			n->totalQuestion = ++qIndex;
			push(n);
		}
		else
		{
			if (qIndex > 9)
			{
				continue;
			}
			n->questions[qIndex] = questionSet{question, ans};
			n->totalQuestion = ++qIndex;
		}
	}
	Node* prev = nullptr;
	Node* cur = top;
	Node* next = nullptr;
	while (cur)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	top = prev;
	return true;
}

Activities::Activities()
{
	pre.load();
}

bool Activities::nextQuestion(const string& ans)
{
	Node* n = pre.peek();
	bool result = (tolower(n->questions[n->completed].answer[0]) == tolower(ans[0]));
	n->score += result;
	n->completed++;
	return result;
}

int Activities::nextAct()
{
	Node* n = pre.pop();
	if (!n)
	{
		return -1;
	}
	post.push(n);
	return n->score;
}

bool Activities::undo()
{
	Node* temp = post.pop();
	if (!temp)
	{
		return false; 
	}
	temp->score = 0;
	temp->completed = 0;
	pre.push(temp);
	return true;
}

Node* Activities::getCur()
{
	return pre.peek();
}

string lower(string input)
{
	for (auto& i : input)
	{
		i = static_cast<char>(tolower(static_cast<unsigned char>(i)));
	}
	return input;
}

void task2Interface(CircularQueue& log, const string& learnerId)
{
	Activities act;
	string input = "";
	bool running = true;
	while (running)
	{
		try
		{
			Node* n = act.getCur();
			if (n == nullptr)
			{
				cout << "All the activities are completed! Nice work!" << endl;
				break;
			}
			if (n->completed == 0)
			{
				cout << "Welcome to " + n->topic + " practice!" << endl
				<< "Enter number to select operation: " << endl
				<< "1. Start\n2. Restart Further\n3. Quit\nChoice: " << endl;
				cin >> input;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				switch(stoi(input))
				{
					case 1:
					{
						break;
					}
					case 2:
					{
						cout << (act.undo() ? "Action successful" : "Action failed, it is the first activity") << endl;
						continue;
					}
					case 3:
					{
						running = false;
						continue;
					}
					default:
					{
						cout << "Invalid input! Please try again" << endl;
						continue;
					}
				}
			}
			if (n->completed > n->totalQuestion - 1)
			{
				log.enqueue(Activity(n->id, learnerId, n->topic, n->score));
				updateLearnerActivity(learnerId, n->topic, n->score);
				cout << "All the questions in this activity are completed! Well Done!" << endl
				<< "Score: " << act.nextAct() << endl << endl
				<< "Enter number to select operation: " << endl
				<< "1. " << (act.getCur() ? "Next Activity" : "Finish" ) << "\n2. Restart\n3. Quit" << endl;
				getline(cin, input);
				switch(stoi(input))
				{
					case 1:
					{
						continue;
					}
					case 2:
					{
						cout << (act.undo() ? "Action successful" : "Action failed, it is the first activity") << endl;
						continue;
					}
					case 3:
					{
						running = false;
						continue;
					}
					default:
					{
						cout << "Invalid input! Please try again" << endl;
						continue;
					}
				}
			}
			cout << (n->completed + 1) << ". " << n->questions[n->completed].question << endl;
			getline(cin, input);
			cout << (act.nextQuestion(input) ? "Congratulations, your answer is correct!" : "Unfortunately, you got this wrong.") << endl << endl;
		}
		catch (exception& ex)
		{
			cout << "Invalid input! Please try again" << endl;
		}
	}
	return;
}