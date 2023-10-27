#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

/* date: 12/12/22
Idea Board:
increase accuracy of payoff calculator
figure out better banking system for our accounts
include investments. ex: stocks, real estate,
create to do list that attaches to assets

fix payment counter format
add money print format ex: $123,456.78

*/
class BankAccount {
    private:
	double amount;
	string type;

    public:
	BankAccount(string name, double x) {
	    amount = x;
	    setType(name);
	    cout << getType() << " acct created. Available funds: $" << getAmount() << endl << endl; 
	}
	double getAmount(){ return amount; }
	string getType()  { return type;   }
	void printAmount()  { cout << getType() << " Account Balance: $" << getAmount() << endl; }
	void setType(string s) { type = s; }
	void setAmount(double n) {  
	    if(amount + n < 0) cout << "Insufficient Funds." << endl << endl;
	    else {
		amount = amount + n;
		//if(amount + n > amount) { cout << getType() << " - $" << n << " deposited" << endl; }
	        //else { cout << getType() << " - $" << -n << " withdrawn" << endl; }
	    }
	}
	void setTransfer(double n, BankAccount &b) {
	    if(n < 0) { cout << "Invalid Amount" << endl << endl; }
	    else { 
		setAmount(-n);
		b.setAmount(n);
	    }
	}
};

class Person {
    private:
	double addWage;
	double debt;
	double wage;
	string name;

    public:
	Person(double aW, double d, double w, string s) {
	    setAddWage(aW);
	    setDebt(d);
	    setWage(w);
	    setName(s);
	    cout << getName() << "\nEarnings: $" << 
	    calcTaxes(calcYearlyWage()) << " /yearly\n          $" << 
	    calcTaxes(calcMonthlyWage()) << " /monthly\n          $" << 
	    calcTaxes(calcWeeklyWage()) << " /weekly\n" << endl; 
	}
	double calcWeeklyWage()     { return getWage() * 40 + getAddWage() * 5; }
	double calcYearlyWage()     { return calcWeeklyWage() * 52; }
	double calcMonthlyWage()    { return calcYearlyWage() / 12; }
	double calcTaxes(double p)  { return p * .7; }
	double getAddWage()  { return addWage; }
	double getDebt()     { return debt;    }
	string getName()     { return name;    }
	double getWage()     { return wage;    }
	void setAddWage(double x)  { addWage = x; }
	void setDebt(double x)     { debt = x;    }
	void setName(string s)	   { name = s;    }
	void setWage(double x)     { wage = x;    }

	//Monthly Expenses and Savings
	void calcMEAS(int numMonths, BankAccount &c) {
	    int moExpenses = 7000;
	    for(int i = 0; i < numMonths; i++) { c.setAmount(calcTaxes(calcMonthlyWage()) - moExpenses); }
	    cout << endl;
	}
	void calcMEAS(int numMonths, Person &a, BankAccount &c) {
	    for(int i = 0; i < numMonths; i++) { c.setAmount(calcTaxes(calcMonthlyWage() + a.calcMonthlyWage()) - 7000); }
	    cout << endl; 
	}
	void calcMEAS(int numMonths, Person &a, BankAccount &c, BankAccount &s) {
	    for(int i = 0; i < numMonths; i++) { 
		if(c.getAmount() > 5000) { s.setAmount(calcTaxes(calcMonthlyWage() + a.calcMonthlyWage()) - 7000); } 
		else c.setAmount(calcTaxes(calcMonthlyWage() + a.calcMonthlyWage()) - 7000); }
	    cout << endl; 
	}
	void printWages(string x){
	    if(x == "after") {
		cout << getName() << 
		"\nEarnings: $" << calcTaxes(calcYearlyWage()) << " /yearly\n          $" << 
		calcTaxes(calcMonthlyWage()) << " /monthly\n          $" << 
		calcTaxes(calcWeeklyWage()) << " /weekly\n" << endl; 
	    }
	    else {
		cout << getName() << 
		"\nEarnings: $" << calcYearlyWage() << " /yearly   (before taxes)\n          $" << 
		calcMonthlyWage() << " /monthly (before taxes)\n          $" << 
		calcWeeklyWage() << " /weekly   (before taxes)\n" << endl; 
	    }
	}
	void printComboWages(Person &b, string x) {
	    if(x == "after") {
		cout << "Combined" << 
		"\nEarnings: $" << calcTaxes(calcYearlyWage()  + b.calcYearlyWage()) << " /yearly\n          $" << 
		calcTaxes(calcMonthlyWage() + b.calcMonthlyWage()) << " /monthly\n          $" << 
		calcTaxes(calcWeeklyWage()  + b.calcWeeklyWage()) << " /weekly\n" << endl;
	    }
	    else {
		cout << "Combined\nEarnings: $" << calcYearlyWage()  + b.calcYearlyWage() << " /yearly\n          $" << 
		calcMonthlyWage() + b.calcMonthlyWage() << " /monthly\n          $" << 
		calcWeeklyWage()  + b.calcWeeklyWage() << " /weekly\n" << endl;
	    }
	}
};

