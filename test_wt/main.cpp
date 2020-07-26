#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

// modified from "Hello World" application from
//   https://www.webtoolkit.eu/wt/doc/tutorial/wt.html

class HelloApplication : public Wt::WApplication
{
public:
    HelloApplication(const Wt::WEnvironment& env);

private:
    void greet();
  
    Wt::WLineEdit *nameEdit_;
    Wt::WLineEdit *titleEdit_;
    Wt::WText *greeting_;
};

HelloApplication::HelloApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
{
    setTitle("Hello world");

    root()->addWidget(std::make_unique<Wt::WText>("Your title, please? "));
    titleEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
    root()->addWidget(std::make_unique<Wt::WBreak>());
    root()->addWidget(std::make_unique<Wt::WText>("Your name, please? "));
    nameEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
    
    Wt::WPushButton *button = root()->addWidget(std::make_unique<Wt::WPushButton>("Greet me."));
    root()->addWidget(std::make_unique<Wt::WBreak>());
    greeting_ = root()->addWidget(std::make_unique<Wt::WText>());
    //auto greet = [this]{
    //  greeting_->setText("Hello there, " + nameEdit_->text());
    //};
    button->clicked().connect(this, &HelloApplication:: greet);
}

void HelloApplication::greet()
{
  greeting_->setText("Hello there, " + titleEdit_->text() + " " + nameEdit_->text());
}
  
  
  

int main(int argc, char **argv)
{
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
      return std::make_unique<HelloApplication>(env);
    });
}
