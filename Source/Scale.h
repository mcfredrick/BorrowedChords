/*
  ==============================================================================

    Scale.h
    Created: 2 May 2021 9:15:46pm
    Author:  Matt

  ==============================================================================
*/

#pragma once
#include "Includes.h"

struct Scale
{
	Scale()	:
	intervals( { 2, 2, 1, 2, 2, 2, 1 } ),
	name( "Major" )
	{}
	
	Scale( std::vector<int> intervalVector, juce::String scaleName )	:
	intervals( intervalVector ),
	name( scaleName )
	{}
	
	// Scales with the same name should be the same.
	bool operator==( const Scale& other )
	{
		return other.name == name;
	}

	friend bool operator<( const Scale& l, const Scale& r )
	{
		return l.name < r.name;
	}

	std::vector<int> intervals;
	juce::String name;
};

static Scale MajorScale( std::vector<int>( { 2, 2, 1, 2, 2, 2, 1 } ), "Major" );
static Scale NaturalMinorScale( std::vector<int>( { 2, 1, 2, 2, 1, 2, 2 } ), "Nat. Minor" );

static Scale AllScales[] =
{
	MajorScale,
	NaturalMinorScale
};
