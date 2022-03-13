#pragma once

//////////////////////////////
//			MAYA			//
//////////////////////////////
#include <maya/MFnPlugin.h>
#include <maya/MGlobal.h>
#include <maya/MStatus.h>

#include <maya/MQtUtil.h>
#include <maya/MPxCommand.h>

//////////////////////////////
//			 Qt 			//
//////////////////////////////
#include <QtCore/qstring.h>
#include <QtCore/qpointer.h>

//////////////////////////////
//		Custom Headers		//
//////////////////////////////
#include "AnimUiEngine.h"

class TransferCmd : public MPxCommand
{
public:
	virtual MStatus doIt(const MArgList&);
	static void* creator() { return new TransferCmd; }
	static void cleanUp();

	static QString			pluginPath;
	static const QString	functionName;
	static const QString	buttonName;
	static QString			buttonObjectName;
	static QPointer<UIWindowController> uiController;
};
QPointer<UIWindowController> TransferCmd::uiController;

MStatus TransferCmd::doIt(const MArgList&)
{
	if (uiController.isNull()) 
	{
		uiController = new UIWindowController;
		uiController.data()->setWindowFlags(Qt::WindowStaysOnTopHint);
		uiController.data()->show();
	}
	else {
		uiController.data()->showNormal();
		uiController.data()->raise();
	}

	return MStatus::kSuccess;
}

void TransferCmd::cleanUp() {
	if (!uiController.isNull())
	{
		uiController.data()->cleanUp();
		delete uiController;
	}
}