/*
SmartPlots.h - Library for smart plots with RFM69HCW only.
Requires the RFM69 library to run this library.
Created by DEROO Matthieu, February 13, 2025.
Released into the public domain.
*/

#include "SmartPlots.h"

// Constructeur
SmartPlots::SmartPlots() {
	// Aucune Action requise ici
}

/* ------------------------------------------------------------------------------------------------------------------------
 * Fonction: setRefCommandSend
 * Définit la référence de la commande à envoyer.
 *
 * Paramètre:
 * - ref_command: Référence de la commande (4 bits).
 * ------------------------------------------------------------------------------------------------------------------------ */
void SmartPlots::setRefCommandSend(const uint8_t ref_command) {
	this->_ref_command_send = ref_command & 0xF; // Conserve uniquement les 4 bits inférieurs
}

/* ------------------------------------------------------------------------------------------------------------------------
 * Fonction: setDataCommandSend
 *  Défifinit les data contenue dans le message ainsi que la taille du tableau data en nombre de bits utiles
 *
 * Paramètre:
 * - data: Valeur uint32_t max representant les données
 * - data_syze : correspond au nombre de bits utils qu'utilise les données
 * ------------------------------------------------------------------------------------------------------------------------ */
void SmartPlots::setDataCommandSend(const uint32_t data, const uint8_t data_size) {
	for (int i = 0; i < 4; i++) { // Met toute les valeur du tableau a zero
		this->_data_send[i] = 0;
	}
	data << (32 - data_size); // Decale les bits de data pour que le bit de point fort de data soit le bits de point fort des données
	this->_data_size = data_size;
	for (int i = 0; i < 4; i++) { // Decoupe data et le fait rentré des _data_send
		this->_data_send[i] = data >> (24 - 8 * i);
	}
}

/* ------------------------------------------------------------------------------------------------------------------------
 * Fonction: getRefCommandReceived
 * Récupère la référence de la commande reçue.
 *
 * Retourne:
 * - La référence de la commande (4 bits).
 * ------------------------------------------------------------------------------------------------------------------------ */
uint8_t SmartPlots::getRefCommandReceived() const {
	return this->_ref_command_received;
}

/* ------------------------------------------------------------------------------------------------------------------------
 * Fonction: getIdCommandReceived
 * Récupère l'ID de la commande reçue.
 *
 * Retourne:
 * - L'ID de la commande (4 bits).
 * ------------------------------------------------------------------------------------------------------------------------ */
uint8_t SmartPlots::getIdCommandReceived() const {
	return this->_id_command_received;
}

/* ------------------------------------------------------------------------------------------------------------------------
 * Fonction: getDataCommandReceived
 * Récupère les données de la commande reçue.
 *
 * Retourne:
 * - Pointeur vers un tableau de 4 octets contenant les données.
 * ------------------------------------------------------------------------------------------------------------------------ */
uint8_t* SmartPlots::getDataCommandReceived() const {
	return this->_data_received;
}

/* ------------------------------------------------------------------------------------------------------------------------
 * Fonction: DecrypteMessage
 * Récupère le message recue et extrait les données selon le protocole
 * Met a jour la ref, l'Id et la data du message recue
 * ------------------------------------------------------------------------------------------------------------------------ */
void SmartPlots::DecrypteMessage() {
	uint8_t message_received[5] = { 0, 0, 0, 0, 0 }; // crée un tableau temporaire contenant le message recue
	for (int i;  (this->radio.DATALEN > 0) || (i < 5); i++) {
		message_received[i] = this->radio.DATA[i];
	}
	this->_ref_command_received = (message_received[0] & 0xF0);
	this->_id_command_received = (message_received[0] & 0xF);
	for (int i = 0; i < 4; i++) {
		this->_data_received[i] = message_received[i + 1];
	}
}

/* ------------------------------------------------------------------------------------------------------------------------
 * Fonction: received
 * Vérifie si un message est recue
 * Si un message est recue, recupère le message et le decrypte
 *
 * Returne:
 * - TRUE si un message est recue et qu'il est bien decrypté
 * ------------------------------------------------------------------------------------------------------------------------ */
 bool SmartPlots::received() {
	 if ((this->radio.receiveDone()) || (this->radio.DATALEN < 5)) {
		 this->DecrypteMessage();
		 return true;
	 }
	 else return false;
 }