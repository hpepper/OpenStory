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
    
    StringArray choices;
    Array<var> choiceVars;
    
    choices.add ("Character");
    choiceVars.add (0);

    choices.add ("Scene");
    choiceVars.add (1);

    choices.add ("Plot");
    choiceVars.add (2);

    choices.add ("Saga");
    choiceVars.add (3);

    choices.add ("Subject");
    choiceVars.add (4);

    choices.add ("Dialog");
    choiceVars.add (5);

    choices.add ("Sense");
    choiceVars.add (6);

    m_pHeadLine = new TextPropertyComponent (Value ("This is a single-line Text Property"), "Headline", 200, false);
    m_pIdeaType = new ChoicePropertyComponent (Value (Random::getSystemRandom().nextInt (7)), "Idea type", choices, choiceVars);
    m_pHeadDescription = new TextPropertyComponent (Value ("Multiline entrys."), "Description", 2000, true);
    
    m_pButtonCommit = new TextButton ("Commit");

    addAndMakeVisible( m_pHeadLine );
    addAndMakeVisible( m_pIdeaType );
    addAndMakeVisible( m_pHeadDescription );
    
    addAndMakeVisible( m_pButtonCommit );

    m_fCurrentFontHeight = 14.0f;
}

IdeaNewComponent::~IdeaNewComponent()
{
    delete m_pHeadLine;
    delete m_pHeadDescription;
    delete m_pIdeaType;
    delete m_pButtonCommit;
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
    m_pIdeaType->setBounds(0, m_pHeadLine->getBottom(), getWidth(), nTextHeight);
    int nHeightLeftEmpty = getHeight() - m_pIdeaType->getBottom();
    m_pHeadDescription->setBounds(0, m_pIdeaType->getBottom(), getWidth(), nHeightLeftEmpty-nTextHeight);
    
    m_pButtonCommit->setBounds(0,m_pHeadDescription->getBottom(), getWidth(), nTextHeight);
}
