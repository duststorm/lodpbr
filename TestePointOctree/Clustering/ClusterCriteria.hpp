#ifndef CLUSTERREFINE_HPP_
#define CLUSTERREFINE_HPP_

#include <vector>

#include "BoundingBox3.hpp"
#include "Point3.hpp"

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
class ClusterCriteria {
  typedef typename LAL::Point3<Real> 		Point3;     ///< A Point in 3D
  typedef typename LAL::BoundingBox3<Real> 	Box3; 
  /// Decides whether or not to split a leaf node
  static bool join (const Box3& world, const std::vector<ItemPtr>& items) {
    return false;
  }
};


/*@class ClusterRefine.
/*@brief Agglomerative criteria for  Clustering.
/* A node is ...*/

template <class Real,class ItemPtr, int Max=3>
class ClusterBySize : public ClusterCriteria <Real,ItemPtr> {
	
  typedef typename LAL::Point3<Real> 		Point3;     ///< A Point in 3D
  typedef typename LAL::BoundingBox3<Real> 	Box3; 
  /// Split a leaf node iff the list contains more than Max items
  static bool join (const Box3& world, const std::vector<ItemPtr>& items) {
    return items.size() > Max;
  }
};

#endif /*CLUSTERREFINE_HPP_*/
