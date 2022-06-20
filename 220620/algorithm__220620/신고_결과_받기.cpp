#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>

using namespace std;

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    vector<int>answer(id_list.size(), 0);
    map<string, int> label;
    map<string, set<string>> attacked;

    for (int idx = 0; idx < id_list.size(); idx++) {
        label[id_list[idx]] = idx;
    }

    for (auto rep : report) {
        stringstream ss(rep);
        string from;
        string to;
        ss >> from >> to;
        attacked[to].insert(from);
    }

    for (auto iter : attacked) {
        if (iter.second.size() >= k) {
            for (auto in_iter : iter.second) {
                answer[label[in_iter]]++;
            }
        }

    }


    return answer;
}