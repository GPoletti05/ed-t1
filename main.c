#include"header.h"

int main(int argc, char *argv[]){
    int j = 1, num_lin = 0, com_lin, tam_qry = 0, com_qry = 0;
    char *arq_entrada_geo = NULL, *saida_svg = NULL, *saida_txt = NULL, *arq_entrada_qry = NULL, *path_entrada = NULL, *path_saida = NULL, *entrada = NULL, *arq_geo = NULL, *arq_qry = NULL, *entrada_qry = NULL, *saida = NULL;
    comandos *informacoes;

    while(j<argc){
        if (strcmp("-e",argv[j])==0){ 
            j++;
            path_entrada = (char *)malloc((strlen(argv[j])+1)*sizeof(char));
            strcpy(path_entrada,argv[j]);
        }

        else if (strcmp("-f",argv[j])==0){ 
            j++;
            arq_entrada_geo = (char *)malloc((strlen(argv[j])+1)*sizeof(char));
            saida_svg = (char *)malloc((strlen(argv[j])+1)*sizeof(char));
            saida_txt = (char *)malloc((strlen(argv[j])+1)*sizeof(char));
            strcpy(arq_entrada_geo,argv[j]);
            strcpy(saida_svg,arq_entrada_geo);
            strcpy(saida_txt,arq_entrada_geo);
        }

        else if (strcmp("-q",argv[j])==0){ 
            j++;
            arq_entrada_qry = (char *)malloc((strlen(argv[j])+1)*sizeof(char));
            strcpy(arq_entrada_qry,argv[j]);
        }

        else if (strcmp("-o", argv[j])==0){
            j++;
            path_saida = (char *)malloc((strlen(argv[j])+1)*sizeof(char));
            strcpy(path_saida, argv[j]);
        }

        j++;
    }

    if(arq_entrada_geo != NULL){ // aloca a memoria necessaria para cada variavel, possui algumas condicoes necessarias para a declaracao correta.
        arq_geo = (char *)malloc(strlen(arq_entrada_geo) * sizeof(char));
        if(path_entrada != NULL){
            entrada = (char *)malloc(strlen(arq_entrada_geo) + strlen(path_entrada) * sizeof(char));
            if(arq_entrada_qry != NULL){
                arq_qry = (char *)malloc(strlen(arq_entrada_qry) * sizeof(char));
                entrada_qry = (char *)malloc(strlen(arq_entrada_qry) + strlen(path_entrada) * sizeof(char));
            }
        }
        else if(path_entrada == NULL){
            entrada = (char *)malloc(strlen(arq_entrada_geo) * sizeof(char));
            if(arq_entrada_qry != NULL){
                arq_qry = (char *)malloc(strlen(arq_entrada_qry) * sizeof(char));
                entrada_qry = (char *)malloc(strlen(arq_entrada_qry) * sizeof(char));
            }
        }
        if(path_saida != NULL){
            saida = (char *)malloc(strlen(path_saida) * sizeof(char));
        }
        parametros(arq_entrada_geo, path_entrada, arq_entrada_qry, path_saida, entrada, arq_geo, arq_qry, entrada_qry, saida); // funcao responsavel por agrupar de forma certa os nomes de pasta de entrada, arquivo geo, qry e pasta de saida.

    }

    informacoes = arquivo_geo(arq_geo, entrada, saida, &num_lin, &com_lin); // retorna as informacoes da string, recebidas originalmente no arquivo .geo, e faz o arquivo .svg original.

    if(arq_entrada_qry != NULL){ // caso haja um arquivo .qry, guarda as informacoes modificadas na string e executa o arquivo .txt.
        informacoes = arquivo_qry(arq_qry, arq_geo, entrada_qry, saida_txt, saida, num_lin, com_lin, &tam_qry, &com_qry, entrada, informacoes);
        arquivos_saida(arq_geo, saida_svg, arq_qry, entrada, saida, num_lin, com_lin, tam_qry, com_qry, informacoes); // cria o arquivo -q.svg (svg modificado pelo qry).
        free(arq_qry);
        free(entrada_qry);
    }

    free(arq_entrada_geo);
    free(arq_geo);
    free(path_entrada);
    free(arq_entrada_qry);
    free(saida_txt);
    free(saida_svg);
    free(path_saida);
    free(informacoes);
    free(saida);
    free(entrada);

    return 0;
}