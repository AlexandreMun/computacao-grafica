// OBJETIVO: Executar a aplicação


/*
 * Iago de Aquino Oliveira - 494017
 * José Alexandre Munis Nogueira - 473393
 * Luan de Lima Leandro - 412815
*/

#include <iostream>
#include <GL/gl.h>
#include <GL/glext.h>
#include<GL\glut.h>
#include<math.h>
#include<tabuleiro.h>
#include"leitura.cpp"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "textura.cpp"
#include "pecas.h"
#include "entradas.cpp"

using namespace std;

float w = 1200,h = 600;

glm::vec3 pos_jogador_branco(29,9.5,17); // Posição da camera do jogador 1
glm::vec3 pos_jogador_preto(-12,7.5,17); // Posição da camera do jogador 2
glm::vec3 pos_camera(-12,7.5,17); // Armazena a posição da camera
glm::vec3 look_preto = glm::vec3(7,-2,4);
glm::vec3 look_branco = glm::vec3(9,18,4);
glm::vec3 look(7,-2,4); // Armazena a posição do look da camera

// Variaveis de iluminação
glm::vec3 pos_luz(3,3,5);
glm::vec3 ambiente(0.25f,0.25f,0.25f);
glm::vec3 difusa(1.0f,1.0f,1.0f);
glm::vec3 especular(0.5f,0.5f,0.5f);


void pegar_novo_tamanho(int width, int height){
    w = width;
    h = height;
}
// Calcula a animação do movimento - Parte 3D
void movimento_animado(int v){
    glutTimerFunc(1000.0/FPS,movimento_animado,0);
    glutPostRedisplay();

    // Ativa as animações e movimentos
    if(ativar == 1){

        /* peca.x == 6 => Peão
         * peca.x == 7 => Camera
         * peca.y => posição da peça
         */

        if(peca.x == 6 && peca.y == 1){
            t+= 0.1;

            // Calcula a reta parametrica
            movido->peoes[0].translate = ((1-t)*movido->peoes[0].translate)+(t * mov);
            cout<<t<<endl;

            // Passar turno
            if(t >= 1){
                passar_turno();
            }
        }

        else if(peca.x == 6 && peca.y == 2){
            t+= 0.1;

            // Calcula a reta parametrica
            movido->peoes[1].translate = ((1-t)*movido->peoes[1].translate)+(t * mov);
            cout<<t<<endl;

            // Passar turno
            if(t >= 1){
                passar_turno();
            }
        }

        else if(peca.x == 6 && peca.y == 3){
            t+= 0.1;

            // Calcula a reta parametrica
            movido->peoes[2].translate = ((1-t)*movido->peoes[2].translate)+(t * mov);
            cout<<t<<endl;

            // Passar turno
            if(t >= 1){
                passar_turno();
            }
        }

        else if(peca.x == 6 && peca.y == 4){
            t+= 0.1;

            // Calcula a reta parametrica
            movido->peoes[3].translate = ((1-t)*movido->peoes[3].translate)+(t * mov);
            cout<<t<<endl;

            // Passar turno
            if(t >= 1){
                passar_turno();
            }
        }

        else if(peca.x == 6 && peca.y == 5){
            t+= 0.1;

            // Calcula a reta parametrica
            movido->peoes[4].translate = ((1-t)*movido->peoes[4].translate)+(t * mov);
            cout<<t<<endl;

            // Passar turno
            if(t >= 1){
                passar_turno();
            }
        }

        else if(peca.x == 6 && peca.y == 6){
            t+= 0.1;

            // Calcula a reta parametrica
            movido->peoes[5].translate = ((1-t)*movido->peoes[5].translate)+(t * mov);
            cout<<t<<endl;

            // Passar turno
            if(t >= 1){
                passar_turno();
            }
        }

        else if(peca.x == 6 && peca.y == 7){
            t+= 0.1;

            // Calcula a reta parametrica
            movido->peoes[6].translate = ((1-t)*movido->peoes[6].translate)+(t * mov);
            cout<<t<<endl;

            // Passar turno
            if(t >= 1){
                passar_turno();
            }
        }

        else if(peca.x == 6 && peca.y == 8){
            t+= 0.1;

            // Calcula a reta parametrica
            movido->peoes[7].translate = ((1-t)*movido->peoes[7].translate)+(t * mov);
            cout<<t<<endl;

            // Passar turno
            if(t >= 1){
                passar_turno();
            }
        }

        else if(peca.x == 7 && peca.y == 1){
            t+= 0.1;

            // Calcula a reta parametrica da movimentação da camera
            pos_camera = (1-t)*pos_jogador_preto + (t*pos_jogador_branco);
            look = (1-t)*look_preto + (t*look_branco);

            // Passar turno e desativa a animação
            if(t >= 1){
                ativar = 0;
                t = 0;
            }
        }

        else if(peca.x == 7 && peca.y == 2){
            t+= 0.1;

            // Calcula a reta parametrica da movimentação da camera
            pos_camera = (1-t)*pos_jogador_branco + (t*pos_jogador_preto);
            look = (1-t)*look_branco + (t*look_preto);
            // Passar turno e desativa a animação
            if(t >= 1){
                ativar = 0;
                t = 0;
            }
        }
    }
}

