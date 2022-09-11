// OBJETIVO: Importar a textura e aplicar configurações

#include <GL/gl.h>
#include <iostream>
#include <GL/glext.h>
#include<GL\glut.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_images.h"

using namespace std;

// inicia as variaveis
unsigned int id = 0;
int largura = 0,altura = 0,canais = 0;

//carregar a textura
void carregar_textura(){
    glGenTextures(1,&id); // 1 textura
    glBindTexture(GL_TEXTURE_2D,id); // ativa a textura
    stbi_set_flip_vertically_on_load(true); // inverte

    // pega os dados
    unsigned char* entrada = stbi_load("textura1.jpg",&largura,&altura,&canais,3);

    // verifica se foi carregado
    if(!entrada){
        cout<<"impossivel de carregar o arquivo"<<endl;
    }else{
        cout<<"arquivo carregado com sucesso"<<endl;
    }

    //configurar textura
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, largura, altura, 0, GL_RGB, GL_UNSIGNED_BYTE, entrada);

    glBindTexture(GL_TEXTURE_2D, 0); // desativa a textura

    // libera
    stbi_image_free(entrada);
}
