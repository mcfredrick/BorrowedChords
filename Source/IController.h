/*
  ==============================================================================

    IController.h
    Created: 2 May 2021 10:18:04pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

class IController
{
public:
	virtual ~IController() {};
	
	virtual void SetRootNote() = 0;
};
