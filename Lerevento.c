#include "Driver_Teclado.h"
#include "Lerevento.h"
#include "Config.h"

int Tecla_atual, Tecla_anterior, Tecla_serial;

int Lerevento (void)
{
    Tecla_atual = NO_EVENT;
    if (Verificar_Teclado(PINO_TECLA_CIMA) == 1)
    {
        Tecla_atual = CIMA;
    }

    if (Verificar_Teclado(PINO_TECLA_BAIXO) == 1)
    {
        Tecla_atual = BAIXO;
    }

    if (Verificar_Teclado(PINO_TECLA_ESQUERDA) == 1)
    {
        Tecla_atual = ESQUERDA;
    }

    if (Verificar_Teclado(PINO_TECLA_DIREITA) == 1)
    {
        Tecla_atual = DIREITA;
    }

    if (Verificar_Teclado(PINO_TECLA_CENTRO) == 1)
    {
        Tecla_atual = ENTER;
    }

    if ((Tecla_atual != Tecla_anterior)&&(Tecla_anterior == NO_EVENT))
    {
        Tecla_anterior = Tecla_atual;
        return Tecla_atual;
    }
    else
    {
        Tecla_anterior = Tecla_atual;
    }

    if (Tecla_serial == CIMA)
    {
        return CIMA;
    }

     if (Tecla_serial == BAIXO)
    {
        return BAIXO;
    }

     if (Tecla_serial == ESQUERDA)
    {
        return ESQUERDA;
    }

     if (Tecla_serial == DIREITA)
    {
        return DIREITA;
    }

     if (Tecla_serial == ENTER)
    {
        return ENTER;
    }

    //return Verificar_Alarme();
    return NO_EVENT;
}
