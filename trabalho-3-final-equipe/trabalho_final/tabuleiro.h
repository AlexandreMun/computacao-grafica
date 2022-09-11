// OBJETIVO: Struct para guardar dados de cada quadrado do tabuleiro

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#ifndef TABULEIRO_H
#define TABULEIRO_H

typedef struct quadrado{
    glm::vec3 pos;
    float color[3];
    int situacao; // se o quadrado está ocupado ou vago
    glm::vec2 peca_ocupada; // guarda um x que armazena o tipo da peça e o y que armazena a posição dentro do vetor de peças
    int jogador_ocupando; // Jogador ocupando o quadrado
}Quadrado;

#endif // TABULEIRO_H
