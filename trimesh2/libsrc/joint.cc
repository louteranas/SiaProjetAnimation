#include "../include/joint.h"
#include <QtGui/QMatrix4x4>

using namespace std;



Joint* Joint::createFromFile(std::string fileName) {
	Joint* root = NULL;
	cout << "Loading from " << fileName << endl;

	ifstream inputfile(fileName.data());
	if(inputfile.good()) {
		while(!inputfile.eof()) {
			string buf;
			inputfile >> buf;
			// TODO : construire la structure de donn�es root � partir du fichier
		}
		inputfile.close();
	} else {
		std::cerr << "Failed to load the file " << fileName.data() << std::endl;
		fflush(stdout);
	}

	cout << "file loaded" << endl;

	return root;
}

Joint* Joint::create(std::string name, double offX, double offY, double offZ, Joint* parent, int id_liste) {
	Joint* child = new Joint();
	child->_name = name;
	child->_offX = offX;
	child->_offY = offY;
	child->_offZ = offZ;
	child->_curTx = 0;
	child->_curTy = 0;
	child->_curTz = 0;
	child->_curRx = 0;
	child->_curRy = 0;
	child->_curRz = 0;
	child->_rorder = 0;
	child->id_liste = id_liste;
	//Initialisation dofs
	child->_dofs = std::vector<AnimCurve>();
	child->_dofs.push_back(AnimCurve("Xrotation"));
	child->_dofs.push_back(AnimCurve("Yrotation"));
	child->_dofs.push_back(AnimCurve("Zrotation"));
	if (id_liste == 1) { //Si c'est le root
		child->_dofs.push_back(AnimCurve("Xposition"));
		child->_dofs.push_back(AnimCurve("Yposition"));
		child->_dofs.push_back(AnimCurve("Zposition"));
	}
	if(parent != NULL) {
		parent->_children.push_back(child);
	}
	return child;
}

void Joint::animate(int iframe)
{
	// Update dofs :
	if(_children.size() == 0)
		return;
	//std::cerr << _dofs[0]._values.size() <<"\n\n";
	_curTx = 0; _curTy = 0; _curTz = 0;
	_curRx = 0; _curRy = 0; _curRz = 0;
	for (unsigned int idof = 0 ; idof < _dofs.size() ; idof++) {
		if(!_dofs[idof].name.compare("Xposition")) _curTx = _dofs[idof]._values[iframe];
		if(!_dofs[idof].name.compare("Yposition")) _curTy = _dofs[idof]._values[iframe];
		if(!_dofs[idof].name.compare("Zposition")) _curTz = _dofs[idof]._values[iframe];
		if(!_dofs[idof].name.compare("Zrotation")) _curRz = _dofs[idof]._values[iframe];
		if(!_dofs[idof].name.compare("Yrotation")) _curRy = _dofs[idof]._values[iframe];
		if(!_dofs[idof].name.compare("Xrotation")) _curRx = _dofs[idof]._values[iframe];
	}
	// Animate children :
	for (unsigned int ichild = 0 ; ichild < _children.size() ; ichild++) {
		_children[ichild]->animate(iframe);
	}
}


void Joint::nbDofs() {
	if (_dofs.empty()) return;

	double tol = 1e-4;

	int nbDofsR = -1;

	// TODO :
	cout << _name << " : " << nbDofsR << " degree(s) of freedom in rotation\n";

	// Propagate to children :
	for (unsigned int ichild = 0 ; ichild < _children.size() ; ichild++) {
		_children[ichild]->nbDofs();
	}

}
