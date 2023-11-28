#pragma once

/// <summary>
/// Classe contenant les Actions pouvant être réaliser par le joeur
/// Impossible = pas possible de faire l'action
/// </summary>
enum Action {
	MAIN_ACTION = 0,
	// OPTIONAL ACTIONS
	USE_PRIVILEGE = 1,
	// MANDATORY ACTIONS
	FILL_BOARD = 2,

	PICK_GEMMES = 3,
	RESERV_CARD = 4,
	BUY_CARD = 5,
	STEAL_GEMMES = 6,

	ADD_PRIVILEGE = 9,
	IMPOSSIBLE = 10,
};