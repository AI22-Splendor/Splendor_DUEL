#pragma once

/// <summary>
/// Classe contenant les Actions pouvant être réaliser par le joeur
/// Impossible = pas possible de faire l'action
/// </summary>
enum Action {
	MAIN_ACTION = -1,
	
	// OPTIONAL ACTIONS
	USE_PRIVILEGE = 7,
	FILL_BOARD = 8,

	// Card Effects
	REPLAY = 1,
	ADD_PRIVILEGE = 2,
	PICK_GEMMES = 3,
	STEAL_GEMMES = 4,
	ASSIGN_CARD = 5,
	RESERV_CARD = 6,

	//RETURN FUNCTION OPTIONS
	IMPOSSIBLE = -2,
};