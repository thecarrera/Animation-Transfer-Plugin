#pragma once

//////////////////////////////
//			MAYA			//
//////////////////////////////
#include <maya/MGlobal.h>
#include <maya/MDGModifier.h>
#include <maya/MDagModifier.h>
#include <maya/MSelectionList.h>
#include <maya/MItSelectionList.h>

#include <maya/MDagPath.h>

#include <maya/MObject.h>
#include <maya/MObjectArray.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MFnDagNode.h>
#include <maya/MFnIkJoint.h>
#include <maya/MItKeyframe.h>

#include <maya/MAnimUtil.h>
#include <maya/MAnimControl.h>
#include <maya/MFnAnimCurve.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MArrayDataHandle.h>
#include <maya/MPlug.h>
#include <maya/MPlugArray.h>
#include <maya/MFnAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MFnMatrixData.h>
#include <maya/MMatrix.h>

#include <maya/MFnNumericAttribute.h>

//////////////////////////////
//			 Qt 			//
//////////////////////////////
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qinputdialog.h>
#include <QtGui/qevent.h>
#include <QtCore/qdebug.h>
#include <QtCore/qobject.h>
#include <QtWidgets/qcheckbox.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>
#include <QtCore/qpointer.h>
#include <QtCore/qmetaobject.h>

class UIWindowController : public QWidget {
public:
	enum class SELTYPE{
		SOURCE,
		TARGET
	};

public:
	UIWindowController();
	static void cleanUp() noexcept;
	void closeEvent(QCloseEvent* event) override;

private:
	static QPointer<QWidget>		thisClass;
	static QPointer<QListWidget>	Target_List;
	static QPointer<QListWidget>	Source_List;
	static QPointer<QPushButton>	Transfer_Button;

	static QPointer<QPushButton>	Target_Up;
	static QPointer<QPushButton>	Target_Delete;
	static QPointer<QPushButton>	Target_Down;
	static QPointer<QPushButton>	Source_Up;
	static QPointer<QPushButton>	Source_Delete;
	static QPointer<QPushButton>	Source_Down;
	
	static QPointer<QLabel>			Target_Check_Label;
	static QPointer<QCheckBox>		Target_Check_Box;
	static QPointer<QPushButton>	Target_Select_Button;
	static QPointer<QLabel>			Target_Root_Label;
	static QPointer<QLabel>			Target_Joints;
	static QPointer<QLineEdit>		Target_Input;

	static QPointer<QLabel>			Source_Check_Label;
	static QPointer<QCheckBox>		Source_Check_Box;
	static QPointer<QPushButton>	Source_Select_Button;
	static QPointer<QLabel>			Source_Root_Label;
	static QPointer<QLabel>			Source_Joints;
	static QPointer<QLineEdit>		Source_Input;

	static bool						Target_From_Sel;
	static bool						Source_From_Sel;
	static bool						retainRootPos;

	static void retranslateUi(QWidget* const);

	static void addJointsToList(MFnDagNode&, QListWidget&);
	static bool peekChildren(MFnDagNode&, QPointer<QListWidget>, QPointer<QLineEdit>);
	static MObject getTrueRoot(MFnDagNode&);
	static void selection(const SELTYPE);

	static void upInList(const SELTYPE);
	static MObject lastChildforDeletion(const MFnDagNode& const);
	static void deleteItemInList(const SELTYPE);
	static void downInList(const SELTYPE);

	static std::unique_ptr<MPlugArray> getJointAttributePlugs(const MObject& const);
	static std::unique_ptr<MPlugArray> getMatrixAttributePlugs(const MObject& const);
	static std::unique_ptr<MPlugArray> getBindAttributePlugs(const MObject& const);
	static MStatus setKeyframes(MPlug& const, const MPlug& const);
	
	//static MStatus setMatrix(MPlug&, MPlug&);
	//static MStatus bindMatrixTransfer(MPlugArray& const, MPlugArray& const);
	//static MStatus matrixTransfer(const MPlugArray& const, const MPlugArray& const);

	static MStatus transferPlugArray(MArrayDataHandle& const, MArrayDataHandle& const);
	static MStatus transferMatrix(MPlug& const, const MPlug& const);
	static MStatus transferDouble3(MPlug& const, const MPlug& const);
	static MStatus transferEnum(MPlug& const, const MPlug& const);
	static MStatus transferPlugs(MPlugArray& const, MPlugArray& const);

	static MStatus jointTransfer(const MObject& const, const MObject& const);
	static void transferAnimation();

	public slots:
	static void selectTarget();
	static void selectSource();
	static void targetFromCheck();
	static void sourceFromCheck();
	static void upTargetList();
	static void deleteTargetListItem();
	static void downTargetList();
	static void upSourceList();
	static void deleteSourceListItem();
	static void downSourceList();

}; // Generated with uic.exe

QPointer<QWidget>		UIWindowController::thisClass;
QPointer<QListWidget>	UIWindowController::Target_List;
QPointer<QListWidget>	UIWindowController::Source_List;
QPointer<QPushButton>	UIWindowController::Transfer_Button;
QPointer<QPushButton>	UIWindowController::Target_Up;
QPointer<QPushButton>	UIWindowController::Target_Delete;
QPointer<QPushButton>	UIWindowController::Target_Down;
QPointer<QPushButton>	UIWindowController::Source_Up;
QPointer<QPushButton>	UIWindowController::Source_Delete;
QPointer<QPushButton>	UIWindowController::Source_Down;
QPointer<QLabel>		UIWindowController::Target_Check_Label;
QPointer<QCheckBox>		UIWindowController::Target_Check_Box;
QPointer<QPushButton>	UIWindowController::Target_Select_Button;
QPointer<QLabel>		UIWindowController::Target_Root_Label;
QPointer<QLabel>		UIWindowController::Target_Joints;
QPointer<QLineEdit>		UIWindowController::Target_Input;
QPointer<QLabel>		UIWindowController::Source_Check_Label;
QPointer<QCheckBox>		UIWindowController::Source_Check_Box;
QPointer<QPushButton>	UIWindowController::Source_Select_Button;
QPointer<QLabel>		UIWindowController::Source_Root_Label;
QPointer<QLabel>		UIWindowController::Source_Joints;
QPointer<QLineEdit>		UIWindowController::Source_Input;
bool					UIWindowController::Target_From_Sel {};
bool					UIWindowController::Source_From_Sel {};
bool					UIWindowController::retainRootPos {};

