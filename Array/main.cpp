#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;


class Solution {
public:
    /**
     * Array. 移动零
     */
//    void moveZeroes(vector<int> nums) {
//        int k = 0;      // nums[0, k) 为非零元素
//
//        for (int i = 0; i < nums.size(); i ++)
//            if (nums[i])
//                nums[k++] = nums[i];
//
//        while (k < nums.size()) {
//            nums[k++] = 0;
//        }
//    }
    void moveZeroes(vector<int>& nums) {
        int k = 0;      // nums[0, k) 为非零元素

        for (int i = 0; i < nums.size(); i ++)
            if (nums[i])
                if (i != k)
                    swap(nums[k++], nums[i]);
                else
                    k ++;

    }


    /**
     * 209. 长度最小的子数组
     */
    //  滑动窗口        O(n)
    int minSubArrayLen(int target, vector<int>& nums) {
        int l = 0, r = -1;   // [l, r]
        int sum = 0, res = nums.size() + 1;

        while (l < nums.size()) {
            if (sum < target && r + 1 < nums.size() )
                sum += nums[++r];
            else
                sum -= nums[l++];

            if (sum >= target)
                res = min(res, r - l +1);

        }

        return res == nums.size() + 1 ? 0 : res;

    }


    /**
     * 167. 两数之和 II - 输入有序数组
     */
    // 思路一：以二分搜索去寻找另一个加数的索引。                    O(log n)
    // 思路二：对撞指针，分别从两边往中间去查询(前提是有序数组)。      O(n)
    vector<int> twoSum(vector<int>& numbers, int target) {
        int l = 0, r = numbers.size() - 1;

        while (l < r) {
            if (numbers[l] + numbers[r] < target) {
                l ++;
            } else if (numbers[l] + numbers[r] > target) {
                r --;
            } else {
                int res[2] = {l + 1, r + 1};
                return vector<int>(res, res + 2);
            }
        }

        throw invalid_argument("The input has no solution.");
    }



    /**
     * 75. 颜色分类
     */
    // 三路快排思想: 仅有0， 1， 2 三种值
    void sortColors(vector<int>& nums) {
        int l = 0, r = nums.size() - 1, p;

//        p = l + (r - l) / 2;    // 以中间值为基值
//        swap(nums[p], nums[l]);

        int i = l -1, j = l - 1, k = r + 1, m = l;            // [l, i] = 0, [i+1, j] = 1, [k, r] = 2;
        while (m < k) {
            assert( nums[m] >=0 && nums[m] <= 2);
            if (nums[m] < 1) {
                swap(nums[++i], nums[m]);
                j ++;
                m ++;
            } else if (nums[m] == 1) {
                j ++;
                m ++;
            } else {
                swap(nums[--k], nums[m]);
            }
        }
    }


    /**
     * 3. 无重复字符的最长子串
     */
    //  滑动窗口        O(n)
    int lengthOfLongestSubstring(string s) {

        int freq[256] = {0};
        int l = 0, r = -1; // [l, r]
        int res = 0;

        while (l < s.size()) {
            if (r + 1 < s.size() && freq[s[r + 1]] == 0)
                freq[s[++r]] = 1;
            else
                freq[s[l++]] = 0;

            res = max(res, r - l +1);
        }
        return res;
    }


    /**
     *  88. 合并两个有序数组
     *  与归并排序中的合并的思路一致
     */
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if (m == 0) {
            nums1 = nums2;
            return;
        }
        if (n == 0) return;

        vector<int> temp(m);
        for (int i = 0; i < m; i ++) temp[i] = (nums1[i]);

        if (nums2[0] > nums1[m-1]) {
            for (int i = m; i < m+n; i ++)
                nums1[i] = nums2[i-m];
            return;
        }

        int l = 0, r = 0, i = 0;
        while (l < m && r < n) {
            if (temp[l] < nums2[r]) {
                nums1[i++] = temp[l++];
            } else {
                nums1[i++] = nums2[r++];
            }
        }


        while (l < m)   nums1[i++] = temp[l++];
        while (r < n)   nums1[i++] = nums2[r++];

    }


    /**
     * 215. 数组中的第K个最大元素
     * 一：快排里面的partition过程中，每次partition返回的索引是定下来的，即每次都找到了 第 索引+1 小的值
     * 二：根据最大堆和最小堆特性，最大堆可以选 第 k 最小的值(堆内是前k小的值)，最小堆可以选 第 k 最大的值(堆内是最大的k个值)
     */
    int findKthLargest(vector<int>& nums, int k) {
        //  这里采用最小堆
        priority_queue<int, vector<int>, greater<>> minHeap;
        for (int i = 0;i < k; i ++) minHeap.push(nums[i]);

        for (int i = k; i < nums.size(); i ++) {
            if (nums[i] > minHeap.top()) {
                minHeap.pop();
                minHeap.push(nums[i]);
            }
        }

        return minHeap.top();
    }


    /**
     * 125. 验证回文串
     * 这里采用双指针的做法
     */
    bool isPalindrome(string s) {
        if (s.size() == 0) return true;
        int l = 0, r = s.size()-1;

        //  去除 s 开头的 不合法字符
        //  测试表明这样预处理，比在while循环体内部的比较中加入判定条件 会得到更高的效率
        while(l <= r && !isValidChar(s[l])) l ++;

        //  [l ~ r] 这个区间中比较
        while (l <= r) {
            while (l <= r && !isValidChar(s[l])) l++;
            while (l <= r && !isValidChar(s[r])) r--;

            if (tolower(s[l]) != tolower(s[r]))
                return false;

            l ++;
            r --;
        }
        return true;
    }



    /**
     * 11. 盛最多水的容器
     * 一： 采用双指针的思路，同时在调整指针的考虑就是贪心的思想
     */
    int maxArea(vector<int>& height) {
        int l = 0, r = height.size() - 1, res = 0;

        // [l, ... r] 区间 不断调整更高的木板
        while (l < r) {
            res = max(res, (r-l) * min(height[l], height[r]));

            if (height[l] < height[r]) l ++;
            else r --;
        }

        return res;
    }

private:
    bool isValidChar (char c) {
        return c >= '0' && c <= '9' && c >= 'A' && c <= 'Z' && c >= 'a' && c <= 'z';
    }


public:
    /**
     * 438. 找到字符串中所有字母异位词
     * 滑动窗口
     */
    vector<int> findAnagrams(string s, string p) {
        if(s.size()<p.size()) return {};

        vector<int> freq_s(26, 0), freq_p(26, 0), res;
        int l = 0, r = -1;

        //  初始化目标词频 及 窗口词频
        for(char c : p){
            freq_p[c - 'a' ]++;
            freq_s[s[++r] - 'a' ]++;
        }

        if ( freq_s == freq_p ) res.push_back( l );

        //  维护滑动窗口
        while( r < s.size()-1 ){
            freq_s[s[++r] - 'a' ]++;
            freq_s[s[l++] - 'a' ]--;
            if ( freq_s == freq_p )
                res.push_back( l );
        }
        return res;
    }
};

int main() {

    auto *s = new Solution();
    vector<int> t = s->findAnagrams("cbaebabacd","abc");
    for (int n: t) cout << n <<endl;

    return 0;
}
