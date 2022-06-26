#include <pybind11/pybind11.h>
#include <hmac_sha512_component.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include <bitset>
using namespace std;


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
            if(Index_Number>2**31){

            }
            std::string Index_Number_B=" ";
            // converti int en 4 byte sequence
            std::string Index_Number_B =intToByte(Index_Number);

            //resSer= 0x00 || ser256(kpar) || ser32(i)
            resSer=Private_Key+Index_Number_B;
            // hmT=hmac_sha512(Chaine_Code,resSer)
            //convert the L part of hmT on binary
            string R_B=stringToBin(hmT[1]);
            Child_D_Key = R_B+Private_Key;

        }
        const std::string &getCkd() const {
            return Child_D_Key; }
          ~Ckd() {}
  }

  namespace py = pybind11;

  PYBIND11_MODULE(composant_4,CKD) {
    py::class_<CKD>(composant_4, "CKD")
    /*py::class_<Cle>(Key, "CKD",py::dynamic_attr())*/
       	.def(py::init<>())
 	      .def("initialize", &Ckd::initialize)
        .def("getCkd", &Ckd::getCkd)
  }

