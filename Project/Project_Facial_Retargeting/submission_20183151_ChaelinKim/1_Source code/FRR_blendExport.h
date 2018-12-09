#ifndef _FRRBLENDEXPORTCmd
#define _FRRBLENDEXPORTCmd

#include "global.h"
#include <iostream>
#include <maya/MFnBlendShapeDeformer.h>
#include <maya/MFnAnimCurve.h>

class FRRBLENDEXPORTCmd : public MPxCommand
{
public:
	virtual MStatus	doIt(const MArgList&);
	virtual MStatus undoIt();
	virtual MStatus redoIt();
	virtual bool isUndoable() const { return true; }

	static void *creator() { return new FRRBLENDEXPORTCmd; }
	static MSyntax newSyntax();

private:
	MDGModifier dgMod;
};

#endif