# include <iostream>
# include <vector>
# include <unordered_set>
# include <set>
# include <unordered_map>
# include <stack>
# include <queue>
# include <math.h>
# include <string>
# include<algorithm>
using namespace std;
// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
/*
 * 206. 反转链表
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* pre = nullptr;
        ListNode* cur = head;
        while (cur != nullptr) {
            ListNode* headnext = cur->next;
            cur->next = pre;
            pre = cur;
            cur = headnext;
        }
        return pre;
    }
};
/*
 * 92. 反转链表 II
 */
class Solution {
public:
    void revserse(ListNode* head) {
        ListNode *pre = nullptr; // *pre == *start
        ListNode *cur = head;
        while (cur != nullptr) {
            ListNode* next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
    }
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* start = dummy;
        start->next = head;
        for (int i = 0; i < left - 1; i++) {
            start = start->next;
        }
        ListNode* end_in = start;
        for (int i = 0; i < right - left + 1; i++) {
            end_in = end_in->next;
        }
        ListNode* end = end_in->next;
        ListNode* start_in = start->next;
        start->next = nullptr;
        end_in->next = nullptr;
        revserse(start_in);
        start->next = end_in;
        start_in->next = end;
        return dummy->next;
    }
};
/*
 * 234. 回文链表
 * 就是该把反转链表写成个函数来用，至于能否找到中间值，就要看需不需要用虚拟头结点，用的话自然会向前一位
 */
class Solution {
public:
    void reverse(ListNode* head) {
        ListNode* pre = head;
        ListNode* tmp = nullptr;
        while (pre != nullptr) {
            ListNode* next = pre->next;
            pre->next = tmp;
            tmp = pre;
            pre = next;
        }
    }
    bool isPalindrome(ListNode* head) {
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* slow = dummy;
        ListNode* start = head;
        ListNode* fast = dummy;
        // 从虚拟头结点开始而不是头结点
        while(fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        if (fast) {
            ListNode* end_in = slow;
            ListNode* start_out = slow->next; // 偶数
            slow->next = nullptr;
            reverse(start);
            while(start_out) {
                if (start_out->val != end_in->val) return false;
                start_out = start_out->next;
                end_in = end_in->next;
            }
            return true;
        }
        else {
            ListNode* end_in = slow;
            ListNode* start_out = slow->next; // 奇数
            slow->next = nullptr;
            reverse(start);
            end_in = end_in->next; // 因为中间多了一个
            while(start_out) {
                if (start_out->val != end_in->val) return false;
                start_out = start_out->next;
                end_in = end_in->next;
            }
            return true;
        }
    }
};
/*
 * 24. 两两交换链表中的节点
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* dummyHead = new ListNode(0); // 设置一个虚拟头结点
        dummyHead->next = head; // 将虚拟头结点指向head，这样方面后面做删除操作
        ListNode* cur = dummyHead;
        while(cur->next != nullptr && cur->next->next != nullptr) {
            ListNode* tmp = cur->next; // 记录临时节点
            ListNode* tmp1 = cur->next->next->next; // 记录临时节点
            cur->next = cur->next->next;    // 步骤一
            cur->next->next = tmp;          // 步骤二
            cur->next->next->next = tmp1;   // 步骤三
            cur = cur->next->next; // cur移动两位，准备下一轮交换
        }
        return dummyHead->next;
    }
};
/*
 * 61. 旋转链表
 * 嗨嗨嗨 成环的特殊用例全给他提前判断出来 
 */
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        int count = 0;
        ListNode* cur = head;
        while (cur != nullptr) {
            count++;
            cur = cur->next;
        }
        if (count == 0 || count == 1 || k == 0 || k == count) return head;
        int num = count - (k % count);
        if (num == count) return head;
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* pre = dummy->next;
        while(num) {
            dummy = dummy->next;
            num--;
        }
        ListNode* start_o = dummy->next;
        dummy->next = nullptr;
        ListNode* end_o = start_o;
        while (end_o->next != nullptr) end_o = end_o->next;
        end_o->next = pre;
        return start_o;
    }
};