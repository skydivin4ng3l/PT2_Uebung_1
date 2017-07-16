#include <iostream>
#include <string>
#include <cassert>

#define DEFAULT_CURRENCY EUR // EUR / USD
#define DEFAULT_TAXCLASS NORMAL // NORMAL / REDUCED
#define EXCHANGE_RATE 1.1467 //1 euro to 1.1467 dollar

using namespace std;

class Amount
{
	// Todo 6.2
	// Implement class Amount
public:
	enum class taxclass	{ NORMAL = 19, REDUCED = 7 };
	enum class currency { EUR = '€', USD = '$' };

	Amount();
	Amount(string label, double netValue);
	Amount(string label, double netValue, currency currency, taxclass taxclass);

	Amount(const Amount& original);

	~Amount() {}

	void setLabel(string label);
	string getLabel() const;

	double setNetValue(double netValue);
	double setNetValue(double netValue, currency currency);
	double getNetValue() const;

	void setTaxclass(taxclass taxclass);
	taxclass getTaxclass() const;

	double getGross() const;
	double getTaxAmount() const;
	double getNetValueInUSD() const;
	double getNetValueInEUR() const;

	void convertCurrency();
	currency getCurrency() const;
	char getCurrencySymbol() const;

	//stream output
	friend std::ostream& operator<<(std::ostream& os, const Amount& Amount);

private:
	double netValue_;
	taxclass taxclass_;
	currency currency_;
	string label_;
};

//ctors
Amount::Amount() : 
	label_{ "undefined" },
	netValue_{ 0.0 },
	currency_{ currency::DEFAULT_CURRENCY },
	taxclass_{ taxclass::DEFAULT_TAXCLASS } 
{}

Amount::Amount(string label, double netValue) :
	label_{ label },
	netValue_{ setNetValue(netValue) },
	currency_{ currency::DEFAULT_CURRENCY },
	taxclass_{ taxclass::DEFAULT_TAXCLASS } 
{}

Amount::Amount(string label, double netValue, currency currency, taxclass taxclass) :
	label_{ label },
	netValue_{ setNetValue(netValue) },
	currency_{ currency},
	taxclass_{ taxclass}
{}

//copy ctor
Amount::Amount(const Amount& original) : 
	label_{ original.getLabel() },
	netValue_{ original.getNetValue() },
	currency_{ original.getCurrency() },
	taxclass_{ original.getTaxclass() }
{}

//"direct access members"
void Amount::setLabel(string label) 
{
	this->label_ = label;
}

string Amount::getLabel() const 
{
	return this->label_;
}

double Amount::setNetValue(double netValue)
{
	this->netValue_ = round(netValue *100.0) / 100.0;
	return this->netValue_;
}

double Amount::setNetValue(double netValue, Amount::currency currency)
{
	this->netValue_ = round(netValue *100.0) / 100.0;
	this->currency_ = currency;
	return this->netValue_;
}

double Amount::getNetValue() const
{
	return this->netValue_;
}

void Amount::setTaxclass(taxclass taxclass)
{
	if (this->taxclass_ == taxclass) return;
	this->taxclass_ = taxclass;
}

Amount::taxclass Amount::getTaxclass() const 
{
	return this->taxclass_;
}

//copy ctor helper currency access
Amount::currency Amount::getCurrency() const
{
	return this->currency_;
}

//print helper
char Amount::getCurrencySymbol() const
{
	return static_cast<char>(static_cast<int>(this->currency_));
}


//calculated "members"
double Amount::getGross() const
{
	double netValue = this->getNetValue();
	double taxAmount = this->getTaxAmount();
	double gross = netValue - taxAmount;

	assert( ( (round(gross*100.0) + round(taxAmount*100.0) ) / 100.0 ) == round(netValue*100.0) / 100.0 );
	return gross;
}

double Amount::getTaxAmount() const
{
	double netValue = this->getNetValue();
	double taxRate = static_cast<double>( static_cast<float>( this->getTaxclass() ) / 100.0f);
	double taxAmount = round((netValue * taxRate) * 100.0) / 100.0;

	return taxAmount;
}

double Amount::getNetValueInUSD() const
{
	if (this->currency_ == Amount::currency::EUR)
	{
		return round((this->getNetValue() * EXCHANGE_RATE) * 100.0) / 100.0;
	}

	return this->netValue_;
}

