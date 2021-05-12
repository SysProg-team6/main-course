#ifndef INSURANCEPOLICY_H
#define INSURANCEPOLICY_H


#include <iostream>

class InsurancePolicy
{
    public:
        InsurancePolicy();
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

    protected:
        int pId;
        int pStartDate;
        int pEndDate;
        double pCost;    // вартість
        double pPayment; // виплата
        bool pIsExpired;
        bool pIsPaid;
        int pPolicyTypeId;
        int pClinetId;
        int pEmployeeId;
};

#endif // INSURANCEPOLICY_H
