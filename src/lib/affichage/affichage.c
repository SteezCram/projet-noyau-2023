/******************************************************************
	MODULE : "affichage"

	CONTENU : Affichage de chaines de caractères et d'entier

	AUTRE MODULES UTILISES  :  Serial.s

	ECRIT/MODIFIE PAR	DERNIERE DATE
	JC      PETTIER		XXeme siecle
	Vincent VILLOT		23/12/04
	JC      PETTIER		15/04/05
	CM mars 2014

*******************************************************************/

#include "constC.h"
#include "lpc17xx_uart.h"


/*******************************************************************
                   TRAITEMENTS
********************************************************************/

IMPORT void initUART0Polling1(void);		// dans serial_uart0_polling simple à changer
																			// si on veut passer sur une autre uart

LOCAL void putchar(int ch)

{
	UART_SendByte(LPC_UART0,( uint8_t)ch);
	
	// wait for current transmission complete - THR must be empty
	
  while (UART_CheckBusy(LPC_UART0) == SET);

}

/*----------------------------------------------------------------------------
		Description :   Passage à la ligne
*/
EXPORT void passeALaLigneSuivante() {
   putchar((char) 13);   /* RC */
   putchar((char) 10);   /* LF */
}

/*----------------------------------------------------------------------------
		Description :   Revient au début de la ligne
*/
EXPORT void revientEnPremiereColonne() {
   putchar((char) 13);   /* RC */
}

/*----------------------------------------------------------------------------
	Description :   Affichage d'une chaine
*/
EXPORT void initialiseAffichage(void) {
  
  initUART0Polling1();

  // il y a des caractères vide au début...pourquoi?

  revientEnPremiereColonne();	
}

/*----------------------------------------------------------------------------
	Description :   Affichage d'une chaine
*/
EXPORT void afficheChaine(const char *p) {
	/* INV : caracteres presents a l'ecran sont ceux de p_init à p exclus */
	while (*p) putchar(*p++);
	
}



/*-------------------------------------------------------------------------------
		Description : affichage d'un chiffre
		Param.pre :   chiffre dans 0..9
*/
LOCAL void sortieChiffre(int chiffre) {
	putchar((char) chiffre+'0');
}

/*-------------------------------------------------------------------------------
		Description : affichage d'un entier non signé
		Param.pre : num>0
*/
LOCAL void affichNumNonSigne(int num) {
	if (num<0) {
		afficheChaine("Precondition de affichNumNonSigne non verifiée");
		passeALaLigneSuivante();
	} else {
		unsigned int numDiv = num/(unsigned) 10;
		if (numDiv>0) {
			affichNumNonSigne(numDiv);
		}
		sortieChiffre(num-numDiv*10);
	}
}

/*----------------------------------------------------------------------------
	Description :   Affichage d'une chaîne de caractères
*/
EXPORT void affiche(const char *msg) {
	afficheChaine(msg);
	passeALaLigneSuivante();
	
}

/*-------------------------------------------------------------------------------
		Description :  Affichage d'un entier signé
*/
EXPORT void afficheNombre(int num) {
	if (num<0) {
		putchar('-');
		affichNumNonSigne(-num);
	} else if (num==0) {
		putchar('0');
	} else {
		affichNumNonSigne(num);
	}
}



