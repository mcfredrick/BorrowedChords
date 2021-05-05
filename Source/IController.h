/*
  ==============================================================================

    IController.h
    Created: 2 May 2021 10:18:04pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

struct Note;
struct Scale;

class IController
{
public:
	virtual ~IController() {};
	
	virtual void SetRootNote( Note note ) = 0;
	virtual Note GetRootNote() = 0;
	
	virtual void SetHomeScale( Scale scale ) = 0;
	virtual Scale GetHomeScale() = 0;
};
