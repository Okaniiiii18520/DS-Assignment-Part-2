# Data Structures (C++) - Programming Learning Analytics & Personalization System (PLAPS)

A prototype system built in C++ that simulates how students interact with programming activities and records their learning behaviour. PLAPS tracks learner progress, manages learning sessions, logs recent activities, and identifies learners who may need extra support using classic data structures.

**Build:**
- **Compile (g++):** `g++ -std=c++17 main.cpp task1/queue.cpp task1/session.cpp task2/task2.cpp task3/circular_queue.cpp -o plaps`
- **VS Code:** use the provided task in `.vscode/tasks.json` to build the project.

**Run:**
- **Windows (PowerShell):** `./plaps`

**Files:**
- **Entry point:** [main.cpp](main.cpp)
- **Task 1 – Learner Registration & Session Management:** [task1/queue.hpp](task1/queue.hpp), [task1/queue.cpp](task1/queue.cpp), [task1/session.hpp](task1/session.hpp), [task1/session.cpp](task1/session.cpp)
- **Task 2 – Activity Navigation & Session Flow:** [task2/task2.hpp](task2/task2.hpp), [task2/task2.cpp](task2/task2.cpp)
- **Task 3 – Recent Activity Logging & Performance History:** [task3/activity.hpp](task3/activity.hpp), [task3/circular_queue.hpp](task3/circular_queue.hpp), [task3/circular_queue.cpp](task3/circular_queue.cpp)
- **Task 4 – At-Risk Learner Priority & Recommendation Engine:** [task4/learner_profile.hpp](task4/learner_profile.hpp), [task4/priority_queue.hpp](task4/priority_queue.hpp), [task4/priority_queue.cpp](task4/priority_queue.cpp), [task4/risk_calculator.hpp](task4/risk_calculator.hpp), [task4/recommendation_engine.hpp](task4/recommendation_engine.hpp), [task4/exporter.hpp](task4/exporter.hpp)
- **Sample dataset:** [data/data.csv](data/data.csv)

**Data Structures Used:**
- **Task 1:** Queue (learner registration), Array (active session)
- **Task 2:** Stack — two stacks (pre and post) for forward navigation and undo
- **Task 3:** Circular Queue (fixed-size rolling activity log)
- **Task 4:** Max-Heap Priority Queue (at-risk learner ranking)

**Purpose:**
- Demonstrates practical application of core data structures in a real-world learning management scenario.
- Supports personalized learning by tracking performance, logging activity, and surfacing at-risk learners with targeted recommendations.

## 👥 Contributors

This project was developed through collaboration by the following team members:

- [Nicholas Pang Tze Shen](https://github.com/Fraxtal) 

- [Ng Wei Hao](https://github.com/02-is-02)

- [Tan Anh Kang](https://github.com/Okaniiiii18520)

- [Teoh Kai Chen](https://github.com/KingstonTeoh)