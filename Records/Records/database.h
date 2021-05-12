#ifndef DATABASE_H
#define DATABASE_H
#include <vector>
#include "insurancepolicy.h"

namespace Records {

    class Database
    {
    public:
        Database();
        ~Database();

        InsurancePolicy& addInsurancePolicy(double inCost, double inPayment, int inStartDate, int inEndDate, bool inIsPayed, int inClientId, int inEmplId, int inPolicyType);
        InsurancePolicy& getInsurancePolicy(int inId);
        void        displayAll();
        void        displayCurrent(int now);
        void        displayNotPaid();
        void readFromDB();
        void writeToDB();
        bool isUniqueId(int id);
    protected:
        int         mNextId;
        std::vector<InsurancePolicy> PoliciesVector;
    };
}

#endif // DATABASE_H

