/*
SmartPlots.h - Library for smart plots with RFM69HCW only.
Requires the RFM69 library to run this library.
Created by DEROO Matthieu, February 13, 2025.
Released into the public domain.
*/

#ifndef Master_h
#define Master_h

#include "SmartPlots.h"

class Master : public SmartPlots {
public:
	Master(); // Constructeur

	/*------------------------------------------------------------------------------------------------------------------------*/

	void sendCommand(const uint8_t ref_command); // Envoi la commande demander d'apres le protocole de chaque commande		--> pas encore terminer

};

#endif // !Master_h