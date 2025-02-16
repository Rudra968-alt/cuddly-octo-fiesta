#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class BankAccount
{
private:
    int accountNumber;
    string name;
    double balance;

public:
    BankAccount() : accountNumber(0), balance(0.0) {}

    void createAccount()
    {
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Initial Deposit: ";
        cin >> balance;

        ofstream outFile("bank_data.txt", ios::app);
        outFile << accountNumber << " " << name << " " << balance << endl;
        outFile.close();

        cout << "Account Created Successfully!\n";
    }

    static void displayAccounts()
    {
        ifstream inFile("bank_data.txt");
        int accNo;
        string accName;
        double accBalance;

        cout << "\nAccount Details:\n";
        while (inFile >> accNo >> ws)
        {
            getline(inFile, accName);
            inFile >> accBalance;
            cout << "Account No: " << accNo << " | Name: " << accName << " | Balance: $" << accBalance << endl;
        }
        inFile.close();
    }

    static void updateAccount(int accNumber, double amount, bool isDeposit)
    {
        ifstream inFile("bank_data.txt");
        ofstream tempFile("temp.txt");
        int accNo;
        string accName;
        double accBalance;
        bool found = false;

        while (inFile >> accNo >> ws)
        {
            getline(inFile, accName);
            inFile >> accBalance;

            if (accNo == accNumber)
            {
                found = true;
                if (isDeposit)
                {
                    accBalance += amount;
                    cout << "Deposited $" << amount << " successfully!\n";
                }
                else
                {
                    if (amount > accBalance)
                    {
                        cout << "Insufficient Balance!\n";
                        tempFile.close();
                        inFile.close();
                        remove("temp.txt");
                        return;
                    }
                    accBalance -= amount;
                    cout << "Withdrawn $" << amount << " successfully!\n";
                }
            }
            tempFile << accNo << " " << accName << " " << accBalance << endl;
        }

        inFile.close();
        tempFile.close();

        remove("bank_data.txt");
        rename("temp.txt", "bank_data.txt");

        if (!found)
        {
            cout << "Account not found!\n";
        }
    }

    static void deleteAccount(int accNumber)
    {
        ifstream inFile("bank_data.txt");
        ofstream tempFile("temp.txt");
        int accNo;
        string accName;
        double accBalance;
        bool found = false;

        while (inFile >> accNo >> ws)
        {
            getline(inFile, accName);
            inFile >> accBalance;

            if (accNo == accNumber)
            {
                found = true;
                cout << "Account " << accNo << " deleted successfully!\n";
                continue;
            }
            tempFile << accNo << " " << accName << " " << accBalance << endl;
        }

        inFile.close();
        tempFile.close();

        remove("bank_data.txt");
        rename("temp.txt", "bank_data.txt");

        if (!found)
        {
            cout << "Account not found!\n";
        }
    }
};

int main()
{
    BankAccount account;
    int choice, accNumber;
    double amount;

    do
    {
        cout << "\n--- Bank Management System ---\n";
        cout << "1. Create Account\n";
        cout << "2. Display Accounts\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Delete Account\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            account.createAccount();
            break;
        case 2:
            BankAccount::displayAccounts();
            break;
        case 3:
            cout << "Enter Account Number: ";
            cin >> accNumber;
            cout << "Enter Amount to Deposit: ";
            cin >> amount;
            BankAccount::updateAccount(accNumber, amount, true);
            break;
        case 4:
            cout << "Enter Account Number: ";
            cin >> accNumber;
            cout << "Enter Amount to Withdraw: ";
            cin >> amount;
            BankAccount::updateAccount(accNumber, amount, false);
            break;
        case 5:
            cout << "Enter Account Number to Delete: ";
            cin >> accNumber;
            BankAccount::deleteAccount(accNumber);
            break;
        case 6:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid Choice! Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
