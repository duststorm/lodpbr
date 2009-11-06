#ifndef SURFELS_HPP_
#define SURFELS_HPP_

#include <vector>
#include <algorithm>

#include <vcg/simplex/vertex/base.h>
#include <vcg/simplex/vertex/component_ocf.h>
#include <vcg/simplex/edge/base.h>
#include <vcg/simplex/face/base.h>
#include <vcg/simplex/face/component_ocf.h>
#include <vcg/simplex/face/topology.h>


#include <wrap/io_trimesh/import_ply.h>
#include <wrap/io_trimesh/export_ply.h>

#include "Math/BoundingBox3.hpp"
#include "Surfel.hpp"
#include "IOSurfels.hpp"


template <class Real >
class SurfelContainer
{
public:


	typedef Celer::BoundingBox3<Real> 			Box3;
	typedef std::vector<Celer::Surfel<Real> > 	Surfels;
	typedef typename Surfels::iterator 			SurfelIterator;

	Surfels mSurfels;
	Box3 	mBox;

	SurfelContainer()
	{

	};

	static void LoadModel (const char * filename, SurfelContainer& pSurfels)
	{
		int mask;
		Celer::IOSurfels<Real>::LoadMask(filename,mask);

		if (mask & Celer::Surfel<Real>::IOM_SURFEL)
		{
			std::cout << "Lendo modelo LSplat ..." << std::endl;
		}
		else
		{
			std::cout << "Lendo modelo Ply ..." << std::endl;
			Celer::IOSurfels<Real>::LoadMesh(filename,pSurfels.mSurfels,pSurfels.mBox);
		}
	}
	virtual ~SurfelContainer(){};

private:



};


#endif /*SURFELS_HPP_*/
