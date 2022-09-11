// OBJETIVO: Iniciar os jogo e guardar as posições e objetos de cada peça

#include<iostream>
#include "objeto.h"
#include <GL/gl.h>
#include <GL/glext.h>
#include<GL\glut.h>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "pecas.h"
#include "leitura.cpp"
#include "tabuleiro.h"

// Guarda as posições do tabuleiro
Quadrado tabuleiro[64];

// Coloca as peças branças no tabuleiro 3D em cada posição
Jogador iniciar_branco(){
    jogador branco;
    glm::mat4 matriz_identidade(1);

    Objeto* torre_1 = ler_arquivo("twe.obj");
    Torre torre;
    torre.obj = torre_1;
    torre.translate = glm::translate(matriz_identidade,glm::vec3(15,1,0));
    branco.torres[0] = torre;

    Objeto* cavalo_1 = ler_arquivo("vavalo.obj");
    Cavalo cavalo;
    cavalo.obj = cavalo_1;
    cavalo.translate = glm::translate(matriz_identidade,glm::vec3(15,3,0));
    branco.cavalos[0] = cavalo;

    Objeto* bispo_1 = ler_arquivo("bispo.obj");
    Bispo bispo;
    bispo.obj = bispo_1;
    bispo.translate = glm::translate(matriz_identidade,glm::vec3(15,5,0));
    branco.bispos[0] = bispo;

    Objeto* rainha_ = ler_arquivo("rainha.obj");
    Rainha rainha;
    rainha.obj = rainha_;
    rainha.translate = glm::translate(matriz_identidade,glm::vec3(15,7,0));
    branco.rainha = rainha;

    Objeto* rei_ = ler_arquivo("rei.obj");
    Rei rei;
    rei.obj = rei_;
    rei.translate = glm::translate(matriz_identidade,glm::vec3(15,9,0));
    branco.rei = rei;

    Objeto* bispo_2 = ler_arquivo("bispo.obj");
    bispo.obj = bispo_2;
    bispo.translate = glm::translate(matriz_identidade,glm::vec3(15,11,0));
    branco.bispos[1] = bispo;

    Objeto* cavalo_2 = ler_arquivo("vavalo.obj");
    cavalo.obj = cavalo_2;
    cavalo.translate = glm::translate(matriz_identidade,glm::vec3(15,13,0));
    branco.cavalos[1] = cavalo;

    Objeto* torre_2 = ler_arquivo("twe.obj");
    torre.obj = torre_2;
    torre.translate = glm::translate(matriz_identidade,glm::vec3(15,15,0));
    branco.torres[1] = torre;

    Objeto* peao_1 = ler_arquivo("pawn3.obj");
    Peao peao;
    peao.obj = peao_1;
    peao.translate = glm::translate(matriz_identidade,glm::vec3(13,1,0));
    branco.peoes[0] = peao;

    Objeto* peao_2 = ler_arquivo("pawn3.obj");
    peao.obj = peao_2;
    peao.translate = glm::translate(matriz_identidade,glm::vec3(13,3,0));
    branco.peoes[1] = peao;

    Objeto* peao_3 = ler_arquivo("pawn3.obj");
    peao.obj = peao_3;
    peao.translate = glm::translate(matriz_identidade,glm::vec3(13,5,0));
    branco.peoes[2] = peao;

    Objeto* peao_4 = ler_arquivo("pawn3.obj");
    peao.obj = peao_4;
    peao.translate = glm::translate(matriz_identidade,glm::vec3(13,7,0));
    branco.peoes[3] = peao;

    Objeto* peao_5 = ler_arquivo("pawn3.obj");
    peao.obj = peao_5;
    peao.translate = glm::translate(matriz_identidade,glm::vec3(13,9,0));
    branco.peoes[4] = peao;

    Objeto* peao_6 = ler_arquivo("pawn3.obj");
    peao.obj = peao_6;
    peao.translate = glm::translate(matriz_identidade,glm::vec3(13,11,0));
    branco.peoes[5] = peao;

    Objeto* peao_7 = ler_arquivo("pawn3.obj");
    peao.obj = peao_7;
    peao.translate = glm::translate(matriz_identidade,glm::vec3(13,13,0));
    branco.peoes[6] = peao;

    Objeto* peao_8 = ler_arquivo("pawn3.obj");
    peao.obj = peao_8;
    peao.translate = glm::translate(matriz_identidade,glm::vec3(13,15,0));
    branco.peoes[7] = peao;

    return branco;
}

