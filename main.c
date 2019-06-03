/*
* Universidad Nacional de Colombia

* Codigo de ejemplo para la asignatura de Microcontroladores
* Tema: PWM DE SALIDA
* Microcontrolador: MC9S08QE16
* Autor: Andrés Felipe Herrera 
* Fecha: Mayo/2019
*/

#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include <stdio.h>
#include <stdlib.h>
#define PRESCALAR 7
#define MODULUS 32768
#define DUTY25 (MODULUS/4)
#define VNkeyboard 2
int counter ;
void main(void) {
	
 EnableInterrupts; /* enable interrupts */
 /*
  * Configuracion de los puertos
  */
 	 PTADD = 0; //initialize as input (Data Direction Register)
 	 PTAPE = 0xf0; //Pullups on upper 4 bits
 	 /*INICIALIZAR COMO PUERTOS DE SALIDA*/
 	 PTCDD = 0xFF; //PUERTOS EN 1
 	 PTCSE = 0xFF; //PUERTO CON SLEW RATE
 	 PTCDS =  0xFF; //PUERTO CON DRIVE STREGHT
  //CONFIGURACIÓN IRQ 
 	 _IRQSC.Byte = 0b00010110;
 			 /*                    ;IRQPDD= 0 ;; habilita resistencias de pull up con pe
                                    ; IRQEDG= 0 ;; habilita flancos de bajada
                                    ; IRQPE = 1 ;; se habilita el IRQ pin enable
                                    ; IRQF  = 0
                                    ; IRQACK= 1 ;; se habilita el ACKNOWLEDGE
                                    ; IRQIE = 1 ;; se habilita el IRQ interrupt enable
                                    ; IRQMOD= 0 ;; solo flanco sin nivel
 			  * 
 			  * */
 	/*CONFIGURACION TPM */
 		  TPM3SC_CLKSA = 1;/*Select BUS clock*/
 		  TPM3SC_CLKSB = 0;
 		  TPM3SC_PS = PRESCALAR;/*clock source divided by prescalar*/
 		  TPM3MOD = MODULUS;/*set Counter modulus*/
 		  /*configure PWM mode and pulse*/
 		  TPM3C0SC_MS0B = 1; /*MS0B=1, MS0A=0; << Edge align PWM*/
 		  TPM3C0SC_ELS0A = 1; /*Select low as true*/
 		  TPM3C0V = DUTY25;/*select final divider (duty cycle)*/
  for(;;) {
  __RESET_WATCHDOG(); /* kicks the dog */
     }
  } /* loop forever */
  interrupt VNkeyboard void intSW1(){
  
 IRQSC_IRQACK = 1;/*acknowledge interrupt*/
 if (counter >= MODULUS) {      // Determina el ciclo util del led
 		counter = 0;
 		 TPM3C0V = counter;
 		 ;
 	} else {
 		counter += DUTY25;
 		TPM3C0V = counter;
 	 	}
 }
