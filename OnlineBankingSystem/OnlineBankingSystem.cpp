#include <iostream>
using namespace std;

class BankAccount {
protected:
    string accountNumber;
    string accountHolderName;
    double balance;
public:
    BankAccount(string accNum, string accHolderName, double initialBalance) {
        this->accountNumber = accNum;
        this->accountHolderName = accHolderName;
        this->balance = initialBalance;
    }

    void deposit(double amount) {
        this->balance += amount;
        cout << "Deposited amount is " << amount << ". New Balance is " << this->balance << endl;
    }

    virtual bool withdraw(double amount) {
        if (this->balance >= amount) {
            this->balance -= amount;
            cout << "Withdrawn Amount is " << amount << ". New balance is " << this->balance << endl;
            return true;
        }
        cout << "Insufficient funds." << endl;
        return false;
    }

    void displayBalance() {
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Current Balance: $" << balance << endl;
    }

    virtual ~BankAccount() {};
};

class SavingAccount : public BankAccount {
private:
    double interestRate;
public:
    SavingAccount(string accNum, string accHolderName, double initialBalance, double rate)
        : BankAccount(accNum, accHolderName, initialBalance), interestRate(rate) {}

    void applyInterest() {
        double interest = balance * (interestRate / 100);
        balance += interest;
        cout << "Interest applied: " << interest << ". New Balance: $" << balance << endl;
    }
};

class CheckingAccount : public BankAccount {
private:
    double overdraftLimit;

public:
    CheckingAccount(string accNum, string accHolder, double initialBalance, double overdraft)
        : BankAccount(accNum, accHolder, initialBalance), overdraftLimit(overdraft) {}

    bool withdraw(double amount) override {
        if (balance + overdraftLimit >= amount) {
            balance -= amount;
            cout << "Withdrawn: " << amount << ". New balance: " << balance << endl;
            return true;
        }
        cout << "Withdrawal denied: Exceeds overdraft limit." << endl;
        return false;
    }

    void applyOverdraft() {
        if (balance < 0) {
            cout << "Overdraft applied. Current balance: $" << balance << endl;
        }
    }
};

int main() {
    BankAccount* account = nullptr;  
    int accountType, choice;
    double amount;

    cout << "Choose account type: \n1. Savings Account\n2. Checking Account\n";
    cin >> accountType;

    string accNumber, accHolder;
    double initialBalance;

    cout << "Enter Account Number: ";
    cin >> accNumber;
    cout << "Enter Account Holder Name: ";
    cin >> accHolder;
    cout << "Enter Initial Balance: ";
    cin >> initialBalance;

    if (accountType == 1) {
        double interestRate;
        cout << "Enter Interest Rate: ";
        cin >> interestRate;
        account = new SavingAccount(accNumber, accHolder, initialBalance, interestRate);
    }
    else if (accountType == 2) {
        double overdraftLimit;
        cout << "Enter Overdraft Limit: ";
        cin >> overdraftLimit;
        account = new CheckingAccount(accNumber, accHolder, initialBalance, overdraftLimit);
    }

    do {
        cout << "\n\nBanking Menu:\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Display Balance\n";
        cout << "4. Apply Interest (for Savings Account)\n";
        cout << "5. Apply Overdraft (for Checking Account)\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter deposit amount: ";
            cin >> amount;
            account->deposit(amount);
            break;

        case 2:
            cout << "Enter withdraw amount: ";
            cin >> amount;
            account->withdraw(amount);
            break;

        case 3:
            account->displayBalance();
            break;

        case 4:
            if (SavingAccount* savings = dynamic_cast<SavingAccount*>(account)) {
                savings->applyInterest();
            }
            else {
                cout << "This option is only available for Savings Account.\n";
            }
            break;

        case 5:
            if (CheckingAccount* checking = dynamic_cast<CheckingAccount*>(account)) {
                checking->applyOverdraft();
            }
            else {
                cout << "This option is only available for Checking Account.\n";
            }
            break;

        case 6:
            cout << "Exiting..." << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (choice != 6);

    delete account;

    return 0;
}
