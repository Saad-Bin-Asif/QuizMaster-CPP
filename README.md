# 🧠 QuizMaster-CPP (Console-Based Quiz Game)

A fully functional, interactive console-based Quiz Game built entirely in **C++**. This project demonstrates core programming concepts, specifically focusing on data persistence through **file handling** to load questions and save game states without hardcoding data into the source code.

## ✨ Features

*   **Dynamic Question Loading:** Questions and multiple-choice options are fetched directly from external text/data files using C++ file streams (`ifstream`).
*   **Data Persistence:** User progress or question banks can be updated and saved using file output streams (`ofstream`).
*   **Interactive CLI:** Clean and easy-to-navigate command-line interface for the user to select answers and view scores.
*   **Score Tracking:** Real-time calculation of correct and incorrect answers, displaying the final score at the end of the quiz.
*   **Error Handling:** Basic input validation to prevent the game from crashing if the user enters invalid options.

## 🛠️ Tech Stack

*   **Language:** C++
*   **Core Concepts Used:** 
    *   File Handling (File I/O)
    *   Control Structures & Loops
    *   Functions & Modular Programming
    *   Basic Data Structures (Arrays/Vectors)

## 🚀 How to Run Locally

1.  **Clone the repository:**
```bash
    git clone [https://github.com/yourusername/your-repo-name.git](https://github.com/yourusername/your-repo-name.git)
    ```
2.  **Navigate to the project directory:**
```bash
    cd your-repo-name
    ```
3.  **Compile the C++ file:**
    Use your preferred compiler (e.g., g++ in VS Code or Visual Studio).
```bash
    g++ main.cpp -o quizgame
    ```
4.  **Run the executable:**
```bash
    ./quizgame
    ```
    *(Note: Ensure that the question data files are in the same directory as the executable before running).*

## 💡 Project Background

This project was developed to solidify foundational programming concepts in C++. By integrating file handling, the game moves beyond basic variable storage, allowing for a scalable question bank where new quizzes can be added simply by modifying a text file—no code recompilation required.

---
*Created by [Your Name/GitHub Handle]*