UIWindowController::UIWindowController(){
	if (this->objectName().isEmpty())
		this->setObjectName(QStringLiteral("Transfer_Window"));
	this->setFixedSize(800, 600);
	thisClass = this;

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
	Target_List = new QListWidget(this);
	Target_List->setObjectName(QStringLiteral("Target_List"));
	Target_List->setGeometry(QRect(140, 90, 250, 450));
	
	Source_List = new QListWidget(this);
	Source_List->setObjectName(QStringLiteral("Source_List"));
	Source_List->setGeometry(QRect(410, 90, 250, 450));
	
	
	//////////////////////////////
	//			Inputs			//
	//////////////////////////////
	Target_Root_Label = new QLabel(this);
	Target_Root_Label->setObjectName(QStringLiteral("Target_Root_Label"));
	Target_Root_Label->setGeometry(QRect(140, 60, 40, 20));
	Target_Root_Label->setFont(font);
	
	Target_Joints = new QLabel(this);
	Target_Joints->setObjectName(QStringLiteral("Target_Joint"));
	Target_Joints->setGeometry(QRect(180, 40, 100, 20));
	Target_Joints->setFont(font);
	
	Target_Input = new QLineEdit(this);
	Target_Input->setObjectName(QStringLiteral("Target_Input"));
	Target_Input->setGeometry(QRect(180, 60, 210, 20));
	
	Source_Root_Label = new QLabel(this);
	Source_Root_Label->setObjectName(QStringLiteral("Source_Root_Label"));
	Source_Root_Label->setGeometry(QRect(410, 60, 40, 20));
	Source_Root_Label->setFont(font);
	
	Source_Joints = new QLabel(this);
	Source_Joints->setObjectName(QStringLiteral("Source_Joint"));
	Source_Joints->setGeometry(QRect(450, 40, 100, 20));
	Source_Joints->setFont(font);
	
	Source_Input = new QLineEdit(this);
	Source_Input->setObjectName(QStringLiteral("Source_Input"));
	Source_Input->setGeometry(QRect(450, 60, 210, 20));
	
	//////////////////////////////
	//		Target Scroll		//
	//////////////////////////////
	Target_Up = new QPushButton(this);
	Target_Up->setObjectName(QStringLiteral("Target_Up"));
	Target_Up->setGeometry(QRect(20, 260, 100, 20));
	Target_Up->setFont(font);
	Target_Up->setAutoFillBackground(true);

	Target_Delete = new QPushButton(this);
	Target_Delete->setObjectName(QStringLiteral("Target_Delete"));
	Target_Delete->setGeometry(QRect(20, 290, 100, 20));
	Target_Delete->setFont(font);
	Target_Delete->setAutoFillBackground(true);

	Target_Down = new QPushButton(this);
	Target_Down->setObjectName(QStringLiteral("Target_Down"));
	Target_Down->setGeometry(QRect(20, 320, 100, 20));
	Target_Down->setFont(font);
	Target_Down->setAutoFillBackground(true);
	
	//////////////////////////////
	//		 Source Sroll		//
	//////////////////////////////
	Source_Up = new QPushButton(this);
	Source_Up->setObjectName(QStringLiteral("Source_Up"));
	Source_Up->setEnabled(true);
	Source_Up->setGeometry(QRect(680, 260, 100, 20));
	Source_Up->setFont(font);
	Source_Up->setAutoFillBackground(true);
	
	Source_Delete = new QPushButton(this);
	Source_Delete->setObjectName(QStringLiteral("Source_Delete"));
	Source_Delete->setGeometry(QRect(680, 290, 100, 20));
	Source_Delete->setFont(font);
	Source_Delete->setAutoFillBackground(true);

	Source_Down = new QPushButton(this);
	Source_Down->setObjectName(QStringLiteral("Source_Down"));
	Source_Down->setGeometry(QRect(680, 320, 100, 20));
	Source_Down->setFont(font);
	Source_Down->setAutoFillBackground(true);
	
	//////////////////////////////
	//		 Key Buttons		//
	//////////////////////////////
	Transfer_Button = new QPushButton(this);
	Transfer_Button->setObjectName(QStringLiteral("Transfer_Button"));
	Transfer_Button->setGeometry(QRect(330, 560, 120, 20));
	Transfer_Button->setFont(font);
	Transfer_Button->setAutoFillBackground(true);

	Target_Check_Label = new QLabel(this);
	Target_Check_Label->setObjectName("Target_Check_Label");
	Target_Check_Label->setGeometry(QRect(45, 20, 100, 20));
	Target_Check_Label->setFont(font);

	Target_Check_Box = new QCheckBox(this);
	Target_Check_Box->setObjectName(QStringLiteral("Target_Check_Box"));
	Target_Check_Box->setGeometry(20, 20, 20, 20);

	Target_Select_Button = new QPushButton(this);
	Target_Select_Button->setObjectName(QStringLiteral("Target_Select_Button"));
	Target_Select_Button->setGeometry(QRect(20, 60, 100, 20));
	Target_Select_Button->setFont(font);
	Target_Select_Button->setAutoFillBackground(true);

	Source_Check_Label = new QLabel(this);
	Source_Check_Label->setObjectName("Source_Check_Label");
	Source_Check_Label->setGeometry(QRect(680, 20, 100, 20));
	Source_Check_Label->setFont(font);

	Source_Check_Box = new QCheckBox(this);
	Source_Check_Box->setObjectName(QStringLiteral("Source_Check_Box"));
	Source_Check_Box->setGeometry(768, 20, 20, 20);

	Source_Select_Button = new QPushButton(this);
	Source_Select_Button->setObjectName(QStringLiteral("Source_Select_Button"));
	Source_Select_Button->setGeometry(QRect(680, 60, 100, 20));
	Source_Select_Button->setFont(font);
	Source_Select_Button->setAutoFillBackground(true);



	//////////////////////////////
	//		 Key Buttons		//
	//////////////////////////////
	//this->connect(Transfer_Button, &QPushButton::clicked, this, &UIWindowController::sourceWritten);

	this->connect(Target_Check_Box, &QCheckBox::clicked, this, &UIWindowController::targetFromCheck);
	this->connect(Source_Check_Box, &QCheckBox::clicked, this, &UIWindowController::sourceFromCheck);
	this->connect(Target_Select_Button, &QPushButton::clicked, this, &UIWindowController::selectTarget);
	this->connect(Source_Select_Button, &QPushButton::clicked, this, &UIWindowController::selectSource);
	this->connect(Target_Up, &QPushButton::clicked, this, &UIWindowController::upTargetList);
	this->connect(Target_Delete, &QPushButton::clicked, this, &UIWindowController::deleteTargetListItem);
	this->connect(Target_Down, &QPushButton::clicked, this, &UIWindowController::downTargetList);
	this->connect(Source_Up, &QPushButton::clicked, this, &UIWindowController::upSourceList);
	this->connect(Source_Delete, &QPushButton::clicked, this, &UIWindowController::deleteSourceListItem);
	this->connect(Source_Down, &QPushButton::clicked, this, &UIWindowController::downSourceList);
	this->connect(Transfer_Button, &QPushButton::clicked, this, &UIWindowController::transferAnimation);


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
	Target_Check_Label->raise();
	Target_Check_Box->raise();
	Target_Select_Button->raise();
	Target_Root_Label->raise();
	Target_Joints->raise();
	Target_Input->raise();
	Source_Check_Label->raise();
	Source_Check_Box->raise();
	Source_Select_Button->raise();
	Source_Root_Label->raise();
	Source_Joints->raise();
	Source_Input->raise();

	//////////////////////////////
	//		   Set text			//
	//////////////////////////////
	retranslateUi(this);
}
void UIWindowController::retranslateUi(QWidget* const Transfer_Window)
{
	Transfer_Window->setWindowTitle(QApplication::translate("Transfer_Window", "Transfer Animation", 0));
	Transfer_Button->setText(QApplication::translate("Transfer_Window", "Transfer Animation", 0));
	Target_Up->setText(QApplication::translate("Transfer_Window", "Up", 0));
	Target_Delete->setText(QApplication::translate("Transfer_Window", "Delete", 0));
	Target_Down->setText(QApplication::translate("Transfer_Window", "Down", 0));
	Source_Up->setText(QApplication::translate("Transfer_Window", "Up", 0));
	Source_Delete->setText(QApplication::translate("Transfer_Window", "Delete", 0));
	Source_Down->setText(QApplication::translate("Transfer_Window", "Down", 0));
	Target_Check_Label->setText(QApplication::translate("Transfer_Window", "From selection", 0));
	Target_Select_Button->setText(QApplication::translate("Transfer_Window", "Target Select:", 0));
	Target_Root_Label->setText(QApplication::translate("Transfer_Window", "Root:", 0));
	Target_Joints->setText(QApplication::translate("Transfer_Window", "Target Joints", 0));
	Source_Check_Label->setText(QApplication::translate("Transfer_Window", "From selection", 0));
	Source_Select_Button->setText(QApplication::translate("Transfer_Window", "Source Select:", 0));
	Source_Root_Label->setText(QApplication::translate("Transfer_Window", "Root:", 0));
	Source_Joints->setText(QApplication::translate("Transfer_Window", "Source Joints", 0));
} // retranslateUi

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
	if (!Target_Check_Label.isNull()) delete Target_Check_Label;
	if (!Target_Check_Box.isNull()) delete Target_Check_Box;
	if (!Target_Select_Button.isNull()) delete Target_Select_Button;
	if (!Target_Root_Label.isNull()) delete Target_Root_Label;
	if (!Target_Joints.isNull()) delete Target_Joints;
	if (!Target_Input.isNull()) delete Target_Input;
	if (!Source_Check_Label.isNull()) delete Source_Check_Label;
	if (!Source_Check_Box.isNull()) delete Source_Check_Box;
	if (!Source_Select_Button.isNull()) delete Source_Select_Button;
	if (!Source_Root_Label.isNull()) delete Source_Root_Label;
	if (!Source_Joints.isNull()) delete Source_Joints;
	if (!Source_Input.isNull()) delete Source_Input;
}
void UIWindowController::closeEvent(QCloseEvent* event) {
	Target_Input->clear();
	Target_List->clear();
	Source_Input->clear();
	Source_List->clear();
}

