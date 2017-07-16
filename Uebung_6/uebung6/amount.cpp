#include <iostream>
#include <cassert>
#include <cmath>
#include <stdlib.h>
#include <iomanip> //std::setprecision

#define NORMAL_TAXRATE 19
#define REDUCED_TAXRATE 7
#define DEFAULT_CUR EUR
#define TRADECOURSE 1.142325  //EUR * TRADECOURSE = USD

class Amount
{
	public:
		enum currency { USD, EUR };
		enum taxRate { REDUCED = REDUCED_TAXRATE,
										NORMAL 	= NORMAL_TAXRATE };

	private:
		currency cur_;
		taxRate tr_;
		double brutto_;
		double netto_;
		std::string label_;

	public:
		Amount(): cur_{DEFAULT_CUR}, tr_{NORMAL}, netto_{0.0}, brutto_{0.0}, label_{"Nothing"} {}
		Amount(std::string l, double n): cur_{DEFAULT_CUR}, tr_{NORMAL}, netto_{n}, brutto_{n*(static_cast<double>(tr_)+100.0)/100.0}, label_{l} {}
		Amount(std::string l, double n, taxRate t): cur_{DEFAULT_CUR}, tr_{t}, netto_{n}, brutto_{n*(static_cast<double>(tr_)+100.0)/100.0}, label_{l} {}
		Amount(std::string l, double n, currency c): cur_{c}, tr_{NORMAL}, netto_{n}, brutto_{n*(static_cast<double>(tr_)+100.0)/100.0}, label_{l} {}
		Amount(std::string l, double n, currency c, taxRate t): cur_{c}, tr_{t}, netto_{n}, brutto_{n*(static_cast<double>(tr_)+100.0)/100.0}, label_{l} {}

		//Copy assignment
		Amount& operator=(const Amount& a){
			cur_ = a.cur_;
			tr_ = a.tr_;
			this->setNetto(a.netto_);
			label_ = a.label_;
			return *this;
		}

		bool operator==(const Amount a){
			if(cur_!=a.cur_) return false;
			if(tr_!=a.tr_) return false;
			if(netto_!=a.netto_) return false;
			if(brutto_!=a.brutto_) return false;
			if(label_.compare(a.label_) != 0) return false;

			return true;
		}

		std::string getLabel(){
			return label_;
		}

		double getBrutto(){
			return brutto_;
		}

		double getNetto(){
			return netto_;
		}

		taxRate getTaxRate(){
			return tr_;
		}

		inline double getTaxFactor(){
			return (static_cast<double>(tr_)+100.0)/100.0;
		}

		currency getCurrency(){
			switch (cur_) {
				case EUR: return EUR;
				case USD: return USD;
				default: return EUR; //Just for avoiding compiler warning
			}
		}

		double getTradedNetto(){
			switch (cur_) {
				case EUR: return netto_ * TRADECOURSE;
				case USD: return netto_ / TRADECOURSE;
				default: return -1;
			}
		}

		double getTradedBrutto(){
			switch (cur_) {
				case EUR: return brutto_ * TRADECOURSE;
				case USD: return brutto_ / TRADECOURSE;
				default: return -1;
			}
		}

		double getTaxAmount(){
			return brutto_ - netto_;
		}

		void setCurrency(currency c){
			if (c != cur_){
				this->setNetto(getTradedNetto());
			}
			cur_ = c;
		}

		void setNetto(double n){
			netto_ = n;
			brutto_ = n * this->getTaxFactor();
		}

		void setNetto(double n, currency c){
			this->setCurrency(c);
			this->setNetto(n);
		}

		void setTaxRate(taxRate t){
			tr_ = t;
			brutto_ = this->getNetto() * this->getTaxFactor();
		}

		void setLabel(std::string s){
			label_ = s;
		}
};

