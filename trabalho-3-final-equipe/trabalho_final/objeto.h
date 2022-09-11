// OBJETIVO: Structs para guardar os objetos importados

#include "glm/glm.hpp"
#include "glm/ext.hpp"

#ifndef OBJETO_H
#define OBJETO_H

// Dados do ponto
typedef struct ponto{
    glm::vec3 coord;
    glm::vec3 normal;
    glm::vec2 tex;
}Ponto;

// Dados da face
typedef struct face{
    int id_ponto_1,id_ponto_2,id_ponto_3;
}Face;

// Dados do objeto
typedef struct objeto{
    struct face faces[50000];
    int quant_lados;
    struct ponto pontos[100000];
    int quant_ponto;
}Objeto;

#endif // OBJETO_H
