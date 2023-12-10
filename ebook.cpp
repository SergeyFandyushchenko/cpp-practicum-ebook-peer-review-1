#include <iostream>
#include <iomanip>
#include <cstdint>
#include <numeric>
#include <map>
#include <unordered_map>

using namespace std;

class Assistant {
public:
    Assistant() = default;

    void Read(int user, int page) {
        if(users_.count(user)) {
            int prev_page = users_.at(user);
            if(pages_.at(prev_page) == 1) {
                pages_.erase(prev_page);
            }
            else {
                pages_.at(prev_page) -= 1;
            }
        }
        users_[user] = page;
        pages_[page] += 1;
    }

    double Cheer(int user) {
        if(users_.count(user) == 0) {
            return 0.;
        }
        if(users_.size() == 1) {
            return 1.;
        }

        return accumulate(pages_.begin(), pages_.find(users_.at(user)), 0, [](int prev_sum, const pair<int, int>& p) {
            return prev_sum + p.second;
        }) / static_cast<double>(users_.size() - 1);
    }

private:
    unordered_map<int, int> users_; // <user_id, page>
    map<int, int> pages_; // <page, <amount users>
};

int main()
{
    Assistant assistant;

    int query_count;
    cin >> query_count;
    for(int i = 0; i < query_count; ++i) {
        string command;
        int user;
        cin >> command >> user;
        if(command == "READ"s) {
            int  page;
            cin >> page;
            assistant.Read(user, page);
            continue;
        }
        if(command == "CHEER"s) {
            cout << setprecision(6) << assistant.Cheer(user) << endl;
        }
    }
    return 0;
}
