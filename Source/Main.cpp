/*
 ==============================================================================
 
 This file contains the basic startup code for a JUCE application.
 
 ==============================================================================
 */

#include <JuceHeader.h>
#include "MainComponent.h"
#include "Includes.h"
#include "IController.h"
#include "Controller.h"

	//==============================================================================
	BorrowedChordsApplication::BorrowedChordsApplication()
	{
	}
	
	const juce::String BorrowedChordsApplication::getApplicationName() { return ProjectInfo::projectName; }
	const juce::String BorrowedChordsApplication::getApplicationVersion() { return ProjectInfo::versionString; }
	bool BorrowedChordsApplication::moreThanOneInstanceAllowed() { return true; }
	
	IController& BorrowedChordsApplication::getController()
	{
		return Controller::GetInstance();
	}
	
	//==============================================================================
	void BorrowedChordsApplication::initialise (const juce::String& /*commandLine*/)
	{
		// This method is where you should put your application's initialisation code..
		controller = std::make_unique<Controller>();
		mainWindow = std::make_unique<MainWindow>( getApplicationName() );
	}
	
	void BorrowedChordsApplication::shutdown()
	{
		// Add your application's shutdown code here..
		
		mainWindow = nullptr; // (deletes our window)
	}
	
	//==============================================================================
	void BorrowedChordsApplication::systemRequestedQuit()
	{
		// This is called when the app is being asked to quit: you can ignore this
		// request and let the app carry on running, or call quit() to allow the app to close.
		quit();
	}
	
	void BorrowedChordsApplication::anotherInstanceStarted (const juce::String& /*commandLine*/)
	{
		// When another instance of the app is launched while this one is running,
		// this method is invoked, and the commandLine parameter tells you what
		// the other instance's command-line arguments were.
	}
	
	//==============================================================================
	/*
	 This class implements the desktop window that contains an instance of
	 our MainComponent class.
	 */

	BorrowedChordsApplication::MainWindow::MainWindow (juce::String name)	:
		DocumentWindow (name,
					juce::Desktop::getInstance().getDefaultLookAndFeel()
					.findColour (juce::ResizableWindow::backgroundColourId),
					DocumentWindow::allButtons)
	{
		setUsingNativeTitleBar (true);
		setContentOwned (new view::MainComponent(), true);
			
#if JUCE_IOS || JUCE_ANDROID
		setFullScreen (true);
#else
		setResizable (true, true);
		centreWithSize (getWidth(), getHeight());
#endif
			
		setVisible (true);
	}
		
	void BorrowedChordsApplication::MainWindow::closeButtonPressed()
	{
			// This is called when the user tries to close this window. Here, we'll just
			// ask the app to quit when this happens, but you can change this to do
			// whatever you need.
		JUCEApplication::getInstance()->systemRequestedQuit();
	}

	//==============================================================================
	// This macro generates the main() routine that launches the app.
	START_JUCE_APPLICATION (BorrowedChordsApplication)
