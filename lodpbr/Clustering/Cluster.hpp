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
	    LAL::BoundingBox3<float> world =     LAL::BoundingBox3<float>(
	    		LAL::Point3<float>(pSurfels.Box().xMin(),pSurfels.Box().yMin(),pSurfels.Box().zMin()),
				LAL::Point3<float>(pSurfels.Box().xMax(),pSurfels.Box().yMax(),pSurfels.Box().zMax())
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
		for (typename std::vector<LAL::Surfel<Real> >::iterator surf =  pSurfels.mSurfels.begin();surf != pSurfels.mSurfels.end(); ++ surf )
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
	/// conditions pass by template parameter.
	/// @param pCont Debug. How many clusters?
	/// @param pCont pKNeighborsSize. The size of the Neighbor.
	/// @param pSeed pKNeighborsSize. Initial Seed.

	void Build(int pCont,int pKNeighborsSize ,const ItemPtr& pSeed)
	{


	    int 				 KNearestSearchComps = 0;
	    int 				 cont                = 0;
	    ItemPtr				 lCurrentSeed        = pSeed;
	    ItemPtr				 lSurfel       		 = pSeed;

	    /// lista dos surfels a serem expandidos
	    std::deque<ItemPtr> lOpen;
	    /// lista dos surfels que passaram pelo teste de agregação
	    std::deque<ItemPtr>	lSeeds;
	    std::list<ItemPtr> 	lClose;
	    ItemPtrList			lExpasion;
	    /// lista dos k vizinhos do surfel semente lSeed, em ordem decrescente de distância

	    lSeeds.push_front(pSeed);

		while ( (cont < pCont ) && (lSeeds.size() != 0))
		{

			lCurrentSeed = lSeeds.front();
			lCurrentSeed->SetCost(0);
			lSeeds.pop_front();

			if (lCurrentSeed->SeedMarked() == 1)
			{
				continue;
			}
		    ItemPtrList 		lNeighbors;// 		= mKDTree.KNearestNeighbors(lCurrentSeed ,16, KNearestSearchComps);

//		    for(typename std::vector<ItemPtr>::iterator it = lNeighbors.begin(); it !=  lNeighbors.end();++it)
//	   		{
//		    	if ((*it)->Marked() == 0)
//		    	{
//		    		(*it)->SetMarked(1);
//		    		lOpen.push_back((*it));
//		    	}
//
//	   		}
		    lCurrentSeed->SetExpansionMarked(1);
			lOpen.push_back(lCurrentSeed);

			while ( (lOpen.size() != 0))
			{
				//std::cout << "lOpen " << lOpen.size() << "--"  <<  "lClose " << lClose.size() << "lExpansion " << lExpasion.size() << std::endl;

				lNeighbors.clear();
				lSurfel = lOpen.front();
				lSurfel->SetSeedMarked(1);
				lOpen.pop_front();
				lClose.push_back(lSurfel);
				lNeighbors 		= mKDTree.KNearestNeighbors(lSurfel ,	8, KNearestSearchComps);
				lExpasion 		= GetNotMarked(lNeighbors);

				for(typename std::vector<ItemPtr>::reverse_iterator it = lExpasion.rbegin(); it !=  lExpasion.rend();++it)
				{
					if ( Similarity::Join(lCurrentSeed,lSurfel,(*it)) )
					{
						(*it)->SetExpansionMarked(1);
						lOpen.push_back((*it));
					}
					else
					{
						if ( (*it)->SeedMarked() == 0 )
						{
							(*it)->SetExpansionMarked(0);
							lSeeds.push_back((*it));
						}


					}
				}

				//std::cout << "lOpen " << lOpen.size() << "--"  <<  "lClose " << lClose.size() << std::endl;
			}


			for(typename std::list<ItemPtr>::iterator it = lClose.begin(); it !=  lClose.end();++it)
			{
				(*it)->SetExpansionMarked(0);
			}
			Clusters.push_back(lClose);
			MergeEllipses<Real> me = MergeEllipses<Real>(lClose);
			mSurfels.push_back(me.NewPtrSurfel());
			lClose.clear();
			++cont;
		}
		//std::cout << "lOpen4 " << lOpen.size() << "--"  <<  "lClose " << lClose.size() << std::endl;

//		while ( (cont <= pCont) && (lNeighbors.size() != 0) )
//		{
//
//			while ( (rellipse != lNeighbors.rend()) )
//			{
//				if ( Similarity::Join(lSeed,(*rellipse)) )
//				{
//					lCluster.push_back((*rellipse));
//					(*rellipse)->SetMarked(1);
//					++rellipse;
//				}
//				else
//				{
//					break;
//				}
//			}
//
//			for (typename std::vector<ItemPtr>::iterator i = lNeighbors.begin(); i != lNeighbors.end(); ++i )
//			{
//				std::cout << " Neibor " << (*i)->Marked() <<  std::endl;
//			}
//
//		    Clusters.push_back(lCluster);
//		    ++cont;
//		    lSeed = lNeighbors[0];
//			lSeed->SetMarked(1);
//		    std::cout << "pSeed" << lSeed->Center() << "--"  <<  std::endl;
//		    lNeighbors.clear();
//		    lNeighbors 		= mKDTree.KNearestNeighborsClustering(lSeed ,	pKNeighborsSize,
//		    													KNearestSearchComps);
//			for (typename std::vector<ItemPtr>::iterator i = lNeighbors.begin(); i != lNeighbors.end(); ++i )
//			{
//				std::cout << " NeiborKDTREE " << (*i)->Marked() <<   std::endl;
//			}
//
//		    rellipse = lNeighbors.rbegin();
//		    lCluster.clear();
//		    lCluster.push_back(lSeed);
//
//		}


	}

	void DrawSurfels()
	{
		std::vector<LAL::Vector4<float> >::iterator c = colors.begin();
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

		std::vector<LAL::Vector4<float> >::iterator c = colors.begin();
	    glPushMatrix();
		if (pNumber == 0)
		{

			c = colors.begin();
			for ( typename std::vector< std::list<ItemPtr> >::iterator i = Clusters.begin(); i != Clusters.end(); ++i )
			{
				glColor3fv(*c);
				++c;
				if(c == colors.end())
					c = colors.begin();
				for ( typename std::list<ItemPtr>::iterator j = i->begin() ; j != i->end(); ++j )
				{
					glVertex3fv((*j)->Center());
				}
			}


		}else
		{

			if (Clusters.size() >= pNumber)
			{


				for ( int  i = pNumber; i != 0; --i )
				{
					glPushMatrix();
				   	glEnable(GL_POINT_SMOOTH);
				   	glPointSize(10.0);
				   	glColor3f(1.0,0.75,0.85);
				    glBegin(GL_POINTS);
					glVertex3fv( (*(Clusters[i].begin()))->Center() );
					glEnd();
					glPopMatrix();
					std::cout << Clusters[i].size() << " Size" << std::endl;
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
					++c;
					glEnd();
					glPopMatrix();

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
