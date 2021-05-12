#include "insurancepolicy.h"
#include <iostream>

using namespace std;

namespace Records {

}
InsurancePolicy::InsurancePolicy()
{
    // initialize data members
    pId = 0;
    //auto start = std::chrono::system_clock::now();
    //pStartDate = std::chrono::system_clock::to_time_t(start); // time(NULL) ?
    //pEndDate= std::chrono::system_clock::to_time_t(start);
    pStartDate = 0;
    pEndDate = 0;
    pCost = 0;
    pPayment = 0;
    pIsExpired = false;
    pIsPaid = false;
    pPolicyTypeId = 0;
    pClinetId = 0;
    pEmployeeId = 0;
}

void InsurancePolicy::renew()
{
  setEndDate(0);
}

void InsurancePolicy::finish(int inEndDay)
{
    setEndDate(inEndDay);
}

void InsurancePolicy::pay()
{
  setIsPaid(true);
}

void InsurancePolicy::display()
{
  cout << "Insurance Policy: " << getStartDate() << " - " << getEndDate() << endl;
  cout << "-------------------------" << endl;
  cout << sendMessage() << endl;
  cout << "Policy Id: " << getId() << endl;
  cout << "Cost: $" << getCost() << endl;
  cout << "Payment: $" << getPayment() << endl;
  cout << endl;
}

InsurancePolicy::~InsurancePolicy()
{
  // cleans up
}

int InsurancePolicy::getId() const
{
  return pId;
}

std::string InsurancePolicy::sendMessage()
{
    if(pIsPaid){
        return "You paid everything. Well done!";
    }
    else{
        return "Please, pay!";
    }
}

// 1st Policy Type provides with 10% discounts

double InsurancePolicy::calculatePriceWithPolicyType()
{
    if(pPolicyTypeId == 1){
        return static_cast<double>((getCost() * 0.9));
    }
    else{
        return pCost;
     }
}

void InsurancePolicy::setId(int id)
{
  pId = id;
}

double InsurancePolicy::getCost() const
{
  return pCost;
}

void InsurancePolicy::setCost(double cost)
{
  pCost = cost;
}

double InsurancePolicy::getPayment() const
{
  return pPayment;
}

void InsurancePolicy::setPayment(double payment)
{
  pPayment = payment;
}

bool InsurancePolicy::isExpired(int now) const
{
    // compare with end time with now time
     return now - pEndDate >= 0;
}

bool InsurancePolicy::isPaid() const
{
  return pIsPaid;
}

void InsurancePolicy::setIsPaid(bool isPaid)
{
  pIsPaid = isPaid;
}

int InsurancePolicy::getPolicyTypeId() const
{
  return pPolicyTypeId;
}

void InsurancePolicy::setPolicyTypeId(int policyTypeId)
{
  pPolicyTypeId = policyTypeId;
}

int InsurancePolicy::getClientId() const
{
  return pClinetId;
}

void InsurancePolicy::setClientId(int clientid)
{
  pClinetId = clientid;
}

int InsurancePolicy::getEmployeeId() const
{
  return pEmployeeId;
}

void InsurancePolicy::setEmployeeId(int employeeId)
{
  pEmployeeId = employeeId;
}

int InsurancePolicy::getStartDate() const
{
    return pStartDate;
}

void InsurancePolicy::setStartDate(int startDate)
{
    if(startDate - pEndDate > 0)
    {
        pStartDate = startDate;
    }
}

int InsurancePolicy::getEndDate() const
{
    return pEndDate;
}

void InsurancePolicy::setEndDate(int endDate)
{
    if(pStartDate - endDate > 0)
    {
        pEndDate = endDate;
    }
}


