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
	Scale() :
		intervals( { 2, 2, 1, 2, 2, 2, 1 } ),
		name( "Major" ),
		triads( { "", "min", "min", "", "", "min", "dim" } ),
		seventhChords( { "maj7", "min7", "min7", "maj7", "7", "min7", "m7b5" } )
	{}
	
	Scale( std::vector<int> intervalVector,
		juce::String scaleName,
		std::vector<juce::String> triads,
		std::vector<juce::String> seventhChords ) :
		intervals( intervalVector ),
		name( scaleName ),
		triads( triads ),
		seventhChords( seventhChords )
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
	std::vector<juce::String> triads;
	std::vector<juce::String> seventhChords;
};

static Scale MajorScale( std::vector<int>( { 2, 2, 1, 2, 2, 2, 1 } ), 
	"Major", 
	std::vector<juce::String>( { "", "min", "min", "", "", "min", "dim" } ),
	std::vector<juce::String>( { "maj7", "min7", "min7", "maj7", "7", "min7", "m7b5" } ) );

static Scale NaturalMinorScale( std::vector<int>( { 2, 1, 2, 2, 1, 2, 2 } ),
	"Nat. Minor",
	std::vector<juce::String>( { "min", "dim", "", "min", "min", "", "" } ),
	std::vector<juce::String>( { "min7", "m7b5", "maj7", "min7", "min7", "maj7", "7" } ) );

static Scale AllScales[] =
{
	MajorScale,
	NaturalMinorScale
};
