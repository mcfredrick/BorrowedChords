/*
  ==============================================================================

    ChordTable.h
    Created: 2 May 2021 6:49:01pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

#include "ViewHeader.h"
#include "Note.h"
#include "Scale.h"
#include "Broadcaster.h"

namespace view
{
	class ChordTableModel	:
		public juce::TableListBoxModel
	{
	public:
		int getNumRows () override
		{
			return 4;
		}

		void paintRowBackground (juce::Graphics & g, int /*rowNumber*/, int /*width*/, int /*height*/, bool /*rowIsSelected*/ ) override
		{
			g.setColour( juce::Colours::white );
			g.drawRect( g.getClipBounds() );
		}

		void paintCell (juce::Graphics & g, int rowNumber, int columnId, int /*width*/, int /*height*/, bool /*rowIsSelected*/) override
		{
			g.setColour( juce::Colours::white );
			g.drawRect( g.getClipBounds() );
			auto text = columnId == 1 ? GetScaleRelation( rowNumber ) : "Chord";
			g.drawFittedText( text, g.getClipBounds(), juce::Justification::centredLeft, 1 );
		}

		// TODO: cache these when something changes and look them up. We can then look up the rest of the cells in the row based
		// on the scale represented by the row.
		// TODO: add a column just for the relationship to the home scale.
		// TODO: suppress juce warnings
		juce::String GetScaleRelation( int rowNum )
		{
			switch ( rowNum )
			{
			case 0:
				return "Home: " + GetController().GetRootNote().GetNoteDescr() + " " + GetController().GetHomeScale().name;
				
			case 1:
			{
				auto scale = GetController().GetHomeScale();
				auto rootNote = GetController().GetRootNote();
				juce::String relScale = scale == MajorScale ? "Min" : "Maj";
				auto incr = scale == MajorScale ? 9 : 3;
				rootNote += incr;
				return "Rel. " + relScale + ": " + rootNote.GetNoteDescr() + " " + relScale;
			}
			case 2:
			{
				auto scale = GetController().GetHomeScale();
				auto rootNote = GetController().GetRootNote();
				juce::String parScale = scale == MajorScale ? "Min" : "Maj";
				return "Par. " + parScale + ": " + rootNote.GetNoteDescr() + " " + parScale;
			}
			case 3:
			{
				auto scale = GetController().GetHomeScale();
				auto rootNote = GetController().GetRootNote();
				juce::String thisScale = scale == MajorScale ? "Maj" : "Min";
				juce::String otherScale = scale == MajorScale ? "Min" : "Maj";
				auto incr = scale == MajorScale ? 3 : 9;
				rootNote += incr;
				return "Rel. " + thisScale + " to Par. " + otherScale  + ": " + rootNote.GetNoteDescr() + " " + thisScale;
			}
			}
			return "Scale";
		}

		//virtual Component * 	refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate)
	};
	
	class ChordTable :
		public ComponentBaseT<juce::TableListBox>,
		public ModelListener
	{
	public:
		ChordTable()
		{}
		
		~ChordTable () 
		{
			GetController().RemoveListener( this );
		}
		
		juce::Result onInit() override
		{
			GetController().AddListener( this );
			setModel( &m_model );
			initColumns();
			return juce::Result::ok();
		}
		
		void initColumns();

		void onChanged( const ModelNotification& note ) override
		{
			if ( note.change == EModelChange::RootChanged ||
				note.change == EModelChange::ScaleChanged ||
				note.change == EModelChange::SharpsFlats )
			{
				initColumns();
			}
		}

	private:
		
		ChordTableModel m_model;
		
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( ChordTable )
	};
}
