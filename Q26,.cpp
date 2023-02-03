// 2260. Minimum Consecutive Cards to Pick Up
//     Medium 603 17 Companies
//         You are given an integer array cards where cards[i] represents the value of the ith card.A pair of cards are matching if the cards have the same value.

//     Return the minimum number of consecutive cards you have to pick up to have a pair of matching cards among the picked cards.If it is impossible to have matching cards,
//     return -1.

class Solution
{
public:
    int minimumCardPickup(vector<int> &cards)
    {

        unordered_map<int, int> m;
        int res = INT_MAX;
        for (int i = 0; i < cards.size(); i++)
        {
            if (m.find(cards[i]) != m.end())
            {
                res = min(res, i - m[cards[i]] + 1);
            }
            m[cards[i]] = i;
        }

        if (res != INT_MAX)
        {
            return res;
        }
        else
            return -1;
    }
};