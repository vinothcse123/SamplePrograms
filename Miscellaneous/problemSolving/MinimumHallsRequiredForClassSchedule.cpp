#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using std::vector;
using std::cout;
using std::string;

void demoFunction1()
{

}

int main()
{
    std::vector<std::pair<int,int>> meetingTimeVec = {{10,13},{11,15},{20,21},{12,17}};

    std::vector<std::pair<int,int>> timeVec;

    for(const std::pair<int,int> &meetingTimePair : meetingTimeVec)
    {
        timeVec.push_back({meetingTimePair.first,1});
        timeVec.push_back({meetingTimePair.second,-1});
    }

    std::sort(timeVec.begin(),timeVec.end(),[](const std::pair<int,int> &timeVec1,const std::pair<int,int> &timeVec2){
        return timeVec1.first < timeVec2.first;
    });

    int maxRoomRequired=0,currentRoomSize=0;


    for(const std::pair<int,int> &timePair : timeVec)
    {
        currentRoomSize += timePair.second;
        maxRoomRequired = std::max(currentRoomSize,maxRoomRequired);
        cout<< "Result :" << maxRoomRequired << '\n';	
    }

    return 0;
}
