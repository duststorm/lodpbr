/*
 * ClusterRenderLog.h
 *
 *  Created on: Nov 4, 2009
 *      Author: fmc
 */

#ifndef CLUSTERRENDERLOG_H_
#define CLUSTERRENDERLOG_H_

class ClusterLog {
public:

	enum Show
	{
		Seed		= 1 << 0,
		Cluster		= 1 << 2
	};

	enum RenderingClusterBy
	{
		Range 			= 1 << 3,
		ID 				= 1 << 4,
		All				= 1 << 5,

	};

	enum RenderingClusterWith
	{
		GLPoint  	 		= 1 << 6,
		GLPointSmooth 		= 1 << 7,
		PyramidSplat		= 1 << 8,
		EWASplat		 	= 1 << 9
	};

	enum BuildClusterWith
	{
		// Heuristics
		NormalOnly				= 1 << 10,
		// Total size
		AllPossibleCluster 		= 1 << 11,
		LimitedNumberOfCluster  = 1 << 12
	};



	ClusterLog();

    virtual ~ClusterLog();


private:

    std::size_t mRenderingClusterBy;
    std::size_t mRenderingClusterWith;
    std::size_t mBuldingClusterWith;

    std::size_t mShow;
    std::size_t	mKNeighborsSize;
    std::size_t mSeedID;
	std::size_t mNumberOfCluster;
	std::size_t mSeedRangeBegin;
	std::size_t mSeedRangeEnd;
	std::size_t mClusteID;
	std::size_t mClusterRangeBegin;
	std::size_t mClusterRangeEnd;
};

#endif /* CLUSTERRENDERLOG_H_ */