// Calcula a luz e retorna as cores
glm::vec3 aplicar_luz(glm::vec3 normal,glm::vec3 pos,glm::vec3 cor_objeto,glm::vec3 obj_ambiente,glm::vec3 obj_especular,int obj_expoente){
    glm::vec3 lp = normalize(pos_luz-pos);
    glm::vec3 vw = normalize(pos_camera-pos);
    glm::vec3 rf = 2*glm::dot(lp,normal)*normal -lp;
    glm::vec3 ambiente_final = ambiente * obj_ambiente;
    glm::vec3 difusa_final = (difusa * cor_objeto) * glm::dot(normal,lp);
    glm::vec3 especular_final;

    // Caso o escalar seja negativo transforma a especular em 0
    if(glm::dot(vw,rf) < 0){
        especular_final = glm::vec3(0.0f,0.0f,0.0f);
    }
    // Calcula a especular
    else{
        especular_final = especular * obj_especular * (float)pow(glm::dot(vw,rf),obj_expoente);
    }

    // Calcula a luz e retorna
    glm::vec3 resultado_final = ambiente_final+difusa_final+especular_final;
    return resultado_final;
}

// Cria o quadrado e guarda no vetor tabuleiro
void criarTabuleiro(){
    int x = 1, y = 1,z = 0,pos = 0,cont = 0;
    for(int i = 0; i < 8 ;i++){
        for(int j = 0;j < 8;j++){
            Quadrado quadrado;
            if(cont % 2 == 0){
                quadrado.color[0] = 1;
                quadrado.color[1] = 1;
                quadrado.color[2] = 1;
            }else{
                quadrado.color[0] = 0;
                quadrado.color[1] = 0;
                quadrado.color[2] = 0;
            }
            quadrado.pos.x = x;
            quadrado.pos.y = y;
            quadrado.pos.z = z;
            tabuleiro[pos] = quadrado;
            x += 2;
            pos++;
            cont++;
        }
        cont++;
        y +=2;
        x = 1;
    }
}

//
void mostrarTabuleiro(){
    for(int i = 0; i < 64;i++){
        cout<<"(id:"<<i<<")"<<endl;
        cout<< tabuleiro[i].pos.x<<endl;
        cout<< tabuleiro[i].pos.y<<endl;
        cout<< tabuleiro[i].pos.z<<endl;
        cout<<"("<<tabuleiro[i].color[0]<<", "<<tabuleiro[i].color[1]<<", "<<tabuleiro[i].color[2]<<")"<<endl;
    }
}

