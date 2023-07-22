//*----------------------------------------------------
//  Universidad:		Universidad Tecnica Nacional(UTN)
//  Curso:		Aplicaciones de Microcontroladores
//  Desarrollado por:	Daniela Méndez Porras y Keylor García Jirón
//  Nombre del proyecto:	Practicas_PIC_16F887A
//  Fecha                 21/11/2021
//  Nombre del archivo:	P6.8) Modificación control motor ac V1
//  --------------------------------------------------*/

#include "local_libraries/global_config_params.h"
#include "local_libraries/lcd.h"

LCD lcd={&PORTB, 2, 3, 4, 5, 6, 7};
char str_buff[10];
char str_buff1[10];
char str_buff2[10];
char str_buff3[10];
char str_buff5[10];
int contador=0;
int reinicio=0, arriba=0, abajo=0, derecha=0, izquierda=0;
char A[]={"GAME OVER"}; 
char cuerpo[]={"?"};//219
char snake[tamano];
char tamano[]=4;
char fruta[]={*};
char campo[D][K];//Tamaño del campo de movimiento
char D[]=7;
char K[]=31;
int fila=5;//Posicion inicial de la culebrita
int columna=16;//Posicion inicial de la culebrita
int posfruta=0;

typedef struct{
    int x, y;
    int modx, mody;
    char imagen;
}snake;

typedef struct{
    int x, y;
}fruit;

snake snake[100];

