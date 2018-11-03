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
   If the command is executed correctly, you can see the "clDeformer1" is made and that node has two attributes.
   - Blend Mesh: The source meshs used to make facial expression of target mesh. It is called "blend shape".
   - Blend Weight: The weight values affecting how much the facial expression of the source mesh is reflected to the target mesh
		Each weight is one to one mapping to the source mesh in Blend Mesh. (0.0 ~ 1.0)
4. Select source meshes and generated deformer "clDeformer1"
5. Execute the MEL command "doBlendShape".
  5-1. If this command is executed, it gets plugs to access the attributes of the deformer node.
  5-2. By iterating over all selected source meshes, it gets "outMesh" of each source mesh.
        Then it makes a connection from the plug of each source outMesh to the plug of the corresponding attribute of the deformer.
  5-4. All values of "Blend Weight" attributes are initialized as 0.0f.
  5-5. The "deform" function in blendshapeNode is called when the attributes are updated.
        By iterating as the number of source meshs, get the source meshes and weights and put them into the each two vectors:
	- arrayBlendPoints: the vertex points of the source meshes
	- arrayWeights: the corresponding weights of source meshes
  5-6. If the command is executed correctly, you can see the outMesh of source meshes are registered in the form of "Blend Mesh" attributes and the corresponding "Blend Weight" attributes are generated in the clDeformer1.
6. See the target mesh's facial expression is changed by changing values of "Blend Weight" attributes in the clDeformer1.
  6-1. If the values of "Blend Weight" attributes are changed, the "deform" function in blendshapeNode is called.
  6-2. By iterating over registered source meshes, compute the facial expression of target mesh using the blendshape equation
        : New face = neutral face + ¢² (deformed face - neutral face) * weight