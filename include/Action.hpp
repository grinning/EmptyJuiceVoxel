/*#****************************************************************#*
 * Empty Juice Voxel: Minecraft clone by the Empty Juice Box Group  *
 * www              : http://www.juicebox.ckef-worx.com             *
 * Copyright (c) Empty Juice Box Group :: All Rights Reserved       *
 *#****************************************************************#*/

#ifndef ACTION_INCLUDED
#define ACTION_INCLUDED

#include "Chunk.hpp"

/**
 * @file Interface for actions
 *
 */
namespace EJV
{
	enum ActionType
	{
	    ACTION_UNKNOWN,

		ACTION_ITEM_USE,
		ACTION_ITEM_CHANGE,

		ACTION_KEY_PRESS,

		ACTION_MENU_SELECT,

		ACTION_CHAT,

		ACTION_COUNT
	};

	enum ItemUseType
	{
		ITEM_USE_PRIMARY,
		ITEM_USE_SENCONDARY,
		ITEM_USE_CANCEL
	};

	enum KeyboardKey
	{
	    // Movement
		KEY_FORWARD,
		KEY_BACKWARD,
		KEY_LEFT,
		KEY_IGHT,

		// Stance
		KEY_JUMP,
		KEY_SNEAK,

		// Items
		KEY_INVENTORY,
		KEY_DROP
	}

    // I suggest we use inheritance instead of unions - Andrew
	/*struct Action
	{
		ActionType type;

		union data
		{
		    std::string message;//This is REALLY bad. Dear god. Will this even compile?
			ItemUseType itemUsed;
			int changedTo;
			KeyboardKey key;
		}
	}*/

	// My proposal - Andrew + Invalid
	namespace Action
	{
	    struct Base
	    {
	        const ActionType type;

	        inline Base(ActionType t) : type(t >= ACTION_COUNT ? ACTION_UNKNOWN : t) {}

	        // TODO: Add more info (like player, world e.t.c.)
	    };

	    struct ItemUse : public Base
	    {
	        const ItemUseType useType;

	        inline ItemUse(ItemUseType _useType) : Base(ACTION_ITEM_USE), useType(_useType) {}
	    };

	    struct ItemChange : public Base
	    {
	        const unsigned short newSlot; // I am not really sure about this - Andrew

	        inline ItemChange(unsigned short _newSlot) : Base(ACTION_ITEM_USE), newSlot(_newSlot) {}
	    };

	    struct KeyPress : public Base
	    {
	        const KeyboardKey key;

	        inline KeyPress(KeyboardKey _key) : Base(ACTION_KEY_PRESS), key(_key) {}
	    };

	    struct MenuSelect : public Base
	    {
	        inline MenuSelect() : Base(ACTION_MENU_SELECT) {}
	    };

	    struct Chat : public Base
	    {
	        const std::string message;

	        inline Chat(const std::string& _message) : Base(ACTION_CHAT), message(_message) {}
	    };
	}
}

#endif //ACTION_INCLUDED
