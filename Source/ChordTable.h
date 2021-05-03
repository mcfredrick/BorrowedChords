/*
  ==============================================================================

    ChordTable.h
    Created: 2 May 2021 6:49:01pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

#include "ViewHeader.h"

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

		void paintRowBackground (juce::Graphics & g, int rowNumber, int width, int height, bool rowIsSelected) override
		{
			g.setColour( juce::Colours::white );
			g.drawRect( g.getClipBounds() );
		}

		void paintCell (juce::Graphics & g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override
		{
			g.setColour( juce::Colours::white );
			g.drawRect( g.getClipBounds() );
			g.drawFittedText( "Chord here", g.getClipBounds(), juce::Justification::centred, 1 );
		}
		
		//virtual Component * 	refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate)
	};
	
	class ChordTable :
	public ComponentBaseT<juce::TableListBox>
	{
	public:
		ChordTable()
		{}
		
		~ChordTable () {}
		
		juce::Result onInit() override
		{
			setModel( &m_model );
			initColumns();
			return juce::Result::ok();
		}
		
		void initColumns()
		{
			auto& header = getHeader();
			
			// Column IDs must start at 1.
			for ( int i = 1; i < 8; ++i )
			{
				header.addColumn ( juce::String( "Chord " + juce::String(i) ), i, getWidth()/7, /*minimumWidth=*/30, /*maximumWidth=*/-1/*, propertyFlags=defaultFlags, insertIndex=-1*/);
			}
		}
		
	private:
		
		ChordTableModel m_model;
		
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( ChordTable )
	};
}
