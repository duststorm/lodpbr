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
 *@todo Real generic class
 * \nosubgrouping */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>


#include <list>
#include <vector>
#include <algorithm>
#include <iostream>

#include "Surfels/Kd-Tree/Kd-Tree.hpp"
#include "Surfels/MergeEllipses.hpp"
#include "Surfels/Surfel.hpp"

#include "Math/BoundingBox3.hpp"
#include "Math/EigenSystem.hpp"
#include "Math/Vector4.hpp"

#include "ClusterCriteria.hpp"

#include "Qt/GLWidget/Log/ClusterLog.hpp"

template <class Real>
class Cluster
{

public:

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

	typedef 		 std::vector<std::pair<int,SurfelList> >  			ClusterContainer;
	typedef typename std::vector<std::pair<int,SurfelList> >::iterator  ClusterIterator;
	/// public attributes

	ClusterContainer					   Clusters;
	KdTree<Real,SurfelPtr>	 			   KDTree;
	SurfelVector						   NewSurfels;
	SurfelVector					       Surfels;


        Cluster()
        {
                Init();
        }
        /// Constructor
        /// Initialize the KD-Tree member with list of surfels
        /// @param Refernce to a list of surfels
        void Initialize(Celer::BoundingBox3<Real> pWorld)
        {
                KDTree = KdTree<Real,SurfelPtr >(pWorld);

                std::cout << "KD-Tree Start " << Surfels.size() << std::endl;
                for (SurfelVectorIterator it =  Surfels.begin();it != Surfels.end(); ++ it )
                {
                        KDTree.Insert ( &(*it) );
                }
                std::cout << "KD-Tree End " << KDTree.Count() <<std::endl;
	        	Real maxC = -1;
		        Real minC = 1;

//                for (SurfelVectorIterator it =  Surfels.begin();it != Surfels.end(); ++ it )
//                 {
// 						SurfelPtr s = new Surfel(*it);
// 						Curvature(s,100);
// 						it->SetCurvature(s->Curvature());
// 						if (maxC <  s->Curvature())
// 						{
// 							maxC = s->Curvature();
// 						}
// 						if (minC > s->Curvature())
// 						{
// 							minC = s->Curvature();
// 						}
//
//                 }

	    		std::cout <<  " minC " << minC <<  ": maxC " << maxC << std::endl;
        }

        void Init()
        {
				//Clear();
				colors.clear();
                colors.push_back(Celer::Vector4<float>(1.0,0.0,0.0,0.5));
                colors.push_back(Celer::Vector4<float>(1.0,1.0,0.0,0.5));
                colors.push_back(Celer::Vector4<float>(0.0,1.0,0.0,0.5));
                colors.push_back(Celer::Vector4<float>(0.0,1.0,1.0,0.5));
                colors.push_back(Celer::Vector4<float>(0.5,0.5,0.5,0.5));
                colors.push_back(Celer::Vector4<float>(0.5,0.0,0.5,0.5));
                colors.push_back(Celer::Vector4<float>(0.25,0.5,0.25,0.5));
                colors.push_back(Celer::Vector4<float>(0.25,0.0,1.0,0.5));
                colors.push_back(Celer::Vector4<float>(0.0,0.0,1.0,0.5));
                colors.push_back(Celer::Vector4<float>(0.1,0.1,0.5,0.5));
                colors.push_back(Celer::Vector4<float>(1.0,0.1,0.5,0.5));
                colors.push_back(Celer::Vector4<float>(0.1,0.1,0.5,0.5));
                colors.push_back(Celer::Vector4<float>(1.0,1.0,0.5,0.5));

        }

        SurfelPtrVector GetNotMarked( SurfelPtrVector& plNeighbors )
        {
                SurfelPtrVector lNeighbors;
                for(SurfelPtrVectorIterator it = plNeighbors.begin(); it !=  plNeighbors.end();++it)
                {

                        if (  ((*it)->ExpansionMarked() == 0) )
                        {
                                lNeighbors.push_back((*it));
                        }

                }
                return lNeighbors;
        }


