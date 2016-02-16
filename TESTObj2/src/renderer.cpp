// Classe responsable du rendu de l'application.

#include "renderer.h"

Renderer::Renderer(){}

void Renderer::setup()
{
	
	// paramètres de rendu
	ofSetFrameRate(60);

	// initialisation des variables
	speed = 100;

	//Param de la luminosite
	ShowGui = true;

	LAMB_R = 255;
	LAMB_G = 255;
	LAMB_B = 255;

	xOffset = 0;
	yOffset = 0;
	zOffset = 0;
	xOffset2 = 0;
	zOffset2 = 0;

	xDelta = speed;
	yDelta = speed;
	xDelta2 = speed;
	yDelta2 = speed;
	zDelta2 = speed;
	zDelta = speed;


	isFlipAxisY = false;

	isActiveTranslation = true;
	isActiveRotation = true;
	isActiveDimension = true;

	isVerbose = true;

	// allocation d'une instance de node pour l'affichage des localisateurs
	node = new ofNode();

	// allocation de vecteurs pour stocker les attributs de transformation
	vectorOrigin     = new ofVec3f(0.0f, 0.0f, 0.0f);
	vectorPosition1  = new ofVec3f(0.0f, 0.0f, 0.0f);
	vectorPosition2  = new ofVec3f(0.0f, 0.0f, 0.0f);
	vectorPosition3  = new ofVec3f(0.0f, 0.0f, 0.0f);

	// nombre maximale d<object dans le tableau
	count = 100;

	// calculer la taille de la structure générique commune à toutes les objects
	stride = sizeof(StructObjectLocator);

	// allouer un espace mémoire de taille suffisante pour contenir les données de l'ensemble des primitives vectorielles
	shape = (StructObjectLocator *)calloc(size, stride);

	// chargement du modèle 3D
	Model3D1 = new ofxAssimpModelLoader();
	Model3D1->loadModel("baby.obj");
	
	Model3D2 = new ofxAssimpModelLoader();
	Model3D2->loadModel("cyclops10.obj");
	
	// création d'une lumière
	light = new ofLight();

	// Chargement du GUI
	setupGui();

	// initialisation de la scène
	reset();
}

void Renderer::draw()
{
	ofBackgroundGradient(ofColor(127), ofColor(32));

	// rendre le contenu de la scène
	drawScene();
}

// fonction qui initialise la scène
void Renderer::reset()
{

	ofEnableDepthTest();
	ofEnableLighting();

	// extraire la résolution du framebuffer
	framebufferWidth  = ofGetWidth();
	framebufferHeight = ofGetHeight();

	// calculer les coordonnées du centre du framebuffer
	xCenter = framebufferWidth  / 2.0f;
	yCenter = framebufferHeight / 2.0f;


	// activer la lumière
	light->setAmbientColor(ofColor(LAMB_R, LAMB_G, LAMB_B));
	light->setDiffuseColor(ofColor(255, 255, 255));
	light->enable();
	
	// Chargement du GUI
	//setupGui();
	ofLog() << "<reset>";
}



// fonction fait le rendu des entités géométriques de la scène
void Renderer::drawScene()
{
	

	// configurer la représentation visuelle des localisateurs
	ofFill();
	ofSetLineWidth(2);
	ofSetColor(127);
	
	// positionner la lumière
	ofSetColor(0);
	ofDrawEllipse(LAMBx, LAMBy, LAMBz,5,5);
	light->setPosition(LAMBx, LAMBy, LAMBz);
	light->setAmbientColor(ofColor(LAMB_R, LAMB_G, LAMB_B));

	ofSetColor(255);
	// copier la matrice de transformation courante sur le dessus de la pile

	ofPushMatrix();

	// inverser l'axe Y pour qu'il pointe vers le haut
	ofScale(1, isFlipAxisY ? -1 : 1);

	// transformer l'origine de la scène au milieu de la fenêtre d'affichage
	ofTranslate(xCenter + xOffset, yCenter, zOffset);

	//rotation en Y de la scène
	ofRotate(yOffset, 0, 1, 0);

	//rotation en Z de la scène
	ofRotate(xOffset2, 1, 0, 0);

	//rotation en Z de la scène
	ofRotate(zOffset2, 0, 0, 1);

	ofEnableDepthTest();
	drawModel();

	// revenir à la matrice de transformation précédente dans la pile
	ofPopMatrix();

	ofDisableDepthTest();
	if (ShowGui) gui.draw();

}

// fonction de rendu du model
void Renderer::drawModel()
{
	ofPushMatrix();


	 //rotation en Y de l<objet
	ofRotate(MD3RotY, 0, 1, 0);

	//rotation en Z de la scène
	ofRotate(MD3RotX, 1, 0, 0);
	
	//rotation en Z de la scène
	ofRotate(MD3RotZ, 0, 0, 1);
	
	//Scale sur 3 axe pas int/ressant
	//Model3D1->setScale(MD3ScaleX, MD3ScaleY, MD3ScaleZ);
	
	Model3D1->setScale(MD3Scale, MD3Scale, MD3Scale);

	Model3D1->setPosition(MD3PosX, MD3PosY, MD3PosZ);
	Model3D1->draw(OF_MESH_FILL);
	ofPopMatrix();
	

	ofPushMatrix();
	//rotation en Y de la scène
	ofRotate(MD3RotY2, 0, 1, 0);

	//rotation en Z de la scène
	ofRotate(MD3RotX2, 1, 0, 0);

	//rotation en Z de la scène
	ofRotate(MD3RotZ2, 0, 0, 1);

	//Scale sur 3 axe pas int/ressant
	//Model3D1->setScale(MD3ScaleX, MD3ScaleY, MD3ScaleZ);

	Model3D2->setScale(MD3Scale2, MD3Scale2, MD3Scale2);

	Model3D2->setPosition(MD3PosX2, MD3PosY2, MD3PosZ2);
	Model3D2->draw(OF_MESH_FILL);
	ofPopMatrix();
}


