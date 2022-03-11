#pragma once

//REQUIRED
#define NT_PLUGIN
#define REQUIRE_IOSTREAM
#define EXPORT __declspec(dllexport)
//

// Maya libs
#pragma comment(lib,"OpenMayaUI.lib")
#pragma comment(lib,"Foundation.lib")
#pragma comment(lib,"OpenMaya.lib")

//////////////////////////////
//			STD 			//
//////////////////////////////
#include <string.h>
//#include <direct.h> //if(mkdir("E:/MyFolder") == -1)
// #include <filesystem> //std::filesystem::current_path().c_str();

//////////////////////////////
//			MAYA			//
//////////////////////////////
#include <maya/MFnPlugin.h>
#include <maya/MGlobal.h>
#include <maya/M3dView.h>
#include <maya/MSelectionList.h>

#include <maya/MQtUtil.h>
#include <maya/MPxCommand.h>
#include <maya/MPxToolCommand.h>
#include <maya/MCommandResult.h>

#include <maya/MObject.h>

//////////////////////////////
//			 Qt 			//
//////////////////////////////

#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtCore/qobject.h>
#include <QtCore/qmetaobject.h>
#include <QtCore/QVariant>

#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QAction>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qstackedwidget.h>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QButtonGroup>

#include <QtWidgets/qlayout.h>

#include <QtCore/qfile.h>
#include <QtUiTools/quiloader.h>

#include <QtCore/qbuffer.h>
#include <QtCore/qiodevice.h>



void print_widget_tree(QObject& object, size_t depth) // Start with print_widget_tree(targetObject/Child, 0);
{
	MString debug{};
	MString depthSorter{};
	for (size_t layer = 0; layer < depth; ++layer)
	{
		depthSorter += "|";
	}
	depthSorter += "_> ";

	QObjectList list {object.children()};
	for (size_t i = 0; i < list.count(); ++i)
	{
		QObject* childObject{ list[i] };
		debug = depthSorter + MQtUtil::fullName(childObject);
		MGlobal::displayInfo(debug.asChar());
		print_widget_tree(*childObject, ++depth);
	}
}

void createShelf()
{
	MString command { R"V0G0N(
	proc addShelf() {
		global string $gShelfTopLevel;    
		shelfLayout -p $gShelfTopLevel "Animation_Transfer_Shelf";
	}
	addShelf();
	)V0G0N" };
	MGlobal::executeCommand(command);
}

void deleteShelf()
{
	MString command{ R"V0G0N(
	proc deleteShelf() {
		global string $gShelfTopLevel;
		string $customShelf = $gShelfTopLevel + "|Animation_Transfer_Shelf";
		if(`shelfLayout -q -ex "Animation_Transfer_Shelf"`)
			deleteUI $customShelf;
	}
	deleteShelf();
	)V0G0N" };
	MGlobal::executeCommand(command);
}

class UIWindowController {
public:
	QListWidget* Source_List;
	QListWidget* Target_List;
	QPushButton* Source_Up;
	QPushButton* Source_Delete;
	QPushButton* Source_Down;
	QPushButton* Target_Up;
	QPushButton* Target_Delete;
	QPushButton* Target_Down;
	QPushButton* Transfer_Button;
	QLineEdit* Source_Input;
	QLabel* Root_Label1;
	QLabel* Root_Label2;
	QLineEdit* Target_Input;
	QLabel* Source_Joints;
	QLabel* Target_Joints;

