#include <iostream>
#include <stdexcept>
#include <string>

#include "database.h"

using namespace std;
using namespace Records;

int displayMenu();
void addNewPolicy(Database& inDB);
void getInformation(Database& inDB);
void readFromFile();
void writeToFile(string str);

int main()
{
    Database* employeeDB = new Database();
    bool done = false;

    while (!done) {
        int selection = displayMenu();

        switch (selection) {
        case 1:
            addNewPolicy(*employeeDB);
            writeToFile("new policy has been registered\n");
            break;
        case 2:
            getInformation(*employeeDB);
            writeToFile("information has been requested\n");
            break;
        case 3:
            employeeDB->displayAll();
            writeToFile("all policies have been displayed");
            break;
        case 4:
            employeeDB->displayCurrent(20210301);
            writeToFile("active policies have been displayed");
            break;
        case 5:
            employeeDB->displayNotPaid();
            writeToFile("not paid policies have been displayed");
            break;
        case 6:
            readFromFile();
            break;
        case 0:
            done = true;
            writeToFile("exited");
            delete(employeeDB);
            break;
        default:
            cerr << "Unknown command." << endl;
        }
    }
}

void readFromFile()
{
    FILE* f;
    f = fopen("info.txt", "r");
    char val[80];
    while (!feof(f))
    {
        if (fscanf(f, "%s\n", val)) {
            cout << val;
        }
    }
    fclose(f);
}

void writeToFile(string str)
{
    FILE* fp;
    fp = fopen("info.txt", "w+");
    fprintf(fp, "%s\n", str.c_str());
    fclose(fp);
}

int displayMenu()
{
    int selection;

    cout << endl;
    cout << "Employee Database" << endl;
    cout << "-----------------" << endl;
    cout << "1) Add new insurance policy" << endl;
    cout << "2) Get indormation about insurance policy" << endl;
    cout << "3) Display all insurance policies" << endl;
    cout << "4) Display active insurance policies" << endl;
    cout << "5) Display not paid insurance policies" << endl;
    cout << "6) Display last activity" << endl;
    cout << "0) Quit" << endl;
    cout << endl;
    cout << "Enter number" << endl;
    cout << "---> ";

    cin >> selection;

    return selection;
}

void addNewPolicy(Database& inDB)
{
    double cost;
    double payment;
    int startdate; 
    int enddate;
    bool isPaid;
    int policyType;

    try
    {
        cout << "Cost? ";
        cin >> cost;
        cout << "Payment? ";
        cin >> payment;
        cout << "Start day in form yyyyMMdd? ";
        cin >> startdate;
        cout << "End date in format yyyyMMdd? ";
        cin >> enddate;
        cout << "Is it payed? [0/1]";
        cin >> isPaid;
        cout << "Policy type? ";
        cin >> policyType;
    }
    catch (std::exception e)
    {
        cerr << "Bad arguments as input" << endl;
    }

    try {
        inDB.addInsurancePolicy(cost, payment, startdate, enddate, isPaid, -1, -1, policyType);
    }
    catch (std::exception ex) {
        cerr << "Unable to add new policy!" << endl;
    }
}

void getInformation(Database& inDB)
{
    int id;

    try
    {
        cout << "Policy id? ";
        cin >> id;
    }
    catch (std::exception e)
    {
        cerr << "Bad arguments as input" << endl;
    }

    try {
        inDB.getInsurancePolicy(id).display();
    }
    catch (std::exception ex) {
        cerr << "Unable to find policy!" << endl;
    }
}