        void Curvature( SurfelPtr pSurfel, int pNeighbourhoodSize )
        {
        	/// How many comparisons the Kd-Tree do to finding an element
        	int KNearestSearchComps = 0;

        	SurfelPtrVector lNeighbors;
        	std::list<Celer::Point3<Real> >	lSurfels;
        	lNeighbors = KDTree.KNearestNeighbors(pSurfel ,pNeighbourhoodSize , KNearestSearchComps);
        	Real signal = 0;

        	Celer::Point3<Real> mean;

        	for(SurfelPtrVectorReverseIterator it = lNeighbors.rbegin(); it != lNeighbors.rend(); ++it)
        	{
        		//signal =  ((*it)->Center()-pSurfel->Center())*(*it)->Normal();
        		lSurfels.push_back( (*it)->Center() );
        		 mean += (*it)->Center();

        	}

        	mean /= lSurfels.size();

//        	if (signal > 0)
//        		signal = 1;
//        	else
//        		signal = (-1);

        	Celer::Point3<Real> lSurfel (pSurfel->Center());

        	Celer::EigenSystem<Real> lEigen(lSurfels,mean);

    		pSurfel->SetCurvature((lEigen.Curvature())*3);

        }


        Surfel GetCurrentEllipse() const
        {
        	return mCurrentEllipse;
        }

        template <class Similarity ,class Aggregation>
        void BuildInteractive(int pKNeighborsSize ,const SurfelPtr& pSeed , ClusterLog& clusterLog)
        {
        	SurfelList  lClose;
        	SurfelPtrList  lOpen;
        	SurfelPtrVector                 lNeighbors;
        	SurfelPtr        		        lSurfel    = 0;
        	int                             KNearestSearchComps = 0;

        	int shape = 0;
        	if (clusterLog.maskBuildClusterShape.Test(ClusterLog::ELLIPTICAL))
        	{
        		shape = 1 << 17;
        	}
        	else
        	{
        		shape = 1 << 18;
        	}

        	if(pSeed == 0)
        	{
        		return;
        	}

        	lSurfel                 = pSeed;
        	lSurfel->SetMarked              (1);
        	lSurfel->SetExpansionMarked     (1);

        	lClose.push_front(lSurfel);

        	MergeEllipses<Real> me = MergeEllipses<Real>(lClose,shape);

        	lNeighbors  = KDTree.KNearestNeighbors(lSurfel ,pKNeighborsSize , KNearestSearchComps);

        	lSurfel->SetPerpendicularError(2.0*(lSurfel->Center().EuclideanDistance(lNeighbors.back()->Center())));
        	std::cout << "Height  surfel" << lSurfel->PerpendicularError() << std::endl;

        	for(SurfelPtrVectorReverseIterator it = lNeighbors.rbegin(); it != lNeighbors.rend(); ++it)
        	{
        		if( ((lSurfel->Center() - (*it)->Center())*lSurfel->Normal()) > lSurfel->PerpendicularError())
        		{
        			continue;

        		}else
        		{
        			if (  me.NewSurfel(shape).TangencialError() <  2.0*lSurfel->MajorAxis().first )
        			{
        				//std::cout << "Altura " << ((lSurfel->Center() - (*it)->Center())*lSurfel->Normal()) << std::endl;
						(*it)->SetExpansionMarked(1);
						lClose.push_back((*(*it)));
						me = MergeEllipses<Real>(lClose,shape);
        			}
        		}
        	}

        	//MergeEllipses<Real> me = MergeEllipses<Real>(lClose,shape);
        	mCurrentEllipse = me.NewSurfel(shape);
        	//mCurrentEllipse.SetPerpendicularError(lSurfel->PerpendicularError());
        	std::cout << " Closed Size " << lClose.size() << std::endl;
        	std::cout << "perpendicular Surfel -- " << lSurfel->PerpendicularError()		 << std::endl;
        	std::cout << "MajorAxois -- " 			<< lSurfel->MajorAxis().first		 << std::endl;
        	std::cout << "perpendicular -- " << mCurrentEllipse.PerpendicularError() << std::endl;
        	std::cout << "Tangencial    -- " << mCurrentEllipse.TangencialError() 	 << std::endl;
        	lClose.clear();
        	lNeighbors.clear();
        	KDTree.ResetMarkedClustering();
        }