// Coloca as peças pretas no tabuleiro 3D em cada posição
Jogador iniciar_preto(){
    jogador preto;
    glm::mat4 matriz_identidade(1);

    Objeto* torre_1 = ler_arquivo("twe.obj");
    Torre torre;
    torre.obj = torre_1;
    torre.translate = glm::translate(matriz_identidade,glm::vec3(1,1,0));
    preto.torres[0] = torre;

    Objeto* cavalo_1 = ler_arquivo("vavalo.obj");
    Cavalo cavalo;
    cavalo.obj = cavalo_1;
    cavalo.translate = glm::translate(matriz_identidade,glm::vec3(1,3,0));
    preto.cavalos[0] = cavalo;

    Objeto* bispo_1 = ler_arquivo("bispo.obj");
    Bispo bispo;
    bispo.obj = bispo_1;
    bispo.translate = glm::translate(matriz_identidade,glm::vec3(1,5,0));
    preto.bispos[0] = bispo;

    Objeto* rainha_ = ler_arquivo("rainha.obj");
    Rainha rainha;
    rainha.obj = rainha_;
    rainha.translate = glm::translate(matriz_identidade,glm::vec3(1,7,0));
    preto.rainha = rainha;

    Objeto* rei_ = ler_arquivo("rei.obj");
    Rei rei;
    rei.obj = rei_;
    rei.translate = glm::translate(matriz_identidade,glm::vec3(1,9,0));
    preto.rei = rei;

    Objeto* bispo_2 = ler_arquivo("bispo.obj");
    bispo.obj = bispo_2;
    bispo.translate = glm::translate(matriz_identidade,glm::vec3(1,11,0));
    preto.bispos[1] = bispo;

    Objeto* cavalo_2 = ler_arquivo("vavalo.obj");
    cavalo.obj = cavalo_2;
    cavalo.translate = glm::translate(matriz_identidade,glm::vec3(1,13,0));
    preto.cavalos[1] = cavalo;

    Objeto* torre_2 = ler_arquivo("twe.obj");
    torre.obj = torre_2;
    torre.translate = glm::translate(matriz_identidade,glm::vec3(1,15,0));
    preto.torres[1] = torre;

    Objeto* peao_1 = ler_arquivo("pawn3.obj");
    Peao peao;
    peao.obj = peao_1;
    peao.translate = glm::translate(matriz_identidade,glm::vec3(3,1,0));
    preto.peoes[0] = peao;

    Objeto* peao_2 = ler_arquivo("pawn3.obj");
    peao.obj = peao_2;
    peao.translate = glm::translate(matriz_identidade,glm::vec3(3,3,0));
    preto.peoes[1] = peao;

    Objeto* peao_3 = ler_arquivo("pawn3.obj");
    peao.obj = peao_3;
    peao.translate = glm::translate(matriz_identidade,glm::vec3(3,5,0));
    preto.peoes[2] = peao;

    Objeto* peao_4 = ler_arquivo("pawn3.obj");
    peao.obj = peao_4;
    peao.translate = glm::translate(matriz_identidade,glm::vec3(3,7,0));
    preto.peoes[3] = peao;

    Objeto* peao_5 = ler_arquivo("pawn3.obj");
    peao.obj = peao_5;
    peao.translate = glm::translate(matriz_identidade,glm::vec3(3,9,0));
    preto.peoes[4] = peao;

    Objeto* peao_6 = ler_arquivo("pawn3.obj");
    peao.obj = peao_6;
    peao.translate = glm::translate(matriz_identidade,glm::vec3(3,11,0));
    preto.peoes[5] = peao;

    Objeto* peao_7 = ler_arquivo("pawn3.obj");
    peao.obj = peao_7;
    peao.translate = glm::translate(matriz_identidade,glm::vec3(3,13,0));
    preto.peoes[6] = peao;

    Objeto* peao_8 = ler_arquivo("pawn3.obj");
    peao.obj = peao_8;
    peao.translate = glm::translate(matriz_identidade,glm::vec3(3,15,0));
    preto.peoes[7] = peao;

    return preto;
}

