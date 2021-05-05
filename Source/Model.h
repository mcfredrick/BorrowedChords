/*
  ==============================================================================

    Model.h
    Created: 2 May 2021 9:15:28pm
    Author:  Matt

  ==============================================================================
*/

#pragma once
#include "../Source/Broadcaster.h"
#include "Note.h"
#include "Scale.h"

class Model	:
public	ModelBroadcaster
{
public:
	Model(){};
	~Model(){};
	
	void SetRootNote( Note note ) { m_rootNote = note; }
	Note GetRootNote() const { return m_rootNote; }
	
	void SetHomeScale( Scale scale ) { m_homeScale = scale; }
	Scale GetHomeScale() const { return m_homeScale; }
	
private:
	Note m_rootNote;
	Scale m_homeScale;
};
