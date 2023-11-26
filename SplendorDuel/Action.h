#pragma once

/// <summary>
/// Classe contenant les Actions pouvant être réaliser par le joeur
/// Impossible = pas possible de faire l'action
/// </summary>
enum Action {
	MAIN_ACTION = 1,
	PICK_GEMMES = 2,
	FILL_BOARD = 3,
	ADD_PRIVILEGE = 4,
	BUY_CARD = 5,
	
	IMPOSSIBLE = 10,
};