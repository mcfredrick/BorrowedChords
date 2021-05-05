#pragma once

#include <JuceHeader.h>
#include "ViewHeader.h"

namespace view
{
	class ChordTable;
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
	class MainComponent  : public ComponentBaseT<juce::AudioAppComponent>
	{
	public:
		//==============================================================================
		MainComponent();
		~MainComponent() override;

		juce::Result onInit() override;
		
		//==============================================================================
		void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
		void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
		void releaseResources() override;

		//==============================================================================
		void paint (juce::Graphics& g) override;
		void resized() override;

	private:
		//==============================================================================
		// Your private member variables go here...

		std::unique_ptr<ChordTable> m_chordTable;
		
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
	};
}