	void setupUi(QWidget* Transfer_Window)
	{
		if (Transfer_Window->objectName().isEmpty())
			Transfer_Window->setObjectName(QStringLiteral("Transfer_Window"));
		Transfer_Window->resize(800, 600);
		Source_List = new QListWidget(Transfer_Window);
		Source_List->setObjectName(QStringLiteral("Source_List"));
		Source_List->setGeometry(QRect(130, 90, 261, 451));
		Target_List = new QListWidget(Transfer_Window);
		Target_List->setObjectName(QStringLiteral("Target_List"));
		Target_List->setGeometry(QRect(410, 90, 261, 451));
		Source_Up = new QPushButton(Transfer_Window);
		Source_Up->setObjectName(QStringLiteral("Source_Up"));
		Source_Up->setEnabled(true);
		Source_Up->setGeometry(QRect(20, 260, 91, 21));
		QFont font;
		font.setPointSize(8);
		Source_Up->setFont(font);
		Source_Up->setAutoFillBackground(true);
		Source_Delete = new QPushButton(Transfer_Window);
		Source_Delete->setObjectName(QStringLiteral("Source_Delete"));
		Source_Delete->setGeometry(QRect(20, 290, 91, 21));
		QFont font1;
		font1.setPointSize(8);
		font1.setBold(false);
		font1.setItalic(false);
		font1.setWeight(50);
		Source_Delete->setFont(font1);
		Source_Delete->setAutoFillBackground(true);
		Source_Down = new QPushButton(Transfer_Window);
		Source_Down->setObjectName(QStringLiteral("Source_Down"));
		Source_Down->setGeometry(QRect(20, 320, 91, 21));
		Source_Down->setFont(font);
		Source_Down->setAutoFillBackground(true);
		Target_Up = new QPushButton(Transfer_Window);
		Target_Up->setObjectName(QStringLiteral("Target_Up"));
		Target_Up->setGeometry(QRect(690, 260, 91, 21));
		QFont font2;
		font2.setPointSize(8);
		font2.setBold(false);
		font2.setWeight(50);
		Target_Up->setFont(font2);
		Target_Up->setAutoFillBackground(true);
		Target_Up->setCheckable(false);
		Target_Delete = new QPushButton(Transfer_Window);
		Target_Delete->setObjectName(QStringLiteral("Target_Delete"));
		Target_Delete->setGeometry(QRect(690, 290, 91, 21));
		QFont font3;
		font3.setPointSize(8);
		font3.setBold(false);
		font3.setItalic(false);
		font3.setUnderline(false);
		font3.setWeight(50);
		font3.setStrikeOut(false);
		font3.setKerning(true);
		Target_Delete->setFont(font3);
		Target_Delete->setAutoFillBackground(true);
		Target_Down = new QPushButton(Transfer_Window);
		Target_Down->setObjectName(QStringLiteral("Target_Down"));
		Target_Down->setGeometry(QRect(690, 320, 91, 21));
		Target_Down->setFont(font);
		Target_Down->setAutoFillBackground(true);
		Transfer_Button = new QPushButton(Transfer_Window);
		Transfer_Button->setObjectName(QStringLiteral("Transfer_Button"));
		Transfer_Button->setGeometry(QRect(330, 560, 121, 21));
		Transfer_Button->setFont(font);
		Transfer_Button->setAutoFillBackground(true);
		Source_Input = new QLineEdit(Transfer_Window);
		Source_Input->setObjectName(QStringLiteral("Source_Input"));
		Source_Input->setGeometry(QRect(170, 60, 221, 21));
		Root_Label1 = new QLabel(Transfer_Window);
		Root_Label1->setObjectName(QStringLiteral("Root_Label1"));
		Root_Label1->setGeometry(QRect(130, 60, 46, 13));
		QFont font4;
		font4.setPointSize(8);
		font4.setBold(true);
		font4.setWeight(75);
		Root_Label1->setFont(font4);
		Root_Label2 = new QLabel(Transfer_Window);
		Root_Label2->setObjectName(QStringLiteral("Root_Label2"));
		Root_Label2->setGeometry(QRect(410, 60, 46, 13));
		Root_Label2->setFont(font4);
		Target_Input = new QLineEdit(Transfer_Window);
		Target_Input->setObjectName(QStringLiteral("Target_Input"));
		Target_Input->setGeometry(QRect(450, 60, 221, 21));
		Source_Joints = new QLabel(Transfer_Window);
		Source_Joints->setObjectName(QStringLiteral("Source_Joints"));
		Source_Joints->setGeometry(QRect(170, 40, 91, 21));
		QFont font5;
		font5.setPointSize(10);
		font5.setBold(true);
		font5.setWeight(75);
		Source_Joints->setFont(font5);
		Target_Joints = new QLabel(Transfer_Window);
		Target_Joints->setObjectName(QStringLiteral("Target_Joints"));
		Target_Joints->setGeometry(QRect(450, 40, 91, 21));
		Target_Joints->setFont(font5);
		Source_List->raise();
		Target_List->raise();
		Source_Up->raise();
		Source_Delete->raise();
		Source_Down->raise();
		Target_Up->raise();
		Target_Delete->raise();
		Target_Down->raise();
		Transfer_Button->raise();
		Source_Input->raise();
		Root_Label1->raise();
		Root_Label2->raise();
		Target_Input->raise();
		Target_Joints->raise();
		Source_Joints->raise();

		retranslateUi(Transfer_Window);

		QMetaObject::connectSlotsByName(Transfer_Window);
	} // setupUi

	void retranslateUi(QWidget* Transfer_Window)
	{
		Transfer_Window->setWindowTitle(QApplication::translate("Transfer_Window", "Transfer Animation", 0));
		Source_Up->setText(QApplication::translate("Transfer_Window", "Up", 0));
		Source_Delete->setText(QApplication::translate("Transfer_Window", "Delete", 0));
		Source_Down->setText(QApplication::translate("Transfer_Window", "Down", 0));
		Target_Up->setText(QApplication::translate("Transfer_Window", "Up", 0));
		Target_Delete->setText(QApplication::translate("Transfer_Window", "Delete", 0));
		Target_Down->setText(QApplication::translate("Transfer_Window", "Down", 0));
		Transfer_Button->setText(QApplication::translate("Transfer_Window", "Transfer Animation", 0));
		Root_Label1->setText(QApplication::translate("Transfer_Window", "Root:", 0));
		Root_Label2->setText(QApplication::translate("Transfer_Window", "Root:", 0));
		Source_Joints->setText(QApplication::translate("Transfer_Window", "Source Joints", 0));
		Target_Joints->setText(QApplication::translate("Transfer_Window", "Target Joints", 0));
	} // retranslateUi
};
// Generated with uic.exe

