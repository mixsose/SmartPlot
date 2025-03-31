/*
SmartPlots.h - Library for smart plots with RFM69HCW only.
Requires the RFM69 library to run this library.
Created by DEROO Matthieu, February 13, 2025.
Released into the public domain.
*/

#ifndef Plot_h
#define Plot_h

#include "SmartPlots.h"

class Plot : public SmartPlots {
public:
	Plot(); // Constructeur

	/*------------------------------------------------------------------------------------------------------------------------*/

	void sendReply(const uint8_t ref_command); // Envoi la reponse du plot par raport a la demande du master			--> pas encore terminer

private:
	uint16_t _metric; // Numero du plot dans la chaine, réinitialiser a chaque mise en réseau
};

#endif // !Plot_h
