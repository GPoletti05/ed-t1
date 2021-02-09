#include"header.h"

comandos *arquivo_geo(char* arq_geo, char* entrada, char* saida, int* num_lin, int*com_lin){
    int i = 0, k = 0, nx, j = 0;
    FILE *f_geo;
    FILE *f_out_svg;
    char ver[2], *nome;
    comandos *inf;

    if(entrada != NULL){
        f_geo = fopen(strcat(entrada, arq_geo), "r");  
        if(f_geo == NULL){
            printf("Arquivo GEO inexistente\n");
            system ("pause");
            exit(1);
        }
    }

    if(entrada == NULL){
        f_geo = fopen(arq_geo, "r"); 
        if(f_geo == NULL){
            printf("Arquivo GEO inexistente\n");
            system ("pause");
            exit(1);
        }
    } 

    fscanf(f_geo, "%s", ver);

    if(strcmp(ver, "nx") == 0){ //verifica se o arquivo .geo, tem um nx na primeira linha.
        i = 1;
        fscanf(f_geo, "%d", &nx);
        inf = (comandos *)malloc( 100000*sizeof(comandos) ); // o certo neste caso era inf = (comandos *)malloc( nx*sizeof(comandos) );, porem em alguns casos houve erro na execusao do programa.
        i++;
        *com_lin = i;
    }

    else{
        i = 1;
        *com_lin = i;
        inf = (comandos *)malloc( 100000*sizeof(comandos) );
        rewind(f_geo);
    }

    while(1){ // guarda as informacoes do .geo, na string.

        if(feof(f_geo)){
            break;
        }
        fscanf(f_geo, "%s", inf[i].com);

        if(strcmp(inf[i].com, "c")== 0){
            fscanf(f_geo, "%d", &inf[i].k);
            fscanf(f_geo, "%f", &inf[i].r);
            fscanf(f_geo, "%f", &inf[i].x);
            fscanf(f_geo, "%f", &inf[i].y);
            fscanf(f_geo, "%s", inf[i].corb);
            fscanf(f_geo, "%s", inf[i].corp);
            i++;
        }

        else if(strcmp(inf[i].com, "t")== 0){
            fscanf(f_geo, "%d", &inf[i].k);
            fscanf(f_geo, "%f", &inf[i].x);
            fscanf(f_geo, "%f", &inf[i].y);
            fscanf(f_geo, "%s", inf[i].corb);
            fscanf(f_geo, "%s", inf[i].corp);
            fgets(inf[i].txto, 100, f_geo);
            i++;
        }

        if(strcmp(inf[i].com, "r")== 0){
            fscanf(f_geo, "%d", &inf[i].k);
            fscanf(f_geo, "%f", &inf[i].w);
            fscanf(f_geo, "%f", &inf[i].h);
            fscanf(f_geo, "%f", &inf[i].x);
            fscanf(f_geo, "%f", &inf[i].y);
            fscanf(f_geo, "%s", inf[i].corb);
            fscanf(f_geo, "%s", inf[i].corp);
            i++;
        }
    }

    *num_lin = *num_lin + i; // contador de linhas para melhorar os comandos "for" futuros.

    if(saida != NULL){ // faz a saida do .geo.
        nome = (char *)malloc( (strlen(saida)+strlen(arq_geo) + 1)*sizeof(char) );

        while(*saida != '\0') {
            nome[j] = *saida;
            saida++;
            j++;
        }
    }

    if(saida == NULL){
        nome = (char *)malloc((strlen(arq_geo) + 1) * sizeof(char));
    }

    while(*arq_geo != '.' && *arq_geo + 1 != 'g') { // recebe o nome do arquivo .geo e converte para .svg.
        nome[j] = *arq_geo;
        arq_geo++;
        j++;
    }
    nome[j] = '\0'; 

    f_out_svg = fopen(strcat(nome, ".svg"), "w"); 

    fprintf(f_out_svg, "<svg height=\"1080\" width=\"1920\">\n");

    for(k=*com_lin;k<=*num_lin;k++){ // realiza o .svg.
        if(strcmp(inf[k].com, "c") == 0){
            fprintf(f_out_svg,"\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" stroke-width=\"3\" fill=\"%s\" />\n", inf[k].x, inf[k].y, inf[k].r, inf[k].corb, inf[k].corp);
        }

        else if(strcmp(inf[k].com, "t") == 0){
            fprintf(f_out_svg,"\t<text x=\"%f\" y=\"%f\" stroke=\"%s\" stroke-width=\"0.5\" fill=\"%s\">%s</text>\n", inf[k].x, inf[k].y, inf[k].corb, inf[k].corp, inf[k].txto);
        }

        else if(strcmp(inf[k].com, "r") == 0){
            fprintf(f_out_svg,"\t<rect width=\"%f\" height=\"%f\" x=\"%f\" y=\"%f\" stroke=\"%s\" stroke-width=\"3\" fill=\"%s\" />\n", inf[k].w, inf[k].h, inf[k].x, inf[k].y, inf[k].corb, inf[k].corp);
        }           
    }
    fprintf(f_out_svg, "</svg>");
    fclose(f_out_svg);   

    fclose(f_geo);
    free(nome);
    return inf;
}