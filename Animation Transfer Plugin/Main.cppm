#pragma once

#define NT_PLUGIN
#define REQUIRE_IOSTREAM
#define EXPORT __declspec(dllexport)

// Commands
#include <maya/MPxCommand.h>
#pragma comment(lib,"OpenMayaUI.lib")

// Libraries to link from Maya
// This can be also done in the properties setting for the project.
#pragma comment(lib,"Foundation.lib")
#pragma comment(lib,"OpenMaya.lib")

#include <string.h>
//#include <direct.h> //if(mkdir("E:/MyFolder") == -1)
// #include <filesystem> //std::filesystem::current_path().c_str();
#include <maya/MFnPlugin.h>
#include <maya/MGlobal.h>
#include <maya/M3dView.h>

#include <maya/MQtUtil.h>
#include <maya/MObject.h>
#include <maya/MPxToolCommand.h>
#include <maya/MCommandResult.h>
#include <QtCore/qobject.h>
#include <QtCore/qmetaobject.h>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qstackedwidget.h>

//#include <QtCore/qfile.h>
//#include <QtUiTools/quiloader.h>

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

class TransferCmd : public MPxCommand
{
public:
	//~TransferCmd() { MGlobal::displayInfo("Deconstructor running!")};
	virtual MStatus doIt(const MArgList&);
	static void* creator() {return new TransferCmd;}

private:
	std::unique_ptr<QWidget> myWidget {new QWidget};
};

MStatus TransferCmd::doIt(const MArgList& list)
{
	MString debug {};
	MGlobal::displayInfo("Command is working!");

	QWidget* windowWidget { MQtUtil::mainWindow() };
	QObject* windowObject { windowWidget };
	QObject* targetChild { windowObject->children()[6]->children()[2]->children()[4]->children()[1]->
		children()[1]->children()[0]->children()[1]->children()[1]->children()[1]->children()[2]->
		children()[1]->children()[0]->children()[4]};
		
	//QWidget* customShelfWidget{ qobject_cast<QWidget*>(targetChild->children()[9]) };
	//QMetaObject metaTarget { targetChild->children()[9]->metaObject() };
	//MGlobal::displayInfo(metaTarget.className());
	//std::unique_ptr<QLayout> customShelfLayout{ new QLayout(customShelfWidget->layout()) };
	//try { this->myWidget.get()->setLayout(customShelfLayout);}
	//catch (std::exception e) { MGlobal::displayInfo("crap"); MGlobal::displayInfo(e.what()); }
	//QStackedWidget* shelfTabs {qobject_cast<QStackedWidget*>(targetChild)};
	//try { shelfTabs->addWidget(myWidget.get()); }
	//catch (std::exception e) { MGlobal::displayInfo(e.what()); };

	debug = MQtUtil::fullName(windowObject->children()[6]->children()[2]->children()[4]->children()[1]->
		children()[1]->children()[0]->children()[1]->children()[1]->children()[1]->children()[2]->
		children()[1]->children()[0]->children()[4]);
	//MGlobal::displayInfo(debug);
	//print_widget_tree(*targetChild, 0);

	//MString command { "proc string testFunc()\n{\n\tstring $test = \"testing\";\n\treturn $test;\n}\n\ntestFunc();" };
	MString command 
	{ "proc string buttonFunc()\n{\n\tstring $result = `shelfButton -parent $"
	};
	MCommandResult comRes {};
	MGlobal::executeCommand(command, comRes);
	MGlobal::displayInfo(comRes.stringResult().asChar());

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

	if (!pluginHandle.registerCommand("animTransfer", TransferCmd::creator));
	{
		res.perror("registerCommand failed!");
	}
	
	

	//if (!MGlobal::executeCommand(shelfSetup))
	//{
	//	MGlobal::displayInfo("What?");
	//}

	MPxToolCommand* tool {};
	


	return res;
}

EXPORT MStatus uninitializePlugin(MObject obj)
{
	MStatus res{};
	MFnPlugin pluginHandle(obj);
	MGlobal::displayInfo("Maya plugin unloaded!");

	res = pluginHandle.deregisterCommand("animTransfer");
	if (!res)
	{
		res.perror("deregisterCommand failed");
	}
	
	return MS::kSuccess;
}