void UIWindowController::addJointsToList(MFnDagNode& dag, QListWidget& List) {
	for (size_t i = 0; i < dag.childCount(); ++i)
	{
		MFnDependencyNode childNode{ dag.child(i) };
		if (childNode.object().apiType() == MFn::kJoint)
		{
			List.addItem(childNode.name().asChar());
		}
		MFnDagNode childDag { childNode.object() };
		addJointsToList(childDag, List);
	}
}
bool UIWindowController::peekChildren(MFnDagNode& dag, QPointer<QListWidget> list, QPointer<QLineEdit> input)
{
	//MGlobal::displayInfo(dag.name().asChar());
	if (dag.name() == input->text().toStdString().c_str()) return true;
	for (size_t i = 0; i < list->count(); ++i)
	{
		if (dag.name() == list->item(i)->text().toStdString().c_str()) return true;
	}

	for (size_t i = 0; i < dag.childCount(); ++i)
	{
		MFnDagNode child {dag.child(i)};
		peekChildren(child, list, input);
	}
	return false;
}
MObject UIWindowController::getTrueRoot(MFnDagNode& dag)
{
	MString debug {};
	MDagPath trueRootPath{};
	dag.getPath(trueRootPath);
	MDagPath latestJoint{};
	size_t length {trueRootPath.length()};

	for (size_t i = 1; i < length; ++i)
	{
		trueRootPath.pop();
		if (trueRootPath.apiType() == MFn::kJoint) latestJoint = trueRootPath;
	}
	if (trueRootPath.apiType() != MFn::kJoint) trueRootPath = latestJoint;
	return trueRootPath.node();
}
void UIWindowController::selection(const SELTYPE type)
{
	MSelectionList selectionList{};
	MGlobal::getActiveSelectionList(selectionList);
	if (selectionList.length() > 1 || selectionList.length() < 1)
	{
		MGlobal::displayInfo("Please select atleast and no more than one target!");
		return;
	}
	MObject selRoot{};
	selectionList.getDependNode(0, selRoot);
	MFnDependencyNode rootNode{ selRoot };
	MFnDagNode rootDag{ selRoot };
	
	bool selBool {};
	QPointer<QLineEdit>   Input{};
	QPointer<QLineEdit>	  OppositeInput{};
	QPointer<QListWidget> OppositeList{};
	QPointer<QListWidget> List {};
	switch (type)
	{
	case SELTYPE::SOURCE:
		Input = Source_Input;
		OppositeInput = Target_Input;
		OppositeList = Target_List;
		List = Source_List;
		selBool = Source_From_Sel;
		break;
	case SELTYPE::TARGET:
		Input = Target_Input;
		OppositeInput = Source_Input;
		OppositeList = Source_List;
		List = Target_List;
		selBool = Target_From_Sel;
		break;
	default:
		MGlobal::displayInfo("Error_type");
		return;
	}

	MFnDagNode trueRoot{getTrueRoot(rootDag)};
	
	if (!selBool)
	{
		rootNode.setObject(trueRoot.object());
		rootDag.setObject(trueRoot.object());
	}
	
	if (rootNode.object().apiType() != MFn::kJoint)
	{
		MGlobal::displayInfo("Must select a joint!");
		return;
	}
	else if (peekChildren(rootDag, OppositeList, OppositeInput))
	{
		MGlobal::displayInfo("Can't select the same joint tree for target and source!");
		return;
	}
	Input->setText(rootNode.name().asChar());
	List->clear();
	
	for (size_t i = 0; i < rootDag.childCount(); ++i)
	{
		MFnDependencyNode childNode{ rootDag.child(i) };
		if (childNode.object().apiType() == MFn::kJoint)
		{
			List->addItem(childNode.name().asChar());
		}
		MFnDagNode childDag{ childNode.object() };
		addJointsToList(childDag, *List);
	}
	if ((Input->text() != "" && OppositeInput->text() != "") &&
		(List->count() != List->count()))
			MGlobal::displayInfo("WARNNING: Count of joint lists are unequal! Adjusting to lowest count!");
}

