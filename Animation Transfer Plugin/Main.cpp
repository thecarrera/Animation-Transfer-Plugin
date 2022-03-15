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
#include <maya/MCommandResult.h>

#include <maya/MQtUtil.h>
#include <maya/MPxCommand.h>

#include <maya/M3dView.h>
#include <maya/MDagPath.h>
#include <maya/MFnDagNode.h>

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
const QString TransferCmd::buttonName("Animation Transfer Tool");
QString TransferCmd::buttonObjectName;
QString TransferCmd::pluginPath;

void createShelfButton() {
	MString command { MString(R"V0G0N(
proc string createButton(){
	string $buttonPath = `shelfButton
	-parent "Animation_Transfer_Shelf"
	-enable 1
	-width 34
	-height 34
	-manage 1
	-visible 1
	-annotation "Animation transfer tool - From selection"
	-image "mayaIcon.png"
	-style "iconOnly"	
	-label ")V0G0N") + MString(TransferCmd::buttonName.toStdString().c_str()) + MString(R"V0G0N("
	-command ")V0G0N") + MString(TransferCmd::functionName.toStdString().c_str()) + MString(R"V0G0N("`;
	
	string $tokenResults[];
	int $numTokens = `tokenize $buttonPath "|" $tokenResults`;
	return $tokenResults[$numTokens - 1];
}
createButton();
	)V0G0N") };
	MCommandResult comRes {};
	MGlobal::executeCommand(command, comRes);
	TransferCmd::buttonObjectName = comRes.stringResult().asChar();
}

void deleteButton() {
	MString command{ MString(R"V0G0N(
proc deleteAnimButton(){
	global string $gShelfTopLevel;
	string $path = $gShelfTopLevel + "|Animation_Transfer_Shelf|)V0G0N")
	+ MString(TransferCmd::buttonObjectName.toStdString().c_str()) + MString(R"V0G0N(";
	deleteUI $path;
}
deleteAnimButton();
)V0G0N") };
	MGlobal::executeCommand(command);
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

	//MDagPath mainCamPath {};
	//M3dView::active3dView().getCamera(mainCamPath);
	//MFnDagNode camDag {mainCamPath.node()};
	//MFnDagNode rootDag {camDag.dagRoot()};
	
	TransferCmd::pluginPath = pluginHandle.loadPath().asChar();
	createShelf();
	createShelfButton();
	
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
	
	deleteButton();
	deleteShelf();
	TransferCmd::cleanUp();
	
	res = pluginHandle.deregisterCommand(TransferCmd::functionName.toStdString().c_str());
	if (!res)
	{
		res.perror("deregisterCommand failed");
	}

	return MS::kSuccess;
}
