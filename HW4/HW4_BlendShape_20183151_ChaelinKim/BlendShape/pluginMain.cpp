#include "blendshapeNode.h"
#include "blendshapeCmd.h"


#include <maya/MFnPlugin.h>

MStatus initializePlugin( MObject obj )
{
    MStatus status;

    MFnPlugin fnPlugin( obj, "GCT522", "1.0", "Any" );

    status = fnPlugin.registerCommand("doBlendShape", blendshapeCmd::creator);

    CHECK_MSTATUS_AND_RETURN_IT( status );

    status = fnPlugin.registerNode( "clDeformer",
									 BlendMesh::id,
									 BlendMesh::creator,
									 BlendMesh::initialize,
									 MPxNode::kDeformerNode );

    CHECK_MSTATUS_AND_RETURN_IT( status );

    return MS::kSuccess;
}


MStatus uninitializePlugin( MObject obj )
{
    MStatus status;

    MFnPlugin fnPlugin( obj );

    status = fnPlugin.deregisterCommand("blendshapeCmd");
    CHECK_MSTATUS_AND_RETURN_IT( status );


    status = fnPlugin.deregisterNode( BlendMesh::id );
    CHECK_MSTATUS_AND_RETURN_IT( status );


    return MS::kSuccess;
}
