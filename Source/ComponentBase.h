/*
  ==============================================================================

    ComponentBase.h
    Created: 2 May 2021 6:57:34pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace view
{
	template<class TComponent>
	class ComponentBaseT :
		public TComponent // Parameterized Base Class Idiom
	{
		static_assert( std::is_base_of<juce::Component, TComponent>::value, "TComponent must derive from juce::Component." );

	public:
		virtual ~ComponentBaseT() = default;

		virtual juce::Result onInit() { return juce::Result::ok(); }

	protected:
		template<typename... Args> // Variadic Template
		ComponentBaseT( Args&&... args ) : // Rvalue Reference
			TComponent( std::forward<Args>( args )... ) // Perfect Forwarding
		{
		}

		bool isInitialized() const { return m_isInitialized; }

		virtual juce::Result initComponentInternal()
		{
			return onInit();
		}

		// Remember to call this base class imlementation if you want
		// to use the initialization procedure!
		void parentHierarchyChanged() override { tryInit(); }

	private:
		void tryInit()
		{
			if ( isInitialized() )
				return; // Already initialized. Move along.

			// If there's a component peer, we know we're actualy on
			// the desktop. Otherwise, no need to initialize yet.
			if ( TComponent::getPeer() == nullptr )
				return;

			// Initialize the component.
			const auto result = initComponentInternal();
			if ( result.failed() )
				throw new std::runtime_error( result.getErrorMessage().toStdString() );

			m_isInitialized = true;
		}

	private:
		bool m_isInitialized = false;
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
