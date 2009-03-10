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
*\nosubgrouping */

template <class Real,class ItemPtr, class Refine = ClusteringBySize<Real,ItemPtr> >
class Cluster
{
public:
	Cluster();
	virtual ~Cluster();
};

#endif /*CLUSTER_HPP_*/