        /// Build a set of Clusters by the Similarities and Aggregations.
        /// @details ...
        /// conditions pass by template parameter.
        /// @param pCont Debug. How many clusters?
        /// @param pCont pKNeighborsSize. The size of the Neighbor.
        /// @param pSeed pKNeighborsSize. Initial Seed.
        template <class Similarity ,class Aggregation>
        void Build2(int pCont,int pKNeighborsSize ,const SurfelPtr& pSeed,ClusterLog& clusterLog,vcg::CallBackPos *cb=0  )
        {

        	if(pSeed == 0)
        	{
        		return;
        	}


        	int shape = 0;
        	if (clusterLog.maskBuildClusterShape.Test(ClusterLog::ELLIPTICAL))
        	{
        		shape = 1 << 17;
        	}
        	else
        	{
        		shape = 1 << 18;
        	}

    		Clusters.clear();
    		NewSurfels.clear();

    		int progress = 0;
    		int kd_tree_size = KDTree.Count();
        	/// How many comparisons the Kd-Tree do to finding an element
        	int                                  KNearestSearchComps = 0;
        	///
        	/// Surfel that belong to the cluster
        	/// @detail
        	SurfelList  lClose;
        	MergeEllipses<Real> me;

        	SurfelPtrList  	lOpen;
        	SurfelPtrVector lNeighbors;
        	SurfelPtr       lSurfel    = pSeed;
        	SurfelPtr       newSeed    = 0;

        	lNeighbors  = KDTree.KNearestNeighbors(lSurfel ,4, KNearestSearchComps);

        	Real mHeightMax	=  0.5*(lSurfel->Center().EuclideanDistance(lNeighbors.back()->Center()));

        	int cont = 0;

        	lOpen.push_back(pSeed);
        	// Para cada semente , gera seus vizinhos e depois escolhe uma semenete que nao esteje na intersecao
        	// de sua vizinhanca
        	while(lSurfel != 0)//while ( (lOpen.size() != 0) )
        	{

        		//lSurfel                 = lOpen.front();
        		//lOpen.pop_front();

        		lSurfel->SetMarked              (1);
        		lSurfel->SetExpansionMarked     (1);
        		lSurfel->SetClusterID           (cont);

        		lClose.push_front(lSurfel);

        		me = MergeEllipses<Real>(lClose,shape);

        		lNeighbors  = KDTree.KNearestNeighbors(lSurfel ,128, KNearestSearchComps);

        		for(SurfelPtrVectorReverseIterator it = lNeighbors.rbegin(); it != lNeighbors.rend(); ++it)
        		{

        			if (((lSurfel->Center() - (*it)->Center())*lSurfel->Normal()) < mHeightMax )
        			{
        				if(me.NewSurfel(shape).TangencialError() <  lSurfel->MajorAxis().first)
        				{
        					if ((*it)->ExpansionMarked() == 1)
        					{
        						(*it)->SetMarked(1);
        						lClose.push_back((*(*it)));
        						me = MergeEllipses<Real>(lClose,shape);

        					}else
        					{
        						(*it)->SetExpansionMarked(1);
        						lClose.push_back((*(*it)));
        						me = MergeEllipses<Real>(lClose,shape);
        					}
							//std::cout << " HeightMax :" << mHeightMax << " me Perpendicular Error " << me.NewSurfel().PerpendicularError() << std::endl;
        				}
        			}else { continue; }

//        			if (lClose.size() >= 28)
//        			{
//        				if ((*it)->Marked() == 0)
//        				{
//        					lOpen.push_back((*it));
//        				}
//        			}


        		}

        		lSurfel = KDTree.SearchSeed();
//        		if (lOpen.size() == 0)
//        		{
//        			newSeed = KDTree.SearchSeed();
//        			if(newSeed != 0)
//        			{
//        				lOpen.push_back(newSeed);
//        			}
//        			//std::cout << "Open Size " << lOpen.size() <<  std::endl;
//        		}

        		++cont;
        		//lClose.pop_front();
        		//lClose.push_front(lSurfel);
        		progress += lClose.size();
        		Clusters.push_back(std::make_pair<int,SurfelList>(cont,lClose));
        		//me = MergeEllipses<Real>(lClose);
        		NewSurfels.push_back(me.NewSurfel(shape));
        		lClose.clear();
        		lNeighbors.clear();
        		if(cb && (progress%100)==0) cb(progress*50/kd_tree_size,"Cluster Building");
        	}
        	cb(100,"Cluster Done!");
        	std::cout << "progress :" << progress << "kdtree " << kd_tree_size << "Cluster Size"<<  std::endl;
    		KDTree.ResetMarkedClustering();
        }

