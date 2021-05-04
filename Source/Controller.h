/*
  ==============================================================================

    Controller.h
    Created: 2 May 2021 6:47:52pm
    Author:  Matt

  ==============================================================================
*/

#pragma once
#include "IController.h"
#include "Includes.h"
#include "Model.h"
#include "Broadcaster.h"

class Controller	:
public IController,
public ModelBroadcaster
{
public:
	friend class BorrowedChordsApplication;
	
	Controller();
	~Controller();
	
	// No copying or deleting. Sorry, bud.
	Controller( Controller const& ) = delete;
	void operator=( Controller const& ) = delete;
	
	void SetRootNote() override
	{
		NotifyListeners( EModelChange::RootChanged/*, newNote*/ );
	}
	
	inline static IController& GetInstance()
	{
		jassert( m_pController != nullptr );
		return *m_pController;
	}
	
private:
	static IController* m_pController;
	Model m_model;
};
