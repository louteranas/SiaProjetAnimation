#ifndef _JOINT_H_
#define _JOINT_H_

#include <string>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <QtGui/QMatrix4x4>

class AnimCurve {
public :
	AnimCurve() {};
	AnimCurve(const char* name) {
			this->name = name;
	};
	~AnimCurve() {
		_values.clear();
	}
public :
	std::string name;					// name of dof
	std::vector<double> _values;		// different keyframes = animation curve
};


enum RotateOrder {roXYZ=0, roYZX, roZXY, roXZY, roYXZ, roZYX};

// Create from data :

class Joint {
public :
	std::string _name;					// name of joint
	int id_liste;
	double _offX;						// initial offset in X
	double _offY;						// initial offset in Y
	double _offZ;						// initial offset in Z
	std::vector<AnimCurve> _dofs;		// keyframes : _animCurves[i][f] = i-th dof at frame f;
	double _curTx;						// current value of translation on X
	double _curTy;						// current value of translation on Y
	double _curTz;						// current value of translation on Z
	double _curRx;						// current value of rotation about X (deg)
	double _curRy;						// current value of rotation about Y (deg)
	double _curRz;						// current value of rotation about Z (deg)
	int _rorder;						// order of euler angles to reconstruct rotation
	QMatrix4x4 mat;
	QVector3D positionInitial;
	//std::vector<std::vector<float>> _children;	// children of the current joint
	std::vector<Joint*> _children;	// children of the current joint


public :
	// Constructor :
	Joint() {};
	// Destructor :
	~Joint() {
		_dofs.clear();
		_children.clear();
	}


	static Joint* create(std::string name, double offX, double offY, double offZ, Joint* parent, int id_liste);

	// Load from file (.bvh) :
	static Joint* createFromFile(std::string fileName);

	void animate(int iframe=0);

	// Analysis of degrees of freedom :
	void nbDofs();
};


#endif
