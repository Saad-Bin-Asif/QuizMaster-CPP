#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib> 
#include<ctime>   

using namespace std;

const int maxQuestions = 50;
string questions[maxQuestions];
string option1[maxQuestions];
string option2[maxQuestions];
string option3[maxQuestions];
string option4[maxQuestions];
string correctAns[maxQuestions];

int totalLoaded = 0;

bool getNextLine(ifstream& file, string& target);
bool loadQuestions(string filename);
void startGame();
void categoryMenu();
void mainMenu();
void saveHighScore(string playerName, int score);
void saveQuizLog(string playerName, int score, int correct, int wrong);
void viewHighScores();
void reviewWrongAnswers(bool wrongIndices[], int count);

int main()
{
	srand((unsigned int)time(0));

	mainMenu();

	return 0;
}

bool getNextLine(ifstream& file, string& target)
{
	while (getline(file, target))
	{
		if (target != "")
		{
			return true;
		}
	}
	return false;
}

bool loadQuestions(string filename)
{
	ifstream file(filename);

	if (file.is_open() == false)
	{
		cout << "\n(Error) File not found: " << filename;
		cout << "\nPlease ensure the file exists in the project folder.\n";
		system("pause");
		return false;
	}

	totalLoaded = 0;

	while (totalLoaded < maxQuestions && getNextLine(file, questions[totalLoaded]))
	{
		if (getNextLine(file, option1[totalLoaded]) == false)
		{
			break;
		}
		if (getNextLine(file, option2[totalLoaded]) == false)
		{
			break;
		}
		if (getNextLine(file, option3[totalLoaded]) == false)
		{
			break;
		}
		if (getNextLine(file, option4[totalLoaded]) == false)
		{
			break;
		}
		if (getNextLine(file, correctAns[totalLoaded]) == false)
		{
			break;
		}

		totalLoaded++;
	}

	file.close();

	if (totalLoaded == 0)
	{
		cout << "\n(Warning) File is empty or format is incorrect.\n";
		system("pause");
		return false;
	}

	cout << "\n(Success) " << totalLoaded << " Questions Loaded Successfully!\n";
	return true;
}

void saveHighScore(string playerName, int score)
{
	ofstream file("high_scores.txt", ios::app);

	if (file.is_open())
	{
		file << playerName << " : " << score << " Points" << endl;
		file.close();
		cout << " -> High Score Saved!\n";
	}
}

void saveQuizLog(string playerName, int score, int correct, int wrong)
{
	ofstream file("quiz_logs.txt", ios::app);

	if (file.is_open())
	{
		file << "Player: " << playerName << " | Score: " << score
			<< " | Correct: " << correct << " | Wrong: " << wrong << endl;
		file.close();
		cout << " -> Session Logged!\n";
	}
}

void viewHighScores()
{
	system("cls");
	ifstream file("high_scores.txt");
	string line;

	cout << "\n==============================";
	cout << "\n       LEADERBOARD";
	cout << "\n==============================\n";

	if (file.is_open())
	{
		while (getline(file, line))
		{
			cout << line << endl;
		}
		file.close();
	}
	else
	{
		cout << "No High Scores recorded yet.\n";
	}
	cout << "\n==============================\n";
	system("pause");
}

void reviewWrongAnswers(bool wrongIndices[], int totalAsked)
{
	system("cls");
	cout << "\n--- REVIEW WRONG ANSWERS ---\n";
	bool anyWrong = false;

	for (int i = 0; i < maxQuestions; i++)
	{
		if (wrongIndices[i] == true)
		{
			anyWrong = true;
			cout << "\nQ: " << questions[i];

			string correctText = "";
			if (correctAns[i] == "1")
			{
				correctText = option1[i];
			}
			else if (correctAns[i] == "2")
			{
				correctText = option2[i];
			}
			else if (correctAns[i] == "3")
			{
				correctText = option3[i];
			}
			else if (correctAns[i] == "4")
			{
				correctText = option4[i];
			}

			cout << "\nCorrect Answer: " << correctText << " (Option " << correctAns[i] << ")" << endl;
		}
	}

	if (anyWrong == false)
	{
		cout << "Perfect Score! Nothing to review.\n";
	}
	cout << "----------------------------\n";
	system("pause");
}

