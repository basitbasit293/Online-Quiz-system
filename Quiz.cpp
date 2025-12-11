#include <iostream>
using namespace std;
struct User {
    char name[50];
    char password[50];
    int score;
    char role[10];
    bool active;
};
struct QuizQuestion {
    char text[200];
    char options[4][100];
    int correctAnswer;
    bool skipped;
};
bool isEqual(char str1[], char str2[]) {
    int i = 0;
    while (str1[i] != '\0' || str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return false;
        }
        i++;
    }
    return true;
}
void registerUser(User users[], int size) {
    cout << "Enter your username: ";
    cin >> users[size].name;
    cout << "Create your password: ";
    cin >> users[size].password;
    
    users[size].role[0] = 'u'; users[size].role[1] = 's'; users[size].role[2] = 'e'; users[size].role[3] = 'r'; users[size].role[4] = '\0';
    users[size].score = 0;
    users[size].active = true;
}
bool authenticateUser(User users[], char name[], char pwd[], int totalUsers, char userRole[]) {
    if (isEqual(name, "master") && isEqual(pwd, "secure123")) {
        userRole[0] = 'a'; userRole[1] = 'd'; userRole[2] = 'm'; userRole[3] = 'i'; userRole[4] = 'n'; userRole[5] = '\0';
        return true;
    }
    for (int i = 0; i < totalUsers; i++) {
        if (isEqual(users[i].name, name) && isEqual(users[i].password, pwd) && users[i].active) {
            for (int j = 0; j < 10; j++) {
                userRole[j] = users[i].role[j];
            }
            return true;
        }
    }
    return false;
}
void addNewQuestion(QuizQuestion quiz[], int &questionCount, int &totalScore) {
    cout << "Enter the question text: ";
    cin.ignore();
    cin.getline(quiz[questionCount].text, 200);
    cout << "Provide the 4 answer choices:\n";
    for (int i = 0; i < 4; i++) {
        cout << "Option " << i + 1 << ": ";
        cin.getline(quiz[questionCount].options[i], 100);
    }
    cout << "Enter the number of the correct answer (1-4): ";
    cin >> quiz[questionCount].correctAnswer;
    
    totalScore++;
    questionCount++;
}
void removeQuestion(QuizQuestion quiz[], int &questionCount, int &totalScore, int questionSize) {
    if (questionSize < 1 || questionSize > questionCount) {
        cout << "Invalid question number!" << endl;
        return;
    }
    for (int i = questionSize - 1; i < questionCount - 1; i++) {
        quiz[i] = quiz[i + 1];
    }
    questionCount--;
    
    // Decrease the totalScore when a question is removed
    totalScore--;
}

void showQuestion(QuizQuestion question) {
    cout << question.text << endl;
    for (int i = 0; i < 4; i++) {
        cout << i + 1 << ". " << question.options[i] << endl;
    }
}

void disableAccount(User users[], int totalUsers, char username[]) {
    for (int i = 0; i < totalUsers; i++) {
        if (isEqual(users[i].name, username)) {
            users[i].active = false;
            cout << "User " << username << " has been disabled." << endl;
            return;
        }
    }
    cout << "User not found!" << endl;
}

