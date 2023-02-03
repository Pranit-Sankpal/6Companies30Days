// Suppose LeetCode will start its IPO soon.In order to sell a good price of its shares to Venture Capital, LeetCode would like to work on some projects to increase its capital before the IPO.Since it has limited resources, it can only finish at most k distinct projects before the IPO.Help LeetCode design the best way to maximize its total capital after finishing at most k distinct projects.

//  You are given n projects where the ith project has a pure profit profits[i] and a minimum capital of capital[i] is needed to start it.

// Initially,you have w capital.When you finish a project, you will obtain its pure profit and the profit will be added to your total capital.
// Pick a list of at most k distinct projects from given projects to maximize your final capital,and return the final maximized capital.
// The answer is guaranteed to fit in a 32 - bit signed integer.

class Solution
{
public:
    int findMaximizedCapital(int k, int w, vector<int> &profits, vector<int> &capital)
    {
        vector<pair<int, int>> arr;
        for (int i = 0; i < profits.size(); i++)
            arr.push_back({capital[i], profits[i]});
        sort(arr.begin(), arr.end());

        priority_queue<int> q;
        int ans = 0, i = 0;
        while (i < arr.size() and k)
        {
            if (w >= arr[i].first)
                q.push(arr[i++].second);
            else
            {
                if (q.empty())
                    return w;

                w += q.top();
                q.pop();
                k--;
            }
        }
        while (k-- and !q.empty())
        {
            w += q.top();
            q.pop();
        }
        return w;
    }
};