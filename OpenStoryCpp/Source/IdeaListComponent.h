/*
  ==============================================================================

    IdeaListComponent.h
    Created: 6 Jun 2014 8:59:30pm
    Author:  Henrik Koch

  ==============================================================================
*/

#ifndef IDEALISTCOMPONENT_H_INCLUDED
#define IDEALISTCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class IdeaListComponent    : public Component
{
public:
    IdeaListComponent();
    ~IdeaListComponent();

    void paint (Graphics&);
    void resized();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IdeaListComponent)
};


#endif  // IDEALISTCOMPONENT_H_INCLUDED
