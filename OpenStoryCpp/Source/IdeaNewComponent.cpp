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

    m_fCurrentFontHeight = 14.0f;
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
    Font cFont = g.getCurrentFont();
    // TODO V Figure out how to set the font globally
    // Figure out how to calculate the font height at the right time.
    m_fCurrentFontHeight = cFont.getHeight();
}

void IdeaNewComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    //m_pHeadLine->setBounds (getLocalBounds().reduced (4));
    //m_pHeadDescription->setBounds (getLocalBounds().reduced (4));
    int nTextHeight = int( m_fCurrentFontHeight * 1.1 ) + 3;
    m_pHeadLine->setBounds(0,0, getWidth(), nTextHeight);
    int nHeightLeftEmpty = getHeight() - m_pHeadLine->getBottom();
    m_pHeadDescription->setBounds(0, m_pHeadLine->getBottom(), getWidth(), nHeightLeftEmpty);
}
