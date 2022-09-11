// José Alexandre Munis Nogueira - 473393

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "textura.cpp"
#include"leitura.cpp"

int janelaLargura, janelaAltura;
float aspectRatio;

// Camera
glm::vec3 camera(12,30,10);
glm::vec3 look(12,-30,-10);

// Luz
glm::vec3 pos_luz(10,10,10);
glm::vec3 luz_ambiente(0.25f,0.25f,0.25f);
glm::vec3 luz_difusa(1.0f,1.0f,1.0f);
glm::vec3 luz_especular(0.5f,0.5f,0.5f);

// Objetos
Objeto* obj_1;
Objeto* obj_2;

// Iluminação
glm::vec3 iluminacao(glm::vec3 normal,glm::vec3 pos,glm::vec3 cor,glm::vec3 obj_ambiente,glm::vec3 obj_especular,int obj_expoente) {
    // Calculo das variaveis
    glm::vec3 lp = normalize(pos_luz-pos);
    glm::vec3 vw = normalize(camera-pos);
    glm::vec3 rf = 2*glm::dot(lp,normal)*normal -lp;

    glm::vec3 ambiente= luz_ambiente * obj_ambiente;
    glm::vec3 difusa= (luz_difusa * cor) * glm::dot(normal,lp);
    glm::vec3 especular;

    // Caso o escalar seja negativo transforma a especular em 0
    if(glm::dot(vw,rf) < 0){
        especular = glm::vec3(0.0f,0.0f,0.0f);
    }
    // Calcula a especular
    else{
        especular = luz_especular * obj_especular * (float)pow(glm::dot(vw,rf),obj_expoente);
    }

    // Calcula a luz e retorna
    glm::vec3 resultado_final = ambiente + difusa + especular;
    return resultado_final;
}

// Carregando configurações
void inicio(){
    glClearColor(0.5, 0.5, 0.5, 1);
    glPointSize(10);
    glLineWidth(5);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    // Lendo os OBJ
    obj_1 = ler_arquivo("pawn3.obj");
    obj_2 = ler_arquivo("rainha.obj");

    // Carregando texturas
    carregar_chao("textura.jpg");
    carregar_obj("textura2.jpg");
}

// Redimensionar a janela
void redimensiona(int w, int h) {
    janelaLargura = w;
    janelaAltura = h;
    aspectRatio = (float)w/h;

    glutPostRedisplay();
}

// Mapeamento do teclado
void teclado(unsigned char key, int x, int y){
        switch(key){
        case '1':
            camera = glm::vec3(12,30,10); look = glm::vec3(12,-30,-10); break;
        case '2':
            camera = glm::vec3(-20,16,10); look = glm::vec3(-2,10,4); break;
        case '3':
            camera = glm::vec3(14,-16,10); look = glm::vec3(0,10,4); break;
        case '4':
            camera = glm::vec3(30,4,10); look = glm::vec3(0,6,4); break;
        }

    glutPostRedisplay();
}

