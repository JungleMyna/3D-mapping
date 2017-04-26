/**
* This file is part of ORB-SLAM2.
*
* Copyright (C) 2014-2016 Raúl Mur-Artal <raulmur at unizar dot es> (University of Zaragoza)
* For more information see <https://github.com/raulmur/ORB_SLAM2>
*
* ORB-SLAM2 is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ORB-SLAM2 is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with ORB-SLAM2. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MAP_H
#define MAP_H

#include "MapPoint.h"
#include "KeyFrame.h"
#include <set>

#include <mutex>



namespace ORB_SLAM2
{

class MapPoint;
class KeyFrame;

class Map
{
public:
    Map();

    void AddKeyFrame(KeyFrame* pKF);
    void AddMapPoint(MapPoint* pMP);
    void EraseMapPoint(MapPoint* pMP);
    void EraseKeyFrame(KeyFrame* pKF);

    // cmxlaser:
    void AddsysCheckKeyFrame(KeyFrame* pKF);

    //????    std::list<KeyFrame*> GetsysCheckKeyFrame(KeyFrame* pKF);
    std::list<KeyFrame*> GetsysCheckKeyFrame()
    { // ?
        //unique_lock<mutex> lock(mMutexMap);
        //?
        return sysCheckKeyFrames;
    }

    bool ChecksysNewKeyFrame()
    {
   //unique_lock<mutex> lock(mMutexsysNewKFs);
   return(!sysCheckKeyFrames.empty());
    }


    void CleansysList()
    {

        for (list<KeyFrame*>::iterator i= sysCheckKeyFrames.begin(); i != sysCheckKeyFrames.end(); )
        {
         sysCheckKeyFrames.erase(i++);
        }

        //cout << "CLean key frame 111" << endl;

    }

    void SetReferenceMapPoints(const std::vector<MapPoint*> &vpMPs);

    std::vector<KeyFrame*> GetAllKeyFrames();
    std::vector<MapPoint*> GetAllMapPoints();
    std::vector<MapPoint*> GetReferenceMapPoints();

    long unsigned int MapPointsInMap();
    long unsigned  KeyFramesInMap();

    long unsigned int GetMaxKFid();

    void clear();

    vector<KeyFrame*> mvpKeyFrameOrigins;

    std::mutex mMutexMapUpdate;

    // This avoid that two points are created simultaneously in separate threads (id conflict)
    std::mutex mMutexPointCreation;

protected:
    std::set<MapPoint*> mspMapPoints;
    std::set<KeyFrame*> mspKeyFrames;
   //cmxlaser:
    std::list<KeyFrame*> sysCheckKeyFrames;


    std::vector<MapPoint*> mvpReferenceMapPoints;

    long unsigned int mnMaxKFid;

    std::mutex mMutexsysNewKFs;
    std::mutex mMutexMap;
};

} //namespace ORB_SLAM

#endif // MAP_H