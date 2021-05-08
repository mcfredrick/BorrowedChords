/*
  ==============================================================================

    SelectorComponents.h
    Created: 7 May 2021 10:12:12pm
    Author:  Matt

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SelectorComponents  : public juce::Component
{
public:
    SelectorComponents();
    ~SelectorComponents() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SelectorComponents)
};
