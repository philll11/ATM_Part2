/**
  * Leonard Phillips
  * 15232331
  * Assignment 1 Part 2
  * This is an ATM. 
  * It takes input from two files (acct.txt, tranz.txt).
  * It then applied changes to the information recieved from acct.txt.
  * These changes depend on the instructions read in from tranz.txt.
  * Instructions that include depositing and withdrawing.
  * It was built using Object Orientated Programming design.
  */

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int MAX_ACC_SIZE = 100;
const int MAX_TRAN_SIZE = 100;

//=================================================================================
/**
 * A class representing a transaction
 */
class Transaction {
	public:
		/**
		 *	Constructor
		 * @param[in] newId 		A account identifier.
		 * @param[in] newType	Type of transaction
		 * @param[in] newAmount	Value of transaction		
		 */
		Transaction(int newId = 0, char newType = 'A', double newAmount = 0);
		/**
		 *	mId Accessor
		 * Returns mId
		 */
		int getId() { return mId; }
		/**
		 *	mType Accessor
		 * Returns mType
		 */
		char getType() { return mType; }
		/**
		 *	mAmount Accessor
		 * Returns mAmount
		 */
		double getAmount() { return mAmount; }
	private:
		int mId; ///< The ID of the account the transaction will operate on
		char mType; ///< The type of transaction to be preformed
		double mAmount; ///< The amount by which the account balance will be altered
};
//---------------------------------------------------------------
Transaction::Transaction(int newId, char newType, double newAmount) : 
		mId(newId), mType(newType), mAmount(newAmount) {}
//---------------------------------------------------------------
//=================================================================================
/**
 * A class representing an account
 */
class Account {
	public:
		/**
		 * Constructor
		 * @param[in] mId			The account identifier
		 * @param[in] mBalance	The initile value of account
		 */
		Account(int mId = 0, double mBalance = 0);
		/**
		 * Member Function applyTrans
		 * @param[in] t[]			An array of type transaction containing data that will mutate mBalance data member
		 * @param[in] transSize	The length of t array
		 */
		void applyTrans(Transaction t[MAX_TRAN_SIZE], int transSize);
		/**
		 * Member Function withdraw
		 * @param[in] amount	The account to be withdrawn from mBalance data member
		 */
		void withdraw(double& amount);
		/**
		 * Member Function deposit
		 * @param[in] amount	The account to be deposited into mBalance data member
		 */
		void deposit(double& amount);
		/**
		 *	Overloaded output operator
		 * @param[in] output 	The stream to be returned containing the output
		 * @param[in] newType	A constant reference to a Account object
		 */
		friend ostream& operator<<(ostream& output, const Account& a);
	private:
		int mId; ///< The identifcation number of the account
		int mTrans; ///< The number of transactions that have altered the account
		double mBalance; ///< The amount of capital in the account
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
/**
	*Checks the file exsits. If the file doesn't exist then a string 
	*is printing on the screen informing the user.
	*@param[in] ifstr The file stream.
	*@param[in] f		The name of a file being checked. Is used to identify what file is missing.
	*/
int fileCheck(ifstream &ifstr, string f);

/**
	* Global Function readAccsInfo.
	* Assigns data from the file stream to the Tccount objects in a[].
	* @param[in] ifs	The file stream.
	* @param[in] a[] 	The Account array that will sort the account data
	*/
int readAccsInfo(ifstream& ifs, Account a[MAX_ACC_SIZE]);
/**
	* Global Function readTransInfo.
	* Assigns data from the file stream to the Transaction objects in t[].
	* @param[in] ifs	The file stream.
	* @param[in] t[]	The Transaction array that wil sort the transaction data.
	*/
int readTransInfo(ifstream& ifs, Transaction t[MAX_TRAN_SIZE]);
/**
   * Prints developers credentials
   */
void print(){
	cout << "Assignment 1\t\tpart 1\n" << "Leonard Phillips\t15232331\n" << "159.234\t\t\tOOP\n\n";
}
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