class Debt {
    private:
	double amount;
	double interest;
	string owner;
	double payment;
	string type;


    public:
	Debt(string s, double n, double i, double p, string name) {
	    setAmount(n);
	    setInterest(i);
	    setOwner(name);
	    payment = p;
	    setType(s);
	    cout << getType() << " debt created.\nDebt Owner: " << getOwner() << 
	    "\nAmount: $" << getAmount() <<  
	    "\nInterest Rate: " << getInterest()*100 << 
	    "%\nPayment: $" << getPayment() << endl << endl;
	}
	double getAmount()   { return amount; }
	double getInterest() { return interest; }
	string getOwner()    { return owner; }
	int getNumPayments(double d, double n) { return d / n; }
	double getPayment()  { return payment; }
	string getType()     { return type;   }
	void printPayment() {
	    cout << getType() << " Payment: $" << getPayment() << 
	    "\nRemaining Balance: $" << getAmount() << 
	    "\nNo. Payments Left: " << getNumPayments(getAmount(), getPayment()) << 
	    "\nNo. Years Left: " << getNumPayments(getAmount(), getPayment()) / 12 << endl << endl;
	}
	//Calculates Amortized Payments
	void principalPayment() {
	    double principalPay = getPayment() - (getAmount() * (getInterest() / 12));
	    principalPay = floor(principalPay*100+0.5)/100;
	    double interestPay = getPayment() - principalPay;
	    double totalInterest = interestPay;
	    double balance = getAmount();
	    balance = floor(balance*100+0.5)/100;
	    int i = 1;

	    cout << setw(3) << "No." << 
	    setw(13) << "Payment" << 
	    setw(15) << "Principal" << 
	    setw(12) << "Interest" << 
	    setw(18) << "Total Interest" << 
	    setw(13) << "Balance" << endl;

	    while(balance >= 0) {

		cout << setw(3) << i << 
		setw(8)<< "$" << getPayment() << 
		setw(9)<< "$" << principalPay << 
		setw(6)<< "$" << interestPay << 
		setw(8)<< "$" << totalInterest << 
		setw(12)<< "$" << balance << endl;

		balance = balance - principalPay;
		balance = floor(balance*100+0.5)/100;
		principalPay = getPayment() - (balance * (getInterest() / 12));
		principalPay = floor(principalPay*100+0.5)/100;
		interestPay = getPayment() - principalPay;
		totalInterest = totalInterest + interestPay;
		i++;		
	    } 
	    cout << endl;
	}
	void setAmount(double n) {
	    if(n <= 0) cout << "Error" << endl; 
	    else amount = n;
	}
	void setInterest(double i) { 
	    if(i < 0 || i >= 1) cout << "Error" << endl;
	    else interest = i;
	}
	void setOwner(string name) { owner = name; }
	void setPayment(double n) {
	    if(amount - n < 0) cout << "Error" << endl;
	    else { amount = amount - n; }
	}
	void setType(string s) { type = s; }
};

void totalDebt(Debt n1, Debt n2, Debt n3) {
    double totalDebt = n1.getAmount() + n2.getAmount() + n3.getAmount();
    double minPayment = n1.getPayment() + n2.getPayment() + n3.getPayment();
    double extra = 1000;
    double extraPayment = minPayment + extra;
    int noMonths = 12;

    int noMinPayment_Debt = totalDebt / minPayment;
    int yearsMinPayment = noMinPayment_Debt / noMonths;
    double decYearsMinPayment = (totalDebt / minPayment) / noMonths;
    int noMonthsMinPayment = (decYearsMinPayment - yearsMinPayment) * noMonths;
    int noExtPayment_Debt = totalDebt / extraPayment;
    int yearsExtPayment = noExtPayment_Debt / noMonths;
    double decYearsExtPayment = (totalDebt / extraPayment) / noMonths;
    int noMonthsExtPayment = (decYearsExtPayment - yearsExtPayment) * noMonths;
    
    cout << "Total Debt: $" << totalDebt << 
    "\n\nPayoff Calculator\nMinimum Payment: $" << minPayment << 
    "\nYears: " << yearsMinPayment << " Months: " << noMonthsMinPayment << 
    "\n\nExtra Payment: $" << extra << 
    "\nTotal Payment: $" << extraPayment <<
    "\nYear: " << yearsExtPayment << " Months: " << noMonthsExtPayment << endl << endl;

}

int main() {
    Person a(4.5, 0, 50.62, "Kenny");
	  a.printWages("before");
    Person b(0, 0, 35, "May");
    a.printComboWages(b, "after");

    BankAccount c("Checking", 0);
    BankAccount s("Saving", 40000);

    Debt d1("Bristol House", 212000, .0235, 1175, a.getName());
    Debt d2("Tesla", 44932, .04, 850, a.getName());
    Debt d3("Chianti Home", 570000, .0599, 4268, b.getName());

    totalDebt(d1, d2, d3);

    a.calcMEAS(12, b, c, s);
    c.printAmount();
    s.printAmount(); 

    return 0;
}
