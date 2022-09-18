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
