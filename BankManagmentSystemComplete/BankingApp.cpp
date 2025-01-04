#include "sarmadheader.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Transaction {
    string type = "";
    int amount = 0;
};

struct Account {
    int accountNo = 0;
    string holderName = "";
    int balance = 0;
};

struct Bank {
    Account accounts[50] = {};
    string bankName = "";
    int accountCount = 0;
};

// Function Prototypes
void listOfAccount(Bank& bank);
void createnewaccount(Bank& bank);
void searchAccount(Bank& bank);
void accessAccount(Bank& bank);
void depositMoney(Account& account);
void withdrawMoney(Account& account);
void viewBalance(const Account& account);
void viewTransactionHitory(const Account& account);
void storeTransactionHistory(const Account& account, const Transaction& transaction);
void pressEnterToContinue();

int main() {
    Bank bank;
    bank.bankName = "Alfalah Bank";
    bank.accountCount = 0;

    PrintWelcomeMessage();
    cout << ":" << endl;

    int choice;
    bool running = true;

    while (running) {
        system("cls");   // Added to Clear Screen After any Option is Selected
        PrintWelcomeMessage();
        cout << ":" << endl;

        cout << " 1. Create New Account" << endl;
        cout << " 2. Access Your Account" << endl;
        cout << " 3. Search By Account Number" << endl;
        cout << " 4. List Of Accounts" << endl;
        cout << " 5. Exit Application" << endl;

        cout << "Enter Your Choice" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
            system("cls");
            cout << "----Create New Account----" << endl;
            createnewaccount(bank);
            pressEnterToContinue();
            break;

        case 2:
            system("cls");
            cout << "----Access Your Account----" << endl;
            accessAccount(bank);
            pressEnterToContinue();
            break;

        case 3:
            system("cls");
            cout << "----Search By Account Number----" << endl;
            searchAccount(bank);
            pressEnterToContinue();
            break;

        case 4:
            system("cls");
            cout << "----List Of Accounts----" << endl;
            listOfAccount(bank);
            pressEnterToContinue();
            break;

        case 5:
            system("cls");
            cout << "----Exit Application----" << endl;
            running = false;
            break;
        default:
            cout << "Invalid Choice. Please Select Between 1-5" << endl;
        }
    }
    return 0;
}

void listOfAccount(Bank& bank) {
    cout << "Account No \t Holder Name \t Balance" << endl;
    for (int i = 0; i < bank.accountCount; i++) {
        cout << bank.accounts[i].accountNo << "\t" << bank.accounts[i].holderName << "\t" << bank.accounts[i].balance << endl;
    }
}

void createnewaccount(Bank& bank) {
    if (bank.accountCount == 50) {
        cout << "Maximum Account Limit Reached" << endl;
    }
    else {
        Account tempAccount = {}; // Ensure all fields are initialized
        cout << "Enter Holder's Name: ";
        cin >> tempAccount.holderName;
        bank.accountCount++;
        tempAccount.accountNo = bank.accountCount;
        bank.accounts[bank.accountCount - 1] = tempAccount;
        cout << "Your Account has been Created with Account Number: " << tempAccount.accountNo << endl;
        cout << "Account Holder Name: " << tempAccount.holderName << endl;
        cout << "Account Balance: " << tempAccount.balance << endl;
    }
}

void searchAccount(Bank& bank) {
    int accountno;
    cout << "Enter Account Number to Search: ";
    cin >> accountno;
    for (int i = 0; i < bank.accountCount; i++) {
        if (bank.accounts[i].accountNo == accountno) {
            cout << "Account Found!" << endl;
            cout << "Account Number: " << bank.accounts[i].accountNo << endl;
            cout << "Account Holder Name: " << bank.accounts[i].holderName << endl;
            cout << "Current Balance: " << bank.accounts[i].balance << endl;
            return;
        }
    }
    cout << "Account Not Found" << endl;
}

void accessAccount(Bank& bank) {
    int accountno;
    cout << "Enter Account Number: ";
    cin >> accountno;

    for (int i = 0; i < bank.accountCount; i++) {
        if (bank.accounts[i].accountNo == accountno) {
            Account& account = bank.accounts[i];
            cout << "Welcome, " << account.holderName << "!" << endl;
            cout << " 1. Deposit Money" << endl;
            cout << " 2. Withdraw Money" << endl;
            cout << " 3. View Balance" << endl;
            cout << " 4. View Transaction History" << endl;

            int option;
            cin >> option;

            switch (option) {
            case 1:
                depositMoney(account);
                pressEnterToContinue();
                break;
            case 2:
                withdrawMoney(account);
                pressEnterToContinue();
                break;
            case 3:
                viewBalance(account);
                pressEnterToContinue();
                break;
            case 4:
                viewTransactionHitory(account);
                pressEnterToContinue();
                break;
            default:
                cout << "Invalid Option" << endl;
            }
            return;
        }
    }
    cout << "Account Not Found" << endl;
}

void depositMoney(Account& account) {
    int amount;
    cout << "Enter Amount to Deposit: ";
    cin >> amount;

    account.balance += amount;

    Transaction transaction = { "Deposit", amount };
    storeTransactionHistory(account, transaction);

    cout << "Money Deposited Successfully. New Balance: " << account.balance << endl;
}

void withdrawMoney(Account& account) {
    int amount;
    cout << "Enter Amount to Withdraw: ";
    cin >> amount;
    if (amount > account.balance) {
        cout << "Insufficient Balance" << endl;
    }
    else {
        account.balance -= amount;
        Transaction transaction = { "Withdraw", amount };
        storeTransactionHistory(account, transaction);
        cout << "Money Withdrawn Successfully. New Balance: " << account.balance << endl;
    }
}

void viewBalance(const Account& account) {
    cout << "Your Current Balance: " << account.balance << endl;
}

void viewTransactionHitory(const Account& account) {
    string fileName = "Account_" + to_string(account.accountNo) + "_History.txt";
    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "No Transaction History Available" << endl;
        return;
    }
    string line;
    cout << "Transaction History:" << endl;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

void storeTransactionHistory(const Account& account, const Transaction& transaction) {
    string fileName = "Account_" + to_string(account.accountNo) + "_History.txt";
    ofstream file(fileName, ios::app);
    file << transaction.type << "\t" << transaction.amount << endl;
    file.close();
}

void pressEnterToContinue() {
    cout << "Press Enter to Continue...";
    cin.ignore();
    cin.get();
}