/*
SmartPlots.h - Library for smart plots with RFM69HCW only.
Requires the RFM69 library to run this library.
Created by DEROO Matthieu, February 13, 2025.
Released into the public domain.
*/

#ifndef SmartPlots_h
#define SmartPlots_h

#include <Arduino.h>
#include <RFM69.h>

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
RFM69 configuration variables
These settings must be the same for all nodes for proper communication.
*/

#define NETWORKID     0   // Network ID (Must be the same for all nodes)
#define MYNODEID      1   // My node ID
#define TONODEID      255 // Destination node ID (255 for broadcast)

#define FREQUENCY     RF69_433MHZ // Communication frequency (433MHz)

#define ENCRYPT       false // Set to "true" to enable encryption
#define ENCRYPTKEY    "TOPSECRETPASSWRD" // 16-byte encryption key for all nodes

#define USEACK        false // Set to "true" to request acknowledgment (ACK)

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------------------------------------------------------------
Command send by the Master
-------------------------------------------------------------------------------------------------------------------------------*/

#define MASTER_IF_PLOTS_FALLEN 0x0 // Master asks for the status of the plots (fallen or not)
/*
Communication protocol using 1 octet (8 bits)

 |           Header            |
 | Ref Command  |  ID Command  |
 |    4 bits    |    4 bits    |
 |     0000     |     0000     |
*/

/*---------------------------------------------------------------------------------*/

#define MASTER_IF_PLOTS_LOW_BATTERY 0x1  // Master asks for the battery status of the plots (low or high)
/*
Communication protocol using 1 octet (8 bits)

 |           Header            |
 | Ref Command  |  ID Command  |
 |    4 bits    |    4 bits    |
 |     0001     |     0000     |
*/

/*---------------------------------------------------------------------------------*/

#define MASTER_TEST_NETWORK 0x2 // Master tests the network (e.g., ping all nodes)

/*---------------------------------------------------------------------------------*/

#define MASTER_NOT_DEFINED_3 0x3 // Reserved for future use

/*---------------------------------------------------------------------------------*/

#define MASTER_NOT_DEFINED_4 0x4 // Reserved for future use

/*---------------------------------------------------------------------------------*/

#define MASTER_NOT_DEFINED_5 0x5 // Reserved for future use

/*---------------------------------------------------------------------------------*/

#define MASTER_NOT_DEFINED_6 0x6 // Reserved for future use

/*---------------------------------------------------------------------------------*/

#define MASTER_NOT_DEFINED_7 0x7 // Reserved for future use

/*-------------------------------------------------------------------------------------------------------------------------------
Command sent by a plot node
-------------------------------------------------------------------------------------------------------------------------------*/

#define PLOT_FALLEN 0x8 // Plot node sends a "fallen" status

/*---------------------------------------------------------------------------------*/

#define PLOT_LOW_BATTERY 0x9 // Plot node sends a "low battery" status

/*---------------------------------------------------------------------------------*/

#define PLOT_HERE 0xA // Plot node sends a "here" status (e.g., presence confirmation)

/*---------------------------------------------------------------------------------*/

#define PLOT_MAYBE_RESEARCH 0xB // Plot node sends a "maybe research" status (e.g., uncertain state)

/*---------------------------------------------------------------------------------*/

#define PLOT_NOT_DEFINED_C 0xC // Reserved for future use

/*---------------------------------------------------------------------------------*/

#define PLOT_NOT_DEFINED_D 0xD // Reserved for future use

/*---------------------------------------------------------------------------------*/

#define PLOT_NOT_DEFINED_E 0xE // Reserved for future use

/*---------------------------------------------------------------------------------*/

#define PLOT_NOT_DEFINED_F 0xF // Reserved for future use

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


class SmartPlots {
public:
	SmartPlots(); // Constructeur pour initialiser l'objet SmartPlots

	/*------------------------------------------------------------------------------------------------------------------------*/

	void DecrypteMessage(); // Récupère le message recue et extrait les données selon le protocole
	bool received(); // Renvoi TRUE si un message et recue et qu'il a été recupérer correctement

	/*------------------------------------------------------------------------------------------------------------------------*/

	void setRefCommandSend(const uint8_t ref_command); // definit le type de commande envoyer
	void setDataCommandSend(const uint32_t data, const uint8_t data_size); // Definit les data contenue dans le message

	/*------------------------------------------------------------------------------------------------------------------------*/

	uint8_t getRefCommandReceived() const; // Récupère la referance de la commande recue
	uint8_t getIdCommandReceived() const; // Récupère l'Id de la commande recue
	uint8_t* getDataCommandReceived() const; // Récupère le pointeur du tableau où sont stockée les data du message recue

protected:
	uint8_t _ref_command_send; // Référence de la commande à envoyer (4 bits)
	uint8_t _id_command_send; // ID de la commande à envoyer (4 bits)
	uint8_t _data_send[4]; // Données du message à envoyer (4 octets)
	uint8_t _data_size; // Taille des data en bits

	uint8_t _ref_command_received; // Référence de la commande reçue (4 bits)
	uint8_t _id_command_received; // ID de la commande reçue (4 bits)
	uint8_t _data_received[4]; // Données du message reçu (4 octets)

	RFM69 radio; // Objet RFM69 pour la communication radio
};


#endif // !SmartPlots_h