// Fonction qui dessine l'origine de la scène
void Renderer::drawLocator(float scale)
{
	ofFill();
	ofSetColor(192);
	ofPushMatrix();
	ofScale(scale, scale);
	node->setPosition(0, 0, 0);
	node->draw();
	ofPopMatrix();
}

void Renderer::imageExport(const string name, const string extension) const
{
	ofImage imageTemp;

	string timestamp = ofGetTimestampString("-%y%m%d-%H%M%S-%i");

	string fileName = name + timestamp + "." + extension;

	imageTemp.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

	imageTemp.save(fileName);

	ofLog() << "<export image: " << fileName << ">";
}

Renderer::~Renderer()
{
	delete Model3D1;

	delete vectorOrigin;

	delete vectorPosition1;
	delete vectorPosition2;
	delete vectorPosition3;

	//delete vectorColor;
	delete node;
}

void Renderer::assignFunctionsToButtons()
{
	
}

void Renderer::setupGui()
{


	gui.setup();
	gui.setPosition(0, 0);
	
	gui.setTextColor(ofColor(255, 255, 255));
	gui.setBackgroundColor(ofColor(0, 0, 0));
	gui.setDefaultFillColor(ofColor(127, 127, 127));
	gui.setHeaderBackgroundColor(ofColor(255, 0, 0));
	gui.setName("Menu de base 1");
	
	groupAmbiant.setName( "Lumiere ambiante");
	groupAmbiant.add(LAMBx.set("Position en X", 0, 0, ofGetWidth()));
	groupAmbiant.add(LAMBy.set("Position en Y", 0, 0, ofGetHeight()));
	groupAmbiant.add(LAMBz.set("Position en Z", 265, 0, 1000));
	groupAmbiant.add(LAMB_R.set("Rouge", 255, 0, 255));
	groupAmbiant.add(LAMB_G.set("Vert", 0, 0, 255));
	groupAmbiant.add(LAMB_B.set("Bleu",0, 0, 255));

	gui.add(groupAmbiant);

	groupModele3D.setName("Param Modele 3D-1");
	groupModele3D.add(MD3Scale.set("Taille", 0.729592, 0, 1));
	groupModele3D.add(MD3PosX.set("Position X", -385.714, -(ofGetWidth() / 2), ofGetWidth()/2));
	groupModele3D.add(MD3PosY.set("Position Y", -430, -(ofGetHeight() / 2), ofGetHeight()/2));
	groupModele3D.add(MD3PosZ.set("Position Z", 352, -500, 500));
	groupModele3D.add(MD3RotX.set("Rotation en X", 80, -360, 360));
	groupModele3D.add(MD3RotY.set("Rotation en Y",18, -360, 360));
	groupModele3D.add(MD3RotZ.set("Rotation en Z", 80, -360, 360));
	//groupModele3D.add(MD3Apha.set("Apha", 255, 0, 255));

	gui.add(groupModele3D);

	groupModele3D2.setName("Param Modele 3D-2");
	groupModele3D2.add(MD3Scale2.set("Taille", 0.73, 0, 1));
	groupModele3D2.add(MD3PosX2.set("Position X", -141, -(ofGetWidth() / 2), ofGetWidth() / 2));
	groupModele3D2.add(MD3PosY2.set("Position Y", 0, -(ofGetHeight() / 2), ofGetHeight() / 2));
	groupModele3D2.add(MD3PosZ2.set("Position Z", 0, -500, 500));
	groupModele3D2.add(MD3RotX2.set("Rotation en X", 0, -360, 360));
	groupModele3D2.add(MD3RotY2.set("Rotation en Y", 135, -360, 360));
	groupModele3D2.add(MD3RotZ2.set("Rotation en Z", 14, -360, 360));
	//groupModele3D.add(MD3Apha.set("Apha", 255, 0, 255));

	gui.add(groupModele3D2);
	groupdessinVectoriel.setName("Outils dessin vectoriel");
	groupdessinVectoriel.add(red.set("Red", 255, 0, 255));
	groupdessinVectoriel.add(blue.set("Blue", 255, 0, 255));
	groupdessinVectoriel.add(green.set("Green", 255, 0, 255));
	groupdessinVectoriel.add(alpha.set("Alpha", 255, 0, 255));
	groupdessinVectoriel.add(pixelButton.set("Draw Pixel",false));
	groupdessinVectoriel.add(pointButton.set("Draw Point",false));
	groupdessinVectoriel.add(lineButton.set("Draw Line", false));
	groupdessinVectoriel.add(rectangleButton.set("Draw Rectangle", false));
	groupdessinVectoriel.add(ellipseButton.set("Draw Ellipse", false));
	groupdessinVectoriel.add(shapeAreFilled.set("Fill shapes", true));

	gui.add(groupdessinVectoriel);

	gui.add(exportButton.setup("Export Image"));
	gui.add(clearButton.setup("Clear window"));


	
}
