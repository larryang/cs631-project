/*
 * classlistGenerate.h
 *
 *  Created on: Aug 1, 2020
 *      Author: larryang
 */

#ifndef CLASSLISTGENERATE_H_
#define CLASSLISTGENERATE_H_

#include <memory>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WTable.h>
#include "student-app.h"
#include "connectMySql.h"

class StudentApplication;

class ClassListGenerateWidget : public Wt::WContainerWidget
{
public:
	ClassListGenerateWidget(StudentApplication* parent);

private:
	StudentApplication *m_parent;

	sql::Driver *driver_ptr;
	std::unique_ptr<sql::Connection> con_ptr;
	std::string handle_SQLException(sql::SQLException &e);

	Wt::WPushButton *generateClassListButton;
	Wt::WText *queryResponse;
	Wt::WTable *table;

	// SLOTS
	void generateClassList(); // probably could just do all of this in the constructor
};



#endif /* CLASSLISTGENERATE_H_ */
