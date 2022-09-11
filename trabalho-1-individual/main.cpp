// José Alexandre Munis Nogueira - 473393

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <stdio.h>
#include <iostream>
#include <ostream>
#include <math.h>
#include <ctime>
#include <vector>

using namespace std;

// Variaveis da tela
int largura, altura;

// Variaveis do Quadrado e Cubo
bool tela_quad_cubo = false;
bool selecionado_quad_cubo = false;
float posx_quad_cubo = 0;
float posy_quad_cubo = 0;
float w_quad_cubo = 0;
float h_quad_cubo = 0;
float translatex_2d = 0;
float translatey_2d = 0;
float translatex_3d = 0;
float translatey_3d = 0;
float r_quad_cubo = 1;
float g_quad_cubo = 0;
float b_quad_cubo = 0;

void inicio(){
    glClearColor(0.5, 0.5, 0.5, 1);
}

// Retorna o tamanho da janela
void resize(int w, int h) {
    largura = w;
    altura = h;
    glutPostRedisplay();
}

// Mapeamento do teclado
void teclado(unsigned char key, int x, int y){
    if(selecionado_quad_cubo == true) {
        switch(key){
        // Movimentação do quadrado e cubo
        case 'w':
            translatex_3d -= 2;
            translatey_2d += 1;
            break;

        case 'a':
            translatey_3d += 2;
            translatex_2d -= 1;
            break;

        case 's':
            translatex_3d += 2;
            translatey_2d -= 1;
            break;

        case 'd':
            translatey_3d -= 2;
            translatex_2d += 1;
            break;


            // Faz Quadrado e Cubo aparecem
        case 'z':
            // Verifica se está na tela
            if(tela_quad_cubo == false) {
                tela_quad_cubo = true;
                // Define as coordenadas
                posx_quad_cubo = (rand()%7)+1;
                posy_quad_cubo = (rand()%7)+1;
                w_quad_cubo = 1;
                h_quad_cubo = 1;
            }
            else {
                tela_quad_cubo = false;
                // Define as coordenadas
                w_quad_cubo = 0;
                h_quad_cubo = 0;
            }
            break;

            // Cores de 1 até 9, muda as variaveis do glcolor
        case '1':
            r_quad_cubo = 1; g_quad_cubo = 0; b_quad_cubo = 0; break;
        case '2':
            r_quad_cubo = 0; g_quad_cubo = 1; b_quad_cubo = 0; break;
        case '3':
            r_quad_cubo = 0; g_quad_cubo = 0; b_quad_cubo = 1; break;
        case '4':
            r_quad_cubo = 1; g_quad_cubo = 1; b_quad_cubo = 0; break;
        case '5':
            r_quad_cubo = 1; g_quad_cubo = 0; b_quad_cubo = 1; break;
        case '6':
            r_quad_cubo = 0; g_quad_cubo = 1; b_quad_cubo = 1; break;
        case '7':
            r_quad_cubo = 1; g_quad_cubo = 0.6; b_quad_cubo = 0.7; break;
        case '8':
            r_quad_cubo = 0.6; g_quad_cubo = 0.2; b_quad_cubo = 1; break;
        case '9':
            r_quad_cubo = 0.4; g_quad_cubo = 0.3; b_quad_cubo = 1; break;

        }
    }
    glutPostRedisplay();
}

// Mapeamento do mouse
void mouse(int button, int state, int mousex, int mousey) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

        int * i = new int[1];
        // Pega as coordenadas em pixels onde o cursor está
        glReadPixels(mousex, mousey, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, i);

        if (i[0] == 1) {
            selecionado_quad_cubo = !selecionado_quad_cubo;
            //            if (selecionado_quad_cubo) {
            //                g_quad_cubo = 1.0f;
            //            }
            //            else {
            //                g_quad_cubo = 0.0f;
            //            }
        }
        delete i;
    }

    glutPostRedisplay();
}

