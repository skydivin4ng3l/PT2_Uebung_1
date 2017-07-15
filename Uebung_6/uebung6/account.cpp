#include <iostream>
#include <cassert>
#include <list>
#include <cstdlib>
#include <string>

using namespace std;


class Account {
public:
	Account(long accountNo, double balance, double limit, bool locked);
	~Account();

	long accountNo() const { return accountNo_; }

	virtual void setLimit(double limit) { limit_ = limit; }
	double getLimit() const { return limit_; }

	virtual bool credit(double amount);
	virtual bool debit(double amount);
	double balance() const { return balance_; }

	void setLock(bool locked) { locked_ = locked; }
	bool getLock() const { return locked_; }

private:
	long accountNo_;
	double balance_;
	double limit_;
	bool locked_;
};

//parent Class Methodes
Account::Account(long accountNo, double balance, double limit, bool locked) :
	accountNo_{accountNo},
	balance_{balance},
	limit_(limit),
	locked_{locked}
{}

Account::~Account() {}

bool Account::credit(double amount)
{
	assert(amount>=0.0);

	// cannot use locked account
	if(locked_) return false;

	balance_ = balance_ + amount;
	return true;
}

bool Account::debit(double amount)
{
	assert(amount>=0.0);

	// cannot use locked account
	if(locked_) return false;

	// check if limit is hit
	if(balance_ - amount < limit_) return false;

	// change balance
	balance_ = balance_ - amount;
	return true;
}

class LoggedAccount : public Account {
public:
	LoggedAccount(long accountNo, double balance, double limit, bool locked);

	virtual void setLimit(double limit) override;
	virtual bool credit(double amount) override;
	virtual bool debit(double amount) override;

	const list<pair<std::string, double>>& transactions();

private:
	list<pair<std::string, double>> transaction_list;
};

//inherited Class Methodes
//ctor
LoggedAccount::LoggedAccount(long accountNo, double balance, double limit, bool locked) :
	Account(accountNo, balance, limit, locked),
	transaction_list{ make_pair("**initial balance**",balance) }
{}

//transactions
const list<pair<std::string, double>>& LoggedAccount::transactions()
{
	transaction_list.push_back(make_pair("**current balance**", balance()));
	return transaction_list;
}

//Overrides
void LoggedAccount::setLimit(double limit)
{
	Account::setLimit(limit);
	transaction_list.push_back(make_pair("**set limit**", getLimit()));
}

bool LoggedAccount::credit(double amount)
{
	bool successful = Account::credit(amount);
	if (successful){ 
		transaction_list.push_back(make_pair("**credit**", amount));
		return successful;
	}
	transaction_list.push_back(make_pair("**credit - failed - account locked**", amount));
	return successful;
}

bool LoggedAccount::debit(double amount)
{
	bool successful = Account::debit(amount);
	if (successful) {
		transaction_list.push_back(make_pair("**debit**", amount));
		return successful;
	}
	transaction_list.push_back(make_pair("**debit - failed - account locked or insufficent funds**", amount));
	return successful;
}

int main(int argc, char** argv)
{
	Account A1(19920, 0.0, -1000.0, false);
	LoggedAccount A2(20020, 0.0, -1000.0, false);

	A1.credit(500.0);
	A2.credit(500.0);
	A2.debit(100.0);
	A2.setLimit(-2000.);

	for (const auto& x : A2.transactions())
	{
		cout << x.first << ": " << x.second << endl;
	}

	return 0;
}

