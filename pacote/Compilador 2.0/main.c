/*	UERN - 2018.1 - Compiladores
	Programa desenvolvido como projeto para disiplina de Compiladores.
	O programa tem como objetivo reconhecer um arquivo .txt com estrutura de um memorando especificado
pela professora.
	O programa retorna dois arquivos .txt um com nome de reperro.txt (Reporte de Erros) e outro com tabela.txt
Desenvolvedores: Althierfson Tullio Azevedo de Lima
				 Marcos André Azevedo de Assis
*/

#include "lexico\\ana_lexica.h"

void main(void){
  FILE *memo;
  memo = fopen("memorando.txt", "r");

  if(memo == NULL){
    printf("Erro na abertura do arquivo\n");
  }else{
      criar_tab(memo);
  }

}
