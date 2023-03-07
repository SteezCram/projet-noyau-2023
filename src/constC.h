/*-----------------------------------------------------------------------------
          fichier include : constC.h
          role            : constantes utilitaires
------------------------------------------------------------------------------*/

#ifndef __const_C_h
#define __const_C_h

/*==============================================================================
				CONSTANTES
==============================================================================*/

#define	NIL		(-1)
#define	OK		0
#define	PB		(-1)

#define	L			int
#define	TAILLE_L	4
#define	TAILLE_W	2

/*========= codes erreur à partager avec l'assembleur
			(convention codes assembleurs debutent à 100) ===================*/

#define CODE_ERREUR_AFFICH 						1
#define CODE_ERREUR_TRACE  						2
#define CODE_ERREUR_DEPASSEMENT_ZONE_DUMP 		3


/*==============================================================================
				TYPES
==============================================================================*/
typedef enum {false=0,true} bool;


/*==============================================================================
				REDEFINITION LANGAGE
==============================================================================*/

#define OU_SINON ||
#define ET_ALORS &&

#define EXPORT
#define IMPORT extern
#define LOCAL static

#endif /* __const_C_h */