// Desenha as peças pretas
void desenhar_preto(int pos,int tipo){
    // Verifica o tipo e desenha - Torre
    if(tipo == 1){
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(preto.torres[pos].translate));
        glScalef(3,3,3);

        // Desenha os triangulos dos objetos de acordo com as faces
        glBegin(GL_TRIANGLES);
            // Percorre as faces
            for(int i = 0;i < preto.torres[pos].obj->quant_lados;i++){
                // Calcula a luz
               glm::vec3 cor1 = aplicar_luz(preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_1 - 1].normal,preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               // Aplica a cor
               glColor3f(cor1.x,cor1.y,cor1.z);
               // Cria os vertices de acordo com as faces
               glVertex3f(preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_1-1].coord.x,preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_1-1].coord.y,preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_1-1].coord.z);

               // Calcula a luz
               glm::vec3 cor2 = aplicar_luz(preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_2 - 1].normal,preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               // Aplica a cor
               glColor3f(cor2.x,cor2.y,cor2.z);
               // Cria os vertices de acordo com as faces
               glVertex3f(preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_2-1].coord.x,preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_2-1].coord.y,preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_2-1].coord.z);

               // Calcula a luz
               glm::vec3 cor3 = aplicar_luz(preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_3 - 1].normal,preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               // Aplica a cor
               glColor3f(cor3.x,cor3.y,cor3.z);
               // Cria os vertices de acordo com as faces
               glVertex3f(preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_3-1].coord.x,preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_3-1].coord.y,preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_3-1].coord.z);
            }
        glEnd();
        glPopMatrix();
    }

    // Verifica o tipo e desenha - Cavalo
    else if(tipo == 2){
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(preto.cavalos[pos].translate));
        glScalef(3,3,3);
        glRotatef(180,0,0,1);
        // Desenha os triangulos dos objetos de acordo com as faces
        glBegin(GL_TRIANGLES);
            for(int i = 0;i < preto.cavalos[pos].obj->quant_lados;i++){
               glm::vec3 cor1 = aplicar_luz(preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_1 - 1].normal,preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_1-1].coord.x,preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_1-1].coord.y,preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_2 - 1].normal,preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_2-1].coord.x,preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_2-1].coord.y,preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_3 - 1].normal,preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor3.x,cor3.y,cor3.z);
               glVertex3f(preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_3-1].coord.x,preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_3-1].coord.y,preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_3-1].coord.z);
            }
        glEnd();
        glPopMatrix();
    }

    // Verifica o tipo e desenha - Bispo
    else if(tipo == 3){
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(preto.bispos[pos].translate));
        glScalef(3,3,3);

        // Desenha os triangulos dos objetos de acordo com as faces
        glBegin(GL_TRIANGLES);
            for(int i = 0;i < preto.bispos[pos].obj->quant_lados;i++){
               glm::vec3 cor1 = aplicar_luz(preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_1 - 1].normal,preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_1-1].coord.x,preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_1-1].coord.y,preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_2 - 1].normal,preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_2-1].coord.x,preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_2-1].coord.y,preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_3 - 1].normal,preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor3.x,cor3.y,cor3.z);
               glVertex3f(preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_3-1].coord.x,preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_3-1].coord.y,preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_3-1].coord.z);
            }
        glEnd();
        glPopMatrix();
    }

    // Verifica o tipo e desenha - Rainha
    else if(tipo == 4){
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(preto.rainha.translate));
        glScalef(3,3,3);
        glBegin(GL_TRIANGLES);
            for(int i = 0;i < preto.rainha.obj->quant_lados;i++){
               glm::vec3 cor1 = aplicar_luz(preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_1 - 1].normal,preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_1-1].coord.x,preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_1-1].coord.y,preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_2 - 1].normal,preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_2-1].coord.x,preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_2-1].coord.y,preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_3 - 1].normal,preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor3.x,cor3.y,cor3.z);
               glVertex3f(preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_3-1].coord.x,preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_3-1].coord.y,preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_3-1].coord.z);
            }
        glEnd();
        glPopMatrix();
    }

    // Verifica o tipo e desenha - Rei
    else if(tipo == 5){
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(preto.rei.translate));
        glScalef(3,3,3);
        glBegin(GL_TRIANGLES);
            for(int i = 0;i < preto.rei.obj->quant_lados;i++){
               glm::vec3 cor1 = aplicar_luz(preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_1 - 1].normal,preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_1-1].coord.x,preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_1-1].coord.y,preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_2 - 1].normal,preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_2-1].coord.x,preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_2-1].coord.y,preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_3 - 1].normal,preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor3.x,cor3.y,cor3.z);
               glVertex3f(preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_3-1].coord.x,preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_3-1].coord.y,preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_3-1].coord.z);
            }
        glEnd();
        glPopMatrix();
    }

    // Verifica o tipo e desenha - Peão
    else if(tipo == 6){
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(preto.peoes[pos].translate));
        glScalef(3,3,3);
        glBegin(GL_TRIANGLES);
            for(int i = 0;i < preto.peoes[pos].obj->quant_lados;i++){
               glm::vec3 cor1 = aplicar_luz(preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_1 - 1].normal,preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_1-1].coord.x,preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_1-1].coord.y,preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_2 - 1].normal,preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_2-1].coord.x,preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_2-1].coord.y,preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_3 - 1].normal,preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor3.x,cor3.y,cor3.z);
               glVertex3f(preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_3-1].coord.x,preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_3-1].coord.y,preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_3-1].coord.z);
            }
        glEnd();
        glPopMatrix();
    }
}

