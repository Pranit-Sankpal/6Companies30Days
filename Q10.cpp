// Given an integer array nums, you need to find one continuous subarray that if you only sort this subarray in ascending order, then the whole array will be sorted in ascending order.

//                                                                                                                               Return the shortest such subarray and output its length.

//                                                                                                                               Example 1 :

//     Input : nums = [ 2, 6, 4, 8, 10, 9, 15 ] Output : 5 Explanation : You need to sort[6, 4, 8, 10, 9] in ascending order to make the whole array sorted in ascending order.Example 2 :

//     Input : nums = [ 1, 2, 3, 4 ] Output : 0 Example 3 :

//     Input : nums = [1] Output : 0

//                    Constraints :

//                    1 <= nums.length <= 104 - 105 <=
//                    nums[i] <= 105

class Solution
{
public:
    int findUnsortedSubarray(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> nums1;
        int ind1 = -1, ind2 = -1; // ind1->first unmatching,ind2->last unmatching
        for (int x : nums)
            nums1.push_back(x);
        sort(nums1.begin(), nums1.end());
        for (int i = 0; i < n; i++)
        {
            if (nums[i] != nums1[i])
            {
                ind1 = i;
                break;
            }
        }
        for (int j = n - 1; j >= 0; j--)
        {
            if (nums1[j] != nums[j])
            {
                ind2 = j;
                break;
            }
        }
        if (ind1 == -1 or ind2 == -1) // condition if array is sorted
            return 0;
        return ind2 - ind1 + 1; // else returning length of window
    }
};