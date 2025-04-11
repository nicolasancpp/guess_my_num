// Full namde: Nikolas Antoniou
// ID: U234N0848
// Course: Programming Principles II | COMP-113

/* This program reads the name of a user and then asks him/her to think of a number within some limits.
   The program then displays a number of tables asking the user if his/her secret number is displayed or not.
   In the end, the program will guess the user's number. 
*/

#include <iostream>
#include <string> // for string manipulation
#include <cmath>
#include <cstdlib> // for random facts
#include <ctime>   // for random number generator
#include <thread>
#include <chrono>
#include <limits> // for numeric limits

const int MAX = 10; // max bits size
int answer[MAX];    // binary array representation
int size;           // bits size

struct user {
    std::string name;
    int bits;
};

// Function prototypes
void initialize_user(user *u);
void fun_fact();
void fun_statistics(const user *u);
int difficulty();
void table_creation(int position, int bits);
int guessing(user *u);
void display_binary_num(int position);

// Main program
int main() 
{
    // Seed the random number generator
    std::srand(std::time(0));

    // Declare the user
    user you;

    // Initialize the user
    initialize_user(&you);

    std::this_thread::sleep_for(std::chrono::seconds(1)); // Delay of 1 second

    // Prompt the user to select the difficulty level
    std::cout << "Are you ready?\n";
    you.bits = difficulty();

    std::this_thread::sleep_for(std::chrono::seconds(1)); // Delay of 1 second

    // Guessing user's number
    std::cout << "Close your eyes, " << you.name << " and think of a number...\nLeT's BeGiN!\n";
    int guessed_num = guessing(&you);

    std::this_thread::sleep_for(std::chrono::seconds(1)); // Delay of 1 second

    // Display the guessed number
    std::cout << "\n" << you.name << ", the number which made my nerves leave my transistors is: " << guessed_num << "!\n";

    std::this_thread::sleep_for(std::chrono::seconds(1)); // Delay of 1 second

    // Fun stats
    fun_statistics(&you);

    std::this_thread::sleep_for(std::chrono::seconds(1)); // Delay of 1 second

    // Fun facts
    fun_fact();

    return 0;
}

// Initialization of the user
void initialize_user(user *u) 
{
    std::cout << " ----Well, well, well---- \n";
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Delay of 1 second

    std::cout << "WeLcOmE tO tHiS cRaZy GaMe!\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Delay of 1 second

    std::cout << "Today I will try to guess your little secret number, but if I don't, don't be judgy! Be kind, I didn't have my coffee yet!\n";
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Delay of 1 second

    std::cout << "Your time to shine, what's your name?\n";

    if (std::cin.peek() == '\n')
    {
        std::cin.ignore();
    }
    std::getline(std::cin, u->name);

    std::cout << "Nice to meet you " << u->name << "!\n";
}

// Fun fact function
void fun_fact() 
{
    std::cout << "\n---- FuN fAcT ----\nDid you know lil human that...\n";

    // random facts
    const char* facts[] = {
        "The first computer bug was an actual BUG?!\n",
        "Apple's and Google's operating systems are more advanced than NASA's spacecraft programs?\n",
        "Coding helps people evolve their critical thinking and mathematical skills.\n",
        "Ada Lovelace, the first programmer, was the daughter of the Mad Poet, Lord Byron.\n"
    };

    // printing the random facts
    int num_facts = sizeof(facts) / sizeof(facts[0]);
    int random_pos = rand() % num_facts;
    std::cout << facts[random_pos] << std::endl;
}

// Game's statistics function
void fun_statistics(const user *u) 
{
    int max = (1 << u->bits) - 1; 
    std::cout << "\n---- GaMe StAts ----\n";
    std::cout << "Player: " << u->name << "\n";
    std::cout << "Number of bits used: " << u->bits << std::endl;
    std::cout << "Range of possible numbers: 1-" << max << std::endl;
    std::cout << "Total tables displayed: " << u->bits << std::endl;
    std::cout << "The guessing algorithm only used " << u->bits << " steps to find your number.\n";
}

// Difficulty function
int difficulty() 
{
    int choice;
    std::cout << "\nWhat level do you want it to be?\n";
    std::cout << "1. EaSy (3 bits: 1-7)\n";
    std::cout << "2. MeDiUm (5 bits: 1-31)\n";
    std::cout << "3. HaRd (6 bits: 1-63)\n";

    do 
    {
        std::cout << "Enter your choice (1-3): ";
        std::cin >> choice;

        if (std::cin.fail()) 
        {
            // Clear invalid input
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Sorry HuMaN, your input is invalid! Between 1-3!\n";
        } else if (choice < 1 || choice > 3) 
        {
            std::cout << "Sorry HuMaN, your input is invalid! Between 1-3!\n";
        }
    } while (choice < 1 || choice > 3);

    switch (choice) 
    {
        case 1:
            return 3; // Easy

        case 2:
            return 5; // Medium

        case 3:
            return 6; // Hard

        default:
            return 3; // Default (shouldn't reach here)
    }
}

// Table creation function
void table_creation(int position, int bits) 
{
    std::cout << "\nTable " << position << ": ";

    int max = (1 << bits) - 1; // 2^bits - 1

    for (int i = 1; i <= max; i++) 
    {
        if ((i >> (position - 1)) & 1) 
        { // Check if bit is set at position
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
}

// Guessing the number function
int guessing(user* u) 
{
    for (int position = 1; position <= u->bits; position++) 
    {
        // Display the table
        table_creation(position, u->bits);

        char response;
        bool valid_input = false;

        // Ask if the number is in the table
        do 
        {
            std::cout << "Is your number in the table above? (y/n): ";
            std::cin >> response;

            if (response == 'y' || response == 'Y') 
            {
                answer[position - 1] = 1;
                valid_input = true;
            } else if (response == 'n' || response == 'N') 
            {
                answer[position - 1] = 0;
                valid_input = true;
            } else 
            {
                std::cout << "Invalid input! Please enter 'y' or 'n'.\n";
            }
        } while (!valid_input);

        // Display updated binary answer
        display_binary_num(position);
    }

    // Convert binary to decimal
    int secret_num = 0;
    for (int i = 0; i < u->bits; i++) 
    {
        secret_num += answer[i] * (1 << i); // Convert binary to decimal
    }

    return secret_num;
}

// Display the binary result so far
void display_binary_num(int position) 
{
    std::cout << "The answer so far: ";
    for (int i = 0; i < position; i++) 
    {
        std::cout << answer[i] << " ";
    }
    std::cout << std::endl;
}