/*
  ==============================================================================

    Types.h
    Created: 13 May 2021 9:41:07pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

enum class ESharpsFlats
{
	none,
	sharps,
	flats,
	both,
	numOfOptions
};

enum class EChordComplexity
{
	none = 0,
	triad,
	seventh,
	numOfOptions
};

const juce::String AllChordComplexities[] =
{
	"none",
	"Triad",
	"Seventh",
	"numOfOptions"
};