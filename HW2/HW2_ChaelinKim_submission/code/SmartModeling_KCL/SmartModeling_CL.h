#ifndef SMARTMODELING_KCL_H
#define SMARTMODELING_KCL_H

#include <maya/MPxCommand.h>
#include <maya/MSyntax.h>

#include <maya/MObjectArray.h>
#include <maya/MSelectionList.h>
#include <maya/MStringArray.h>
#include <maya/MDagPath.h>
#include <maya/MDGModifier.h>

class SmartModeling : public MPxCommand {
public:
	virtual MStatus doIt(const MArgList&);
	virtual MStatus undoIt();
	virtual MStatus redoIt();
	virtual bool isUndoable() const { return true; };

	static void *creator() { return new SmartModeling; }
	static MSyntax newSyntax();

private:
	MObjectArray instanceArray;		// for Undo
	MSelectionList selectPlane;		// Plane selection
	MSelectionList selectObjects;	// objects selection
	MStringArray objectArr;
	MDagPath dagMesh;

	int height;
	int *randomHeightArray;
	int *randomScaleArray;
};
#endif // !SMARTMODELING_KCL_H
