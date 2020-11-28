//Project 4
//Author: Han
//ID: 
//Compile: g++

#include <iostream>

using namespace std;

#define INT_MAX 2147483647

//Define linked list
struct TriviaNode {
    string question;
    string answer;
    int award;
    TriviaNode* next;
};

//Insert new list
TriviaNode* addTrivia(TriviaNode* head, string questionIn, string answerIn, int awardIn) {
    //New list, stroing data
    TriviaNode* newTrivia = new TriviaNode();
    newTrivia -> question = questionIn;
    newTrivia -> answer = answerIn;
    newTrivia -> award = awardIn;
    newTrivia -> next = NULL;

    //Find the last list, set new list is the next of it
    TriviaNode* p = head;
    while (p -> next != NULL) {
        p = p -> next;
    }
    p -> next = newTrivia;
    return head;
}

//Get number of trivia, help judge when testing
int getTriviaSize(TriviaNode* head) {
    int length = 0;
    TriviaNode* p = head;
    while(p -> next != NULL) {
        length++;
        p = p -> next;
    }
    return length;
}

//Ask question and return award obtained
int askQuestion(TriviaNode* p, int award) {
    cout << "Question: " << p -> question << endl;
    cout << "Answer: ";
    int tempAward = award;
    string userAnswer;
    getline(cin, userAnswer);
    if (userAnswer == p -> answer) {
        cout << "Your answer is correct. You receive " << p -> award << " points. " << endl;
        tempAward += p -> award;
    }
    else {
        cout << "Your answer is wrong. The correct answer is: " << p -> answer << endl;
    }
    cout << "Your Total points: " << tempAward << endl;
    cout << endl;
    return tempAward;
}

//Let user answer all question and calculate award
void answerBoard(TriviaNode* head) {
    TriviaNode* p = head;
    if(getTriviaSize(p) < 1) {
        cout << "Warning - the number of trivia to be asked must equal to or be larger than 1. " << endl;
        return;
    }
    int finalAward = 0;
    while(p -> next != NULL) {
        p = p -> next;
        finalAward = askQuestion(p, finalAward);
    }
}

//Get users trivia
TriviaNode* userQuestion() {
    TriviaNode* p = new TriviaNode();
    string userQuestion;
    string userAnswer;
    int userAward = 0;
    string judge;

    for(int i = 0; i < 100; i++) {
        userQuestion = "";
        while (userQuestion.empty()) {
            cout << "Enter a question: ";
            getline(cin, userQuestion);
        }
        userAnswer = "";
        while (userAnswer.empty()) {
            cout << "Enter an answer: ";
            getline(cin, userAnswer);
        }
        userAward = 0;
        while (userAward <= 0) {
            cout << "Enter award points: ";
            cin >> userAward;
        }
        p = addTrivia(p, userQuestion, userAnswer, userAward);
        cout << "Continue? (Yes/No): ";
        cin >> judge;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        if (judge == "No") {
            break;
        }
    }
    cout << endl;
    return p;
}


//Debugging version
void testVersion() {

    cout << "*** This is a debugging version ***" << endl;
    cout << "Unit Test Case 1: Ask no question. The program should give a warning message. " << endl;
    //Case 1, no trivia insert
    TriviaNode* p1 = new TriviaNode();
    answerBoard(p1);
    if (getTriviaSize(p1) >= 1) {
        cout << "Abnormal case" << endl;
        return;
    }
    cout << "Case 1 Passed" << endl;
    cout << endl;

    cout << "Unit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer. " << endl;
    //Case 2, only insert first example trivia
    TriviaNode* p2 = new TriviaNode();
    int testAward2 = 0;
    string question1 = "How long was the shortest war on record? (Hint: How many minutes?)";
    string answer1 = "38";
    int award1 = 100;
    p2 = addTrivia(p2, question1, answer1, award1);
    p2 = p2 -> next;
    testAward2 = askQuestion(p2, testAward2);
    //Fail when answer is correct and get award
    if (testAward2 != 0) {
        cout << "Abnormal case" << endl;
        return;
    }
    cout << "Case 2.1 Passed" << endl;
    cout << endl;

    cout << "Unit Test Case 2.2: Ask 1 question in the linked list. The tester enters a correct answer. " << endl;
    testAward2 = askQuestion(p2, testAward2);
    //Fail when answer is incorrect and don't get award
    if (testAward2 == 0) {
        cout << "Abnormal case" << endl;
        return;
    }
    cout << "Case 2.2 Passed" << endl;
    cout << endl;

    cout << "Unit Test Case 3: Ask all the questions of the last trivia in the linked list. " << endl;
    //Case 3, insert all 3 example trivia
    TriviaNode* p3 = new TriviaNode();
    p3 = addTrivia(p3, question1, answer1, award1);
    string question2 = "What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)";
    string answer2 = "Bank of Italy";
    int award2 = 50;
    p3 = addTrivia(p3, question2, answer2, award2);
    string question3 = "What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)";
    string answer3 = "Wii Sports";
    int award3 = 20;
    p3 = addTrivia(p3, question3, answer3, award3);
    answerBoard(p3);
    cout << "Case 3 Passed" << endl;
    cout << endl;

    cout << "Unit Test Case 4: Ask 5 questions in the linked list. " << endl;
    //Case 4, the number of trivia is not 5
    if (getTriviaSize(p3) == 3) {
        cout << "Abnormal case" << endl;
        return;
    }
    else {
        cout << "Warning - There is only 3 trivia in the list. " << endl;
    }
    cout << "Case 4 Passed" << endl;
    cout << endl;
}

//Change the version by changing the following notes
//#define UNIT_TESTING
int main()
{
    #ifdef UNIT_TESTING
    //Debugging version
    cout << "*** This is a debugging version ***" << endl;
    testVersion();
    cout << "*** End of the Debugging Version ***";
    #else
    cout << "*** Welcome to Han's trivia quiz game ***" << endl;
    TriviaNode* p = userQuestion();
    answerBoard(p);
    cout << "*** Thank you for playing the trivia quiz game. Goodbye! ***";
    #endif

    return 0; 
}
