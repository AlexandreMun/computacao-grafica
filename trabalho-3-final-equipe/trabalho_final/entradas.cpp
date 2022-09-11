// OBJETIVO: Captar os dados do usuario e mover as peças - Parte 2D

#include <iostream>
#include <GL/gl.h>
#include <GL/glext.h>
#include<GL\glut.h>
#include<math.h>
#include<tabuleiro.h>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "pecas.h"
#include "iniciar_jogo.cpp"

#define FPS 60

using namespace std;

Quadrado * selecionado;
int ativar = 0; // se for = 1, ativa as animações e movimentos
Jogador* movido;
glm::mat4 matriz_identidade(1);
glm::mat4 mov;
glm::vec2 peca; // x guarda o tipo do movimento e y guarda a posição da peça, no caso o peão
float t;
int turno = 2;
int foiSelecionado = 0;
Quadrado* possiveis[64]; // guarda todos os quadrados em que a peça pode se mover
int quant_possivel = 0; // guarda a caminho que o quadrado se move

// Responsavel por passar o turno e ativar a movimentação da camera
void passar_turno(){
    if(turno == 2){
        turno = 1;
        ativar = 1;
        t = 0;
        peca = glm::vec2(7,1); // Define o tipo como camera
    }else{
        turno = 2;
        ativar = 1;
        t = 0;
        peca = glm::vec2(7,2); // Define o tipo como camera
    }
}

