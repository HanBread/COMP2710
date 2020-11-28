//Project 1
//Author: Han
//ID: 
//Compile: g++

#include <iostream>
using namespace std;
int main()
{
    double loan = 0;
    double rate = 0;
    double payment = 0;

    bool loanCheck = false;
    bool rateCheck = false;
    bool paymentCheck = false;
    bool validCheck = false;

    //check valid input, if no, reinput
    while (!validCheck) {
        while (!loanCheck){
        cout << "Loan Amount: ";
        cin >> loan;
        if (loan >= 0) {
            loanCheck = true;
            }
        }
    
        while (!rateCheck) {
            cout << "Interest Rate (% per year): ";
            cin >> rate;
            if (rate >= 0) {
            rateCheck = true;
            }
        }
    
        while (!paymentCheck) {
            cout << "Monthly Payments: ";
            cin >> payment;
            if (payment >= 0) {
                paymentCheck = true;
            }
        }
        if (payment > loan * rate / 12 / 100) {
            validCheck = true;
        }
        else {
            loanCheck = false;
            rateCheck = false;
            paymentCheck = false;
        }
        cout << endl;
    }
    
    //keep the output to two decimal places
    cout.setf(ios::fixed); 
    cout.setf(ios::showpoint); 
    cout.precision(2); 

    //print title
    cout << "********************************************************\n"
         << "\tAmortization Table\n"
         << "********************************************************\n"
         << "Month" << "\t"
         << "Balance" << "\t"
         << "Payment" << "\t"
         << "Rate" << "\t"
         << "Interest" << "\t"
         << "Principal" << endl;

    double monthRate = rate / 12;
    int month = 0;
    double interest = 0;
    double principal = 0;
    double totalInterest = 0;

    while (loan >= payment) {
        //first month, print different data
        if (month == 0) {
            cout << month++  << "\t"
                 << "$" << loan << "\t"
                 << "N/A" << "\t"
                 << "N/A" << "\t"
                 << "N/A" << "\t"
                 << "N/A" << endl;
        }
        else {
            interest = loan * (monthRate / 100);
            principal = payment - interest;
            loan -= principal;
            totalInterest += interest;

            cout << month++ << "\t"
                 << "$" << loan << "\t"
                 << "$" << payment << "\t"
                 << monthRate << "\t"
                 << "$" << interest << "\t"
                 << "$" << principal << endl;
        }
    }

    interest = loan * (monthRate / 100);
    payment = loan + interest;
    principal = loan;
    totalInterest += interest;
    loan = 0;

    //print final month data
    cout << month << "\t"
         << "$" << loan << "\t"
         << "$" << payment << "\t"
         << monthRate << "\t"
         << "$" << interest << "\t"
         << "$" << principal << endl;

    //print summary
    cout << "********************************************************\n\n"
         << "It takes " << month << " months to pay off the loan. \n"
         << "Total interest paid is: $" << totalInterest << endl;

    return 0;
}