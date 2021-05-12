#ifndef INSURANCEPOLICY_H
#define INSURANCEPOLICY_H

#include <iostream>

class InsurancePolicy
{
public:
    InsurancePolicy();
    InsurancePolicy(int id, int start, int end, double cost, double payment, bool paid, int type, int client, int emp);
    ~InsurancePolicy();

    int getId() const;
    void setId(int id);

    int getStartDate() const;
    void setStartDate(int startDate);

    int getEndDate() const;
    void setEndDate(int endDate);

    double getCost() const;
    void setCost(double cost);

    double getPayment() const;
    void setPayment(double payment);

    bool isExpired(int now) const;

    bool isPaid() const;
    void setIsPaid(bool isPaid);

    int getPolicyTypeId() const;
    void setPolicyTypeId(int id);

    int getClientId() const;
    void setClientId(int id);

    int getEmployeeId() const;
    void setEmployeeId(int id);

    std::string toString() const;

    std::string sendMessage();
    void renew();
    void finish(int inEndDay);
    void pay();
    void display();
    double calculatePriceWithPolicyType();
    std::string InfoAboutPayment(InsurancePolicy& policy);
    std::string PolicyInfo(InsurancePolicy& policy);

protected:
    int pId;
    int pStartDate;
    int pEndDate;
    double pCost;    
    double pPayment; 
    bool pIsPaid;
    int pPolicyTypeId;
    int pClinetId;
    int pEmployeeId;
};

#endif // INSURANCEPOLICY_H
