
#include "NumberWithUnits.hpp"
using namespace ariel;
map<string, map<string, double>> NumberWithUnits::units;

const double EPS = 0.0001;

 bool NumberWithUnits::checkUnitExists(string un)
{
	for(auto elem : units)
	{
		if(elem.first == un)
		return true;
		for(auto elem2 : elem.second)
		{
			if(elem2.first == un)
			return true;
		}
	}
	return false;
}
double NumberWithUnits::fromTo(string from, string to)const
{
   if(from == to)
        return 1;
    if(units.find(to) != units.end())
    {
        //units[to] -> map (string(from), amount)
        if(units[to].find(from) != units[to].end())
            return 1 / units[to][from];
    }
    if(units.find(from) != units.end())
    {
        //units[from] -> map (string(to), amount)
         if(units[from].find(to) != units[from].end())
            return units[from][to];
    }
    //the belong to someone
    return -1;
    //else return -1 (error)
}

double NumberWithUnits::RecfromTo(string from, string to)const
{
    //example: meter + dcm 
    //from dcm to meter
    //try to get from meter (to) to dcm (from)
    if(from == to)
        return 1;
    // cout << "1. from: " << from << ". to: " << to<< endl ;
    double res = fromTo(from, to);
    if(res != -1)
    {
        // cout << "2. from: " << from << ". to: " << to << ". res:" << res<< endl ;
        return res;
    }
    else
    {
        // cout << "3.." << endl;
        for(auto elem : units[from])
        {
            double price = RecfromTo(elem.first, to);
            if(price != -1)
            {
            // cout << "price: " << price <<  endl;
            // cout << "many: " << fromTo(from, elem.first) << endl;
            if(price != -1)
                return price * fromTo(from, elem.first);
            }
        }
    }
    return -1;
}
double NumberWithUnits::conversion(string from, string to)const
{
    double result = fromTo(from, to);
    if(result != -1)
        return result;
    result = RecfromTo(from, to);
    if(result != -1)
        return result;
    result = RecfromTo(to, from);
    if(result != -1)
        return 1 / result;
    return -1;
}
 void NumberWithUnits::read_units(ifstream &file)
	{
	    if(!file.is_open())
	        return;
	    while(!file.eof())
	    {
	        double amount1, amount2;
	        string unit1, unit2;
	        string garb;
	        file >> amount1 >> unit1 >> garb >> amount2 >> unit2;
	        //cout << amount1 <<" " << unit1;
	        //cout << endl << amount2 << unit2 << endl;
	        amount2 = amount2 / amount1;
	        amount1 = 1;
	        if (units.find(unit1) == units.end()) 
	        {
	            map<string, double> valuesMap;
	            valuesMap[unit2] = amount2;
	            units[unit1] = valuesMap;
	            
	            //IMPORTANT DON'T ADD MULTIPLE DEFINITIONS (CHECK IF EXISTS)
	            // TO PREVENT INFINITE LOOP
	            
	            
	            /*
	            map<string, double> valuesMap2;
	            valuesMap2[unit1] = 1 / amount2;
	            units[unit2] = valuesMap2;
	            */
	        }
	        else
	        {
	          units[unit1][unit2] = amount2;
	          //units[unit2][unit1] = 1/amount2;
	        }
	    }
	    file.close();
	}
	NumberWithUnits& NumberWithUnits::operator++()
	{
		this->setAmount(getAmount() + 1);
		return *this;
	}
	NumberWithUnits NumberWithUnits::operator++(int)
	{
		NumberWithUnits copy = *this;
		++*this;
		return copy;
	}
	NumberWithUnits NumberWithUnits::operator--(int)
	{
		NumberWithUnits copy = *this;
		--*this;
		
		return copy;
	}
	NumberWithUnits &NumberWithUnits::operator--()
	{

	
			this->setAmount(getAmount() - 1);
		return *this;
	}
	NumberWithUnits::NumberWithUnits(double amount, const string& unit):amount(amount), unit(unit)
	{
	    if(checkUnitExists(unit) == false || unit == "")
	    	throw invalid_argument("Unit does not exist");
	}
		 ostream& ariel::operator<<(ostream& os, const NumberWithUnits& num)
	 {
	     os << num.getAmount() << "[" << num.getUnit() << "]";
	     return os;
	 }
	 	NumberWithUnits& NumberWithUnits::operator=(const NumberWithUnits &other)
	 	{
	 		if(checkUnitExists(other.getUnit()) == false)
	 			throw invalid_argument("unit does not exist");
	 		this->setAmount(other.getAmount());
	 		this->setUnit(other.getUnit());
	 		return *this;
	 	}
	 	NumberWithUnits NumberWithUnits:: operator-() const
	{
	    NumberWithUnits newNum(-getAmount(), getUnit());
	    return newNum;
	}
		NumberWithUnits  NumberWithUnits::operator+() const
	{
		 NumberWithUnits newNum(getAmount(), getUnit());
	    return newNum;
	}

		NumberWithUnits NumberWithUnits::operator*(double num) const
	{
	     NumberWithUnits newNum(num * amount, unit);
	    return newNum;
	}
	NumberWithUnits ariel::operator*(double num, const NumberWithUnits& b)
	{
	    NumberWithUnits newNum(num * b.getAmount(), b.getUnit());
	    return newNum;
	}
		NumberWithUnits NumberWithUnits::operator+(NumberWithUnits &other) 
	{
	    double oneAmount = conversion(other.getUnit(), unit);
	       if(oneAmount == -1)
	       {
	        throw invalid_argument("Units do not match - [" + other.getUnit() +"] cannot be converted to [" + unit + "]");
	        
	        NumberWithUnits newNum(amount, unit);
	        return newNum;
	       }
	   //cout << oneAmount*other.getAmount() << endl;
	    NumberWithUnits newNum(amount +  oneAmount*other.getAmount(), unit);
	    return newNum;
	}
		NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &other) 
	{
	    double oneAmount = conversion(other.getUnit(), unit);
	       if(oneAmount == -1)
	       {
	        throw invalid_argument("Units do not match - [" + other.getUnit() +"] cannot be converted to [" + unit + "]");
	        
	        NumberWithUnits newNum(amount, unit);
	        return newNum;
	       }
	   //cout << oneAmount*other.getAmount() << endl;
	    NumberWithUnits newNum(amount +  oneAmount*other.getAmount(), unit);
	    return newNum;
	}
		NumberWithUnits& NumberWithUnits::operator+=(NumberWithUnits other)
	{
	    *this = *this + other;
	    return *this;
	}
	
		NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits& other)
	{
	    *this = *this - other;
	    return *this;
	}
		NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &other)
	{
	     double oneAmount = conversion(other.getUnit(), unit);
	       if(oneAmount == -1)
	       {
	        throw invalid_argument("Units do not match - [" + other.getUnit() +"] cannot be converted to [" + unit + "]");
	        NumberWithUnits newNum(amount, unit);
	        return newNum;
	       }
	    NumberWithUnits newNum(amount -  oneAmount*other.getAmount(), unit);
	    return newNum;
	}
	NumberWithUnits NumberWithUnits::operator-(NumberWithUnits &other)
	{
	     double oneAmount = conversion(other.getUnit(), unit);
	       if(oneAmount == -1)
	       {
	        throw invalid_argument("Units do not match - [" + other.getUnit() +"] cannot be converted to [" + unit + "]");
	        NumberWithUnits newNum(amount, unit);
	        return newNum;
	       }
	    NumberWithUnits newNum(amount -  oneAmount*other.getAmount(), unit);
	    return newNum;
	}
		bool NumberWithUnits::operator ==(const NumberWithUnits &other) const
	{
	    double oneAmount = conversion(other.getUnit(), unit);
	       if(oneAmount == -1)
	       {
	        throw invalid_argument("Units do not match - [" + other.getUnit() +"] cannot be converted to [" + unit + "]");
	        
	        return false;
	       }
	    return abs(amount - oneAmount * other.getAmount()) < EPS;
	}
	bool NumberWithUnits::operator ==( NumberWithUnits &other) const
	{
	    double oneAmount = conversion(other.getUnit(), unit);
	       if(oneAmount == -1)
	       {
	        throw invalid_argument("Units do not match - [" + other.getUnit() +"] cannot be converted to [" + unit + "]");
	        
	        return false;
	       }
	       
	    return abs(amount - oneAmount * other.getAmount()) < EPS;
	}
		bool NumberWithUnits::operator !=(const NumberWithUnits &b) const
	{
	    return !(*this == b);
	}
		bool NumberWithUnits::operator >=(const NumberWithUnits &other) const
	{
	     double oneAmount = conversion(other.getUnit(), unit);
	       if(oneAmount == -1)
	       {
	        throw invalid_argument("Units do not match - [" + other.getUnit() +"] cannot be converted to [" + unit + "]");
	        
	        return false;
	       }
	    return amount >= oneAmount * other.getAmount();
	}
		bool NumberWithUnits::operator <=(const NumberWithUnits &other) const
	{
	    double oneAmount = conversion(other.getUnit(), unit);
	       if(oneAmount == -1)
	       {
	        throw invalid_argument("Units do not match - [" + other.getUnit() +"] cannot be converted to [" + unit + "]");
	         
	        return false;
	       }
	    return amount <= oneAmount * other.getAmount();
	}
		bool NumberWithUnits::operator >(const NumberWithUnits &other) const
	{
	     double oneAmount = conversion(other.getUnit(), unit);
	       if(oneAmount == -1)
	       {
	        throw invalid_argument("Units do not match - [" + other.getUnit() +"] cannot be converted to [" + unit + "]");
	         
	        return false;
	       }
	    return amount > oneAmount * other.getAmount();
	}
		bool NumberWithUnits::operator <(const NumberWithUnits &other) const
	{
	   double oneAmount = conversion(other.getUnit(), unit);
	       if(oneAmount == -1)
	       {
	        throw invalid_argument("Units do not match - [" + other.getUnit() +"] cannot be converted to [" + unit + "]");
	       
	        return false;
	       }
	    return amount < oneAmount * other.getAmount();
	}
	
		 std::istream   &ariel::operator>>(std::istream   &in, NumberWithUnits  &other)
	{
	    double num = 0;
	    string stnum = "";
	    char ch = ' ';
	    in.get(ch);
	     while(ch != '[')
	    {
	        stnum += ch;
	        in.get(ch);
	    }
	    num = stod(stnum);
	    in.get(ch);
	    string type = "";
	    while(ch != ']')
	    {
	        if(ch != ' ')
	            type += ch;
	         in.get(ch);
	    }
	    NumberWithUnits cop(num, type);
	    other = cop;
	    other.setUnit(type);
	    other.setAmount(num);
	    return in;
	}
	