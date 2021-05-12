/*
  ==============================================================================

	SelectorComponents.h
	Created: 7 May 2021 10:12:12pm
	Author:  Matt

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ViewHeader.h"
#include "Scale.h"
#include "Note.h"

//==============================================================================
/*
*/
namespace view
{
	class NoteSelector :
		public ComponentBaseT<juce::ComboBox>,
		public ModelListener
	{
	public :
		NoteSelector() {}
		~NoteSelector()
		{
			GetController().RemoveListener( this );
		}

		juce::Result onInit() override
		{
			GetController().AddListener( this );

			for ( auto i = 0; i < 12; ++i )
			{
				addItem( Note::GetNoteDescr( i ), i + 1 );
			}

			setSelectedId( GetController().GetRootNote().pitch + 1, juce::dontSendNotification );

			onChange = [this] () {updateModel(); };

			return juce::Result::ok();
		}

		void updateModel()
		{
			GetController().SetRootNote( Note( getSelectedId() - 1 ) );
		}

		void onChanged( const ModelNotification& note ) override
		{
			if ( note.change == EModelChange::RootChanged )
			{
				setSelectedId( GetController().GetRootNote().pitch + 1, juce::dontSendNotification );
			}
		}

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( NoteSelector );
	};
	
	class ScaleSelector :
		public ComponentBaseT<juce::ComboBox>,
		public ModelListener
	{
	public:
		ScaleSelector() {}
		~ScaleSelector()
		{
			GetController().RemoveListener( this );
		}

		juce::Result onInit() override
		{
			GetController().AddListener( this );

			int i = 1;
			auto currScale = GetController().GetHomeScale();
			for ( auto scale : AllScales )
			{
				addItem( scale.name, i );
				scaleIdMap.insert_or_assign( scale, i );
				if ( scale == currScale )
					setSelectedId( i, juce::dontSendNotification );
				++i;
			}

			onChange = [this] () {updateModel(); };

			return juce::Result::ok();
		}

		void updateModel()
		{
			bool success = false;
			for ( auto scale : scaleIdMap )
			{
				if ( scale.second == getSelectedId() )
				{
					success = true;
					GetController().SetHomeScale( scale.first );
				}
			}

			jassert( success );
		}

		void onChanged( const ModelNotification& note ) override
		{
			if ( note.change == EModelChange::ScaleChanged )
			{
				auto match = scaleIdMap.find( GetController().GetHomeScale() );
								
				if ( match != scaleIdMap.end() )
					setSelectedId( match->second, juce::dontSendNotification );
				else
				{
					jassertfalse;
				}
			}
		}

		std::map<Scale, int> scaleIdMap;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( ScaleSelector );
	};
	
	class SelectorComponents :
		public ComponentBaseT<juce::Component>
	{
	public:
		SelectorComponents();
		~SelectorComponents() override;

		juce::Result onInit() override;

		void paint( juce::Graphics& ) override;
		void resized() override;

	private:
		NoteSelector	m_cmbNote;
		ScaleSelector	m_cmbScale;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( SelectorComponents )
	};
};