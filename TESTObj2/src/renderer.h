// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxGui.h"
#include "primitive.h"

class Renderer
{

public:

	EnumObject DefObj;
	StructObjectLocator * shape;
	ofVec3f * vectorOrigin;

	ofVec3f * vectorPosition1;
	ofVec3f * vectorPosition2;
	ofVec3f * vectorPosition3;
	
	ofColor * vectorColor;
	
	ofxAssimpModelLoader * Model3D1;
	ofxAssimpModelLoader * Model3D2;
	ofLight * light;

	ofNode * node;

	//GUI
	ofParameterGroup groupAmbiant, groupModele3D, groupModele3D2, groupdessinVectoriel;
	ofxPanel gui;
	ofxButton exportButton;
	ofxButton clearButton;

	bool ShowGui; 
	ofParameter<float> LAMBx, LAMBy, LAMBz, MD3ScaleX, MD3ScaleY, MD3ScaleZ, MD3Scale, MD3PosX, MD3PosZ, MD3PosY;
	ofParameter<int> MD3Red, MD3Green, MD3Blue, MD3Apha, MD3RotX, MD3RotY, MD3RotZ;

	ofParameter<float>MD3ScaleX2, MD3ScaleY2, MD3ScaleZ2, MD3Scale2, MD3PosX2, MD3PosZ2, MD3PosY2;
	ofParameter<int> MD3Red2, MD3Green2, MD3Blue2 ,MD3Apha2, MD3RotX2, MD3RotY2, MD3RotZ2;

	ofParameter<int> red, LAMB_R, LAMB_G, LAMB_B;
	ofParameter<int> green;
	ofParameter<int> blue;
	ofParameter<int> alpha;
	ofParameter<int> radius;
	ofParameter<bool> shapeAreFilled, pixelButton, pointButton, lineButton, rectangleButton, ellipseButton, zoneButton;


	float xCenter;
	float yCenter;

	float speed;

	float xOffset, xOffset2;
	float yOffset;
	float zOffset;
	float zOffset2;

	float xDelta, xDelta2;
	float yDelta,  yDelta2;
	float zDelta, zDelta2;

	float soupRadius;

	float triangleRadius;

	int triangleCount;

	int triangleBufferSize;
	int triangleBufferHead;

	int index, count, stride,size;

	int framebufferWidth;
	int framebufferHeight;

	bool isFlipAxisY;

	bool isActiveTranslation;
	bool isActiveRotation;
	bool isActiveDimension;
	bool isVerbose;

	Renderer();
	~Renderer();

	void setup();
	void draw();
	void reset();


	void drawScene();
	void drawLocator(float scale);
	void drawModel();


	void imageExport(const string name, const string extension) const;
	

private:
	void assignFunctionsToButtons();
	void setupGui();
};
