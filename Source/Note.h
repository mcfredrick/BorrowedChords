/*
  ==============================================================================

    Note.h
    Created: 2 May 2021 9:16:01pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

#include "Includes.h"

enum class ENoteLetter
{
	A = 0,
	B,
	C,
	D,
	E,
	F,
	G
};

juce::String NoteLetters[]
{
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G"
};

enum class EPitchModifier
{
	flat = 0,
	natural,
	sharp
};

juce::String PitchModifiers[]
{
	"b",
	"",
	"#"
};

struct Note
{
	juce::String GetNoteLetterString()
	{
		return NoteLetters[int(letter)];
	}
	
	juce::String GetPitchModifierString()
	{
		return PitchModifiers[int(modifier)];
	}
	
	juce::String GetDescription()
	{
		return juce::String( GetNoteLetterString() + GetPitchModifierString() );
	}
	
	ENoteLetter letter;
	EPitchModifier modifier;
};
