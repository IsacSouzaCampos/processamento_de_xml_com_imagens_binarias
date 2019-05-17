#include <iostream>
#include <fstream>
#include <string.h>
#include "queue.h"

bool defineDimensao(string*);

int linhas = 0, colunas = 0;

bool contaComponentes(string *texto) {
  structures::LinkedQueue<int> fila;
  defineDimensao(texto);
  cout << linhas << "\n" << colunas << endl;
}

bool defineDimensao(string *texto) {
  string height = "";
  string width = "";
  string texto_temp = *texto;
  for (int i = 0; i < texto_temp.length(); i++) {
    if (texto_temp[i] == '<') {
      int j = i + 1;
      string tag = "";
      while (texto_temp[j] != '>') {
        tag += texto_temp[j];
        j++;
      }
      j++;
      if (tag == "height") {
        while (texto_temp[j] != '<')
          height += texto_temp[j];
        linhas = stoi(height);
        cout << "chegou linhas\n";
      } else if (tag == "width") {
        while (texto_temp[j] != '<') {
          width += texto_temp[j];
          j++;
        }
        colunas = stoi(width);
        cout << "chegou colunas\n";
        return true;
      }
    }
  }
  return false;
}