void __interrupt(high_priority) tc0Int(void){  
    
    if (PIR1bits.TMR2IF==1){ //Si se levanta la bandera 
        PIR1bits.TMR2IF=0;//se limpia
        TMR2=0;//se inicializa el temporizador
        PR2=195; //50ms
        contador++;
        
        //Configuración del botón de inicio o reinicio
        if(PORTAbits.RA0==1){//Cuando se presiona el boton RA0 se 
            reinicio++;//incrementa la variable para indicar el inicio 
        }
        
        if(reinicio==2){//Si reinicio es igual a 2 
            reinicio=0;//es para reiniciar el juego
        }
//---------------------------------------------------------------------------------------
//                        El juego empieza
//---------------------------------------------------------------------------------------       
        if(reinicio==1){
            
//----------------------------------------------------------------------------------------
//             Configuración de botones que mueven la serpiente y movimiento
//----------------------------------------------------------------------------------------            
            if(PORTAbits.RA1==1){ //si se presiona el boton 
                arriba++;//se incrementa la variable que mueve la serpiente hacia arriba
            }
            else if((PORTAbits.RA2==0)&&(PORTAbits.RA3==0)&&(PORTAbits.RA4==0)){ //Cuando se presiona cualquiera menos el que es la dirección
                if(contador==10){//velocidad de movimiento de 500ms
                    fila++;//se incrementa en la dirección hacia arriba
                }
                itoa(str_buff, fila, 10 );
                lcd_cursor(&lcd, str_buff, str_buff2);//Se mueve en la direccion de fila cuando se presionó arriba
            }
            if(PORTAbits.RA2==1){ //si se presiona el boton 
                abajo++;//se incrementa la variable que mueve la serpiente hacia abajo
            }
            else if((PORTAbits.RA1==0)&&(PORTAbits.RA3==0)&&(PORTAbits.RA4==0)){ //Cuando se presiona cualquiera menos el que es la dirección
                if(contador==10){//velocidad de movimiento de 500ms
                    fila--;//se decrementa en la dirección hacia abajo
                }
                itoa(str_buff, fila, 10 );
                lcd_cursor(&lcd, str_buff, str_buff2);//Se mueve en la direccion de fila cuando se presionó abajo
            }
            if(PORTAbits.RA3==1){ //si se presiona el boton 
                derecha++;//se incrementa la variable que mueve la serpiente hacia la derecha
            }
            else if((PORTAbits.RA2==0)&&(PORTAbits.RA1==0)&&(PORTAbits.RA4==0)){ //Cuando se presiona cualquiera menos el que es la dirección
                if(contador==10){//velocidad de movimiento de 500ms
                    columna++;//se incrementa en la dirección derecha
                }
                itoa(str_buff2, columna, 10 );
                lcd_cursor(&lcd, str_buff, str_buff2);//Se mueve en la direccion de fila cuando se presionó abajo
            }
            if(PORTAbits.RA4==1){ //si se presiona el boton 
                izquierda++;//se incrementa la variable que mueve la serpiente hacia la izquierda
            }
            else if((PORTAbits.RA2==0)&&(PORTAbits.RA1==0)&&(PORTAbits.RA3==0)){ //Cuando se presiona cualquiera menos el que es la dirección
                if(contador==10){//velocidad de movimiento de 500ms
                    columna--;//se incrementa en la dirección izquierda
                }
                itoa(str_buff2, columna, 10 );
                lcd_cursor(&lcd, str_buff, str_buff2);//Se mueve en la direccion de fila cuando se presionó abajo
            }

//----------------------------------------------------------------------------------------
//                            Imprimir la serpiente
//---------------------------------------------------------------------------------------- 
            for(int t=1; t==tamano; t++){ // impresion de la serpiente
                    fila--;//lo va colocando detras de lo que ya hay
                    columna--;//lo va colocando detras de lo que ya hay
                    itoa(str_buff2, fila, 10 );
                    itoa(str_buff2, columna, 10 );
                    lcd_cursor(&lcd, str_buff, str_buff2);
                    lcd_print(&lcd, cuerpo);
            }
//----------------------------------------------------------------------------------------
//                              Persecucion
//----------------------------------------------------------------------------------------             
            for(int m=1; m==tamano; m++){ 
                snake[m]=snake[m-1];
            }
//----------------------------------------------------------------------------------------
//                            Fruta posiciones
//----------------------------------------------------------------------------------------  
        if(posfruta==0){    
            lcd_cursor(&lcd,7,27); //Posición de la primera fruta 
            lcd_print(&lcd,fruta);//Imprime la fruta
        }
        if(posfruta==1){    
            tamano[]++;//aumenta el tamaño del cuerpo de la serpiente
            lcd_cursor(&lcd,3,10); //Posición de la segunda fruta 
            lcd_print(&lcd,fruta);//Imprime la fruta
            lcd_cursor(&lcd,7,27); //Posición de la fruta anterior 
            lcd_print(&lcd," ");//Borra la fruta anterior
        }    
        if(posfruta==2){   
            tamano[]++;//aumenta el tamaño del cuerpo de la serpiente
            lcd_cursor(&lcd,5,16); //Posición de la tercera fruta 
            lcd_print(&lcd,fruta);//Imprime la fruta
            lcd_cursor(&lcd,3,10); //Posición de la fruta anterior 
            lcd_print(&lcd," ");//Borra la fruta anterior
        }
        if(posfruta==3){   
            tamano[]++;//aumenta el tamaño del cuerpo de la serpiente
            lcd_cursor(&lcd,2,3); //Posición de la cuarta fruta 
            lcd_print(&lcd,fruta);//Imprime la fruta
            lcd_cursor(&lcd,5,16); //Posición de la fruta anterior
            lcd_print(&lcd," ");//Borra la fruta anterior
        }
        if(posfruta==4){   
            tamano[]++;//aumenta el tamaño del cuerpo de la serpiente
            lcd_cursor(&lcd,6,20); //Posición de la quinta fruta 
            lcd_print(&lcd,fruta);//Imprime la fruta
            lcd_cursor(&lcd,2,3); //Posición de la fruta anterior 
            lcd_print(&lcd," ");//Borra la fruta anterior
        }
        if(posfruta==5){   
            tamano[]++;//aumenta el tamaño del cuerpo de la serpiente
            lcd_cursor(&lcd,4,19); //Posición de la sexta fruta 
            lcd_print(&lcd,fruta);//Imprime la fruta
            lcd_cursor(&lcd,6,20); //Posición de la fruta anterior 
            lcd_print(&lcd," ");//Borra la fruta anterior
        }
        if(posfruta==6){   
            tamano[]++; //aumenta el tamaño del cuerpo de la serpiente
            lcd_cursor(&lcd,6,14); //Posición de la septima fruta 
            lcd_print(&lcd,fruta);//Imprime la fruta
            lcd_cursor(&lcd,4,19); //Posición de la fruta anterior 
            lcd_print(&lcd," ");//Borra la fruta anterior
        }
            
//----------------------------------------------------------------------------------------
//                    Configuración de los limites
//                           GAME OVER            
//----------------------------------------------------------------------------------------             
            
               if (str_buff==campo[D]){//Si el limite se alcanzó, es decir que ya tocó los bordes
                   lcd_cursor(&lcd,4,11); //Posición del mensaje 
                   lcd_print(&lcd, A);//Imprime mensaje de GAME OVER en LCD 
                   reinicio=0;//El juego se termina;
               } 
            
               if (str_buff1==campo[K]){//Si el limite se alcanzó, es decir que ya tocó los bordes
                   lcd_cursor(&lcd,4,11); //Posición del mensaje 
                   lcd_print(&lcd,A);//Imprime mensaje de GAME OVER en LCD  
                   reinicio=0;//El juego se termina;
               } 

//----------------------------------------------------------------------------------------
//                      Si choca en ella misma
//                            GAME OVER            
//----------------------------------------------------------------------------------------               
            if((tamano==str_buff)||(tamano==str_buff1)){
                   lcd_cursor(&lcd,4,11); //Posición del mensaje 
                   lcd_print(&lcd,A);//Imprime mensaje de GAME OVER en LCD  
                   reinicio=0;//El juego se termina;
            }
            
    }
        
    }//end 
}//end interrupt

