#pragma once

//////////////////////////////
//			MAYA			//
//////////////////////////////
#include <maya/MGlobal.h>
#include <maya/MSelectionList.h>
#include <maya/MItSelectionList.h>

#include <maya/MObject.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MFnIkJoint.h>

//////////////////////////////
//			 Qt 			//
//////////////////////////////
#include <QtWidgets/qapplication.h>
#include <QtCore/qdebug.h>
#include <QtCore/qobject.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>
#include <QtCore/qpointer.h>
#include <QtCore/qmetaobject.h>

class UIWindowController : public QWidget {
public:
	UIWindowController();
	static void cleanUp() noexcept;

private:
	static QPointer<QListWidget> Target_List;
	static QPointer<QListWidget> Source_List;
	static QPointer<QPushButton> Transfer_Button;

	static QPointer<QPushButton> Target_Up;
	static QPointer<QPushButton> Target_Delete;
	static QPointer<QPushButton> Target_Down;
	static QPointer<QPushButton> Source_Up;
	static QPointer<QPushButton> Source_Delete;
	static QPointer<QPushButton> Source_Down;
	
	static QPointer<QPushButton>	Target_Select_Button;
	static QPointer<QLabel>			Target_Root_Label;
	static QPointer<QLabel>			Target_Joints;
	static QPointer<QLineEdit>		Target_Input;
	static QPointer<QPushButton>	Source_Select_Button;
	static QPointer<QLabel>			Source_Root_Label;
	static QPointer<QLabel>			Source_Joints;
	static QPointer<QLineEdit>		Source_Input;

	static void retranslateUi(QWidget* Transfer_Window);

	public slots:
	static void selectTarget();




}; // Generated with uic.exe

QPointer<QListWidget>	UIWindowController::Target_List;
QPointer<QListWidget>	UIWindowController::Source_List;
QPointer<QPushButton>	UIWindowController::Transfer_Button;
QPointer<QPushButton>	UIWindowController::Target_Up;
QPointer<QPushButton>	UIWindowController::Target_Delete;
QPointer<QPushButton>	UIWindowController::Target_Down;
QPointer<QPushButton>	UIWindowController::Source_Up;
QPointer<QPushButton>	UIWindowController::Source_Delete;
QPointer<QPushButton>	UIWindowController::Source_Down;
QPointer<QPushButton>	UIWindowController::Target_Select_Button;
QPointer<QLabel>		UIWindowController::Target_Root_Label;
QPointer<QLabel>		UIWindowController::Target_Joints;
QPointer<QLineEdit>		UIWindowController::Target_Input;
QPointer<QPushButton>	UIWindowController::Source_Select_Button;
QPointer<QLabel>		UIWindowController::Source_Root_Label;
QPointer<QLabel>		UIWindowController::Source_Joints;
QPointer<QLineEdit>		UIWindowController::Source_Input;

