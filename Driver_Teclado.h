#ifndef DRIVER_TECLADO_H_INCLUDED
#define DRIVER_TECLADO_H_INCLUDED

#define PINO_TECLA_CIMA 10
#define PINO_TECLA_CENTRO 7
#define PINO_TECLA_BAIXO 9
#define PINO_TECLA_DIREITA 6
#define PINO_TECLA_ESQUERDA 8

unsigned int Verificar_Teclado(unsigned char tecla);
void Inicializa_Teclado (void);
void LCD_number(unsigned int a);

#endif /* DRIVER_TECLADO_H_INCLUDED */
