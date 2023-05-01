/*
  rec03.cpp
  Author: Faith Villarreal
 */

// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Task 1
// Define an Account struct
struct Account{
    string account_name;
    int account_number;
};

// Task 2
// Define an Account class (use a different name than in Task 1)
class Account2{
public:
    Account2(const string& name, int num): account_name(name), account_number(num){}
    const string& getName()const{
        return account_name;
    }
    int getAccNum()const{
        return account_number;
    }
    friend ostream& operator<<(ostream& os, const Account2& a);

private:
    string account_name;
    int account_number;
};

ostream &operator<<(ostream& os, const Account2& a) {
    os << "Account Name: " << a.account_name << "  Account Number: " << a.account_number<< endl;
    return os;
}

// Task 3
// Define an Account (use a different name than in Task 1&2) and
// Transaction classes



class Transaction{
public:
    Transaction(string type, int acc_num, int amnt): deposit_or_withdrawl(type), account_number(acc_num), amount(amnt){}
    friend ostream& operator<<(ostream& os, Transaction transaction);

    int getAmount(){
        return amount;
    }
private:
    int amount;
    int account_number;
    string deposit_or_withdrawl;

};

ostream &operator<<(ostream& os, Transaction transaction) {
    os << transaction.deposit_or_withdrawl << " of " << transaction.amount << endl;
    return os;
}

class Account3{
public:
    Account3(string name, int num): account_name(name), account_number(num){}
    void deposit(Transaction& transaction){
        trans_history.push_back(transaction);
        balance += transaction.getAmount();
    }
    void withdrawal(Transaction& transaction){
        if(balance - transaction.getAmount() > 0){
            trans_history.push_back(transaction);

            balance -= transaction.getAmount();
        }else{
            cerr << "withdrawal invalid. insufficient funds." << endl;
        }
    }
    friend Account3& findAccount(int, vector<Account3>&);

    friend ostream& operator<<(ostream&, Account3);

private:
    string account_name;
    int account_number;
    int balance = 0;
    vector<Transaction> trans_history;
};


Account3& findAccount(int acc_num , vector<Account3>& acc_vec){
    for(Account3& a : acc_vec){
        if(a.account_number == acc_num){
            return a;
        }
    }
}

ostream &operator<<(ostream& os, Account3 account3) {
    os << "Account Name: " << account3.account_name << "  Account Number: " << account3.account_number<< endl;
    os << "Transaction History:" << endl;
    for(const Transaction& t : account3.trans_history){
        os << t;
    }
    return os;
}

// Task 4
// Define an Account with a nested public Transaction class
// (use different names than in the previous Tasks)


class Account_v4{
public:


    Account_v4(string name, int num): account_name(name), account_number(num){}

    class Transaction_v2{
    public:
        Transaction_v2(string type, int acc_num, int amnt): deposit_or_withdrawl(type), account_number(acc_num), amount(amnt){}
        friend ostream& operator<<(ostream& os, Transaction_v2 transaction);

        int getAmount(){
            return amount;
        }
    private:
        int amount;
        int account_number;
        string deposit_or_withdrawl;

    };
    void deposit(Transaction_v2& transaction){
        trans_history.push_back(transaction);
        balance += transaction.getAmount();
    }
    void withdrawal(Transaction_v2& transaction){
        if(balance - transaction.getAmount() > 0){
            trans_history.push_back(transaction);

            balance -= transaction.getAmount();
        }else{
            cerr << "withdrawal invalid. insufficient funds." << endl;
        }
    }
    friend Account_v4& findAccount(int, vector<Account_v4>&);

    friend ostream& operator<<(ostream&, Account_v4);

private:
    string account_name;
    int account_number;
    int balance = 0;
    vector<Transaction_v2> trans_history;
};

ostream &operator<<(ostream& os, Account_v4::Transaction_v2 transaction) {
    os << transaction.deposit_or_withdrawl << " of " << transaction.amount << endl;
    return os;
}
Account_v4& findAccount(int acc_num , vector<Account_v4>& acc_vec){
    for(Account_v4& a : acc_vec){
        if(a.account_number == acc_num){
            return a;
        }
    }
}

ostream &operator<<(ostream& os, Account_v4 account3) {
    os << "Account Name: " << account3.account_name << "  Account Number: " << account3.account_number<< endl;
    os << "Transaction History:" << endl;
    for(const Account_v4::Transaction_v2& t : account3.trans_history){
        os << t;
    }
    return os;
}

// Task 5
// Define an Account with a nested private Transaction class
// (use different names than in the previous Tasks)


