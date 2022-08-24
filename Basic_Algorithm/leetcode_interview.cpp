# include <iostream>
# include <vector>
# include <unordered_set>
# include <unordered_map>
# include <stack>
# include <queue>
# include <iostream>
# include <string>
using namespace std;
/*
 * 前缀和(动态数组和)
 */
class easy0_0 {
public:
    vector<int> runningSum(vector<int>& nums) {
        for (auto i = 1; i < nums.size(); ++i) nums[i] += nums[i - 1]; 
        return nums;
    }
};
class easy0_1 {
public:
    vector<int> runningSum(vector<int>& nums) {
        vector<int> res;
        res[0] = nums[0];
        for (auto i = 1; i < nums.size(); ++i) {
            res[i] = res[i] + nums[i];
        }
        return res;
    }
};
/*
 * 724. 寻找数组的中心下标
 */
class easy1_0 {
public:
    int pivotIndex(vector<int>& nums) {
        int sum = 0;
        int left = 0;
        for (auto i : nums) sum += i;
        //cout << sum << endl;
        for (auto i = 0; i < nums.size(); ++i) {
            if (left * 2 + nums[i] == sum) return i;
            left += nums[i];
          //  cout << left << endl;
        }
        return -1;
    }
};
/*
 * 同构数组
 * 双向哈希映射
 */ 
class easy2_0 {
public:
    bool isIsomorphic(string s, string t) {
        unordered_map<char, char> map1;
        unordered_map<char, char> map2;
        for (auto i, j : s, t) {
            map1[i] = j;
            map2[j] = i;
        }
        for (auto i, j : s, t) {
            if (map1[i] != j || map2[j] != i);
            return false;
        }
        return true;
    }
};
/*
 * 合并两个有序链表
 * 这道题是合并链表，通过新建一个链表的头结点（虚拟节点，哨兵节点新建法（也就是虚拟节点的next指向的是头结点））
 * 用新建的头结点来连接合并的链表。这时需要的是一个真实存在的头结点来作为哨兵（虚拟）节点，来产生新链表
 */ 
class easy4_0 {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* prehead = new ListNode(-1); // 构造函数
        ListNode* pre = prehead;
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val <= l2->val) {
                pre->next = l1;
                l1 = l1->next;
            }
            else {
                pre->next = l2;
                l2 = l2->next;
            }
            pre = pre->next;
            
        }
        pre->next = l1 == nullptr ? l2 : l1;
        return prehead->next;
    }
};
/*
 * 翻转链表
 * 这道题是翻转链表，通过新建一个空指针，来进行指向的位置，依次翻转next指针指向
 * 而这里就是和上一题不一样的地方。需要的不是真实存在的节点 而是空区域的指针。一旦用了真实存在节点，链表就会多出一个节点
 * 其实上一题的虚拟头节点也是一样的。因为最后的结果只需要虚拟头节点next的部分，其本身只是为了指向真实头结点的。
 */ 
class easy4_1 {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* pre = nullptr;
        while (head != nullptr) {
            ListNode* next = head->next;
            head->next = pre;
            pre = head;
            head = next;
        }
        return pre;
    }
};