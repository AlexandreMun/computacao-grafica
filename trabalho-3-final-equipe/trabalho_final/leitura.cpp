// OBJETIVO: Ler um arquivo e importa os dados

#include <iostream>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "objeto.h"

#ifndef LEITURA_H
#define LEITURA_H

using namespace std;

// Ler o arquivo
Objeto* ler_arquivo(char* nome){
    // Cria o objeto
    Objeto* obj = new(Objeto);
    int cont = 0;
    int cont_normal = 0;
    int cont_face = 0;
    int cont_text = 0;

    // Abre o arquivo
    FILE* file = fopen(nome,"r");

    // Verifica se o arquivo está vazio
    if(file == NULL){
        cout<<"erro na leitura"<<endl;
    }

    // Percorre o arquivo
    else{
        while(1){
            char linha[100];
            int res = fscanf(file,"%s",linha);
            if(res == EOF){
                break;
            }

            // Lê os pontos
            if(strcmp(linha,"v") == 0){
                Ponto p;
                fscanf(file, "%f %f %f\n", &p.coord.x, &p.coord.y, &p.coord.z );
                obj->pontos[cont] = p;
                cont++;
            }

            // Lê a textura
            else if(strcmp(linha,"vt") == 0){
                glm::vec2 tex;
                fscanf(file,"%f %f\n",&tex.x,&tex.y);
                obj->pontos[cont_text].tex = tex;
                cont_text++;
            }

            // Lê os vetores normais
            else if(strcmp(linha,"vn") == 0){
                glm::vec3 normal;
                fscanf(file,"%f %f %f\n",&normal.x,&normal.y,&normal.z);
                obj->pontos[cont_normal].normal = normal;
                cont_normal++;
            }

            // Lê as faces
            else if(strcmp(linha,"f") == 0){
                unsigned int vertice[3],textura[3],normal[3];
                fscanf(file," %d/%d/%d %d/%d/%d %d/%d/%d \n",&vertice[0],&textura[0],&normal[0],&vertice[1],&textura[1],&normal[1],&vertice[2],&textura[2],&normal[2]);
                obj->faces[cont_face].id_ponto_1 = vertice[0];
                obj->faces[cont_face].id_ponto_2 = vertice[1];
                obj->faces[cont_face].id_ponto_3 = vertice[2];
                cont_face++;
            }
        }
    }

    // Armazena a quantidade
    obj->quant_ponto = cont;
    obj->quant_lados = cont_face;

    // Retorna o objeto
    return obj;
}
#endif // LEITURA_H
