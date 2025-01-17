#include <pybind11/pybind11.h>
#include "hmac_sha512/hmac_sha512_component/hmac_sha512.h"
#include <string>
#include <stdexcept>
#include <iostream>
#include <bitset>
#include<sstream>
using namespace std;
string int_to_hex( int i )
{
std::stringstream sstream;
sstream << std::hex << i;
std::string result = sstream.str();
//const char *res=result.c_str();
return result;
}

string intToByte( uint32_t n )
{
  string r;
  unsigned char bytes[4];
  bytes[0] = (n >> 24) & 0xFF;
  bytes[1] = (n >> 16) & 0xFF;
  bytes[2] = (n >> 8) & 0xFF;
  bytes[3] = (n >> 0) & 0xFF;
   for(int i = 0; i < 4; i++){
     for (int j = 7; j >= 0; j--) {
        int b = bytes[i] >> j;
        if (b & 1)
            r+= "1";
        else
            r+= "0";
    }
   }

  return r;
}
string  stringToBin(string str)
{
    std::string res;
    for (std::size_t i = 0; i < str.size(); i++) {
         res+=bitset<8>(str[i]).to_string();
    }

    return res;
}

class Ckd
{

    private:

        std::string Child_D_Key;

      public:
          Ckd();
          //uint32 to make sure that i is 32 bytes
          void initialize(std::string &Private_Key,std::string &Chaine_Code,uint32_t  Index_Number) {
            // converti int en 4 byte sequence
            string  index_Number_H =int_to_hex(Index_Number);

            //resSer= 0x00 || ser256(kpar) || ser32(i)
            string resSer=Private_Key+index_Number_H;
	   // const char*resSer_c=resSer.c_str();

            string  hmT=hmac_sha512(Chaine_Code,resSer);
	    //hmac ne retourne plus un tableau de 2 string 
	    //il faut donc couper le string en 2 et prendre la première partie 
	    string hmTR=hmT.substr(0,hmT.length()/2);
            //convert the L part of hmT on binary
            //string hmT[2]={"aab","97GY"};
	    //string hmTI=hmT[1]+index_Number_H;
	    string hmTI=hmTR+index_Number_H;
            Child_D_Key =Private_Key+hmTI;

        }
        const std::string &getCkd() const {
            return Child_D_Key; }
          ~Ckd() {}
  };

  namespace py = pybind11;

  PYBIND11_MODULE(composant_4,CKD) {
    py::class_<Ckd>(CKD,"Ckd")
    /*py::class_<Cle>(Key, "CKD",py::dynamic_attr())*/
       	.def(py::init<>())
 	      .def("initialize", &Ckd::initialize)
        .def("getCkd", &Ckd::getCkd);
  }