// Desenha as peças brancas
void desenhar_branco(int pos,int tipo){
    // Verifica o tipo e desenha - Torre
    if(tipo == 1){
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(branco.torres[pos].translate));
        glScalef(3,3,3);
        glBegin(GL_TRIANGLES);
            for(int i = 0;i < branco.torres[pos].obj->quant_lados;i++){
               glm::vec3 cor1 = aplicar_luz(branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_1 - 1].normal,branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_1-1].coord.x,branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_1-1].coord.y,branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_2 - 1].normal,branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_2-1].coord.x,branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_2-1].coord.y,branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_3 - 1].normal,branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor3.x,cor3.y,cor3.z);
               glVertex3f(branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_3-1].coord.x,branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_3-1].coord.y,branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_3-1].coord.z);
            }
        glEnd();
        glPopMatrix();
    }

    // Verifica o tipo e desenha - Cavalo
    else if(tipo == 2){
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(branco.cavalos[pos].translate));
        glScalef(3,3,3);
        glBegin(GL_TRIANGLES);
            for(int i = 0;i < branco.cavalos[pos].obj->quant_lados;i++){
               glm::vec3 cor1 = aplicar_luz(branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_1 - 1].normal,branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_1-1].coord.x,branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_1-1].coord.y,branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_2 - 1].normal,branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_2-1].coord.x,branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_2-1].coord.y,branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_3 - 1].normal,branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor3.x,cor3.y,cor3.z);
               glVertex3f(branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_3-1].coord.x,branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_3-1].coord.y,branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_3-1].coord.z);
            }
        glEnd();
        glPopMatrix();
    }

    // Verifica o tipo e desenha - Bispo
    else if(tipo == 3){
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(branco.bispos[pos].translate));
        glScalef(3,3,3);
        glBegin(GL_TRIANGLES);
            for(int i = 0;i < branco.bispos[pos].obj->quant_lados;i++){
               glm::vec3 cor1 = aplicar_luz(branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_1 - 1].normal,branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_1-1].coord.x,branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_1-1].coord.y,branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_2 - 1].normal,branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_2-1].coord.x,branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_2-1].coord.y,branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_3 - 1].normal,branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor3.x,cor3.y,cor3.z);
               glVertex3f(branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_3-1].coord.x,branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_3-1].coord.y,branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_3-1].coord.z);
            }
        glEnd();
        glPopMatrix();
    }

    // Verifica o tipo e desenha - Rainha
    else if(tipo == 4){
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(branco.rainha.translate));
        glScalef(3,3,3);
        glBegin(GL_TRIANGLES);
            for(int i = 0;i < branco.rainha.obj->quant_lados;i++){
               glm::vec3 cor1 = aplicar_luz(branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_1 - 1].normal,branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_1-1].coord.x,branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_1-1].coord.y,branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_2 - 1].normal,branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_2-1].coord.x,branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_2-1].coord.y,branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_3 - 1].normal,branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor3.x,cor3.y,cor3.z);
               glVertex3f(branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_3-1].coord.x,branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_3-1].coord.y,branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_3-1].coord.z);
            }
        glEnd();
        glPopMatrix();
    }

    // Verifica o tipo e desenha - Rei
    else if(tipo == 5){
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(branco.rei.translate));
        glScalef(3,3,3);
        glBegin(GL_TRIANGLES);
            for(int i = 0;i < branco.rei.obj->quant_lados;i++){
               glm::vec3 cor1 = aplicar_luz(branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_1 - 1].normal,branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_1-1].coord.x,branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_1-1].coord.y,branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_2 - 1].normal,branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_2-1].coord.x,branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_2-1].coord.y,branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_3 - 1].normal,branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor3.x,cor3.y,cor3.z);
               glVertex3f(branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_3-1].coord.x,branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_3-1].coord.y,branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_3-1].coord.z);
            }
        glEnd();
        glPopMatrix();
    }

    // Verifica o tipo e desenha - Peão
    else if(tipo == 6){
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(branco.peoes[pos].translate));
        glScalef(3,3,3);
        glBegin(GL_TRIANGLES);
            for(int i = 0;i < branco.peoes[pos].obj->quant_lados;i++){
               glm::vec3 cor1 = aplicar_luz(branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_1 - 1].normal,branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_1-1].coord.x,branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_1-1].coord.y,branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_2 - 1].normal,branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_2-1].coord.x,branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_2-1].coord.y,branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_3 - 1].normal,branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor3.x,cor3.y,cor3.z);
               glVertex3f(branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_3-1].coord.x,branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_3-1].coord.y,branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_3-1].coord.z);
            }
        glEnd();
        glPopMatrix();
    }
}

