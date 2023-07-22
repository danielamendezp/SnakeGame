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

LCD lcd={&PORTD, 2, 3, 4, 5, 6, 7};
int H;
int V;
int RH;
int RV;
int cont=0;
int ciclo=0;

char cuerpo[10]={"o","*","*","*","*","*","*","*","*","*"};

int tamano=0;

int reinicio=0, arriba=0, abajo=0, derecha=0, izquierda=0;
int fila=15;//Posicion inicial de la culebrita
int columna=5;//Posicion inicial de la culebrita

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
//   lcd_init(&lcd);
//   lcd_clear(&lcd);
   
  //Entradas digitales
   ADCON1=0b11111110;
   ADCON1bits.PCFG = 0x07;   
} //END SETUP

void lcds (int columna,fila);
int main(void){
   setup();    // Call function configuration
   
        PORTB=0b00000111;
        lcd_init(&lcd);   
        lcd_clear(&lcd);
        PORTB=0b00000110;
        lcd_init(&lcd);
        PORTB=0b00000101;
        lcd_init(&lcd);
        PORTB=0b00000100;
        lcd_init(&lcd);
        PORTB=0b00000011;
        lcd_init(&lcd);
        PORTB=0b00000010;
        lcd_init(&lcd);
        PORTB=0b00000001;
        lcd_init(&lcd);
        PORTB=0b00000000;
        lcd_init(&lcd); 
        lcds(columna,fila);    
        lcd_print(&lcd,"0"); 
        
        
   
    while(1){//se mantiene en la interrupcion de alta prioridad
        
//       if(PORTAbits.RA4==1){
//            reinicio++;
//            __delay_ms(500);
//        }
//        if(reinicio==1){
            botones();
            serpiente();   
            ratones();
//            limites();
//        }
//        if(reinicio==0){
//            if(ciclo==1){
//                lcd_print(&lcd,"GAME OVER");
//            }
//        }        
        
    }//end while
}//end main

//*****LCD MODIFICACIÓN PARA LEER VALORES DE 0 A 8 EN COLUMNA Y 0 A 32 EN FILAS****
void lcds (int columna,fila){
    int x1,y1;
    //*****columna1LCD*******
    if (columna<=1 && fila<=15){
    x1=columna;
    y1=fila;
    PORTB=0b00000000;
    lcd_cursor(&lcd,x1,y1);
    }
    
    if (columna>1 && columna<=3 && fila<=15){ //columna 1 display2
    x1=abs(columna-2);
    y1=fila;
    PORTB=0b00000010;
    lcd_cursor(&lcd,x1,y1);
    }
    
    if (columna>3 && columna<=5 && fila<=15){
    x1=abs(columna-4);
    y1=fila;
    PORTB=0b00000100;
    lcd_cursor(&lcd,x1,y1);
    }
    
    if (columna>5 && columna<=7 && fila<=15){
    x1=abs(columna-6);
    y1=fila;
    PORTB=0b00000110;
    lcd_cursor(&lcd,x1,y1);
    }
    
   //*****columna2LCD*******
    
    if (columna<=1 && fila>15 && fila<=31){
    x1=columna;
    y1=abs(fila-16);
    PORTB=0b00000001;
    lcd_cursor(&lcd,x1,y1);
    }
    
    if (columna>1 && columna<=3 && fila>15 && fila<=31){ //columna 1 display2
    x1=abs(columna-2);
    y1=abs(fila-16);
    PORTB=0b00000011;
    lcd_cursor(&lcd,x1,y1);
    }
    
    if (columna>3 && columna<=5 && fila>15 && fila<=31){
    x1=abs(columna-4);
    y1=abs(fila-16);
    PORTB=0b00000101;
    lcd_cursor(&lcd,x1,y1);
    }
    
    if (columna>5 && columna<=7 && fila>15 && fila<=31){
    x1=abs(columna-6);
    y1=abs(fila-16);
    PORTB=0b00000111;
    lcd_cursor(&lcd,x1,y1);
    }   
}

