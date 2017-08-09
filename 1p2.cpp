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
#include <cstdlib>
#include <sstream>
#include <iomanip>

using namespace std;

class Accounts
{
	public:
		Accounts(int);
		~Accounts();
		int getNAccounts();
		int getId(int);
		int getTrans(int);
		double getBalance(int);
		void setNAccounts(int);
		void setId(int, int);
		void setTrans(int, int);
		void setBalance(int, double);
	private:
		int nAccounts;
		int *id;
		int *trans;
		double *balance;
};

//	Accounts constructor
Accounts::Accounts(int s) {
	nAccounts = 0;
	id = new int[s];
	trans = new int[s];
	for (int i = 0; i < s; i++){
		trans[i] = 0;
	}
	balance = new double[s];
}

//	Accounts deconstructor
Accounts::~Accounts() {
	delete[] id;
	delete[] trans;
	delete[] balance;
}

//	Account getters
int Accounts::getNAccounts(){ return nAccounts; }
int Accounts::getId(int i){ return id[i]; }
int Accounts::getTrans(int i){ return trans[i]; }
double Accounts::getBalance(int i){ return balance[i]; }

//	Account setters
void Accounts::setNAccounts(int v){ nAccounts = v; }
void Accounts::setId(int i, int v){ id[i] = v; }
void Accounts::setTrans(int i, int v){ trans[i] = v; }
void Accounts::setBalance(int i, double v){ balance[i] = v; }



class Instructions
{
	public:
		Instructions(int);
		~Instructions();
		int getNInstructions();
		int getId(int);
		char getType(int);
		double getAmount(int);
		void setNInstructions(int);
		void setId(int, int);
		void setType(int, int);
		void setAmount(int, double);
	private:
		int nInstructions;
		int *id;
		char *type;
		double *amount;
};

Instructions::Instructions(int s) {
	nInstructions = 0;
	id = new int[s];
	type = new char[s];
	amount = new double[s];
}

// Instructions deconstructor
Instructions::~Instructions() {
	delete[] id;
	delete[] type;
	delete[] amount;
}

//	Instruction getters
int Instructions::getNInstructions(){ return nInstructions; }
int Instructions::getId(int i){ return id[i]; }
char Instructions::getType(int i){ return type[i]; }
double Instructions::getAmount(int i){ return amount[i]; }

//	Instruction setters
void Instructions::setNInstructions(int v){ nInstructions = v; }
void Instructions::setId(int i, int v){ id[i] = v; }
void Instructions::setType(int i, int v){type[i] = v; }
void Instructions::setAmount(int i, double v){ amount[i] = v; }

const int limit = 100;


int fileCheck(ifstream &ifstr, string f);
/*
	Checks the file exsits.
	param[0]: the file stream.
	param[1]: the the name of a file being passed as a string type.
*/
void readFile(ifstream &ifstrm, Accounts &anAccount, int count);
/*
	Reads account details from a file and fills accounts[] structure.
	param[0]: the file stream
	param[1]: a refernece to an Accounts object
	param[2]: is the limit of accounts read in from the file
*/

void readFile(ifstream &ifstrm, Instructions &anInstruction);
/*
	Reads transaction details from a file and files instruction[]s structure.
	param[0]: the file stream
	param[1]: a referance to an Instructions object
*/

void applyChanges(Accounts &anAccount, Instructions &anInstruction);
/*
	Applies transaction changes from instruction[]s to accounts[].
	param[0]: a refernace to a Accounts object that conatin the data to be altered 
	param[1]: a refernace to a Instructions object that contains the changes to be made
*/
bool vaildTrans(double accAmount, double transAmount);
/*
	Checks whether the transaction will result in a negative balance.
	param[0]: the account balance
	param[1]: the transaction amount to be withdrawn
*/

void print();
/*
	Prints developers credentials
*/

void print(Accounts &anAccount);
/*
	Prints accounts summary.
	param[0]: a refernace to an Account object to be printed
*/



int main() {
	print();
	
	string f1 = "acct.txt";
	string f2 = "tranz.txt";
	ifstream ifs1(f1);
	ifstream ifs2(f2);
	
	Accounts acc(limit);	
	Instructions instruct(100);
	
	if(fileCheck(ifs1, f1) != 1)
	{
		if(fileCheck(ifs2, f2) != 1)
		{
			cout << "Initial data as in file \"acct.txt\"\n";
			readFile(ifs1, acc, limit);
			cout << acc.getNAccounts() << " correct accounts read from file.\n";

			print(acc);
			
			cout << "\nAfter processing data in file \"tranz.txt\"\n";
			readFile(ifs2, instruct);
			
			ifs1.close();
			ifs2.close();
			
			applyChanges(acc, instruct);	
			print(acc);
		}
	}
	else
	{		
		return 1;
	}
	
	
	return 0;
}



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
void readFile(ifstream &ifstm, Accounts &anAccount, int l)
{
	int i = 0, tempId;
	double tempBal;

	while (!ifstm.eof() && i < l)
	{
		ifstm >> tempId >> tempBal;
		if (tempId >= 0 && tempBal >= 0)
		{
			anAccount.setId(i, tempId);
			anAccount.setBalance(i, tempBal);
			i++;
		}
	}
	anAccount.setNAccounts(i);
}

//---------------------
void readFile(ifstream &ifstrm, Instructions &anInstruction)
{
	string s;
	int i = 0, tempId;	
	char tempType;
	double tempAmount;
	
	getline(ifstrm, s);
	while(!ifstrm.eof())
	{
		ifstrm >> tempId >> tempType >> tempAmount;
		if(tempId >= 0 && tempAmount >= 0)
		{
			if(tempType == 'D' || tempType == 'W')
			{
				anInstruction.setId(i, tempId);
				anInstruction.setType(i, tempType);
				anInstruction.setAmount(i, tempAmount);
				i++;
			}
		}
	}
	anInstruction.setNInstructions(i);
}

//---------------------
void applyChanges(Accounts &anAccount, Instructions &anInstruction)
{
	for(int i = 0; i < anInstruction.getNInstructions(); i++)
	{
		for(int j = 0; j < anAccount.getNAccounts(); j++)
		{
			if(anInstruction.getId(i) == anAccount.getId(j))
			{
				if(anInstruction.getType(i) == 'D')
				{
					anAccount.setBalance(j,(anAccount.getBalance(j) + anInstruction.getAmount(i)));
					anAccount.setTrans(j, (anAccount.getTrans(j) + 1));
				}
				else
				{
					if (vaildTrans(anAccount.getBalance(j), anInstruction.getAmount(i)))
					{
						anAccount.setBalance(j,(anAccount.getBalance(j) - anInstruction.getAmount(i)));
						anAccount.setTrans(j, (anAccount.getTrans(j) + 1));
					}
				}
				break;
			}
		}
	}
}

//---------------------
bool vaildTrans(double accAmount, double transAmount)
{
	if((accAmount - transAmount) < 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

//---------------------
void print()
{
	cout << "Assignment 1\t\tpart 1\n" << "Leonard Phillips\t15232331\n" << "159.234\t\t\tOOP\n\n";
}

//---------------------
void print(Accounts &anAccount)
{
	for (int i = 0; i < anAccount.getNAccounts(); i++)
	{
		cout << "Acct#\t" << anAccount.getId(i) << "\tBal:\t"
			<< setprecision (2) << fixed << anAccount.getBalance(i) 
			<< "    \tTrans so far:\t" << anAccount.getTrans(i) << "\n";
	}
}


