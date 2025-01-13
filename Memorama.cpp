//Author: Christopher Espinosa
//Date: 12-January-2024
//Description: Simulation of the memorama game using C++
/**********************************************************************************************************/
//Inclusion of preprocessing directives
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <string>
#ifdef _WIN32
#include <Windows.h>
#endif
//This struct is in charge to contain the functions related to the system
struct System {
//This function will able printing emojis in the console by allowing UTF - 8
void allowEmojis() {
#ifdef _WIN32
system("chcp 65001");
#endif
}
//Function to clear the console 
void clearScreen() {
#ifdef _WIN32
system("cls");
#else
system("clear");
#endif
}
//Function to count time and call the "clearScreen" function
void clearScreenAfterTime(int seconds) {
std::time_t startTime = std::time(nullptr);
std::cout << "The cards will hide after " << seconds << " seconds..." << std::endl;
while (std::time(nullptr) - startTime < seconds);
clearScreen();
}
};
//This struct is in charge to contain some of the functions and variables related to the game functionality
struct Game {
//This boolean vector will contain the if the card is already revealed or unrevealed
std::vector<bool> cards;
//This strings vector contains 100 emojis just to call the necessaries depending on the board size (n x n)
std::vector<std::string> emojis = {
" 🙄", " 😏", " 😣", " 😥", " 😮", " 👽", " 😯", " 😪", " 😎", " 😍",
" 🧐", " 😈", " 👿", " 👺", " 🙈", " 🥙", " 🍨", " 🐺", " 😀", " 😁",
" 😂", " 🤡", " 😃", " 😨", " 😅", " 😆", " 😉", " 😭", " 👻", " 😋", 
" 😶", " 🥎", " ⚽", " 🏀", " 🏐", " 🔕", " 😻", " 😼", " 😘", " 🤓", 
" 👽", " 🟨", " 🍪", " 😱", " 😝", " 🐸", " 😷", " 😡", " 👀", " 🤢" 
};


//Vector to store the suffled emojis
std::vector<std::string> shuffledEmojis;
int size;
//This function ask for an user input to store the value on the size variable
int getSize(){
std::cout << "Introduce the size for the board game (n x n): ";
std::cin >> size;
return size;
}
//Check that the size is even, greater than 0
void validSizeInput() {
do {
getSize();
if (size <= 0 || size > 10 || size % 2 != 0) {
std::cout << "The input has to be even, greater than 0 and equal or minor than 10. Try again."<<std::endl;
}
} while (size <= 0 || size > 10 || size % 2 != 0);
}
//This function generates a pseudorandom quality index
int getRandomIndex() {
static std::random_device rd;
static std::mt19937 mt(rd());
std::uniform_int_distribution<int> randomIndex(0, size * size - 1);
return randomIndex(mt);
}
//Generate the random board
void generateBoard() {
shuffledEmojis.clear();
cards.clear();
// Add an emoji twice into the vector
int totalCards = size * size;
for (int i = 0; i < totalCards / 2; ++i) {
shuffledEmojis.push_back(emojis[i]); // First card of the pair 
shuffledEmojis.push_back(emojis[i]); // Second card of the pair
}
// Shuffle the emojis
for (int i = totalCards - 1; i > 0; i--) {
int j = getRandomIndex();
std::string temp = shuffledEmojis[i];
shuffledEmojis[i] = shuffledEmojis[j];
shuffledEmojis[j] = temp;
}}
//Initializing the boolean vector with unrevealed cards
void initBoolVector(){
for (int i = 0; i < size * size; i++) {
cards.push_back(false);
}
}
//Prints the board with unrevealed or revealed cards
void printBoard() {
for (int i = 0; i < size * size; ++i) {
if (cards[i]) {
std::cout << "     " << shuffledEmojis[i];
} else {
std::cout << "      ❓";
}
if ((i + 1) % size == 0) std::cout << std::endl;
}
std::cout << std::endl;
}
//Prints all the emojis in the board 
void printUnmaskedBoard() {
for (int i = 0; i < size * size; ++i) {
std::cout << "      " << shuffledEmojis[i];
if ((i + 1) % size == 0) std::cout << std::endl;
}
std::cout << std::endl;
}
//Verify if the selected coordenates are in range for the board size
bool isValidCoordinate(int x, int y) {
if (x < 1 || x > size || y < 1 || y > size) {
return false;
}
return true;
}
//Transform 2D coordenates to 1D coordenates
int getLinearIndex(int x, int y) {
return (x - 1) * size + (y - 1);
}
//Flip the cards choosed and keep it visible if they are the same 
void revealCards(int index1, int index2) {
std::cout << "\nCard 1: " << shuffledEmojis[index1] << std::endl;
std::cout << "card 2: " << shuffledEmojis[index2] << std::endl;
//if the emojis are the same let the user know he found a match
if (shuffledEmojis[index1] == shuffledEmojis[index2]) {
std::cout << "Congratulations! You found the same emoji.\n";
cards[index1] = true;
cards[index2] = true;
} else {
std::cout << "The emojis does not match. Try again.\n";
}
std::cout << "Press Enter to continue...";
std::cin.ignore();
std::cin.get();
}
//Function to evaluate if all of the board has been revealed
bool allCardsRevealed() {
for (int i = 0; i < size * size; i++) {
if (cards[i] == false) {
return false;
}
}
return true;
}
//Function to execute the firsts steps of the game
void initializeGame() {
validSizeInput();
generateBoard();
initBoolVector();
}
//Show the placement for all the emojis
void showInitialBoard() {
std::cout << "\nTime to memorize!\n";
printUnmaskedBoard();
}
//Make x and y pass as a reference and not a copy so they can be used later
//we will pass a string but with const and making it a reference to avoid copying the value and only reading it
void getValidCoordinates(int& x, int& y, const std::string& cardNumber)
{
do {
std::cout << std::endl << "Enter the coordenates for the " << cardNumber << " card (x y): ";
std::cin >> x >> y;
if(!isValidCoordinate(x, y)) {
std::cout << "No valid coordenates, try again." <<
std::endl;
}
} while (!isValidCoordinate(x, y));
}
//Function to verify if the elected coordenates are not the same
bool isSameIndexes(int index1, int index2){
return index1 == index2;
}
//Check if the elected card was already revealed before  
bool isAlreadyRevealed(int index1, int index2){
return cards[index1] || cards[index2];
}
//Function to do all the card selection process
bool processCardSelection() {
//Declaration of the 4 variables to select coordenates
int x1, y1, x2, y2;
getValidCoordinates(x1, y1, "first");
getValidCoordinates(x2, y2, "second");
int index1 = getLinearIndex(x1, y1);
int index2 = getLinearIndex(x2, y2);
if(isSameIndexes(index1 , index2)){
std::cout << "You select the same card, try again." << std::endl;
std::cout << "Press Enter to continue...";
std::cin.ignore();
std::cin.get();
return false;
}
if(isAlreadyRevealed(index1, index2)) {
std::cout << "One of the card are been already revealed before, try again." << std::endl;
std::cout << "Press Enter to continue...";
std::cin.ignore();
std::cin.get();
return false;
}
//If the process did not return a false, flip the cards and show it to the user
revealCards(index1, index2);
return true;
}
//Tell the user he won the game
void showGameComplete() {
std::cout << "Congratulaions! You win.\n";
printUnmaskedBoard();
}
};
int main() {
System system;
Game game;
system.allowEmojis();
game.initializeGame();
game.showInitialBoard();
system.clearScreenAfterTime(game.size * game.size / 2);
int maxTurns = (game.size * game.size / 2) + 1;
int turns = 1;
//Only give to the user size / 2 + 1 opportunities to select cards
while(turns <= maxTurns) {
// First of all, we need to clean the screen
system.clearScreen();
std::cout << "This is your turn #" << turns << " of "<<
maxTurns<<" in total." << std::endl;
//Execute the process card selection 
game.printBoard();
if(game.processCardSelection()){
//If all of the cards have been revealed the user have won
if(game.allCardsRevealed()) {
system.clearScreen();
std::cout << "Ypu have won in " << turns << " turns!" <<
std::endl;
game.showGameComplete();
return 0;
}
turns++;
}
}
//If turns > maxTurns the user loses
system.clearScreen();
std::cout << "No turns left. End of the game!" << std::endl;
return 0;
}