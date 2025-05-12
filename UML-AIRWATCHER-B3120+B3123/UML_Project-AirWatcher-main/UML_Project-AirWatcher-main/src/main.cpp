/*
AirWatcher - A C++ program to manage air quality monitoring stations.
View -> Command Line Interface (CLI) Main File

*/

// Directives and Libraries

/*
AirWatcher - A C++ program to manage air quality monitoring stations.
View -> Command Line Interface (CLI) Main File

*/

/*
Main : 
- Welcome message
- Menu
    - Sign In
    - Exit
- If sign in successful, start main loop in view

*/

// Directives and Libraries

#include <iostream>
#include "Controller.h"

using namespace std;

int main(int argc, char* argv[]) {
    cout << "Welcome to AirWatcher!" << endl;
    
    Controller controller;
    bool isAuthenticated = false;

    while (true) {
        cout << "\nMenu:" << endl;
        cout << "1. Sign In" << endl;
        cout << "2. Exit" << endl;
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: 
                {
                    if (isAuthenticated) {
                        cout << "Already signed in!" << endl;
                    } else {
                        string userKey;
                        cout << "Enter user login: ";
                        cin >> userKey;
                        isAuthenticated = controller.attemptSignInUser(userKey);
                    }
                    
                    if (isAuthenticated) {
                        controller.mainLoop();
                        isAuthenticated = false; // When view gives control back, it means user has signed out
                    }
                }
                break;
            case 2: 
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}
