#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

enum {Alarme_POT_Ligado, Alarme_POT_Desligado, Alarme_LDR_Ligado, Alarme_LDR_Desligado}Alarmes;
enum {Teclado}Comando;
enum {Baixo, Alto}Nivel_Alarme;
void Config_LDR_inf (void);
void Config_LDR_sup(void);
void Config_POT_inf(void);
void Config_POT_sup(void);
int LDR_inf (int evento);
int LDR_sup (int evento);
int LDR_infe (void);
int LDR_supe (void);
int POT_inf (int evento);
int POT_sup (int evento);
int POT_infe (void);
int POT_supe (void);
void Liga_Desliga_Alarme_LDR (int status);
void Liga_Desliga_Alarme_POT (int status);
//void Frequencia_Alarme (void);
void Alarme(int Lvl);
int tempo (void);
int Verificar_Alarme (void);
int SENHA(void);
int Valor_SENHA1(int evento);
int Valor_SENHA2(int evento);
int Valor_SENHA3(int evento);
int Valor_SENHA4(int evento);
int Freq(void);
int Valor_Freq(int evento);
int Valor_MES(int evento);
int Valor_DIA(int evento);
int Valor_ANO(int evento);
int MES(void);
int DIA(void);
int ANO(void);
int Verificar_Alarme (void);
void Desliga_LED_BUZZER (void);
void Config_Freq_Atualizacao (int valor);

#endif /* CONFIG_H_INCLUDED */
