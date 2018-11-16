#ifndef _toonShaderOverride
#define _toonShaderOverride

#include <maya/MPxSurfaceShadingNodeOverride.h>

class toonShaderOverride : public MHWRender::MPxSurfaceShadingNodeOverride {
public:
	static MHWRender::MPxSurfaceShadingNodeOverride* creator(const MObject& obj);

	virtual ~toonShaderOverride();

	virtual MHWRender::DrawAPI supportedDrawAPIs() const;

	virtual MString fragmentName() const;
	virtual void getCustomMappings(
		MHWRender::MAttributeParameterMappingList& mappings);

	virtual MString primaryColorParameter() const;
	virtual MString bumpAttribute() const;

	virtual void updateDG();
	virtual void updateShader(
		MHWRender::MShaderInstance& shader,
		const MHWRender::MAttributeParameterMappingList& mappings);

private:
	toonShaderOverride(const MObject &obj);

	MObject fObject;
	float fSpecularColor[3];
	mutable MString fResolvedSpecularColorName;
};

#endif	//_toonShaderOverride