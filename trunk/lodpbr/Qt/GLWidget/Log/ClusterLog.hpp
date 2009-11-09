/*
 * ClusterRenderLog.h
 *
 *  Created on: Nov 4, 2009
 *      Author: fmc
 */

#ifndef CLUSTERRENDERLOG_H_
#define CLUSTERRENDERLOG_H_


#include "Qt/Tools/BitMask.hpp"

class ClusterLog {
public:

	enum Show
	{
		Seed		= 1 << 1,
		Cluster		= 1 << 2,
		Model		= 1 << 3
	};

	enum RenderingClusterBy
	{
		Range 			= 1 << 4,
		Index 			= 1 << 5,
		All				= 1 << 6
	};
    enum RenderingClusterWith
    {
		GLPoint 		= 1 << 7,
		GLPointSmooth 	= 1 << 8,
		PyramidSplat 	= 1 << 9,
		EWASplat 		= 1 << 10
    };
    enum BuildClusterWith
    {
    	NormalOnly 				= 1 << 11,
    	AllPossibleCluster 		= 1 << 12,
    	LimitedNumberOfCluster 	= 1 << 13
    };

    enum BuildClusterSystem
	{
    	Continuous    		 = 1 << 14,
    	Interactive			 = 1 << 15
    };

    Bitmask<unsigned int,Show				 > 	maskShow;
    Bitmask<unsigned int,RenderingClusterBy  > 	maskRenderingClusterBy;
    Bitmask<unsigned int,RenderingClusterWith> 	maskRenderingClusterWith;
    Bitmask<unsigned int,BuildClusterWith    >  maskBuildClusterWith;
    Bitmask<unsigned int,BuildClusterSystem  >  maskBuildClusterSystem;

    ClusterLog();

    virtual ~ClusterLog();

    unsigned int getClusteIndex() const
    {
        return mClusteIndex;
    }

    unsigned int getClusterRangeBegin() const
    {
        return mClusterRangeBegin;
    }

    unsigned int getClusterRangeEnd() const
    {
        return mClusterRangeEnd;
    }

    unsigned int getKNeighborsSize() const
    {
        return mKNeighborsSize;
    }

    unsigned int getNumberOfCluster() const
    {
        return mNumberOfCluster;
    }

    unsigned int getSeedIndex() const
    {
        return mSeedIndex;
    }

    unsigned int getSeedRangeBegin() const
    {
        return mSeedRangeBegin;
    }

    unsigned int getSeedRangeEnd() const
    {
        return mSeedRangeEnd;
    }

    void setClusteIndex(unsigned int mClusteIndex)
    {
        this->mClusteIndex = mClusteIndex;
    }

    void setClusterRangeBegin(unsigned int mClusterRangeBegin)
    {
        this->mClusterRangeBegin = mClusterRangeBegin;
    }

    void setClusterRangeEnd(unsigned int mClusterRangeEnd)
    {
        this->mClusterRangeEnd = mClusterRangeEnd;
    }

    void setKNeighborsSize(unsigned int mKNeighborsSize)
    {
        this->mKNeighborsSize = mKNeighborsSize;
    }

    void setNumberOfCluster(unsigned int mNumberOfCluster)
    {
        this->mNumberOfCluster = mNumberOfCluster;
    }

    void setSeedIndex(unsigned int mSeedIndex)
    {
        this->mSeedIndex = mSeedIndex;
    }

    void setSeedRangeBegin(unsigned int mSeedRangeBegin)
    {
        this->mSeedRangeBegin = mSeedRangeBegin;
    }

    void setSeedRangeEnd(unsigned int mSeedRangeEnd)
    {
        this->mSeedRangeEnd = mSeedRangeEnd;
    }



private:

    unsigned int mKNeighborsSize;

    unsigned int mSeedIndex;
	unsigned int mSeedRangeBegin;
	unsigned int mSeedRangeEnd;
	unsigned int mNumberOfCluster;

	unsigned int mClusteIndex;
	unsigned int mClusterRangeBegin;
	unsigned int mClusterRangeEnd;
};

#endif /* CLUSTERRENDERLOG_H_ */
