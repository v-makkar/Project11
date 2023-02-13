#include <iostream>
#include <chrono>

using namespace std;

class Account
{

private:
    int OwnerID, AID;
    float balance;
    time_t last_modified;

public:
    Account() : AID(-1), balance(0) {}
    int getAID() { return AID; }
    float getBal() { return balance; }
    int getOID() { return OwnerID; }
    void setBal(float bal) { balance = bal; }
    void deposit(int amt) { balance = balance + amt; last_modified = time(0); }
    void withdraw(int amt) { balance = balance - amt; last_modified = time(0); }
    void init(int aid, float bal, int OID)
    {
        AID = aid;
        balance = bal;
        OwnerID = OID;
        last_modified = time(0);
    }
    time_t getLMTime() { return last_modified; }
};

class Bank
{

private:
    int BID; float ROI; int done;
    Account AccountList[15];

public:
    int createAccount(int loginID, int bal)
    {

        int empty_slot = -5;

        for (int i = 14; i >= 0; i--)
        {
            if (AccountList[i].getAID() == -1)
                empty_slot = i;
        }

        if (empty_slot == -5)
            return -5;

        AccountList[empty_slot].init(empty_slot, bal, loginID);
    }
    void setROI(int n) { ROI = n; }
    void setBID(int n) { BID = n; }
    void printActiveAccounts()
    {
        cout << "Active accounts in Bank" << BID << endl;
        for (int i = 0; i < 15; i++)
        {
            if (AccountList[i].getAID() != -1)
            {
                cout << "AID " << AccountList[i].getAID() << endl;
                cout << "Bal " << AccountList[i].getBal() << endl;
                cout << "ownder ID " << AccountList[i].getOID() << endl;
            }
        }
    }
    void printActAccOfID(int loginID)
    {
        cout << endl;
        cout << "Active accounts in Bank " << BID << "of User ID " << loginID << endl;
        for (int i = 0; i < 15; i++)
        {
            if (AccountList[i].getAID() != -1 && AccountList[i].getAID() == loginID)
            {
                cout << "Account No. " << AccountList[i].getAID() << endl;
                cout << "Bal " << getBal(i) << endl;
            }
        }
    }
    void calculateInterest()
    {
        time_t now = time(0);
        for (int i = 0; i < 15; i++)
        {
            if (AccountList[i].getAID() != -1)
            {
                int T = difftime(now, AccountList[i].getLMTime()); int t = T / 10; float r = ROI / 100;
                if (done != t) {
                    float P = AccountList[i].getBal() * (1 + (r * t)); cout << "P " << P << endl;
                    AccountList[i].setBal(P);
                    done = t;
                }
                cout << "Interest has been accumulated " << done << " times" << endl;
            }
        }
    }
    int getBal(int AID)
    {
        calculateInterest();
        return AccountList[AID].getBal();
    }
    void deposit(int AID, int amount)
    {
        calculateInterest();
        AccountList[AID].deposit(amount);
    }
    void withdraw(int AID, int amount)
    {
        calculateInterest();
        if (AccountList[AID].getBal() >= amount)
            AccountList[AID].withdraw(amount);
            cout << "Insufficient balance." << endl;
    }
};

class User
{

private:
    int UID;
    string pass;

public:
    User() : UID(-1) {};
    int getUID() { return UID; }
    void setUID(int n) { UID = n; }
    void setPass(string inp) { pass = inp; }
    int checkPass(string inp)
    {
        if (pass == inp)
            return 1;
        else
            return 0;
    }
};

