#ifndef DRIVER_LCD_H_INCLUDED
#define DRIVER_LCD_H_INCLUDED

void LCD_iniciar();
void LCD_comando( char v_cComando );
void LCD_caractere( char v_cCaractere );
void lcdString(char * txt);
void LCD_number2(unsigned int a);
void LCD_number3(unsigned int a);
void LCD_number4(unsigned int a);
#endif /* DRIVER_LCD_H_INCLUDED */
