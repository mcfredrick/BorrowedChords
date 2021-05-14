/*
  ==============================================================================

    Note.h
    Created: 2 May 2021 9:16:01pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

#include "Includes.h"
#include "Types.h"

struct BaseNote
{
	BaseNote( int pitchNum ) :
		pitch( pitchNum )
	{}

	// Default to C
	BaseNote() :
		pitch( 0 )
	{}
	
	// pitch is the degree of the chromatic scale starting at C which this represents
	int pitch = 0;

	static juce::String GetNoteDescr( int pitch, bool useSharps )
	{
		return juce::MidiMessage::getMidiNoteName( pitch, useSharps, false, 4 );
	}

	static juce::String GetNoteDescr( int pitch, ESharpsFlats choice )
	{
		switch ( choice )
		{
		case ESharpsFlats::sharps:
			return GetNoteDescr( pitch, true );
		case ESharpsFlats::flats:
			return GetNoteDescr( pitch, false );
		case ESharpsFlats::both:
			auto withSharps = GetNoteDescr( pitch, true );
			if ( withSharps.contains( "#" ) )
				return GetNoteDescr( pitch, false ) + " / " +  withSharps;
			else
				return withSharps;
		}

		return "No Note Description.";
	}

	juce::String GetNoteDescr( bool useSharps )
	{
		return GetNoteDescr( pitch, useSharps );
	}
	
	juce::String GetNoteDescr( ESharpsFlats choice )
	{
		return GetNoteDescr( pitch, choice );
	}

	// Scales with the same name should be the same.
	bool operator==( const BaseNote& other )
	{
		return other.pitch == pitch;
	}

	BaseNote& operator+=( const int& incr ) 
	{
		pitch += incr;
		while ( pitch > 11 )
			pitch -= 12;
		return *this;
	}

	friend bool operator<( const BaseNote& l, const BaseNote& r )
	{
		return l.pitch < r.pitch;
	}
};

#include "IController.h"
#include "Main.h"

struct Note :
	public BaseNote
{
	Note( int pitchNum ) :
		BaseNote( pitchNum )
	{}

	// Default to C
	Note() :
		BaseNote( 0 )
	{}

	inline static IController& GetController()
	{
		return BorrowedChordsApplication::getController();
	}

	static juce::String GetNoteDescr( int pitch )
	{
		return BaseNote::GetNoteDescr( pitch, GetController().GetSharpsOrFlats() );
	}

	juce::String GetNoteDescr()
	{
		return BaseNote::GetNoteDescr( pitch, GetController().GetSharpsOrFlats() );
	}
};
