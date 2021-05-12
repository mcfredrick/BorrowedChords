/*
  ==============================================================================

    Note.h
    Created: 2 May 2021 9:16:01pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

#include "Includes.h"
#if 0
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
#endif
struct Note
{
	Note( int pitchNum ) :
		pitch( pitchNum )
	{}

	// Default to C
	Note() :
		pitch( 0 )
	{}
	
	
	// pitch is the degree of the chromatic scale starting at C which this represents
	int pitch = 0;
	
	static juce::String GetNoteDescr( int pitch )
	{
		return juce::MidiMessage::getMidiNoteName( pitch, true, false, 4 );
	}

	juce::String GetNoteDescr()
	{
		return GetNoteDescr( pitch );
	}
	
	// Scales with the same name should be the same.
	bool operator==( const Note& other )
	{
		return other.pitch == pitch;
	}

	friend bool operator<( const Note& l, const Note& r )
	{
		return l.pitch < r.pitch;
	}

#if 0
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
#endif
};
