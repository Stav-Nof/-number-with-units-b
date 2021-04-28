#ifndef __NUMBERS__UNITS_H
#define __NUMBERS__UNITS_H
#include <fstream>
#include <map>
#include <string>
#include <iostream>
using namespace std;
namespace ariel
{
class NumberWithUnits
{
private:
	double amount;
	string unit;
	double fromTo(string from, string to)const;
	double RecfromTo(string from, string to)const;
	double conversion(string from, string to)const;
	 bool checkUnitExists(string un);
public:

	static map<string, map<string, double>> units;
	double getAmount() const
	{
	    return amount;
	}
	 string getUnit()const
	{
	    return unit;
	}
	void setUnit(string un)
	{
	    unit = un;
	}
	void setAmount(double am)
	{
	    amount = am;
	}
	static void read_units(ifstream &file);
	NumberWithUnits(double amount,const string& unit);
	
	 
	 //-
	NumberWithUnits operator-() const;
	NumberWithUnits operator+() const;
	// *
	NumberWithUnits operator*(double num) const;
	

	
	// + -
	NumberWithUnits operator+(NumberWithUnits &other) ;
	NumberWithUnits operator+(const NumberWithUnits &other) ;
	NumberWithUnits& operator+=(NumberWithUnits other);
	NumberWithUnits& operator=(const NumberWithUnits &other);
	NumberWithUnits operator++(int);
	NumberWithUnits& operator++();
	NumberWithUnits operator-(const NumberWithUnits &other);
	NumberWithUnits operator-( NumberWithUnits &other);
	NumberWithUnits& operator-=(const NumberWithUnits& other);
	NumberWithUnits operator--(int);
	NumberWithUnits& operator--();
	
	// compare operators
	bool operator ==(const NumberWithUnits &b) const;
	bool operator ==( NumberWithUnits &b) const;
	bool operator !=(const NumberWithUnits &b) const;
	bool operator >=(const NumberWithUnits &b) const;
	bool operator <=(const NumberWithUnits &b) const;
	bool operator >(const NumberWithUnits &b) const;
	bool operator <(const NumberWithUnits &b) const;

};
	 ostream& operator<<(ostream& os, const NumberWithUnits& num);
	 	 std::istream   & operator>>(std::istream   &in, NumberWithUnits  &other);
	 	  
	 	 NumberWithUnits operator*(double num, const NumberWithUnits& b);
}
#endif