// Recebe a posição x e y que o usuario clicou
void movimentar(float x, float y){
    // Peão
    // Vez do jogador 2 - preto
    if(selecionado->jogador_ocupando == 2){
        // busca o quadrado clicado e verifica o que está ocupado
        if(selecionado->peca_ocupada.x == 6 && selecionado->peca_ocupada.y == 1){
            movido = &preto;
            // matriz de translação para a nova posição - move a peça
            mov = glm::translate(matriz_identidade,glm::vec3(x,y,0));
            //guarda a peça que está sendo movida
            peca = glm::vec2(6,1);
            ativar = 1;
        }

        // busca o quadrado clicado e verifica o que está está ocupado
        else if(selecionado->peca_ocupada.x == 6 && selecionado->peca_ocupada.y == 2){
            movido = &preto;
            // matriz de translação para a nova posição - move a peça
            mov = glm::translate(matriz_identidade,glm::vec3(x,y,0));
            peca = glm::vec2(6,2);
            ativar = 1;
        }

        // busca o quadrado clicado e verifica o que está está ocupado
        else if(selecionado->peca_ocupada.x == 6 && selecionado->peca_ocupada.y == 3){
            movido = &preto;
            // matriz de translação para a nova posição - move a peça
            mov = glm::translate(matriz_identidade,glm::vec3(x,y,0));
            peca = glm::vec2(6,3);
            ativar = 1;
        }

        // busca o quadrado clicado e verifica o que está está ocupado
        else if(selecionado->peca_ocupada.x == 6 && selecionado->peca_ocupada.y == 4){
            movido = &preto;
            // matriz de translação para a nova posição - move a peça
            mov = glm::translate(matriz_identidade,glm::vec3(x,y,0));
            //guarda a peça que está sendo movida
            peca = glm::vec2(6,4);
            ativar = 1;
        }

        // busca o quadrado clicado e verifica o que está está ocupado
        else if(selecionado->peca_ocupada.x == 6 && selecionado->peca_ocupada.y == 5){
            movido = &preto;
            // matriz de translação para a nova posição - move a peça
            mov = glm::translate(matriz_identidade,glm::vec3(x,y,0));
            //guarda a peça que está sendo movida
            peca = glm::vec2(6,5);
            ativar = 1;
        }

        // busca o quadrado clicado e verifica o que está está ocupado
        else if(selecionado->peca_ocupada.x == 6 && selecionado->peca_ocupada.y == 6){
            movido = &preto;
            // matriz de translação para a nova posição - move a peça
            mov = glm::translate(matriz_identidade,glm::vec3(x,y,0));
            //guarda a peça que está sendo movida
            peca = glm::vec2(6,6);
            ativar = 1;
        }

        // busca o quadrado clicado e verifica o que está está ocupado
        else if(selecionado->peca_ocupada.x == 6 && selecionado->peca_ocupada.y == 7){
            movido = &preto;
            // matriz de translação para a nova posição - move a peça
            mov = glm::translate(matriz_identidade,glm::vec3(x,y,0));
            //guarda a peça que está sendo movida
            peca = glm::vec2(6,7);
            ativar = 1;
        }

        // busca o quadrado clicado e verifica o que está está ocupado
        else if(selecionado->peca_ocupada.x == 6 && selecionado->peca_ocupada.y == 8){
            movido = &preto;
            // matriz de translação para a nova posição - move a peça
            mov = glm::translate(matriz_identidade,glm::vec3(x,y,0));
            //guarda a peça que está sendo movida
            peca = glm::vec2(6,8);
            ativar = 1;
        }
    }

    // Vez do jogador 1 - branco
    if(selecionado->jogador_ocupando == 1){
        // busca o quadrado clicado e verifica o que está está ocupado
        if(selecionado->peca_ocupada.x == 6 && selecionado->peca_ocupada.y == 1){
            movido = &branco;
            // matriz de translação para a nova posição - move a peça
            mov = glm::translate(matriz_identidade,glm::vec3(x,y,0));
            //guarda a peça que está sendo movida
            peca = glm::vec2(6,1);
            ativar = 1;
        }

        // busca o quadrado clicado e verifica o que está está ocupado
        else if(selecionado->peca_ocupada.x == 6 && selecionado->peca_ocupada.y == 2){
            movido = &branco;
            // matriz de translação para a nova posição - move a peça
            mov = glm::translate(matriz_identidade,glm::vec3(x,y,0));
            //guarda a peça que está sendo movida
            peca = glm::vec2(6,2);
            ativar = 1;
        }

        // busca o quadrado clicado e verifica o que está está ocupado
        else if(selecionado->peca_ocupada.x == 6 && selecionado->peca_ocupada.y == 3){
            movido = &branco;
            // matriz de translação para a nova posição - move a peça
            mov = glm::translate(matriz_identidade,glm::vec3(x,y,0));
            //guarda a peça que está sendo movida
            peca = glm::vec2(6,3);
            ativar = 1;
        }

        // busca o quadrado clicado e verifica o que está está ocupado
        else if(selecionado->peca_ocupada.x == 6 && selecionado->peca_ocupada.y == 4){
            movido = &branco;
            // matriz de translação para a nova posição - move a peça
            mov = glm::translate(matriz_identidade,glm::vec3(x,y,0));
            //guarda a peça que está sendo movida
            peca = glm::vec2(6,4);
            ativar = 1;
        }

        // busca o quadrado clicado e verifica o que está está ocupado
        else if(selecionado->peca_ocupada.x == 6 && selecionado->peca_ocupada.y == 5){
            movido = &branco;
            // matriz de translação para a nova posição - move a peça
            mov = glm::translate(matriz_identidade,glm::vec3(x,y,0));
            //guarda a peça que está sendo movida
            peca = glm::vec2(6,5);
            ativar = 1;
        }

        // busca o quadrado clicado e verifica o que está está ocupado
        else if(selecionado->peca_ocupada.x == 6 && selecionado->peca_ocupada.y == 6){
            movido = &branco;
            // matriz de translação para a nova posição - move a peça
            mov = glm::translate(matriz_identidade,glm::vec3(x,y,0));
            //guarda a peça que está sendo movida
            peca = glm::vec2(6,6);
            ativar = 1;
        }

        // busca o quadrado clicado e verifica o que está está ocupado
        else if(selecionado->peca_ocupada.x == 6 && selecionado->peca_ocupada.y == 7){
            movido = &branco;
            // matriz de translação para a nova posição - move a peça
            mov = glm::translate(matriz_identidade,glm::vec3(x,y,0));
            //guarda a peça que está sendo movida
            peca = glm::vec2(6,7);
            ativar = 1;
        }

        // busca o quadrado clicado e verifica o que está está ocupado
        else if(selecionado->peca_ocupada.x == 6 && selecionado->peca_ocupada.y == 8){
            movido = &branco;
            // matriz de translação para a nova posição - move a peça
            mov = glm::translate(matriz_identidade,glm::vec3(x,y,0));
            //guarda a peça que está sendo movida
            peca = glm::vec2(6,8);
            ativar = 1;
        }
    }

    glutPostRedisplay();
}