int main() {
    ifstream text("accounts.txt");
    if(!text){
        cerr << "file failed to open!" << endl;
        exit(1);
    }

    // Task 1: account as struct
    //      1a
    cout << "Task1a:\n";
    vector<Account> all_accounts;
    string name;
    int id;
    while(text >> name >> id){
        Account new_account;
        new_account.account_name = name;
        new_account.account_number = id;
        all_accounts.push_back(new_account);
    }
    text.close();

    for(const Account& a : all_accounts){
        cout << a.account_name << " " << a.account_number << endl;
    }
    //      1b
    cout << endl << "Task1b:\n";
    cout << "Filling vector of struct objects, using {} initialization:\n";

    ifstream text2("accounts.txt");
    if(!text2){
        cerr << "file failed to open!" << endl;
        exit(1);
    }
    all_accounts.clear();
    while(text2 >> name >> id){
        all_accounts.push_back(Account{name, id});
    }
    text2.close();
    for(const Account& a : all_accounts){
        cout << a.account_name << " " << a.account_number << endl;
    }

    //==================================
    // Task 2: account as class

    //      2a
    cout << "==============\n";
    cout << "\nTask2a:";
    cout << "\nFilling vector of class objects, using local class object:\n";
    vector<Account2> classAccounts;
    ifstream text3("accounts.txt");
    if(!text3){
        cerr << "file 3 not found";
        exit(1);
    }

    int id1;
    while(text3 >> name >> id1){
        Account2 temp_Account (name, id1);
        classAccounts.push_back(temp_Account);
    }
    text3.close();

    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";
    for(size_t i =0 ; i < classAccounts.size(); i++){
        Account2& curr_acc = classAccounts[i];
        cout << "Account Name: " << curr_acc.getName() << "   Account Number: " << curr_acc.getAccNum() << endl;

    }

    cout << "\nTask2c:\n";
    cout << "output using output operator as friend without getters\n";
    for(size_t i =0 ; i < classAccounts.size(); i++){
        cout << classAccounts[i];
    }

    cout << "\nTask2d:\n";
    cout << "Filling vector of class objects, using temporary class object:\n";
    classAccounts.clear();
    ifstream text4("accounts.txt");
    if(!text4){
        cerr << "file 3 not found" << endl;
        exit(1);
    }

    while(text4 >> name >> id){
        classAccounts.push_back(Account2(name, id));
    }
    text4.close();
    for(const Account2& a : classAccounts){
        cout << a;
    }

    cout << "\nTask2e:\n";
    cout << "Filling vector of class objects, using emplace_back:\n";
    classAccounts.clear();
    ifstream text5("accounts.txt");
    if(!text5){
        cerr << "file 5 not found";
        exit(1);
    }

    while(text5 >> name >> id){
        classAccounts.emplace_back(name, id);
    }
    text5.close();
    for(const Account2& a : classAccounts){
        cout << a;
    }

    cout << "==============\n";
    cout << "\nTask 3:\nAccounts and Transaction:\n";
   vector<Account3> task3_Vector;
    ifstream text6("transactions.txt");
    if(!text6){
        cerr << "file 6 not found";
        exit(1);
    }
    string type;
    while(text6 >> type){
        if(type == "Account"){
            string name;
            int acc_num;
            text6 >> name >> acc_num;
            Account3 temp_account = Account3(name, acc_num);
            task3_Vector.push_back(temp_account);

        }else{
            int acc_num, bal;
            text6 >> acc_num >> bal;
            Transaction new_transaction = Transaction(type, acc_num, bal);
            Account3& target_account = findAccount(acc_num, task3_Vector);
            if(type == "Deposit"){
                target_account.deposit(new_transaction);

            }else
                target_account.withdrawal(new_transaction);
        }
    }
    for(Account3 a : task3_Vector){
        cout << a;
    }

    cout << "==============\n";
    cout << "\nTask 4:\nTransaction nested in public section of Account:\n";

    vector<Account_v4> task4_Vector;
    ifstream text7("transactions.txt");
    if(!text7){
        cerr << "file 7 not found";
        exit(1);
    }
    while(text7 >> type){
        if(type == "Account"){
            string name;
            int acc_num;
            text7 >> name >> acc_num;
            Account_v4 temp_account = Account_v4(name, acc_num);
            task4_Vector.push_back(temp_account);

        }else{
            int acc_num, bal;
            text7 >> acc_num >> bal;
            Account_v4::Transaction_v2 new_transaction = Account_v4::Transaction_v2(type, acc_num, bal);
            Account_v4& target_account = findAccount(acc_num, task4_Vector);
            if(type == "Deposit"){
                target_account.deposit(new_transaction);

            }else
                target_account.withdrawal(new_transaction);
        }
    }
    for(Account_v4 a : task4_Vector){
        cout << a;
    }
    cout << "==============\n";
    cout << "\nTask 5:\nTransaction nested in private section of Account:\n";


}
