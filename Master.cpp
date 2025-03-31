/*
SmartPlots.h - Library for smart plots with RFM69HCW only.
Requires the RFM69 library to run this library.
Created by DEROO Matthieu, February 13, 2025.
Released into the public domain.
*/

#include "Master.h"

/* ------------------------------------------------------------------------------------------------------------------------
 * Constructeur: Initialise la classe Master
 *
 * - Initialise le module radio RFM69
 * - crée pour la première fois l'id de commande par un nombre aleatoir (0-15)
 * ------------------------------------------------------------------------------------------------------------------------ */
Master::Master() {
    this->radio.initialize(FREQUENCY, MYNODEID, NETWORKID); // Initialise le module radio
    this->radio.setHighPower(); // obligatoire pour ce module
    this->_id_command_send = (random() & 0xF); // Initialise l'id par un nbr aleatoire
}

/* ------------------------------------------------------------------------------------------------------------------------
 * Fonction: sendCommand
 * Envoi une commande basé sur le protocole
 *
 * Parametre:
 * - referance de la commande, sur 4 bits
 * ------------------------------------------------------------------------------------------------------------------------ */
void Master::sendCommand(const uint8_t ref_command) {
	if (ref_command & 0xF0) {
		Serial.println("le commande n'existe pas");
		return; // Vérifie que la referance est bien sur 4bits
	}

	if (ref_command == MASTER_IF_PLOTS_FALLEN) {
		Serial.println("MASTER_IF_PLOTS_FALLEN envoyer");
		this->_id_command_send++; // Crée la nouvelle Id pour la nouvelle commande
		uint8_t message_master_if_plots_fallen = ((ref_command << 4) + (this->_id_command_send & 0x0F));
		this->radio.send(TONODEID, &message_master_if_plots_fallen, 1);
	}
	else if (ref_command == MASTER_IF_PLOTS_LOW_BATTERY) {
		Serial.println("MASTER_IF_PLOTS_LOW_BATTERY envoyer");
		this->_id_command_send++; // Crée la nouvelle Id pour la nouvelle commande
		uint8_t message_master_if_plots_low_battery = ((ref_command << 4) + (this->_id_command_send & 0x0F));
		this->radio.send(TONODEID, &message_master_if_plots_low_battery, 1);
	} else {
			Serial.println("Valeur non reconnue dans le switch");
	}
}