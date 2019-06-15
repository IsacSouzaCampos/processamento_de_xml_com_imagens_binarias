/*!
    @file problema2.h
    @brief classe para rotulação das imagens
    
    Classe que faz a rotulação dos arquivos chamados pelo main

    @author Bryan Lima
    @author Isac Campos

    @date 21 May 2019
*/


#include <iostream>
#include <fstream>
#include <string.h>
#include "queue.h"

int linhas = 0, colunas = 0; //! < inteiros linhas e colunas como variavel global
int rotulo = 1; //! inteiro utilizado para a rotulação das matrizes
int **matrix_e, **matrix_r; //! < matriz inteiras, uma de entrada e a outra rotulada

bool defineDimensao(string*);
void montaMatrixEntrada(string *texto);
void enfileraCoordenadas(string nome);

/*!
   @brief struct para guardar coordenadas x e y
*/
struct coord_t
{
  int x = 0;  //! < inteiro que guardar coordenada x do elemento da matriz */
  int y = 0;  //! < inteiro que guardar coordenada y do elemento da matriz */
};

/*!
    @brief Classe principal de problema2.h que chama os principais metodos

    Possui o construtor da matriz de entrada, que é lida a partir do arquivo lido 
*/
bool contaComponentes(string *texto) {
  structures::LinkedQueue<int> fila;
  defineDimensao(texto);

  matrix_e = new int*[linhas];
  for (int i = 0; i < linhas; i++) {
    matrix_e[i] = new int[colunas];
  }

  montaMatrixEntrada(texto);

  return true;
}

/*!
    @brief classe montaMatrixEntrada

    Aqui é feito a leitura das tagas name e data. A tag name é utilizada para
    identificar qual imagem possui a rotulação. A tag data é para saber quando
    a matriz de entrada será lida para a rotulação

    @param texto string com todos os caracteres do arquivo lido

*/
void montaMatrixEntrada(string *texto) {
  string texto_temp = *texto;
  string nome = "";
  for (int i = 0; i < texto_temp.length(); i++) {
    if (texto_temp[i] == '<') {
      int j = i + 1;
      string tag = "";
      while (texto_temp[j] != '>') {
        tag += texto_temp[j];
        j++;
      }

      if (tag == "name") {
        j++;
        string novo_nome = "";
        while (texto_temp[j] != '<')
          novo_nome += texto_temp[j++];
        nome = novo_nome;
      }

      if (tag == "data") {
        j += 2;
        //preenchimento da matrix de entrada
        for (int l = 0; l < linhas; l++) {
          for (int c = 0; c < colunas; c++) {
            if (texto_temp[j] == '0') {
              matrix_e[l][c] = 0;
            }
            else {
              matrix_e[l][c] = 1;
            }
            j++;
          }
          j++;
        }
        enfileraCoordenadas(nome);
      }
      //atualiza valor de i
      i = j;
    }
  }
}

/*!
    @brief classe defineDimensão

    Aqui se lê as tags height e width para achar o tamanho das matrizes
    que serão usada para a rotulação

    @param texto string com todos os caracteres do arquivo lido
    @return true se a classe teve sucesso em implementar o metodo
*/
bool defineDimensao(string *texto) {
  string texto_temp = *texto;
  string height = "";
  string width = "";
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
        while (texto_temp[j] != '<') {
          height += texto_temp[j];
          j++;
        }
        linhas = stoi(height);
      } else if (tag == "width") {
        while (texto_temp[j] != '<') {
          width += texto_temp[j];
          j++;
        }
        colunas = stoi(width);
        return true;
      }
    }
  }
  return false;
}