double Amount::getNetValueInEUR() const
{
	if (this->currency_ == Amount::currency::USD)
	{
		return round((this->getNetValue() / EXCHANGE_RATE) * 100.0) / 100.0;
	}

	return this->netValue_;
}

void Amount::convertCurrency()
{
	if (this->currency_ == Amount::currency::USD)
	{
		this->netValue_ = this->getNetValueInEUR();
		this->currency_ = Amount::currency::EUR;

	}
	else if (currency_ == Amount::currency::EUR)
	{
		this->netValue_ = this->getNetValueInUSD();
		this->currency_ = Amount::currency::USD;
	}
}

std::ostream& operator<<(std::ostream& os, const Amount& Amount)
{
	os << Amount.getLabel() << ":" << std::endl
		<< "\t NetValue: " << Amount.getNetValue() << " " << Amount.getCurrencySymbol() << std::endl
		<< "\t Taxclass: " << static_cast<double>(static_cast<float>(Amount.getTaxclass() )) << "%" << std::endl
		<< "\t GrossValue: " << Amount.getGross() << " " << Amount.getCurrencySymbol() << std::endl
		<< "\t TaxAmount: " << Amount.getTaxAmount() << " " << Amount.getCurrencySymbol() << std::endl
		<< "\t Exchanged NetValue: ";
	if (Amount.getCurrency() == Amount::currency::EUR)
	{
		os << Amount.getNetValueInUSD() << " $";
	}
	else
	{
		os << Amount.getNetValueInEUR() << " €";
	}
	os << std::endl;
	return os;
}

