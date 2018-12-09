#ifndef _FRRCVEXPORTCmd
#define _FRRCVEXPORTCmd

#include "global.h"
#include <iostream>

class FRRCVEXPORTCmd : public MPxCommand
{
public:
	virtual MStatus	doIt(const MArgList&);
	virtual MStatus undoIt();
	virtual MStatus redoIt();
	virtual bool isUndoable() const { return true; }

	static void *creator() { return new FRRCVEXPORTCmd; }
	static MSyntax newSyntax();

private:
	MDGModifier dgMod;
};

#endif