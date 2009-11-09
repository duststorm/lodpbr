/*
 * ClusterRenderLog.cpp
 *
 *  Created on: Nov 4, 2009
 *      Author: fmc
 */

#include "ClusterLog.hpp"

ClusterLog::ClusterLog()
{
	// TODO Auto-generated constructor stub

    mKNeighborsSize 	= 0;
    mSeedIndex 			= 0;
	mSeedRangeBegin 	= 0;
	mSeedRangeEnd		= 0;
	mNumberOfCluster    = 0;
	mClusteIndex		= 0;
	mClusterRangeBegin	= 0;
	mClusterRangeEnd	= 0;

	maskRenderingClusterBy			= ClusterLog::Index;
	maskRenderingClusterWith 		= ClusterLog::GLPointSmooth;

	maskBuildClusterSystem 		= ClusterLog::Continuous;
	maskBuildClusterWith 		= ClusterLog::NormalOnly;
	maskShow					=  0;
}

ClusterLog::~ClusterLog() {
	// TODO Auto-generated destructor stub
}
