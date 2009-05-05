#ifndef CLUSTERREFINE_HPP_
#define CLUSTERREFINE_HPP_

#include <vector>

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
  static bool Join ( ItemPtr seed, ItemPtr  item)
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
	static bool Join ( ItemPtr seed, ItemPtr  item)
	{
		return ( (seed->Normal() * item->Normal()) > 0.8  );
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
	static bool Merge ( ItemPtr seed, std::vector<ItemPtr>  item)
	{
		return 1;
	}
};

#endif /*CLUSTERREFINE_HPP_*/