//
// NOTE: Figure out a better way to storing data from callbacks...
//
UIWindowController* uiController{ new UIWindowController };
MString thisAnimPath {};
QWidget* uiWidget {new QWidget};
class TransferCmd : public MPxCommand
{
public:
	TransferCmd() {
		QDialog dialog;
		uiWidget->setWindowFlags(Qt::WindowStaysOnTopHint);
		uiController->setupUi(uiWidget);
		uiWidget->show();

		uiWidget->connect(uiController->Source_Input, SIGNAL(uiController->Source_Input->textEdited()), uiWidget, SIGNAL(sourceWritten()));
		uiWidget->connect(uiController->Transfer_Button, SIGNAL(uiController->Transfer_Button->pressed()), uiWidget, SIGNAL(sourceWritten()));
	};
	~TransferCmd() { uiWidget->hide(); delete uiWidget; delete uiController; MGlobal::displayInfo("Deconstructor running!"); };
	virtual MStatus doIt(const MArgList&);
	static void* creator() {return new TransferCmd;}
	//void  destroyer() { this->uiWidget->hide(); delete this->uiWidget; delete uiController; };

	signals:
	void sourceWritten()
	{
		//uiController->Source_List->clear();
		//QString tInput {uiController->Source_Input->text()};
		MGlobal::displayInfo("Working!");
	}


private:
	MString path {};
};

MStatus TransferCmd::doIt(const MArgList& list)
{
	MString debug {};
	
	//MGlobal::displayInfo(thisAnimPath);
	QString uiFullPath { thisAnimPath.asChar() };
	uiFullPath += "/AnimationTransferUI.ui";

	QUiLoader loader;
	QFile uiFile(uiFullPath);
	if (uiFile.exists())
	{
		uiFile.open(QFile::ReadOnly);
		uiWidget = loader.load(&uiFile, MQtUtil::mainWindow());
		uiFile.close();
	}
	
	
	//QByteArray uiByteArray {};
	//if (uiFile.get()->exists())
	//{
	//	uiFile.get()->open(QFile::ReadOnly);
	//	uiByteArray = uiFile.get()->readAll();
	//	uiFile.get()->close();
	//}
	//
	//if (uiByteArray.isEmpty())
	//{
	//	MGlobal::displayInfo("Couldn't find UI file!");
	//	return MStatus::kFailure;
	//}
	//
	//std::unique_ptr<QBuffer> uiBuffer {new QBuffer()};
	//uiBuffer->open(QBuffer::ReadOnly | QBuffer::WriteOnly);
	//uiBuffer->write(uiByteArray);
	//uiBuffer->seek(0);
	//
	//QUiLoader uiLoader;
	//this->uiWidget = uiLoader.load(qobject_cast<QIODevice*>(uiBuffer.get()), MQtUtil::mainWindow());

	/*MGlobal::displayInfo("Command is working!");

	MString command { R"V0G0N(
		proc string buttonFunc()\n
		{\n\t
				string $result = `shelfButton -parent 
		}
	)V0G0N" };
	MCommandResult comRes {};
	MGlobal::executeCommand(command, comRes);
	MGlobal::displayInfo(comRes.stringResult().asChar());*/

	return MS::kSuccess;
}


EXPORT MStatus initializePlugin(MObject obj) {
	MStatus res{ MS::kFailure };
	MFnPlugin pluginHandle{ obj, "Animation Transfer", "1.0", "Any", &res };
	if (!res)
	{
		CHECK_MSTATUS(res);
		return res;
	}
	else
	{
		MGlobal::displayInfo("Maya plugin loaded!");
	}

	thisAnimPath = pluginHandle.loadPath();
	createShelf();

	if (!pluginHandle.registerCommand("animTransfer", TransferCmd::creator))
	{
		res.perror("registerCommand failed!");
	}	

	return res;
}

EXPORT MStatus uninitializePlugin(MObject obj)
{
	MStatus res{};
	MFnPlugin pluginHandle(obj);
	MGlobal::displayInfo("Maya plugin unloaded!");

	//uiWidget->hide();
	//if (uiWidget)
	//{
	//	delete uiWidget;
	//}
	//if (uiController)
	//{
	//	delete uiController;
	//}
	deleteShelf();

	res = pluginHandle.deregisterCommand("animTransfer");
	if (!res)
	{
		res.perror("deregisterCommand failed");
	}
	
	return MS::kSuccess;
}
