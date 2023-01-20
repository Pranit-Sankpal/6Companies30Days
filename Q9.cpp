// 2426. Number of Pairs Satisfying Inequality
//         Hard 353 6 Companies
//             You are given two 0 -
//     indexed integer arrays nums1 and nums2,
//     each of size n, and an integer diff.Find the number of pairs(i, j)
// such that :

//         0 <= i < j <= n - 1 and
//     nums1[i] - nums1[j] <= nums2[i] - nums2[j] + diff.Return the number of pairs that satisfy the conditions.

//                                                  Example 1 :

//     Input : nums1 = [ 3, 2, 5 ],
//             nums2 = [ 2, 2, 1 ], diff = 1 Output : 3 Explanation : There are 3 pairs that satisfy the conditions : 1. i = 0, j = 1 : 3 - 2 <= 2 - 2 + 1. Since i < j and 1 <= 1, this pair satisfies the conditions.2. i = 0, j = 2 : 3 - 5 <= 2 - 1 + 1. Since i < j and -2 <= 2, this pair satisfies the conditions.3. i = 1, j = 2 : 2 - 5 <= 2 - 1 + 1. Since i < j and -3 <= 2, this pair satisfies the conditions.Therefore, we return 3. Example 2 :

//     Input : nums1 = [ 3, -1 ],
//             nums2 = [ -2, 2 ], diff = -1 Output : 0 Explanation : Since there does not exist any pair that satisfies the conditions, we return 0.

//                                                                                                                                          Constraints :

//     n == nums1.length == nums2.length 2 <= n <= 105 - 104 <= nums1[i],
//             nums2[i] <= 104 - 104 <= diff <= 104

class Solution
{
public:
    long long int count;

    void checkCount(vector<int> &nums, int start, int mid, int end, int d)
    {

        int l = start, r = mid + 1;
        while (l <= mid && r <= end)
        {
            if (nums[l] <= (nums[r] + d)) // if (nums[l]<=nums[r]+d) then all values from nums[r] to nums[end] will be be having their summation with d greater than or equal to nums[l]
            {
                count += (end - r + 1);
                l++;
            }
            else // otherwise we need to increment r so that we can find match for nums[l]
            {
                r++;
            }
        }
        // sort all values from start to end
        sort(nums.begin() + start, nums.begin() + end + 1); // (Sort using two-pointers for better time complexity)
        return;
    }
    void mergeSort(vector<int> &nums, int start, int end, int d)
    {
        if (start == end)
            return;

        int mid = (start + end) / 2;
        mergeSort(nums, start, mid, d);
        mergeSort(nums, mid + 1, end, d);

        checkCount(nums, start, mid, end, d);
        return;
    }
    long long numberOfPairs(vector<int> &a, vector<int> &b, int d)
    {
        count = 0;
        int n = a.size();
        vector<int> c(n);

        for (int i = 0; i < n; i++)
            c[i] = a[i] - b[i];

        mergeSort(c, 0, n - 1, d);

        return count;
    }
};