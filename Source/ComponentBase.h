/*
  ==============================================================================

    ComponentBase.h
    Created: 2 May 2021 6:57:34pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

#include "ViewHeader.h"

namespace view
{
	template<class TComponent>
	class ComponentBaseT :
		public TComponent // Parameterized Base Class Idiom
	{
		static_assert( std::is_base_of<juce::Component, TComponent>::value, "TComponent must derive from juce::Component." );

	public:
		virtual ~ComponentBaseT() = default;

	protected:
		template<typename... Args> // Variadic Template
		ComponentBaseT( Args&&... args ) : // Rvalue Reference
			TComponent( std::forward<Args>( args )... ) // Perfect Forwarding
		{
		}

		// Derived components can override virtual juce::Result onInit() to perform initialization outside of the constructor.
		// Useful when you need to use XCDObject methods during initialization. All view components,
		// including the main view itself, will have been fully created/constructed by the time
		// onInit() gets called, so its safe to use any XCDObject method in there.

		// onInit is called any time parent hierarchy is changed. So it will be triggered when the view is created.
	};
	
	//==================================================================================================
	// ComponentBase Class
	//
	// Inherit from this class, instead of juce::Component, to give your UI component convenient access
	// to the controller, transport and other relevant objects.
	//==================================================================================================
	class ComponentBase : public ComponentBaseT<juce::Component>
	{
	public:
		virtual ~ComponentBase() = default;

	protected:
		ComponentBase() = default;
	};
		
};
