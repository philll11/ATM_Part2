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
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;

//=====================================================
class Account{
	public:		
		Account(int newId = 0, double newBal = 0);
	
		friend ostream& operator<<(ostream& output, const Account& account);
		//friend istream& operator>>(istream& input, Account& account);
	
		int getId();
		int getTrans();
		double getBal();
	private:
		int mId;
		int mTrans;
		double mBalance;
};

/*
istream& operator>>(istream& input, Account& account) {		
	int tempId;
	double tempBal;
	input >> tempId >> tempBal;	
	if (tempId >= 0 && tempBal >= 0)
	{
		account.mId = tempId;
		account.mBalance = tempBal;
	}
	return input;
}
*/
//	Account constructor
Account::Account(int newId, double newBal) : mId(newId), mTrans(0), mBalance(newBal) {}

ostream& operator<<(ostream& output, const Account& account) {
	output << "Acct#\t" << account.mId << "\tBal:\t" 
		<< setprecision(2) << fixed << account.mBalance
		<< "    \tTrans so far:\t" << account.mTrans << endl;
	
	return output;
}
int Account::getId() { return mId; }
int Account::getTrans() { return mTrans; }
double Account::getBal() { return mBalance; }
//=================================================================================
class Instruction{
	public:
		Instruction(int newId = 0, char newType = 'A', double newAmount = 0);		
	
	private:
		int mId;
		char _type;
		double _amount;	
};

Instruction::Instruction(int newId, char newType, double newAmount) : mId(newId), _type(newType),
	_amount(newAmount) {}
//=================================================================================
class ATM{
	public:
		ATM();		
		ATM(const ATM&);
		ATM(ATM&&);
		const ATM& operator=(const ATM&);
		ATM& operator=(ATM&& a);
		~ATM();
	
		int getLimit() const { return mLimit; }
		
		int getAccountSize() const { return mAcountSize; }
		int getInstSize() const { return mInstSize; }
		Account& getAccount(int i) const { return mAccountPtr[i]; }
		Instruction& getInst(int i) const { return mInstPtr[i]; }
		
		void setAccountSize(int v) { mAcountSize = v; }
		void setInstSize(int v) { mInstSize = v; }
		void setAccount(int i, const Account& v) { mAccountPtr[i] = v; }
		void setInst(int i, const Instruction& v) { mInstPtr[i] = v; }
	
	private:
		int mLimit;
		int mAcountSize;
		int mInstSize;
		Account *mAccountPtr;
		Instruction *mInstPtr;
};
//----------------------------------------------------------------------------------
// Default constructor

// Default constructor
ATM::ATM() : mLimit(100), mAcountSize(0), mInstSize(0) {
	//cout << "\nATM default constructor entered" << endl;
	mAccountPtr = new Account[mLimit];
	mInstPtr = new Instruction[mLimit];
	//cout << "\nATM default constructor exited" << endl;
}
//----------------------------------------------------------------------------------
// Copy constructor
ATM::ATM(const ATM& oldATM) : mLimit(oldATM.mLimit),	mAcountSize(oldATM.mAcountSize), 
	mInstSize(oldATM.mInstSize) {
		
	//cout << "\nATM copy constructor entered" << endl;
	mAccountPtr = new Account[mLimit];
	mInstPtr = new Instruction[mLimit];
	int i;
	for(i = 0; i < mAcountSize; ++i) {
		mAccountPtr[i] = oldATM.mAccountPtr[i];
	}
	for(i = 0; i < mInstSize; ++i) {
		mInstPtr[i] = oldATM.mInstPtr[i];
	}
	//cout << "\nATM copy constructor exited" << endl;
}
//----------------------------------------------------------------------------------
//	Move constructor
ATM::ATM(ATM&& oldATM) : mLimit(oldATM.mLimit), mAcountSize(oldATM.mAcountSize),
	mInstSize(oldATM.mInstSize), mAccountPtr(oldATM.mAccountPtr), mInstPtr(oldATM.mInstPtr) {
	//cout << "\nATM moved constructor entered" << endl;
	
	oldATM.mAccountPtr = nullptr;
	oldATM.mInstPtr = nullptr;
	//cout << "\nATM moved constructor exited" << endl;
}
//----------------------------------------------------------------------------------
//	Assignment operator
const ATM& ATM::operator=(const ATM& a) {
	if(this != &a) {
		delete[] mAccountPtr;
		delete[] mInstPtr;
		
		mLimit = a.mLimit;
		mAcountSize = a.mAcountSize;
		mInstSize = a.mInstSize;
		mAccountPtr = new Account[a.mLimit];
		mInstPtr = new Instruction[a.mLimit];
		
		int i;
		for(i = 0; i < mAcountSize; ++i) {
			mAccountPtr[i] = a.mAccountPtr[i];
		}
		for(i = 0; i < mInstSize; ++i) {
			mInstPtr[i] = a.mInstPtr[i];
		}
	}
	return *this;
}
//----------------------------------------------------------------------------------
//	Move Assignment operator
ATM& ATM::operator=(ATM&& a) {
		
	delete[] mAccountPtr;
	mLimit = a.mLimit;
	mAcountSize = a.mAcountSize;
	mInstSize = a.mInstSize;
	mAccountPtr = a.mAccountPtr;
	mInstPtr = a.mInstPtr;
	
	a.mAccountPtr = nullptr;	
	a.mInstPtr = nullptr;
	return *this;	
}
//----------------------------------------------------------------------------------
//	Deconstructor
ATM::~ATM() {
	//cout << "\nATM deconstructor entered" << endl;
	delete[] mAccountPtr;
	delete[] mInstPtr;
	
	mAccountPtr = nullptr;
	mInstPtr = nullptr;
	//cout << "\nATM deconstructor exited" << endl;
}
//=================================================================================

