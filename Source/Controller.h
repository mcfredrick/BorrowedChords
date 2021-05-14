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

class Controller	:
public IController
{
public:
	friend class BorrowedChordsApplication;
	
	Controller();
	~Controller();
	
	// No copying or deleting. Sorry, bud.
	Controller( Controller const& ) = delete;
	void operator=( Controller const& ) = delete;
	
	inline static IController& GetInstance()
	{
		jassert( m_pController != nullptr );
		return *m_pController;
	}
	
	void SetRootNote( Note note ) override
	{
		m_model.SetRootNote( note );
		ModelBroadcaster::NotifyListeners( EModelChange::RootChanged );
	}
	
	Note GetRootNote() override
	{
		return m_model.GetRootNote();
	}
	
	void SetHomeScale( Scale scale ) override
	{
		m_model.SetHomeScale( scale );
		NotifyListeners( EModelChange::ScaleChanged );
	}
	
	Scale GetHomeScale() override
	{
		return m_model.GetHomeScale();
	}
	
	ESharpsFlats GetSharpsOrFlats() override
	{
		return m_sharpsFlats;
	}
	
	void SetSharpsOrFlats( ESharpsFlats choice ) override
	{
		m_sharpsFlats = choice;
		NotifyListeners( EModelChange::SharpsFlats );
	}

private:
	static IController* m_pController;
	Model m_model;
	ESharpsFlats m_sharpsFlats = ESharpsFlats::both;
};