void UIWindowController::upInList(const SELTYPE type) {
	QPointer<QListWidget> list {};
	QPointer<QLineEdit> label {};
	switch (type)
	{
	case SELTYPE::SOURCE:
		list = Source_List;
		label = Source_Input;
		break;
	case SELTYPE::TARGET:
		list = Target_List;
		label = Target_Input;
		break;
	default:
		MGlobal::displayInfo("Error_type");
		return;
	}
	if (list->count() < 1 || label->text().length() < 1) return;
	if (list->selectedItems().size() < 1) list->setCurrentRow(list->count()-1);
	int index = list->currentRow();
	QListWidgetItem* currentItem {list->takeItem(index)};
	MSelectionList slList{};
	MGlobal::clearSelectionList();
	MGlobal::selectByName(currentItem->text().toStdString().c_str());
	MGlobal::getActiveSelectionList(slList);
	MObject currentObj {};
	slList.getDependNode(0, currentObj);

	MStatus res{};
	MFnDagNode currentDag {currentObj};
	MObjectArray childObjects {};
	for (size_t i = 0; i < currentDag.childCount(); ++i)
	{
		childObjects.append(currentDag.child(i));
	}
	MFnDagNode parentDag {currentDag.parent(0)};
	MFnDagNode grandParentDag {parentDag.parent(0)};
	
	//Change to C++ code
	MString command {};
	if (grandParentDag.name() == "world")
		command = MString(R"V0G0N(parent )V0G0N") + MString("-w ") + currentDag.name();
	else
		command = MString(R"V0G0N(parent )V0G0N") + currentDag.name() + MString(" ") + grandParentDag.name();	
	
	MGlobal::executeCommand(command);
	for (size_t i = 0; i < childObjects.length(); ++i)
	{
		MFnDagNode childDag {childObjects[i]};
		command = MString(R"V0G0N(parent )V0G0N") + childDag.name() + MString(" ") + parentDag.name();
		MGlobal::executeCommand(command);
	}
	command = MString(R"V0G0N(parent )V0G0N") + parentDag.name() + MString(" ") + currentDag.name();
	MGlobal::executeCommand(command);

	//for (size_t i = 0; i < childObjects.length(); ++i)
	//{
	//	res = parentNode.addChild(childObjects[i], i);
	//	MFnDagNode childDag{childObjects[i]};
	//	MGlobal::displayInfo(childDag.name());
	//	MGlobal::displayInfo(res.errorString());
	//}
	//MObject parentObj {parentNode.object()};
	//res = currentDagNode.addChild(parentObj);
	//MGlobal::displayInfo(parentNode.name());
	//MGlobal::displayInfo(res.errorString());

	if (index == 0) {
		MGlobal::getActiveSelectionList(slList);

		list->insertItem(0,label->text());
		label->setText(currentItem->text());
		list->setCurrentRow(0);
		MGlobal::clearSelectionList();
		MGlobal::selectByName(list->currentItem()->text().toStdString().c_str());
	}
	else {
		list->insertItem(index - 1, currentItem);
		list->setCurrentRow(index - 1);

		MGlobal::clearSelectionList();
		MGlobal::selectByName(list->currentItem()->text().toStdString().c_str());
	}
}
MObject UIWindowController::lastChildforDeletion(const MFnDagNode& const dag)
{
	MObject childObj{};
	if (dag.childCount() > 0)
	{
		MFnDagNode childDag{ dag.child(dag.childCount() - 1) };
		childObj = lastChildforDeletion(childDag);
		if (childObj.isNull()) return childDag.object();
	}
	return childObj;
}
void UIWindowController::deleteItemInList(const SELTYPE type)
{
	QPointer<QListWidget> list {};
	QPointer<QLineEdit> label {};
	switch (type)
	{
	case SELTYPE::SOURCE:
		list = Source_List;
		label = Source_Input;
		break;
	case SELTYPE::TARGET:
		list = Target_List;
		label = Target_Input;
		break;
	default:
		MGlobal::displayInfo("Error_type");
		return;
	}
	if (list->count() < 1 && label->text().isEmpty() ||
		list->selectedItems().length() < 1 && label->text().isEmpty()) return;
	QListWidgetItem* currentItem {};
	MObject selObject{};
	MSelectionList selectionList{};
	if (list->count() < 1)
	{
		MGlobal::clearSelectionList();
		MGlobal::selectByName(label->text().toStdString().c_str());
		MGlobal::getActiveSelectionList(selectionList);
		if (selectionList.length() > 0)
		{
			selectionList.getDependNode(0, selObject);
			MFnDagNode currentDag{ selObject };
			MString command{ "delete " + MString(currentDag.name()) };
			MGlobal::executeCommand(command); label->setText("");
		}
	}
	else
	{
		int currentRow { list->currentRow() };
		MGlobal::clearSelectionList();
		MGlobal::selectByName(MString(list->item(currentRow)->text().toStdString().c_str()));
		MGlobal::getActiveSelectionList(selectionList);
		if (selectionList.length() > 0)
		{
			selectionList.getDependNode(0, selObject);
			MFnDagNode currentDag{ selObject };
			MObject lastChildObject {lastChildforDeletion(currentDag)};
			if (lastChildObject.isNull()) 
			{
				MGlobal::displayInfo("Entered 1");
				list->takeItem(currentRow);
			}
			else
			{
				MFnDagNode lastChild {lastChildObject};
				int lastRow {};
				int listIndex{ currentRow+1 };
				while (!lastRow)
					if (list->item(listIndex)->text().toStdString().c_str() == lastChild.name()) {
						lastRow = listIndex;
					}
					else { ++listIndex; };
				MGlobal::displayInfo(QString::number(listIndex).toStdString().c_str());
				MGlobal::displayInfo(QString::number(lastRow).toStdString().c_str());
				for (size_t i = lastRow; i >= currentRow; --i)
				{
					MGlobal::displayInfo(QString::number(i).toStdString().c_str());
					list->takeItem(i);
				}
			}
			MString command{ "delete " + MString(currentDag.name()) };
			MGlobal::executeCommand(command);
		}
	}
}
void UIWindowController::downInList(const SELTYPE type)
{
	QPointer<QListWidget> list {};
	switch (type)
	{
	case SELTYPE::SOURCE:
		list = Source_List;
		break;
	case SELTYPE::TARGET:
		list = Target_List;
		break;
	default:
		MGlobal::displayInfo("Error_type");
		return;
	}
	if (list->count() < 2) return;
	if (list->selectedItems().size() < 1) list->setCurrentRow(0);
	int index = list->currentRow();
	QListWidgetItem* currentItem { list->item(index) };
	if (index == list->count()-1)
	{
		MGlobal::displayInfo("entered 1st");
		list->insertItem(index, currentItem);
		list->setCurrentRow(index);
	}
	else
	{
		MGlobal::displayInfo("entered 2nd");
		
		MGlobal::clearSelectionList();
		MGlobal::selectByName(list->currentItem()->text().toStdString().c_str());
		MSelectionList selList {};
		MGlobal::getActiveSelectionList(selList);
		MObject currentObj {};
		selList.getDependNode(0,currentObj);
		
		bool ok;
		MFnDagNode currentDag{ currentObj };
		QString dialogLabel{ QString("Please select a child (out of ") + QString::number(currentDag.childCount()) + QString("):") };
		QPointer<QInputDialog> idialog {new QInputDialog};
		int value {};
		value = idialog->getInt(thisClass, tr("Select Child"), dialogLabel.toStdString().c_str(), 0, 0, currentDag.childCount(), 1, &ok);
		MGlobal::displayInfo(MString("is OK: ") + MString(QString::number(ok).toStdString().c_str()));
		
		if (value > 0)
		{
			MString command {};
			MFnDagNode parentDag {currentDag.parent(0)};
			MFnDagNode childDag {currentDag.child(value-1)};
			currentItem = list->takeItem(index);
			for (size_t i = index; i < list->count(); ++i)
			{
				MGlobal::displayInfo(MString(QString::number(i).toStdString().c_str()));
				MGlobal::displayInfo(MString("Item name: ") + MString(list->item(i)->text().toStdString().c_str()));
				MGlobal::displayInfo(MString("childDag name: ") + MString(childDag.name().asChar()));
				if (list->item(i)->text().toStdString() == childDag.name().asChar())
				{
					MGlobal::displayInfo("MATCH!");
					list->insertItem(i+1, currentItem);
					list->setCurrentRow(i+1);
				}
			}
			for (size_t i = 0; i < currentDag.childCount(); ++i)
			{
				MFnDagNode tempChild {currentDag.child(i)};
				command = MString(R"V0G0N(parent )V0G0N") + tempChild.name() + MString(" ") + parentDag.name();
				MGlobal::executeCommand(command);
			}
			for (size_t i = 0; i < childDag.childCount(); ++i)
			{
				MFnDagNode grandChildDag {childDag.child(i)};
				command = MString(R"V0G0N(parent )V0G0N") + grandChildDag.name() + MString(" ") + currentDag.name();
				MGlobal::executeCommand(command);
			}
			command = MString(R"V0G0N(parent )V0G0N") + currentDag.name() + MString(" ") + childDag.name();
			MGlobal::executeCommand(command);
		}
		delete idialog;
	}
}

