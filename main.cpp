#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;


typedef pair<long long,long long> range;
struct Range{
    range r;
    int amountOfStations;

    Range(range r, int amountOfStations) : r(std::move(r)), amountOfStations(amountOfStations) {}

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
            currentXElement = INT32_MAX;
        }

        long long currentYElement;
        if (currentY < rangesYs.size()) {
            currentYElement = rangesYs[currentY];
        }else{
            currentYElement = INT32_MAX;
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
int main() {

    range r1 (3, 18);
    range r2 (50,100);
    range r3 (22,51);

    vector<range> ranges {r1,r2,r3};




    return 0;
}