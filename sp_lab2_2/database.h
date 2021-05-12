#ifndef DATABASE_H
#define DATABASE_H

#include "insurancepolicy.h"

namespace Records {

  const int kMaxPolicies = 100;
  const int kFirstPolicyId = 1000;
    class DataBase
      {
      public:
    DataBase();
    ~DataBase();

    InsurancePolicy& addInsurancePolicy(double inCost, int inStartDate, double inPayment);
    InsurancePolicy& getInsurancePolicy(int inId);
    void        displayAll();
    void        displayCurrent();
    void        displayNotPaid();
      protected:
    InsurancePolicy    mInsurancePolicies[kMaxPolicies];
    int         mNextSlot;
    int         mNextId;
      };
}

#endif // DATABASE_H
