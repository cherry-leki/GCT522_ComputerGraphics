* Source code (.sln/ .cpp / .h / .vcproj)
- .cpp / .h / .vcproj: HW5_ToonShader_20183151_ChaelinKim\code\toonShader_CL
- .sln /		: HW5_ToonShader_20183151_ChaelinKim\code

* Maya scene file (.mb)
- toonShaderScene.mb	: HW5_ToonShader_20183151_ChaelinKim\scene

* Compiled binary file (.mll)
- toonShader_CL.mll	: HW5_ToonShader_20183151_ChaelinKim\code

* Target Machine & Software
: Maya 2017, Visual Studio 2017, x64

* How to use commands
1. Open the "toonShaderScene.mb" scene file.
2. Register the plugin "toonShader_CL.mll" file in Maya.
   (Windows -> Settings/Preferences -> Plug-in Manager)
  2-1. Check if the plugin is correctly registerd.
	- Dependency nodes: toonNode
3. Open the "Hypershade" window.
4. In "Create" panel, type "Toon Node" and click it.
   Then new material "toonNode" is registered.
   : Toon Node is made by toon shading(cel shading) that is a type of non-photorealistic rendering.
     This implementation is a transformed version of the phong shader and it has two changes.
	- Toon shading: Applying step function to the diffuse color(R, G, B) values.
		         Toon shading is designed to make 3D computer graphics appear to be flat by using less shading color instead of a shade gradient.
		         So, it can be implemented by applying constant colors according to the step.
		         In this code, the step is set to 0.2f, 0.4f, 0.6f, 1.0f(4 Band)
		         To make flat color, specular and incandescence value is deleted in resultColor.
	- Silhouette Edge: Drawing black color at the edge.
			For this in 3D, if the angle between ray direction and surface normal is bigger than 90 deg(or certain threshold), the color value of that point is set to black.
			Using the cosine law and dot product, the angle between normal(surface normal) and refVector(ray direction vector) can be calculated.
			If the result(refVector * normal) is smaller than the threshold, the resultColor value is set to (0, 0, 0) (black)
			In this code, the threshold value is set to 0.3f arbitrarily.
5. Click the "toonNode" material and change the color what you want.
6. Drag the material(with click mouse right button) to an object you want to apply.
7. Click the "Render View" and see the result image
   (Before that, "Render Using" parameter in Render Settings is set to the"Maya Software") 