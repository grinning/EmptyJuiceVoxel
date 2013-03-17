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

	// My proposal - Andrew
	namespace Action
	{
	    struct Base
	    {
	        const ActionType type;

	        Base(ActionType _type = ACTION_UNKNOWN) : type(_type)
	        {
	            if (type >= ACTION_COUNT) type = ACTION_UNKNOWN;
	        }

	        // TODO: Add more info (like player, world e.t.c.)
	    };

	    struct ItemUse : public Base
	    {
	        ItemUseType useType;

	        ItemUse(ItemUseType _useType) : Base(ACTION_ITEM_USE), useType(_useType) {}
	    };

	    struct ItemChange : public Base
	    {
	        unsigned short newSlot; // I am not really sure about this - Andrew

	        ItemChange(unsigned short _newSlot) : Base(ACTION_ITEM_USE), newSlot(_newSlot) {}
	    };

	    struct KeyPress : public Base
	    {
	        KeyboardKey key;

	        KeyPress(KeyboardKey _key) : Base(ACTION_KEY_PRESS), key(_key) {}
	    };

	    struct MenuSelect : public Base
	    {
	        MenuSelect() : Base(ACTION_MENU_SELECT) {}
	    };

	    struct Chat : public Base
	    {
	        std::string message;

	        Chat(const std::string& _message) : Base(ACTION_CHAT), message(_message) {}
	    };
	}
}

#endif //ACTION_INCLUDED
