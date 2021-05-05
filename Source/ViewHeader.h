/*
  ==============================================================================

    View.h
    Created: 2 May 2021 6:59:03pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "ComponentBase.h"
#include "Includes.h"
#include "IController.h"
#include "Main.h"

inline static IController& GetController()
{
	return BorrowedChordsApplication::getController();
}


