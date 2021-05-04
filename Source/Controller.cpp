/*
  ==============================================================================

    Controller.cpp
    Created: 2 May 2021 6:47:52pm
    Author:  Matt

  ==============================================================================
*/

#include "Controller.h"

// Define a static member variable for the interface.
// This has to happen in the .cpp file or there will be
// linker errors.
IController* Controller::m_pController = nullptr;

Controller::Controller()
{
	jassert( m_pController == nullptr );
	m_pController = this;
}

Controller::~Controller()
{
	jassert( m_pController != nullptr );
	m_pController = nullptr;
}
