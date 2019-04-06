#ifndef VIEW_H
#define VIEW_H

#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WHBoxLayout>
#include <Wt/WApplication>

class View : public Wt::WApplication {
public:
  View(const Wt::WEnvironment& env);

private:
  Wt::WHBoxLayout *CreateTopTab(Wt::WApplication *app, Wt::WContainerWidget *container);
  Wt::WHBoxLayout *CreateTopSelectionLine(Wt::WApplication *app, Wt::WContainerWidget *container);
};

#endif
