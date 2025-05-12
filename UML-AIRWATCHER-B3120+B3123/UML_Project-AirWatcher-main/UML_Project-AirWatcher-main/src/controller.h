#ifndef CONTROLLER_H
#define CONTROLLER_H


#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include "Account.h"
#include "Model.h"
#include "View.h"
using namespace std;

typedef struct {
    string title;
    vector<string> options;
} Menu;

class Controller {
    public:
        // Constructor
        Controller();
        
        // Destructor
        ~Controller();
        
        // Public Member Functions
        string loadPrivilegedMenu();

        bool selectOption(int option);

        bool attemptSignInUser(string key);

        void signOutUser();

        void mainLoop();

        vector<Account> showAvailableAccounts();

    private:
        
        Account account;
        Model model;
        AirWatcherView view;
        
        Menu adminMenu = {
            "Admin Menu",
            {
                "4. Sign Out"
            }
        };

        Menu userMenu = {
            "User Menu",
            {
                "4. Sign Out"
            }
        };

        Menu publicInstitutionMenu = {
            "Public Institution Menu",
            {
                "1. Show 10 most recent sensor readings",
                "2. Calculate mean air quality over area",
                "3. Rank sensors by similarity",
                "4. Sign Out"
            }
        };

        Menu providerMenu = {
            "Provider Menu",
            {
                "4. Sign Out"
            }
        };
};

#endif