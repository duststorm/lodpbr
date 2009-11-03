#ifndef CLUSTER_HPP_
#define CLUSTER_HPP_




/*! \brief The Cluster class .
 * Cluster class ...
 *@class Cluster.
 *@brief Class that represent the Cluster hierarchy
 *@details ...
 *@author Felipe Moura.
 *@email fmc@cos.ufrj.br
 *@version 1.0.
 * \nosubgrouping */

#include <GL/gl.h>
#include <GL/glu.h>

#include <deque>
#include <list>
#include <algorithm>
#include <iostream>

#include "ClusterCriteria.hpp"

#include "Kd-Tree/Kd-Tree.hpp"

#include "Surfels/SurfelContainer.hpp"
#include "Surfels/MergeEllipses.hpp"

#include "Math/BoundingBox3.hpp"

#include "Math/Vector4.hpp"

template <class Real,class ItemPtr, class Similarity  = JoinByNormal<Real,ItemPtr>,
									class Aggregation = MergeBySize <Real,ItemPtr> >
class Cluster
{

	typedef  std::vector<ItemPtr>		ItemPtrList;

public:
	/// public attributes
	std::vector< std::list<ItemPtr> >   Clusters;
	std::vector<ItemPtr>			    mSurfels;
	KdTree<Real,ItemPtr>				mKDTree;

	Cluster()
	{
		init();
	}
	/// Constructor
	/// Initialize the KD-Tree member with list of surfels
	/// @param Refernce to a list of surfels
	Cluster(SurfelContainer<Real>& pSurfels)
	{
		init();
	    Celer::BoundingBox3<float> world =     Celer::BoundingBox3<float>(
	    		Celer::Point3<float>(pSurfels.Box().xMin(),pSurfels.Box().yMin(),pSurfels.Box().zMin()),
				Celer::Point3<float>(pSurfels.Box().xMax(),pSurfels.Box().yMax(),pSurfels.Box().zMax())
																     );

		if (mKDTree.root ==  0)
		{
			mKDTree = KdTree<Real,ItemPtr >(world);
		}
		else
		{
			delete mKDTree.root;
			mKDTree = KdTree<Real,ItemPtr >(world);
		}

		std::cout << "KD-Tree Start" << std::endl;
		for (typename std::vector<Celer::Surfel<Real> >::iterator surf =  pSurfels.mSurfels.begin();surf != pSurfels.mSurfels.end(); ++ surf )
		{
			mKDTree.Insert ( new Celer::Surfel<Real>(*surf) );
		}
		std::cout << "KD-Tree End" << std::endl;


	}

	void init()
	{
		colors.push_back(Celer::Vector4<float>(1.0,0.0,0.0,0.5));
		colors.push_back(Celer::Vector4<float>(1.0,1.0,0.0,0.5));
		colors.push_back(Celer::Vector4<float>(0.0,1.0,0.0,0.5));
		colors.push_back(Celer::Vector4<float>(0.0,1.0,1.0,0.5));
		colors.push_back(Celer::Vector4<float>(0.5,0.5,5.0,0.5));
		colors.push_back(Celer::Vector4<float>(0.5,0.0,0.5,0.5));
		colors.push_back(Celer::Vector4<float>(0.25,0.5,0.25,0.5));
		colors.push_back(Celer::Vector4<float>(0.25,0.0,0.75,0.5));
		colors.push_back(Celer::Vector4<float>(0.0,0.0,1.0,0.5));
		colors.push_back(Celer::Vector4<float>(0.1,0.1,0.5,0.5));
		colors.push_back(Celer::Vector4<float>(1.0,0.1,0.5,0.5));
		colors.push_back(Celer::Vector4<float>(0.1,0.1,0.5,0.5));
		colors.push_back(Celer::Vector4<float>(1.0,1.0,0.5,0.5));
	}

	ItemPtrList GetNotMarked( ItemPtrList& plNeighbors )
	{
		ItemPtrList lNeighbors;
		for(typename std::vector<ItemPtr>::iterator it = plNeighbors.begin(); it !=  plNeighbors.end();++it)
		{

			if (  ((*it)->ExpansionMarked() == 0) )
			{
				lNeighbors.push_back((*it));
			}

		}
		return lNeighbors;
	}

	/// Build a set of Clusters by the Similarities and Aggregations.
	/// @details ...
	/// conditions pass by template parameter.
	/// @param pCont Debug. How many clusters?
	/// @param pCont pKNeighborsSize. The size of the Neighbor.
	/// @param pSeed pKNeighborsSize. Initial Seed.

