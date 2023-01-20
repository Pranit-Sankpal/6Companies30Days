// There is an undirected tree with n nodes labeled from 0 to n - 1, rooted at node 0. You are given a 2D integer array edges of length n - 1 where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.

// At every node i, there is a gate. You are also given an array of even integers amount, where amount[i] represents:

// the price needed to open the gate at node i, if amount[i] is negative, or,
// the cash reward obtained on opening the gate at node i, otherwise.
// The game goes on as follows:

// Initially, Alice is at node 0 and Bob is at node bob.
// At every second, Alice and Bob each move to an adjacent node. Alice moves towards some leaf node, while Bob moves towards node 0.
// For every node along their path, Alice and Bob either spend money to open the gate at that node, or accept the reward. Note that:
// If the gate is already open, no price will be required, nor will there be any cash reward.
// If Alice and Bob reach the node simultaneously, they share the price/reward for opening the gate there. In other words, if the price to open the gate is c, then both Alice and Bob pay c / 2 each. Similarly, if the reward at the gate is c, both of them receive c / 2 each.
// If Alice reaches a leaf node, she stops moving. Similarly, if Bob reaches node 0, he stops moving. Note that these events are independent of each other.
// Return the maximum net income Alice can have if she travels towards the optimal leaf node.

 

// Example 1:


// Input: edges = [[0,1],[1,2],[1,3],[3,4]], bob = 3, amount = [-2,4,2,-4,6]
// Output: 6
// Explanation: 
// The above diagram represents the given tree. The game goes as follows:
// - Alice is initially on node 0, Bob on node 3. They open the gates of their respective nodes.
//   Alice's net income is now -2.
// - Both Alice and Bob move to node 1. 
//   Since they reach here simultaneously, they open the gate together and share the reward.
//   Alice's net income becomes -2 + (4 / 2) = 0.
// - Alice moves on to node 3. Since Bob already opened its gate, Alice's income remains unchanged.
//   Bob moves on to node 0, and stops moving.
// - Alice moves on to node 4 and opens the gate there. Her net income becomes 0 + 6 = 6.
// Now, neither Alice nor Bob can make any further moves, and the game ends.
// It is not possible for Alice to get a higher net income.
// Example 2:


// Input: edges = [[0,1]], bob = 1, amount = [-7280,2350]
// Output: -7280
// Explanation: 
// Alice follows the path 0->1 whereas Bob follows the path 1->0.
// Thus, Alice opens the gate at node 0 only. Hence, her net income is -7280. 
 

// Constraints:

// 2 <= n <= 105
// edges.length == n - 1
// edges[i].length == 2
// 0 <= ai, bi < n
// ai != bi
// edges represents a valid tree.
// 1 <= bob < n
// amount.length == n
// amount[i] is an even integer in the range [-104, 104].


////////////////////////CODE C++/////////////////////////////////////////

class Solution
{
public:
    int MAX_EDGES = 1e5;

    vector<int> find_bob_path(vector<vector<int>> &g, int bob, int parent)
    {
        if (bob == 0)
            return {0};
        for (int child : g[bob])
        {
            if (child != parent)
            {
                vector<int> curr = find_bob_path(g, child, bob);
                if (!curr.empty())
                {
                    curr.push_back(bob);
                    return curr;
                }
            }
        }
        return {};
    }

    int simulate(vector<vector<int>> &g, vector<bool> &gate_opened, vector<int> &amount, int alice, int parent, vector<int> &bob_path, int time)
    {
        if (g[alice].size() == 1 && g[alice][0] == parent)
            return gate_opened[alice] ? 0 : amount[alice]; // reached a leaf node.
        int bob_pos = min(time, (int)bob_path.size() - 1);
        int bob = bob_path[bob_pos];
        int cost_alice = (gate_opened[alice] ? 0 : amount[alice]);
        if (bob == alice)
            cost_alice /= 2;
        int res = INT_MIN;
        // cout << "visited: " << alice << endl;
        // cout << "bob: " << bob << endl;
        gate_opened[alice] = true;
        gate_opened[bob] = true;
        for (int child : g[alice])
        {
            if (child != parent)
            {
                // cout << "visiting: " << child << endl << endl;
                int cost = simulate(g, gate_opened, amount, child, alice, bob_path, time + 1);
                res = max(res, cost + cost_alice);
            }
        }
        gate_opened[alice] = false;
        gate_opened[bob] = false;
        return res;
    }

    int mostProfitablePath(vector<vector<int>> &edges, int bob, vector<int> &amount)
    {
        vector<vector<int>> g(MAX_EDGES);
        vector<bool> gate_opened(MAX_EDGES, false);
        for (vector<int> pair : edges)
        {
            g[pair[0]].push_back(pair[1]);
            g[pair[1]].push_back(pair[0]);
        }
        vector<int> bob_path = find_bob_path(g, bob, -1);
        reverse(bob_path.begin(), bob_path.end());
        return simulate(g, gate_opened, amount, 0, -1, bob_path, 0);
    }
};