UIWindowController::UIWindowController(){
	if (this->objectName().isEmpty())
		this->setObjectName(QStringLiteral("Transfer_Window"));
	this->resize(800, 600);
	
	QFont font {};
	font.setPointSize(8);
	font.setBold(false);
	font.setItalic(false);
	font.setWeight(50);
	font.setUnderline(false);
	font.setStrikeOut(false);
	font.setKerning(true);

	//////////////////////////////
	//			 Lists			//
	//////////////////////////////
	Source_List = new QListWidget(this);
	Source_List->setObjectName(QStringLiteral("Source_List"));
	Source_List->setGeometry(QRect(130, 90, 261, 451));
	
	Target_List = new QListWidget(this);
	Target_List->setObjectName(QStringLiteral("Target_List"));
	Target_List->setGeometry(QRect(410, 90, 261, 451));
	
	//////////////////////////////
	//			Inputs			//
	//////////////////////////////
	Target_Root_Label = new QLabel(this);
	Target_Root_Label->setObjectName(QStringLiteral("Target_Root_Label"));
	Target_Root_Label->setGeometry(QRect(130, 60, 46, 13));
	Target_Root_Label->setFont(font);
	
	Target_Joints = new QLabel(this);
	Target_Joints->setObjectName(QStringLiteral("Target_Joints"));
	Target_Joints->setGeometry(QRect(450, 40, 91, 21));
	Target_Joints->setFont(font);
	
	Target_Input = new QLineEdit(this);
	Target_Input->setObjectName(QStringLiteral("Target_Input"));
	Target_Input->setGeometry(QRect(450, 60, 221, 21));
	
	Source_Root_Label = new QLabel(this);
	Source_Root_Label->setObjectName(QStringLiteral("Source_Root_Label"));
	Source_Root_Label->setGeometry(QRect(410, 60, 46, 13));
	Source_Root_Label->setFont(font);
	
	Source_Joints = new QLabel(this);
	Source_Joints->setObjectName(QStringLiteral("Source_Joints"));
	Source_Joints->setGeometry(QRect(170, 40, 91, 21));
	Source_Joints->setFont(font);
	
	Source_Input = new QLineEdit(this);
	Source_Input->setObjectName(QStringLiteral("Source_Input"));
	Source_Input->setGeometry(QRect(170, 60, 221, 21));
	
	//////////////////////////////
	//		Target Scroll		//
	//////////////////////////////
	Target_Up = new QPushButton(this);
	Target_Up->setObjectName(QStringLiteral("Target_Up"));
	Target_Up->setGeometry(QRect(690, 260, 91, 21));
	Target_Up->setFont(font);
	Target_Up->setAutoFillBackground(true);

	Target_Delete = new QPushButton(this);
	Target_Delete->setObjectName(QStringLiteral("Target_Delete"));
	Target_Delete->setGeometry(QRect(690, 290, 91, 21));
	Target_Delete->setFont(font);
	Target_Delete->setAutoFillBackground(true);

	Target_Down = new QPushButton(this);
	Target_Down->setObjectName(QStringLiteral("Target_Down"));
	Target_Down->setGeometry(QRect(690, 320, 91, 21));
	Target_Down->setFont(font);
	Target_Down->setAutoFillBackground(true);
	
	//////////////////////////////
	//		 Source Sroll		//
	//////////////////////////////
	Source_Up = new QPushButton(this);
	Source_Up->setObjectName(QStringLiteral("Source_Up"));
	Source_Up->setEnabled(true);
	Source_Up->setGeometry(QRect(20, 260, 91, 21));
	Source_Up->setFont(font);
	Source_Up->setAutoFillBackground(true);
	
	Source_Delete = new QPushButton(this);
	Source_Delete->setObjectName(QStringLiteral("Source_Delete"));
	Source_Delete->setGeometry(QRect(20, 290, 91, 21));
	Source_Delete->setFont(font);
	Source_Delete->setAutoFillBackground(true);

	Source_Down = new QPushButton(this);
	Source_Down->setObjectName(QStringLiteral("Source_Down"));
	Source_Down->setGeometry(QRect(20, 320, 91, 21));
	Source_Down->setFont(font);
	Source_Down->setAutoFillBackground(true);
	
	//////////////////////////////
	//		 Key Buttons		//
	//////////////////////////////
	Transfer_Button = new QPushButton(this);
	Transfer_Button->setObjectName(QStringLiteral("Transfer_Button"));
	Transfer_Button->setGeometry(QRect(330, 560, 121, 21));
	Transfer_Button->setFont(font);
	Transfer_Button->setAutoFillBackground(true);

	Target_Select_Button = new QPushButton(this);
	Target_Select_Button->setObjectName(QStringLiteral("Target_Select_Button"));
	Target_Select_Button->setGeometry(QRect(20, 61, 91, 20));
	Target_Select_Button->setFont(font);
	Target_Select_Button->setAutoFillBackground(true);

	Source_Select_Button = new QPushButton(this);
	Source_Select_Button->setObjectName(QStringLiteral("Source_Select_Button"));
	Source_Select_Button->setGeometry(QRect(690, 61, 91, 20));
	Source_Select_Button->setFont(font);
	Source_Select_Button->setAutoFillBackground(true);

	//////////////////////////////
	//		 Key Buttons		//
	//////////////////////////////
	//this->connect(Transfer_Button, &QPushButton::clicked, this, &UIWindowController::sourceWritten);

	this->connect(Target_Select_Button, &QPushButton::clicked, this, &UIWindowController::selectTarget);


	//////////////////////////////
	//		    Update			//
	//////////////////////////////
	Source_List->raise();
	Target_List->raise();
	Transfer_Button->raise();
	Target_Up->raise();
	Target_Delete->raise();
	Target_Down->raise();
	Source_Up->raise();
	Source_Delete->raise();
	Source_Down->raise();
	Target_Select_Button->raise();
	Target_Root_Label->raise();
	Target_Joints->raise();
	Target_Input->raise();
	Source_Select_Button->raise();
	Source_Root_Label->raise();
	Source_Joints->raise();
	Source_Input->raise();

	//////////////////////////////
	//		   Set text			//
	//////////////////////////////
	retranslateUi(this);
}

