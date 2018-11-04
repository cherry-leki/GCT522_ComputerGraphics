* Source code (.sln/ .cpp / .h / .vcproj)
"BlendShape"
- .cpp / .h / .vcproj: HW4_BlendShape_20183151_ChaelinKim\code\BlendShape
- .sln /		: HW4_BlendShape_20183151_ChaelinKim\code

* Compiled binary file (.mll)
- BlendShape.mll	: HW4_BlendShape_20183151_ChaelinKim\code

* Target Machine & Software
: Maya 2017, Visual Studio 2017, x64

* How to use commands
1. Open the "HW4_blendshape.mb" scene file.
2. Register the plugin "BlendShape.mll" file in Maya.
   (Windows -> Settings/Preferences -> Plug-in Manager)
  2-1. Check if the plugin is correctly registered.
        - Commands: doBlendShape
        - Dependency nodes: clDeformer
3. Select the target mesh "tgt_neutral" and execute the MEL command "deformer -type clDeformer".
   : This commend is to make a deformer node that connects source meshes and target mesh for creating facial expression. Each source mesh is applyed as per weight value.
  3-1. When this command is executed, the "initialize" function in blendshapeNode is called.
        In this function, the attributes for source meshes and corresponding weights are initialized.
        (The "deform" function in blendshapeNode is also called. But there are no selection for source meshes, so values are not allocated yet)
4. If the command is executed correctly, you can see the "clDeformer1" is made and that node has two attributes.
   - Blend Mesh: The source meshs used to make facial expression of target mesh. It is called "blend shape".
   - Blend Weight: The weight values affecting how much the facial expression of the source mesh is reflected to the target mesh
		Each weight is one to one mapping to the source mesh in Blend Mesh. (0.0 ~ 1.0)
5. Select source meshes and generated deformer "clDeformer1"
6. Execute the MEL command "doBlendShape".
   : This command is to allocate connect source outMesh to each blend mesh attributes of the deformer node and initialize corresponding weights to each blend weight attributes of the deformer node.
  6-1. If this command is executed, it gets plugs to access the attributes of the deformer node.
  6-2. By iterating over all selected source meshes, it gets "outMesh" of each source mesh.
        Then it makes a connection from the plug of each source outMesh to the plug of the corresponding attribute of the deformer.
        This process set the "Blend Mesh" attributes to the deformer.
  6-3. All values of "Blend Weight" attributes are initialized as 0.0f.
  6-4. The "deform" function in blendshapeNode is called when the attributes are updated.
        In this function, the points of each source meshs are calculated from the blendshape(source mesh). Then the facial expression is made by calculating the target mesh's points with points of source meshes and corresponding weights.
        By iterating as the number of source meshs, get the source meshes and weights from each attributes and put them into the each two vectors:
	- arrayBlendPoints: the vertex points of the source meshes
	- arrayWeights: the corresponding weights of source meshes
7. If the command is executed correctly, you can see the outMesh of source meshes are registered in the form of "Blend Mesh" attributes and the corresponding "Blend Weight" attributes are generated in the clDeformer1.
8. See the target mesh's facial expression is changed by changing values of "Blend Weight" attributes in the clDeformer1.
  8-1. If the values of "Blend Weight" attributes are changed, the "deform" function in blendshapeNode is called.
  8-2. By iterating over registered source meshes, compute the facial expression of target mesh using the blendshape equation
        : New face = neutral face + ¢² (deformed face - neutral face) * weight