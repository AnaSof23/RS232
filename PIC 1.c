////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                     COMUNICACIÓN RS232 ENTRE DOS PIC                       //
//                                                                            //
//                                  PIC 1                                     //
//                                                                            //
//                             RobotyPic 2011                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <16F876a.h>

#fuses XT, NOWDT

#use delay(clock=4000000)
#use rs232(baud=9600, xmit=pin_c6, rcv=pin_c7)

#define use_portb_lcd TRUE
#define use_portb_kbd TRUE
#include <lcd.c>
#include <kbd.c>

   int valor;                 //Dato a transmitir
   char tecla;                //Dato ASCII tecla pulsada  
   
/******************************************************************************/
/*************  FUNCIÓN INTERRUPCIÓN POR RECEPCIÓN DE DATOS *******************/

#int_RDA                               //Interrupción por recepción de datos

void RDA_isr(){

   valor=getc();                 //En "valor" el dato recibido via RS232
   printf(lcd_putc, "\fRecibido %d ", valor);   //Se muestra en pantalla información recibida
   delay_ms(500);
   }

/******************************************************************************/
/************************  FUNCIÓN PRINCIPAL  *********************************/

void main () {
    
   port_b_pullups(TRUE);
   lcd_init();                   //Inicialización del display
   
   enable_interrupts(INT_RDA);   //Habilitación interrupción por recepción RS232
   enable_interrupts(GLOBAL);
   
   while(1){
         tecla=kbd_getc();       //En "tecla" la tecla pulsada
         valor=tecla-48;         //Valor ASCII se pasa a su valor numérico
         if(tecla!=0){           //Si se pulsa tecla...
            putc(valor);         //...se envía contenido de "valor" (tecla pulsada)
            printf(lcd_putc, "\fEnviado %d", valor);   //Se muestra en pantalla información enviada
            delay_ms(500);
         }
   }
}