        /// Build a set of Clusters by the Similarities and Aggregations.
        /// @details ...
        /// conditions pass by template parameter.
        /// @param pCont Debug. How many clusters?
        /// @param pCont pKNeighborsSize. The size of the Neighbor.
        /// @param pSeed pKNeighborsSize. Initial Seed.
        template <class Similarity ,class Aggregation>
        void Build(int pCont,int pKNeighborsSize ,const SurfelPtr& pSeed,vcg::CallBackPos *cb=0 )
        {
    		Clusters.clear();
    		NewSurfels.clear();

    		int progress = 0;
    		int kd_tree_size = KDTree.Count();
        	/// How many comparisons the Kd-Tree do to finding an element
        	int                                  KNearestSearchComps = 0;
        	///
        	/// Surfel that belong to the cluster
        	/// @detail
        	SurfelList  lClose;

        	SurfelPtrList  	lOpen;
        	SurfelPtrVector lNeighbors;
        	SurfelPtr       lSurfel    = 0;

        	Real mHeightMax	= 0.0;

        	int cont = 0;

        	if(pSeed == 0)
        	{
        		return;
        	}

        	lOpen.push_back(pSeed);
        	// Para cada semente , gera seus vizinhos e depois escolhe uma semenete que nao esteje na intersecao
        	// de sua vizinhanca
        	while ( (lOpen.size() != 0) )
        	{

        		lSurfel                 = lOpen.front();
        		lOpen.pop_front();
        		if(lSurfel->Marked() == 1)
        		{
        			//std::cout << "cont " << cont << std::endl;
        			continue;
        		}
        		lSurfel->SetMarked              (1);
        		lSurfel->SetExpansionMarked     (1);
        		lSurfel->SetClusterID           (cont);

        		lNeighbors  = KDTree.KNearestNeighbors(lSurfel ,128, KNearestSearchComps);

        		mHeightMax = std::fabs(lSurfel->Normal()*( lNeighbors.back()->Center() - lSurfel->Center() ));

        		mHeightMax *= 4.0;

        		for(SurfelPtrVectorReverseIterator it = lNeighbors.rbegin(); it != lNeighbors.rend(); ++it)
        		{

        			Real Dist = std::fabs(lSurfel->Normal()*( (*it)->Center() - lSurfel->Center() )) ;

        			//std::cout << "Height " << mHeightMax << "Dist " << Dist << std::endl;

        			if( Dist >=  mHeightMax)
        			{
        				if ((*it)->Marked() == 0 )
        					lOpen.push_back((*it));
//        				for(size_t j = i; j != 0; --j)
//        				{
//        					if (lNeighbors[j]->ExpansionMarked()== 0)
//        						lOpen.push_back(lNeighbors[j]);
//        				}
//        				i = 0;
        				//break;

        			}else
        			{
							if ((*it)->ExpansionMarked() == 1)
							{
								if ((*it)->Marked() == 0 )
								{
									(*it)->SetMarked(1);


									lClose.push_back((*(*it)));
								}

							}else
							{
								(*it)->SetExpansionMarked(1);
								lClose.push_back((*(*it)));
								//lOpen.push_back((*it));
							}


        			}
//        			else
//        			{
//
//        				if (lNeighbors[i]->Marked() == 0)
//        				{
//        					lNeighbors[i]->SetClusterID             (cont);
//        					lNeighbors[i]->SetExpansionMarked(1);
//        					lClose.push_back(*lNeighbors[i]);
//        				}
//        			}
        			//std::cout << "cont " << cont << std::endl;
        		}
        		++cont;
        		//lClose.pop_front();
        		lClose.push_front(lSurfel);
        		progress += lClose.size();
        		Clusters.push_back(std::make_pair<int,SurfelList>(0,lClose));
        		MergeEllipses<Real> me = MergeEllipses<Real>(lClose);
        		NewSurfels.push_back(me.NewSurfel());
        		lClose.clear();
        		lNeighbors.clear();
        		if(cb && (progress%100)==0) cb(progress*50/kd_tree_size,"Cluster Building");
        	}
        	cb(100,"Cluster Done!");
        	std::cout << "progress :" << progress << "kdtree " << kd_tree_size << "Cluster Size"<<  std::endl;
    		KDTree.ResetMarkedClustering();
        }

/* ------------------------------- Draw Functions -------------------------- */

