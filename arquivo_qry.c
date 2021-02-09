#include"header.h"

comandos*arquivo_qry(char* arq_qry, char* arq_geo, char* entrada_qry, char* saida_txt, char* saida, int num_lin, int com_lin, int* tam_qry, int* com_qry, char* entrada, comandos *forma){
    int i, tam, j, k, l, n = 0, nx;
    char *nome, ver[2];
    float dis_cir, raio_cir, r1x, r1y, r1w, r1h, r2x, r2y, r2w, r2h, testX, testY, distX, distY, dis;
    FILE *f_qry;
    FILE *f_txt_qry;
    comandos *inf2, *inf3;

    inf2 = (comandos *)malloc(sizeof(comandos) ); // structs auxiliares.
    inf3 = (comandos *)malloc(sizeof(comandos) );

    if(entrada_qry != NULL){
        f_qry = fopen(strcat(entrada_qry, arq_qry), "r"); 
        if(f_qry == NULL){
            printf("Arquivo QRY inexistente\n");
            system ("pause");
            exit(1);
        }
    }

    if(entrada_qry == NULL){
        f_qry = fopen(arq_qry, "r");
        
        if(f_qry == NULL){
            printf("Arquivo QRY inexistente\n");
            system ("pause");
            exit(1);
        }
    } 

    if(saida != NULL){

        nome = (char *)malloc( (strlen(saida)+strlen(arq_geo) + 3)*sizeof(char) );

        while(*saida != '\0') {
            nome[n] = *saida;
            saida++;
            n++;
        }
    }

    else if(saida == NULL){
        nome = (char *)malloc((strlen(arq_geo) + 3)* sizeof(char));
    }

    while(*arq_geo != '.' && *arq_geo + 1 != 'g') {
        nome[n] = *arq_geo;
        arq_geo++;
        n++;
    }
    nome[n] = '\0';  

    f_txt_qry = fopen(strcat(nome, "-q.txt"), "w"); // arquiv de saida .txt.

    *com_qry = num_lin + 1; //contadores de linhas.
    *tam_qry = *com_qry;
    l = *tam_qry;

    while(1){ // laco de repeticao da leitura do arquivo .qry, e modificacao das struct originais do .geo.
        if(feof(f_qry)){
            break;
        }
        fscanf(f_qry, "%s", inf2->com); // recebe a primeira informacao da linha atual do qry, para comparar com as opcoes abaixo.

        if(strcmp(inf2->com, "pnt") == 0){
            fscanf(f_qry, "%d ", &inf2->j);
            fscanf(f_qry, "%s", inf2->corb);
            fscanf(f_qry, "%s", inf2->corp);
            for(i=com_lin;i<=num_lin;i++){
                if(inf2->j == forma[i].k){
                    strcpy(forma[i].corb, inf2->corb);
                    strcpy(forma[i].corp, inf2->corp);
                    fprintf(f_txt_qry, "%s %s %d %s %s\nx:%f y:%f\n\n",  inf2->com, forma[i].com, inf2->j, inf2->corb, inf2->corp,forma[i].x, forma[i].y);
                }
            }
        }

        else if(strcmp(inf2->com, "pnt*") == 0){
            fscanf(f_qry, "%d ", &inf2->j);
            fscanf(f_qry, "%d ", &inf2->k);
            fscanf(f_qry, "%s", inf2->corb);
            fscanf(f_qry, "%s", inf2->corp);
            for(i=com_lin;i<=num_lin;i++){
                if(forma[i].k >= inf2->j && forma[i].k <= inf2->k){
                    strcpy(forma[i].corb, inf2->corb);
                    strcpy(forma[i].corp, inf2->corp);
                    fprintf(f_txt_qry, "%s %s %d %s %s\nx:%f y:%f\n\n", inf2->com, forma[i].com, forma[i].k, inf2->corb, inf2->corp,forma[i].x, forma[i].y);
                }
            }
        }

        else if(strcmp(inf2->com, "delf") == 0){
            fprintf(f_txt_qry, "%s ", inf2->com);
            fscanf(f_qry, "%d", &inf2->j);
            fprintf(f_txt_qry, "%d\n", inf2->j);
            for(i=com_lin;i<=num_lin;i++){
                if(inf2->j == forma[i].k){
                    if(strcmp(forma[i].com, "c") == 0){
                        fprintf(f_txt_qry, "%s %d %f %f %f %s %s\n\n", forma[i].com, forma[i].k, forma[i].r, forma[i].x, forma[i].y, forma[i].corb, forma[i].corp);
                        strcpy(forma[i].com, "x");
                    }
                    else if(strcmp(forma[i].com, "r") == 0){
                        fprintf(f_txt_qry, "%s %d %f %f %f %f %s %s\n\n", forma[i].com, forma[i].k, forma[i].w, forma[i].h, forma[i].x, forma[i].y, forma[i].corb, forma[i].corp);
                        strcpy(forma[i].com, "x");
                    }
                    else if(strcmp(forma[i].com, "t") == 0){
                        fprintf(f_txt_qry, "%s %d %f %f %s %s %s\n", forma[i].com, forma[i].k,forma[i].x, forma[i].y, forma[i].corb,forma[i].corp, forma[i].txto);
                        strcpy(forma[i].com, "x");
                    }
                }
            }
        }

        else if(strcmp(inf2->com, "delf*") == 0){
            fprintf(f_txt_qry, "%s ", inf2->com);
            fscanf(f_qry, "%d", &inf2->j);
            fprintf(f_txt_qry, "%d ", inf2->j);
            fscanf(f_qry, "%d", &inf2->k);
            fprintf(f_txt_qry, "%d\n", inf2->k);
            for(i=com_lin;i<=num_lin;i++){
                if(forma[i].k >= inf2->j && forma[i].k <= inf2->k){
                    if(strcmp(forma[i].com, "c") == 0){
                        fprintf(f_txt_qry, "%s %d %f %f %f %s %s\n\n", forma[i].com, forma[i].k, forma[i].r, forma[i].x, forma[i].y, forma[i].corb, forma[i].corp);
                        strcpy(forma[i].com, "x");
                    }
                    else if(strcmp(forma[i].com, "r") == 0){
                        fprintf(f_txt_qry, "%s %d %f %f %f %f %s %s\n\n", forma[i].com, forma[i].k, forma[i].w, forma[i].h, forma[i].x, forma[i].y, forma[i].corb, forma[i].corp);
                        strcpy(forma[i].com, "x");
                    }
                    else if(strcmp(forma[i].com, "t") == 0){
                        fprintf(f_txt_qry, "%s %d %f %f %s %s %s\n", forma[i].com, forma[i].k,forma[i].x, forma[i].y, forma[i].corb,forma[i].corp, forma[i].txto);
                        strcpy(forma[i].com, "x");
                    }
                }
            }
        }

        else if(strcmp(inf2->com, "o?") == 0){
            fprintf(f_txt_qry, "%s ", inf2->com);
            fscanf(f_qry, "%d", &inf2->j);
            fprintf(f_txt_qry, "%d ", inf2->j);
            fscanf(f_qry, "%d", &inf2->k);
            fprintf(f_txt_qry, "%d\n", inf2->k);
            for(i=com_lin;i<=num_lin;i++){
                if(strcmp(forma[i].com, "nx") == 0){
                    continue;
                }
                else if(forma[i].k == inf2->j){
                    if(strcmp(forma[i].com, "c") == 0){
                        strcpy(inf2->com, forma[i].com);
                        inf2->x = forma[i].x;
                        inf2->y = forma[i].y;
                        inf2->r = forma[i].r;
                        fprintf(f_txt_qry, "%d: circulo ", inf2->j);
                    }
                    else if(strcmp(forma[i].com, "r") == 0){
                        strcpy(inf2->com, forma[i].com);
                        inf2->x = forma[i].x;
                        inf2->y = forma[i].y;
                        inf2->h = forma[i].h;
                        inf2->w = forma[i].w;
                        fprintf(f_txt_qry, "%d: retangulo ", inf2->j);
                    }

                }
                else if(forma[i].k == inf2->k){
                    if(strcmp(forma[i].com, "c") == 0){
                        strcpy(inf3->com, forma[i].com);
                        inf3->x = forma[i].x;
                        inf3->y = forma[i].y;
                        inf3->r = forma[i].r;
                        fprintf(f_txt_qry, "%d: circulo ", inf2->k);
                    }
                    else if(strcmp(forma[i].com, "r") == 0){
                        strcpy(inf3->com, forma[i].com);
                        inf3->x = forma[i].x;
                        inf3->y = forma[i].y;
                        inf3->h = forma[i].h;
                        inf3->w = forma[i].w;
                        fprintf(f_txt_qry, "%d: retangulo ", inf2->k);
                    }
                }
                else{
                    continue;
                }
            }
            if(strcmp(inf2->com, "c") == 0 && strcmp(inf3->com, "c") == 0){
                dis_cir = sqrt((inf2->x - inf3->x) * (inf2->x - inf3->x) + (inf2->y - inf3->y) * (inf2->y - inf3->y));
                raio_cir = (inf2->r + inf3->r) * (inf2->r + inf3->r);

                if(dis_cir <= inf2->r + inf3->r){
                    strcpy(forma[l].com, "cs");
                    if(inf2->x < inf3->x){
                        forma[l].x =  inf2->x - inf2->r;
                        forma[l].w =  (inf3->x + inf3->r) - (inf2->x - inf2->r); 
                    }    
                    else if(inf3->x < inf2->x){
                        forma[l].x =  inf3->x - inf3->r;
                        forma[l].w =  (inf2->x + inf2->r) - (inf3->x - inf3->r);
                    }
                    else if(inf3->x == inf2->x){
                        forma[l].x =  inf2->x - inf2->r;
                        if(inf2->r > inf3->r){
                            forma[l].w = inf2->r * 2; 
                        }
                        else if(inf2->r < inf3->r){
                            forma[l].w = inf3->r * 2;
                        }
                        else if(inf2->r == inf3->r){
                            forma[l].w = inf3->r * 2;
                        }
                    }
                    if(inf2->y < inf3->y){
                        forma[l].y =  inf2->y - inf2->r;
                        forma[l].h =  (inf3->y + inf3->r) - (inf2->y - inf2->r); 
                    }    
                    else if(inf3->y < inf2->y){
                        forma[l].y =  inf3->y - inf3->r;
                        forma[l].h =  (inf2->y + inf2->r) - (inf3->y - inf3->r);
                    }
                    else if(inf3->y == inf2->y){
                        forma[l].y =  inf2->y - inf2->r;
                        if(inf2->r > inf3->r){
                            forma[l].h = inf2->r * 2; 
                        }
                        else if(inf2->r < inf3->r){
                            forma[l].h = inf3->r * 2;
                        }
                        else if(inf2->r == inf3->r){
                            forma[l].h = inf3->r * 2;
                        }
                    } 
                    fprintf(f_txt_qry, " SIM\n\n");
                }
                else{
                   strcpy(forma[l].com, "cn");
                    if(inf2->x < inf3->x){
                        forma[l].x =  inf2->x - inf2->r;
                        forma[l].w =  (inf3->x + inf3->r) - (inf2->x - inf2->r); 
                    }    
                    else if(inf3->x < inf2->x){
                        forma[l].x =  inf3->x - inf3->r;
                        forma[l].w =  (inf2->x + inf2->r) - (inf3->x - inf3->r);
                    }
                    else if(inf3->x == inf2->x){
                        forma[l].x =  inf2->x - inf2->r;
                        if(inf2->r > inf3->r){
                            forma[l].w = inf2->r * 2; 
                        }
                        else if(inf2->r < inf3->r){
                            forma[l].w = inf3->r * 2;
                        }
                        else if(inf2->r == inf3->r){
                            forma[l].w = inf3->r * 2;
                        }
                    }
                    if(inf2->y < inf3->y){
                        forma[l].y =  inf2->y - inf2->r;
                        forma[l].h =  (inf3->y + inf3->r) - (inf2->y - inf2->r); 
                    }    
                    else if(inf3->y < inf2->y){
                        forma[l].y =  inf3->y - inf3->r;
                        forma[l].h =  (inf2->y + inf2->r) - (inf3->y - inf3->r);
                    }
                    else if(inf3->y == inf2->y){
                        forma[l].y =  inf2->y - inf2->r;
                        if(inf2->r > inf3->r){
                            forma[l].h = inf2->r * 2; 
                        }
                        else if(inf2->r < inf3->r){
                            forma[l].h = inf3->r * 2;
                        }
                        else if(inf2->r == inf3->r){
                            forma[l].h = inf3->r * 2;
                        }
                    } 
                    fprintf(f_txt_qry, " NAO\n\n");
                } 
            l++;
            }
            else if(strcmp(inf2->com, "r") == 0 && strcmp(inf3->com, "r") == 0){
                if(inf2->x + inf2->w >= inf3->x && inf2->x <= inf3->x + inf3->w && inf2->y + inf2->h >= inf3->y && inf2->y <= inf3->y + inf3->h){    
                    strcpy(forma[l].com, "rs");
                    fprintf(f_txt_qry, "SIM\n\n");
                    if(inf2->x < inf3->x){
                        forma[l].x = inf2->x;
                        if(inf2->w < inf3->w){
                            forma[l].w = (inf3->x - inf2->x) + inf3->w;
                        }
                        else if(inf3->w < inf2->w){
                            forma[l].w = (inf3->x - inf2->x) + inf2->w;
                        }
                        else{
                            forma[l].w = (inf3->x - inf2->x) + inf2->w;
                        }
                    }
                    else if(inf3->x < inf2->x){
                        forma[l].x = inf3->x;
                        if(inf2->w < inf3->w){
                            forma[l].w = (inf2->x - inf3->x) + inf3->w;
                        }
                        else if(inf3->w < inf2->w){
                            forma[l].w = (inf2->x - inf3->x) + inf2->w;
                        }
                        else{
                            forma[l].w = (inf2->x - inf3->x) + inf2->w;
                        }
                    }
                    if(inf2->y < inf3->y){
                        forma[l].y = inf2->y;
                        if(inf2->h < inf3->h){
                            forma[l].h = (inf3->y - inf2->y) + inf3->h;
                        }
                        else if(inf3->h < inf2->h){
                            forma[l].h = (inf3->y - inf2->y) + inf2->h;
                        }
                        else{
                            forma[l].h = (inf3->y - inf2->y) + inf2->h;
                        }
                    }
                    else if(inf3->y < inf2->y){
                        forma[l].y = inf3->y;
                        if(inf3->h < inf2->h){
                            forma[l].h = (inf2->y - inf3->y) + inf2->h;
                        }
                        else if(inf2->h < inf3->h){
                            forma[l].h = (inf2->y - inf3->y) + inf3->h;
                        }
                        else{
                            forma[l].h = (inf2->y - inf3->y) + inf3->h;
                        }
                    }
                }
                else{
                    strcpy(forma[l].com, "rn");
                    fprintf(f_txt_qry, "NAO\n\n");
                    if(inf2->x < inf3->x){
                        forma[l].x = inf2->x;
                        if(inf2->w < inf3->w){
                            forma[l].w = (inf3->x - inf2->x) + inf3->w;
                        }
                        else if(inf3->w < inf2->w){
                            forma[l].w = (inf3->x - inf2->x) + inf2->w;
                        }
                        else{
                            forma[l].w = (inf3->x - inf2->x) + inf2->w;
                        }
                    }
                    else if(inf3->x < inf2->x){
                        forma[l].x = inf3->x;
                        if(inf2->w < inf3->w){
                            forma[l].w = (inf2->x - inf3->x) + inf3->w;
                        }
                        else if(inf3->w < inf2->w){
                            forma[l].w = (inf2->x - inf3->x) + inf2->w;
                        }
                        else{
                            forma[l].w = (inf2->x - inf3->x) + inf2->w;
                        }
                    }
                    if(inf2->y < inf3->y){
                        forma[l].y = inf2->y;
                        if(inf2->h < inf3->h){
                            forma[l].h = (inf3->y - inf2->y) + inf3->h;
                        }
                        else if(inf3->h < inf2->h){
                            forma[l].h = (inf3->y - inf2->y) + inf2->h;
                        }
                        else{
                            forma[l].h = (inf3->y - inf2->y) + inf2->h;
                        }
                    }
                    else if(inf3->y < inf2->y){
                        forma[l].y = inf3->y;
                        if(inf3->h < inf2->h){
                            forma[l].h = (inf2->y - inf3->y) + inf2->h;
                        }
                        else if(inf2->h < inf3->h){
                            forma[l].h = (inf2->y - inf3->y) + inf3->h;
                        }
                        else{
                            forma[l].h = (inf2->y - inf3->y) + inf3->h;
                        }
                    }
                }
            l++;
            }
            else if(strcmp(inf2->com, "r") == 0 && strcmp(inf3->com, "c") == 0){
                testX = inf3->x;
                testY = inf3->y;

                if(inf3->x < inf2->x){
                    testX = inf2->x;
                }
                else if(inf3->x > inf2->x + inf2->w){
                    testX = inf2->x + inf2->w;
                }
                if(inf3->y < inf2->y){
                    testY = inf2->y;
                }
                else if(inf3->y > inf2->y + inf2->h){
                    testY = inf2->y + inf2->h;
                }

                distX = inf3->x - testX;
                distY = inf3->y - testY;
                dis = sqrt((distX*distX) + (distY*distY));
                if(dis <= inf3->r){
                    strcpy(forma[l].com, "rcs");
                    fprintf(f_txt_qry, " SIM\n\n");
                }
                else{
                    strcpy(forma[l].com, "rcn");
                    fprintf(f_txt_qry, " NAO\n\n");
                }
                if(inf2->x < inf3->x){
                    forma[l].x = inf2->x - inf3->r;
                    forma[l].w = (inf3->x - inf2->x) + (inf3->r * 2);
                }
                else if(inf3->x < inf2->x){
                    forma[l].x = inf3->x - inf3->r;
                    forma[l].w = (inf2->x - inf3->x) + (inf3->r * 2);
                }
                if(inf2->y < inf3->y){
                    forma[l].y = inf2->y - inf3->r;
                    forma[l].h = (inf3->y - inf2->y) + (inf3->r * 2);
                }
                else if(inf3->y < inf2->y){
                    forma[l].y = inf3->y - inf3->r;
                    forma[l].h = (inf2->y - inf3->y) + (inf3->r * 2);
                }
            l++;
            }
            else if(strcmp(inf2->com, "c") == 0 && strcmp(inf3->com, "r") == 0){
                testX = inf2->x;
                testY = inf2->y;

                if(inf2->x < inf3->x){
                    testX = inf3->x;
                }
                else if(inf2->x > inf3->x + inf3->w){
                    testX = inf3->x + inf3->w;
                }
                if(inf2->y < inf3->y){
                    testY = inf3->y;
                }
                else if(inf2->y > inf3->y + inf3->h){
                    testY = inf3->y + inf3->h;
                }

                distX = inf2->x - testX;
                distY = inf2->y - testY;
                dis = sqrt((distX*distX) + (distY*distY));
                if(dis <= inf2->r){
                    strcpy(forma[l].com, "rcs");
                    fprintf(f_txt_qry, " SIM\n\n");
                }
                else{
                    strcpy(forma[l].com, "rcn");
                    fprintf(f_txt_qry, " NAO\n\n");
                }
                if(inf3->x < inf2->x){
                    forma[l].x = inf3->x - inf2->r;
                    forma[l].w = (inf2->x - inf3->x) + (inf2->r * 2);
                }
                else if(inf2->x < inf3->x){
                    forma[l].x = inf2->x - inf2->r;
                    forma[l].w = (inf3->x - inf2->x) + (inf2->r * 2);
                }
                if(inf3->y < inf2->y){
                    forma[l].y = inf3->y - inf2->r;
                    forma[l].h = (inf2->y - inf3->y) + (inf2->r * 2);
                }
                else if(inf2->y < inf3->y){
                    forma[l].y = inf2->y - inf2->r;
                    forma[l].h = (inf3->y - inf2->y) + (inf2->r * 2);
                }
            l++;
            }
        }

        else if(strcmp(inf2->com, "i?") == 0){
            fscanf(f_qry, "%d", &inf2->j);
            fscanf(f_qry, "%f", &inf2->x);
            fscanf(f_qry, "%f", &inf2->y);
            fprintf(f_txt_qry, "%s ", inf2->com);
            fprintf(f_txt_qry, "%d ", inf2->j);
            fprintf(f_txt_qry, "%f ", inf2->x);
            fprintf(f_txt_qry, "%f\n", inf2->y);
            for(i=com_lin;i<=num_lin;i++){
                if(strcmp(forma[i].com, "nx") == 0){
                    fscanf(f_qry, "%d", &nx);
                    continue;
                }
                if(forma[i].k == inf2->j){
                    if(strcmp(forma[i].com, "c") == 0){
                        strcpy(inf3->com, forma[i].com);
                        inf3->x = forma[i].x;
                        inf3->y = forma[i].y;
                        inf3->r = forma[i].r;
                        fprintf(f_txt_qry, "%d: circulo ", inf2->j);
                        distX = inf2->x - inf3->x;
                        distY = inf2->y - inf3->y;
                        dis = sqrt( (distX * distX) + (distY * distY));
                        if(dis <= inf3->r){
                            fprintf(f_txt_qry, "INTERNO\n\n");
                            strcpy(forma[l].com, "ci");
                            forma[l].x = inf2->x;
                            forma[l].y = inf2->y;
                            strcpy(forma[l].corp, "blue");
                            strcpy(forma[l].corb, "blue");
                            l++;
                            strcpy(forma[l].com, "lin");
                            forma[l].x = inf2->x;
                            forma[l].y = inf2->y;
                            forma[l].w = inf3->x;
                            forma[l].h = inf3->y;
                            strcpy(forma[l].corp, "blue");
                            l++;
                        }
                        else{
                            fprintf(f_txt_qry, "NAO INTERNO\n\n");
                            strcpy(forma[l].com, "cni");
                            forma[l].x = inf2->x;
                            forma[l].y = inf2->y;
                            strcpy(forma[l].corp, "magenta");
                            strcpy(forma[l].corb, "magenta");
                            l++;
                            strcpy(forma[l].com, "lin");
                            forma[l].x = inf2->x;
                            forma[l].y = inf2->y;
                            forma[l].w = inf3->x;
                            forma[l].h = inf3->y;
                            strcpy(forma[l].corp, "magenta");
                            l++;
                        }
                    }
                    else if(strcmp(forma[i].com, "r") == 0){
                        strcpy(inf3->com, forma[i].com);
                        inf3->x = forma[i].x;
                        inf3->y = forma[i].y;
                        inf3->h = forma[i].h;
                        inf3->w = forma[i].w;
                        fprintf(f_txt_qry, "%d: retangulo ", inf2->j);
                        if(inf2->x >= inf3->x && inf2->x <= inf3->x + inf3->w && inf2->y >= inf3->y && inf2->y <= inf3->y + inf3->h){
                            fprintf(f_txt_qry, "INTERNO\n\n");
                            strcpy(forma[l].com, "ri");
                            forma[l].x = inf2->x;
                            forma[l].y = inf2->y;
                            strcpy(forma[l].corp, "blue");
                            strcpy(forma[l].corb, "blue");
                            l++;
                            strcpy(forma[l].com, "lin");
                            forma[l].x = inf2->x;
                            forma[l].y = inf2->y;
                            forma[l].w = inf3->x + inf3->w/2;
                            forma[l].h = inf3->y + inf3->h/2;
                            strcpy(forma[l].corp, "blue");
                            l++;
                        }
                        else{
                            fprintf(f_txt_qry, "NAO INTERNO\n\n");
                            strcpy(forma[l].com, "rni");
                            forma[l].x = inf2->x;
                            forma[l].y = inf2->y;
                            strcpy(forma[l].corp, "magenta");
                            strcpy(forma[l].corb, "magenta");
                            l++;
                            strcpy(forma[l].com, "lin");
                            forma[l].x = inf2->x;
                            forma[l].y = inf2->y;
                            forma[l].w = inf3->x + inf3->w/2;
                            forma[l].h = inf3->y + inf3->h/2;
                            strcpy(forma[l].corp, "magenta");
                            l++;
                        }
                    }
                }
            }
        }
    }

    *tam_qry = l;

    fclose(f_qry);
    fclose(f_txt_qry);
    free(nome);
    free(inf2);
    free(inf3);
    return forma;
}