//----------------------------------------------------------------------------------------
//                            Imprimir la serpiente
//---------------------------------------------------------------------------------------- 
int serpiente (void){  //solo funciona si presiono los botones
    V=columna;
    H=fila;
    if(derecha==1){
//    lcd_clear(&lcd);
    __delay_ms(10);
    lcds(V,H);    
    lcd_print(&lcd,"0");  
    if (tamano==0){
    lcds(V,H-1);
    lcd_print(&lcd," ");
    }
    if(tamano>0){
        lcds(V,H-1);
        lcd_print(&lcd,"*");
        lcds(V,H-2);
        lcd_print(&lcd," ");
    } 
    if(tamano>1){
        lcds(V,H-2);
        lcd_print(&lcd,"*");
        lcds(V,H-3);
        lcd_print(&lcd," ");
    }
    if(tamano>2){
        lcds(V,H-3);
        lcd_print(&lcd,"*");
        lcds(V,H-4);
        lcd_print(&lcd," ");
    }
    if(tamano>3){
        lcds(V,H-4);
        lcd_print(&lcd,"*");
        lcds(V,H-5);
        lcd_print(&lcd," ");
    }
    if(tamano>4){
        lcds(V,H-5);
        lcd_print(&lcd,"*");
        lcds(V,H-6);
        lcd_print(&lcd," ");
    }
    if(tamano>5){
        lcds(V,H-6);
        lcd_print(&lcd,"*");
        lcds(V,H-7);
        lcd_print(&lcd," ");
    }
    if(tamano>6){
        lcds(V,H-7);
        lcd_print(&lcd,"*");
        lcds(V,H-8);
        lcd_print(&lcd," ");
    }
    if(tamano>7){
        lcds(V,H-8);
        lcd_print(&lcd,"*");
        lcds(V,H-9);
        lcd_print(&lcd," ");
    }
    if(tamano>8){
        lcds(V,H-9);
        lcd_print(&lcd,"*");
        lcds(V,H-10);
        lcd_print(&lcd," ");
    }
    }
    
    if(izquierda==1){
//    lcd_clear(&lcd);
    __delay_ms(10);
    lcds(V,H);    
    lcd_print(&lcd,"0");  
    if (tamano==0){
    lcds(V,H+1);
    lcd_print(&lcd," ");
    }
    if(tamano>0){
        lcds(V,H+1);
        lcd_print(&lcd,"*");
        lcds(V,H+2);
        lcd_print(&lcd," ");
    } 
    if(tamano>1){
        lcds(V,H+2);
        lcd_print(&lcd,"*");
        lcds(V,H+3);
        lcd_print(&lcd," ");
    }
    if(tamano>2){
        lcds(V,H+3);
        lcd_print(&lcd,"*");
        lcds(V,H+4);
        lcd_print(&lcd," ");
    }
    if(tamano>3){
        lcds(V,H+4);
        lcd_print(&lcd,"*");
        lcds(V,H+5);
        lcd_print(&lcd," ");
    }
    if(tamano>4){
        lcds(V,H+5);
        lcd_print(&lcd,"*");
        lcds(V,H+6);
        lcd_print(&lcd," ");
    }
    if(tamano>5){
        lcds(V,H+6);
        lcd_print(&lcd,"*");
        lcds(V,H+7);
        lcd_print(&lcd," ");
    }
    if(tamano>6){
        lcds(V,H+7);
        lcd_print(&lcd,"*");
        lcds(V,H+8);
        lcd_print(&lcd," ");
    }
    if(tamano>7){
        lcds(V,H+8);
        lcd_print(&lcd,"*");
        lcds(V,H+9);
        lcd_print(&lcd," ");
    }
    if(tamano>8){
        lcds(V,H+9);
        lcd_print(&lcd,"*");
        lcds(V,H+10);
        lcd_print(&lcd," ");
    }
    }
    
    
//********************    
    if(arriba==1){
//    lcd_clear(&lcd);
    lcds(V,H);
    lcd_print(&lcd,"0");
    if (tamano==0){
    lcds(V+1,H);
    lcd_print(&lcd," ");
    }
    if(tamano>0){
        lcds(V+1,H);
        lcd_print(&lcd,"*");
        lcds(V+2,H);
        lcd_print(&lcd," ");
    }
    if(tamano>1){
        lcds(V+2,H);
        lcd_print(&lcd,"*");
        lcds(V+2,H);
        lcd_print(&lcd," ");
    }
    if(tamano>2){
        lcds(V+3,H);
        lcd_print(&lcd,"*");
        lcds(V+2,H);
        lcd_print(&lcd," ");
    }
    if(tamano>3){
        lcds(V+4,H);
        lcd_print(&lcd,"*");
        lcds(V+2,H);
        lcd_print(&lcd," ");
    }
    if(tamano>4){
        lcds(V+5,H);
        lcd_print(&lcd,"*");
        lcds(V+2,H);
        lcd_print(&lcd," ");
    }
    if(tamano>5){
        lcds(V+6,H);
        lcd_print(&lcd,"*");
        lcds(V+2,H);
        lcd_print(&lcd," ");
    }
    if(tamano>6){
        lcds(V+7,H);
        lcd_print(&lcd,"*");
        lcds(V+2,H);
        lcd_print(&lcd," ");
    }
    if(tamano>7){
        lcds(V+8,H);
        lcd_print(&lcd,"*");
        lcds(V+2,H);
        lcd_print(&lcd," ");
    }
    if(tamano>8){
        lcds(V+9,H);
        lcd_print(&lcd,"*");
        lcds(V+2,H);
        lcd_print(&lcd," ");
    }
    }
    
    if(abajo==1){
//    lcd_clear(&lcd);
    lcds(V,H);
    lcd_print(&lcd,"0");
    if (tamano==0){
    lcds(V-1,H);
    lcd_print(&lcd," ");
    }
    if(tamano>0){
        lcds(V-1,H);
        lcd_print(&lcd,"*");
        lcds(V-2,H);
        lcd_print(&lcd," ");
    }
    if(tamano>1){
        lcds(V-2,H);
        lcd_print(&lcd,"*");
        lcds(V-3,H);
        lcd_print(&lcd," ");
    }
    if(tamano>2){
        lcds(V-3,H);
        lcd_print(&lcd,"*");
        lcds(V-4,H);
        lcd_print(&lcd," ");
    }
    if(tamano>3){
        lcds(V-4,H);
        lcd_print(&lcd,"*");
        lcds(V-5,H);
        lcd_print(&lcd," ");
    }
    if(tamano>4){
        lcds(V-5,H);
        lcd_print(&lcd,"*");
        lcds(V-6,H);
        lcd_print(&lcd," ");
    }
    if(tamano>5){
        lcds(V-6,H);
        lcd_print(&lcd,"*");
        lcds(V-7,H);
        lcd_print(&lcd," ");
    }
    if(tamano>6){
        lcds(V-8,H);
        lcd_print(&lcd,"*");
        lcds(V-9,H);
        lcd_print(&lcd," ");
    }
    if(tamano>7){
        lcds(V-8,H);
        lcd_print(&lcd,"*");
        lcds(V-9,H);
        lcd_print(&lcd," ");
    }
    if(tamano>8){
        lcds(V-9,H);
        lcd_print(&lcd,"*");
        lcds(V-10,H);
        lcd_print(&lcd," ");
    }
    }
}