        void DrawSurfels(ClusterLog& pClusterLog,unsigned int pSteps = 8 )
        {
    	 	glPushMatrix();
    	    glEnable(GL_POLYGON_OFFSET_FILL | GL_POLYGON_SMOOTH_HINT | GL_MULTISAMPLE);
    	    glPolygonOffset(1,1);
    	 	glEnable (GL_BLEND);
    	 	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    	 	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    	 	//glColor4f(0.5f,0.5f,0.5f,1.0f);
    	 	glColor4f(1.0,0.35,0.0,0.75);
    	 	if(pClusterLog.maskRenderingClusterBy.Test(ClusterLog::Range))
    	 	{
    	 	for(unsigned int i = pClusterLog.getClusterRangeBegin(); i <= pClusterLog.getClusterRangeEnd() ; ++i )
    	 	{

    	 		if ( ( pClusterLog.getCamera().Eyes().Norm() * NewSurfels[i].Normal() ) > -0.2f )
    	 		{
    	 			std::list<Celer::Point3<float> > lBoundaries = NewSurfels[i].BoundariesSamples(pSteps,pClusterLog.getRadiusf());
    	 			glBegin (GL_TRIANGLE_FAN);
    	 			for(typename std::list<Celer::Point3<float> >::iterator  it = lBoundaries.begin();it != lBoundaries.end();++it)
    	 			{
    	 				glVertex3fv( *it );
    	 			}
    	 			glEnd();
    	 		}
    	 	}

    	 	}
    	 	if(pClusterLog.maskRenderingClusterBy.Test(ClusterLog::Index))
    	 	{
	 			std::list<Celer::Point3<float> > lBoundaries = NewSurfels[pClusterLog.getClusteIndex()].BoundariesSamples(pSteps,pClusterLog.getRadiusf());
	 			glBegin (GL_TRIANGLE_FAN);
	 			for(typename std::list<Celer::Point3<float> >::iterator  it = lBoundaries.begin();it != lBoundaries.end();++it)
	 			{
	 				glVertex3fv( *it );
	 			}
	 			glEnd();
    	 	}
    	 	glPopMatrix();


        }

