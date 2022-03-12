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
#include "AnimTransCmd.h"

//////////////////////////////
//	Static Class Variables	//
//////////////////////////////
const QString TransferCmd::functionName("animTransfer");
QString TransferCmd::path;

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
	
	TransferCmd::path = pluginHandle.loadPath().asChar();
	createShelf();

	if (!pluginHandle.registerCommand(TransferCmd::functionName.toStdString().c_str(), TransferCmd::creator));
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
	
	deleteShelf();
	TransferCmd::cleanUp();

	res = pluginHandle.deregisterCommand(TransferCmd::functionName.toStdString().c_str());
	if (!res)
	{
		res.perror("deregisterCommand failed");
	}

	return MS::kSuccess;
}
