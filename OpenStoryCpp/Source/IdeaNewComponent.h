/*
  ==============================================================================

    IdeaNewComponent.h
    Created: 6 Jun 2014 9:00:26pm

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
    TextPropertyComponent *m_pHeadLine;
    TextPropertyComponent *m_pHeadDescription;
    
    float m_fCurrentFontHeight;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IdeaNewComponent)
};


#endif  // IDEANEWCOMPONENT_H_INCLUDED