std::unique_ptr<MPlugArray> UIWindowController::getJointAttributePlugs(const MObject& const obj) {
	const MFnDependencyNode node{ obj };
	std::unique_ptr<MPlugArray> plugs{new MPlugArray};
	if (retainRootPos &&
		(Source_Input->text().toStdString().c_str() != node.name() ||
			Target_Input->text().toStdString().c_str() != node.name()))
	{
		return plugs;
	}

	//	119 translate				132 shear						144 scalePivot					156 transMinusRotatePivot 
	//	120 translateX				133 shearXY						145 scalePivotX					157 transMinusRotatePivotX
	//	121 translateY				134 shearXZ						146 scalePivotY					158 transMinusRotatePivotY
	//	122 translateZ				135 shearYZ						147 scalePivotZ					159 transMinusRotatePivotZ
	//	123 rotate					136 rotatePivot 				148 scalePivotTranslate 		160 minTransLimit 
	//	124 rotateX					137 rotatePivotX				149 scalePivotTranslateX		161 minTransXLimit
	//	125 rotateY					138 rotatePivotY				150 scalePivotTranslateY		162 minTransYLimit
	//	126 rotateZ					139 rotatePivotZ				151 scalePivotTranslateZ		163 minTransZLimit
	//	127 rotateOrder				140 rotatePivotTranslate 		152 rotateAxis 					164 maxTransLimit 
	//	128 scale					141 rotatePivotTranslateX		153 rotateAxisX					165 maxTransXLimit
	//	129 scaleX					142 rotatePivotTranslateY		154 rotateAxisY					166 maxTransYLimit
	//	130 scaleY					143 rotatePivotTranslateZ		155 rotateAxisZ					167 maxTransZLimit
	//	131 scaleZ

	//	168 minTransLimitEnable		180 maxRotLimit					192 minScaleLimit				204 maxScaleLimitEnable 
	//	169 minTransXLimitEnable	181 maxRotXLimit				193 minScaleXLimit				205 maxScaleXLimitEnable
	//	170 minTransYLimitEnable	182 maxRotYLimit				194 minScaleYLimit				206 maxScaleYLimitEnable
	//	171 minTransZLimitEnable	183 maxRotZLimit				195 minScaleZLimit				207 maxScaleZLimitEnable
	//	172 maxTransLimitEnable 	184 minRotLimitEnable 			196 maxScaleLimit 
	//	173 maxTransXLimitEnable	185 minRotXLimitEnable			197 maxScaleXLimit
	//	174 maxTransYLimitEnable	186 minRotYLimitEnable			198 maxScaleYLimit
	//	175 maxTransZLimitEnable	187 minRotZLimitEnable			199 maxScaleZLimit
	//	176 minRotLimit 			188 maxRotLimitEnable 			200 minScaleLimitEnable 
	//	177 minRotXLimit			189 maxRotXLimitEnable			201 minScaleXLimitEnable
	//	178 minRotYLimit			190 maxRotYLimitEnable			202 minScaleYLimitEnable
	//	179 minRotZLimit			191 maxRotZLimitEnable			203 minScaleZLimitEnable
	
	MPlug visibility {obj, node.attribute(50)};
	plugs->append(visibility);
	for (size_t i = 119; i <= 207; ++i)
	{
		MPlug plug{ obj, node.attribute(i) };
		plugs->append(plug);
	}

	//	234 jointOrient					247 preferredAngle				259 maxRotateDampRange
	//	235 jointOrientX				248 preferredAngleX				260 maxRotateDampRangeX
	//	236 jointOrientY				249 preferredAngleY				261 maxRotateDampRangeY
	//	237 jointOrientZ				250 preferredAngleZ				262 maxRotateDampRangeZ
	//	238 segmentScaleCompensate		251 minRotateDampRange			263 maxRotateDampStrength
	//	239 inverseScale				252 minRotateDampRangeX			264 maxRotateDampStrengthX
	//	240 inverseScaleX				253 minRotateDampRangeY			265 maxRotateDampStrengthY
	//	241 inverseScaleY				254 minRotateDampRangeZ			266 maxRotateDampStrengthZ
	//	242 inverseScaleZ				255 minRotateDampStrength		
	//	243 stiffness					256 minRotateDampStrengthX		304 radius
	//	244 stiffnessX					257 minRotateDampStrengthY
	//	245 stiffnessY					258 minRotateDampStrengthZ
	//	246 stiffnessZ

	for (size_t i = 234; i <= 266; ++i)
	{
		MPlug plug{ obj, node.attribute(i) };
		plugs->append(plug);
	}
	MPlug radius{ obj, node.attribute(304) };
	plugs->append(radius);

	return plugs;
}
std::unique_ptr<MPlugArray> UIWindowController::getMatrixAttributePlugs(const MObject& const obj)
{
	const MFnDependencyNode node{ obj };
	std::unique_ptr<MPlugArray> plugs{new MPlugArray};
	if (retainRootPos &&
		(Source_Input->text().toStdString().c_str() == node.name() ||
			Target_Input->text().toStdString().c_str() == node.name()))
	{
		return plugs;
	}

	//44 matrix
	//45 inverseMatrix
	//46 worldMatrix
	//47 worldInverseMatrix
	//48 parentMatrix
	//49 parentInverseMatrix

	for (size_t i = 44; i <= 49; ++i)
	{
		MPlug plug {obj, node.attribute(i)};
		plugs->append(plug);
	}
	return plugs;
}
std::unique_ptr<MPlugArray> UIWindowController::getBindAttributePlugs(const MObject& const obj)
{
	const MFnDependencyNode node{ obj };
	std::unique_ptr<MPlugArray> plugs{new MPlugArray};
	if (retainRootPos &&
		(Source_Input->text().toStdString().c_str() == node.name() ||
			Target_Input->text().toStdString().c_str() == node.name()))
	{
		return plugs;
	}

	//  267 bindPose				276 bindRotateAxis		284 bindInverseScale
	//  268 bindRotation			277 bindRotateAxisX		285 bindInverseScaleX
	//  269 bindRotationX			278 bindRotateAxisY		286 bindInverseScaleY
	//  270 bindRotationY			279 bindRotateAxisZ		287 bindInverseScaleZ
	//  271 bindRotationZ			280 bindScale			288 bindSegmentScaleCompensate
	//  272 bindJointOrient			281 bindScaleX								
	//  273 bindJointOrientX		282 bindScaleY								
	//  274 bindJointOrientY		283 bindScaleZ				
	//  275 bindJointOrientZ							
	
	
	MString debug {};
	for (size_t i = 267; i <= 288; ++i)
	{
		MPlug plug {obj, node.attribute(i)};
		plugs->append(plug);
	}
	return plugs;
}
//MStatus UIWindowController::setMatrix(MPlug& targetPlug, MPlug& sourcePlug)
//{
//	MStatus res {};
//	MGlobal::displayInfo(QString::number(sourcePlug.isNull()).toStdString().c_str());
//	MGlobal::displayInfo(sourcePlug.asMObject().apiTypeStr());
//	MGlobal::displayInfo("1");
//	MDataHandle targetDH{};
//	MGlobal::displayInfo("2");
//	MDataHandle sourceDH{};
//	MGlobal::displayInfo("3");
//	sourcePlug.getValue(sourceDH);
//	MGlobal::displayInfo("4");
//	MMatrix mat{ sourceDH.asMatrix() };
//	MGlobal::displayInfo("5");
//	
//	//targetDH.setMMatrix(mat);
//	//MGlobal::displayInfo("6");
//	//targetPlug.setValue(targetDH);
//	//MGlobal::displayInfo("7");
//	return MStatus::kSuccess;
//}
MStatus UIWindowController::setKeyframes(MPlug& const targetPlug, const MPlug& const sourcePlug)
{
	MStatus res {MStatus::kFailure};
	MFnAnimCurve targetAnimCurve{ targetPlug };
	MFnAnimCurve sourceAnimCurve{ sourcePlug };
	if (sourceAnimCurve.object().apiType() != MFn::kInvalid)
	{
		res = MStatus::kSuccess;
		if (targetAnimCurve.object().apiType() == MFn::kInvalid) targetAnimCurve.create(targetPlug);

		UINT tNumKeys{ targetAnimCurve.numKeys() };
		UINT sNumKeys{ sourceAnimCurve.numKeys() };
		
		if (MAnimUtil::isAnimated(targetPlug))
		{
			for (size_t i = 1; i < tNumKeys; ++i)
			{
				res = targetAnimCurve.remove(i);
			}
		}
		for (size_t i = 0; i < sNumKeys; ++i)
		{
			MTime time{ sourceAnimCurve.time(i) };
			double sourceValue{ sourceAnimCurve.value(i) };
			targetAnimCurve.addKeyframe(time, sourceValue);
		}
	}
	return res;
}
//MStatus UIWindowController::bindMatrixTransfer(MPlugArray& targetPlugs, MPlugArray& sourcePlugs) {
//	MGlobal::displayInfo(MString(QString::number(sourcePlugs.length()).toStdString().c_str()));
//	setMatrix(targetPlugs[0], sourcePlugs[0]);
//	//for (size_t i = 1; i < sourcePlugs.length(); ++i)
//	//{
//	//	setKeyframes(targetPlugs[i], sourcePlugs[i]);
//	//}
//	return MStatus::kSuccess;
//}
//MStatus UIWindowController::matrixTransfer(const MPlugArray& const targetPlugs, const MPlugArray& const sourcePlugs) {
//	for (size_t i = 0; i < sourcePlugs.length(); ++i)
//	{
//		MDataHandle targetDH {targetPlugs[i].asMDataHandle()};
//		MDataHandle sourceDH {sourcePlugs[i].asMDataHandle()};
//		MMatrix mat {sourceDH.asMatrix()};
//		targetDH.setMMatrix(mat);
//	}
//	return MStatus::kSuccess;
//}
//MStatus UIWindowController::plugTransfer(const MPlugArray& const targetPlugs, const MPlugArray& const sourcePlugs)
//{
//	MStatus res{};
//	for (size_t i = 0; i < sourcePlugs.length(); ++i)
//	{
//		setKeyframes(targetPlugs[i], sourcePlugs[i]);
//	}
//	return MStatus::kSuccess;
//}