std::ostream& operator<<(std::ostream& os, Amount::currency c){
	switch (c) {
		case Amount::EUR : os << "€"; break;
		case Amount::USD : os << "$"; break;
		default: os << "";
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, Amount a) {
	os << "Label:\t\"" << a.getLabel() << "\"" << std::endl;
	os << "Brutto:\t " << std::fixed << std::setprecision(2) << a.getBrutto() << a.getCurrency() << std::endl;
	os << "Netto:\t " << std::fixed << std::setprecision(2) << a.getNetto() << a.getCurrency() << std::endl;
	os << "TaxRate: " << a.getTaxRate() << "%" << std::endl;

	return os;
}


void test()
{
	// Todo 6.2
	// Implement tests

	//Default constructor
	Amount empty;
	std::cout << "Test default constructor" << std::endl;
	std::cout << empty << std::endl;
	assert(empty.getNetto()==0 && empty.getBrutto() == 0 && empty.getTaxRate()==NORMAL_TAXRATE
				 && empty.getCurrency()==Amount::EUR);

	//Contructor
	Amount a {"Mango", 1.0};
	std::cout << "Test constructor(label,netto)" << std::endl;
	std::cout << "Example constructor(\"Mango\",1.0)" << std::endl;
	std::cout << a << std::endl;
	assert(a.getNetto()==1.0 && a.getBrutto() == 1.0*a.getTaxFactor() && a.getTaxRate()==Amount::NORMAL
				 && a.getCurrency()==Amount::EUR && a.getLabel().compare("Mango") == 0);

	//Contructor
 	Amount a1 {"Mango", 1.0, Amount::USD};
  std::cout << "Test constructor(label,netto,currency)" << std::endl;
	std::cout << "Example constructor(\"Mango\",1.0,USD)" << std::endl;
  std::cout << a1 << std::endl;
  assert(a1.getNetto()==1.0 && a1.getBrutto() == 1.0*a1.getTaxFactor() && a1.getTaxRate()==Amount::NORMAL
 	 		  && a1.getCurrency()==Amount::USD && a1.getLabel().compare("Mango") == 0);

	//Contructor
	Amount a2 {"Mango", 1.0, Amount::REDUCED};
  std::cout << "Test constructor(label,netto,taxrate)" << std::endl;
	std::cout << "Example constructor(\"Mango\",1.0,REDUCED)" << std::endl;
  std::cout << a2 << std::endl;
  assert(a2.getNetto()==1.0 && a2.getBrutto() == 1.0*a2.getTaxFactor() && a2.getTaxRate()==Amount::REDUCED
 	 		  && a2.getCurrency()==Amount::EUR && a2.getLabel().compare("Mango") == 0);

	//Contructor
	Amount a3 {"MangoUS", 0.8, Amount::USD, Amount::REDUCED};
	std::cout << "Test constructor(label,netto,currency,taxrate)" << std::endl;
	std::cout << "Example constructor(\"MangoUS\",0.8,USD,REDUCED)" << std::endl;
	std::cout << a3 << std::endl;
	assert(a3.getNetto()==0.8 && a3.getBrutto() == 0.8*1.07 && a3.getTaxRate()==Amount::REDUCED
	 			 && a3.getCurrency()==Amount::USD && a3.getLabel().compare("MangoUS") == 0);


	//Copy assignment
	a3 = a2;
	std::cout << "Set MangoUS to Mango, with copy assignment" << std::endl;
	std::cout << a3 << std::endl;
	assert(a3==a2);


	 //setCurrency()
	std::cout << "Change Currency from EUR to USD" << std::endl;
	std::cout << "Brutto:\t" << a3.getBrutto() << a3.getCurrency() << " -> " << a3.getTradedBrutto() << "$" << std::endl;
	std::cout << "Netto:\t"  << a3.getNetto()  << a3.getCurrency() << " -> " << a3.getTradedNetto()  << "$" << std::endl;
	a3.setCurrency(Amount::USD);
	std::cout << a3 << std::endl;
	assert(a3.getNetto() == 1.0*TRADECOURSE && a3.getBrutto() == 1.07*TRADECOURSE  && a3.getCurrency()==Amount::USD);

	//setNetto()
	std::cout << "Change Netto to 1 and let current currency" << std::endl;
	std::cout << "\tBrutto:\t"  << "Netto:\t" << std::endl;
	std::cout << "from\t" << a3.getBrutto() << a3.getCurrency() << "\t" << a3.getNetto() << a3.getCurrency() << std::endl;
	a3.setNetto(1);
	std::cout << "to\t" << a3.getBrutto() << a3.getCurrency() << "\t" << a3.getNetto() << a3.getCurrency() << std::endl << std::endl;
	assert(a3.getNetto() == 1.0 && a3.getBrutto() == 1.0*a3.getTaxFactor());


	//setNetto() with specific currency
	std::cout << "Change Netto to 2EUR" << std::endl;
	std::cout << "\tBrutto:\t"  << "Netto:\t" << std::endl;
	std::cout << "from\t" << a3.getBrutto() << a3.getCurrency() << "\t" << a3.getNetto() << a3.getCurrency() << std::endl;
	a3.setNetto(2,Amount::EUR);
	std::cout << "to\t" << a3.getBrutto() << a3.getCurrency() << "\t  " << a3.getNetto() << a3.getCurrency() << std::endl << std::endl;
	assert(a3.getNetto() == 2.0 && a3.getBrutto() == 2.0*a3.getTaxFactor() && a3.getCurrency()==Amount::EUR);

	//setTaxRate()
	std::cout << "Change Tax Rate from REDUCED to NORMAL" << std::endl;
	std::cout << "Brutto:\tNetto:\tTaxRate" << std::endl;
	std::cout << a3.getBrutto() << a3.getCurrency() << "\t " << a3.getNetto() << a3.getCurrency() << "\t" << a3.getTaxRate() << "%" << std::endl;
	a3.setTaxRate(Amount::NORMAL);
	std::cout << a3.getBrutto() << a3.getCurrency() << "\t " << a3.getNetto() << a3.getCurrency() << "\t" << a3.getTaxRate() << "%" << std::endl << std::endl;
	assert(a3.getBrutto() == 2.0*a3.getTaxFactor() && a3.getTaxRate() == Amount::NORMAL);

	//setLabel()
	std::cout << "Change label from \"Mango\" to \"New Mango\"" <<std::endl;
	std::cout << "\"" << a3.getLabel() << "\" -> ";
	a3.setLabel("New Mango");
	std::cout << "\"" << a3.getLabel() << std::endl << std::endl;
	assert(a3.getLabel().compare("New Mango") == 0);

	//getTaxAmount()
	std::cout << "Get the amount of tax of the brutto price" << std::endl;
	std::cout << "Brutto - Netto = TaxAmount" << "\""<< std::endl;
	std::cout << a3.getBrutto() << a3.getCurrency() << " - " << a3.getNetto() << a3.getCurrency() << " = " << a3.getTaxAmount() << a3.getCurrency() << std::endl;
	assert(a3.getBrutto() - a3.getNetto() == a3.getTaxAmount());
}

int main()
{
	test();
	return 0;
}
