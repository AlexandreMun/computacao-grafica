// José Alexandre Munis Nogueira - 473393

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <iostream>

using namespace std;

int largura = 0, altura = 0, nCanais = 0;
unsigned int texID_chao = 0;
unsigned int texID_obj = 0;
unsigned char *dados;

// Carrega dados da textura do chão
void carregar_chao(char* arquivo) {
    stbi_set_flip_vertically_on_load(true);
    dados = stbi_load(arquivo, &largura, &altura, &nCanais, 3);

    // Verificação
    if(!dados){
        cout<<"Não pode ser carregado."<<endl;
    }else{
        cout<<"Textura carregada."<<endl;
    }

    // Cria a textura
    glGenTextures(1, &texID_chao);
    // Ativa a textura
    glBindTexture(GL_TEXTURE_2D, texID_chao);

    //Configura a textura
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_COMBINE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, largura, altura, 0, GL_RGB, GL_UNSIGNED_BYTE, dados);

    // Desativa a textura
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(dados);
}

// Carrega dados da textura do objeto 1
void carregar_obj(char* arquivo) {
    stbi_set_flip_vertically_on_load(true);

    // Pega os dados da textura
    dados = stbi_load(arquivo, &largura, &altura, &nCanais, 3);

    // Verificação
    if(!dados){
        cout<<"Não pode ser carregado."<<endl;
    }else{
        cout<<"Textura carregada."<<endl;
    }

    // Cria a textura
    glGenTextures(1, &texID_obj);
    // Ativa a textura
    glBindTexture(GL_TEXTURE_2D, texID_obj);

    //Configura a textura
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_COMBINE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, largura, altura, 0, GL_RGB, GL_UNSIGNED_BYTE, dados);

    // Desativa a textura
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(dados);
}
