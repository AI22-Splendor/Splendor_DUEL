#include "CardEffectTakePrivilege.h"
#include "PrivilegeHandler.h"


void CardEffectTakePrivilege::executeEffect() {
	PrivilegeHandler::getInstance()->givePlayerPrivilege(player);
}