// checa se clicou no quadrado
bool checar_pontos_quadrado(float x_quadrado,float y_quadrado,float x_peca,float y_peca){
    if(x_quadrado - 1.0 <= x_peca && x_quadrado + 1.0 >= x_peca && y_quadrado - 1.0 <= y_peca && y_quadrado + 1.0 >= y_peca){
        return true;
    }
    return false;
}

// seleciona e retorna o quadrado clicado
Quadrado* pegar_quadrado(float x,float y){
    for(int i = 0;i < 64;i++){
        if(checar_pontos_quadrado(tabuleiro[i].pos.x,tabuleiro[i].pos.y,x,y)){
            foiSelecionado = 1;
            return &tabuleiro[i];
        }
    }
}

// testa se o quadrado clicado é possível se mover
bool selecionar_possivel(float x,float y){
    for(int i = 0;i < quant_possivel;i++){
        // testa o ponto clicado
        if(checar_pontos_quadrado(possiveis[i]->pos.x,possiveis[i]->pos.y,x,y)){
            // move para a nova posição
            possiveis[i]->situacao = selecionado->situacao;
            possiveis[i]->peca_ocupada = selecionado->peca_ocupada;
            possiveis[i]->jogador_ocupando = selecionado->jogador_ocupando;
            // chama a função para fazer a animação
            movimentar(possiveis[i]->pos.x,possiveis[i]->pos.y);

            // torna o quadrado em que a peça estava vazio
            selecionado->situacao = 0;
            selecionado->peca_ocupada = glm::vec2(0,0);
            selecionado->jogador_ocupando = 0;
            foiSelecionado = 0;
            quant_possivel = 0;

            return true;
        }
    }

    return false;

    glutPostRedisplay();
}

// busca as coordenadas exatas do quadrado dentro do vetor
Quadrado* buscar_quadrado_preciso(float x,float y){
    Quadrado* quadrado;
    for(int i = 0;i<64;i++){
        if(tabuleiro[i].pos.x == x && tabuleiro[i].pos.y == y){
           if(tabuleiro[i].situacao == 0){
              quadrado = &tabuleiro[i];
           }else{
               return NULL;
           }
        }
    }
    return quadrado;
}

// guarda os quadrados possíveis de se mover
void buscar_possiveis(Quadrado* selecionado){
    // vez do jogador 1 - branco
    if(turno == 1){
        if(selecionado->jogador_ocupando == 1){
            int xAtual = selecionado->pos.x;
            int yAtual = selecionado->pos.y;
            if(selecionado->peca_ocupada.x == 6){
                for(int i = 0;i < 2;i++){
                    xAtual -= 2;
                    Quadrado* possivel = buscar_quadrado_preciso(xAtual,yAtual);
                    if(possivel != NULL){
                        possiveis[quant_possivel] = possivel;
                        quant_possivel++;
                    }else{
                        break;
                    }
                }
            }
        }
    }

    // vez do jogador 2 - preto
    else if(turno == 2){
        if(selecionado->jogador_ocupando == 2){
            int xAtual = selecionado->pos.x;
            int yAtual = selecionado->pos.y;
            if(selecionado->peca_ocupada.x == 6){
                for(int i = 0;i < 2;i++){
                    xAtual += 2;
                    Quadrado* possivel = buscar_quadrado_preciso(xAtual,yAtual);
                    if(possivel != NULL){
                        possiveis[quant_possivel] = possivel;
                        quant_possivel++;
                    }else{
                        break;
                    }
                }
            }
        }
    }
}
