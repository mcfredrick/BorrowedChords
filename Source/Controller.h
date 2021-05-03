/*
  ==============================================================================

    Controller.h
    Created: 2 May 2021 6:47:52pm
    Author:  Matt

  ==============================================================================
*/

#pragma once
#include "Includes.h"
#include "IController.h"

class Controller	:
public IController
{
public:
	Controller()
	{
		jassert( s_pController == nullptr );
		s_pController = this;
	}
	
	inline static IController& GetInstance()
	{
		jassert( s_pController != nullptr );
		return *s_pController;
	}
	
private:
	static IController*	s_pController;
};
