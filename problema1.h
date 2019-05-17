#include <iostream>
#include <fstream>
#include <string.h>
#include "stack.h"
using namespace std;

bool validacao(string *texto) {
  structures::LinkedStack<string> pilha;
  string texto_temp = *texto;
  int cont = 0;
  for (int i = 0; i < texto_temp.length(); i++) {
    if (texto_temp[i] == '<') {
      if (texto_temp[i + 1] != '/') {
        int j = i + 1;
        string tag = "";
        while (texto_temp[j] != '>') {
          tag += texto_temp[j];
          j++;
        }
        i = j;
        pilha.push(tag);
        cont++;
      } else {
        int j = i + 2;
        string tag = "";
        while (texto_temp[j] != '>') {
          tag += texto_temp[j];
          j++;
        }
        i = j;
        string tag_pilha = pilha.pop();
        if (!(tag == tag_pilha)) {
          cout << "Tag '" << tag_pilha << "' não fechada" << "\ncont: " << cont << endl;
          return false;
        }
      }
    }
  }
  return pilha.empty();
}