// Define as configurações da comera
void camera_3d() {
    float eixox = translatex_3d;
    float eixoz = translatey_3d;

    // Configurações principais
    glm::mat4 cameraMatrix = glm::lookAt(glm::vec3(13, 0, -15),  // eye
                                         glm::vec3(0 + eixox, 0, -4  + eixoz), // at
                                         glm::vec3(0, 1, 0)); // up

    // Substitui a matriz
    glLoadMatrixf(glm::value_ptr(cameraMatrix));

    // Aplica transformações
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0,0,-5));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-4,-2,-9));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(1,0,0));

    // Multiplica a matriz
    glMultMatrixf(glm::value_ptr(modelMatrix));
}

// Criar o tabuleiro 2D
void tabuleiro_2d() {
    // Dois for de 8 para criar os quadrados do tabuleiro
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            // Definir cor
            if((i + j) % 2 == 0) {
                glColor3f(0, 0, 0);
            }
            else {
                glColor3f(1, 1, 1);
            }


            // Cria o quadrado
            glBegin(GL_QUADS);
            glVertex2f(i, j+1);
            glVertex2f(i+1, j+1);
            glVertex2f(i+1, j);
            glVertex2f(i, j);
            glEnd();
        }
    }
}

// Criar o tabuleiro 3D
void tabuleiro_3d() {
    // Dois for de 8 para criar os quadrados do tabuleiro
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            // Definir cor
            if((i + j) % 2 == 0) {
                glColor3f(0, 0, 0);
            }
            else {
                glColor3f(1, 1, 1);
            }

            // Escala de 2 e cria o quadrado
            glPushMatrix();
            glScalef(2,2,1);

            glBegin(GL_QUADS);
            glVertex2f(i, j+1);
            glVertex2f(i+1, j+1);
            glVertex2f(i+1, j);
            glVertex2f(i, j);
            glEnd();

            glPopMatrix();
        }
    }
}

// Cria quadrado 2D
void quadrado_2d() {
    glStencilFunc(GL_ALWAYS, 1, -1);

    glPushMatrix();

    // Define a cor e a tranalação para movimentar
    glTranslatef(translatex_2d, translatey_2d, 0);
    glColor3f(r_quad_cubo, g_quad_cubo, b_quad_cubo);

    // Cria quadrado
    glBegin(GL_QUADS);
    glVertex2f(posx_quad_cubo,             posy_quad_cubo            );
    glVertex2f(posx_quad_cubo+w_quad_cubo, posy_quad_cubo            );
    glVertex2f(posx_quad_cubo+w_quad_cubo, posy_quad_cubo+h_quad_cubo);
    glVertex2f(posx_quad_cubo,             posy_quad_cubo+h_quad_cubo);
    glEnd();

    glPopMatrix();
}

// Cria Triangulo 2D
void triangulo_2d() {
    glPushMatrix();
    glColor3f(0, 0, 1);

    // Cria quadrado
    glBegin(GL_TRIANGLES);
    glVertex2f(1, 1);
    glVertex2f(2, 1);
    glVertex2f(1.5, 2);
    glEnd();

    glPopMatrix();
}

// Cria Circulo 2D
void circulo_2d() {
    float theta;

    glPushMatrix();
    glColor3d(0, 1, 0);

    glBegin(GL_POLYGON);

    for(int i = 0; i < 360; i++) {
        theta = i * 3.142/180;
        glVertex2f(cos(theta), sin(theta));
    }

    glEnd();
    glPopMatrix();
}