class Simulator
{

private:
    User UserList[3];
    Bank BankList[3];

public:
    void init_UserMode()
    {
        int boolean = 1;
        while (boolean)
        {

            int choice;
            system("cls");
            printActiveUsers();
            cout << "***********************************\n";
            cout << "\t\tuser menu"
                << "\n\t1 to create new user"
                << "\n\t2 to login in existing user"
                << "\n\t0 to exit" << endl;
            cout << "*************************************\n";
            cout << "option: ";
            cin >> choice;
            if (choice == 1)
            { // create user // any User object in the array with UID = -1 is an empty user slot.

                int empty_slot = -5;

                for (int i = 2; i >= 0; i--)
                {
                    if (UserList[i].getUID() == -1)
                        empty_slot = i;
                }

                if (empty_slot == -5)
                {
                    cout << "No more users can be created" << endl;
                }

                else
                {
                    string pass;
                    UserList[empty_slot].setUID(empty_slot); // UID = Index of that User object in the user list.
                    cout << "Your User ID is " << empty_slot << endl;
                    cout << "Set login password " << endl;
                    cin >> pass;
                    UserList[empty_slot].setPass(pass);
                    cout << "User created successfully" << endl;
                    printActiveUsers();
                }
            }
            else if (choice == 2)
            {
                // login to a user
                printActiveUsers();
                cout << "Select your User ID from above" << endl;
                int selectedID;
                string pass;
                cin >> selectedID;
                cout << "Enter your password" << endl;
                cin >> pass;
                int succ = UserList[selectedID].checkPass(pass);
                cout << "Login successfully.... "
                    << "\nPress enter to continue.." << endl;
                cin.ignore();
                cin.get();
                if (succ)
                {
                    int loginID = selectedID;
                    int feature;
                    while (1)
                    {

                        cout << "***********************************\n";
                        cout << "\t\tLoged in"
                            << "\n\t1 to see profile"
                            << "\n\t2 to open a bank account"
                            << "\n\t3 to deposit money"
                            << "\n\t4 to withdraw money"
                            << "\n\t5 to see balance of all accounts of a particular bank"
                            << "\n\t0 to Back=>" << endl;
                        cout << "*************************************\n";
                        cout << "option: ";
                        // MENU: see profile, open a bank acc, dep money, withdraw money, see outstanding bills -- pay using -- select account -- withdraw
                        cin >> feature;
                        if (feature == 1)
                        {
                            // MENU: show all bank accounts
                            system("cls");
                            cout << "keep choosing this option to watch the interest accumulate" << endl;
                            BankList[0].printActAccOfID(loginID);
                            BankList[1].printActAccOfID(loginID);
                            BankList[2].printActAccOfID(loginID);
                        }

                        if (feature == 2)
                        { // open a bank acc

                            while (1)
                            {
                                system("cls");
                                cout << "***********************************\n";
                                cout << "\t\tChoose Bank"
                                    << "\n\tEnter 0 for Bank 0, with ROI = 5%"
                                    << "\n\tEnter 1 for Bank 1 with ROI = 7%"
                                    << "\n\tEnter 2 for Bank 2 with ROI = 9%"
                                    << endl;
                                cout << "*************************************\n";
                                cout << "option: ";

                                int bankchoice, bal;
                                cin >> bankchoice;

                                cout << "Enter Starting Balance" << endl;
                                cin >> bal;
                                createAccInBank(bankchoice, loginID, bal);
                                break;
                            }
                        }
                        else if (feature == 3)
                        {
                            // deposit money
                            cout << "Which bank?" << endl; int bc; cin >> bc;
                            BankList[bc].printActAccOfID(loginID);
                            cout << "which account" << endl; int acc; cin >> acc;
                            cout << "how much?" << endl; int amt; cin >> amt;
                            BankList[bc].deposit(acc, amt);
                            cout << "success" << endl;

                        }
                        else if (feature == 4)
                        {
                            // withdraw money
                            cout << "Which bank?" << endl; int bc; cin >> bc;
                            BankList[bc].printActAccOfID(loginID);
                            cout << "which account" << endl; int acc; cin >> acc;
                            cout << "how much?" << endl; int amt; cin >> amt;
                            BankList[bc].withdraw(acc, amt);
                            cout << "sucess" << endl;

                        }
                        else if (feature == 5)
                        {  // see balance
                            cout << "Which bank?" << endl; int bc; cin >> bc;
                            BankList[bc].printActAccOfID(loginID);
                        }
                        else if (feature == 0)
                            break;
                    }
                }
                else
                {
                    cout << "wrong pass" << endl;
                    continue;
                }
            }
            else if (choice == 0)
                break;
            else
                cout << "Wrong option\n";
        }
    }
    void printActiveUsers()
    {
        cout << "Active users" << endl;
        for (int i = 0; i < 3; i++)
        {
            if (UserList[i].getUID() != -1)
            {
                cout << "UID " << UserList[i].getUID() << endl;
            }
        }
    }
    void createAccInBank(int i, int loginID, int bal)
    {
        int IsPossible = BankList[i].createAccount(loginID, bal);
        if (!IsPossible)
        {
            cout << "bank full, choose another bank.." << endl;
        }
        else
        {
            cout << "Acc created" << endl;
            BankList[i].printActAccOfID(loginID);
        }
        cout << "\nPress enter to continue.." << endl;
        cin.ignore();
        cin.get();
    }
    void initBanks()
    {
        BankList[0].setROI(5);
        BankList[1].setROI(7);
        BankList[2].setROI(9);
        BankList[0].setBID(0);
        BankList[1].setBID(1);
        BankList[2].setBID(2);
    }
};

void starting_prompt()
{
    cout << "** This is a bank simulation." << endl;
    cout << "** There are three banks with different interest rates" << endl;
    cout << "** Upto three users can be created" << endl;
    // cout << "** Each user is given 1,000,000 cash in the beginning to create accounts" << endl;
    cout << "** This is a simulation. So, interest accumulates every 10 seconds after an account is created" << endl;
    cout << "** Files are created after the program ends to display a record of the simulation" << endl;

    cout << "\nPress enter to continue.." << endl;
    cin.ignore();
    cin.get();
}

int main()
{
    starting_prompt();
    Simulator S;
    S.initBanks();
    S.init_UserMode();
}