/****************************
	*Methods
**/

int fileCheck(ifstream &ifstr, string f);
/**
	*Checks the file exsits. If the file doesn't exist then a string 
	*is printing on the screen informing the user.
	*@param[in]: the file stream.
	*@param[in]: the the name of a file being passed as a string type.
**/
void readAccountsFile(ifstream &ifstm, ATM& accounts);
/**
	*Reads account details from the "accs.txt" file and loads them into
	*the mAccountPtr data member of the ATM class.
	*@param[in]: the file stream
	*@param[in, out]: a refernece to an ATM object	
**/

void readInstructionsFile(ifstream& ifstm, ATM& accounts);
/**
	*Reads transaction details from the "trans.txt" file and loads them into
	*the mInstPtr data member of the ATM class.
	*@param[in]: the file stream
	*@param[in, out]: a refernece to an ATM object	
**/



/**
  *Prints developers credentials
*/
void print();


int main() {
	
	string f1 = "acct.txt";
	string f2 = "tranz.txt";
	ifstream ifs1(f1);
	ifstream ifs2(f2);
	
	ATM atm = ATM();
	
	if(fileCheck(ifs1, f1) != 1)
	{
		if(fileCheck(ifs2, f2) != 1)
		{
			print();
			cout << "Initial data as in file \"acct.txt\"\n";
			
			/**
			I am unsure if this this the best way to create an ATM object.
			The process I have used involves creating 100 default account and instruction objects in the
			atm object. Then assigning each new account and instruction objects to the already default
			existing ones.
			Is there a way to initialize these account and instruction objects with data read in from the
			files and assign them to the atm object all at once?
			**/
			readAccountsFile(ifs1, atm);
			readInstructionsFile(ifs2, atm);
			
			int i = 0;
			int tempSize = atm.getAccountSize();
			while(i < tempSize){		
				cout << atm.getAccount(i);
				++i;
			}
			//Create the applyChanges function
			//print(mATM);
			
		}
	}
	else
	{		
		return 1;
	}
	
	return 0;
}

/**
	Create the applyChanges function

**/

//---------------------
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
//---------------------
void readAccountsFile(ifstream& ifstm, ATM& accounts)
{
	int tempId;
	int i = 0;
	int limit = accounts.getLimit();
	double tempBal;
	while (!ifstm.eof() && i < limit)
	{
		ifstm >> tempId >> tempBal;
		if (tempId >= 0 && tempBal >= 0)
		{
			accounts.setAccount(i, Account(tempId, tempBal));
			++i;
		}
	}
	accounts.setAccountSize(i);
}
void readInstructionsFile(ifstream& ifstm, ATM& accounts) {
	int i = 0;
	int tempSize = accounts.getInstSize();
	int tempId;
	char tempType;
	double tempAmount;
	while (!ifstm.eof() && i < tempSize)
	{
		ifstm >> tempId >> tempType >> tempAmount;
		if (tempId >= 0 && tempAmount >= 0)
		{
			if(tempType == 'D' || tempType == 'W') {
				accounts.setInst(i, Instruction(tempId, tempType, tempAmount)); // Replace with operator=
				++i;
			}
		}
	}
	accounts.setInstSize(i);
}
//---------------------
void print(){
	cout << "Assignment 1\t\tpart 1\n" << "Leonard Phillips\t15232331\n" << "159.234\t\t\tOOP\n\n";
}









