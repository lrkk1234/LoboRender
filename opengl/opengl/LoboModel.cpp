#include "stdafx.h"
#include "LoboModel.h"


LoboModel::LoboModel()
{
	tinyobj::LoadObj(shapes_, materials_, "mesh/dragonlite.obj");
}

LoboModel::LoboModel(const char* filename)
{
	LoadModel(filename);
}

LoboModel::~LoboModel()
{
}

bool LoboModel::LoadModel(const char* filename)
{
	std::string err = tinyobj::LoadObj(shapes_, materials_, filename);
	if (!err.empty()) {
		std::cerr << err << std::endl;
		return false;
	}
	return true;
}

