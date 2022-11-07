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
 * 25. K 个一组翻转链表
 * 反转链表就该写成函数
 */
class Solution {
private:
    ListNode* reverse(ListNode* head) {
        ListNode* tmp = nullptr;
        while (head != nullptr) {
            ListNode* next = head->next;
            head->next = tmp;
            tmp = head;
            head = next; 
        }
        return tmp;
    }
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* pre = dummy;
        ListNode* end = dummy;
        while (head->next != nullptr) {
            for (int i = 0; i < k && end != nullptr; i++) end = end->next;
            if (end == nullptr) break;
            ListNode* start = pre->next;
            ListNode* next = end->next;
            end->next = nullptr;
            pre->next = reverse(start);
            start->next = next;
            pre = start;
            end = pre;
        }
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
    bool isPailndrome(ListNode* head) {
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
        if (count == 0 || count == 1 || k == 0 || k == count) return head; // 特殊情况
        int num = count - (k % count);
        if (num == count) return head; // 特殊情况
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
/*
 * 面试题 02.05. 链表求和
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int sum = 0, carry = 0; // sum是两数之和，carry是进位
        ListNode* head = new ListNode(-1); // 新的节点用来连接结果
        ListNode* pre = head; // 用来最后输出的头结点，因为head会一直走到后面去了
        while (l1 || l2 || carry) {
            sum = 0;
            if (l1 != NULL) {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2 != NULL) {
                sum += l2->val;
                l2 = l2->next;
            }
            // 数之和 + 进位
            sum += carry;
            ListNode* tmp = new ListNode(sum % 10); // 取余数作为当前链表节点数
            carry = sum / 10; // 计算进位
            head->next = tmp; // 结果链表向后连接
            head = head->next;
        }
        return pre->next; // 输出结果链表头结点
    }
};
/*
 * 83. 删除排序链表中的重复元素（删掉重复的部分，保留最少一个）
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr) return head;
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        while (head->next != nullptr) {
            ListNode* next = head->next;
            if (head->val == next->val) head->next = next->next;
            else head = head->next;
        }
        return dummy->next;
    }
};
/*
 * 82. 删除排序链表中的重复元素 II（只要是重复元素就都删除）
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        ListNode* preHead = new ListNode(0);
        preHead->next = head;
        
        ListNode* pre = preHead;
        ListNode* cur = head;
        while (cur) {
            //跳过当前的重复节点，使得cur指向当前重复元素的最后一个位置
            while (cur->next && cur->val == cur->next->val) {
                cur = cur->next;
            }
            if (pre->next == cur) {
                //pre和cur之间没有重复节点，pre后移
                pre = pre->next; 
            } else {
                //pre->next指向cur的下一个位置（相当于跳过了当前的重复元素）
                //但是pre不移动，仍然指向已经遍历的链表结尾
                pre->next = cur->next;
            }
            cur = cur->next;
        }
        return preHead->next;
    }
};
/*
 * 141. 环形链表
 * 套圈问题，慢指针一步快指针两步，最后相遇就是环形
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (head == nullptr || head->next == nullptr || head->next == nullptr) {
            return false;
        }
        ListNode* slow = head;
        ListNode* fast = head->next;
        while (slow != fast) {
            if (fast == nullptr || fast->next == nullptr || fast->next->next == nullptr) {
                return false;
            }
            slow = slow->next;
            fast = fast->next->next;
        }
        return true;
    }
};
/*
 * 142. 环形链表 II
 * 套圈问题，慢指针一步快指针两步，最后相遇就是环形.相遇后，从头结点和相遇节点同时开始，相遇位置是环形入口
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                ListNode* index1 = head;
                ListNode* index2 = fast;
                while (index1 != index2) {
                    index1 = index1->next;
                    index2 = index2->next;
                }
                return index1;
            }
        }
        return NULL;
    }
};
/*
 * 剑指 Offer 22. 链表中倒数第k个节点
 * 先遍历统计节点总数，然后 sum-k 往后走几步就行了
 */
class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        struct ListNode listnew(-1);
        ListNode* dummyHead = & listnew;
        dummyHead->next = head;
        int num = 1;
        while (head != NULL) {
            head = head->next;
            num++;
        } 
        for (int i = 0; i < num - k; i++) {
            dummyHead = dummyHead->next;
        }
        return dummyHead;
    }
};
/*
 * 19. 删除链表的倒数第 N 个结点
 * 快慢指针，找到要删除的节点，连接其next就行
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummyhead = new ListNode(-1);
        dummyhead->next = head;
        ListNode* slow = head;
        ListNode* fast = head;
        if (head == nullptr || head->next == nullptr) return NULL;
        for (int i = 0; i < n; i++) fast = fast->next;
        if (!fast) return head->next;
        while (fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
        cout << slow->val;
        slow->next = slow->next->next;
        return dummyhead->next;
    }
};
/*
 * 21. 合并两个有序链表
 * 边判断边连接
 */
class Solution {
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
 * 23. 合并K个升序链表
 * 归并排序 难呀
 */
class Solution {
private:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode* dummy = new ListNode(-1);
    ListNode* pre = dummy;
    if (list1 == nullptr && list2 != nullptr) return list2;
    if (list2 == nullptr && list1 != nullptr) return list1;
    if (list1 == nullptr && list2 == nullptr) return nullptr;
    while (list1 != nullptr && list2 != nullptr) {
        if (list1->val <= list2->val) {
            dummy->next = list1;
            list1 = list1->next;
        }
        else {
            dummy->next = list2;
            list2 = list2->next;
        }
        dummy = dummy->next;
    }
    if (list1 != nullptr) dummy->next = list1;
    if (list2 != nullptr) dummy->next = list2;
    return pre->next;
}
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.size() == 0) return nullptr;
        if (lists.size() == 1) return lists[0];
        if (lists.size() == 2) return mergeTwoLists(lists[0], lists[1]);
        int mid = lists.size() / 2;
        vector<ListNode*> l1(mid);
        for (int i =0; i < mid; i++) {
            l1[i] = lists[i];
        }
        vector<ListNode*> l2(lists.size() - mid);
        for (int i = mid, j =0; i < lists.size(); i++, j++) {
            l2[j] = lists[i];
        }
        return mergeTwoLists(mergeKLists(l1), mergeKLists(l2));
    }
};
/*
 *  牛客 链表的奇偶重排
 */
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        // write code here
        if (head == nullptr) return head;
        ListNode* odd = head; // 奇数
        ListNode* even = head->next; // 偶数
        ListNode* evenH = even;
        while (even != nullptr && even->next != nullptr)
        {
            odd->next = even->next;
            odd = odd->next;
            even->next = odd->next;
            even = even->next;
        }
        odd->next = evenH;
        return head;
    }
};
/*
 *  牛客 链表的偶奇重排
 */
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        // write code here
        if (head == nullptr) return head;
        ListNode* odd = head; // 奇数
        ListNode* even = head->next; // 偶数
        ListNode* oddH = odd; 
        ListNode* evenH = even;
        while (even != nullptr && even->next != nullptr)
        {
            odd->next = even->next;
            odd = odd->next;
            even->next = odd->next;
            even = even->next;
        }
        odd->next = nullptr; // 注意奇数节点的最后一个肯定还连着最后一个偶数节点，所以要断开不然会成环
        even->next = oddH;
        return evenH;
    }
};



