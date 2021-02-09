#include"header.h"

void arquivos_saida(char* arq_geo, char* saida_svg, char* arq_qry, char* entrada, char* saida, int num_lin, int com_lin, int tam_qry, int com_qry, comandos *qry){

    FILE *f_out_svg_qry;
    int k, i = 0;
    char *nome2;

    if(saida != NULL){
        nome2 = (char *)malloc( (strlen(saida)+strlen(arq_geo) + 3)*sizeof(char) );

        while(*saida != '\0') {
            nome2[i] = *saida;
            saida++;
            i++;
        }
    }

    if(saida == NULL){
        nome2 = (char *)malloc((strlen(arq_geo) + 3)* sizeof(char));
    }

    while(*arq_geo != '.' && *arq_geo + 1 != 'g') {
        nome2[i] = *arq_geo;
        arq_geo++;
        i++;
    }
  
    nome2[i] = '\0'; 
    
    f_out_svg_qry = fopen(strcat(nome2, "-q.svg"), "w"); // saida do -q.svg (arquivo svg modificado pelo qry).
    
    fprintf(f_out_svg_qry, "<svg height=\"1080\" width=\"1920\">\n");
    for(k=com_lin;k<=num_lin;k++){ // for responsavel por inserir as informacoes sem modificacoes.
        if(strcmp(qry[k].com, "x") == 0){ // esse x representa as formas que passaram pelos comandos delf e *delf.
            continue;
        }
        if(strcmp(qry[k].com, "c") == 0){
            fprintf(f_out_svg_qry,"\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" stroke-width=\"3\" fill=\"%s\" />\n", qry[k].x, qry[k].y, qry[k].r, qry[k].corb, qry[k].corp);
        }
        else if(strcmp(qry[k].com, "t") == 0){
            fprintf(f_out_svg_qry,"\t<text x=\"%f\" y=\"%f\" stroke=\"%s\" stroke-width=\"0.5\" fill=\"%s\">%s</text>\n", qry[k].x, qry[k].y, qry[k].corb, qry[k].corp, qry[k].txto);
        }
        else if(strcmp(qry[k].com, "r") == 0){
            fprintf(f_out_svg_qry,"\t<rect width=\"%f\" height=\"%f\" x=\"%f\" y=\"%f\" stroke=\"%s\" stroke-width=\"3\" fill=\"%s\" />\n", qry[k].w, qry[k].h, qry[k].x, qry[k].y, qry[k].corb, qry[k].corp);
        }          
    } 
    if(tam_qry > com_qry){ // caso a opcao i? e o? for usada no qry, abre esse laco.
        for(k=com_qry;k<tam_qry;k++){
            if(strcmp(qry[k].com, "cs") == 0){
                fprintf(f_out_svg_qry,"\t<rect width=\"%f\" height=\"%f\" x=\"%f\" y=\"%f\" stroke=\"black\" stroke-width=\"3\" fill=\"none\" />\n", qry[k].w, qry[k].h, qry[k].x, qry[k].y);
            }
            else if(strcmp(qry[k].com, "cn") == 0){
                fprintf(f_out_svg_qry,"\t<rect width=\"%f\" height=\"%f\" x=\"%f\" y=\"%f\" stroke=\"black\" stroke-dasharray=\"5\" fill=\"none\" />\n", qry[k].w, qry[k].h, qry[k].x, qry[k].y);
            }
            else if(strcmp(qry[k].com, "rn") == 0){
                fprintf(f_out_svg_qry,"\t<rect width=\"%f\" height=\"%f\" x=\"%f\" y=\"%f\" stroke=\"black\" stroke-dasharray=\"5\" fill=\"none\" />\n", qry[k].w, qry[k].h, qry[k].x, qry[k].y);
            }
            else if(strcmp(qry[k].com, "rs") == 0){
                fprintf(f_out_svg_qry,"\t<rect width=\"%f\" height=\"%f\" x=\"%f\" y=\"%f\" stroke=\"black\" stroke-width=\"3\" fill=\"none\" />\n", qry[k].w, qry[k].h, qry[k].x, qry[k].y);
            }
            else if(strcmp(qry[k].com, "rcs") == 0){
                fprintf(f_out_svg_qry,"\t<rect width=\"%f\" height=\"%f\" x=\"%f\" y=\"%f\" stroke=\"black\" stroke-width=\"3\" fill=\"none\" />\n", qry[k].w, qry[k].h, qry[k].x, qry[k].y);
            }
            else if(strcmp(qry[k].com, "rcn") == 0){
                fprintf(f_out_svg_qry,"\t<rect width=\"%f\" height=\"%f\" x=\"%f\" y=\"%f\" stroke=\"black\" stroke-dasharray=\"5\" fill=\"none\" />\n", qry[k].w, qry[k].h, qry[k].x, qry[k].y);
            }
            else if(strcmp(qry[k].com, "ci") == 0){
                fprintf(f_out_svg_qry,"\t<circle cx=\"%f\" cy=\"%f\" r=\"2.5\" stroke=\"%s\" stroke-width=\"3\" fill=\"%s\" />\n", qry[k].x, qry[k].y, qry[k].corb, qry[k].corp);
            }
            else if(strcmp(qry[k].com, "cni") == 0){
                fprintf(f_out_svg_qry,"\t<circle cx=\"%f\" cy=\"%f\" r=\"2.5\" stroke=\"%s\" stroke-width=\"3\" fill=\"%s\" />\n", qry[k].x, qry[k].y, qry[k].corb, qry[k].corp);
            }
            else if(strcmp(qry[k].com, "ri") == 0){
                fprintf(f_out_svg_qry,"\t<circle cx=\"%f\" cy=\"%f\" r=\"2.5\" stroke=\"%s\" stroke-width=\"3\" fill=\"%s\" />\n", qry[k].x, qry[k].y, qry[k].corb, qry[k].corp);
            }
            else if(strcmp(qry[k].com, "rni") == 0){
                fprintf(f_out_svg_qry,"\t<circle cx=\"%f\" cy=\"%f\" r=\"2.5\" stroke=\"%s\" stroke-width=\"3\" fill=\"%s\" />\n", qry[k].x, qry[k].y, qry[k].corb, qry[k].corp);
            }
            else if(strcmp(qry[k].com, "lin") == 0){
                fprintf(f_out_svg_qry,"\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" stroke-width=\"3\"/>\n", qry[k].x, qry[k].y, qry[k].w, qry[k].h, qry[k].corp);
            }
        } 
    }
    fprintf(f_out_svg_qry, "</svg>");
    fclose(f_out_svg_qry);

    free(nome2);
}