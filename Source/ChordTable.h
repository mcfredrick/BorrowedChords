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

		void paintCell( juce::Graphics& g, int rowNumber, int columnId, int /*width*/, int /*height*/, bool /*rowIsSelected*/ ) override
		{
			g.setColour( juce::Colours::white );
			g.drawRect( g.getClipBounds() );
			auto row = GetCachedRow( rowNumber );
			if ( row.has_value() )
			{
				juce::String text = " - ";
				if ( columnId == 1 )
					text = row.value().relationship;
				else
				{
					auto root = row.value().root;
					for ( int i = 0; i < ( columnId - 2 ); ++i )
						root += row.value().scale.intervals[i];

					text = root.GetNoteDescr();
				}

				g.drawFittedText( text, g.getClipBounds().reduced( 2 ), juce::Justification::centredLeft, 1 );
			}
		}

		struct Row
		{
			juce::String relationship;
			Note root;
			Scale scale;
		};

		Row GetRelatedScaleForRow( int rowNum )
		{
			switch ( rowNum )
			{
			case 0:
			{
				auto homeScale = GetController().GetHomeScale();
				auto rootNote = GetController().GetRootNote();
				return { "Home: " + rootNote.GetNoteDescr() + " " + homeScale.name, rootNote, homeScale };
			}
			case 1:
			{
				auto scale = GetController().GetHomeScale();
				auto rootNote = GetController().GetRootNote();
				juce::String relScale = scale == MajorScale ? "Min" : "Maj";
				auto incr = scale == MajorScale ? 9 : 3;
				rootNote += incr;
				return { "Rel. " + relScale + ": " + rootNote.GetNoteDescr() + " " + relScale, rootNote, scale == MajorScale ? NaturalMinorScale : MajorScale };
			}
			case 2:
			{
				auto scale = GetController().GetHomeScale();
				auto rootNote = GetController().GetRootNote();
				juce::String parScale = scale == MajorScale ? "Min" : "Maj";
				return { "Par. " + parScale + ": " + rootNote.GetNoteDescr() + " " + parScale, rootNote, scale == MajorScale ? NaturalMinorScale : MajorScale };
			}
			case 3:
			{
				auto scale = GetController().GetHomeScale();
				auto rootNote = GetController().GetRootNote();
				juce::String thisScale = scale == MajorScale ? "Maj" : "Min";
				juce::String otherScale = scale == MajorScale ? "Min" : "Maj";
				auto incr = scale == MajorScale ? 3 : 9;
				rootNote += incr;
				return { "Rel. " + thisScale + " to Par. " + otherScale + ": " + rootNote.GetNoteDescr() + " " + thisScale, rootNote, scale == MajorScale ? MajorScale : NaturalMinorScale };
			}
			}
			return { "Scale", Note( 0 ), MajorScale };
		}

		void UpdateRowCache()
		{
			rowCache.clear();

			for ( int i = 0; i < 4; ++i )
			{
				rowCache.insert( { i, GetRelatedScaleForRow( i ) } );
			}
		}

		std::optional<Row> GetCachedRow( int rowNum )
		{
			auto row = rowCache.find( rowNum );
			jassert( row != rowCache.end() );
			if ( row != rowCache.end() )
				return row->second;

			return std::nullopt;
		}

		std::map<int, Row> rowCache;
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