	void Build(int pCont,int pKNeighborsSize ,const ItemPtr& pSeed)
	{

		/// How many comparisons the Kd-Tree do to finding an element
	    int 				 KNearestSearchComps = 0;
	    /// Number of clustering. Only for debuging
	    int 				 cont                = 0;
	    ///
	    ItemPtr				 lCurrentSeed        = pSeed;
	    ///
	    ItemPtr				 lSurfel       		 = pSeed;

	    /// list of surfels for expansion
	    std::deque<ItemPtr> lOpen;
	    /// list of seeds
	    std::deque<ItemPtr>	lSeeds;
	    /// Surfel that belong to the cluster
	    /// @detail
	    std::list<ItemPtr> 	lClose;
	    ItemPtrList			lExpasion;
	    ItemPtrList 		lNeighbors;
	    /// lista dos k vizinhos do surfel semente lSeed, em ordem decrescente de distância

	    lSeeds.push_front(pSeed);

		while ( (cont < pCont ) && (lSeeds.size() != 0))
		{

			lCurrentSeed = lSeeds.front();
			lSeeds.pop_front();

			if (lCurrentSeed->SeedMarked() == 1)
			{
				continue;
			}
			lCurrentSeed->SetCost(0);
			lCurrentSeed->SetID(cont);
		    lCurrentSeed->SetExpansionMarked(1);
			lOpen.push_back(lCurrentSeed);


			while ( (lOpen.size() != 0) && (lClose.size() < 200))
			{
				lNeighbors.clear();
				lSurfel = lOpen.front();
				lSurfel->SetSeedMarked(1);
				lOpen.pop_front();
				lClose.push_back(lSurfel);
				lNeighbors 		= mKDTree.KNearestNeighbors(lSurfel ,	8, KNearestSearchComps);

				lExpasion 		= GetNotMarked(lNeighbors);

//				std::cout << "SEED " <<  lCurrentSeed->ID() << std::endl;
//				std::cout << "Surfel " << contSurfel << std::endl;
				for(typename std::vector<ItemPtr>::reverse_iterator it = lNeighbors.rbegin(); it !=  lNeighbors.rend();++it)
				{

					if ( Similarity::Join(lCurrentSeed,lSurfel,(*it)) )
					{
						(*it)->SetExpansionMarked(1);
						lOpen.push_back((*it));
					}
					else
					{

						if ( ((*it)->SeedMarked() == 0) && ((*it)->ExpansionMarked() == 0))
						{
							lSeeds.push_back((*it));
						}


					}
//					std::cout << "Cost " << (*it)->Cost() << std::endl;
				}
//				std::cout << "---" << std::endl;

			}


			for(typename std::list<ItemPtr>::iterator it = lClose.begin(); it !=  lClose.end();++it)
			{
				(*it)->SetExpansionMarked(0);
			}
			//std::cout << "lOpen " << lOpen.size() << "--"  <<  "lClose " << lClose.size() << std::endl;
			Clusters.push_back(lClose);
			MergeEllipses<Real> me = MergeEllipses<Real>(lClose);
			mSurfels.push_back(me.NewPtrSurfel());
			lClose.clear();
			++cont;
		}


	}


/* ---------------------------------------- Draw Functions ---------------------------------------- */

	void DrawSurfels()
	{
		std::vector<Celer::Vector4<float> >::iterator c = colors.begin();
		for ( typename std::vector<ItemPtr>::iterator it = mSurfels.begin(); it != mSurfels.end();++it)
		{
			glPushMatrix();
			glColor3fv(*c);
			++c;
			if(c == colors.end())
				c = colors.begin();
			(*it)->DrawTriangleFan(8);
			glPopMatrix();
		}
	}

	void DrawClusters (int pNumber)
	{

		std::vector<Celer::Vector4<float> >::iterator c = colors.begin();
	    glPushMatrix();

			if (Clusters.size() >= pNumber)
			{

				for ( int  i = 0; i !=  pNumber ; ++i )
				{
					//std::cout << Clusters[i].size() << " Size" << std::endl;
					glPointSize(5.0);
					if(c == colors.end())
						c = colors.begin();
					glPushMatrix();
				   	glEnable(GL_POINT_SMOOTH);
				   	glPointSize(5.0);
					glColor3fv(*c);
				    glBegin(GL_POINTS);
						for ( typename std::list<ItemPtr>::iterator j = Clusters[i].begin() ; j != Clusters[i].end(); ++j )
						{
							glVertex3fv( (*j)->Center() );
						}
					glEnd();
					glPopMatrix();

					// Desenha a semente

					glPushMatrix();
				   	glEnable(GL_POINT_SMOOTH);
				   	glPointSize(15.0);
				   	glColor3fv(*c);
				    glBegin(GL_POINTS);
						glVertex3fv( (*(Clusters[i].begin()))->Center() );
					glEnd();
					glPopMatrix();
					++c;

				}

			}

    	glEnd();
    	glPopMatrix();
	}
	/// destructor
	virtual ~Cluster()
	{

	}
private:

    std::vector<Celer::Vector4<float> > colors;
};



#endif /*CLUSTER_HPP_*/
