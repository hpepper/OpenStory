/*
  ==============================================================================

    IdeaNewComponent.h
    Created: 6 Jun 2014 9:00:26pm
    Author:  Henrik Koch

  ==============================================================================
*/

#ifndef IDEANEWCOMPONENT_H_INCLUDED
#define IDEANEWCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class IdeaNewComponent    : public Component
{
public:
    IdeaNewComponent();
    ~IdeaNewComponent();

    void paint (Graphics&);
    void resized();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IdeaNewComponent)
};


#endif  // IDEANEWCOMPONENT_H_INCLUDED
