/*
  ==============================================================================

    Main.h
    Created: 3 May 2021 10:11:30pm
    Author:  Matt

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Controller; // forward declaration - storing a pointer
class MainComponent;
//==============================================================================
class BorrowedChordsApplication  : public juce::JUCEApplication
{
public:
	//==============================================================================
	BorrowedChordsApplication();

	const juce::String getApplicationName() override;
	const juce::String getApplicationVersion() override;
	bool moreThanOneInstanceAllowed() override;

	static IController& getController();
	
	//==============================================================================
	void initialise (const juce::String& commandLine) override;

	void shutdown() override;

	//==============================================================================
	void systemRequestedQuit() override;

	void anotherInstanceStarted (const juce::String& commandLine) override;

	//==============================================================================
	/*
		This class implements the desktop window that contains an instance of
		our MainComponent class.
	*/
	class MainWindow    : public juce::DocumentWindow
	{
	public:
		MainWindow (juce::String name);

		void closeButtonPressed() override;

		/* Note: Be careful if you override any DocumentWindow methods - the base
		   class uses a lot of them, so by overriding you might break its functionality.
		   It's best to do all your work in your content component instead, but if
		   you really have to override any DocumentWindow methods, make sure your
		   subclass also calls the superclass's method.
		*/

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
	};

private:
	std::unique_ptr<MainWindow> mainWindow;
	std::unique_ptr<Controller> controller;
};


