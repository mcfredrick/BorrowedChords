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
struct BCNotification
{
	static_assert( std::is_enum<TChange>::value, "Expecting TChange to be an enum class" );
	
	TChange change;
	std::any data;
};

template<class TNotification>
class BCListener
{
public:
	virtual ~BCListener() = 0;
	
	virtual void onChanged( const TNotification& note ) = 0;
};
 /*
ListenerList<MyListenerType> listeners;
listeners.add (someCallbackObjects...);
 
// This will invoke myCallbackMethod (1234, true) on each of the objects
// in the list...
listeners.call ([] (MyListenerType& l) { l.myCallbackMethod (1234, true); });
*/
template<class TListenerClass, class TNotification, class TChange>
class BCBroadcaster
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
	
	void NotifyListeners( const TChange& note, std::any data = std::any() )
	{
		juce::MessageManager::callAsync( [this, note, data] ()
		{
			listenerList.call ([note, data] (TListenerClass& l) { l.onChanged ({ note, data }); });
		}
		);
	};
	
	void NotifyListenersSync( TChange note, std::any data = std::any() )
	{
		listenerList.call ([note, data] (TListenerClass& l) { l.onChanged ({ note, data }); });
	}
	
	juce::ListenerList<TListenerClass> listenerList;
};

enum class EModelChange
{
	RootChanged,
	ScaleChanged
};

typedef BCNotification<EModelChange> ModelNotification;

typedef BCListener<ModelNotification> ModelListener;

typedef BCBroadcaster<ModelListener, ModelNotification, EModelChange> ModelBroadcaster;
