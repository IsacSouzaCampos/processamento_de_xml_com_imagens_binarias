/*!
    @file problema1.h
    @brief classe para validação das tags
    
    Verifica se todas as tags estão de acordo com o padrão

    @author Bryan Lima
    @author Isac Campos

    @date 21 May 2019
*/

#include <iostream>
#include <fstream>
#include <string.h>
#include "stack.h"
using namespace std;

//Método para análise das tags. Recebe como parâmetro o texto aberto em main.cpp
/*!
    @brief classe validacao

    Empilha as tags que são abertas durante a análise e analisa se estas são fechadas
    de acordo com a ordem de abertura.

    @param texto string com todos os caracteres do arquivo lido
    @return true caso as tags estejam corretas e false se não estiverem
*/
bool validacao(string *texto) {
  //! Criação da pilha que guardará o nome das tags abertas ao decorrer do texto
  structures::LinkedStack<string> pilha;
  string texto_temp = *texto;
  //! Um contador é criado para facilitar a localização de possíveis erros
  int cont = 0;

  //! For que percorrerá todo o texto
  for (int i = 0; i < texto_temp.length(); i++) {
    //! Entra no if caso encontre uma abertura de tag
    if (texto_temp[i] == '<') {
      //! Verifica se a tag é de abertura ou fechamento
      if (texto_temp[i + 1] != '/') {
        //! Variável j é criada com valor inicial atualizado referente à i
        int j = i + 1;
        string tag = "";
        //! concatena os caracteres até a formação completa do nome da tag
        while (texto_temp[j] != '>') {
          tag += texto_temp[j];
          j++;
        }
        //! valor de i atualizado
        i = j;
        //! A nova tag é adicionada à pilha e cont é incrementado
        pilha.push(tag);
        cont++;
      //! Entra no else se for uma tag de fechamento
      } else {
        int j = i + 2;
        string tag = "";
        //! Etapa para pegar o nome da tag idêntica à do if
        while (texto_temp[j] != '>') {
          tag += texto_temp[j];
          j++;
        }
        //! Atualiza o i e desempilha a tag do topo de pilha
        i = j;
        string tag_pilha = pilha.pop();
        //! Se a tag desempilhada for diferente do esperado printa mensagem de erro e retorna false
        if (!(tag == tag_pilha)) {
          cout << "Tag '" << tag_pilha << "' não fechada" << "\ncont: " << cont << endl;
          return false;
        }
      }
    }
  }
  //! retorna true se a pilha estiver vazia e false se não estiver
  return pilha.empty();
}
