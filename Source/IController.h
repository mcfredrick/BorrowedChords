/*
  ==============================================================================

    IController.h
    Created: 2 May 2021 10:18:04pm
    Author:  Matt

  ==============================================================================
*/

#pragma once
#include "Broadcaster.h"
#include "Types.h"

struct Note;
struct Scale;

class IController	:
	public ModelBroadcaster
{
public:
	virtual ~IController() {};
	
	virtual void SetRootNote( Note note ) = 0;
	virtual Note GetRootNote() = 0;
	
	virtual void SetHomeScale( Scale scale ) = 0;
	virtual Scale GetHomeScale() = 0;

	virtual ESharpsFlats GetSharpsOrFlats() = 0;
	virtual void SetSharpsOrFlats( ESharpsFlats choice ) = 0;
};