// Ocupa os quadrados nas posições das peças do tabuleiro no 2D
void iniciar_2D(){
    // inicia a posição de cada peça
    for(int i=0;i<64;i++){
        if(tabuleiro[i].pos.x == 1 && tabuleiro[i].pos.y == 1){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(1,1);
            tabuleiro[i].jogador_ocupando = 2;
        }else if(tabuleiro[i].pos.x == 1 && tabuleiro[i].pos.y == 3){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(2,1);
            tabuleiro[i].jogador_ocupando = 2;
        }else if(tabuleiro[i].pos.x == 1 && tabuleiro[i].pos.y == 5){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(3,1);
            tabuleiro[i].jogador_ocupando = 2;
        }else if(tabuleiro[i].pos.x == 1 && tabuleiro[i].pos.y == 7){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(4,1);
            tabuleiro[i].jogador_ocupando = 2;
        }else if(tabuleiro[i].pos.x == 1 && tabuleiro[i].pos.y == 9){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(5,1);
            tabuleiro[i].jogador_ocupando = 2;
        }else if(tabuleiro[i].pos.x == 1 && tabuleiro[i].pos.y == 11){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(3,2);
            tabuleiro[i].jogador_ocupando = 2;
        }else if(tabuleiro[i].pos.x == 1 && tabuleiro[i].pos.y == 13){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(2,2);
            tabuleiro[i].jogador_ocupando = 2;
        }else if(tabuleiro[i].pos.x == 1 && tabuleiro[i].pos.y == 15){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(1,2);
            tabuleiro[i].jogador_ocupando = 2;
        }else if(tabuleiro[i].pos.x == 3 && tabuleiro[i].pos.y == 1){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(6,1);
            tabuleiro[i].jogador_ocupando = 2;
        }else if(tabuleiro[i].pos.x == 3 && tabuleiro[i].pos.y == 3){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(6,2);
            tabuleiro[i].jogador_ocupando = 2;
        }else if(tabuleiro[i].pos.x == 3 && tabuleiro[i].pos.y == 5){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(6,3);
            tabuleiro[i].jogador_ocupando = 2;
        }else if(tabuleiro[i].pos.x == 3 && tabuleiro[i].pos.y == 7){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(6,4);
            tabuleiro[i].jogador_ocupando = 2;
        }else if(tabuleiro[i].pos.x == 3 && tabuleiro[i].pos.y == 9){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(6,5);
            tabuleiro[i].jogador_ocupando = 2;
        }else if(tabuleiro[i].pos.x == 3 && tabuleiro[i].pos.y == 11){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(6,6);
            tabuleiro[i].jogador_ocupando = 2;
        }else if(tabuleiro[i].pos.x == 3 && tabuleiro[i].pos.y == 13){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(6,7);
            tabuleiro[i].jogador_ocupando = 2;
        }else if(tabuleiro[i].pos.x == 3 && tabuleiro[i].pos.y == 15){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(6,8);
            tabuleiro[i].jogador_ocupando = 2;
        }else if(tabuleiro[i].pos.x == 15 && tabuleiro[i].pos.y == 1){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(1,1);
            tabuleiro[i].jogador_ocupando = 1;
        }else if(tabuleiro[i].pos.x == 15 && tabuleiro[i].pos.y == 3){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(2,1);
            tabuleiro[i].jogador_ocupando = 1;
        }else if(tabuleiro[i].pos.x == 15 && tabuleiro[i].pos.y == 5){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(3,1);
            tabuleiro[i].jogador_ocupando = 1;
        }else if(tabuleiro[i].pos.x == 15 && tabuleiro[i].pos.y == 7){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(4,1);
            tabuleiro[i].jogador_ocupando = 1;
        }else if(tabuleiro[i].pos.x == 15 && tabuleiro[i].pos.y == 9){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(5,1);
            tabuleiro[i].jogador_ocupando = 1;
        }else if(tabuleiro[i].pos.x == 15 && tabuleiro[i].pos.y == 11){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(3,2);
            tabuleiro[i].jogador_ocupando = 1;
        }else if(tabuleiro[i].pos.x == 15 && tabuleiro[i].pos.y == 13){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(2,2);
            tabuleiro[i].jogador_ocupando = 1;
        }else if(tabuleiro[i].pos.x == 15 && tabuleiro[i].pos.y == 15){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(1,2);
            tabuleiro[i].jogador_ocupando = 1;
        }else if(tabuleiro[i].pos.x == 13 && tabuleiro[i].pos.y == 1){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(6,1);
            tabuleiro[i].jogador_ocupando = 1;
        }else if(tabuleiro[i].pos.x == 13 && tabuleiro[i].pos.y == 3){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(6,2);
            tabuleiro[i].jogador_ocupando = 1;
        }else if(tabuleiro[i].pos.x == 13 && tabuleiro[i].pos.y == 5){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(6,3);
            tabuleiro[i].jogador_ocupando = 1;
        }else if(tabuleiro[i].pos.x == 13 && tabuleiro[i].pos.y == 7){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(6,4);
            tabuleiro[i].jogador_ocupando = 1;
        }else if(tabuleiro[i].pos.x == 13 && tabuleiro[i].pos.y == 9){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(6,5);
            tabuleiro[i].jogador_ocupando = 1;
        }else if(tabuleiro[i].pos.x == 13 && tabuleiro[i].pos.y == 11){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(6,6);
            tabuleiro[i].jogador_ocupando = 1;
        }else if(tabuleiro[i].pos.x == 13 && tabuleiro[i].pos.y == 13){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(6,7);
            tabuleiro[i].jogador_ocupando = 1;
        }else if(tabuleiro[i].pos.x == 13 && tabuleiro[i].pos.y == 15){
            tabuleiro[i].situacao = 1;
            tabuleiro[i].peca_ocupada = glm::vec2(6,8);
            tabuleiro[i].jogador_ocupando = 1;
        }else{
            tabuleiro[i].situacao = 0;
            tabuleiro[i].peca_ocupada = glm::vec2(0,0);
            tabuleiro[i].jogador_ocupando = 0;
        }
    }

}