/*!
    @brief classe enfileraCoordenadas
    
    Aqui é feita todo o processo de rotulação, utilizando o metodo do vizinho-4
    analisando as seguintes coordenadas (x-1, y); (x+1, y); (x, y-1); (x, y+1);
    do pixel atual. Enquanto houver vizinhos com intensidade 1, a matriz vai
    atribuindo o rotulo atual a esses pixels, até que eles acabem. No final, o
    rotulo é incrementado e se analisa o proximo pixel de intensidade 1.

    @param nome string que possui o nome da imagem que esta sendo rotulada
*/
void enfileraCoordenadas(string nome) {
  matrix_r = new int*[linhas];
  for (int i = 0; i < linhas; i++) {
    matrix_r[i] = new int[colunas];
  }
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
      matrix_r[i][j] = 0;
    }
}

  rotulo = 1;
  structures::LinkedQueue<coord_t> fila;
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
      if (matrix_e[i][j] == 1 && matrix_r[i][j] == 0) {
        coord_t coordAtual;
        coordAtual.x = i;
        coordAtual.y = j;
        fila.enqueue(coordAtual);
        //vizinho-4
        while (!fila.empty()) {
          coord_t coordAux;
          coordAux = fila.dequeue();
          //get linha e coluna atual
          int linha = coordAux.x;
          int coluna = coordAux.y;

          int eixoXmenosUm = linha - 1;
          int eixoXmaisUm = linha + 1;
          int eixoYmenosUm = coluna - 1;
          int eixoYmaisUm = coluna + 1;
          matrix_r[linha][coluna] = rotulo;

          //----------------------------------------------------------primeiro vizinho (x-1, y)
          //verifica se esta dentro dos limites do array
          if ((eixoXmenosUm) >= 0) {
            //verifica se é um a intensidade e se ja foi analisado
            if (matrix_e[eixoXmenosUm][coluna] == 1 && matrix_r[eixoXmenosUm][coluna] == 0) {
              coord_t coordElemento;
              coordElemento.x = eixoXmenosUm;
              coordElemento.y = coluna;
              fila.enqueue(coordElemento);
              matrix_r[coordElemento.x][coordElemento.y] = rotulo;
            }
          }
          //----------------------------------------------------------segundo vizinho (x+1, y)
          //verifica se esta dentro dos limites do array
          if ((eixoXmaisUm) < linhas) {
            //verifica se é um a intensidade e se ja foi analisado
            if (matrix_e[eixoXmaisUm][coluna] == 1 && matrix_r[eixoXmaisUm][coluna] == 0) {
              coord_t coordElemento;
              coordElemento.x = eixoXmaisUm;
              coordElemento.y = coluna;
              fila.enqueue(coordElemento);
              matrix_r[coordElemento.x][coordElemento.y] = rotulo;
            }
          }
          //----------------------------------------------------------terceiro vizinho (x, y-1)
          //verifica se esta dentro dos limites do array
          if ((eixoYmenosUm) >= 0) {
            //verifica se é um a intensidade e se ja foi analisado
            if (matrix_e[linha][eixoYmenosUm] == 1 && matrix_r[linha][eixoYmenosUm] == 0) {
              coord_t coordElemento;
              coordElemento.x = linha;
              coordElemento.y = eixoYmenosUm;
              fila.enqueue(coordElemento);
              matrix_r[coordElemento.x][coordElemento.y] = rotulo;
            }
          }
          //----------------------------------------------------------quarto vizinho (x, y+1)
          //verifica se esta dentro dos limites do array
          if ((eixoYmaisUm) < colunas) {
            //verifica se é um a intensidade e se ja foi analisado  
            if (matrix_e[linha][eixoYmaisUm] == 1 && matrix_r[linha][eixoYmaisUm] == 0) {
              coord_t coordElemento;
              coordElemento.x = linha;
              coordElemento.y = eixoYmaisUm;
              fila.enqueue(coordElemento);
              matrix_r[coordElemento.x][coordElemento.y] = rotulo;
            }
          }
        }
        rotulo++;
      }
    }
  }
  rotulo--;
  cout << nome << " " << rotulo << endl;
}