void UIWindowController::cleanUp() noexcept {
	if (!Source_List.isNull()) delete Source_List;
	if (!Target_List.isNull()) delete Target_List;
	if (!Transfer_Button.isNull()) delete Transfer_Button;
	if (!Target_Up.isNull()) delete Target_Up;
	if (!Target_Delete.isNull()) delete Target_Delete;
	if (!Target_Down.isNull()) delete Target_Down;
	if (!Source_Up.isNull()) delete Source_Up;
	if (!Source_Delete.isNull()) delete Source_Delete;
	if (!Source_Down.isNull()) delete Source_Down;
	if (!Target_Select_Button.isNull()) delete Target_Select_Button;
	if (!Target_Root_Label.isNull()) delete Target_Root_Label;
	if (!Target_Joints.isNull()) delete Target_Joints;
	if (!Target_Input.isNull()) delete Target_Input;
	if (!Source_Select_Button.isNull()) delete Source_Select_Button;
	if (!Source_Root_Label.isNull()) delete Source_Root_Label;
	if (!Source_Joints.isNull()) delete Source_Joints;
	if (!Source_Input.isNull()) delete Source_Input;
}

void UIWindowController::retranslateUi(QWidget* Transfer_Window)
{
	Transfer_Window->setWindowTitle(QApplication::translate("Transfer_Window", "Transfer Animation", 0));
	Transfer_Button->setText(QApplication::translate("Transfer_Window", "Transfer Animation", 0));
	Target_Up->setText(QApplication::translate("Transfer_Window", "Up", 0));
	Target_Delete->setText(QApplication::translate("Transfer_Window", "Delete", 0));
	Target_Down->setText(QApplication::translate("Transfer_Window", "Down", 0));
	Source_Up->setText(QApplication::translate("Transfer_Window", "Up", 0));
	Source_Delete->setText(QApplication::translate("Transfer_Window", "Delete", 0));
	Source_Down->setText(QApplication::translate("Transfer_Window", "Down", 0));
	Target_Select_Button->setText(QApplication::translate("Transfer_Window", "Target Select:", 0));
	Target_Root_Label->setText(QApplication::translate("Transfer_Window", "Root:", 0));
	Target_Joints->setText(QApplication::translate("Transfer_Window", "Target Joints", 0));
	Source_Select_Button->setText(QApplication::translate("Transfer_Window", "Source Select:", 0));
	Source_Root_Label->setText(QApplication::translate("Transfer_Window", "Root:", 0));
	Source_Joints->setText(QApplication::translate("Transfer_Window", "Source Joints", 0));
} // retranslateUi

void UIWindowController::selectTarget()
{
	//MSelectionList selectionList {};
	//MGlobal::getActiveSelectionList(selectionList);
	//
	//for (auto i {0}; i < selectionList.length(); ++i)
	//{
	//	MObject currentObject {};
	//	selectionList.getDependNode(i, currentObject);
	//	MFnDependencyNode currentNode {currentObject};
	//	MGlobal::displayInfo(currentNode.name().asChar());
	//	MGlobal::displayInfo(currentNode.object().apiTypeStr());
	//	
	//
	//}
}