// Inicializa
void inicializar(){
    glEnable(GL_TEXTURE_2D);
    glClearColor(0.5,0.5,0.5,1);
    glPointSize(10);
    glLineWidth(5);

    // Inicializa as peças
    branco = iniciar_branco();
    preto = iniciar_preto();

    // Cria o tabuleiro
    criarTabuleiro();
    iniciar_2D();
    //mostrarTabuleiro();

    // Carrega as texturas
    carregar_textura();
}

// Desenha o tabuleiro 3D
void desenhar_tabuleiro(){
    glBindTexture(GL_TEXTURE_2D,id);
    for(int i = 0;i<64;i++){
        glBegin(GL_QUADS);
            glm::vec3 cor1 = aplicar_luz(glm::vec3(0,0,1),glm::vec3(tabuleiro[i].pos.x-1,tabuleiro[i].pos.y+1,tabuleiro[i].pos.z),glm::vec3(tabuleiro[i].color[0],tabuleiro[i].color[1],tabuleiro[i].color[2]),glm::vec3(0.2,0.2,0.2),glm::vec3(0.7,0.7,0.7),1);
            glColor3f(cor1.x,cor1.y,cor1.z);
            glTexCoord2f(0,1);
            glVertex3f(tabuleiro[i].pos.x-1,tabuleiro[i].pos.y+1,tabuleiro[i].pos.z);

            glm::vec3 cor2 = aplicar_luz(glm::vec3(0,0,1),glm::vec3(tabuleiro[i].pos.x+1,tabuleiro[i].pos.y+1,tabuleiro[i].pos.z),glm::vec3(tabuleiro[i].color[0],tabuleiro[i].color[1],tabuleiro[i].color[2]),glm::vec3(0.2,0.2,0.2),glm::vec3(0.7,0.7,0.7),1);
            glColor3f(cor2.x,cor2.y,cor2.z);
            glTexCoord2f(1,1);
            glVertex3f(tabuleiro[i].pos.x+1,tabuleiro[i].pos.y+1,tabuleiro[i].pos.z);

            glm::vec3 cor3 = aplicar_luz(glm::vec3(0,0,1),glm::vec3(tabuleiro[i].pos.x+1,tabuleiro[i].pos.y-1,tabuleiro[i].pos.z),glm::vec3(tabuleiro[i].color[0],tabuleiro[i].color[1],tabuleiro[i].color[2]),glm::vec3(0.2,0.2,0.2),glm::vec3(0.7,0.7,0.7),1);
            glColor3f(cor3.x,cor3.y,cor3.z);
            glTexCoord2f(1,0);
            glVertex3f(tabuleiro[i].pos.x+1,tabuleiro[i].pos.y-1,tabuleiro[i].pos.z);

            glm::vec3 cor4 = aplicar_luz(glm::vec3(0,0,1),glm::vec3(tabuleiro[i].pos.x-1,tabuleiro[i].pos.y-1,tabuleiro[i].pos.z),glm::vec3(tabuleiro[i].color[0],tabuleiro[i].color[1],tabuleiro[i].color[2]),glm::vec3(0.2,0.2,0.2),glm::vec3(0.7,0.7,0.7),1);
            glColor3f(cor4.x,cor4.y,cor4.z);
            glTexCoord2f(0,0);
            glVertex3f(tabuleiro[i].pos.x-1,tabuleiro[i].pos.y-1,tabuleiro[i].pos.z);
        glEnd();
    }
    glBindTexture(GL_TEXTURE_2D,0);
}

