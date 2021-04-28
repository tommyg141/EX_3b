
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "NumberWithUnits.hpp"
#include <math.h>
using namespace std;
const double EPS = 0.001;
const char check = '-';

namespace ariel
{
    static map<string, map<string, double>> Data_Base;
    NumberWithUnits::NumberWithUnits(double k, const string &t)
    {
        //the "t" is connect to the namespace
        if (Data_Base.count(t) == 0)
        {
            throw invalid_argument("not exist");
        }
        this->key = k;
        this->type = t;
    };
    void NumberWithUnits::read_units(ifstream &units_file)
    {
        string first_argument;
        string secound_argument;
        string split;
        double value_first = 1;
        double value_secound = 0;
        while (!units_file.eof())
        {
            //"1" "unit" "=" "double" "unit"
            units_file >> value_first >> first_argument >> split >> value_secound >> secound_argument;
            Data_Base[first_argument][secound_argument] = value_secound;
            Data_Base[secound_argument][first_argument] = value_first / value_secound;
            /**fill the map , i want to fill it like a big graph , we want to make path between for example 
                from km to cm and in the same time we want to have from cm to km .
                for this one i find a nice waay to do in geeksforgeeks , also seen some of the showes for learning 

                **/
            for (auto &make_map : Data_Base[secound_argument])
            {
                if (secound_argument != make_map.first)
                {
                    Data_Base[first_argument][make_map.first] = make_map.second / (1 / value_secound);
                    Data_Base[make_map.first][first_argument] = (1 / value_secound) / make_map.second;
                }
            }
            for (auto &make_map : Data_Base[first_argument])
            {
                if (secound_argument != make_map.first)
                {
                   // Data_Base[{make_map.first,secound_argument}] = (1* value_secound) / make_map.second;
                   Data_Base[make_map.first][secound_argument] = (1 * value_secound) / make_map.second;
                    Data_Base[secound_argument][make_map.first] = make_map.second / (1 * value_secound);
                   
                }
            }
        }
    }

    /** 
              * for example here we do the check if the type of the unit are same , if for example it be like this
              * km ==ton its will trhow expction .
              * we want first of all to see if the unit from the same type , to avoid unnassery checks
              * after this we want to check if it in the unit file
              * then after this checks we can multiplay cuse we make a map with all the converts
             */
    double convert(const string &unit1, const string &unit2, double value)
    {
        if (unit1 == unit2)
        {
            return value;
        }
        if (Data_Base[unit1][unit2] == 0)
        {
            throw invalid_argument("not path between unit1 to unit 2");
        }
        return value * Data_Base[unit1][unit2];
    }
    std::ostream &operator<<(std::ostream &output, const NumberWithUnits &data)
    {
        output << data.key << "[" << data.type << ']';
        return output;
    }
   
    std::istream &operator>>(std::istream &in_uni, NumberWithUnits &stream)
    {
        string type;
        char dote;
        double value_of_unit = 0;
        in_uni >> value_of_unit >> dote >> type >> dote;
        if (type[type.length() - 1] == ']')
        {
            type.pop_back();
        }
        if (dote == check)
        {
            in_uni.putback(check);
        }
        if (Data_Base.count(type) == 0)
        {
            throw std::invalid_argument(" is not from the same type");
        }
        Data_Base.at(type);
        stream.key = value_of_unit;
        stream.type = type;
        return in_uni;
    }
    NumberWithUnits operator+(const NumberWithUnits &a, const NumberWithUnits &b)
    {
        double plus = convert(b.type, a.type, b.key);
        return NumberWithUnits(a.key + plus, a.type);
    }
    NumberWithUnits operator+(const NumberWithUnits &a)
    {
        return NumberWithUnits(a.key, a.type);
    }

    NumberWithUnits operator-(const NumberWithUnits &a)
    {
        return NumberWithUnits(-a.key, a.type);
    }
    NumberWithUnits operator-(const NumberWithUnits &a, const NumberWithUnits &b)
    {
        double minus = convert(b.type, a.type, b.key);
        return NumberWithUnits(a.key - minus, a.type);
    }
    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &a)
    {
        double plus = convert(a.type, this->type, a.key);
        this->key += plus;
        return *this;
    }
    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &a)
    {
        double minus = convert(a.type, this->type, a.key);
        this->key -= minus;
        return *this;
    }
    /**
     * most of this bool operators use the "==" and "< />"
     * after i make them and use the EPS  to check them 4points after the dote 
     * also i use the convert func to check if the type of them is the same and then to convert them to same type to do the check
    */
    bool operator==(const NumberWithUnits &a, const NumberWithUnits &b)
    {
        double temp = convert(b.type, a.type, b.key);
        return (fabs(a.key - temp) <= EPS);
    }
    bool operator>(const NumberWithUnits &a, const NumberWithUnits &b)
    {
        return (a.key > convert(b.type, a.type, b.key));
    }

    bool operator<(const NumberWithUnits &a, const NumberWithUnits &b)
    {
        return (a.key < convert(b.type, a.type, b.key));
    }
    bool operator<=(const NumberWithUnits &a, const NumberWithUnits &b)
    {
        return ((a < b) || (a == b));
    }

    bool operator!=(const NumberWithUnits &a, const NumberWithUnits &b)
    {
        return !(a == b);
    }
    bool operator>=(const NumberWithUnits &a, const NumberWithUnits &b)
    {
        return ((a > b) || (a == b));
    }
    //(* ,*=)
    NumberWithUnits operator*(const NumberWithUnits &b, const double &a)
    {
        return NumberWithUnits(b.key * a, b.type);
    }

    NumberWithUnits operator*(const double &a, const NumberWithUnits &b)
    {
        return NumberWithUnits(b.key * a, b.type);
    }

    NumberWithUnits &NumberWithUnits::operator++()
    {
        this->key += 1;
        return *this;
    }
    NumberWithUnits &NumberWithUnits::operator--()
    {
        this->key -= 1;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator++(int)
    {
        NumberWithUnits temp(this->key, this->type);
        this->key++;
        return temp;
    }
    NumberWithUnits NumberWithUnits::operator--(int)
    {
        NumberWithUnits temp(this->key, this->type);
        this->key--;
        return temp;
    }
    int comp(const NumberWithUnits &a, const NumberWithUnits &b)
    {
        return 0;
    }

}
