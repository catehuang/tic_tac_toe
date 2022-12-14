#include <iostream>
#include <vector>
#include <string>
using namespace std;


void draw_the_board(string snapshot[], int size) {
        string s = "";
        for (int i = 0; i < size; i++) {
                string mark = snapshot[i];
                if (mark.length() == 0) {
                        mark = to_string(i);
                }
                if (i % 3 == 1) {
                        s = "| " + mark + " |";
                } else {
                        s = " " + mark + " ";
                }
                // 2, 5 append a new line
                if (i == 2 || i == 5) {
                        s += "\n";
                }
                 cout << s;
        }
        cout << endl;
}

bool validate_input(string snapshot[], string str) {
        if (str.length() != 1){
                return false;
        }
        if  (!isdigit(str[0])) {
                return false;
        }
        int num = stoi(str);
        if (num > 9 || num < 0) {
                return false;
        }
        if (snapshot[num] != "") {
                return false;
        }
        return true;
}

int generate_number(string snapshot[], int size) {
        vector <int> options;
        for (int i = 0; i < size; i++) {
                if (snapshot[i] == "") {
                        options.push_back(i);
                }
        }
        srand(time(0));
        int nth = rand() % options.size();
        return options[nth];
}

/**
        return -1 if no one wins
        return 1 if player wins
        return 2 if computer wins 
*/
int check_result(string snapshot[], int size, int counter) {
        // can't make a line
        if (counter < 3) {
                return -1;
        }
        // four types of lines:
        // when a = 0, 3, 6 -> a, a+1, a+2
        // when a = 0, 1, 2 -> a, a+3, a+6
        // when a =  0 -> a, a+4, a+8
        // when a = 2 -> a, a+2, a+4
        string a = snapshot[0];
        for (int i= 0; i < size; i += 3) {
                if (snapshot[i] != "" && snapshot[i] == snapshot[i + 1] && snapshot[i + 1] == snapshot[i + 2]) {
                        return snapshot[i] == "O" ? 1 : 2;
                }                
        }
        for (int i = 0; i < 3; i++) {
                if (snapshot[i] != "" && snapshot[i] == snapshot[i + 3] && snapshot[i + 3] == snapshot[i + 6]) {
                        return snapshot[i] == "O" ? 1 : 2;
                }       
        }

        int i = 0;
        if (snapshot[i] != "" && snapshot[i] == snapshot[i +4] && snapshot[i + 4] == snapshot[i + 8]) {
                return snapshot[i] == "O" ? 1 : 2;
         }  

        i = 2;
        if (snapshot[i] != "" && snapshot[i] == snapshot[i +2] && snapshot[i + 2] == snapshot[i + 4]) {
                return snapshot[i] == "O" ? 1 : 2;
         }  

         return -1;
}

// draw the board
// accept input from a user
// computer - random select place to put mark
int main() {
        string snapshot[9];
        string input;
        int counter = 0;
        int num = -1;
        int size = sizeof(snapshot) / sizeof(snapshot[0]);
        bool game_over = false;
        int winner = -1;

        // 0 - new a game // 5 - repeat steps from 1
        while (!game_over) {
                // 1 - print menu 
                counter++;
                draw_the_board(snapshot, size);
                do {
                        // ask for a number 0-9
                        cout << "Choose a place to place your mark (0-9): ";
                        // 2 - read input and validate
                        cin >> input;              
                } while (!validate_input(snapshot, input));
                // assign the mark to the position
                snapshot[stoi(input)] = "O";

                // 3 - draw the board
                // draw_the_board(snapshot, size);

                // 3.1 - is game over? yes -> 6; no -> 4
                winner = check_result(snapshot, size, counter);

                if ( winner == -1  && counter != 9) {
                        // 4 - computer pick up one place to mark
                        counter++;
                        int n = generate_number(snapshot, size); 
                        snapshot[n] = "X";

                        // 4.1 - is game over? yse -> 6; no -> 5
                        winner = check_result(snapshot, size, counter);
                }
                // 6 - print out result
                if (counter == 9 || winner != -1) {
                        draw_the_board(snapshot, size);
                        game_over = true;
                        switch (winner) {
                                case -1:
                                        cout << "Draw";
                                        break;
                                case 1:
                                        cout << "You win!";
                                        break;
                                case 2:
                                        cout << "You lose";        
                                        break;
                                default:
                                        break;
                        }
                        cout << endl;
                }
                // 7 - start a new game or exit
        }
        return 0;
}
