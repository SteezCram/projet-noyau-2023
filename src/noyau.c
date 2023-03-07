#include "noyau.h"

IMPORT void appelSvcInitNoyau(void);
IMPORT void demoRestitution(void);

void static messageDemarrageNoyau()

  /*

  Message début du noyau
	
	*/

{
	
	affiche("*** Démarrage du système ***");
	
	affiche("Binôme : Thomas - Victor");
	
	affiche("Année 2022-2023");

}

void initNoyau()

  /*

  Début de l'initialisation du noyau, on est en mode handler donc tout va bien
	
	*/

{

  // on commence par se mettre en mode atomique/indivisible puisque l'on touche au structure
	// du noyau => masquage des IT pour un mono proc ce qui est notre cas
	
	__disable_fault_irq(); // seules NMI et RESET passent

	// initialisation de l'UART
	
	initialiseAffichage();
	
	// message d'accueil
	
	messageDemarrageNoyau();
	
	// fin de l'initialisation pour l'étape 1
	// on appelle demoRestitution, une fct en ASM qui va faire la restitution de contexte à partir d'une structure
	// état calcul statique
	
	demoRestitution();
	
  // on ne revient pas ici mais afin de parer à tout problème
	// vous pouvez imaginer ici un appel à une fonction panicKernel avec un système d'erreur et de message
	
	while (true) ;

}

int main()

{

	/*

 	Point d'entrée de notre programme juste après l'initialisation de base
	   
	On est :
	  * on vient juste d'executer le code d'initialisation après le reset
	    * init de la pile MSP
	    * init des horloges systèmes
	    * init des zones mémoires utilisées (à zéro ou aux valeurs d'initialisation faite dans le code
	  * en mode thread privilégié, avec la pile MSP
	
	Il faut maintenant que l'on passe en mode "noyau" pour initiliaser le noyau et lancer
	notre premier processus utilisateur comme un restitution de contexte normal (via un retour
	d'exception, l'entrée dans le noyau se faisant via une exception)
	
	Hors le cortex M3 ne veut pas faire de retour d'exception en mode thread même en mode
	privilégié, ceci génère une faute matérielle, il faut donc faire une exception pour prendre la
	main dans le bon mode
	
	Plusieurs solutions (il y en a peut-être d'autres):
	  * faire une exception logicielle (SVC) : problème, on va utiliser SVC par la suite, il ne 
		  faudrait pas que un utilisateur réutilise cet appel système qui initialise le noyau. 2 solutions :
      * 1a) on change la table d'exception (via le vecteur de relocation du nvic)
      * 1b) lors des appels systèmes, on n'autorise cet appel qu'à partir d'un thread privilégié  			
	  * 2) on utilise une exception qui ne sert pas et que l'on ne peut pas appelée en mode thread non
		  privilégié, par exemple Pend_SVC en activant l'exception par logiciel dans le NVIC
		
		Pour l'étape 1, nous allons faire simple et utilisé un simple SVC. Pour les étapes suivantes,
		à vous de voir (mais je vous donnerai le code de 1a).
		Personnellement je trouve 1a plus "élégant" et carré, 1b est plus touchy et 2 est plus de la bidouille.
		
	*/
	
	// appel d'une fonction en assembleur pour faire le SVC 
	// on pourrait le faire via du C ou via une instruction assembleur insérée directement
	
	appelSvcInitNoyau();

	// on ne revient pas ici mais afin de parer à tout problème
	// vous pouvez imaginer ici un appel à une fonction panicKernel avec un système d'erreur et de message
	
	while (true) ;

}