void startGame()
{
	system("cls");
	int score = 0;
	int count = 0;
	int questionsToAsk = 10;

	bool isAsked[maxQuestions] = { 0 };
	bool wrongIndices[maxQuestions] = { 0 };

	int correctCount = 0;
	int wrongCount = 0;
	int streak = 0;
	int penalty = 2;

	bool used5050 = false;
	bool usedSkip = false;
	bool usedReplace = false;

	cout << "\nSelect Difficulty Level:";
	cout << "\n1. Easy (Penalty -2)";
	cout << "\n2. Medium (Penalty -3)";
	cout << "\n3. Hard (Penalty -5)";

	string diff;
	while (true)
	{
		cout << "\nEnter Choice (1-3): ";
		cin >> diff;
		if (diff == "1" || diff == "2" || diff == "3")
		{
			break;
		}
		cout << "(Invalid Input) Please enter 1, 2, or 3 only.\n";
	}

	if (diff == "2")
	{
		penalty = 3;
	}
	else if (diff == "3")
	{
		penalty = 5;
	}
	else
	{
		penalty = 2;
	}

	if (totalLoaded < questionsToAsk)
	{
		questionsToAsk = totalLoaded;
	}

	while (count < questionsToAsk)
	{
		system("cls");

		cout << "\n--- QUIZ PROGRESS: " << count + 1 << "/" << questionsToAsk << " ---\n";

		int randomIndex = rand() % totalLoaded;

		if (isAsked[randomIndex] == 1)
		{
			continue;
		}

		cout << "\nQ" << count + 1 << ": " << questions[randomIndex];
		cout << "\n1. " << option1[randomIndex];
		cout << "\n2. " << option2[randomIndex];
		cout << "\n3. " << option3[randomIndex];
		cout << "\n4. " << option4[randomIndex];
		cout << "\n5. (USE LIFELINE) (Type 5)" << endl;

		time_t startTime = time(0);
		string userChoice;

		while (true)
		{
			cout << "Your Answer: ";
			cin >> userChoice;
			if (userChoice == "1" || userChoice == "2" || userChoice == "3" || userChoice == "4" || userChoice == "5")
			{
				break;
			}
			cout << "(Invalid) Enter 1-5 only.\n";
		}

		time_t endTime = time(0);
		double timeTaken = difftime(endTime, startTime);

		if (timeTaken > 10.0)
		{
			cout << "\n(TIME OVER!) You took " << timeTaken << " seconds.";
			cout << "\nPenalty: -" << penalty << " Points\n";
			score = score - penalty;
			wrongCount++;
			streak = 0;
			wrongIndices[randomIndex] = true;
			isAsked[randomIndex] = 1;
			count++;

			cout << "\nPress any key for next question...";
			system("pause > 0");
			continue;
		}

		if (userChoice == "5")
		{
			cout << "\n--- LIFELINES MENU ---";

			if (used5050 == false)
			{
				cout << "\n1. 50/50";
			}
			if (usedSkip == false)
			{
				cout << "\n2. Skip Question";
			}
			if (usedReplace == false)
			{
				cout << "\n3. Replace Question";
			}

			cout << "\n4. Cancel";

			string lifeChoice;
			while (true)
			{
				cout << "\nSelect Lifeline (1-4): ";
				cin >> lifeChoice;
				if (lifeChoice == "1" || lifeChoice == "2" || lifeChoice == "3" || lifeChoice == "4")
				{
					break;
				}
				cout << "Invalid choice.\n";
			}

			if (lifeChoice == "1" && used5050 == false)
			{
				used5050 = true;
				cout << "\n(50/50 USED) Hint: Answer is EITHER " << correctAns[randomIndex] << " OR " << ((rand() % 4) + 1) << endl;

				while (true)
				{
					cout << "Enter Answer again (1-4): ";
					cin >> userChoice;
					if (userChoice == "1" || userChoice == "2" || userChoice == "3" || userChoice == "4")
					{
						break;
					}
					cout << "Invalid input.\n";
				}
			}
			else if (lifeChoice == "2" && usedSkip == false)
			{
				usedSkip = true;
				cout << "\n(SKIP USED) Moving to next...\n";
				isAsked[randomIndex] = 1;
				count++;

				cout << "\nPress any key for next question...";
				system("pause > 0");
				continue;
			}
			else if (lifeChoice == "3" && usedReplace == false)
			{
				usedReplace = true;
				cout << "\n(REPLACE USED) Showing new question...\n";

				cout << "\nPress any key for new question...";
				system("pause > 0");
				continue;
			}
			else if (lifeChoice == "4")
			{
				cout << "Resuming...\n";
				while (true)
				{
					cout << "Enter Answer (1-4): ";
					cin >> userChoice;
					if (userChoice == "1" || userChoice == "2" || userChoice == "3" || userChoice == "4")
					{
						break;
					}
					cout << "Invalid input.\n";
				}
			}
			else
			{
				cout << "Invalid/Used! Answer directly.\n";
				while (true)
				{
					cout << "Enter Answer (1-4): ";
					cin >> userChoice;
					if (userChoice == "1" || userChoice == "2" || userChoice == "3" || userChoice == "4")
					{
						break;
					}
					cout << "Invalid input.\n";
				}
			}
		}

		if (userChoice == correctAns[randomIndex])
		{
			cout << "\n>>> CORRECT! (+10 Points) <<<\n";
			score = score + 10;
			correctCount++;
			streak++;

			if (streak == 3)
			{
				cout << "STREAK BONUS! (+5 Points)\n";
				score = score + 5;
			}
			if (streak == 5)
			{
				cout << "SUPER STREAK! (+15 Points)\n";
				score = score + 15;
			}
		}
		else
		{
			cout << "\n>>> WRONG! <<<\n";
			cout << "Correct Answer was: " << correctAns[randomIndex] << "\n";
			score = score - penalty;
			wrongCount++;
			streak = 0;
			wrongIndices[randomIndex] = true;
		}

		isAsked[randomIndex] = 1;
		count++;

		cout << "\nPress any key for next question...";
		system("pause > 0");
	}

	system("cls");
	cout << "\n##############################";
	cout << "\n       GAME OVER!";
	cout << "\n Final Score: " << score;
	cout << "\n Correct: " << correctCount << " | Wrong: " << wrongCount;
	cout << "\n##############################\n";

	string playerName;
	cout << "\nEnter your name to save record: ";
	cin >> playerName;

	saveHighScore(playerName, score);
	saveQuizLog(playerName, score, correctCount, wrongCount);

	cout << "\nDo you want to review wrong answers? (y/n): ";
	string reviewChoice;
	cin >> reviewChoice;

	if (reviewChoice == "y" || reviewChoice == "Y")
	{
		reviewWrongAnswers(wrongIndices, totalLoaded);
	}
}

