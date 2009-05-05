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

#include "Kd-Tree/Kd-Tree.hpp"
#include "ClusterCriteria.hpp"

template <class Real,class ItemPtr, class Similarity  = JoinByNormal<Real,ItemPtr>,
									class Aggregation = MergeBySize <Real,ItemPtr> >
class Cluster
{

	typedef  std::vector<ItemPtr>		ItemPtrList;

public:
	/// public attributes
	std::vector< std::vector<ItemPtr> > Clusters;

	/// Constructor
	/// @param reference to the KDTree
	Cluster(KdTree<Real,ItemPtr>& pKDTree)
	{
		this->mKDTree = pKDTree;
	}

	/// Build a set of Clusters by the Similarities and Aggregations.
	/// conditions pass by template parameter.
	/// @param pCont Debug. How many clusters?
	/// @param pCont pKNeighborsSize. The size of the Neighbor.
	/// @param pSeed pKNeighborsSize. Initial Seed.

	void Build(int pCont,int pKNeighborsSize ,ItemPtr pSeed)
	{


	    int 				 KNearestSearchComps = 0;
	    int 				 cont                = 0;
	    ItemPtrList lCluster;
	    ItemPtrList lNeighbors 		= mKDTree.KNearestNeighbors(pSeed ,
																	pKNeighborsSize,
																	KNearestSearchComps);

		typename std::vector<ItemPtr>::reverse_iterator rellipse = lNeighbors.rbegin();

		while ( (rellipse != lNeighbors.rend()) && (cont <= pCont) )
		{
			if ( Similarity::Join(pSeed,*rellipse) )
			{
				lCluster.push_back((*rellipse));
				++rellipse;
			}
			else
			{
				break;
			}
		}

	    Clusters.push_back(lCluster);

	}
	/// destructor
	virtual ~Cluster()
	{

	}
private:

	KdTree<Real,ItemPtr>				mKDTree;
};

#endif /*CLUSTER_HPP_*/
