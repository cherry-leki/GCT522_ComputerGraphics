#ifndef _FRRCVIMPORTCmd
#define _FRRCVIMPORTCmd

#include "global.h"
#include <iostream>

class FRRCVIMPORTCmd : public MPxCommand
{
public:
	virtual MStatus	doIt(const MArgList&);
	virtual MStatus undoIt();
	virtual MStatus redoIt();
	virtual bool isUndoable() const { return true; }

	static void *creator() { return new FRRCVIMPORTCmd; }
	static MSyntax newSyntax();

private:
	MDGModifier dgMod;
};

#endif