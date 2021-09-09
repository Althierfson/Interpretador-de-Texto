//esse arquivo (apesar do nome) trata todas as partes do interpretador lexico, sintatico e semantico

//bibliotecas usadas
#include <stdio.h> //biblioteca basica
#include <stdlib.h> // biblioteca basica
#include <string.h> // ultilizada para manipulção de strings
#include <time.h> // ultilizada para coleta de ano do sistema
#include "automatos.h" //biblioteca que criar e manipula automatos
//fim_bibliotecas usadas

//alfabetos
char letras[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o' ,'p', 'q',
'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

char letrasM[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

char numeros[10] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};

char car_especi[5] = {':', ',', '.', '-', '/'};
//fim_alfabeto

struct tab_dina{ //estrutura da tabela dinanmica
  int linha;
  char token[50];
  char ana_lexica[20];
  char ana_sintatica[20];
  struct tab_dina *prox;
};

/*automatos reconhecedores de tokens
  obs.
      foi utilizado automatos para reconhecimento das cadeias de caracteres.
      a utilização em conjunto dos dois arqivos(ana_lexica.h e automatos.h) é o que faz o reconhecimento correto
    dos automatos, uma vez que a biblioteca automatos.h nao reconhece por se so os token, apenas criar e
    manipula.
      para funcionamento correto os estados finais são declarados com identificadores negativos, a função
    reconhecer() da automatos.h retonar o estado fina em que o token terminou, se o token for
    reconhecido o estado serar negativo.
      função nome() esta comentada, os outros seguem a mesma logica
*/
int nome(char token[]){//automato que reconhece nome
  /*sempre que a funçao é chamanda ela criar um novo automato, infelismente nao foi feita
    funções de liberação de memoria*/
  struct vet *nome=NULL; //ponteiro com estutura do automato
  char trans[67]; //variavel que controla os caracteres de transaçao
  int result; // variavel que guarda o estado final

  //criando estados
  nome = inserir_v(nome, 0); // Q0
  nome = inserir_v(nome, -1);// Q1 estado final declarado em negativo
  nome = inserir_v(nome, 2); // Q2 é estado de morte
  //fim_creando estados

  //criando as transaçoes entre os estados
  //Q0 para Q1 qualque letra do vetor letrasM esse vetor contem apenas letras maiúsculas
  nome = inserir_a(nome, 0, -1, letrasM);
  memset(trans, 0 , 67);//limpando vetor transaçao

  //inserindo no veotor trans todos os caracteres aceitos para transação
  strncat(trans, letras, 26);strncat(trans, numeros, 10);strncat(trans, car_especi, 5);
  //Q0 para Q2 qualque caractere que não seja maiúscula
  nome = inserir_a(nome, 0, 2, trans);
  memset(trans, 0 ,67); //limpando vetor transaçao

  //inserindo no vetor trans todos os caracteres contidos en letras veotr com letras minusculas
  strncat(trans, letras, 26);
  //Q1 par Q1 todos as letras maiusculas
  nome = inserir_a(nome, -1, -1, trans);
  memset(trans, 0 ,67); //limpando trans

  // Q1 para Q2
  strncat(trans, letrasM, 26);strncat(trans, numeros, 10);strncat(trans, car_especi, 5);
  nome = inserir_a(nome, -1, 2, trans);
  memset(trans, 0, 67);

  //Q2 para Q2
  strncat(trans, letrasM, 26);strncat(trans, numeros, 10);strncat(trans, car_especi, 5);strncat(trans, letras, 26);
  nome = inserir_a(nome, 2, 2, trans);

  result = reconhecer(nome, token);//retona o estado final

  if(result < 0){// se estado negativos reconhece e retorna 1
    return 1;
  }else{// retona 0
    return 0;
  }
}

int numero(char token[]){//automato que reconhece numeros
  struct vet *nome=NULL;
  char trans[67];
  int result;

  nome = inserir_v(nome, 0);
  nome = inserir_v(nome, -1);
  nome = inserir_v(nome, 2);
  memset(trans, 0, 67);
  strncat(trans, numeros, 9);
  nome = inserir_a(nome, 0, -1, trans);
  memset(trans, 0, 67);
  strncat(trans, letras, 26);strncat(trans, letrasM, 26);strncat(trans, car_especi, 5);strncat(trans, "0", 1);
  nome = inserir_a(nome, 0, 2, trans);
  memset(trans, 0, 67);
  strncat(trans, numeros, 10);
  nome = inserir_a(nome, -1, -1, trans);
  memset(trans, 0, 67);
  strncat(trans, letras, 26);strncat(trans, letrasM, 26);strncat(trans, car_especi, 5);
  nome = inserir_a(nome, -1, 2, trans);
  memset(trans, 0, 67);
  strncat(trans, letras, 26);strncat(trans, letrasM, 26);strncat(trans, car_especi, 5);strncat(trans, numeros, 10);
  nome = inserir_a(nome, 2, 2, trans);

  result = reconhecer(nome, token);

  if(result < 0){
    return 1;
  }else{
    return 0;
  }
}

int dia(char token[]){//automato que reconhece dia
  struct vet *nome=NULL;
  char trans[67];
  int result;

  nome = inserir_v(nome, 0);
  nome = inserir_v(nome, 1);
  nome = inserir_v(nome, -2);
  nome = inserir_v(nome, 3);
  nome = inserir_v(nome, -4);
  nome = inserir_v(nome, 5);
  //estado q0
  memset(trans, 0, 67);
  strncat(trans, "012", 3);
  nome = inserir_a(nome, 0, 1, trans);
  memset(trans, 0 ,67);
  strncat(trans, letras, 26);strncat(trans, letrasM, 26);strncat(trans, car_especi, 5);strncat(trans, "456789", 6);
  nome = inserir_a(nome, 0, 5, trans);
  memset(trans, 0, 67);
  nome = inserir_a(nome, 0, 3, "3");
  //estado q1
  memset(trans, 0, 67);
  strncat(trans, numeros, 10);
  nome = inserir_a(nome, 1, -2, trans);
  memset(trans, 0, 67);
  strncat(trans, letras, 26);strncat(trans, letrasM, 26);strncat(trans, car_especi, 5);
  nome = inserir_a(nome, 1, 5, trans);
  //q2
  memset(trans, 0 ,67);
  strncat(trans, letras, 26);strncat(trans, letrasM, 26);strncat(trans, car_especi, 5);strncat(trans, numeros, 10);
  nome = inserir_a(nome, -2, 5, trans);
  //q3
  memset(trans, 0, 67);
  strncat(trans, "012", 3);
  nome = inserir_a(nome, 3, -4, trans);
  memset(trans, 0, 67);
  strncat(trans, letras, 26);strncat(trans, letrasM, 26);strncat(trans, car_especi, 5);strncat(trans, "3456789", 7);
  nome = inserir_a(nome, 3, 5, trans);
  //q4
  memset(trans, 0, 67);
  strncat(trans, letras, 26);strncat(trans, letrasM, 26);strncat(trans, car_especi, 5);strncat(trans, numeros, 10);
  nome = inserir_a(nome, -4, 5, trans);
  //q5
  nome = inserir_a(nome, 5, 5, trans);

  result = reconhecer(nome, token);

  if(result < 0){
    return 1;
  }else{
    return 0;
  }
}

int ano(char token[]){//automatos que reconhece ano
  struct vet *nome=NULL;
  char trans[67];
  int result;

  nome = inserir_v(nome, 0);
  nome = inserir_v(nome, 1);
  nome = inserir_v(nome, 2);
  nome = inserir_v(nome, 3);
  nome = inserir_v(nome, -4);
  nome = inserir_v(nome, 5);
  //q0
  nome = inserir_a(nome, 0, 1, numeros);
  memset(trans, 0 ,67);
  strncat(trans, letras, 26);strncat(trans, letrasM, 26);strncat(trans, car_especi, 5);
  nome = inserir_a(nome, 0, 5, trans);
  //q1
  nome = inserir_a(nome, 1, 2, numeros);
  nome = inserir_a(nome, 1, 5, trans);
  //q2
  nome = inserir_a(nome, 2, 3, numeros);
  nome = inserir_a(nome, 2, 5, trans);
  //q3
  nome = inserir_a(nome, 3, -4, numeros);
  nome = inserir_a(nome, 3, 5, trans);
  //q4
  strncat(trans, numeros, 10);
  nome = inserir_a(nome, -4, 5, trans);
  //q5
  nome = inserir_a(nome, 5, 5, trans);

  result = reconhecer(nome, token);

  if(result < 0){
    return 1;
  }else{
    return 0;
  }
}

int palavra(char token[]){//automato que reconhece palavras
  struct vet *nome=NULL;
  char trans[67];
  int result;

  nome = inserir_v(nome, 0);
  nome = inserir_v(nome, -1);
  nome = inserir_v(nome, 2);
  //q0
  memset(trans, 0 ,67);
  strncat(trans, letras, 26);strncat(trans, letrasM, 26);strncat(trans, car_especi, 5);
  nome = inserir_a(nome, 0, -1, trans);
  memset(trans, 0 ,67);
  strncat(trans, numeros, 10);
  nome = inserir_a(nome, 0, 2, trans);
  //q1
  memset(trans, 0, 67);
  strncat(trans, letras, 26);strncat(trans, letrasM, 26);strncat(trans, car_especi, 5);
  nome = inserir_a(nome, -1, -1, trans);
  memset(trans, 0, 67);
  strncat(trans, numeros, 10);
  nome = inserir_a(nome, -1, 2, trans);
  //q2
  memset(trans, 0, 67);
  strncat(trans, letras, 26);strncat(trans, letrasM, 26);strncat(trans, car_especi, 5);strncat(trans, numeros, 10);
  nome = inserir_a(nome, 2, 2, trans);

  result = reconhecer(nome, token);

  if(result < 0){
    return 1;
  }else{
    return 0;
  }
}

int mes(char token[]){//verifica o mês

  if(strcmp(token, "janeiro") == 0){
    return 1;
  }
  if(strcmp(token, "fevereiro") == 0){
    return 1;
  }
  if(strcmp(token, "marco") == 0){
    return 1;
  }
  if (strcmp(token, "abril") == 0) {
    return 1;
  }
  if (strcmp(token, "maio") == 0) {
    return 1;
  }
  if (strcmp(token, "junho") == 0) {
    return 1;
  }
  if (strcmp(token, "julho") == 0) {
    return 1;
  }
  if (strcmp(token, "agosto") == 0) {
    return 1;
  }
  if (strcmp(token, "setembro") == 0) {
    return 1;
  }
  if (strcmp(token, "outubro") == 0) {
    return 1;
  }
  if (strcmp(token, "novembro") == 0) {
    return 1;
  }
  if (strcmp(token, "dezembro") == 0) {
    return 1;
  }

  return 0;
}

int palres(char token[]){// verifica se o token é uma palavra reservarda

  if(strcmp(token, "MEMORANDO") == 0){
    return 1;
  }
  if (strcmp(token, "no.") == 0) {
    return 2;
  }
  if (strcmp(token, "de") == 0) {
    return 3;
  }
  if (strcmp(token, "De:") == 0) {
    return 4;
  }
  if (strcmp(token, "Para:") == 0) {
    return 5;
  }
  if (strcmp(token, "Assunto:") == 0) {
    return 6;
  }
  if (strcmp(token, "Atenciosamente.") == 0) {
    return 7;
  }

  return 0;
}

int checar(char str[]){// verifica os caracteres especiais Ex: / , OBS: nao é automato
  int i;
  char ch = str[0];

  for(i=0;i<5;i++){
    if(ch == car_especi[i]){
      return 1;
    }
  }

  return 0;
}

int protra(char token[]){//automato que reconhece pronomes de tratamento Ex: PR.
  struct vet *nome=NULL;
  char trans[67];
  int result;

  nome = inserir_v(nome, 0);
  nome = inserir_v(nome, 1);
  nome = inserir_v(nome, 2);
  nome = inserir_v(nome, -3);
  nome = inserir_v(nome, 4);
  //q0
  nome = inserir_a(nome, 0, 1, letrasM);
  memset(trans, 0, 67);
  strncat(trans, letras, 26);strncat(trans, numeros, 10);strncat(trans, car_especi, 5);
  nome = inserir_a(nome, 0, 4, trans);
  //q1
  nome = inserir_a(nome, 1, 2, letrasM);
  nome = inserir_a(nome, 1, 4, trans);
  //q2
  nome = inserir_a(nome, 2, -3, ".");
  memset(trans, 0, 67);
  strncat(trans, letras, 26);strncat(trans, numeros, 10);strncat(trans, letrasM, 26);strncat(trans, "-,:/", 4);
  nome = inserir_a(nome, 2, 4, trans);
  //q3
  memset(trans, 0, 67);
  strncat(trans, letras, 26);strncat(trans, numeros, 10);strncat(trans, letrasM, 26);strncat(trans, car_especi, 5);
  nome = inserir_a(nome, -3, 4, trans);
  //q4
  nome = inserir_a(nome, 4, 4, trans);

  result = reconhecer(nome, token);

  if(result < 0){
    return 1;
  }else{
    return 0;
  }
}

int sigla(char token[]){// automato que reconhece siglas Ex: RN
  struct vet *nome=NULL;
  char trans[67];
  int result;

  nome = inserir_v(nome, 0);
  nome = inserir_v(nome, 1);
  nome = inserir_v(nome, -2);
  nome = inserir_v(nome, 3);
  //q0
  nome = inserir_a(nome, 0, 1, letrasM);
  memset(trans, 0, 67);
  strncat(trans, letras, 26);strncat(trans, numeros, 10);strncat(trans, car_especi, 5);
  nome = inserir_a(nome, 0, 3, trans);
  //q1
  nome = inserir_a(nome, 1, -2, letrasM);
  nome = inserir_a(nome, 1, 3, trans);
  //q2
  strncat(trans, letrasM, 26);
  nome = inserir_a(nome, -2, 3, trans);
  //q3
  nome = inserir_a(nome, 3, 3, trans);

  result = reconhecer(nome, token);

  if(result < 0){
    return 1;
  }else{
    return 0;
  }
}
//fim_dos automatos reconhecedores

//funcoes de tratamento de exibição de erros, tabela dinamica e criação da tabela dianamica
struct tab_dina *tabela=NULL;//ponteiro global para a tabela dinamica

void add(char token[], char estado[], int lin, char estsint[20]){//adiciona a tabela dinamica um novo token
  //foi ultilizado a estrutura de lista simplesmente encadeada

  struct tab_dina *novo=NULL;//ponteiro para estrutura
  struct tab_dina *p; //ponteiro para encontra o final da lista

  //inserindo valores nos respecitivos campos
  novo = (struct tab_dina*)malloc(sizeof(struct tab_dina));
  novo->linha = lin;//linha do token
  memset(novo->token, 0, 50);
  strncat(novo->token, token, strlen(token));//token
  memset(novo->ana_lexica, 0, 20);
  strncat(novo->ana_lexica, estado, strlen(estado));//estado lexico
  memset(novo->ana_sintatica, 0, 20);
  strncat(novo->ana_sintatica, estsint, strlen(estsint));//estado sintatico
  novo->prox = NULL;

  if(tabela == NULL){//caso primeiro elemento da lista
    tabela = novo;
  }else{
    p = tabela;
    while(p->prox != NULL){//encontrando ultimo elemento de lista
      p = p->prox;
    }

    p->prox = novo;
  }
}

FILE *rep;//ponteiro global para o arquivo de erros;

void criaraqrep(){//criar o arquivo de exibição de erros
  rep = fopen("reperro.txt", "w");
}

void reperro(char tk[], int lin, int tip){//exibir no arquivo .txt os erros encontrados
  FILE *rep;
  rep = fopen("reperro.txt", "a");//abrir o arquivo

  switch (tip) { //casos de erros
    case 1:
      fprintf(rep, "Erro lexico na linha(%i) no token(%s): Caractere não reconhecido\n", lin, tk);
      break;
    case 2:
      fprintf(rep, "Erro lexico na linha(%i) no token(%s): Token não foi reconhecido\n", lin, tk);
      break;
    case 3:
      fprintf(rep, "Erro sintatico na linha(%i) no token(%s): Token não era o esperado\n", lin, tk);
      break;
    case 4:
      fprintf(rep, "Erro sintatico na linha(%i) É necessario uma quebra de linha\n", lin);
      break;
    case 5:
      fprintf(rep, "Erro semantico na linha(%i) Fevereiro nao possui dia (30, 31)\n", lin);
      break;
    case 6:
      fprintf(rep, "Erro semantico nas linhas(%i): Rementente e destinatarios iguais\n", lin);
      break;
    case 7:
      fprintf(rep, "Erro semantico na linha(%i) no token (%s) Ano diferente do atual\n", lin, tk);
      break;
  }

  return;
}

char * vertoken(char str[]){ //testa o token em todos os automatos e retorna o primeiro que reconhecer
  char *est = (char*)calloc(20, sizeof(char));

  if(nome(str) == 1){
    est = "nome";
    return est;
  }
  if(palres(str) >= 1){
    est = "p.reservada";
    return est;
  }
  if(numero(str) == 1){
    est = "numero";
    return est;
  }
  if(sigla(str) == 1){
    est = "sigla";
    return est;
  }
  if(checar(str) == 1){
    est = "car.especial";
    return est;
  }
  if(dia(str) == 1){
    est = "dia";
    return est;
  }
  if(mes(str) == 1){
    est = "mes";
    return est;
  }
  if(ano(str) == 1){
    est = "ano";
    return est;
  }
  if(protra(str) == 1){
    est = "pr.tratamento";
    return est;
  }
  if(palavra(str) == 1){
    est = "palavra";
    return est;
  }
  est = "erro";

  return est;
}

void tabelaw(void){//criar o arquivo .txt da tabela dinamica
  FILE *tab;
  tab = fopen("tabela.txt", "w");
  struct tab_dina *p = tabela;

  fprintf(tab, "linha |token | lexico |sintatico \n");

  while(p != NULL){
    fprintf(tab, "%i |", p->linha);
    fprintf(tab, "%s |", p->token);
    fprintf(tab, "%s |", p->ana_lexica);
    fprintf(tab, "%s |", p->ana_sintatica);
    fprintf(tab, "\n");

    p = p->prox;
  }

  close(tab);
}
//fim_funcoes de tratamento de exibição de erros, tabela dinamica e criação da tabela dianamica

//declaraçao de funçoes sintaticas
void ana_sinta(char tk[50], int lin, char ult, int dc_erro);
void dia_fev();
void de_para();
void anoatual();
//fim_declaraçao de funçoes sintaticas

void criar_tab(FILE *memo){//coleta os token do arquivo
  char ch; //variavel que recebe car do arquivo
  char tokarq[50]; // token coletado
  char afbcom[68];//alfabeto completo
  char *est; //estado do token
  strncat(afbcom, letras, 26);strncat(afbcom, letrasM, 26);strncat(afbcom, numeros, 10);strncat(afbcom, car_especi, 5);
  int decerro=0; //determina erro de caracteres nao reconhecidos
  int i=0, j=0;//variaveis de controle
  int linha=1; //indetificado de linha

  criaraqrep();//criando arquivo de menssagems de erros

  memset(tokarq, 0, 50);
  ch = fgetc(memo);
  while(ch != EOF){//EOF endica o final do documento
    i = 0;
    while(i < 68){
      if(ch == afbcom[i]){//verifia se o caractere existi no alfabeto
        break;
      }
      i++;
    }

    if(i == 68 && ch != ' ' && ch != '\n'){//caractere nao foi reconchecido
      decerro = 1;
    }

    //separção de tokens
    if(ch == ' '){//se espaço
      ana_sinta(tokarq, linha, ch, decerro);
      j = 0;//restaurar para posiçao inicialdo vetor de token
      decerro=0;//restaurar valor
      memset(tokarq, 0, 50);
    }else if(ch == '\n'){//se quebra de linha
      ana_sinta(tokarq, linha, ch, decerro);
      memset(tokarq, 0, 50);
      j = 0;
      decerro = 0;
      linha++;//contar linha
    }else{
      tokarq[j] = ch;
      j++;
    }
    ch = fgetc(memo);
  }
  //fim_separção de tokens
  //funcoes de analise de semantica
  dia_fev();
  de_para();
  anoatual();

  close(rep);
  tabelaw();
}

//comando de controle da fase sintatica
int ctrgra=1; //cariavel de controle da gramatica

/*
  separamos as partes do arquivo em 4 para melhorar a compreensão inicio, info(informçoes), mens(menssagem)
  e fim
*/

void inicio(char tk[50], int lin, char ult){ //parte inicial do memorando
  int erro;
  char *est;

  //nome completo
  if(ctrgra == 1){
    if(ult != '\n'){// se ultimo elemento visto não for uma quebra de linha
      erro = nome(tk); //verifica de token é o esperado pela gramtica
      if(erro == 0){ // se não é o esperado
        est = vertoken(tk); //verifique se é reconhecido por algum automato
        if(strcmp(est, "erro") == 0){ //nao foi reconhecido por nem um
          reperro(tk, lin, 2); //reporta o erro lexico
        }
        add(tk, est, lin, "erro"); //adiciona token a tabela com estado lexico e erro no estado sintatico
        reperro(tk, lin, 3); //reporta o erro sintatico
      }else{
        add(tk, "nome", lin, " ");// adiciona sem erro na tabela
      }
    }else if(ult == '\n'){// se igual a \n reconheça o token e avançe na gramatica
      erro = nome(tk);
      if(erro == 0){
        est = vertoken(tk);
        if(strcmp(est, "erro") == 0){
          reperro(tk, lin, 2);
        }
        add(tk, est, lin, "erro");
        reperro(tk, lin, 3);
      }else{
        add(tk, "nome", lin, " ");
      }
      ctrgra++;// atualiza o estado da gramatica
    }
    return;
  }
  //MEMORANDO
  if(ctrgra == 2){
    erro = palres(tk);
    if(erro != 1){
      est = vertoken(tk);
      if(strcmp(est, "erro") == 0){
        reperro(tk, lin, 2);
      }
      add(tk, est, lin, "erro");
      reperro(tk, lin, 3);
    }else{
      add(tk, "p.reservada", lin, " ");
    }
    ctrgra++;
    return;
  }
  //no.
  if(ctrgra == 3){
    erro = palres(tk);
    if(erro != 2){
      est = vertoken(tk);
      if(strcmp(est, "erro") == 0){
        reperro(tk, lin, 2);
      }
      add(tk, est, lin, "erro");
      reperro(tk, lin, 3);
    }else{
      add(tk, "p.reservada", lin, " ");
    }
    ctrgra++;
    return;
  }
  //numero
  if(ctrgra == 4){
    erro = numero(tk);
    if(erro == 0){
      est = vertoken(tk);
      if(strcmp(est, "erro") == 0){
        reperro(tk, lin, 2);
      }
      add(tk, est, lin, "erro");
      reperro(tk, lin, 3);
    }else{
      add(tk, "numero", lin, " ");
    }
    ctrgra++;
    return;
  }
  //nome
  if(ctrgra == 5){
    erro = nome(tk);
    if(erro == 0){
      est = vertoken(tk);
      if(strcmp(est, "erro") == 0){
        reperro(tk, lin, 2);
      }
      add(tk, est, lin, "erro");
      reperro(tk, lin, 3);
    }else{
      add(tk, "nome", lin, " ");
    }
    ctrgra++;
    return;
  }
  // /
  if(ctrgra == 6){
    if(strcmp(tk, "/") != 0){
      est = vertoken(tk);
      if(strcmp(est, "erro") == 0){
        reperro(tk, lin, 2);
      }
      add(tk, est, lin, "erro");
      reperro(tk, lin, 3);
    }else{
      add(tk, "car.especial", lin, " ");
    }
    ctrgra++;
    return;
  }
  //sigla
  if(ctrgra == 7){
    erro = sigla(tk);
    if(erro == 0){
      est = vertoken(tk);
      if(strcmp(est, "erro") == 0){
        reperro(tk, lin, 2);
      }
      add(tk, est, lin, "erro");
      reperro(tk, lin, 3);
    }else{
      add(tk, "sigla", lin, " ");
    }
    ctrgra++;
    return;
  }
  // ,
  if(ctrgra == 8){
    if(strcmp(tk, ",") != 0){
      est = vertoken(tk);
      if(strcmp(est, "erro") == 0){
        reperro(tk, lin, 2);
      }
      add(tk, est, lin, "erro");
      reperro(tk, lin, 3);
    }else{
      add(tk, "car.especial", lin, " ");
    }
    ctrgra++;
    return;
  }
  // dia
  if(ctrgra == 9){
    erro = dia(tk);
    if(erro == 0){
      est = vertoken(tk);
      if(strcmp(est, "erro") == 0){
        reperro(tk, lin, 2);
      }
      add(tk, est, lin, "erro");
      reperro(tk, lin, 3);
    }else{
      add(tk, "dia", lin, " ");
    }
    ctrgra++;
    return;
  }
  //de
  if(ctrgra == 10){
    erro = palres(tk);
    if(erro != 3){
      est = vertoken(tk);
      if(strcmp(est, "erro") == 0){
        reperro(tk, lin, 2);
      }
      add(tk, est, lin, "erro");
      reperro(tk, lin, 3);
    }else{
      add(tk, "p.reservada", lin, " ");
    }
    ctrgra++;
    return;
  }
  //mes
  if(ctrgra == 11){
    erro = mes(tk);
    if(erro == 0){
      est = vertoken(tk);
      if(strcmp(est, "erro") == 0){
        reperro(tk, lin, 2);
      }
      add(tk, est, lin, "erro");
      reperro(tk, lin, 3);
    }else{
      add(tk, "mes", lin, " ");
    }
    ctrgra++;
    return;
  }
  //de
  if(ctrgra == 12){
    erro = palres(tk);
    if(erro != 3){
      est = vertoken(tk);
      if(strcmp(est, "erro") == 0){
        reperro(tk, lin, 2);
      }
      add(tk, est, lin, "erro");
      reperro(tk, lin, 3);
    }else{
      add(tk, "p.reservada", lin, " ");
    }
    ctrgra++;
    return;
  }
  //ano
  if(ctrgra == 13){
    erro = ano(tk);
    if(erro == 0){
      est = vertoken(tk);
      if(strcmp(est, "erro") == 0){
        reperro(tk, lin, 2);
      }
      add(tk, est, lin, "erro");
      reperro(tk, lin, 3);
    }else{
      add(tk, "ano", lin, " ");
    }
    ctrgra++;
    return;
  }
  // quebra de linha
  if(strlen(tk) == 0 && ctrgra == 14){
    if(ult == '\n'){
      // void
    }else{
      reperro(tk, lin, 4);
    }
    ctrgra++;
    return;
  }
}

void info(char tk[50], int lin, char ult){// parte informativa
  int erro;
  char *est;

  //de:
  if(ctrgra == 15){
    erro = palres(tk);
    if(erro != 4){
      est = vertoken(tk);
      if(strcmp(est, "erro") == 0){
        reperro(tk, lin, 2);
      }
      add(tk, est, lin, "erro");
      reperro(tk, lin, 3);
    }else{
      add(tk, "p.reservada", lin, " ");
    }
    ctrgra++;
    return;
  }
  // nomecom
  if(ctrgra == 16){
    if(ult != '\n'){
      erro = nome(tk);
      if(erro == 0){
        est = vertoken(tk);
        if(strcmp(est, "erro") == 0){
          reperro(tk, lin, 2);
        }
        add(tk, est, lin, "erro");
        reperro(tk, lin, 3);
      }else{
        add(tk, "nome", lin, " ");
      }
    }else if(ult == '\n'){
      erro = nome(tk);
      if(erro == 0){
        est = vertoken(tk);
        if(strcmp(est, "erro") == 0){
          reperro(tk, lin, 2);
        }
        add(tk, est, lin, "erro");
        reperro(tk, lin, 3);
      }else{
        add(tk, "nome", lin, " ");
      }
      ctrgra++;
    }
    return;
  }
  // para:
  if(ctrgra == 17){
    erro = palres(tk);
    if(erro != 5){
      est = vertoken(tk);
      if(strcmp(est, "erro") == 0){
        reperro(tk, lin, 2);
      }
      add(tk, est, lin, "erro");
      reperro(tk, lin, 3);
    }else{
      add(tk, "P.reservada", lin, " ");
    }
    ctrgra++;
    return;
  }
    // nomecom
    if(ctrgra == 18){
      if(strcmp(tk, "/") != 0){
        erro = nome(tk);
        if(erro == 0){
          est = vertoken(tk);
          if(strcmp(est, "erro") == 0){
            reperro(tk, lin, 2);
          }
          add(tk, est, lin, "erro");
          reperro(tk, lin, 3);
        }else{
          add(tk, "nome", lin, " ");
        }
      }else if(strcmp(tk, "/") == 0){
        ctrgra++;
        info(tk, lin, ult);
        return;
      }
    }
      // /
      if(ctrgra == 19){
        if(strcmp(tk, "/") != 0){
          est = vertoken(tk);
          if(strcmp(est, "erro") == 0){
            reperro(tk, lin, 2);
          }
          add(tk, est, lin, "erro");
          reperro(tk, lin, 3);
        }else{
          add(tk, "car.especial", lin, " ");
        }
        ctrgra++;
        return;
      }
      // nomecom
      if(ctrgra == 20){
        if(ult != '\n'){
          erro = nome(tk);
          if(erro == 0){
            est = vertoken(tk);
            if(strcmp(est, "erro") == 0){
              reperro(tk, lin, 2);
            }
            add(tk, est, lin, "erro");
            reperro(tk, lin, 3);
          }else{
            add(tk, "nome", lin, " ");
          }
        }else if(ult == '\n'){
          erro = nome(tk);
          if(erro == 0){
            est = vertoken(tk);
            if(strcmp(est, "erro") == 0){
              reperro(tk, lin, 2);
            }
            add(tk, est, lin, "erro");
            reperro(tk, lin, 3);
          }else{
            add(tk, "nome", lin, " ");
          }
          ctrgra++;
        }
        return;
      }
      // resumo:
      if(ctrgra == 21){
        erro = palres(tk);
        if(erro != 6){
          est = vertoken(tk);
          if(strcmp(est, "erro") == 0){
            reperro(tk, lin, 2);
          }
          add(tk, est, lin, "erro");
          reperro(tk, lin, 3);
        }else{
          add(tk, "p.reservada", lin, " ");
        }
        ctrgra++;
        return;
      }
      // texto
      if(ctrgra == 22){
        if(ult != '\n'){
          erro = palavra(tk);
          if(erro == 0){
            est = vertoken(tk);
            if(strcmp(est, "erro") == 0){
              reperro(tk, lin, 2);
            }
            add(tk, est, lin, "erro");
            reperro(tk, lin, 3);
          }else{
            add(tk, "palavra", lin, " ");
          }
        }else if(ult == '\n'){
          erro = palavra(tk);
          if(erro == 0){
            est = vertoken(tk);
            if(strcmp(est, "erro") == 0){
              reperro(tk, lin, 2);
            }
            add(tk, est, lin, "erro");
            reperro(tk, lin, 3);
          }else{
            add(tk, "palavra", lin, " ");
          }
          ctrgra++;
        }
        return;
      }
      // quebra de linha
      if(ctrgra == 23){
        if(strlen(tk) == 0 && ult == '\n'){
          // void
        }else{
          reperro(tk, lin, 4);
        }
        ctrgra++;
        return;
      }
}

void mens(char tk[50], int lin, char ult){// parte da menssagem
  int erro;
  char *est;

  //pronome de tratamento
  if(ctrgra == 24){
    erro = protra(tk);
    if(erro == 0){
      est = vertoken(tk);
      if(strcmp(est, "erro") == 0){
        reperro(tk, lin, 2);
      }
      add(tk, est, lin, "erro");
      reperro(tk, lin, 3);
    }else{
      add(tk, "pro.tratamento", lin, " ");
    }
    ctrgra++;
    return;
  }
  // nome
  if(ctrgra == 25){
    erro = nome(tk);
    if(erro == 0){
      est = vertoken(tk);
      if(strcmp(est, "erro") == 0){
        reperro(tk, lin, 2);
      }
      add(tk, est, lin, "erro");
      reperro(tk, lin, 3);
    }else{
      add(tk, "nome", lin, " ");
    }
    ctrgra++;
    return;
  }
  // menssagem
  if(ctrgra == 26){
    if(strlen(tk) != 0){
      erro = palavra(tk);
      if(erro == 0){
        est = vertoken(tk);
        if(strcmp(est, "erro") == 0){
          reperro(tk, lin, 2);
        }
        add(tk, est, lin, "erro");
        reperro(tk, lin, 3);
      }else{
        add(tk, "palavra", lin, " ");
      }
    }else if(strlen(tk) == 0 && ult == '\n'){
      ctrgra++;
      mens(tk, lin, ult);
      return;
    }
  }
  // quebra de linha
  if(ctrgra == 27){
    if(strlen(tk) == 0 && ult == '\n'){
      // void
    }else{
      reperro(tk, lin, 4);
    }
    ctrgra++;
    return;
  }
  // atenciosamente,
  if(ctrgra == 28){
    erro = palres(tk);
    if(erro != 7){
      est = vertoken(tk);
      if(strcmp(est, "erro") == 0){
        reperro(tk, lin, 2);
      }
      add(tk, est, lin, "erro");
      reperro(tk, lin, 3);
    }else{
      add(tk, "p.reservada", lin, " ");
    }
    ctrgra++;
    return;
  }
  // quebra de linha
  if(ctrgra == 29){
    if(strlen(tk) == 0 && ult == '\n'){
      // void
    }else{
      reperro(tk, lin, 4);
    }
    ctrgra++;
    return;
  }
}

void fim(char tk[50], int lin, char ult){// parte final
  int erro;
  char *est;

  // nomecom
  if(ctrgra == 30){
    if(strcmp(tk, "/") != 0){
      erro = nome(tk);
      if(erro == 0){
        est = vertoken(tk);
        if(strcmp(est, "erro") == 0){
          reperro(tk, lin, 2);
        }
        add(tk, est, lin, "erro");
        reperro(tk, lin, 3);
      }else{
        add(tk, "nome", lin, " ");
      }
    }else if(strcmp(tk, "/") == 0){
      ctrgra++;
      fim(tk, lin, ult);
      return;
    }
  }
  // /
  if(ctrgra == 31){
    if(strcmp(tk, "/") != 0){
      est = vertoken(tk);
      if(strcmp(est, "erro") == 0){
        reperro(tk, lin, 2);
      }
      add(tk, est, lin, "erro");
      reperro(tk, lin, 3);
    }else{
      add(tk, "car.especial", lin, " ");
    }
    ctrgra++;
    return;
  }
  // nomecom
  if(ctrgra == 32){
    if(ult != '\n'){
      erro = nome(tk);
      if(erro == 0){
        est = vertoken(tk);
        if(strcmp(est, "erro") == 0){
          reperro(tk, lin, 2);
        }
        add(tk, est, lin, "erro");
        reperro(tk, lin, 3);
      }else{
        add(tk, "nome", lin, " ");
      }
    }else if(ult == '\n'){
      erro = nome(tk);
      if(erro == 0){
        est = vertoken(tk);
        if(strcmp(est, "erro") == 0){
          reperro(tk, lin, 2);
        }
        add(tk, est, lin, "erro");
        reperro(tk, lin, 3);
      }else{
        add(tk, "nome", lin, " ");
      }
      ctrgra++;
    }
    return;
  }

}

void ana_sinta(char tk[50], int lin, char ult, int dc_erro){ //controle da analise sintatica

  if(dc_erro == 1){ //se alguma caractere não for reconhecido
    reperro(tk, lin, 1);
  }

  if(strcmp(tk, " ") == 0){// descartar espaços
    return;
  }

  if(ctrgra <= 14){//controla o estado da gramtica
    inicio(tk, lin, ult);
  }else if(ctrgra > 14 && ctrgra <= 23){
    info(tk, lin, ult);
  }else if(ctrgra > 23 && ctrgra <= 29){
    mens(tk, lin, ult);
  }else if(ctrgra > 29 && ctrgra <= 32){
    fim(tk, lin, ult);
  }else{
    reperro(tk, lin, 2);
  }
}
//fim_comando de controle da fase sintatica

//analise de semantica
void dia_fev(){ //verifica erro dos dias 30 e 31 de fevereiro
  struct tab_dina *b=tabela; //buscar
  struct tab_dina *dia, *mes; // guarda os dados

  while(b != 0){
    if(strcmp(b->ana_lexica, "dia") == 0){
      dia = b;
    }
    if(strcmp(b->ana_lexica, "mes") == 0){
      mes = b;
      break;
    }
    b = b->prox;
  }

  if(dia == NULL || mes == NULL){//caso a ja erros ana parte semantica ou sintatica
    return;
  }

  if(strcmp(mes->token, "fevereiro") == 0){
    if(strcmp(dia->token, "30") == 0){
      reperro(dia->token, dia->linha, 5);
    }
    if(strcmp(dia->token, "31") == 0){
      reperro(dia->token, dia->linha, 8);
    }
  }
}

void de_para(){// verfica erro do remetente igual a destinatario
  struct tab_dina *b=tabela; //buscar;
  struct tab_dina *de, *para;
  char nomep[100]; memset(nomep, 0 , 100);//Para
  char nomed[100]; memset(nomed, 0, 100);//de

  while(b != NULL){//buscando o nome do destinatario
    if(strcmp(b->ana_lexica, "P.reservada") == 0 && strcmp(b->token, "Para:") == 0){
      while(strcmp(b->token, "/") != 0){
        b = b->prox;
      }
      b = b->prox->prox;
      while(strcmp(b->token, "Assunto:") != 0){//coletando o nome do destinatario
        strncat(nomep, b->token, strlen(b->token));
        b = b->prox;
      }
      para = b;
      break;
    }
    b = b->prox;
  }

  b = tabela;//apontando b para o começo da tabela

  while(b != NULL){//buscando o nome do fonecedor
    if(strcmp(b->token, "Atenciosamente.") == 0){

      b = b->prox;
      while(strcmp(b->token, "/") != 0){//coletando nome do remetente
        strncat(nomed, b->token, strlen(b->token));
        b = b->prox;
      }
      de = b;
      break;
    }
    b = b->prox;
  }

  if(de == NULL || para == NULL){
    return;
  }

  if(strcmp(nomed, nomep) == 0){
    reperro(de->token, b->linha, 6);
  }
}

void anoatual(){//verifica erro do ano diferente do atual
  struct tab_dina *b=tabela;//buscar
  char anoc[5]; //ano em char;
  time_t data_tempo;
  int ano; //guarda o ano atual

  //coletando ano atual
  time(&data_tempo);
  struct tm *data = localtime(&data_tempo);
  ano = data->tm_year + 1900;

  while(b != NULL){//buscando o token ano
    if(strcmp(b->ana_lexica, "ano") == 0){
      break;
    }
    b = b->prox;
  }

  if(b == NULL){
    return;
  }

  sprintf(anoc, "%i", ano);

  if(strcmp(anoc, b->token) != 0){
    reperro(b->token, b->linha, 7);
  }

}
//fim_analise de semantica