void categoryMenu()
{
	system("cls");
	string catChoice;

	cout << "\n--- SELECT CATEGORY ---";
	cout << "\n1. Science";
	cout << "\n2. Computer";
	cout << "\n3. Sports";
	cout << "\n4. History";
	cout << "\n5. IQ / Logic";

	while (true)
	{
		cout << "\nEnter Choice (1-5): ";
		cin >> catChoice;
		if (catChoice == "1" || catChoice == "2" || catChoice == "3" || catChoice == "4" || catChoice == "5")
		{
			break;
		}
		cout << "(Error) Invalid Input! Please enter a number between 1 and 5.\n";
	}

	string filename = "";
	if (catChoice == "1")
	{
		filename = "science.txt";
	}
	else if (catChoice == "2")
	{
		filename = "computer.txt";
	}
	else if (catChoice == "3")
	{
		filename = "sports.txt";
	}
	else if (catChoice == "4")
	{
		filename = "history.txt";
	}
	else if (catChoice == "5")
	{
		filename = "iq.txt";
	}

	if (loadQuestions(filename) == true)
	{
		startGame();
	}
}

void mainMenu()
{
	string choice;

	do
	{
		system("cls");
		cout << "\n==============================";
		cout << "\n      QUIZ MASTER GAME";
		cout << "\n==============================";
		cout << "\n1. Start Quiz";
		cout << "\n2. View High Scores";
		cout << "\n3. Exit Game";
		cout << "\n\nSelect Option (1-3): ";
		cin >> choice;

		if (choice == "1")
		{
			categoryMenu();
		}
		else if (choice == "2")
		{
			viewHighScores();
		}
		else if (choice == "3")
		{
			cout << "\nExiting Game... Goodbye!\n";
			system("pause");
		}
		else
		{
			cout << "\n(Error) Invalid Choice! Try again.\n";
			system("pause");
		}
	} while (choice != "3");
}