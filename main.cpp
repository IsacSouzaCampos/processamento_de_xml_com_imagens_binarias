/*!
    @file main.cpp
    @brief classe principal
    
    Classe principal chama os métodos de outras classes e contém
    método para abertura do arquivo

    @author Bryan Lima
    @author Isac Campos

    @date 21 May 2019
*/

#include <iostream>
#include <fstream>
#include <string.h>
#include "problema1.h"
#include "problema2.h"
using namespace std;

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

/*!
    @brief classe abrirArquivo

    Efetua a abertura do arquivo pedido pelo usuário que será
    utilizado durante toda a execução do programa

    @param texto string a ser atualizado com o texto do arquivo
    @return true se a classe teve sucesso em implementar o metodo
*/
bool abrirArquivo(string *texto) {
  string xmlfilename;
  //! Aguarda para receber o nome do arquivo fornecido pelo usuário
  cin >> xmlfilename;


  string line;
  string result;
  fstream myfile(xmlfilename);

  //! Testa se o arquivo está realmente aberto
  if (myfile.is_open()) {
    //! Passa cada uma das linhas do .xml para a variável line e concatena o que foi passado pra ela com a string result
    while (getline(myfile, line))
      result += line + "\n";
  } else {
    //! Dá um close no arquivo caso ele não entre no if e retorna false
    myfile.close();
    return false;
  }
  //! Fecha o arquivo
  myfile.close();
  //! Setta o texto criado em main.cpp igual ao resultado final de result
  *texto = result;
  //Se chegou aqui é pq tudo ocorreu como deveria, então retorna true
  return true;
}

/*!
    @brief classe main

    Classe principal que dá início à execução do arquivo e administra
    a ordem das chamadas de métodos

    @param parâmetros padrões de métodos main
    @return 0 se o programa chegou ao fim
*/
int main() {
    //! Criação do texto a ser usado durante toda a execução do programa
    string texto = "";
    //! Chama o método abrirArquivo e testa se ele deu erro ou executou
    //corretamente até o final
    if (!abrirArquivo(&texto)) {
      //! Mensagem de erro caso algo errado tenha ocorrido e retorna zero para finalizar a execução do programa
      cout << "erro ao abrir o arquivo.\n";
      return 0;
    }
    //! Executa o método validação pertencente à problema1.h e testa se sua execução foi dada com êxido
    if (!validacao(&texto)) {
      //! Mensagem de erro em caso de problema na execução
      cout << "error" << endl;
    //! Executa o método contaComponentes apenas se a validação tiver ocorrido como o esperado
    } else if (contaComponentes(&texto)) {
    }
    //! Finaliza o programa
    return 0;
}
