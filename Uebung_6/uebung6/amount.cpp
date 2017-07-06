#include <iostream>
#include <cassert>
#include <cmath>
#include <stdlib.h>
#include <iomanip> //std::setprecision

#define NORMAL_TAXRATE 19
#define REDUCED_TAXERATE 7
#define DEFAULT_CUR EUR
#define TRADECOURSE 1.142325  //EUR * TRADECOURSE = USD

class Amount
{
	public:
		enum currency { USD, EUR };
		enum taxeRate { REDUCED = REDUCED_TAXERATE,
										NORMAL 	= NORMAL_TAXRATE };
	// Todo 6.2
	// Implement class Amount
	private:
		currency cur_;
		taxeRate tr_;
		double brutto_;
		double netto_;
		std::string label_;

	public:
		Amount(): cur_{DEFAULT_CUR}, tr_{NORMAL}, netto_{0.0}, brutto_{0.0}, label_{"Nothing"} {}
		Amount(std::string l, double n): cur_{DEFAULT_CUR}, tr_{NORMAL}, netto_{n}, brutto_{n*(static_cast<double>(tr_+100)/100)}, label_{l} {}
		Amount(std::string l, double n, taxeRate t): cur_{DEFAULT_CUR}, tr_{t}, netto_{n}, brutto_{n*(static_cast<double>(tr_+100)/100)}, label_{l} {}
		Amount(std::string l, double n, currency c): cur_{c}, tr_{NORMAL}, netto_{n}, brutto_{n*(static_cast<double>(tr_+100)/100)}, label_{l} {}
		Amount(std::string l, double n, currency c, taxeRate t): cur_{c}, tr_{t}, netto_{n}, brutto_{n*(static_cast<double>(tr_+100)/100)}, label_{l} {}

		std::string getLabel(){
			return label_;
		}

		double getBrutto(){
			return brutto_;
		}

		double getNetto(){
			return netto_;
		}

		taxeRate getTaxRate(){
			return tr_;
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
			brutto_ = n*(static_cast<double>(tr_+100)/100);
		}

		void setTaxRate(taxeRate t){
			tr_ = t;
			brutto_ = this->getNetto() * (static_cast<double>(tr_+100)/100);
		}
};

std::ostream& operator<<(std::ostream& os, Amount::currency c){
	switch (c) {
		case Amount::EUR : os << "EUR"; break;
		case Amount::USD : os << "USD"; break;
		default: os << "";
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, Amount a) {
	os << "\"" << a.getLabel() << "\"" << std::endl;
	os << "Brutto: " << std::fixed << std::setprecision(2) << a.getBrutto() << a.getCurrency() << std::endl;
	os << "Netto: " << std::fixed << std::setprecision(2) << a.getNetto() << a.getCurrency() << std::endl;
	os << "TaxeRate: " << a.getTaxRate() << "%" << std::endl;

	return os;
}

void test()
{
	// Todo 6.2
	// Implement tests

	Amount empty;
	std::cout << empty << std::endl;
	assert(empty.getNetto()==0 && empty.getBrutto() == 0 && empty.getTaxRate()==NORMAL_TAXRATE
				 && empty.getCurrency()==Amount::EUR);


	Amount a {"Mango", 1.20};
	std::cout << a << std::endl;
	assert(a.getNetto()==1.2 && a.getBrutto() == 1.2*1.19 && a.getTaxRate()==Amount::NORMAL
				 && a.getCurrency()==Amount::EUR && a.getLabel().compare("Mango") == 0);

}

int main()
{
	test();
	return 0;
}