MStatus UIWindowController::transferPlugArray(MArrayDataHandle& const targetArrayHandle, MArrayDataHandle& const sourceArrayHandle) {
	MStatus res {};
	MGlobal::displayInfo(QString::number(targetArrayHandle.elementCount()).toStdString().c_str());
	MGlobal::displayInfo(QString::number(sourceArrayHandle.elementCount()).toStdString().c_str());
	for (size_t i = 0; i < sourceArrayHandle.elementCount(); ++i)
	{
		targetArrayHandle.jumpToArrayElement(i);
		sourceArrayHandle.jumpToArrayElement(i);
		MDataHandle targetDH {targetArrayHandle.outputValue(&res)};
		MDataHandle sourceDH {sourceArrayHandle.outputValue(&res)};
		if (sourceDH.data().apiType() == MFn::kMatrixData)
		{
			//MFnMatrixData targetData {targetDH.data()};
			MFnMatrixData sourceData {sourceDH.data()};
			MMatrix sourceMatrix {sourceMatrix.identity};
			MMatrix targetMatrix {targetDH.asMatrix()};
			sourceMatrix = sourceData.matrix();
			targetMatrix = sourceMatrix;
			//*targetMatrix = sourceMatrix;
			//targetData.set(mat);
			//targetDH.setMMatrix(mat);
			
		}
	}

	return MStatus::kSuccess;
}
MStatus UIWindowController::transferMatrix(MPlug& const targetPlug, const MPlug& const sourcePlug)
{
	MString debug {};
	MObject targetMatObj{};
	MObject sourceMatObj {};
	targetPlug.getValue(targetMatObj);
	sourcePlug.getValue(sourceMatObj);
	MFnMatrixData targetData {targetMatObj};
	MFnMatrixData sourceData {sourceMatObj};
	MMatrix mat {mat.identity};
	mat = sourceData.matrix();
	targetData.set(mat);
	targetPlug.setValue(targetMatObj);
	return MStatus::kSuccess;
}
MStatus UIWindowController::transferDouble3(MPlug& const targetPlug, const MPlug& const sourcePlug) {
	MGlobal::displayInfo(targetPlug.name());
	MGlobal::displayInfo(sourcePlug.name());
	
	MDataHandle targetDH {targetPlug.asMDataHandle()};
	MDataHandle sourceDH {sourcePlug.asMDataHandle()};
	double3& arr {sourceDH.asDouble3()};
	targetDH.set3Double(arr[0], arr[1], arr[2]);
	targetPlug.setMDataHandle(targetDH);
	return MStatus::kSuccess;
}
MStatus UIWindowController::transferPlugs(MPlugArray& const targetPlugs, MPlugArray& const sourcePlugs) {
	
	for (size_t i = 0; i < sourcePlugs.length(); ++i)
	{
		//MGlobal::viewFrame(MAnimControl::minTime());
		//MGlobal::displayInfo(sourcePlugs[i].name());
		//MGlobal::displayInfo(sourcePlugs[i].asMObject().apiTypeStr());
		//MGlobal::displayInfo(sourcePlugs[i].attribute().apiTypeStr());
		switch (sourcePlugs[i].attribute().apiType()) 
		{
		case MFn::kAttribute3Double:
			if (sourcePlugs[i].asMObject().apiType() == MFn::kData3Double)
			{
				// This isn't really necessary since kDoubleLinearAttribute accesses these
				// 3 values individually and sets the value every keyframe.
				transferDouble3(targetPlugs[i], sourcePlugs[i]);
			}
			break;
		case MFn::kTypedAttribute:
			if (sourcePlugs[i].asMObject().apiType() == MFn::kMatrixData)
			{
				transferMatrix(targetPlugs[i], sourcePlugs[i]);
			}
			else if (sourcePlugs[i].isArray())
			{
				//DATA HANDLE
				targetPlugs[i].setNumElements(sourcePlugs[i].numElements());
				UINT numElements {sourcePlugs[i].numElements()};
				MArrayDataHandle targetHandle {targetPlugs[i].asMDataHandle()};
				MArrayDataHandle sourceHandle {sourcePlugs[i].asMDataHandle()};
				transferPlugArray(targetHandle, sourceHandle);
			
				////PLUG
				//for (size_t j = 0; j < sourcePlugs[i].numElements(); ++j)
				//{
				//	if (sourcePlugs[i].elementByLogicalIndex(j).asMObject().apiType() == MFn::kMatrixData)
				//	{	
				//		MPlug tChildPlug {targetPlugs[i].elementByLogicalIndex(j)};
				//		MPlug sChildPlug {sourcePlugs[i].elementByLogicalIndex(j)};
				//		transferMatrix(tChildPlug, sChildPlug);
				//	}
				//
				//	// TODO: See if there's any more attributes for kTypedAttribute that isn't Matrices.
				//}
			}
			break;
		case MFn::kDoubleLinearAttribute:
		case MFn::kDoubleAngleAttribute:
		case MFn::kEnumAttribute:
		case MFn::kNumericAttribute:
			setKeyframes(targetPlugs[i], sourcePlugs[i]);
			break;
		}
	}
	return MStatus::kSuccess;
}