int main() {
    cout << "----------------------------" << endl;
    cout << "-- Welcome to D Quiz site --" << endl;
    cout << "----------------------------" << endl;

    int totalUsers = 0;
    User users[50];
    
    QuizQuestion quiz1[10] = {
        {"What is the capital of Pakistan?", {"Islamabad", "Karachi", "Lahore", "Faisalabad"}, 1, false},
        {"Which is the largest continent?", {"Asia", "Africa", "Europe", "Australia"}, 1, false},
        {"What is the largest ocean?", {"Pacific Ocean", "Atlantic Ocean", "Indian Ocean", "Arctic Ocean"}, 1, false},
        {"Who is known as the father of modern physics?", {"Albert Einstein", "Isaac Newton", "Nikola Tesla", "Galileo Galilei"}, 1, false}
    };
    int quiz1Count = 4;
    int quiz1TotalScore = quiz1Count;  // Initialize total score for quiz1

    QuizQuestion quiz2[10] = {
        {"What is the name of Monkey D. Luffy's devil fruit?", {"Gomu Gomu no Mi", "Mera Mera no Mi", "Yami Yami no Mi", "Ito Ito no Mi"}, 1, false},
        {"Which Dragon Ball Z character is known for his Kamehameha attack?", {"Goku", "Vegeta", "Trunks", "Piccolo"}, 1, false},
        {"Who is the main character in Naruto?", {"Naruto Uzumaki", "Sasuke Uchiha", "Sakura Haruno", "Kakashi Hatake"}, 1, false},
        {"What is the name of the protagonist in One Piece?", {"Monkey D. Luffy", "Roronoa Zoro", "Nami", "Sanji"}, 1, false}
    };
    int quiz2Count = 4;
    int quiz2TotalScore = quiz2Count;  // Initialize total score for quiz2

    QuizQuestion quiz3[10] = {
        {"What is the minimum amount required to open a trading account on Binance?", {"$10", "$50", "$100", "No minimum amount required"}, 4, false},
        {"Which of the following payment methods is accepted by Binance?", {"Credit/debit card", "Bank transfer", "Cryptocurrency", "All of the above"}, 4, false},
        {"What is Binance's native cryptocurrency?", {"BNB", "BTC", "ETH", "USDT"}, 1, false},
        {"How many cryptocurrencies does Binance support?", {"Over 500", "Over 100", "Over 300", "Over 700"}, 1, false}
    };
    int quiz3Count = 4;
    int quiz3TotalScore = quiz3Count;  // Initialize total score for quiz3

    int choice;
    char action, username[50], password[50], userRole[10];

    do {
        cout << "-------------------------" << endl;
        cout << "1. Register Account" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "-------------------------" << endl;
        cin >> choice;

        if (choice == 1) {
            registerUser(users, totalUsers);
            cout << "Account created successfully!" << endl;
            totalUsers++;
        } else if (choice == 2) {
            cout << "Enter your username: ";
            cin >> username;
            cout << "Enter your password: ";
            cin >> password;

            if (authenticateUser(users, username, password, totalUsers, userRole)) {
                cout << "Login successful!" << endl;

    if (isEqual(userRole, "admin")) {
          do {
           cout << "Admin Menu: \n";
           cout << "1. Add New Question\n";
           cout << "2. Remove Question\n";
            cout << "3. Manage User Accounts\n";
          cout << "Select an option: ";
           cin >> action;
            switch (action) {
             case '1': {
             int quizChoice;
            cout << "Select quiz to add a question (1 - General Knowledge, 2 - Anime, 3 - Binance): ";
            cin >> quizChoice;
   if (quizChoice == 1) {
  addNewQuestion(quiz1, quiz1Count, quiz1TotalScore);
} else if(quizChoice == 2) {
  addNewQuestion(quiz2, quiz2Count, quiz2TotalScore);
} else if(quizChoice == 3) {
   addNewQuestion(quiz3, quiz3Count, quiz3TotalScore);
} else{
    cout << "Invalid quiz selection!" << endl;
              }
      break;
}
             case '2': {
              int quizChoice;
              cout << "Select quiz to remove a question (1 - General Knowledge, 2 - Anime, 3 - Binance): ";
              cin >> quizChoice;
               if (quizChoice == 1) {
                 int questionSize;
                  cout << "Enter question number to remove (1-" << quiz1Count << "): ";
                   cin >> questionSize;
                   removeQuestion(quiz1, quiz1Count, quiz1TotalScore, questionSize);
                      } else if (quizChoice == 2) {
                      int questionSize;
                        cout << "Enter question number to remove (1-" << quiz2Count << "): ";
                        cin >> questionSize;
                    removeQuestion(quiz2, quiz2Count, quiz2TotalScore, questionSize);
                   } else if(quizChoice == 3) {
                       int questionSize;
                         cout << "Enter question number to remove (1-" << quiz3Count << "): ";
                         cin >> questionSize;
                     removeQuestion(quiz3, quiz3Count, quiz3TotalScore, questionSize);
                   } else{
                                    cout << "Invalid quiz selection!" << endl;
                                }
                                break;
                 }
                 case '3':{
                      char usernameToDisable[50];
                      cout << "Enter username to disable: ";
                      cin >> usernameToDisable;
                      disableAccount(users, totalUsers, usernameToDisable);
                      break;
                  }
                     default:
                    cout << "Invalid choice" << endl;
                  }

                        cout << "Do you want to continue? (y/n): ";
                        cin >> action;
                    }while (action == 'y');
                } else if(isEqual(userRole, "user")) {
                    do{
                        int score = 0;
                        char skippedQuestions[10]; // Array to track skipped questions
                        int skippedCount = 0;
                        cout << "User Menu: \n";
                        cout << "1. Take Quiz\n";
                        cout << "2. Exit\n";
                        cout << "Choose an option: ";
                        cin >> action;
 switch (action) {
    case '1': {
    int quizChoice;
     cout << "Select quiz to take (1 - General Knowledge, 2 - Anime, 3 - Binance): ";
     cin >> quizChoice;
     QuizQuestion *chosenQuiz;
     int quizTotalScore;
     if (quizChoice == 1) {
        chosenQuiz = quiz1;
        quizTotalScore = quiz1TotalScore;
   } else if(quizChoice == 2){
     chosenQuiz = quiz2;
     quizTotalScore = quiz2TotalScore;
   } else if (quizChoice == 3) {
      chosenQuiz = quiz3;
      quizTotalScore = quiz3TotalScore;
   }else{
     cout << "Invalid quiz choice!" << endl;
 break;
}
      for (int i = 0; i < quizTotalScore; i++) {
       showQuestion(chosenQuiz[i]);
       int answer;
       cout << "Enter your answer (1-4) or 5 to skip: ";
       cin >> answer;
       if(answer == chosenQuiz[i].correctAnswer) {
         cout << "Correct!" << endl;
          score++;
  } else if(answer == 5) {
     cout << "Question skipped!" << endl;
      chosenQuiz[i].skipped = true;
      skippedQuestions[skippedCount++] = i; 
      } else{
       cout << "Incorrect! Correct answer: " << chosenQuiz[i].options[chosenQuiz[i].correctAnswer - 1] << endl;
         }
       }
         if(skippedCount > 0){
  char tryAgain;
     cout << "\nYou have skipped some questions. Would you like to try them again? (y/n): ";
     cin >> tryAgain;
   if(tryAgain == 'y') {
   for (int i = 0; i < skippedCount; i++) {
    int x= skippedQuestions[i];
   showQuestion(quiz1[x]);
cout << "Enter your answer (1-4): ";
   int retryAnswer;
   cin >> retryAnswer;
  if (retryAnswer == quiz1[x].correctAnswer) {
  cout << "Correct!" << endl;
score++;
 } else {
 cout << "Incorrect! Correct answer: " << quiz1[x].options[quiz1[x].correctAnswer - 1] << endl;
        }    }
}
 }
 cout << "Your final score is: " << score << " out of " << quizTotalScore << endl;
    break;
   }
      default:
          cout << "Invalid choice!" << endl;
 }
         cout << "Do you want to continue? (y/n): ";
         cin >> action;
       } while(action == 'y');
     }
            }else{
                cout << "Login failed! Invalid credentials or account is disabled." << endl;
            }
        }else if(choice < 1 || choice > 3) {
     cout << "Invalid selection!" << endl;
        }
    } while (choice != 3);
    return 0;
}
