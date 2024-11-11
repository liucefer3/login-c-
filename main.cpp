#include <iostream>
#include <fstream>
using namespace std;

string green = "\033[32m";
string red = "\033[31m";
string reset = "\033[0m";
string gay = "\033[34m";
string pirpl = "\033[35m";
string yell = "\033[33m";

void registerUser () {
    string newLogin, newPassword;

    cout << yell << "Enter a new "<<pirpl<<"username:\n" << reset;
    cin >> newLogin;

    ifstream inFile("users.txt");
    bool loginTaken = false;

    if (inFile.is_open()) {
        string fileLogin;
        while (getline(inFile, fileLogin)) {
            if (fileLogin == newLogin) {
                loginTaken = true;
                break;
            }
        }
        inFile.close();
    } else {
        return;
    }

    if (loginTaken) {
        cout << red << "This username is already occupied\n" << reset;
        return;
    }

    cout << yell << "Enter a new "<<pirpl<<"password:\n" << reset;
    cin >> newPassword;

    ofstream outFile("users.txt", ios::app);
    if (outFile.is_open()) {
        outFile << newLogin << endl << newPassword << endl;
        outFile.close();
        cout << green << "You have successfully registered" << reset << endl;
    } else {
        cout << red << "Error during registration" << reset << endl;
    }
}

bool loginUser (const string& log, const string& pass) {
    ifstream inFile("users.txt");
    string fileLogin, filePassword;

    if (inFile.is_open()) {
        while (getline(inFile, fileLogin) && getline(inFile, filePassword)) {
            if (fileLogin == log && filePassword == pass) {
                return true; 
                inFile.close();
            }
        }
        inFile.close();
    }
    return false; 
}

int main() {
    int regOrLog;
    cout << gay << "1) Log in\n2) Register\n" << reset;
    cin >> regOrLog;
    if (regOrLog != 1 && regOrLog != 2)
    {
        cout<<red<<"Write a correct answer\n"<<reset;
        return main();
    }
    

    else if (regOrLog == 2) {
        registerUser ();
    }

    while (true) {
        string log, pass;
        cout << pirpl << "\nEnter your username:\n" << reset;
        cin >> log;
        cout << pirpl << "Enter the password:\n" << reset;
        cin >> pass;

        if (loginUser (log, pass)) {
            cout << green << "Hello, " << gay << log << reset << endl;
            break; 
        } else {
            cout << red << "\nThere is no such user in the database" << reset << endl;
            cout << gay << "1) Try again\n2) Register\n" << reset;
            int registerChoice;
            cin >> registerChoice;

            if (registerChoice !=1 && registerChoice !=2){
                cout<<red<<"Write a correct answer\n"<<reset;
                return main();
            }
            if (registerChoice == 2) {
                registerUser ();
            }
        }
    }
    return 0;
}