int limites (void){
    if((columna<=0)||(columna>=32)){
        lcd_clear(&lcd);
        reinicio=0;
        ciclo=1;
    }
    if((fila<=0)||(fila>=8)){
        lcd_clear(&lcd);
        reinicio=0;
        ciclo=1;
    }
}

int botones (void){
//----------------------------------------------------------------------------------------
//             Configuración de botones que mueven la cabeza de la serpiente
//----------------------------------------------------------------------------------------            
            if(PORTAbits.RA0==1){ //si se presiona el boton arriba
                abajo=0;
                izquierda=0;
                derecha=0;
                arriba=1;
            }
             if(arriba==1){
                columna--;//se incrementa la variable que mueve la serpiente hacia arriba
                serpiente();
                __delay_ms(500);
                
            } 
            if(PORTAbits.RA1==1){ //si se presiona el boton 
                izquierda=0;
                derecha=0;
                arriba=0;
                abajo=1;
            }
                
             if(abajo==1){   
                columna++;//se incrementa la variable que mueve la serpiente hacia abajo
                serpiente();
                __delay_ms(500);
             }
            
            if(PORTAbits.RA2==1){ //si se presiona el boton 
                abajo=0;
                izquierda=0;
                arriba=0;
                derecha=1;
            }
             if(derecha==1){  
                fila++;//se incrementa la variable que mueve la serpiente hacia la derecha
                serpiente();
                __delay_ms(500);
            }

            if(PORTAbits.RA3==1){ //si se presiona el boton 
                abajo=0;
                derecha=0;
                arriba=0;
                izquierda=1;
            }
            if(izquierda==1){
                fila--;//se incrementa la variable que mueve la serpiente hacia la izquierda
                serpiente();
                __delay_ms(500);
            }
}
            
int ratones (void){ 
    if(V==RV && H==RH){
        tamano++;
    }
    if (tamano==0){
    RV=5;
    RH=18;
    lcds(RV,RH);
    lcd_print(&lcd,"o");
    }
    
    if (tamano==1){
    RV=2;
    RH=10;
    lcds(RV,RH);
    lcd_print(&lcd,"o");
    }
    
    if (tamano==2){
    RV=7;
    RH=3;
    lcds(RV,RH);
    lcd_print(&lcd,"o");
    }
    
    if (tamano==3){
    RV=5;
    RH=10;
    lcds(RV,RH);
    lcd_print(&lcd,"o");
    }
    
    if (tamano==4){
    RV=3;
    RH=3;
    lcds(RV,RH);
    lcd_print(&lcd,"o");
    }
    
    if (tamano==5){
    RV=8;
    RH=10;
    lcds(RV,RH);
    lcd_print(&lcd,"o");
    }
    
    if (tamano==6){
    RV=5;
    RH=18;
    lcds(RV,RH);
    lcd_print(&lcd,"o");
    }
    
    if (tamano==7){
    RV=5;
    RH=18;
    lcds(RV,RH);
    lcd_print(&lcd,"o");
    }
    
    if (tamano==8){
    RV=5;
    RH=18;
    lcds(RV,RH);
    lcd_print(&lcd,"o");
    }
    
    if (tamano==9){
    RV=5;
    RH=18;
    lcds(RV,RH);
    lcd_print(&lcd,"o");
    }
}