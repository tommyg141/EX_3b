
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace std;
namespace ariel{
        class NumberWithUnits{
        
        private:
             double key;
             std::string type;
        
        
        public:
        NumberWithUnits(double k,const string &t) ;
        static void read_units(ifstream& units_file);
        friend int comp(const NumberWithUnits& a, const NumberWithUnits& b);
        ~NumberWithUnits(){};        
        friend NumberWithUnits operator+(const NumberWithUnits& a, const NumberWithUnits& b);
        friend NumberWithUnits operator+(const NumberWithUnits& a);
        friend NumberWithUnits operator-(const NumberWithUnits& a) ;
        friend NumberWithUnits operator-(const NumberWithUnits& a, const NumberWithUnits& b);
         NumberWithUnits& operator+=(const NumberWithUnits& a);
         NumberWithUnits& operator-=(const NumberWithUnits& a);
    //(==,!=,<=,>=)
            friend bool operator==(const NumberWithUnits& a, const NumberWithUnits& b);
            friend bool operator!=(const NumberWithUnits& a, const NumberWithUnits& b);
            friend bool operator<=(const NumberWithUnits& a, const NumberWithUnits& b);
            friend bool operator>=(const NumberWithUnits& a, const NumberWithUnits& b);
            friend bool operator<(const NumberWithUnits& a, const NumberWithUnits& b);
            friend bool operator>(const NumberWithUnits& a, const NumberWithUnits& b);
        //(* ,*=)
            friend NumberWithUnits operator*(const double& a, const NumberWithUnits& b);
            friend NumberWithUnits operator*(  const NumberWithUnits& b,const double& a);
        //opost and pre fix
             NumberWithUnits& operator++();     
             NumberWithUnits& operator--( );     
             NumberWithUnits operator++(int);          
             NumberWithUnits operator--(int);    
        //(input,output)
            friend std::ostream& operator<< (std::ostream& output, const NumberWithUnits& c);
            friend std::istream& operator>> (std::istream& input , NumberWithUnits& c);

            
    };    
    
}