// Desenha o tabuleiro 2D
void desenhar_tabuleiro_2D(){
    for(int i = 0;i<64;i++){
        glBegin(GL_QUADS);
            glColor3f(tabuleiro[i].color[0],tabuleiro[i].color[1],tabuleiro[i].color[2]);
            glVertex2f(tabuleiro[i].pos.x-1,tabuleiro[i].pos.y+1);
            glVertex2f(tabuleiro[i].pos.x+1,tabuleiro[i].pos.y+1);
            glVertex2f(tabuleiro[i].pos.x+1,tabuleiro[i].pos.y-1);
            glVertex2f(tabuleiro[i].pos.x-1,tabuleiro[i].pos.y-1);
            if(tabuleiro[i].situacao == 1){
                glColor3f(1,0,0);
                glVertex2f(tabuleiro[i].pos.x-0.5,tabuleiro[i].pos.y);
                glVertex2f(tabuleiro[i].pos.x,tabuleiro[i].pos.y+0.5);
                glVertex2f(tabuleiro[i].pos.x+0.5,tabuleiro[i].pos.y);
                glVertex2f(tabuleiro[i].pos.x,tabuleiro[i].pos.y-0.5);
            }
        glEnd();
    }
    glutPostRedisplay();
}

// Desenha as peças no tabuleiro 3D de ambos os lados
void desenhar_pecas(){
    int tipo; // => tipo da peça

    /* 1 = Torre
     * 2 = Cavalo
     * 3 = Bispo
     * 4 = Rainha
     * 5 = Rei
     * 6 = Peão
     */

    // Desenha da torre ao bispo
    for(tipo = 1;tipo<4;tipo++){
        for(int i =0;i<2;i++){
            // Chama a função de desenhar
            desenhar_branco(i,tipo);
            desenhar_preto(i,tipo);
        }
    }

    // Desenha o rei e a rainha
    for(tipo = 4;tipo<6;tipo++){
        for(int i =0;i<1;i++){
            // Chama a função de desenhar
            desenhar_branco(i,tipo);
            desenhar_preto(i,tipo);
        }
    }

    // Desenha os peões
    tipo = 6;
    for(int i =0;i<8;i++){
        // Chama a função de desenhar
        desenhar_branco(i,tipo);
        desenhar_preto(i,tipo);
    }
}

