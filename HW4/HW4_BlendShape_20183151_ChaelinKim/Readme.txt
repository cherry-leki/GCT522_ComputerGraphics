* Source code (.sln/ .cpp / .h / .vcproj)
"BlendShape"
- .cpp / .h / .vcproj: HW4_BlendShape_20183151_ChaelinKim\code\BlendShape
- .sln /		: HW4_BlendShape_20183151_ChaelinKim\code

* Compiled binary file (.mll)
- BlendShape.mll	: HW4_BlendShape_20183151_ChaelinKim\code

* Target Machine & Software
: Maya 2017, Visual Studio 2017, x64

* How to use command
1. Open the "HW4_blendshape.mb" scene file.
2. Register the plugin "BlendShape.mll" file in Maya.
   (Windows -> Settings/Preferences -> Plug-in Manager)
  2-1. Check if the plugin is correctly registered.
        - Commands: doBlendShape
        - Dependency nodes: clDeformer
3. Select the target mesh "tgt_neutral" and execute the MEL command "deformer -type clDeformer".
   If the command is executed correctly, you can see the "clDeformer1" is made and that node has two attributes.
	- Blend Mesh: 
	- Blend Weight: (0.0 ~ 1.0)
4. Select source meshes and created deformer "clDeformer1"
5. Execute the MEL command "doBlendShape".
   If the command is executed correctly, you can see source meshes are registered in the form of "Blend Mesh" attributes and the corresponding "Blend Weight" attributes are generated.
6. See the target mesh's facial expression is changed by changing values of "Blend Weight" attributes.