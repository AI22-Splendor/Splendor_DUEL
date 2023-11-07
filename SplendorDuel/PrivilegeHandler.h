#pragma once


class PrivilegeHandler {
public:
	// On supprime la recopie (singleton)
	PrivilegeHandler(PrivilegeHandler& copie) = delete;
	// On supprime l'opérateur d'affectation (singleton)
	void operator=(const PrivilegeHandler&) = delete;

	static PrivilegeHandler* getInstance();


private:
	// On empêche la construction du singleton
	PrivilegeHandler() {}

	static PrivilegeHandler* singleton;
	enum PrivilegePosition { Board = 1, Player1 = 2, Player2 = 3 };

	PrivilegePosition* emplacementsPrivilege = new PrivilegePosition[3];
};