// Pega a posição clicada no tabuleiro 2D
void pegar_click(int button,int status, int x,int y){
    // Converte a coordenada do pixel para coordenada x e y
    float xFinal = (float)(16*x)/(w/2);
    float yFinal = (float)(16*(h-y))/h;

    if(button == GLUT_LEFT_BUTTON && status == GLUT_UP && xFinal < 16){
        bool moveu;
        // Se está selecionado
        if(foiSelecionado == 1){
            // seleciona os possiveis quadrados para se mover
            moveu = selecionar_possivel(xFinal,yFinal);

            // Caso clique em um quadrado que não é possível se mover
            if(!moveu){
                cout<<"errou";
                selecionado = pegar_quadrado(xFinal,yFinal);
                quant_possivel = 0;

                // Seleciona o quadrado depois de ter selecionado outro
                if(selecionado->situacao == 1){
                    buscar_possiveis(selecionado);
                }
            }
        }

        // Se não está selecionado
        else if(foiSelecionado == 0){
            // Seleciona o quadrado
            selecionado = pegar_quadrado(xFinal,yFinal);
            // Seleciona o quadrado antes de ter selecionado outro
            if(selecionado->situacao == 1){
                buscar_possiveis(selecionado);
            }
        }
    }
 }

void desenhar(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0,0,w/2,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,17.0,0,16.0,-1,1);

    // Desenha o tabuleiro 2D
    desenhar_tabuleiro_2D();

    // Cria as bordas no quadrado selecionado
    if(foiSelecionado == 1){
        glLineWidth(5);
        glBegin(GL_LINES);
            glColor3f(1,1,0.2);
            glVertex2f(selecionado->pos.x-1,selecionado->pos.y+1);
            glVertex2f(selecionado->pos.x+1,selecionado->pos.y+1);
            glVertex2f(selecionado->pos.x+1,selecionado->pos.y+1);
            glVertex2f(selecionado->pos.x+1,selecionado->pos.y-1);
            glVertex2f(selecionado->pos.x+1,selecionado->pos.y-1);
            glVertex2f(selecionado->pos.x-1,selecionado->pos.y-1);
            glVertex2f(selecionado->pos.x-1,selecionado->pos.y-1);
            glVertex2f(selecionado->pos.x-1,selecionado->pos.y+1);
        glEnd();
    }

    // Cria as bordas nos quadrados possíveis
    if(quant_possivel > 0){
        for(int i = 0;i< quant_possivel;i++){
            glBegin(GL_LINES);
                glColor3f(1,1,0.2);
                glVertex2f(possiveis[i]->pos.x-1,possiveis[i]->pos.y+1);
                glVertex2f(possiveis[i]->pos.x+1,possiveis[i]->pos.y+1);
                glVertex2f(possiveis[i]->pos.x+1,possiveis[i]->pos.y+1);
                glVertex2f(possiveis[i]->pos.x+1,possiveis[i]->pos.y-1);
                glVertex2f(possiveis[i]->pos.x+1,possiveis[i]->pos.y-1);
                glVertex2f(possiveis[i]->pos.x-1,possiveis[i]->pos.y-1);
                glVertex2f(possiveis[i]->pos.x-1,possiveis[i]->pos.y-1);
                glVertex2f(possiveis[i]->pos.x-1,possiveis[i]->pos.y+1);
            glEnd();
        }
    }

    glViewport(w/2,0,w,h);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90,1,1,40);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    // Troca o look da camera
    if(turno == 2){

    }else{

    }

    // Dados da cemera
    glm::mat4 camera = glm::lookAt(pos_camera,
                                   look,
                                   glm::vec3(0,0,1));

    glLoadMatrixf(glm::value_ptr(camera));

    // Desenhas eixos
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

    // Desenha o tabuleiro e peças do 3D
    desenhar_tabuleiro();
    desenhar_pecas();

    glDisable(GL_DEPTH_TEST);
    glPopMatrix();

    glFlush();
}

int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100,20);
    glutInitWindowSize(1200,600);

    glutCreateWindow("Xadrez");

    inicializar();
    glutDisplayFunc(desenhar);
    glutMouseFunc(pegar_click);
    glutReshapeFunc(pegar_novo_tamanho);
    glutTimerFunc(1000/FPS,movimento_animado,0);

    glutMainLoop();
}
