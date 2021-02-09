#include"header.h"

void parametros(char *arq_entrada_geo, char *path_entrada, char* arq_entrada_qry, char* path_saida, char* entrada, char* arq_geo, char* arq_qry, char* entrada_qry, char* saida){
    char *aux, *aux2, *aux_geo, *aux_qry;
    int i = 0, j = 0,val = 0, k = 0, val2 = 0, tam_arq_entrada_geo, tam_path_entrada, tam_saida, tam_aux, tam_arq_entrada_qry;

    if(path_entrada != NULL){  //caso haja um -e informado, executa as condicoes abaixo, para melhor "alocacao" das variaveis.

        tam_path_entrada = strlen(path_entrada);

        if(path_entrada[0] == '.'){
            if(path_entrada[1] == '/'){
                for(i=2; i < tam_path_entrada; i++){
                    entrada[i - 2] = path_entrada[i];
                }
            }
        }

        else{
            strcat(entrada, path_entrada);
        }

        if(entrada[tam_path_entrada - 1] != '/' && arq_entrada_geo[0] != '/'){
            strcat(entrada, "/");
        }

        if(arq_entrada_qry != NULL){
            tam_path_entrada = strlen(path_entrada);

            if(path_entrada[0] == '.'){
                if(path_entrada[1] == '/'){
                    for(i=2; i < tam_path_entrada; i++){
                        entrada_qry[i - 2] = path_entrada[i];
                    }
                }
            }

            else{
                strcat(entrada_qry, path_entrada);
            }

            if(entrada_qry[tam_path_entrada - 1] != '/' && arq_entrada_qry[0] != '/'){
                strcat(entrada_qry, "/");
            }
        }

        aux = (char *)malloc(strlen(arq_entrada_geo) * sizeof(char));

        tam_arq_entrada_geo = strlen(arq_entrada_geo);

        for(i = 0;i < tam_arq_entrada_geo; i++){
            if(arq_entrada_geo[i] == '/'){
                val++;
            }
        }

        for(i = 0;i < tam_arq_entrada_geo; i++){
            if(arq_entrada_geo[i] == '/'){
                aux[j] = arq_entrada_geo[i];
                j++;
                val2++;
            }
            else if(val2 == val){
                arq_geo[k] = arq_entrada_geo[i];
                k++;
                val2++;
            }
            else if(val2 < val ){
                aux[j] = arq_entrada_geo[i];
                j++;
            }
            else if(val2 > val){
                arq_geo[k] = arq_entrada_geo[i];
                k++;
            }
        }
        
        if(aux[0] == '.' && aux[1] == '/'){
            tam_aux = strlen(aux);
            aux_geo = (char *)malloc(strlen(aux) * sizeof(char));
            j = 0;
            for(i = 2;i < tam_aux; i++){
                aux_geo[j] = aux[i];
                j++;
            }
            if(entrada!=NULL){
                strcat(entrada, aux_geo);
                free(aux_geo);
            }
        }

        else{
            if(entrada!=NULL){
                strcat(entrada, aux);
                free(aux);
            }
        }
    }

    if(path_entrada == NULL){ ;// caso nao haja um -e, executa as condicoes abaixo, para melhor "alocacao" das variaveis.
        aux = (char *)malloc(strlen(arq_entrada_geo) * sizeof(char));

        tam_arq_entrada_geo = strlen(arq_entrada_geo);

        for(i = 0;i < tam_arq_entrada_geo; i++){
            if(arq_entrada_geo[i] == '/'){
                val++;
            }
        }

        for(i = 0;i < tam_arq_entrada_geo; i++){
            if(arq_entrada_geo[i] == '/'){
                aux[j] = arq_entrada_geo[i];
                j++;
                val2++;
            }
            else if(val2 == val){
                arq_geo[k] = arq_entrada_geo[i];
                k++;
                val2++;
            }
            else if(val2 < val ){
                aux[j] = arq_entrada_geo[i];
                j++;
            }
            else if(val2 > val){
                arq_geo[k] = arq_entrada_geo[i];
                k++;
            }
        }
        
        if(aux[0] == '.' && aux[1] == '/'){
            tam_aux = strlen(aux);
            aux_geo = (char *)malloc(strlen(aux) * sizeof(char));
            j = 0;
            for(i = 2;i < tam_aux; i++){
                aux_geo[j] = aux[i];
                j++;
            }
            strcat(entrada, aux_geo);
            free(aux_geo);
        }

        else{
            strcat(entrada, aux);
            free(aux);
        }
    }

    if(path_saida != NULL){

        tam_saida = strlen(path_saida);

        if(path_saida[0] == '.'){
            if(path_saida[1] == '/'){
                for(i=2; i < tam_saida; i++){
                    saida[i - 2] = path_saida[i];
                }
            }
        }

        else{
            strcat(saida, path_saida);
        }

        if(path_saida[tam_saida - 1] != '/'){
            strcat(saida, "/");
        }
    }

    if(arq_entrada_qry != NULL){

        val= 0;
        val2 = 0;
        j = 0;
        k = 0;

        if(path_entrada != NULL){
            if(path_entrada[0] == '.'){
                if(path_entrada[1] == '/'){
                    for(i=2; i < tam_path_entrada; i++){
                        entrada_qry[i - 2] = path_entrada[i];
                    }
                }
            }

            if(entrada_qry[tam_path_entrada - 1] != '/' && arq_entrada_qry[0] != '/'){
                strcat(entrada_qry, "/");
            }
        }

        aux2 = (char *)malloc(strlen(arq_entrada_qry) * sizeof(char));
        tam_arq_entrada_qry = strlen(arq_entrada_qry);
        for(i = 0;i < tam_arq_entrada_qry; i++){
            if(arq_entrada_qry[i] == '/'){
                val++;
            }
        }
        for(i = 0;i < tam_arq_entrada_qry; i++){
            if(arq_entrada_qry[i] == '/'){
                aux2[j] = arq_entrada_qry[i];
                j++;
                val2++;
            }
            else if(val2 == val){
                arq_qry[k] = arq_entrada_qry[i];
                k++;
                val2++;
            }
            else if(val2 < val ){
                aux2[j] = arq_entrada_qry[i];
                j++;
            }
            else if(val2 > val){
                arq_qry[k] = arq_entrada_qry[i];
                k++;
            }
        }
        if(aux2[0] == '.' && aux2[1] == '/'){
            tam_aux = strlen(aux2);
            aux_qry = (char *)malloc(strlen(aux2) * sizeof(char));
            j = 0;
        
            for(i = 2;i < tam_aux; i++){
                aux_qry[j] = aux2[i];
                j++;
            }
            strcat(entrada_qry, aux_qry);
            free(aux_qry);
        }
        else{
            strcat(entrada_qry, aux2);
            free(aux2);
        }

    }
}
