#include "PrivilegeHandler.h"

PrivilegeHandler* PrivilegeHandler::singleton = nullptr;

PrivilegeHandler* PrivilegeHandler::getInstance() {
	if (singleton) {
		return singleton;
	}
	
	singleton = new PrivilegeHandler();
	for (int i = 0; i < 3; i++) {
		singleton->emplacementsPrivilege[i] = PrivilegePosition::Board;
	}

	return singleton;
}