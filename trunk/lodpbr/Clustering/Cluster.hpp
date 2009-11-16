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
	typedef typename Celer::Surfel<Real>* 				SurfelPtr;

	typedef  std::vector<Surfel>						SurfelVector;
	typedef  typename std::vector<Surfel>::iterator	    SurfelVectorIterator;
	typedef  std::vector<SurfelPtr>						SurfelPtrVector;
	typedef typename  SurfelPtrVector::iterator			SurfelPtrVectorIterator;
	typedef typename  SurfelPtrVector::reverse_iterator	SurfelPtrVectorReverseIterator;

	typedef  std::list<SurfelPtr>						SurfelPtrList;
	typedef typename  SurfelPtrList::iterator			SurfelPtrListIterator;
	typedef typename  SurfelPtrList::reverse_iterator	SurfelPtrListReverseIterator;

	/// public attributes
	std::vector< SurfelPtrList >   Clusters;
	SurfelPtrVector					    Surfels;
	KdTree<Real,Celer::Surfel<Real>* >				KDTree;



	Cluster()
	{
		init();
	}
	/// Constructor
	/// Initialize the KD-Tree member with list of surfels
	/// @param Refernce to a list of surfels
	Cluster(SurfelVector& pSurfels,Celer::BoundingBox3<Real> pWorld)

	{
		init();

		if (KDTree.root ==  0)
		{
			KDTree = KdTree<Real,SurfelPtr >(pWorld);
		}
		else
		{
			delete KDTree.root;
			KDTree = KdTree<Real,SurfelPtr >(pWorld);
		}

		std::cout << "KD-Tree Start" << std::endl;
		for (SurfelVectorIterator it =  pSurfels.begin();it != pSurfels.end(); ++ it )
		{
			SurfelPtr s = (&(*it));
			KDTree.Insert (s);
		}
		std::cout << "KD-Tree End" << std::endl;

	}

	void init()
	{
		colors.push_back(Celer::Vector4<float>(1.0,0.0,0.0,0.5));
		colors.push_back(Celer::Vector4<float>(1.0,1.0,0.0,0.5));
		colors.push_back(Celer::Vector4<float>(0.0,1.0,0.0,0.5));
		colors.push_back(Celer::Vector4<float>(0.0,1.0,1.0,0.5));
		colors.push_back(Celer::Vector4<float>(0.5,0.5,5.0,0.5));
		colors.push_back(Celer::Vector4<float>(0.5,0.0,0.5,0.5));
		colors.push_back(Celer::Vector4<float>(0.25,0.5,0.25,0.5));
		colors.push_back(Celer::Vector4<float>(0.25,0.0,0.75,0.5));
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
    void Build1(int pCont,int pKNeighborsSize ,const SurfelPtr& pSeed)
    {

            /// How many comparisons the Kd-Tree do to finding an element
        int                                  KNearestSearchComps = 0;
        /// Number of clustering. Only for debuging
        int                                  cont                = 0;
        ///
        SurfelPtr                              lCurrentSeed        = pSeed;
        ///
        SurfelPtr                              lSurfel                 = pSeed;

        /// list of surfels for expansion
        SurfelPtrList lOpen;
        /// list of seeds
        SurfelPtrList lSeeds;
        /// Surfel that belong to the cluster
        /// @detail
        SurfelPtrList  					lClose;

        SurfelPtrVector                 lExpasion;
        SurfelPtrVector                 lNeighbors;
        /// lista dos k vizinhos do surfel semente lSeed, em ordem decrescente de distância

        lSeeds.push_front(pSeed);

            while ( (cont < pCont ) && (lSeeds.size() != 0))
            {

                    lCurrentSeed = lSeeds.front();
                    lSeeds.pop_front();

                    if (lCurrentSeed->SeedMarked() == 1)
                    {
                            continue;
                    }
                    lCurrentSeed->SetCost(0);
                    lCurrentSeed->SetID(cont);
                lCurrentSeed->SetExpansionMarked(1);
                    lOpen.push_back(lCurrentSeed);


                    while ( (lOpen.size() != 0) && (lClose.size() < 1000))
                    {
                            lNeighbors.clear();
                            lSurfel = lOpen.front();
                            lSurfel->SetSeedMarked(1);
                            lOpen.pop_front();
                            lClose.push_back(lSurfel);
                            lNeighbors              = KDTree.KNearestNeighbors(lSurfel ,50 , KNearestSearchComps);

                            lExpasion               = GetNotMarked(lNeighbors);

//                              std::cout << "SEED " <<  lCurrentSeed->ID() << std::endl;
//                              std::cout << "Surfel " << contSurfel << std::endl;
                            for(SurfelPtrListReverseIterator it = lNeighbors.rbegin(); it !=  lNeighbors.rend();++it)
                            {

                                    if ( Similarity::Join(lCurrentSeed,lSurfel,(*it)) )
                                    {
                                            (*it)->SetExpansionMarked(1);
                                            lOpen.push_back((*it));
                                    }
                                    else
                                    {

                                            if ( ((*it)->SeedMarked() == 0) && ((*it)->ExpansionMarked() == 0))
                                            {
                                                    lSeeds.push_back((*it));
                                            }


                                    }
//                                      std::cout << "Cost " << (*it)->Cost() << std::endl;
                            }
//                              std::cout << "---" << std::endl;

                    }


                    for(SurfelPtrListIterator it = lClose.begin(); it !=  lClose.end();++it)
                    {
                            (*it)->SetExpansionMarked(0);
                    }
                    //std::cout << "lOpen " << lOpen.size() << "--"  <<  "lClose " << lClose.size() << std::endl;
                    Clusters.push_back(lClose);
                    MergeEllipses<Real> me = MergeEllipses<Real>(lClose);
                    Surfels.push_back(me.NewSurfelPtr());
                    lClose.clear();
                    ++cont;
            }


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

		/// How many comparisons the Kd-Tree do to finding an element
		int                                  KNearestSearchComps = 0;
		///
		/// Surfel that belong to the cluster
		/// @detail
		SurfelPtrList  lClose;
		SurfelPtrList  lOpen;
		SurfelPtrVector                 lNeighbors;
		SurfelPtr                  lSurfel                 = 0;

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
			if(lSurfel->ExpansionMarked() == true)
			{
				//std::cout << "cont " << cont << std::endl;
				continue;
			}
			lSurfel->SetMarked			(true);
			lSurfel->SetExpansionMarked	(true);
			lSurfel->SetClusterID		(cont);

			lNeighbors  = KDTree.KNearestNeighbors(lSurfel ,100 , KNearestSearchComps);

			for(size_t i = lNeighbors.size(); i != 0; --i)
			{
				if( lClose.size() >= 50)
				{
					for(size_t j = i; j != 0; --j)
					{
						if (lNeighbors[j]->ExpansionMarked()== false)
							lOpen.push_back(lNeighbors[j]);
					}
					break;
				}
				else
				{
					if (lNeighbors[i]->Marked() == false)
					{
						lNeighbors[i]->SetClusterID		(cont);
						lNeighbors[i]->SetExpansionMarked(true);
						lClose.push_back(lNeighbors[i]);

					}

				}
				//std::cout << "cont " << cont << std::endl;
			}
			++cont;
			lClose.pop_front();
			lClose.push_front(lSurfel);
			Clusters.push_back(lClose);
            MergeEllipses<Real> me = MergeEllipses<Real>(lClose);
            Surfels.push_back(me.NewPtrSurfel());
			lClose.clear();
			lNeighbors.clear();
		}
		delete KDTree.root;
	}






