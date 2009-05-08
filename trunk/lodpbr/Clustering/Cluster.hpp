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

#include "ClusterCriteria.hpp"

#include "Kd-Tree/Kd-Tree.hpp"

#include "Surfels/surfels.hpp"

#include "Math/BoundingBox3.hpp"

#include "Math/Vector4.hpp"

template <class Real,class ItemPtr, class Similarity  = JoinByNormal<Real,ItemPtr>,
									class Aggregation = MergeBySize <Real,ItemPtr> >
class Cluster
{

	typedef  std::vector<ItemPtr>		ItemPtrList;

public:
	/// public attributes
	std::vector< std::vector<ItemPtr> > Clusters;
	KdTree<Real,ItemPtr>				mKDTree;

	Cluster()
	{
		init();
	}
	/// Constructor
	/// @param reference to the KDTree
	Cluster(Surfels<Real>& pSurfels)
	{
		init();
	    LAL::BoundingBox3<float> world =     LAL::BoundingBox3<float>(
	    		LAL::Point3<float>(pSurfels.box().xMin(),pSurfels.box().yMin(),pSurfels.box().zMin()),
				LAL::Point3<float>(pSurfels.box().xMax(),pSurfels.box().yMax(),pSurfels.box().zMax())
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
		for (typename std::vector<LAL::Surfel<Real> >::iterator surf =  pSurfels.surfels.begin();surf != pSurfels.surfels.end(); ++ surf )
		{
			mKDTree.Insert ( new LAL::Surfel<Real>(*surf) );
		}
		std::cout << "KD-Tree End" << std::endl;


	}

	void init()
	{
		colors.push_back(LAL::Vector4<float>(1.0,0.0,0.0,0.5));
		colors.push_back(LAL::Vector4<float>(1.0,1.0,0.0,0.5));
		colors.push_back(LAL::Vector4<float>(0.0,1.0,0.0,0.5));
		colors.push_back(LAL::Vector4<float>(0.0,1.0,1.0,0.5));
		colors.push_back(LAL::Vector4<float>(0.5,0.5,5.0,0.5));
		colors.push_back(LAL::Vector4<float>(0.5,0.0,0.5,0.5));
		colors.push_back(LAL::Vector4<float>(0.25,0.5,0.25,0.5));
		colors.push_back(LAL::Vector4<float>(0.25,0.0,0.75,0.5));
		colors.push_back(LAL::Vector4<float>(0.0,0.0,1.0,0.5));
		colors.push_back(LAL::Vector4<float>(0.1,0.1,0.5,0.5));
		colors.push_back(LAL::Vector4<float>(1.0,0.1,0.5,0.5));
		colors.push_back(LAL::Vector4<float>(0.1,0.1,0.5,0.5));
		colors.push_back(LAL::Vector4<float>(1.0,1.0,0.5,0.5));
	}
	/// Build a set of Clusters by the Similarities and Aggregations.
	/// conditions pass by template parameter.
	/// @param pCont Debug. How many clusters?
	/// @param pCont pKNeighborsSize. The size of the Neighbor.
	/// @param pSeed pKNeighborsSize. Initial Seed.

	void Build(int pCont,int pKNeighborsSize ,const ItemPtr& pSeed)
	{


	    int 				 KNearestSearchComps = 0;
	    int 				 cont                = 0;
	    ItemPtr				 lSeed               = pSeed;

	    ItemPtrList lCluster;
	    ItemPtrList lNeighbors 		= mKDTree.KNearestNeighbors(lSeed ,
																	pKNeighborsSize,
																	KNearestSearchComps);

		typename std::vector<ItemPtr>::reverse_iterator rellipse = lNeighbors.rbegin();
		lSeed->SetMarked(1);
		lCluster.push_back(pSeed);

		while ( (cont <= pCont) && (lNeighbors.size() != 0) )
		{

			while ( (rellipse != lNeighbors.rend()) )
			{
				if ( Similarity::Join(lSeed,(*rellipse)) )
				{
					lCluster.push_back((*rellipse));
					(*rellipse)->SetMarked(1);
					++rellipse;
				}
				else
				{
					break;
				}
			}

			for (typename std::vector<ItemPtr>::iterator i = lNeighbors.begin(); i != lNeighbors.end(); ++i )
			{
				std::cout << " Neibor " << (*i)->Marked() <<  std::endl;
			}

		    Clusters.push_back(lCluster);
		    ++cont;
		    lSeed = lNeighbors[0];
			lSeed->SetMarked(1);
		    std::cout << "pSeed" << lSeed->Center() << "--"  <<  std::endl;
		    lNeighbors.clear();
		    lNeighbors 		= mKDTree.KNearestNeighborsClustering(lSeed ,	pKNeighborsSize,
		    													KNearestSearchComps);
			for (typename std::vector<ItemPtr>::iterator i = lNeighbors.begin(); i != lNeighbors.end(); ++i )
			{
				std::cout << " NeiborKDTREE " << (*i)->Marked() <<   std::endl;
			}

		    rellipse = lNeighbors.rbegin();
		    lCluster.clear();
		    lCluster.push_back(lSeed);

		}


	}

	void DrawClusters (int pNumber)
	{

		std::vector<LAL::Vector4<float> >::iterator c = colors.begin();

	   	glPointSize(5.0);
	    glEnable(GL_POINT_SMOOTH);
	    glBegin(GL_POINTS);
	    glPushMatrix();

		if (pNumber == 0)
		{

			c = colors.begin();
			for ( typename std::vector< std::vector<ItemPtr> >::iterator i = Clusters.begin(); i != Clusters.end(); ++i )
			{
				glColor3fv(*c);
				++c;
				if(c == colors.end())
					c = colors.begin();
				for ( typename std::vector<ItemPtr>::iterator j = i->begin() ; j != i->end(); ++j )
				{
					glVertex3fv((*j)->Center());
				}
			}


		}else
		{

			if (Clusters.size() >= pNumber)
			{

				for ( int  i = 0; i != pNumber; ++i )
				{
					glColor3fv(*c);
					++c;
					if(c == colors.end())
						c = colors.begin();
					for ( typename std::vector<ItemPtr>::iterator j = Clusters[i].begin() ; j != Clusters[i].end(); ++j )
					{
						glVertex3fv( (*j)->Center() );
					}
				}

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

    std::vector<LAL::Vector4<float> > colors;
};


#endif /*CLUSTER_HPP_*/
