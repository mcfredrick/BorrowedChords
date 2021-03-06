#include "MainComponent.h"
#include "ChordTable.h"
#include "SelectorComponents.h"

namespace view
{
	//==============================================================================
	MainComponent::MainComponent()
	{
		// Make sure you set the size of the component after
		// you add any child components.
		setSize( 920, 600 );

		// Some platforms require permissions to open input channels so request that here
		if ( juce::RuntimePermissions::isRequired( juce::RuntimePermissions::recordAudio )
			&& !juce::RuntimePermissions::isGranted( juce::RuntimePermissions::recordAudio ) )
		{
			juce::RuntimePermissions::request( juce::RuntimePermissions::recordAudio,
				[&] ( bool granted ) { setAudioChannels( granted ? 2 : 0, 2 ); } );
		}
		else
		{
			// Specify the number of input and output channels that we want to open
			setAudioChannels( 2, 2 );
		}
	}

	MainComponent::~MainComponent()
	{
		// This shuts down the audio device and clears the audio source.
		shutdownAudio();
	}

	juce::Result MainComponent::onInit()
	{
		m_chordTable = std::make_unique<ChordTable>();
		m_selector = std::make_unique<SelectorComponents>();
		resized();
		addAndMakeVisible( *m_chordTable );
		addAndMakeVisible( *m_selector );
		return juce::Result::ok();
	}

	//==============================================================================
	void MainComponent::prepareToPlay( int /*samplesPerBlockExpected*/, double /*sampleRate*/ )
	{
		// This function will be called when the audio device is started, or when
		// its settings (i.e. sample rate, block size, etc) are changed.

		// You can use this function to initialise any resources you might need,
		// but be careful - it will be called on the audio thread, not the GUI thread.

		// For more details, see the help for AudioProcessor::prepareToPlay()
	}

	void MainComponent::getNextAudioBlock( const juce::AudioSourceChannelInfo& bufferToFill )
	{
		// Your audio-processing code goes here!

		// For more details, see the help for AudioProcessor::getNextAudioBlock()

		// Right now we are not producing any data, in which case we need to clear the buffer
		// (to prevent the output of random noise)
		bufferToFill.clearActiveBufferRegion();
	}

	void MainComponent::releaseResources()
	{
		// This will be called when the audio device stops, or when it is being
		// restarted due to a setting change.

		// For more details, see the help for AudioProcessor::releaseResources()
	}

	//==============================================================================
	void MainComponent::paint( juce::Graphics& g )
	{
		// (Our component is opaque, so we must completely fill the background with a solid colour)
		g.fillAll( getLookAndFeel().findColour( juce::ResizableWindow::backgroundColourId ) );

		// You can add your drawing code here!
	}

	void MainComponent::resized()
	{
		auto lb = getLocalBounds();
		if ( m_selector != nullptr )
		{
			m_selector->setBounds( lb.removeFromTop( 100 ).reduced( lb.getWidth() / 4, 25 ) );
		}

		if ( m_chordTable != nullptr )
		{
			auto h = ( 4 * m_chordTable->getRowHeight() ) + m_chordTable->getHeaderHeight() + m_chordTable->getHorizontalScrollBar().getHeight();
			m_chordTable->setSize( getWidth(), h );

			
			m_chordTable->setBounds( lb.removeFromTop( h ).reduced( 20, 0 ) );
		}
	}

};
