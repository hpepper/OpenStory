/*
  ==============================================================================

    StoryComponent.h
    Created: 6 Jun 2014 8:30:48pm
    Author:  Henrik Koch

  ==============================================================================
*/

#ifndef STORYCOMPONENT_H_INCLUDED
#define STORYCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class StoryComponent    : public Component
{
public:
    StoryComponent();
    ~StoryComponent();

    void paint (Graphics&);
    void resized();

private:
    TabbedComponent m_LocalTab;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StoryComponent)
};


#endif  // STORYCOMPONENT_H_INCLUDED
