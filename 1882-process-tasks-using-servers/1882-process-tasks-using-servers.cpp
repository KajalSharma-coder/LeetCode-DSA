
class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        int n = servers.size();
        int m = tasks.size();

        priority_queue<pair<int, int>, vector<pair<int, int>>,
                       greater<pair<int, int>>>
            freeServers;

        priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                       greater<pair<long long, int>>>
            busyServers;

        for (int i = 0; i < n; i++) {
            freeServers.push({servers[i], i});
        }

        vector<int> ans;
        long long time = 0;

        for (int i = 0; i < m; i++) {
            time = max(time, (long long)i);

            while (!busyServers.empty() && busyServers.top().first <= time) {

                int idx = busyServers.top().second;
                busyServers.pop();

                freeServers.push({servers[idx], idx});
            }
            if (freeServers.empty()) {
                time = busyServers.top().first;

                while (!busyServers.empty() &&
                       busyServers.top().first <= time) {

                    int idx = busyServers.top().second;
                    busyServers.pop();

                    freeServers.push({servers[idx], idx});
                }
            }

            auto [weight, idx] = freeServers.top();
            freeServers.pop();

            ans.push_back(idx);

            busyServers.push({time + tasks[i], idx});
        }

        return ans;
    }
};
