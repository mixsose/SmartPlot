/*
SmartPlots.h - Library for smart plots with RFM69HCW only.
Requires the RFM69 library to run this library.
Created by DEROO Matthieu, February 13, 2025.
Released into the public domain.
*/

#include "Plot.h"

/* ------------------------------------------------------------------------------------------------------------------------
 * Constructeur: Initialise la classe Plot
 *
 * - Initialise le module radio RFM69
 * ------------------------------------------------------------------------------------------------------------------------ */
Plot::Plot() {
	this->radio.initialize(FREQUENCY, MYNODEID, NETWORKID); // Initialise le module radio
	this->radio.setHighPower(); // obligatoire pour ce module
}

/* ------------------------------------------------------------------------------------------------------------------------
 * Fonction: sendCommand
 * Envoi la reponse du plot par raport a la demande du master
 *
 * Parametre:
 * - referance de la commande, sur 4 bits
 * ------------------------------------------------------------------------------------------------------------------------ */
void Plot::sendReply(const uint8_t ref_command) {

}