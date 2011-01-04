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

template <class Real,class SurfelPtr>
class JoinCriteria
{

  /// Decides whether or not add the item to the clustering start by seed
  static bool Join ( SurfelPtr seed,SurfelPtr surfel, SurfelPtr  item)
  {
    return 0;
  }

};

template <class Real,class SurfelPtr>
class MergeCriteria
{
  /// Decides whether or not add the item to the clustering start by seed
  static bool Merge ( SurfelPtr seed, std::vector<SurfelPtr>  item)
  {
    return 0;
  }

};

/*@class ClusterRefine.
 *@brief Agglomerative criteria for  Clustering.
 * A node is ...*/
template <class Real,class SurfelPtr>
class JoinByNormal : public JoinCriteria <Real,SurfelPtr>
{


public:
	static bool Join ( SurfelPtr seed, SurfelPtr surfel, SurfelPtr  item)
	{

		if (  (seed->Normal() * item->Normal()) > 0.0  )
		{
			Real lim = 0.3;
			Real alfa = 3;
			Real dist               = alfa*surfel->Center().EuclideanDistance(item->Center());
			Real Normaldist = ( (1 - (surfel->Normal() * item->Normal()) ));
			Real Similarity = (dist+Normaldist+surfel->Similarity());
			std::cout << "cost " << Similarity << "Normaldist " << Normaldist <<  "dist " << dist<< std::endl;
			if (Similarity < lim)
			{

				if( item->Similarity() > Similarity )
				{
					item->SetSimilarity(Similarity);
					return 1;
				}else
				{
					return 0;
				}

			}else
			{

			}


		}else
		{
			return 0;
		}

		return 0;
	}
};


/*@class ClusterRefine.
 *@brief Agglomerative criteria for  Clustering.
 * A node is ...*/

template <class Real,class SurfelPtr>
class MergeBySize : public MergeCriteria <Real,SurfelPtr>
{
	/// Add an item to the clustering if the angle between the seed
	/// and the item is over the NORMAL
public:
	static bool Merge ( SurfelPtr surfel, std::vector<SurfelPtr>  item)
	{
		return 1;
	}
};

#endif /*CLUSTERREFINE_HPP_*/
