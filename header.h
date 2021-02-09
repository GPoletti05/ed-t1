#ifndef _H_HEADER
#define _H_HEADER

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct{ // struct responsavel por guardar as informacoes do geo e qry.
    float r, x, y, w, h;
    int k, j;
    char com[5], corb[20], corp[20], txto[50];
}comandos; 

void parametros(char* arq_entrada_geo, char* path_entrada, char* arq_entrada_qry, char* path_saida,  char* entrada, char* arq_geo, char* arq_qry, char* entrada_qry, char* saida); //verifica os parametros de entrada do terminal e converte para os caminhos certos para abrir o geo, qry e pasta de entrada.

comandos *arquivo_geo(char* arq_geo, char* entrada, char* saida, int* num_lin, int*com_lin); // coloca as informacoes do geo na string e executa o .svg do geo.

comandos *arquivo_qry(char* arq_qry, char* arq_geo, char* entrada_qry, char* saida_txt, char* saida, int num_lin, int com_lin, int* tam_qry, int* com_qry, char* entrada, comandos *forma); //caso haja um arquivo qry, modifica as informacoes na string e prepara para a nova saida -q.svg, alem disso ja executa o arquivo .txt do qry.

void arquivos_saida(char* arq_geo, char* saida_svg, char* arq_qry, char* entrada, char* saida, int num_lin, int com_lin, int tam_qry, int com_qry, comandos *qry); //responsavel pela saida -q.svg, caso haja o arquivo qry.

#endif