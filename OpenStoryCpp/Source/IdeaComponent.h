/*
  ==============================================================================

    IdeaComponent.h
    Created: 5 Jun 2014 8:42:19pm

  ==============================================================================
*/

#ifndef IDEACOMPONENT_H_INCLUDED
#define IDEACOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class IdeaComponent    : public Component
{
public:
    IdeaComponent();
    ~IdeaComponent();

    void resized();

private:
    TabbedComponent m_LocalTab;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IdeaComponent)
};


#endif  // IDEACOMPONENT_H_INCLUDED
