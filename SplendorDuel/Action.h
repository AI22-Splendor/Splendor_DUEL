#pragma once

/// <summary>
/// Classe contenant les Actions pouvant �tre r�aliser par le joeur
/// Impossible = pas possible de faire l'action
/// </summary>
enum Action {
	MAIN_ACTION = 0,
	// OPTIONAL ACTIONS
	USE_PRIVILEGE = 1,
	FILL_BOARD = 2,
	// MANDATORY ACTIONS
	PICK_GEMMES = 3,
	RESERV_CARD = 4,
	BUY_CARD = 5,
	ADD_PRIVILEGE = 9,
	IMPOSSIBLE = 10,
};