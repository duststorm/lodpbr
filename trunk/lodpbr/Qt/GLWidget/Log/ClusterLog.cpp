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
    mSeedIndex 			= 1;
	mSeedRangeBegin 	= 1;
	mSeedRangeEnd		= 1;
	mNumberOfCluster    = 1;
	mClusteIndex		= 1;
	mClusterRangeBegin	= 1;
	mClusterRangeEnd	= 1;
	mRadius				= 100;

	maskRenderingClusterBy			= ClusterLog::Index;
	maskRenderingClusterWith 		= ClusterLog::GLPointSmooth;

	maskBuildClusterShape 		= ClusterLog::ELLIPTICAL;
	maskBuildClusterWith 		= ClusterLog::NormalOnly;
	maskShow					=  0;
}

ClusterLog::~ClusterLog() {
	// TODO Auto-generated destructor stub
}
