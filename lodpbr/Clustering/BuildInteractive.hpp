/*
 * BuildInteractive.hpp
 *
 *  Created on: Dec 10, 2009
 *      Author: fmc
 */

#ifndef BUILDINTERACTIVE_HPP_
#define BUILDINTERACTIVE_HPP_

#include "Surfels/Kd-Tree/Kd-Tree.hpp"
#include "Surfels/MergeEllipses.hpp"
#include "Surfels/Surfel.hpp"

#include "Math/BoundingBox3.hpp"
#include "Math/EigenSystem.hpp"
#include "Math/Vector4.hpp"

template <class Real>
class BuildInteractive {
public:

	typedef Celer::BoundingBox3<Real>					Box3;

	typedef typename Celer::Surfel<Real>				Surfel;
	typedef typename Celer::Surfel<Real>*			    SurfelPtr;

	typedef std::vector<Surfel>							SurfelVector;
	typedef typename std::vector<Surfel>::iterator	    SurfelVectorIterator;

	typedef std::vector<SurfelPtr>						SurfelPtrVector;
	typedef typename  SurfelPtrVector::iterator			SurfelPtrVectorIterator;
	typedef typename  SurfelPtrVector::reverse_iterator	SurfelPtrVectorReverseIterator;


	typedef std::list<Surfel>							SurfelList;
	typedef typename  SurfelList::iterator				SurfelListIterator;
	typedef typename  SurfelList::reverse_iterator		SurfelListReverseIterator;

	typedef std::list<SurfelPtr>						SurfelPtrList;
	typedef typename  SurfelPtrList::iterator			SurfelPtrListIterator;
	typedef typename  SurfelPtrList::reverse_iterator	SurfelPtrListReverseIterator;


	BuildInteractive();
	void Draw();
	virtual ~BuildInteractive();
private:

	Surfel mSeed;
	Surfel mNeighbors;
	Surfel mNextElement;

	Surfel mNextEllipse;
	Surfel mCurrentEllipse;
	Surfel mLastEllipse;

};

#endif /* BUILDINTERACTIVE_HPP_ */
