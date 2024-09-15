#include <iostream>
#include <fstream>
using namespace std;

class Bank {
private:
    string name;
    string Account_number;
    double balance;
    string contact;
    string email;
    string address;
    string acc_password;

    void displayHeader(const string &title) {
        cout << "\t\t\t========================================" << endl;
        cout << "\t\t\t          " << title << endl;
        cout << "\t\t\t========================================" << endl;
    }

public:
    string getName();
    string getAccountNumber();
    void menu();
    void adminlogin();
    void admin();
    void newaccount();
    void modifyaccount();
    void deleteaccount();
    void deposit();
    void user();
    void user_info();
    void send_money();
};

string Bank::getName(){
    return name;
}

string Bank::getAccountNumber(){
    return Account_number;
}

void Bank::menu() {
    int choice;

    while (true) {
        system("cls");
        displayHeader("Bank Main Menu");
        cout << "\t\t\t\t\t 1.ADMIN" << endl;
        cout << "\t\t\t\t\t 2.USER" << endl;
        cout << "\t\t\t\t\t 3.EXIT" << endl;
        cout << "\t\t\t\tEnter choice: "; 
        cin >> choice;

        switch (choice) {
            case 1:
                adminlogin();
                break;
            case 2:
                user();
                break;
            case 3:
                exit(0);
            default:
                cout << "\t\t\t\nInvalid choice. Please try again." << endl;
        }
        cin.ignore();
        cin.get();
    }
}

void Bank::adminlogin() {
    string username, password;
    displayHeader("Admin Login");
    cout << "\t\t\tUsername: ";
    cin >> username;
    cout << "\t\t\tPassword: ";
    cin >> password;
    if (username == "admin" && password == "admin123") {
        admin();
    } else {
        cout << "\t\t\tInvalid username or password." << endl;
    }
}

void Bank::admin() {
    int choice;

    while (true) {
        system("cls");
        displayHeader("Admin Menu");
        cout << "\t\t\t1. Create New Account" << endl;
        cout << "\t\t\t2. Delete Account" << endl;
        cout << "\t\t\t3. Modify Account" << endl;
        cout << "\t\t\t4. Deposit" << endl;
        cout << "\t\t\t5. Exit" << endl;
        cout << "\t\t\tEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                newaccount();
                break;
            case 2:
                deleteaccount();
                break;
            case 3:
                modifyaccount();
                break;
            case 4:
                deposit();
                break;
            case 5:
                return;
            default:
                cout << "\t\t\tInvalid choice. Please try again." << endl;
        }
        cin.ignore();
        cin.get();
    }
}

void Bank::newaccount() {
    system("cls");
    displayHeader("Create New Account");

    cout << "\t\t\tEnter Name: ";
    cin >> name;
    cout << "\t\t\tEnter Account Number: ";
    cin >> Account_number;
    balance = 1000; 
    cout << "\t\t\tEnter Address: ";
    cin >> address;
    cout << "\t\t\tEnter Email ID: ";
    cin >> email;
    cout << "\t\t\tEnter Contact Number: ";
    cin >> contact;

    cout << "\t\t\tEnter Password: ";
    cin >> acc_password;

    fstream file;
    file.open("bank.txt", ios::app | ios::out);
    if (!file) {
        cout << "\t\t\tError: Could not open file for writing!" << endl;
        return;
    }
    file << name << " " << Account_number << " " << balance << " " << email << " " << contact << " " << address << " " << acc_password << "\n";
    file.close();

    cout << "\t\t\tAccount created successfully! :)" << endl;
}

void Bank::modifyaccount() {
    displayHeader("Modify Account");

    string acc_no;
    cout << "\t\t\tEnter Account Number to Modify: ";
    cin >> acc_no;

    fstream file, temp_file;
    file.open("bank.txt", ios::in);
    if (!file) {
        cout << "\t\t\tError: Could not open file for reading! :(" << endl;
        return;
    }

    temp_file.open("temp.txt", ios::app | ios::out);
    if (!temp_file) {
        cout << "\t\t\tError: Temporary file could not be opened! :(" << endl;
        file.close();
        return;
    }

    bool found = false;
    while (file >> name >> Account_number >> balance >> email >> contact >> address >> acc_password) {
        if (acc_no == Account_number) {
            cout << "\t\t\tEnter new Name: ";
            cin >> name;
            cout << "\t\t\tEnter new Address: ";
            cin >> address;
            cout << "\t\t\tEnter new Email ID: ";
            cin >> email;
            cout << "\t\t\tEnter new Contact Number: ";
            cin >> contact;
            cout << "\t\t\tEnter new Password: ";
            cin >> acc_password;
        }
        temp_file << name << " " << Account_number << " " << balance << " " << email << " " << contact << " " << address << " " << acc_password << "\n";
    }
    file.close();
    temp_file.close();

    remove("bank.txt");
    rename("temp.txt", "bank.txt");

    cout << "Account modified successfully! :)" << endl;
}

