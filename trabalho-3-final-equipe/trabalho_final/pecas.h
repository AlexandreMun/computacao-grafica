// OBJETIVO: Structs para guardar os dados das peças que serão implementados durante o codigo

#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "objeto.h"

#ifndef PECAS_H
#define PECAS_H

typedef struct torre{
    Objeto* obj;
    glm::mat4 translate;
}Torre;

typedef struct peao{
    Objeto* obj;
    glm::mat4 translate;
    int turnos;
}Peao;

typedef struct bispo{
    Objeto* obj;
    glm::mat4 translate;
}Bispo;

typedef struct cavalo{
    Objeto* obj;
    glm::mat4 translate;
}Cavalo;

typedef struct rei{
    Objeto* obj;
    glm::mat4 translate;
    int situacao;
}Rei;

typedef struct rainha{
    Objeto* obj;
    glm::mat4 translate;
}Rainha;

// Dados do jogador
typedef struct jogador{
    struct rainha rainha;
    struct rei rei;
    struct peao peoes[8];
    struct torre torres[2];
    struct bispo bispos[2];
    struct cavalo cavalos[2];
}Jogador;

Jogador branco;
jogador preto;

#endif // PECAS_H
