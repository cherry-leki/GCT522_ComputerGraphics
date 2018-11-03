#ifndef BLENDCMD_H
#define BLENDCMD_H

#include <maya/MPxCommand.h>
#include <maya/MDGModifier.h>

class blendshapeCmd : public MPxCommand
{
public:
	virtual MStatus	doIt(const MArgList&);
	virtual MStatus undoIt();
	virtual MStatus redoIt();
	virtual bool	isUndoable() const { return true; }

	static	void	*creator() { return new blendshapeCmd; }
	static  MSyntax newSyntax();

private:
	MDGModifier dgMod;
};

#endif
