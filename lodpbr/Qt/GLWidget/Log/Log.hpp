/*
 * ClusterRenderLog.h
 *
 *  Created on: Nov 4, 2009
 *      Author: fmc
 */

#ifndef CLUSTERRENDERLOG_H_
#define CLUSTERRENDERLOG_H_

class Log {
public:

	enum ClusterRender
	{
		SeedRange 		= 0x00001,
		Seedid 			= 0x00002,
		ClusterRange 	= 0x00004,
		ClusterID 		= 0x00004

	};

	enum PointRenderer
	{
		GLPoint  	 		= 0x00001,
		GLPointSmooth 		= 0x00002,
		PyramidSplat		= 0x00003,
		EWASplat		 	= 0x00004,

	};

	ClusterRenderLog();
	virtual ~ClusterRenderLog();
private:
	std::size_t mSeedid;
	std::size_t mSeedRangeBegin;
	std::size_t mSeedRangeEnd;
	std::size_t mClusteID;
	std::size_t mClusteRangeBegin;
	std::size_t mClusteRrangeEnd;
};

#endif /* CLUSTERRENDERLOG_H_ */