// Cria o Cubo 3D
void cubo_3d() {
    glPushMatrix();
    glTranslatef(translatex_3d,translatey_3d,0);
    glTranslatef(9, 14, 0);
    //    glRotatef(60, 0, 0, 1);

    glColor3f(r_quad_cubo, g_quad_cubo, b_quad_cubo);

    glBegin(GL_QUADS);
    // Face 1
    glVertex3f( -1, 1, 1);
    glVertex3f( 1, 1, 1);
    glVertex3f( 1, 1, -1);
    glVertex3f( -1, 1, -1);

    // Face 2
    glVertex3f( -1, -1, -1);
    glVertex3f( 1, -1, -1);
    glVertex3f( 1, 1, -1);
    glVertex3f( -1, 1, -1);

    // Face 3
    glVertex3f( 1, -1, -1);
    glVertex3f( 1, -1, 1);
    glVertex3f( 1, 1, 1);
    glVertex3f( 1, 1, -1);

    // Face 4
    glVertex3f( -1, 1, 1);
    glVertex3f( 1, 1, 1);
    glVertex3f( 1, -1, 1);
    glVertex3f( -1, -1, 1);

    // Face 5
    glVertex3f( -1, 1, -1);
    glVertex3f( -1, 1, 1);
    glVertex3f( -1, -1, 1);
    glVertex3f( -1, -1, -1);

    // Face 6
    glVertex3f( -1, -1, 1);
    glVertex3f( 1, -1, 1);
    glVertex3f( 1, -1, -1);
    glVertex3f( -1, -1, -1);

    glEnd();
    glPopMatrix();
}

void piramide_3d() {
    glPushMatrix();
    glTranslatef(9, 9, 0);
    glRotatef(-90, 1, 0, 0);
    glColor3f(0, 0, 1);
    glBegin(GL_TRIANGLES);

    // Face 1
    glVertex3f( 0, 1, 0);
    glVertex3f( -1, -1, 1);
    glVertex3f( 1, -1, 1);

    // Face 2
    glVertex3f( 0, 1, 0);
    glVertex3f( 1, -1, 1);
    glVertex3f( 1, -1, -1);

    // Face 3
    glVertex3f( 0, 1, 0);
    glVertex3f( 1, -1, -1);
    glVertex3f( -1, -1, -1);

    // Face 4
    glVertex3f( 0, 1, 0);
    glVertex3f( -1, -1, -1);
    glVertex3f( -1, -1, 1);

    glEnd();
    glPopMatrix();
}

void cilindro_3d(){
    glTranslatef(2, 9, 0);
    glColor3f(0, 1, 0);

    float angulo, delta, x, y;

    delta = 2.0 * M_PI/20;

    // Circulo de cima
    glBegin(GL_TRIANGLE_FAN);
    // z=1 para a parte de cima
    glVertex3f(0, 0, 1);

    for(int i = 0; i <= 20; i++){
        angulo = i*delta;
        x = 1 * cos(angulo);
        y = 1 * sin(angulo);

        glVertex3f(x, y, 1);
    }
    glEnd();

    //Circulo de baixo
    glBegin(GL_TRIANGLE_FAN);
    //z=0 para a parte de baixo
    glVertex3f(0, 0, 0);

    for(int i = 20; i >= 0; i--){
        angulo = i*delta;
        x = 1 * cos(angulo);
        y = 1 * sin(angulo);

        glVertex3f(x, y, 0);
    }
    glEnd();


    // Lateral - Pega as coordenadas das partes de cima e baixo e alterna
    glBegin(GL_TRIANGLE_STRIP);
    for(int i = 0; i <= 20; i++){
        angulo = i * delta;
        x = 1 * cos(angulo);
        y = 1 * sin(angulo);

        // Circulo de cima
        glVertex3f(x, y, 1);
        // Circulo de Baixo
        glVertex3f(x, y, 0);
    }
    glEnd();
}

void desenha(){
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearStencil(0);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    // Redimensiona a janela em relação a altura
    float h = 16.0 * altura/(largura+160);

    // 2D
    glViewport(0, 0, largura/2, altura);
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 8, 0, h, -1, 1);


    tabuleiro_2d();
    quadrado_2d();
    glPopMatrix();

    // 3D
    glViewport(largura/2, 0, largura/2, altura);

    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 2,  100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    camera_3d();
    tabuleiro_3d();
    cubo_3d();
    piramide_3d();
    cilindro_3d();

    glPopMatrix();

    glutSwapBuffers();

}

int main(int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_STENCIL);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Janela");

    inicio();

    glutReshapeFunc(resize);
    glutDisplayFunc(desenha);
    glutKeyboardFunc(teclado);
    glutMouseFunc(mouse);

    glutMainLoop();

    return 0;
}
