/*
  ==============================================================================

    Broadcaster.h
    Created: 2 May 2021 9:29:15pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Includes.h"

template <typename TChange>
struct Notification
{
	static_assert( std::is_enum<TChange>::value, "Expecting TChange to be an enum class" );
	
	TChange change;
	std::any data;
};

template<class TNotification>
class Listener
{
public:
	virtual void onChanged( const TNotification& note ) = 0;
};
 /*
ListenerList<MyListenerType> listeners;
listeners.add (someCallbackObjects...);
 
// This will invoke myCallbackMethod (1234, true) on each of the objects
// in the list...
listeners.call ([] (MyListenerType& l) { l.myCallbackMethod (1234, true); });
*/
template<class TListenerClass, class TNotification>
class Broadcaster
{
public:

	void AddListener( TListenerClass* listener )
	{
		listenerList.addListener( listener );
	}
	
	void RemoveListener( TListenerClass* listener )
	{
		listenerList.removeListener( listener );
	}
	
	void NotifyListeners( const TNotification& note )
	{
		juce::MessageManager::callAsync( [this] (TNotification& note)
		{
			listenerList.call(void (TListenerClass::onChanged)(note));
		}
		);
	}
	
	juce::ListenerList<TListenerClass> listenerList;
};

enum class EModelChange
{
	RootChanged,
	ScaleChanged
};

typedef Notification<EModelChange> ModelNotification;

typedef Listener<ModelNotification> ModelListener;

typedef Broadcaster<ModelListener, ModelNotification> ModelBroadcaster;
