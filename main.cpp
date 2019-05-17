#include <iostream>
#include <fstream>
#include <string.h>
#include "problema1.h"
#include "problema2.h"
using namespace std;

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

bool abrirArquivo(string *texto) {
  string line;
  string result;
  fstream myfile("dataset01.xml");
  if (myfile.is_open()) {
    while (getline(myfile, line))
      result += line + "\n";
  } else {
    myfile.close();
    return false;
  }
  myfile.close();
  *texto = result;
  return true;
}

int main() {
    string texto = "";
    if (!abrirArquivo(&texto)) {
      cout << "erro ao abrir o arquivo.\n";
      return 0;
    }
    cout << texto << endl;
    if (validacao(&texto))
      cout << "validacao terminada com exito" << endl;

      if (contaComponentes(&texto))
        cout << "Conta de componentes terminada com exito" << endl;
    return 0;
}
