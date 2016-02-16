// Classe principale de l'application.

#include "ofApp.h"

ofApp::ofApp()
{
	isKeyPressUp = false;
	isKeyPressDown = false;
	isKeyPressLeft = false;
	isKeyPressRight = false;
	isKeyPressZ = false;
	isKeyPressX = false;
	isKeyPressC = false;
	isKeyPressV = false;
	isKeyPressM = false;
	ShowMenu = true;
	renderer = nullptr;
}

void ofApp::setup()
{
	ofLog() << "<ofApp::setup>";

	ofSetWindowTitle("Test obj file  et menu (keys: arrows, z, x, (m)enu");

	renderer = new Renderer();
	renderer->setup();

	isVerbose = false;
}

void ofApp::update()
{
	timeCurrent = ofGetElapsedTimef();
	timeElapsed = timeCurrent - timeLast;
	timeLast = timeCurrent;

	// déplacement sur le plan XZ en fonction de l'état des flèches du clavier
	if (isKeyPressUp)
		renderer->zOffset += renderer->zDelta * timeElapsed;
	if (isKeyPressDown)
		renderer->zOffset -= renderer->zDelta * timeElapsed;
	if (isKeyPressLeft)
		renderer->xOffset += renderer->xDelta * timeElapsed;
	if (isKeyPressRight)
		renderer->xOffset -= renderer->xDelta * timeElapsed;

	// rotation en Y en fonction de l'état des touches Z et X
	if (isKeyPressZ)
		renderer->yOffset += renderer->yDelta * timeElapsed;
	if (isKeyPressX)
		renderer->yOffset -= renderer->yDelta * timeElapsed;

	// rotation en z en fonction de l'état des touches C et V
	if (isKeyPressC)
		renderer->zOffset2 += renderer->zDelta2 * timeElapsed;
	if (isKeyPressV)
		renderer->zOffset2 -= renderer->zDelta2 * timeElapsed;

	// rotation en x en fonction de l'état des touches w et s
	if (isKeyPressW)
		renderer->xOffset2 += renderer->xDelta2 * timeElapsed ;
	if (isKeyPressS)
		renderer->xOffset2 -= renderer->xDelta2 * timeElapsed ;

}

void ofApp::draw()
{
	renderer->draw();
}

void ofApp::mouseReleased(int x, int y, int button)
{
	// réinitialiser la scène
	renderer->reset();

	if (isVerbose)
		ofLog() << "<ofApp::mouse release at: (" << x << ", " << y << ")>";
}

void ofApp::keyPressed(int key)
{
	switch (key)
	{
	case 119: // key w
		isKeyPressW = true;
		break;
	case 115: // key s
		isKeyPressS = true;
		break;
	case 120: // X
		isKeyPressX = true;
		break;
	case 122: // Z
		isKeyPressZ = true;
		break;
	case 356: // key left
		isKeyPressLeft = true;
		break;
	case 357: // key up
		isKeyPressUp = true;
		break;
	case 358: // key right
		isKeyPressRight = true;
		break;
	case 359: // key down
		isKeyPressDown = true;
		break;
	case 99: // key c
		isKeyPressC = true;
		break;
	case 118: // key v
		isKeyPressV = true;
		break;

	case 109: // key M
		isKeyPressM = true;
		break;
	default:
		break;
	}
}

void ofApp::keyReleased(int key)
{
	switch (key)
	{
	case 119: // key w
		isKeyPressW = false;
		break;
	case 115: // key s
		isKeyPressS = false;
		break;
	case 120: // X
		isKeyPressX = false;
		break;
	case 122: // Z
		isKeyPressZ = false;
		break;
	case 356: // key left
		isKeyPressLeft = false;
		break;
	case 357: // key up
		isKeyPressUp = false;
		break;
	case 358: // key right
		isKeyPressRight = false;
		break;
	case 359: // key down
		isKeyPressDown = false;
		break;
	case ' ': // space
		renderer->imageExport("render", "png");
		break;
	case 99: // key c
		isKeyPressC = false;
		break;
	case 118: // key v
		isKeyPressV = false;
		break;

	case 109: // key M
		isKeyPressM = false;
		if (ShowMenu) {
			ShowMenu = false;
		}	
		else {
			ShowMenu = true;
		}
		renderer->ShowGui= ShowMenu;
		break;

	default:
		// réinitialiser la scène
		renderer->reset();
		break;
	}
}

void ofApp::exit()
{
	ofLog() << "<ofApp::exit>";
}

ofApp::~ofApp()
{
	if (nullptr != renderer)
		delete renderer;
}
