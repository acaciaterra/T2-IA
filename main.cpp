/*
    Alunos: Acácia dos Campos da Terra e João Pedro Winckler Bernardi
    Professor: José Carlos Bins Filho
    Disciplina: Inteligência Artificial
    Descrição: Blbalbala
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX 1000
#define calcerror(x, y) ((x[0] != y[0]) + (x[1] != y[1]))
#define getbitn(i) (bitnoise[i] + '0')

typedef pair <string, string> ss;

int err;
vector<int> bitin, bitcod, bitnoise, bitdec;

map<string, ss> cod, prox;

void init(){
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
    for (i = 0; scanf("%c", &tmp) != EOF; i++)
        if (tmp != ' ' && tmp != '\n')
            bitin.push_back((tmp - '0'));
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
    // printf("indices: %d  || tam: %d | qtderr: %d\n", int(indices.size()), int(bitcod.size()), qtderr);
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

string menorError(int verror[]){
    int i, menor = 0; char ret = '0';
    for (i = 0; i < 4; i++)
        if (verror[i] < verror[menor] ||
           (verror[i] == verror[menor] && (rand() % 2))) {
            ret = ((i & 1) + '0');
            menor = i;
        }
    // printf("UEPAAA\n");
    // printf("%c\n", ret);
    string tmp = ""; tmp += ret;
    return tmp;
}

void decodifica() {
    int i, error0, error1;
    int error00, error01, error10, error11;
    int _error00, _error01, _error10, _error11;
    string dec = "", par = "";

    //Primeiro passo
    par = getbitn(0); par += getbitn(1);
    error0 = calcerror(par, "00"); error1 = calcerror(par, "11");
    dec += error0 < error1 ? '0' : '1';
    //printf("original: %s\ner0: %d\ner1: %d\n", par.c_str(), error0, error1);
    // cout << ">dec: " << dec << endl;
    //Segundo passo
    par = getbitn(2); par += getbitn(3);
    error00 = calcerror(par, "00") + error0;
    error10 = calcerror(par, "11") + error0;
    error01 = calcerror(par, "10") + error1;
    error11 = calcerror(par, "01") + error1;
    int verror[] = {error00, error10, error01, error11};
    dec += menorError(verror);
    // cout << ">dec: " << dec << endl;
    // printf(">dec: %s", dec.c_str());

    for (i = 4; i < (int) bitnoise.size(); i += 2) {
        par = getbitn(i); par += getbitn(i + 1);
        _error00 = min(calcerror(par, "00") + error00, calcerror(par, "11") + error01);
        _error10 = min(calcerror(par, "11") + error00, calcerror(par, "00") + error01);
        _error01 = min(calcerror(par, "10") + error10, calcerror(par, "01") + error11);
        _error11 = min(calcerror(par, "01") + error10, calcerror(par, "10") + error11);
        verror[0] = error00; verror[1] = error10; verror[2] = error01; verror[3] = error11;
        dec += menorError(verror);
        // cout << ">dec: " << dec << endl;
        error00 = _error00; error01 = _error01; error10 = _error10; error11 = _error11;
    }
    // printf("\ndec: %s\n", dec.c_str());
    for (i = 0; i < (int)dec.size() - 2; i++) bitdec.push_back(dec[i] - '0');
}

void debbug() {
    printf("Entrada:\n");
    for (auto& b: bitin) printf("[%d]", b);
    printf("\n\n");
    printf("Cod\n");
    for (auto& i: cod) {
        printf("%s: (%s | %s)\n", i.first.c_str(), i.second.first.c_str(), i.second.second.c_str());
    }
    printf("\nProx\n");
    for (auto& i: prox) {
        printf("%s: (%s | %s)\n", i.first.c_str(), i.second.first.c_str(), i.second.second.c_str());
    }
    printf("\nCodificado:");
    for (auto& b: bitcod) printf("[%d]", b);
    printf("\n");
    printf("\nRuido:     ");
    for (auto& b: bitnoise) printf("[%d]", b);
    printf("\n");
    printf("\nDecod:     ");
    for (auto& b: bitdec) printf("[%d]", b);
    printf("\n");
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
