#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>

#include <conio.h>

#include "database.h"

using namespace std;

namespace Records {
    std::vector<InsurancePolicy> PoliciesVector;


    Database::Database()
    {
        readFromDB();
        mNextId = 0;
        
        for (vector<InsurancePolicy>::iterator it = PoliciesVector.begin(); it != PoliciesVector.end(); it++)
        {
            InsurancePolicy ip = *it;
            if (ip.getId() > mNextId)
                mNextId = ip.getId();
        }
        mNextId++;
    }

    Database::~Database()
    {
        writeToDB();
    }


    void Database:: writeToDB()
    {
        FILE* f;
        f = fopen("database.txt", "w+");

        ofstream fof(f);
        for (InsurancePolicy& p : PoliciesVector) {
            fof << p.getId() << endl << p.getStartDate() << endl << p.getEndDate() << endl << p.getCost() << endl << p.getPayment() << endl
                << p.isPaid() << endl << p.getPolicyTypeId() << endl << p.getClientId() << endl << p.getEmployeeId() << endl;
        }
        fof.close();
    }

    void Database::readFromDB()
    {
        FILE* f;
        f = fopen("database.txt", "r");

        ifstream fin(f);
        int Id;
        int StartDate;
        int EndDate;
        double Cost;
        double Payment;
        bool Paid;
        int TypeId;
        int ClientId;
        int EmployeeId;

        if (fin.is_open())
        {
            PoliciesVector.clear();
            while (!fin.eof())
            {
                fin >> Id >> StartDate >> EndDate >> Cost >> Payment >> Paid >> TypeId >> ClientId >> EmployeeId;

                if (Id < 0 || !isUniqueId(Id)) continue;

                PoliciesVector.push_back(InsurancePolicy(Id, StartDate, EndDate, Cost, Payment, Paid, TypeId, ClientId, EmployeeId));
                /*
                fin >> Id >>  Cost >> Payment >> StartDate;
                InsurancePolicy policy;
                policy.setId(Id);
                policy.setCost(Cost);
                policy.setPayment(Payment);
                policy.setStartDate(StartDate);
                PoliciesVector.push_back(policy);
                */
            }

            fin.close();
        }
        else
        {
            cout << "Error! Input file isn't opened!";
        }
    }

    InsurancePolicy& Database::addInsurancePolicy(double inCost, double inPayment, int inStartDate, int inEndDate, bool inIsPayed, int inClientId, int inEmplId, int inPolicyType)
    {

        InsurancePolicy policy;
        policy.setId(mNextId++);
        policy.setCost(inCost);
        policy.setPayment(inPayment);
        policy.setStartDate(inStartDate);
        policy.setEndDate(inEndDate);
        policy.setIsPaid(inIsPayed);
        policy.setClientId(inClientId);
        policy.setEmployeeId(inEmplId);
        policy.setPolicyTypeId(inPolicyType);
        PoliciesVector.push_back(policy);     //Add to vector

        return policy;
    }

    InsurancePolicy& Database::getInsurancePolicy(int inId)
    {
        for (vector<InsurancePolicy>::iterator it = PoliciesVector.begin(); it != PoliciesVector.end(); it++)
        {
            InsurancePolicy ip = *it;
            if (ip.getId() == inId)
                return ip;
        }

        cerr << "No employee with employee number " << inId << endl;
        throw exception();
    }

    void Database::displayAll()
    {
        for (vector<InsurancePolicy>::iterator it = PoliciesVector.begin(); it != PoliciesVector.end(); it++)
        {
            InsurancePolicy ip = *it;
            ip.display();
        }
    }

    void Database::displayCurrent(int now)
    {
        for (vector<InsurancePolicy>::iterator it = PoliciesVector.begin(); it != PoliciesVector.end(); it++)
        {
            InsurancePolicy ip = *it;
            if (!ip.isExpired(now))
                ip.display();
        }
    }

    void Database::displayNotPaid()
    {
        for (vector<InsurancePolicy>::iterator it = PoliciesVector.begin(); it != PoliciesVector.end(); it++)
        {
            InsurancePolicy ip = *it;
            if (!ip.isPaid())
                ip.display();
        }
    }

    bool Database::isUniqueId(int id)
    {
        for (vector<InsurancePolicy>::iterator it = PoliciesVector.begin(); it != PoliciesVector.end(); it++)
        {
            InsurancePolicy ip = *it;
            if (ip.getId() == id)
                return false;
        }

        return true;
    }

}

