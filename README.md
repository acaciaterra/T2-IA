# T2-IA
Trabalho de Inteligêncial Artificial

###### Alunos
  * Acácia dos Campos da Terra
  * João Pedro Winckler bernardi

###### Professor
  * José Carlos Bins Filho

# Descrição
  O trabalho consiste de um programa que dada um valor x e uma sequência de bits, codifica-se essa sequência, aplica-se ruído a codificação(alterando x% bits) e, por fim, realiza-se a decodificação da sequência codificada com ruído através do algoritmo de Viterbi.
  O algoritmo de Viterbi foi implementado através de uma matriz de estados e programação dinâmica.

# Compilação
  O programa pode ser compilado através do comando "make" no terminal ou pelo comando "g++ main.cpp -std=c++11 -Wall -O2".

# Execução
  ./'nome do programa' ou ./'nome do programa' < 'Arquivo de entrada'
  * Nome do programa, se compilado com o Makefile, é 'viterbi'

# Entrada
  A entrada consiste de um inteiro de 0 a 100 e uma sequência de bits.

# Saída
  A saída mostrará a sequência de bits informada, a sequência codificada, a sequência com o ruído aplicado, a sequência decodificada e a quantidade de bits errados quando comparamos a entrada e a sequência decodificada.