MStatus UIWindowController::jointTransfer(const MObject& const targetObject, const MObject& const sourceObject) {
	MStatus res {};
	// TODO: - Clean this part more gracefully. carefull about scope.
	//		 - Add Skin Binding
	//// BindPose
	std::unique_ptr<MPlugArray> targetPlugs {getBindAttributePlugs(targetObject)};
	std::unique_ptr<MPlugArray> sourcePlugs {getBindAttributePlugs(sourceObject)};
	res = transferPlugs(*targetPlugs.get(), *sourcePlugs.get());
	if (MFAIL(res)) return res;
	////// <---- Skin
	////// <---- delete plug ptrs

	targetPlugs.reset();
	sourcePlugs.reset();
	targetPlugs = getMatrixAttributePlugs(targetObject);
	sourcePlugs = getMatrixAttributePlugs(sourceObject);
	res = transferPlugs(*targetPlugs.get(), *sourcePlugs.get());
	if (MFAIL(res)) return res;

	targetPlugs.reset();
	sourcePlugs.reset();
	targetPlugs = getJointAttributePlugs(targetObject);
	sourcePlugs = getJointAttributePlugs(sourceObject);
	res = transferPlugs(*targetPlugs.get(), *sourcePlugs.get());
	if (MFAIL(res)) return res;
	return MStatus::kSuccess;
}
void UIWindowController::transferAnimation() {
	if (!(!Target_Input->text().isEmpty() && !Source_Input->text().isEmpty())) {
		MGlobal::displayInfo("No joints selected for transfer!");
		return;
	}
	MGlobal::clearSelectionList();
	if (!MGlobal::selectByName(Target_Input->text().toStdString().c_str())) {
		MGlobal::displayInfo("Error: Unable to fetch target joint. Non existant?");
		return;
	}
	if (!MGlobal::selectByName(Source_Input->text().toStdString().c_str())) {
		MGlobal::displayInfo("Error: Unable to fetch source joint. Non existant?");
		return;
	}

	MSelectionList selection{};
	MGlobal::getActiveSelectionList(selection);
	MObject targetObject{};
	MObject sourceObject{};
	selection.getDependNode(0, targetObject);
	selection.getDependNode(1, sourceObject);
	jointTransfer(targetObject, sourceObject);
	
	UINT listCount {};
	if (Target_List->count() < Source_List->count()) listCount = Target_List->count();
	else listCount = Source_List->count();
	MGlobal::displayInfo(QString::number(listCount).toStdString().c_str());
	for (size_t i = 0; i < listCount; ++i)
	{
		MGlobal::displayInfo(QString::number(i).toStdString().c_str());
		Target_List->setCurrentRow(i);
		Source_List->setCurrentRow(i);
		MGlobal::clearSelectionList();
		if (!MGlobal::selectByName(Target_List->currentItem()->text().toStdString().c_str())) {
			MGlobal::displayInfo("Error: Unable to fetch target joint. Non existant?");
			return;
		}
		if (!MGlobal::selectByName(Source_List->currentItem()->text().toStdString().c_str())) {
			MGlobal::displayInfo("Error: Unable to fetch source joint. Non existant?");
			return;
		}
		MGlobal::getActiveSelectionList(selection);
		MObject targetChildObject {};
		MObject sourceChildObject {};
		selection.getDependNode(0, targetChildObject);
		selection.getDependNode(1, sourceChildObject);
		jointTransfer(targetChildObject, sourceChildObject);
	}


	//MFnDependencyNode targetNode {targetObject};
	//for (size_t i = 0; i < targetNode.attributeCount(); ++i)
	//{
	//	MFnAttribute attr {targetNode.attribute(i)};
	//	MGlobal::displayInfo(MString(QString::number(i).toStdString().c_str()) + MString(" ") + attr.name());
	//}
}

void UIWindowController::targetFromCheck()
{
	Target_From_Sel = Target_Check_Box->isChecked();
}
void UIWindowController::sourceFromCheck()
{
	Source_From_Sel = Source_Check_Box->isChecked();
}
void UIWindowController::selectTarget()
{
	selection(SELTYPE::TARGET);
}
void UIWindowController::selectSource()
{
	selection(SELTYPE::SOURCE);
}
void UIWindowController::upTargetList() {
	upInList(SELTYPE::TARGET);
}
void UIWindowController::deleteTargetListItem() {
	deleteItemInList(SELTYPE::TARGET);
}
void UIWindowController::downTargetList() {
	downInList(SELTYPE::TARGET);
}
void UIWindowController::upSourceList() {
	upInList(SELTYPE::SOURCE);
}
void UIWindowController::deleteSourceListItem() {
	deleteItemInList(SELTYPE::SOURCE);
}
void UIWindowController::downSourceList() {
	downInList(SELTYPE::SOURCE);
}