void Bank::deleteaccount() {
    system("cls");
    displayHeader("Delete Account");

    string acc_no;
    cout << "\t\t\tEnter Account Number to Delete: ";
    cin >> acc_no;

    fstream file, temp_file;
    file.open("bank.txt", ios::in);
    if (!file) {
        cout << "\t\t\tError: Could not open file for reading! :(" << endl;
        return;
    }

    temp_file.open("temp.txt", ios::app | ios::out);
    if (!temp_file) {
        cout << "\t\t\tError: Temporary file could not be opened!" << endl;
        file.close();
        return;
    }

    bool found = false;
    while (file >> name >> Account_number >> balance >> email >> contact >> address >> acc_password) {
        if (acc_no != Account_number) {
            temp_file << name << " " << Account_number << " " << balance << " " << email << " " << contact << " " << address << " " << acc_password << "\n";
        } else {
            found = true;
        }
    }
    file.close();
    temp_file.close();

    remove("bank.txt");
    rename("temp.txt", "bank.txt");

    if (found) {
        cout << "\t\t\tAccount deleted successfully! :)" << endl;
    } else {
        cout << "\t\t\tAccount not found!" << endl;
    }
}

void Bank::deposit() {
    system("cls");
    displayHeader("Deposit");

    string acc_no;
    double depo;
    cout << "\t\t\tEnter Account Number: ";
    cin >> acc_no;
    cout << "\t\t\tEnter Amount to Deposit: ";
    cin >> depo;

    fstream file, temp_file;
    file.open("bank.txt", ios::in);
    if (!file) {
        cout << "\t\t\tError: Could not open file for reading!" << endl;
        return;
    }

    temp_file.open("temp.txt", ios::app | ios::out);
    if (!temp_file) {
        cout << "\t\t\tError: Temporary file could not be opened!" << endl;
        file.close();
        return;
    }

    bool found = false;
    while (file >> name >> Account_number >> balance >> email >> contact >> address >> acc_password) {
        if (acc_no == Account_number) {
            balance += depo;
            found = true;
        }
        temp_file << name << " " << Account_number << " " << balance << " " << email << " " << contact << " " << address << " " << acc_password << "\n";
    }
    file.close();
    temp_file.close();

    remove("bank.txt");
    rename("temp.txt", "bank.txt");

    if (found) {
        cout << "\t\t\tDeposit successful!" << endl;
    } else {
        cout << "\t\t\tAccount not found!" << endl;
    }
}

void Bank::user() {
    system("cls");
    displayHeader("User Login");

    string user_email, user_password;
    cout << "\t\t\tEmail: ";
    cin >> user_email;
    cout << "\t\t\tPassword: ";
    cin >> user_password;

    fstream file;
    file.open("bank.txt", ios::in);
    if (!file) {
        cout << "\t\t\tError: Could not open file for reading!" << endl;
        return;
    }

    bool found = false;
    while (file >> name >> Account_number >> balance >> email >> contact >> address >> acc_password) {
        if (user_email == email && user_password == acc_password) {
            found = true;
            user_info();
            break;
        }
    }
    file.close();

    if (!found) {
        cout << "\t\t\tInvalid email or password." << endl;
    }
}

void Bank::user_info() {
    int choice;

    system("cls");
    displayHeader("User Information");
    cout << "\t\t\tName: " << name << endl;
    cout << "\t\t\tAccount Number: " << Account_number << endl;
    cout << "\t\t\tBalance: $" << balance << endl;

    cout << "\n\t\t\t1. Send Money" << endl;
    cout << "\t\t\t2. Exit" << endl;
    cout << "\t\t\tEnter choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            send_money();
            break;
        case 2:
            cout << "\t\t\tExiting user information..." << endl;
            break;
        default:
            cout << "\t\t\tInvalid choice. Please try again. :(" << endl;
    }
}

void Bank::send_money(){
    system("cls");
    displayHeader("Send Money");

    string recipient_acc_no;
    double transfer_amount;
    cout << "\t\t\tEnter Recipient Account Number: ";
    cin >> recipient_acc_no;
    cout << "\t\t\tEnter Amount to Transfer: ";
    cin >> transfer_amount;
    bool sender_found = false;
    bool recipient_found = false;

    fstream writeFile("temp.txt",ios::out);
    fstream readFile("bank.txt",ios::in);

    string name;
    string acc_number;
    double balance;
    string email;
    string num;
    string address;
    string pass;

    while(readFile >> name >> acc_number >> balance >> email >> num >> address >> pass){
        if(acc_number == recipient_acc_no){
            balance += transfer_amount;
            sender_found = true;
        }
        writeFile << name << " " << acc_number << " " << balance << "  " << email <<  " " << num << " " << address << " " <<
        pass << endl;
    }

    readFile.close();
    writeFile.close();
    
    readFile.open("temp.txt",ios::in);
    writeFile.open("bank.txt",ios::out);


    while(readFile >> name >> acc_number >> balance >> email >> num >> address >> pass){
        if(transfer_amount > balance){
        cout<<"insufficient balance."<<endl;
        }
        else{
        if(acc_number == this->getAccountNumber()){
            balance -= transfer_amount;
            recipient_found = true;
        }
        writeFile << name << " " << acc_number << " " << balance << "  " << email <<  " " << num << " " << address << " " <<
        pass << endl;
    }
    }
    
    writeFile.close();
    readFile.close();
    remove("bank.txt");
    rename("temp.txt", "bank.txt");
     if (sender_found && recipient_found) {
         cout << "\t\t\tTransfer successful! :)" << endl;
     } else if (!sender_found) {
         cout << "\t\t\tSender account not found! :(" << endl;
     } else if (!recipient_found) {
         cout << "\t\t\tRecipient account not found! :(" << endl;
     }
}


int main() {
    Bank bank;
    bank.menu();
    return 0;
}
