#ifndef SMARTMODELING_KCL_H
#define SMARTMODELING_KCL_H

#include <maya/MPxCommand.h>
#include <maya/MSyntax.h>

#include <maya/MObjectArray.h>
#include <maya/MSelectionList.h>
#include <maya/MStringArray.h>
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
	MObjectArray instanceArray;		// for Undo/Redo
	MSelectionList selectPlane;		// Plane selection
	MSelectionList selectObjects;	// objects selection
	MStringArray objectArr;

	int height;

	MDGModifier dgMod;
};
#endif // !SMARTMODELING_KCL_H