void test()
{
	// Todo 6.2
	// Implement tests

	//default constructor
	Amount a1;
	std::cout << "Test default constructor" << std::endl;
	cout << a1 << std::endl;
	assert(a1.getLabel() == "undefined" && a1.getNetValue() == 0.0 && a1.getCurrency() == Amount::currency::EUR && a1.getTaxclass() == Amount::taxclass::NORMAL && a1.getGross() == 0.0 && a1.getTaxAmount() == 0.0);

	//Constructor
	Amount a2{ "orange", 1.0 };
	std::cout << "Test constructor(label,netto)" << std::endl;
	std::cout << "Example constructor(\"orange\",1.0)" << std::endl;
	cout << a2 << std::endl;
	assert(a2.getLabel() == "orange" && a2.getNetValue() == 1.0 && a2.getCurrency() == Amount::currency::EUR && a2.getTaxclass() == Amount::taxclass::NORMAL && a2.getGross() == 0.81 && a2.getTaxAmount() == 0.19);

	//constructor
	Amount a3{ "apple", 0.5, Amount::currency::USD, Amount::taxclass::REDUCED };
	std::cout << "Test constructor(label,netto,currency,taxclass)" << std::endl;
	std::cout << "Example constructor(\"apple\",0.5)" << std::endl;
	cout << a3 << std::endl;
	assert(a3.getLabel() == "apple" && a3.getNetValue() == 0.5 && a3.getCurrency() == Amount::currency::USD && a3.getTaxclass() == Amount::taxclass::REDUCED && a3.getGross() == 0.5 - (round((0.5 * 0.07) * 100.0) / 100.0) && a3.getTaxAmount() == (round((0.5 * 0.07) * 100.0) / 100.0) );

	//this needs more complex ctors
	/*Amount a4{ "apple juice", 0.75, '$', 7 };
	cout << a4;*/

	//copy assignment
	Amount a4 = a2;
	std::cout << "Test Copy Assignment" << std::endl;
	std::cout << "Should be same as (\"orange\",1.0)" << std::endl;
	cout << a4 << std::endl;
	assert(a4.getLabel() == "orange" && a4.getNetValue() == 1.0 && a4.getCurrency() == Amount::currency::EUR && a4.getTaxclass() == Amount::taxclass::NORMAL && a4.getGross() == 0.81 && a4.getTaxAmount() == 0.19);

	//void setLabel(string label);
	std::cout << "Test a4.setLabel(string label)" << std::endl;
	std::cout << "(\"orange\" should be changed to \"mango\" ) " << std::endl;
	a4.setLabel("mango");
	cout << a4 << std::endl;
	assert(a4.getLabel() == "mango" && a4.getNetValue() == 1.0 && a4.getCurrency() == Amount::currency::EUR && a4.getTaxclass() == Amount::taxclass::NORMAL && a4.getGross() == 0.81 && a4.getTaxAmount() == 0.19);
	
	//string getLabel() const;
	std::cout << "Test a4.getLabel()" << std::endl;
	std::cout << " Nothing should be changed " << std::endl;
	cout << "a4 Label is:  " << a4.getLabel() << std::endl;
	cout << a4 << std::endl;
	assert(a4.getLabel() == "mango" && a4.getNetValue() == 1.0 && a4.getCurrency() == Amount::currency::EUR && a4.getTaxclass() == Amount::taxclass::NORMAL && a4.getGross() == 0.81 && a4.getTaxAmount() == 0.19);

	//double setNetValue(double netValue);
	std::cout << "Test a4.setNetValue(double netValue)" << std::endl;
	std::cout << " setNetValue(10.0): " << std::endl;
	a4.setNetValue(10.0);
	cout << a4 << std::endl;
	assert(a4.getLabel() == "mango" && a4.getNetValue() == 10.0 && a4.getCurrency() == Amount::currency::EUR && a4.getTaxclass() == Amount::taxclass::NORMAL && a4.getGross() == 8.1 && a4.getTaxAmount() == 1.9);

	//double setNetValue(double netValue, currency currency);
	std::cout << "Test a4.setNetValue(double netValue, currency currency)" << std::endl;
	std::cout << " setNetValue(1.0, USD): " << std::endl;
	a4.setNetValue(1.0, Amount::currency::USD);
	cout << a4 << std::endl;
	assert(a4.getLabel() == "mango" && a4.getNetValue() == 1.0 && a4.getCurrency() == Amount::currency::USD && a4.getTaxclass() == Amount::taxclass::NORMAL && a4.getGross() == 0.81 && a4.getTaxAmount() == 0.19);
	
	//double getNetValue() const;
	std::cout << "Test a4.getNetValue()" << std::endl;
	std::cout << " Nothing should change. NetValue should be 1.0 and is currently: " << a4.getNetValue() << std::endl;
	cout << a4 << std::endl;
	assert(a4.getLabel() == "mango" && a4.getNetValue() == 1.0 && a4.getCurrency() == Amount::currency::USD && a4.getTaxclass() == Amount::taxclass::NORMAL && a4.getGross() == 0.81 && a4.getTaxAmount() == 0.19);

	//void setTaxclass(taxclass taxclass);
	std::cout << "Test a4.setTaxclass(taxclass taxclass)" << std::endl;
	std::cout << " setTaxClass(Amount::taxclass::REDUCED) should change Gross to 0.93 and taxAmount to 0.07 " << std::endl;
	a4.setTaxclass(Amount::taxclass::REDUCED);
	cout << a4 << std::endl;
	assert(a4.getLabel() == "mango" && a4.getNetValue() == 1.0 && a4.getCurrency() == Amount::currency::USD && a4.getTaxclass() == Amount::taxclass::REDUCED && a4.getGross() == 1.0 - (round((1.0 * 0.07) * 100.0) / 100.0) && a4.getTaxAmount() == (round((1.0 * 0.07) * 100.0) / 100.0));

	//taxclass getTaxclass() const;
	std::cout << "Test a4.getTaxclass()" << std::endl;
	std::cout << " Nothing should change " << std::endl;
	a4.getTaxclass();
	cout << a4 << std::endl;
	assert(a4.getLabel() == "mango" && a4.getNetValue() == 1.0 && a4.getCurrency() == Amount::currency::USD && a4.getTaxclass() == Amount::taxclass::REDUCED && a4.getGross() == 1.0 - ( round((1.0 * 0.07) * 100.0) / 100.0 ) && a4.getTaxAmount() == (round((1.0 * 0.07) * 100.0) / 100.0) );

	//double getGross() const;
	std::cout << "Test a4.getGross()" << std::endl;
	std::cout << " Nothing should change Gross should be 0.93 and is now: "<< a4.getGross() << std::endl;
	cout << a4 << std::endl;
	assert(a4.getLabel() == "mango" && a4.getNetValue() == 1.0 && a4.getCurrency() == Amount::currency::USD && a4.getTaxclass() == Amount::taxclass::REDUCED && a4.getGross() == 1.0 - ( round((1.0 * 0.07) * 100.0) / 100.0 ) && a4.getTaxAmount() == (round((1.0 * 0.07) * 100.0) / 100.0) );

	//double getTaxAmount() const;
	std::cout << "Test a4.getTaxAmount()" << std::endl;
	std::cout << " Nothing should change TaxAmount should be 0.07 and is now: " << a4.getTaxAmount() << std::endl;
	cout << a4 << std::endl;
	assert(a4.getLabel() == "mango" && a4.getNetValue() == 1.0 && a4.getCurrency() == Amount::currency::USD && a4.getTaxclass() == Amount::taxclass::REDUCED && a4.getGross() == 1.0 - ( round((1.0 * 0.07) * 100.0) / 100.0 ) && a4.getTaxAmount() == (round((1.0 * 0.07) * 100.0) / 100.0) );

	//double getNetValueInUSD() const;
	std::cout << "Test a2.getNetValueInUSD()" << std::endl;
	std::cout << " Nothing should change, netValueInUSD should be "<< a2.getNetValue() * EXCHANGE_RATE << " and is now: " << a2.getNetValueInUSD() << std::endl;
	cout << a2 << std::endl;
	assert(a2.getLabel() == "orange" && a2.getNetValue() == 1.0 && a2.getCurrency() == Amount::currency::EUR && a2.getTaxclass() == Amount::taxclass::NORMAL && a2.getGross() == 1.0 - ( round((1.0 * 0.19) * 100.0) / 100.0 ) && a2.getTaxAmount() == (round((1.0 * 0.19) * 100.0) / 100.0) );
	
	//double getNetValueInEUR() const;
	std::cout << "Test a4.getNetValueInEUR()" << std::endl;
	std::cout << " Nothing should change getNetValueInEUR should be "<< a4.getNetValue() / EXCHANGE_RATE <<" and is now: " << a4.getNetValueInEUR() << std::endl;
	cout << a4 << std::endl;
	assert(a4.getLabel() == "mango" && a4.getNetValue() == 1.0 && a4.getCurrency() == Amount::currency::USD && a4.getTaxclass() == Amount::taxclass::REDUCED && a4.getGross() == 1.0 - ( round((1.0 * 0.07) * 100.0) / 100.0 ) && a4.getTaxAmount() == (round((1.0 * 0.07) * 100.0) / 100.0) );

	//void convertCurrency();
	std::cout << "Test a4.convertCurrency()" << std::endl;
	std::cout << "Should change into opposite Currency from USD to EUR and convert netValue Gross TaxAmount from:" << std::endl;
	cout << a4 << " to:" << std::endl;
	a4.convertCurrency();
	cout << a4 << std::endl;
	assert(a4.getLabel() == "mango" && a4.getNetValue() == round((1.0 / EXCHANGE_RATE) * 100.0) / 100.0 && a4.getCurrency() == Amount::currency::EUR && a4.getTaxclass() == Amount::taxclass::REDUCED && a4.getGross() == round((0.93 / EXCHANGE_RATE) * 100.0) / 100.0 && a4.getTaxAmount() == round((0.07 / EXCHANGE_RATE) * 100.0) / 100.0);

	//currency getCurrency() const;
	//char getCurrencySymbol() const;
	std::cout << "Test a2.getCurrency() and a3.getCurrencySymbol " << std::endl;
	std::cout << " Nothing should change, Currency of a2 should be Amount::currency::EUR represented by € and is now: " << static_cast<char>( static_cast<int>(a2.getCurrency() ) ) << std::endl;
	cout << a2 << std::endl;
	std::cout << " Nothing should change, Currency of a3 should be Amount::currency::USD represented by $ and is now: " << a3.getCurrencySymbol() << std::endl;
	cout << a3 << std::endl;
	assert(a2.getLabel() == "orange" && a2.getNetValue() == 1.0 && a2.getCurrency() == Amount::currency::EUR && a2.getTaxclass() == Amount::taxclass::NORMAL && a2.getGross() == 1.0 - ( round((1.0 * 0.19) * 100.0) / 100.0 ) && a2.getTaxAmount() == (round((1.0 * 0.19) * 100.0) / 100.0) );
	assert(a3.getLabel() == "apple" && a3.getNetValue() == 0.5 && a3.getCurrency() == Amount::currency::USD && a3.getTaxclass() == Amount::taxclass::REDUCED && a3.getGross() == 0.5 - (round((0.5 * 0.07) * 100.0) / 100.0) && a3.getTaxAmount() == (round((0.5 * 0.07) * 100.0) / 100.0));
	
}

int main()
{
	test();
	return 0;
}
