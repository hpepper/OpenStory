/*
  ==============================================================================

    IdeaNewComponent.cpp
    Created: 6 Jun 2014 9:00:26p

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "IdeaNewComponent.h"

//==============================================================================
IdeaNewComponent::IdeaNewComponent()
{
    m_pHeadLine = new TextPropertyComponent (Value ("This is a single-line Text Property"), "Headline", 200, false);
    m_pHeadDescription = new TextPropertyComponent (Value ("Multiline entrys."), "Description", 2000, true);
    
    addAndMakeVisible( m_pHeadLine );
    addAndMakeVisible( m_pHeadDescription );

}

IdeaNewComponent::~IdeaNewComponent()
{
    delete m_pHeadLine;
    delete m_pHeadDescription;
}

void IdeaNewComponent::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (Colours::white);   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::lightblue);
    g.setFont (14.0f);
}

void IdeaNewComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    //m_pHeadLine->setBounds (getLocalBounds().reduced (4));
    //m_pHeadDescription->setBounds (getLocalBounds().reduced (4));
    m_pHeadLine->setBounds(0,0, getWidth(), 20);
    m_pHeadDescription->setBounds(0,20, getWidth(), 20);
}