// Desenha quadrado
void desenha_chao() {
    unsigned int texID_chao = 1;
    // Ativando a textura
    if(texID_chao != 0) glBindTexture(GL_TEXTURE_2D, texID_chao);

    glBegin(GL_QUADS);
        // Calculando a iluminação
        glm::vec3 cor1 = iluminacao(glm::vec3(0,0,1), glm::vec3(0,0,0), glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
        // Aplicando a cor com a iluminação
        glColor3f(cor1.x,cor1.y,cor1.z);
        // Aplicando a textura
        glTexCoord2f(0, 0);
        // Criando os pontos
        glVertex3f(0,0,0);

        // Calculando a iluminação
        glm::vec3 cor2 = iluminacao(glm::vec3(0,0,1), glm::vec3(0,20,0), glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
        // Aplicando a cor com a iluminação
        glColor3f(cor2.x,cor2.y,cor2.z);
        // Aplicando a textura
        glTexCoord2f(0, 1);
        // Criando os pontos
        glVertex3f(0,20,0);

        // Calculando a iluminação
        glm::vec3 cor3 = iluminacao(glm::vec3(0,0,1), glm::vec3(20,20,0), glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
        // Aplicando a cor com a iluminação
        glColor3f(cor3.x,cor3.y,cor3.z);
        // Aplicando a textura
        glTexCoord2f(1, 1);
        // Criando os pontos
        glVertex3f(20,20,0);

        // Calculando a iluminação
        glm::vec3 cor4 = iluminacao(glm::vec3(0,0,1), glm::vec3(20,0,0), glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
        // Aplicando a cor com a iluminação
        glColor3f(cor4.x,cor4.y,cor4.z);
        // Aplicando a textura
        glTexCoord2f(1, 0);
        // Criando os pontos
        glVertex3f(20,0,0);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);

}

// Desenha o objeto 1
void desenhar_obj_1(){
    // Ativando a textura
    glBindTexture(GL_TEXTURE_2D, texID_obj);

    glPushMatrix();

    // Aplicando translate e scale no objeto
    glTranslatef(12,8,0);
    glScalef(6,6,6);

    // Criando o objeto em triangulos
    glBegin(GL_TRIANGLES);
        for(int i = 0;i < obj_1->quant_lados;i++){
            // Calculando a iluminação
            glm::vec3 cor1 = iluminacao(obj_1->pontos[obj_1->faces[i].id_ponto_1 - 1].normal, obj_1->pontos[obj_1->faces[i].id_ponto_1 - 1].coord, glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
            // Aplicando a cor com a iluminação
            glColor3f(cor1.x,cor1.y,cor1.z);
            // Aplicando a textura de acordo com o objeto
            glTexCoord2f(obj_1->pontos->tex.x, obj_1->pontos->tex.y);
            // Criando os pontos de acordo com o objeto
            glVertex3f(obj_1->pontos[obj_1->faces[i].id_ponto_1-1].coord.x,obj_1->pontos[obj_1->faces[i].id_ponto_1-1].coord.y,obj_1->pontos[obj_1->faces[i].id_ponto_1-1].coord.z);

            // Calculando a iluminação
            glm::vec3 cor2 = iluminacao(obj_1->pontos[obj_1->faces[i].id_ponto_2 - 1].normal,obj_1->pontos[obj_1->faces[i].id_ponto_2 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
            // Aplicando a cor com a iluminação
            glColor3f(cor2.x,cor2.y,cor2.z);
            // Aplicando a textura de acordo com o objeto
            glTexCoord2f(obj_1->pontos->tex.x, obj_1->pontos->tex.y);
            // Criando os pontos de acordo com o objeto
            glVertex3f(obj_1->pontos[obj_1->faces[i].id_ponto_2-1].coord.x,obj_1->pontos[obj_1->faces[i].id_ponto_2-1].coord.y,obj_1->pontos[obj_1->faces[i].id_ponto_2-1].coord.z);

            // Calculando a iluminação
            glm::vec3 cor3 = iluminacao(obj_1->pontos[obj_1->faces[i].id_ponto_3 - 1].normal,obj_1->pontos[obj_1->faces[i].id_ponto_3 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
            // Aplicando a cor com a iluminação
            glColor3f(cor3.x,cor3.y,cor3.z);
            // Aplicando a textura de acordo com o objeto
            glTexCoord2f(obj_1->pontos->tex.x, obj_1->pontos->tex.y);
            // Criando os pontos de acordo com o objeto
            glVertex3f(obj_1->pontos[obj_1->faces[i].id_ponto_3-1].coord.x,obj_1->pontos[obj_1->faces[i].id_ponto_3-1].coord.y,obj_1->pontos[obj_1->faces[i].id_ponto_3-1].coord.z);
        }
    glEnd();

    glPopMatrix();

    // Desativando a textura
    glBindTexture(GL_TEXTURE_2D, 0);
}

// Desenha o objeto 2
void desenhar_obj_2(){
    // Ativando a textura
    glBindTexture(GL_TEXTURE_2D, texID_obj);

    glPushMatrix();

    // Aplicando translate e scale no objeto
    glTranslatef(4,16,0);
    glScalef(4,4,4);

    // Criando o objeto em triangulos
    glBegin(GL_TRIANGLES);
        for(int i = 0;i < obj_2->quant_lados;i++){
            // Calculando a iluminação
            glm::vec3 cor1 = iluminacao(obj_2->pontos[obj_2->faces[i].id_ponto_1 - 1].normal, obj_2->pontos[obj_2->faces[i].id_ponto_1 - 1].coord, glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
            // Aplicando a cor com a iluminação
            glColor3f(cor1.x,cor1.y,cor1.z);
            // Aplicando a textura de acordo com o objeto
            glTexCoord2f(obj_1->pontos->tex.x, obj_1->pontos->tex.y);
            // Criando os pontos de acordo com o objeto
            glVertex3f(obj_2->pontos[obj_2->faces[i].id_ponto_1-1].coord.x,obj_2->pontos[obj_2->faces[i].id_ponto_1-1].coord.y,obj_2->pontos[obj_2->faces[i].id_ponto_1-1].coord.z);

            // Calculando a iluminação
            glm::vec3 cor2 = iluminacao(obj_2->pontos[obj_2->faces[i].id_ponto_2 - 1].normal,obj_2->pontos[obj_2->faces[i].id_ponto_2 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
            // Aplicando a textura de acordo com o objeto
            glColor3f(cor2.x,cor2.y,cor2.z);
            // Aplicando a textura de acordo com o objeto
            glTexCoord2f(obj_1->pontos->tex.x, obj_1->pontos->tex.y);
            // Criando os pontos de acordo com o objeto
            glVertex3f(obj_2->pontos[obj_2->faces[i].id_ponto_2-1].coord.x,obj_2->pontos[obj_2->faces[i].id_ponto_2-1].coord.y,obj_2->pontos[obj_2->faces[i].id_ponto_2-1].coord.z);

            // Calculando a iluminação
            glm::vec3 cor3 = iluminacao(obj_2->pontos[obj_2->faces[i].id_ponto_3 - 1].normal,obj_2->pontos[obj_2->faces[i].id_ponto_3 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
            // Aplicando a textura de acordo com o objeto
            glColor3f(cor3.x,cor3.y,cor3.z);
            // Aplicando a textura de acordo com o objeto
            glTexCoord2f(obj_1->pontos->tex.x, obj_1->pontos->tex.y);
            // Criando os pontos de acordo com o objeto
            glVertex3f(obj_2->pontos[obj_2->faces[i].id_ponto_3-1].coord.x,obj_2->pontos[obj_2->faces[i].id_ponto_3-1].coord.y,obj_2->pontos[obj_2->faces[i].id_ponto_3-1].coord.z);
        }
    glEnd();

    glPopMatrix();

    // Desativando a textura
    glBindTexture(GL_TEXTURE_2D, 0);
}

// Desenha na tela
void desenha(){
    glViewport(0, 0, janelaLargura, janelaAltura);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glm::mat4 projectionMatrix = glm::perspective(45.0f, aspectRatio, 1.0f, 500.0f);
    glLoadMatrixf(glm::value_ptr(projectionMatrix));

    glMatrixMode(GL_MODELVIEW);

    // Camera
    glm::mat4 cameraMatrix = glm::lookAt(camera, look, glm::vec3(0,0,1));
    glLoadMatrixf(glm::value_ptr(cameraMatrix));

    glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(100,0,0);

        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,100,0);

        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,100);
    glEnd();

    desenha_chao();
    desenhar_obj_1();
    desenhar_obj_2();

    glutSwapBuffers();

}

int main(int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_STENCIL);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Trabalho 2");

    inicio();

    glutReshapeFunc(redimensiona);
    glutKeyboardFunc(teclado);
    glutDisplayFunc(desenha);

    glutMainLoop();

    return 0;
}
