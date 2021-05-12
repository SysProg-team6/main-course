#include <iostream>
#include <stdexcept>
#include <string>

#include "database.h"

using namespace std;

namespace Records {

  DataBase::DataBase()
  {
    mNextSlot = 0;
    mNextId = kFirstPolicyId;
  }

  DataBase::~DataBase()
  {
  }

  InsurancePolicy& DataBase::addInsurancePolicy(double inCost, int inStartDate, double inPayment)
  {
    if (mNextSlot >= kMaxPolicies) {
      cerr << "There is no more room to add the new employee!" << endl;
      throw exception();
    }

    InsurancePolicy& policy = mInsurancePolicies[mNextSlot++];
    policy.setId(mNextId++);
    policy.setCost(inCost);
    policy.setPayment(inPayment);
    policy.setStartDate(inStartDate);

    return policy;
  }

  InsurancePolicy& DataBase::getInsurancePolicy(int inId)
  {
    for (int i = 0; i < mNextSlot; i++)
    {
      if (mInsurancePolicies[i].getId() == inId)
      {
          return mInsurancePolicies[i];
      }
    }

    cerr << "No employee with employee number " << inId << endl;
    throw exception();
  }

  void DataBase::displayAll()
  {
    for (int i = 0; i < mNextSlot; i++) {
      mInsurancePolicies[i].display();
    }
  }

  void DataBase::displayCurrent()
  {
    for (int i = 0; i < mNextSlot; i++)
    {
      if (!mInsurancePolicies[i].isExpired(20210223))
      {
          mInsurancePolicies[i].display();
      }
    }
  }

  void DataBase::displayNotPaid()
  {
    for (int i = 0; i < mNextSlot; i++)
    {
      if (!mInsurancePolicies[i].isPaid())
      {
          mInsurancePolicies[i].display();
      }
    }
  }
}