        void DrawClustersIndex (const Celer::Vector3<float>& view,unsigned int pNumber,bool pShowSeed )
        {
        	glPushMatrix();
        	glDisable(GL_LIGHTING);
        	itColor = colors.begin();
        	glEnable(GL_POINT_SMOOTH);
        	glEnable(GL_MULTISAMPLE);
        	if (Clusters.size() >= pNumber)
        	{

        		glPushMatrix();
        		glPointSize(5.0);
        		glColor3fv(Colors());
        		glBegin(GL_POINTS);
        		for ( SurfelListIterator j = Clusters[pNumber].second.begin() ; j != Clusters[pNumber].second.end(); ++j )
        		{
                	//if ((view *  j->Normal())> 0.2f )
                	{
                		glNormal3fv (j->Normal());
						glVertex3fv( j->Center() );
                	}
        		}
        		glEnd();
        		glPopMatrix();

        		if (pShowSeed == true)
        		{
        			glPushMatrix();
        			glPointSize(10.0);
        			glEnable(GL_POINT_SMOOTH);
        			glColor3f(0.0f,0.0f,0.0f);
        			glBegin(GL_POINTS);
        			{
        				glNormal3fv (Clusters[pNumber].second.begin()->Normal());
        				glVertex3fv( Clusters[pNumber].second.begin()->Center());
        			}
        			glEnd();
        			glPopMatrix();
        		}
        	}
        	glDisable(GL_MULTISAMPLE);
        	glEnable(GL_LIGHTING);
        	glPopMatrix();

        }

        void DrawClustersRange (const Celer::Vector3<float>&view,unsigned int Begin, unsigned int End,bool pShowSeed)
        {
        	glPushMatrix();
        	itColor = colors.begin();
        	for(unsigned int i = Begin; i <= End ; ++i )
        	{
        		glPushMatrix();
        		glPointSize(5.0);
        		glColor3fv(Colors());
        		glBegin(GL_POINTS);
        		for ( SurfelListIterator j = Clusters[i].second.begin() ; j != Clusters[i].second.end(); ++j )
        		{
                	//if ((view *  j->Normal())> 0.2f )
                    	{
                    		glNormal3fv (j->Normal());
    						glVertex3fv( j->Center() );
                    	}
        		}
        		glEnd();
        		glPopMatrix();

        		if (pShowSeed == true)
        		{
        			glPushMatrix();
        			glPointSize(10.0);
        			glEnable(GL_POINT_SMOOTH);
        			glColor3f(0.0f,0.0f,0.0f);
        			glBegin(GL_POINTS);
        			{
        				glNormal3fv (Clusters[i].second.begin()->Normal());
        				glVertex3fv( Clusters[i].second.begin()->Center() );
        			}
        			glEnd();
        			glPopMatrix();
        		}



        	}
        	glEnd();
        	glPopMatrix();
        }

    	void Clear()
    	{

    		Clusters.clear();
    		NewSurfels.clear();
    		KDTree.Clear();

    		std::cout << Clusters.size() << " sizes " << NewSurfels.size() << std::endl;
    	}

        /// destructor
        virtual ~Cluster()
        {

        }
private:

        Celer::Vector4<float> Colors()
        {

        	if((++itColor) != colors.end())
        	{
                return (*itColor);
        	}
        	else
        	{
        		itColor = colors.begin();
        		return (*itColor);
        	}


        }

    	// Interactive Building
    	Surfel mSeed;
    	Surfel mNeighbors;
    	Surfel mNextElement;

    	Surfel mNextEllipse;
    	Surfel mCurrentEllipse;
    	Surfel mLastEllipse;

        enum
        {
            VERTEX = 0,
            NORMAL = 1
        };

        std::vector<Celer::Vector4<float> >::iterator itColor;
        std::vector<Celer::Vector4<float> > colors;
};



#endif /*CLUSTER_HPP_*/

