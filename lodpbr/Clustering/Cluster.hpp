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

#include <list>
#include <vector>
#include <algorithm>
#include <iostream>

#include "Surfels/Kd-Tree/Kd-Tree.hpp"
#include "Surfels/MergeEllipses.hpp"
#include "Surfels/Surfel.hpp"

#include "Math/BoundingBox3.hpp"
#include "Math/Vector4.hpp"

#include "ClusterCriteria.hpp"


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

	typedef 		 std::vector<SurfelList>   			ClusterContainer;
	typedef typename std::vector<SurfelList>::iterator  ClusterIterator;
	/// public attributes

	ClusterContainer					   Clusters;
	SurfelVector					       Surfels;
	KdTree<Real,SurfelPtr>	 			   KDTree;



        Cluster()
        {
                Init();
        }
        /// Constructor
        /// Initialize the KD-Tree member with list of surfels
        /// @param Refernce to a list of surfels
        Cluster(SurfelVector& pSurfels,Celer::BoundingBox3<Real> pWorld)

        {
                Init();

                KDTree = KdTree<Real,SurfelPtr >(pWorld);

                std::cout << "KD-Tree Start " << pSurfels.size() << std::endl;
                for (SurfelVectorIterator it =  pSurfels.begin();it != pSurfels.end(); ++ it )
                {
						SurfelPtr s = new Surfel(*it);
                        KDTree.Insert (s);
                }
                std::cout << "KD-Tree End " << KDTree.Count() <<std::endl;

        }

        void Init()
        {
				//Clear();
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


        /// Build a set of Clusters by the Similarities and Aggregations.
        /// @details ...
        /// conditions pass by template parameter.
        /// @param pCont Debug. How many clusters?
        /// @param pCont pKNeighborsSize. The size of the Neighbor.
        /// @param pSeed pKNeighborsSize. Initial Seed.
        template <class Similarity ,class Aggregation>
        void Build(int pCont,int pKNeighborsSize ,const SurfelPtr& pSeed)
        {
    		Clusters.clear();
    		Surfels.clear();
    		KDTree.ResetMarkedClustering();
        	/// How many comparisons the Kd-Tree do to finding an element
        	int                                  KNearestSearchComps = 0;
        	///
        	/// Surfel that belong to the cluster
        	/// @detail
        	SurfelList  lClose;

        	SurfelPtrList  lOpen;
        	SurfelPtrVector                 lNeighbors;
        	SurfelPtr                  lSurfel    = 0;

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
        		if(lSurfel->ExpansionMarked() == 1)
        		{
        			//std::cout << "cont " << cont << std::endl;
        			continue;
        		}
        		lSurfel->SetMarked              (1);
        		lSurfel->SetExpansionMarked     (1);
        		lSurfel->SetClusterID           (cont);

        		lNeighbors  = KDTree.KNearestNeighbors(lSurfel ,200 , KNearestSearchComps);

        		for(SurfelPtrVectorReverseIterator it = lNeighbors.rbegin(); it != lNeighbors.rend(); ++it)
        		{

        			if( lClose.size() >= 100)
        			{
        				if ((*it)->ExpansionMarked()== 0)
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
//							if ((*it)->ExpansionMarked() == 0)
//							{
								(*it)->SetExpansionMarked(1);
								lClose.push_back((*(*it)));
//							}

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
        		Clusters.push_back(lClose);
        		MergeEllipses<Real> me = MergeEllipses<Real>(lClose);
        		Surfels.push_back(me.NewSurfel());
        		lClose.clear();
        		lNeighbors.clear();
        	}

        }






/* ------------------------------- Draw Functions -------------------------- */

        void DrawSurfels(unsigned int pNumber,unsigned int pSteps = 8,const Real& pRadius = 1.0 )
        {
        	itColor = colors.begin();
        	glPushAttrib(GL_ALL_ATTRIB_BITS);
        	glPushMatrix();
        	glColor3fv(Colors());
        	Surfels[pNumber].DrawTriangleFan(pSteps,pRadius);
        	glPopMatrix();
        	glPopAttrib();
        }

        void DrawClustersIndex (unsigned int pNumber,bool pShowSeed )
        {
        	glPushAttrib(GL_ALL_ATTRIB_BITS);
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
        		for ( SurfelListIterator j = Clusters[pNumber].begin() ; j != Clusters[pNumber].end(); ++j )
        		{
    	 			glNormal3fv (j->Normal());
        			glVertex3fv( j->Center() );
        		}
        		glEnd();
        		glPopMatrix();

        		if (pShowSeed == true)
        		{
        			glPushMatrix();
        			glPointSize(10.0);
        			glEnable(GL_POINT_SMOOTH);
        			glColor3f(1.0f,1.0f,1.0f);
        			glBegin(GL_POINTS);
        			{
        				glNormal3fv (Clusters[pNumber].begin()->Normal());
        				glVertex3fv( Clusters[pNumber].begin()->Center());
        			}
        			glEnd();
        			glPopMatrix();
        		}
        	}
        	glDisable(GL_MULTISAMPLE);
        	glEnable(GL_LIGHTING);
        	glPopMatrix();
        	glPopAttrib();
        }

        void DrawClustersRange (unsigned int Begin, unsigned int End,bool pShowSeed)
        {
        	glPushAttrib(GL_ALL_ATTRIB_BITS);
        	glPushMatrix();
        	glDisable(GL_LIGHTING);
        	itColor = colors.begin();
        	for(unsigned int i = Begin; i <= End ; ++i )
        	{
        		glPushMatrix();
        		glPointSize(5.0);
        		glColor3fv(Colors());
        		glBegin(GL_POINTS);
        		for ( SurfelListIterator j = Clusters[i].begin() ; j != Clusters[i].end(); ++j )
        		{
        			glNormal3fv (j->Normal());
        			glVertex3fv( j->Center() );
        		}
        		glEnd();
        		glPopMatrix();

        		if (pShowSeed == true)
        		{
        			glPushMatrix();
        			glPointSize(10.0);
        			glEnable(GL_POINT_SMOOTH);
        			glColor3f(1.0f,1.0f,1.0f);
        			glBegin(GL_POINTS);
        			{
        				glNormal3fv (Clusters[i].begin()->Normal());
        				glVertex3fv( Clusters[i].begin()->Center() );
        			}
        			glEnd();
        			glPopMatrix();
        		}



        	}
        	glEnd();
        	glEnable(GL_LIGHTING);
        	glPopMatrix();
        	glPopAttrib();
        }

    	void Clear()
    	{

    		Clusters.clear();
    		Surfels.clear();
    		KDTree.Clear();

    		std::cout << Clusters.size() << " sizes " << Surfels.size() << std::endl;
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

        std::vector<Celer::Vector4<float> >::iterator itColor;

    std::vector<Celer::Vector4<float> > colors;
};



#endif /*CLUSTER_HPP_*/

