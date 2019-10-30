#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <list>
#include <cmath>

using namespace std;


typedef pair<long long,long long> range;
struct Range{
    range r;
    int amountOfStations;

    Range(range r, int amountOfStations) : r(std::move(r)), amountOfStations(amountOfStations) {}

    long long size(){
        return (abs(r.first - r.second) + 1) * amountOfStations;
    }

    friend ostream &operator<<(ostream &os, const Range &range1) {
        os << range1.r.first << " - " << range1.r.second << " = " << to_string(range1.amountOfStations) << endl;
        return os;
    }
};


list<Range> getStationRanges(const vector<range>& ranges){
    // sort Xs and Ys
    vector<int> rangesXs;
    rangesXs.resize(ranges.size());

    vector<int> rangesYs;
    rangesYs.resize(ranges.size());

    for(unsigned long i= 0; i < ranges.size();i++){
        rangesXs[i] = ranges[i].first;
        rangesYs[i] = ranges[i].second;
    }

    sort(rangesXs.begin(), rangesXs.end());
    sort(rangesYs.begin(), rangesYs.end());

    // create ranges

    int currentX = 0;
    int currentY = 0;
    int open = 0;
    long long last;

    list<Range> stationRanges;
    while(currentX < ranges.size() || currentY < ranges.size()) {
        long long currentXElement;
        if (currentX < rangesXs.size()) {
            currentXElement = rangesXs[currentX];
        }else{
            currentXElement = INT64_MAX;
        }

        long long currentYElement;
        if (currentY < rangesYs.size()) {
            currentYElement = rangesYs[currentY];
        }else{
            currentYElement = INT64_MAX;
        }



        if(currentXElement < currentYElement){
            if(open > 0) {
                stationRanges.push_back({{last, currentXElement}, open});
            }
            last = currentXElement;
            open++;
            currentX++;

        }else{
            stationRanges.push_back({{last, currentYElement}, open});
            last = currentYElement;
            open--;
            currentY++;
        }
    }
    return stationRanges;

}

long long getRoomNumber(long long friendsRoom, const list<Range>& stationRanges){
    auto it = stationRanges.begin();
    long long& room = friendsRoom;
    long long roomNumber;

    while(true){
        Range r = *it;
        long long tmp = room;
        room -= r.size();
        if(room <= 0){
            room = tmp;
            roomNumber = (long long) (r.r.first) + (long long)floor(room / r.amountOfStations);
            break;
        }
        advance(it,1);
    }
    return roomNumber;
}


vector<long long> getRoomNumbers(vector<long long> friendsRooms, const list<Range>& stationRanges){
    vector<long long> result;
    result.resize(friendsRooms.size());

    for(unsigned long i = 0; i < friendsRooms.size(); i++){
        result[i] = getRoomNumber(friendsRooms[i],stationRanges);
    }
    return result;
}

int main() {
    long long room = 5;
    range r1 (6, 10);
    range r2 (9,12);
    range r3 (4,8);
    vector<range> ranges {r1, r2, r3};
    vector<long long> friendRooms {3, 7, 9, 1};
    list<Range> stationRanges = getStationRanges(ranges);
    for(Range r: stationRanges) cout << r;

    for(long long n: getRoomNumbers(friendRooms,stationRanges)){
        cout << n << endl;
    }



    return 0;
}