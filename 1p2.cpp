/*
Leonard Phillips
15232331
Assignment 1 Part 2
This is an ATM. 
It takes input from two files (acct.txt, tranz.txt).
It then applied changes to the information recieved from acct.txt.
These changes depend on the instructions read in from tranz.txt.
Instructions that include depositing and withdrawing.
*/

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//=================================================================================

const int MAX_ACC_SIZE = 100;
const int MAX_TRAN_SIZE = 100;


class Transaction {
	public:
		Transaction(int newId = 0, char newType = 'A', double newAmount = 0);	
		friend ostream& operator<<(ostream& output, const Transaction& a);
		int getId() { return mId; }
		char getType() { return mType; }
		double getAmount() { return mAmount; }
	private:
		int mId;
		char mType;
		double mAmount;
};

//---------------------------------------------------------------

Transaction::Transaction(int newId, char newType, double newAmount) : 
		mId(newId), mType(newType), mAmount(newAmount) {}

//---------------------------------------------------------------

ostream& operator<<(ostream& output, const Transaction& a) {
	output << "Acct#\t" << a.mId << "\tBal:\t" 
		<< setprecision(2) << fixed << a.mAmount
		<< "    \tTrans so far:\t" << a.mType << endl;
	
	return output;
}

//---------------------------------------------------------------

//=================================================================================


class Account {
	public:
		Account(int mId = 0, double mBalance = 0);
		void applyTrans(Transaction t[MAX_TRAN_SIZE], int transSize);
		void withdraw(double& amount);
		void deposit(double& amount);
		friend ostream& operator<<(ostream& output, const Account& a);
	private:
		int mId;
		int mTrans;
		double mBalance;
};

//---------------------------------------------------------------

Account::Account(int newId, double newBal) : mId(newId), mTrans(0), mBalance(newBal) {}

//---------------------------------------------------------------

void Account::applyTrans(Transaction t[MAX_TRAN_SIZE], int transSize) {
	for(int i = 0; i < transSize; ++i){
		if(mId == t[i].getId()){
			if(t[i].getType() == 'D') {
				double temp = t[i].getAmount();				
				this->deposit(temp);
			} else {
				double temp = t[i].getAmount();
				this->withdraw(temp);
			}
		}
	}
}
	
//---------------------------------------------------------------

void Account::withdraw(double& amount) {
	if((mBalance - amount) > 0) {
		mBalance -= amount;
		++mTrans;
	}
}

//---------------------------------------------------------------

void Account::deposit(double& amount) {
	mBalance += amount;
	++mTrans;
}

//---------------------------------------------------------------

ostream& operator<<(ostream& output, const Account& a) {
	output << "Acct#\t" << a.mId << "\tBal:\t" 
		<< setprecision(2) << fixed << a.mBalance
		<< "    \tTrans so far:\t" << a.mTrans << endl;
	
	return output;
}

//---------------------------------------------------------------

//=================================================================================


int fileCheck(ifstream &ifstr, string f);
/**
	*Checks the file exsits. If the file doesn't exist then a string 
	*is printing on the screen informing the user.
	*@param[in]: the file stream.
	*@param[in]: the the name of a file being passed as a string type.
**/	

int readAccsInfo(ifstream& ifs, Account a[MAX_ACC_SIZE]);
int readTransInfo(ifstream& ifs, Transaction t[MAX_TRAN_SIZE]);
/**
	* Reads Account details from the "accs.txt" file. It then creates a new Account object 
	* using each line from the file. The new Account object then added to the Account array a[100].
	* @param[in]: the file stream
	* @param[in, out]: the default array of Account being mutated
**/
void print(){
	cout << "Assignment 1\t\tpart 1\n" << "Leonard Phillips\t15232331\n" << "159.234\t\t\tOOP\n\n";
}
/**
  *Prints developers credentials
*/

//=================================================================================

int main() {
	
	string f1 = "acct.txt";
	string f2 = "tranz.txt";
	ifstream ifs1("acct.txt");
	ifstream ifs2("tranz.txt");
	
	Account accs[MAX_ACC_SIZE];
	Transaction trans[MAX_TRAN_SIZE];
	
	int numOfAccount, numOfTransaction, i = 0;
	
	if(fileCheck(ifs1, f1) != 1)
	{
		if(fileCheck(ifs2, f2) != 1)
		{
			print();
			cout << "Initial data as in file \"acct.txt\"\n";
			
			numOfAccount = readAccsInfo(ifs1, accs);
			numOfTransaction = readTransInfo(ifs2, trans);
			
			while(i < numOfAccount){		
				cout << accs[i];
				++i;
			}
			
			for(i = 0; i < numOfAccount; ++i) {
				accs[i].applyTrans(trans, numOfTransaction);
			}
			
			cout << "\nAfter processing data in file \"tranz.txt\"" << endl;
			i = 0;
			while(i < numOfAccount){		
				cout << accs[i];
				++i;
			}
		}
		else
		{
			return 1;
		}
	}
	else
	{		
		return 1;
	}
	return 0;
}

//=================================================================================

//---------------------------------------------------------------
int fileCheck(ifstream &ifstr, string f)
{
	if (!ifstr.is_open())
	{
		cout << "There was a problem opening the " << f << ". The application will close\n";
		return 1;
	}
	else 
	{
		return 0;
	}
}
//---------------------------------------------------------------
int readAccsInfo(ifstream& ifs, Account a[MAX_ACC_SIZE]) {
	int tempId, i = 0;
	double tempBal;
	while(!ifs.eof() && i < MAX_ACC_SIZE) {
		ifs >> tempId >> tempBal;
		if(tempId >= 0 && tempBal >= 0) {
			a[i] = Account(tempId, tempBal);
			++i;
		}
	}
	return i;
}
//---------------------------------------------------------------
int readTransInfo(ifstream& ifs, Transaction t[MAX_TRAN_SIZE]) {
	string s;
	int tempId, i = 0;
	char tempType;
	double tempAmount;
	
	getline(ifs, s);
	
	while(!ifs.eof() && i < MAX_TRAN_SIZE) {
		ifs >> tempId >> tempType >> tempAmount;
		if(tempId >= 0 && tempAmount >= 0) {
			if(tempType == 'D' || tempType == 'W') {
				t[i] = Transaction(tempId, tempType, tempAmount);
				++i;				
			}
		}			
	}	
	return i;
}