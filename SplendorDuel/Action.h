#pragma once

/// <summary>
/// Classe contenant les Actions pouvant être réaliser par le joeur
/// Impossible = pas possible de faire l'action
/// </summary>
enum Action {
	MAIN_ACTION = -1,
	REPLAY = 1,
	// OPTIONAL ACTIONS
	USE_PRIVILEGE = 0,
	FILL_BOARD = 1,
	// MANDATORY ACTIONS
	
	PICK_GEMMES = 3,
	ASIGN_CARD = 5,
	STEAL_GEMMES = 4,
	ADD_PRIVILEGE = 2,
	RESERV_CARD = 6,
	//RETURN FUNCTION OPTIONS
	IMPOSSIBLE = -2,
};