void setup(void){
   //Config puertos
   TRISA= 0xFF; // definir si va como entrada o salida
   PORTA = 0x00; // inicializar el puerto
   TRISEbits.PSPMODE=0; //
   PORTB = 0x00;//se inicializa el puerto
   TRISB = 0x00; //0b10000000; output salida
   TRISD = 0x00; //0b00000000; output salida
   PORTD = 0x00;//se inicializa el puerto
   TRISC = 0x00; //0b00000000; output salida
   PORTC = 0x00;//se inicializa el puerto
   
  //Inicialización de LCD
   lcd_init(&lcd);
   lcd_clear(&lcd);
   
  //Entradas digitales
   ADCON1bits.PCFG=0x07; //habilita entradas digitales
   CMCON=0b00000111; //deshabilita el comparador de voltaje 
   
   //Configuraciones de interrupciones globales
   INTCONbits.GIE=1;//se habilita el global interrupt enable -todas las interrupciones
   INTCONbits.PEIE=1;//habilita (1) o deshabilita (0) las interrupciones asociadas a módulos periféricos
   INTCONbits.TMR0IE=1;//Habilitación de interrupción de desbordamiento TMR0
   INTCONbits.TMR0IF=0;//Bit de indicador de interrupción de desbordamiento
   ei();// Habilitar interrupciones globales a nivel de compilador XC8
   
   //Configuraciones del timer T2
   T2CONbits.T2CKPS0=0;//Bit 0 el prescarler 1:16, reduce la frecuencia que ingresa al timer es de 1:16
   T2CONbits.T2CKPS1=1;//Bit 1el prescarler 1:16, reduce la frecuencia que ingresa al timer es de 1:16
   T2CONbits.TOUTPS0=1;//El postescaler ralentiza la frecuencia con la que genera interrupciones es de 1:16
   T2CONbits.TOUTPS1=1;//El postescaler ralentiza la frecuencia con la que genera interrupciones es de 1:16
   T2CONbits.TOUTPS2=1;//El postescaler ralentiza la frecuencia con la que genera interrupciones es de 1:16
   T2CONbits.TOUTPS3=1; //El postescaler ralentiza la frecuencia con la que genera interrupciones es de 1:16
   PIR1bits.TMR2IF=0;  //limpieza de la bandera de desbordamiento
   PIE1bits.TMR2IE=1;//habilita la interrupcion del timer
   TMR2=0; //Comienza en 0 y llega hasta PR2
   PR2=195; //PR2 llega a 50ms
   T2CONbits.TMR2ON=1; //Iniciamos el timer, se enciende 
   
} //END SETUP

void campojuego(char campo[D][K]){
//----------------------------------------------------------------------------------------            
//                                  Campo de juego
//---------------------------------------------------------------------------------------- 
 int i, j;
 for (i = 0 ; i < D; i++){
        for (j = 0; j < K; j++){
            if (i == 0 || i == D - 1){
                campo [i][j] = '?';
            }
            else if (j == 0 || j == K - 1){
                campo [i][j] = '|';
            }
            else {
                campo[i][j] = ' ';
            }
        }
    }
}

int main(void){
   setup();    // Call function configuration
    while(1){//se mantiene en la interrupcion de alta prioridad
        asm("nop");
    }//end while
}//end main
 
            
