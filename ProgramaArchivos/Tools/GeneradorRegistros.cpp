#pragma once

#include "GeneradorRegistros.h"
#include <string>
#include <random>


int GeneradorRegistros::generarDNIAleatorio()
{
    default_random_engine generador(random_device{}());
    uniform_int_distribution<int> distribucion(10000000, 19999999);
    return distribucion(generador);
}
