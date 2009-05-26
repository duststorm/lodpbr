#ifndef CLUSTERREFINE_HPP_
#define CLUSTERREFINE_HPP_

#include <vector>
#include <iostream>

/*! \brief The ClusterRefine class .
 * Agglomerative criteria for  Clustering

*@class ClusterRefine.
*@brief Agglomerative criteria for  Clustering
*@details ...
*@author Felipe Moura.
*@email fmc@cos.ufrj.br
*@version 1.0.
*\nosubgrouping */

template <class Real,class ItemPtr>
class JoinCriteria
{
  /// Decides whether or not add the item to the clustering start by seed
  static bool Join ( ItemPtr seed,ItemPtr surfel, ItemPtr  item)
  {
    return 0;
  }

};

template <class Real,class ItemPtr>
class MergeCriteria
{
  /// Decides whether or not add the item to the clustering start by seed
  static bool Merge ( ItemPtr seed, std::vector<ItemPtr>  item)
  {
    return 0;
  }

};

/*@class ClusterRefine.
 *@brief Agglomerative criteria for  Clustering.
 * A node is ...*/

template <class Real,class ItemPtr>
class JoinByNormal : public JoinCriteria <Real,ItemPtr>
{
	/// Add an item to the clustering if the angle between the seed
	/// and the item is over the NORMAL
public:
	static bool Join ( ItemPtr seed, ItemPtr surfel, ItemPtr  item)
	{
//		 if ( 1 )//(seed->Normal() * item->Normal()) > 0.0  )
//		 {
			 Real lim = 0.3;
			 Real alfa = 3;
			 Real dist 		 = alfa*surfel->Center().EuclideanDistance(item->Center());
			 Real Normaldist = ((1 - (surfel->Normal() * item->Normal()))*surfel->Cost())*(1/lim);
			 Real cost = (dist+Normaldist+surfel->Cost());
			 //std::cout << "cost " << Normaldist << std::endl;
			 if (cost < lim)
			 {

				 if( item->Cost() > cost )
				 {
					 item->SetCost(cost);
					 return 1;
				 }else
				 {
					 return 0;
				 }

			 }else
			 {
				 return 0;
			 }

//		 }else
//		 {
//			 return 0;
//		 }



	}
};

/*@class ClusterRefine.
 *@brief Agglomerative criteria for  Clustering.
 * A node is ...*/

template <class Real,class ItemPtr>
class MergeBySize : public MergeCriteria <Real,ItemPtr>
{
	/// Add an item to the clustering if the angle between the seed
	/// and the item is over the NORMAL
public:
	static bool Merge ( ItemPtr seed, std::vector<ItemPtr>  item)
	{
		return 1;
	}
};

#endif /*CLUSTERREFINE_HPP_*/
