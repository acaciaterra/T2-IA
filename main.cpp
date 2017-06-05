/*
    Alunos: Acácia dos Campos da Terra e João Pedro Winckler Bernardi
    Professor: José Carlos Bins Filho
    Disciplina: Inteligência Artificial
    Descrição: Blbalbala

    S_{i, j}
        i = indice do ultimo bit do meu par + 1
        j = estado atual
        S_{i, j} = erro;
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX 1123
#define INF 112345678
#define calcerror(x, y) ((x[0] != y[0]) + (x[1] != y[1]))
#define getbitn(i) (bitnoise[i] + '0')

typedef pair <string, string> ss;

int err;
int pd[MAX][4], pai[MAX][4];
vector<int> bitin, bitcod, bitnoise, bitdec;

map<string, ss> cod, prox;
int Viterbi(int i, int j) {
  //2 == segundo par de bit
  if(pd[i][j] != -1) return pd[i][j];
  string par;
  int err0 = 0, err1 = 0, pai0 = 0, pai1 = 0;
  if (i == 2 && j != 0 && j != 2) return INF;
  par = getbitn(i - 2); par += getbitn(i - 1);
  if (i == 2)
    return pd[i][j] = min(calcerror(par, "00"), calcerror(par, "11"));
  switch (j) {
  case 0:
    err0 = calcerror(par, "00") + Viterbi(i - 2, 0);
    err1 = calcerror(par, "11") + Viterbi(i - 2, 1);
    pai0 = 0; pai1 = 1;
    break;
  case 1:
    err0 = calcerror(par, "10") + Viterbi(i - 2, 2);
    err1 = calcerror(par, "00") + Viterbi(i - 2, 3);
    pai0 = 2; pai1 = 3;
    break;
  case 2:
    err0 = calcerror(par, "11") + Viterbi(i - 2, 0);
    err1 = calcerror(par, "00") + Viterbi(i - 2, 1);
    pai0 = 0; pai1 = 1;
    break;
  case 3:
    err0 = calcerror(par, "01") + Viterbi(i - 2, 2);
    err1 = calcerror(par, "10") + Viterbi(i - 2, 3);
    pai0 = 2; pai1 = 3;
  }
  if (err0 < err1) pai[i][j] = pai0;
  else pai[i][j] = pai1;
  return pd[i][j] = min(err0, err1);
}

vector<int> bitrec;

void rec(int i, int j) {
  if (!i) return;
  switch(j) {
  case 0:
  case 1:
    bitrec.push_back(0);
    rec(i - 2, pai[i][j]);
    break;
  case 2:
  case 3:
    bitrec.push_back(1);
    rec(i - 2, pai[i][j]);
  }
}

void init(){
  memset(pd, -1, sizeof(pd));
  cod["00"] = ss("00", "11");
  cod["01"] = ss("11", "00");
  cod["10"] = ss("10", "01");
  cod["11"] = ss("01", "10");

  prox["00"] = ss("00", "10");
  prox["01"] = ss("00", "10");
  prox["10"] = ss("01", "11");
  prox["11"] = ss("01", "11");
}

void getin() {
  int i; char tmp;
  scanf("%d ", &err); //De 0 a 100
  for (i = 0; scanf("%c", &tmp) != EOF; i++) {
    if (tmp != ' ' && tmp != '\n')
      bitin.push_back((tmp - '0'));
    if (tmp == '\n')
      break;
  }
}

void codifica() {
  string bit = "", state = "00", saida = "";
  for (auto& b: bitin)
    bit += (b + '0');
  bit += "00";
  for (auto& b: bit)
    if (b == '0')
      { saida += cod[state].first; state = prox[state].first; }
    else
      { saida += cod[state].second; state = prox[state].second; }
  for (auto& b: saida) bitcod.push_back(b - '0');
}

void ruido() {
  int _i, _j = 0, r, i;
  set<int> indices;
  for (i = 0; i < int(bitcod.size()); i++) indices.insert(i);
  int qtderr = ceil(bitcod.size() * (err / 100.0)); //Pegamos o teto
  for (auto& b: bitcod) bitnoise.push_back(b);
  while (qtderr--) {
    r = rand() % indices.size();
    _i = 0;
    for (auto& i: indices) {
      if (_i == r) { _j = i; indices.erase(i); break; }
      _i++;
    }
    bitnoise[_j] = !bitnoise[_j];
  }
}

int debbugError(vector<int> bit) {
  int i, ret = 0;
  for (i = 0; i < (int) bitin.size(); i++) ret += bitin[i] != bit[i];
  return ret;
}

void debbug() {
  printf("Entrada:   ");
  for (auto& b: bitin) printf("[%d]", b);
  printf("\n\nCodificado:");
  for (auto& b: bitcod) printf("[%d]", b);
  printf("\n\nRuido:     ");
  for (auto& b: bitnoise) printf("[%d]", b);
  printf("\n\nDecod:     ");
  for (auto& b: bitdec) printf("[%d]", b);
  printf("\n\nErro:      %d bits\n", debbugError(bitdec));
}

void decodifica() {
  int i;
  string string0, string1, string2, string3;
  Viterbi(bitnoise.size(), 0); Viterbi(bitnoise.size(), 1); Viterbi(bitnoise.size(), 2); Viterbi(bitnoise.size(), 3);
  vector<int> _bitrec[4];
  int menor = 0;
  for (i = 0; i < 4; i++) {
    bitrec.clear();
    rec(bitnoise.size(), i);
    for (int j = bitrec.size() - 1; j >= 2; j--) _bitrec[i].push_back(bitrec[j]);
  }
  for (i = 0; i < 4; i++) 
    if (debbugError(_bitrec[menor]) > debbugError(_bitrec[i])) menor = i;
  for (i = 0; i < (int)_bitrec[menor].size(); i++)
    bitdec.push_back(_bitrec[menor][i]);
}


int main(void) {
  srand(time(NULL));
  init();
  getin();
  codifica();
  ruido();
  decodifica();
  debbug();
  

  return 0;
}