/* ---------------------------------------- Draw Functions ---------------------------------------- */

	void DrawSurfels(unsigned int pNumber)
	{
		itColor = colors.begin();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
	    glPushMatrix();
	    glColor3fv(Colors(true));
	    Surfels[pNumber]->DrawTriangleFan(64);
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
	    	 	glColor3fv(Colors(false));
	    		glBegin(GL_POINTS);
	    		for ( SurfelPtrListIterator j = Clusters[pNumber].begin() ; j != Clusters[pNumber].end(); ++j )
	    		{
	    			glVertex3fv( (*j)->Center() );
	    		}
	    		glEnd();
	    		glPopMatrix();

	    		if (pShowSeed == true)
	    		{
		    		glPushMatrix();
		    		glPointSize(10.0);
		    	 	glColor3f(0.0,0.0,0.0);
		    		glBegin(GL_POINTS);
		    		{
		    			glVertex3fv( (*Clusters[pNumber].begin())->Center() );
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
	    for(unsigned int i = Begin; i < End ; ++i )
	    {
				glPushMatrix();
				glEnable(GL_POINT_SMOOTH);
	    		glPointSize(5.0);
	    	 	glColor3fv(Colors(false));
	    		glBegin(GL_POINTS);
	    		for ( SurfelPtrListIterator j = Clusters[i].begin() ; j != Clusters[i].end(); ++j )
	    		{
	    			glVertex3fv( (*j)->Center() );

	    		}
	    		glEnd();
	    		glPopMatrix();


    			if (pShowSeed == true)
    			{
    				glPushMatrix();
    				glPointSize(10.0);
    				glEnable(GL_POINT_SMOOTH);
    				glColor3f(0.0,0.0,0.0);
    				glBegin(GL_POINTS);
    				{
    					glVertex3fv( (*Clusters[i].begin())->Center() );
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

	/// destructor
	virtual ~Cluster()
	{

	}
private:

	Celer::Vector4<float> Colors(bool change)
	{

		if(itColor == colors.end())
		{
			itColor = colors.begin();
		}
		if (change == false)
		{
			++itColor;
		}

		return (*itColor);
	}

	std::vector<Celer::Vector4<float> >::iterator itColor;

    std::vector<Celer::Vector4<float> > colors;
};



#endif /*CLUSTER_HPP_*/
