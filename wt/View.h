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
  void CreateSeriesTab();
  Wt::WHBoxLayout *CreateTopTab(Wt::WApplication *app, Wt::WContainerWidget *container);
  Wt::WHBoxLayout *CreateTopSelectionLine(Wt::WApplication *app, Wt::WContainerWidget *container);
  void SeriesTabSeriesChanged(int);
  void SeasonComboBoxSeriesChanged(int);

  Wt::WContainerWidget *m_pSeriesContainer;
  Wt::WComboBox *m_cbSeries;
  Wt::WComboBox *m_cbSeason;
};

#endif
