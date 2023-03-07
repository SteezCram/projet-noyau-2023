#include "constC.h"

IMPORT void affiche(const char*);

/*------------------------------------------------------------------------------
	Description : fonction invoquée par défaut en terminaison de processus
*/
EXPORT void detruitProcessusAppelant() {
  affiche("declenchera detruitProcessus(obtientPid())");
  while (true);				// evite de partir dans la nature à la fin
}
