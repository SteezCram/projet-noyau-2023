;/**************************************************************************//**
; * @file     allocateur.s
; * @brief    
; *           
; * @version  V1.0
; * @date     
; *
; * @note
; * 
; *
; * @par
; * 
; *
; * @par
; * 
; *
; ******************************************************************************/

; constantes

Stack_Size      EQU     0x00000040

controleThreadNP	EQU	0x1					; valeur pour controle avec mode thread non privil�gi�
											; pour la pile c'est lors de retour d'exceprion qu'elle est positionn�e
xPSRInitial 	EQU		0x01000000			; xPSR avec juste Thumb � 1, le reste est � 0 (comme suite � un reset)

LRThreadPSP		EQU		0xFFFFFFFD			; valeur de la pseudo @ de retour pour une exception en revenant en mode
											; thread avec utilisation de la pile PSP
											
; area => ALIGN implicit de 4 octets
; ici area data standard initialis�

                AREA    |.data|, DATA, READWRITE, ALIGN=3

; les piles sont � aligner sur 8 octets en cas de gestion des nombres flottants, comme ce n'est pas le cas avec
; notre projet, nous ne devrions pas �tre embet�
; cependant il est toujours pr�f�rable de respecter les conventions afin d'�viter tous probl�mes

; SPACE ne g�re pas l'alignement et les area sont pas d�faut sur des adresses doublement paires, on va donc forcer
; l'alignement sur une adresse triplement paires

				ALIGN 8

; Pile PSP pour demoRestitution

				SPACE   8*Stack_Size		; on multiplie la pile par 8, on est sur de conserver l'alignement pour le d�but
											; de la pile
Pile_PSP									; rappel le d�but de la pile est en bas

; Pile MSP pour demoRestitution

				SPACE   8*Stack_Size
Pile_MSP									; rappel le d�but de la pile est en bas


; DCD permet l'initialisation et la r�servation de 4 octets, il est align� sur une fronti�re doublement paire (modulo 4 donc)

; Initialisation en dur d'un contexte � restituer
				
etatCalcul		DCD		controleThreadNP	; controle
				DCD		4					; R4
				DCD		5					; R5
				DCD		6					; ...
				DCD		7
				DCD		8
				DCD		9
				DCD		10
				DCD		11					; R11
				DCD		Pile_PSP			; PSP
				DCD		Pile_MSP			; MSP
				DCD		LRThreadPSP			; LR en mode handler

; area => ALIGN implice de 4 octets
; zone de code

                AREA    |.text|, CODE, READONLY

				PRESERVE8					; le C souhaite une pile sur une @ triplement double, sans cette option 
											; l'assembleur lance des warning comme on s'interface avec le langage C
											; mais attention, si on veut pr�server la pile sur une @ triplement double
											; c'est � nous programmeur de faire ce qu'il faut
								
				
demoRestitution	PROC
				IMPORT  PInitial
 				EXPORT  demoRestitution

; fct qui va faire une cr�ation de processus/restitution de contexte � partir d'une structure etatCalcul et
; de piles statiques

; on est :
;  en mode handler
;  les IT sont d�sactiv� => indivisible/initerruptible
;  la structure � restituer est dans etatCalcul
;  les registres du processeur sont libres et disponibles
;  la pile MSP est valide


; � vous d'�crire le code ici!!!!!!!!!!!!!!!!!!!!!!!!

				LDR R2, = etatCalcul 		; Met dans R2 l'adresse de etatCalcul
				LDR R3, [R2]				; Met dans R3 la valeur contenu � l'adresse de R2
				MSR CONTROL, R3				; Met dans CONTROL le rgistre R3
				
				LDR R4, [R2, #4]			; Met dans R4 la valeur contenu � l'adresse de R2 avec un offset de 4
				LDR R5, [R2, #8]			; Met dans R5 la valeur contenu � l'adresse de R2 avec un offset de 8
				LDR R6, [R2, #12]			; etc.
				LDR R7, [R2, #16]
				LDR R8, [R2, #20]
				LDR R9, [R2, #24]
				LDR R10, [R2, #28]
				LDR R11, [R2, #32]
				
				LDR R3, [R2, #36]           ; Met dans R3 la valeur contenu � l'adresse de R2 avec un offset de 36
				MSR PSP, R3		            ; Met dans PSP le rgistre R3
				
				LDR R3, [R2, #40]           ; Met dans R3 la valeur contenu � l'adresse de R2 avec un offset de 40
				MSR MSP, R3                 ; Met dans PSP le rgistre R3
				
				LDR LR, [R2, #44]           ; On met dans LR la valeur contenu � l'adresse de R2 avec un offset de 44
				
				B PInitial
  


; on ne doit pas passer par ce code, par s�curit� on met une boucle

				B	.
				
				ENDP

				END

