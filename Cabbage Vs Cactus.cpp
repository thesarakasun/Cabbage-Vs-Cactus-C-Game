#include <iostream> // For standard input/output operations
#include <conio.h> // For _getch() and _kbhit() functions
#include <ctime>  // For handling time-related functions, such as delays
#include <windows.h> // For Windows-specific functions
#include <string> // for handlng string operations
#include <fstream>  // Added for file handling

using namespace std;

// Function to set the cursor position in the console
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Function to create a delay in milliseconds
void delay(unsigned int mseconds) {
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

// Function to draw the initial setup for the game
void getup() {
    system("cls");
    gotoxy(10, 2);
    cout << "Press x to reach main menu";
    gotoxy(10, 3);
    cout << "Press SPACE to Jump";
    gotoxy(10, 4);
    cout << "Press ESC to pause";
    gotoxy(62, 2);
    cout << "SCORE : ";
    gotoxy(1, 25);
    //draws the ground like structure
    for (int x = 0; x < 79; x++)
        cout << (char)223;
}

// Global variables for game state
int t = 0, speed = 40; // t for verticle position and speed to measure the speed
int highestScore = 0;
string highestScorer = "No one";

// Function to load the highest score from a file
void loadHighestScore() {
    ifstream file("score.txt"); //opens file in read mode
    if (file.is_open()) {
        file >> highestScore; //read the highest score
        file.ignore();
        getline(file, highestScorer);//reading the name of highest scorer
        file.close(); //closing the file
    }
}

// Function to save the highest score to a file
void saveHighestScore() {
    ofstream file("score.txt"); //opens file in write mode
    if (file.is_open()) {
        file << highestScore << endl; //save highest score
        file << highestScorer << endl; //save the highest scorer
        file.close();//cloding the file
    }
}

// Function to draw the ball 
// 'jump' parameter is used to control the ball's movement while jumping
void drawBall(int jump = 0) {
    if (jump == 0)
        t = 0; // Reset jump state when not jumping
    else if (jump == 2)
        t--; // Decrease 't' when the ball is falling down
    else
        t++; // Increase 't' when the ball is jumping up

    gotoxy(2, 15 - t);
    cout << "                 ";
    gotoxy(2, 16 - t);
    cout << "        @@@@@@   ";
    gotoxy(2, 17 - t);
    cout << "      @@@@@@@@@  ";
    gotoxy(2, 18 - t);
    cout << "     @@@@@@@@@@@ ";
    gotoxy(2, 19 - t);
    cout << "     @@@@@@@@@@@ ";
    gotoxy(2, 20 - t);
    cout << "      @@@@@@@@@  ";
    gotoxy(2, 21 - t);
    cout << "        @@@@@@   ";
    gotoxy(2, 22 - t);
    cout << "                 ";
    gotoxy(2, 23 - t);
    cout << "                 ";

    if (jump != 0) {
        gotoxy(2, 24 - t);
        cout << "                ";
    } else {
        gotoxy(2, 24 - t);
        cout << "                ";
    }
    delay(speed);
}

// Declare x globally so it can be reset between games
int x = 0;

// Function to handle cactus (obstacle) movement and collision
void obj(string playerName, bool &gameOver, int &scr) {
    if (x == 56 && t < 4) {
        if (scr > highestScore) {
            highestScore = scr;
            highestScorer = playerName;
            saveHighestScore();  // calling the fumction to save new highest score to the file
        }
        scr = 0; //reset the speed
        speed = 40; //reset the score
        gotoxy(36, 8);
        cout << "Game Over";
        gameOver = true; //set gameOver flag using bool
        getch();
        gotoxy(36, 8);
        cout << "         "; // used to clear game over message
    }
    //drawing the cactus using 'Û' symbols 
    gotoxy(74 - x, 20);
    cout << "Û    Û ";
    gotoxy(74 - x, 21);
    cout << "Û    Û ";
    gotoxy(74 - x, 22);
    cout << "ÛÜÜÜÜÛ ";
    gotoxy(74 - x, 23);
    cout << "  Û    ";
    gotoxy(74 - x, 24);
    cout << "  Û  ";
    x++;
    // Reset cactus position and increase the score when it goes off the screen
    if (x == 73) {
        x = 0; //horizontal position varibale is set to 0
        scr++; //score is incremented
        //below 4 lines state how ol score is deleted and new score is added to console
        gotoxy(70, 2);
        cout << "     ";
        gotoxy(70, 2);
        cout << scr;
        
        /*In the code, the speed variable is controlling the delay between each frame
		 of the game. As the game progresses, the speed value is decreased to make the game run faster.*/
        
        if (speed > 20)
            speed--;
    }
}

// Function to display the game instructions
void instructions() {
    system("mode con: lines=30 cols=120");//set console sze

    system("cls");
    gotoxy(0, 0);
    cout << "                                                                                                                                 " << endl;
    cout << "                                                                                                                                 " << endl;
    cout << "                                                                                                                                 " << endl;
    cout << "                                                                                                                                 " << endl;
    cout << "                       ________________________________________________________________________________                          " << endl;
    cout << "                      |                                  INSTRUCTIONS                                  |                         " << endl;
    cout << "                      |________________________________________________________________________________|                         " << endl;
    cout << "                      |  Your task : Destroy all Cactuses invading the Cabbage kingdom.                |                         " << endl;
    cout << "                      |                                                                                |                         " << endl;
    cout << "                      |  1. You can press SPACE to jump onto cactuses                                  |                         " << endl;
    cout << "                      |  2. You can press lowercase x to reach the main menu                           |                         " << endl;
    cout << "                      |  3. Destroy Cactuses as much as possible to reach the highest score            |                         " << endl;
    cout << "                      |  4. You can press ESC to pause the game                                        |                         " << endl;
    cout << "                      |                                                                                |                         " << endl;
    cout << "                      |  Keyboard keys you can use;                                                    |                         " << endl;
    cout << "                      |    SPACE         - To Jump                                                     |                         " << endl;
    cout << "                      |    x             - Reach Menu                                                  |                         " << endl;
    cout << "                      |    Esc           - To pause                                                    |                         " << endl;
    cout << "                      |                                                                                |                         " << endl;
    cout << "                      |                             Happy Destroying :)                                |                         " << endl;
    cout << "                      |________________________________________________________________________________|                         " << endl;
    cout << "\nPress any key to go back to the menu..." << endl;    
    getch();
}

// Function to display the main menu
void displayMenu() {
    system("mode con: lines=29 cols=82");
    
    system("cls");
    gotoxy(35, 10);
    cout << "1. Start Game";
    gotoxy(35, 12);
    cout << "2. Highest Score";
    gotoxy(35, 14);
    cout << "3. Instructions";
    gotoxy(35, 16);
    cout << "4. Exit";
    gotoxy(35, 18);
    cout << "Select an option: ";
}

// Function to start the game
void startGame() {
    system("mode con: lines=29 cols=82");
    char ch;
    int i;
    string playerName;
    bool gameOver = false;
    bool paused = false;
    int scr = 0;

    // Reset x when the game starts to prevent the cactus from striking immediately
    x = 0;

    system("cls");
    gotoxy(35, 10);
    cout << "Enter your name: "; //get player name
    gotoxy(51, 10);
    cin >> playerName;

    getup(); //setup initil game screen
    
    while (true) {
        if (!paused && !gameOver) {
            while (!kbhit() && !gameOver) {
                drawBall();
                obj(playerName, gameOver, scr);
            }
        }

        if (gameOver) break; //exit the loop if game is over

        ch = getch();
        //jumping scenario
        if (ch == ' ') {
            for (i = 0; i < 10; i++) {
                drawBall(1); //jump up
                obj(playerName, gameOver, scr);
                if (gameOver) break;
            }
            if (gameOver) break;
            for (i = 0; i < 10; i++) {
                drawBall(2); //fall down
                obj(playerName, gameOver, scr);
                if (gameOver) break;
            }
        //exiting to main menu scenario
        } else if (ch == 'x') {
            break;
        //Pausing the game
        } else if (ch == 27) {
            paused = !paused; // Toggle pause if ESC is pressed
            if (paused) {
                gotoxy(35, 12);
                // Display pause message
                cout << "Game Paused. Press 'Esc' to resume.";
            } else {
                gotoxy(35, 12);
                // Clear pause message
                cout << "                                   ";
            }
        }
    }
}

// Function to display the title
void cac() {
    gotoxy(28, 7);
    cout << "------------Cabbage Vs Cactus------------" << endl;
}

// Main function
int main() {
    // Calling the highest score function from the file at the start of the game
    loadHighestScore();

    char choice;
    do {
        displayMenu();
        cac();
        choice = getch();//get user choice as a char
        //witching cases depending on users choice
        switch (choice) {
            case '1':
                startGame();
                break;
            case '2':
                system("cls");
                gotoxy(35, 10);
                cout << "Highest Score: " << highestScore << endl;
                gotoxy(35, 12);
                cout << "Scored by: " << highestScorer << endl;
                gotoxy(35, 14);
                cout << "Press any key to go back to the menu... "  << endl;
                getch(); //waiting for user input
                break;
            case '3':
                instructions();
                break;
            case '4':
                break;
            default:
                system("cls");
                cout << "Invalid choice. Please select a valid option.\n";
                cout << "Press any key to continue...";
                getch();
                break;
        }
    } while (choice != '4'); // Repeat until user selects option to exit(4)

    return 0;
}

