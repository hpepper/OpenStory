#include "View.h"

#include <Wt/WContainerWidget>
#include <Wt/WText>
#include <Wt/WMenu>
#include <Wt/WVBoxLayout>
#include <Wt/WHBoxLayout>
#include <Wt/WNavigationBar>
#include <Wt/WStackedWidget>
#include <Wt/WPopupMenu>
#include <Wt/WLineEdit>
#include <Wt/WTabWidget>
#include <Wt/WTextArea>
#include <Wt/WGridLayout>
#include <Wt/WLength>
#include <Wt/WComboBox>
#include <Wt/WSignal>
#include <Wt/WText>


// https://www.webtoolkit.eu/wt/doc/reference/html/classWt_1_1WApplication.html#ae29a843f4d50159b17abfa9503c389db
// wApp->log("notice") << "User " << userName << " logged in successfully.";

// This is the top-level widget container of the application, and corresponds to entire browser window. The user interface of your application is represented by the content of this container.
// The root() widget is only defined when the application manages the entire window.

// The resource files in /usr/share/Wt/resources has to be available.

/**
  Constructor for View

  This will layout the GUI.
  It uses the gridlayout, because it can actually stretch the gui to fill the
    screen/browser window.
 */
View::View(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
{
  setTitle("Story teller");

  log("info") << "Test";

  // This is the container for the full screen.
  Wt::WContainerWidget *pScreenContainer = new Wt::WContainerWidget();
  pScreenContainer->resize(Wt::WLength::Auto, Wt::WLength::Auto);
  // Add the primary container to the root widget?
  root()->addWidget(pScreenContainer);

  // This creates the layout that will hold all the layouts that we will use.
  Wt::WVBoxLayout *pBaseLayout = new Wt::WVBoxLayout();
  pScreenContainer->setLayout(pBaseLayout);

  // this is the layout that holds the Drop down combos for Series etc.
  Wt::WContainerWidget *pDropDownLineLayout = new Wt::WContainerWidget();
  CreateTopSelectionLine(this, pDropDownLineLayout);
  pBaseLayout->addWidget(pDropDownLineLayout);

/* Move to each tab:
  Wt::WGridLayout *pScreenLayout = new Wt::WGridLayout();
  pScreenContainer->setLayout(pScreenLayout);
  */

  // This is the tab list.
  // Create the container for the North field
  Wt::WContainerWidget *pMainContainer = new Wt::WContainerWidget();
  CreateTopTab(this, pMainContainer);

  // Add the main container to the screen layout
  pBaseLayout->addWidget(pMainContainer);



  Wt::WText *item = new Wt::WText("Status text");
  item->setStyleClass("green-box");
  pBaseLayout->addWidget(item, 1,0);

  /*
       * Let row 1 and column 1 take the excess space.
       */
  //pScreenLayout->setRowStretch(0, 0);
  //pScreenLayout->setColumnStretch(0, 0);

} // end


Wt::WHBoxLayout *View::CreateTopSelectionLine(Wt::WApplication *app, Wt::WContainerWidget *container) {
  Wt::WHBoxLayout *hbox = new Wt::WHBoxLayout();
  container->setLayout(hbox);

    // Create the label
  Wt::WText *lblSeriesChoice = new Wt::WText("Series:");
  // set right align the label
  lblSeriesChoice->setTextAlignment(Wt::AlignRight);
  hbox->addWidget(lblSeriesChoice);

  // Create the dropdown
  Wt::WComboBox *cbSeries = new Wt::WComboBox();
  cbSeries->addItem("");
  cbSeries->addItem("New");
  cbSeries->addItem("Krakken awoke");
  cbSeries->addItem("Appocalypse survival");
  cbSeries->setCurrentIndex(0); // Empty string
  hbox->addWidget(cbSeries);


  // Create the connection
  //cbSeries->activated().connect(this, &View::DropDownSelectionChange);
  /* Signals connect to Slots.
  * You may specify up to 6 arguments which may be of arbitrary types that are Copyable, that may be passed through the signal to connected slots.
  *   https://www.webtoolkit.eu/wt/doc/reference/html/group__signalslot.html
  * I think the 
  *   first parm - is a pointer to the target class.
  *   second parm - is the name of the method?
  * 
  * See: Wt::Signal.
  */

}


/**
 * Create the Tab for the top part. It also create the container for each tab.
 */
Wt::WHBoxLayout *View::CreateTopTab(Wt::WApplication *app, Wt::WContainerWidget *container) {
  //TODO N create destructors that delete all the 'new()' operations.
  Wt::WHBoxLayout *hbox = new Wt::WHBoxLayout();
  container->setLayout(hbox);

  // Things are getting added to the hbox.
  Wt::WTabWidget *tabW = new Wt::WTabWidget(container);
  tabW->addTab(new Wt::WTextArea("This is the contents of the first tab."),
             "Ideas", Wt::WTabWidget::PreLoading);
  tabW->addTab(new Wt::WTextArea("The contents of the tabs are pre-loaded in"
                               " the browser to ensure swift switching."),
             "Series", Wt::WTabWidget::PreLoading);
  tabW->addTab(new Wt::WTextArea("You could change any other style attribute of the"
                               " tab widget by modifying the style class."
                               " The style class 'trhead' is applied to this tab."),
             "Season", Wt::WTabWidget::PreLoading);
  tabW->addTab(new Wt::WTextArea("The contents of the tabs are pre-loaded in"
                               " the browser to ensure swift switching."),
             "Episode", Wt::WTabWidget::PreLoading);
  tabW->addTab(new Wt::WTextArea("The contents of the tabs are pre-loaded in"
                                       " the browser to ensure swift switching."),
                     "Encounter", Wt::WTabWidget::PreLoading);
  tabW->setStyleClass("tabwidget");
  hbox->addWidget(tabW);

  app->log("info") << "DDD CreateTopTab() done";
  return(hbox);
} // end CreateTopTab
