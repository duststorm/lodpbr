//============================================================================
// Name        : agglomerative.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#define MAX_ERROR	0.1
#define MAX_COST    0.1

// Forma de agregacao das ellipse
#define BIGELLIPSE 0

#define STEP 10

struct Ellipse
{
	Vector3 mCenter;
	Vector3 mNormal;
	Vector3 mMinAxis;
	Vecotr3 mMaxAxis;

	int 	mClusterID   		= -1;
	// Error em relacao ao cluster
	float   mLastClusterCost 	= 9999;
	// Ultimo cluster gerado
	int    	mLastClusterID 		= -1;
	// Error em relacao a elipse gerada
	float 	mError 				= 9999;

};


std::map<float,Ellipse> kNeighbor(int k)
{
}

//Para ou continua a expanssao
bool Aggregation(close)
{

	return ( close.size() == STEP );
}


void SeedExpansion(Ellipse seed,int idCluster,std::list<Ellipse> ListSeed)
{
	// Custo do caminho do processo de expanssao da semente
	std::map<float,Ellipse,greater> open;
	// Lista de ellipse  que representa ellipes originais que podem vir a ser
	// usada no processo de agregacao
	std::vector<Ellipse> close;
	std::vector<Ellipse> Cluster;

	float mNexCostAggregation;
	int   mNextNumPointsAggregation;

	Ellipse mCurrentEllipse = seed;

	open.insert(std::make_pair(0,seed));

	while (open.size() > 0)
	{

		target = open.pop();


		float   cost 	 = target.first;
		Ellipse ellipse  = target.second;


		// Se o ponto ja foi expandido , tirar proximo elemento ta lista aberta
		if( (ellipse.mLastClusterID == idCluster) && (ellipse.mLastClusterCost < cost) )
		{
			continue;
		}

		// inclui apenas as ellipses para uma futura agregacao
		close.insert(target.second);
		// dado criterio de agregacao .. saber se para e gera um Ellipse
		if( Aggregation(close) == true  )
		{
			if( BIGELLIPSE )
			{

				close.insert(mCurrentEllipse);
				mCurrentEllipse = MakeEllipse(close);

			}
			else
			{
				mCurrentEllipse = MakeEllipse(new vector(close + Cluster));
			}

			if ( mCurrentEllipse.mError > MAX_ERROR )
			{

				while ( close.size() > 0 )
				{
					temp = close.pop();
					if (temp.mClusterID == -1)
					{
						ListSeed.append(temp);
					}
				}

				while ( open.size() > 0)
				{
					temp = open.pop();
					if (temp.mClusterID == -1)
					{
						ListSeed.append(temp);
					}


				}

			}
			else // mCurrentEllipse.mError < MAX_ERROR
			{
				UpdateAggregationCoditions();
				Cluster.append(close);
				while ( close.size() > 0)
				{
					temp = close.pop();
					if (temp.mError > mCurrentEllipse.mError)
					{
						temp.mError = mCurrentEllipse.mError;
						temp.mClusterID = idCluster;
					}
				}

			}



		} //if Aggregarion == True


		/// Similarity = dist(ellipse,mKNeighbor[i]) * w_1 +  (1-(ellipse.mNormal*mKNeighbor[i].mNormal)�) * w_2
		///	<Similarity,Ellipse>
		std::map<float,Ellipse> mKNeighbor;


		mKNeighbor = kNeighbor(ellipse,k);

		for (int i = 0; i < mKNeighbor.size() ; ++i)
		{
			// Se n�o estiver em um cluster ou seu costo do novo caminho desde a semente � melhor
			if( (mKNeighbor[i].second.mLastClusterID != idCluster) || (mKNeighbor[i].first < mKNeighbor[i].second.mLastClusterCost) )
			{
				// Se custo for melhor que um Threshold , poe na lista aberto para futura expanssao
				if (mKNeighbor[i].first < MAX_COST)
				{
					mKNeighbor[i].second.mLastClusterCost = mKNeighbor[i].first;
					mKNeighbor[i].second.mLastClusterID   = idCluster;
					open.insert(mKNeighbor[i]);
				// Senao acrescenta-o a  lista de semente
				}else
				{

					if( mKNeighbor[i].second.mLastClusterID == -1)
					{
						ListSeed.append(mKNeighbor[i].second);
					}

				}


			}
		}




	}// End While

	//
	if( close.size() > 0 )
	{
		if( BIGELLIPSE )
		{
			close.insert(mCurrentEllipse);
			mCurrentEllipse = MakeEllipse(close);
		}
		else
		{
			mCurrentEllipse = MakeEllipse(close);
		}

		if ( mCurrentEllipse.mError > MAX_ERROR )
		{
			while ( close.size() > 0)
			{
				temp = close.pop();
				if (temp.mClusterID == -1)
				{
					ListSeed.append(temp);
				}
			}

		}
		else // mCurrentEllipse.mError < MAX_ERROR
		{

			while ( close.size() > 0)
			{
				Cluster.append(close);
				temp = close.pop();
				if (temp.mError > mCurrentEllipse.mError)
				{
					temp.mError = mCurrentEllipse.mError;
					temp.mClusterID = idCluster;
				}
			}

		}

	}

}



int main()
{

	Ellipse seed;

	std::list<Ellipse> ListSeed;

	ListSeed.append(seed);

	while (ListSeed.size() > 0)
	{
		Ellipse currentSeed = ListSeed.pop();
		if ( currentSeed.mClusterID == -1)
		{
			SeedExpansion(currentSeed,getNextID());
		}

	}

	return 0;
}
