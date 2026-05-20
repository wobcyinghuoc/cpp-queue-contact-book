#include <iostream>
#include <string>
using namespace std;

// 队列最大存储容量
#define MAX_SIZE 30

// 联系人结构体：存储姓名、电话
struct Contact
{
    string name;   // 姓名
    string phone;  // 电话
};

// 循环队列结构体
struct SqQueue
{
    Contact data[MAX_SIZE];  // 存储联系人的数组
    int front;               // 队头下标
    int rear;                // 队尾下标
};

// 1.初始化循环队列
void InitQueue(SqQueue& q)
{
    q.front = 0;
    q.rear = 0;
}

// 2.判断队列是否为空
bool isEmpty(SqQueue& q)
{
    return q.front == q.rear;
}

// 3.判断队列是否已满
bool isFull(SqQueue& q)
{
    return (q.rear + 1) % MAX_SIZE == q.front;
}

// 4.增加联系人（入队）
void addContact(SqQueue& q)
{
    if (isFull(q))
    {
        cout << "通讯录已满，无法添加！" << endl;
        return;
    }
    cout << "请输入联系人姓名：";
    cin >> q.data[q.rear].name;
    cout << "请输入联系电话：";
    cin >> q.data[q.rear].phone;

    // 队尾指针循环后移
    q.rear = (q.rear + 1) % MAX_SIZE;
    cout << "联系人添加成功！" << endl;
}

// 5.查找联系人（按姓名查询）
void searchContact(SqQueue& q)
{
    if (isEmpty(q))
    {
        cout << "暂无联系人信息！" << endl;
        return;
    }
    string name;
    cout << "请输入要查找的姓名：";
    cin >> name;

    // 从队头遍历到队尾
    int i = q.front;
    while (i != q.rear)
    {
        if (q.data[i].name == name)
        {
            cout << "查找成功！姓名：" << q.data[i].name << " 电话：" << q.data[i].phone << endl;
            return;
        }
        i = (i + 1) % MAX_SIZE;
    }
    cout << "未找到该联系人！" << endl;
}

// 6.修改联系人电话
void modifyContact(SqQueue& q)
{
    if (isEmpty(q))
    {
        cout << "暂无联系人信息！" << endl;
        return;
    }
    string name;
    cout << "请输入要修改的姓名：";
    cin >> name;

    int i = q.front;
    while (i != q.rear)
    {
        if (q.data[i].name == name)
        {
            cout << "请输入新的联系电话：";
            cin >> q.data[i].phone;
            cout << "信息修改成功！" << endl;
            return;
        }
        i = (i + 1) % MAX_SIZE;
    }
    cout << "未找到该联系人！" << endl;
}

// 7.删除指定姓名的联系人
void delContact(SqQueue& q)
{
    if (isEmpty(q))
    {
        cout << "暂无联系人信息！" << endl;
        return;
    }
    string name;
    cout << "请输入要删除的姓名：";
    cin >> name;

    // 先找到目标联系人下标
    int i = q.front;
    while (i != q.rear && q.data[i].name != name)
    {
        i = (i + 1) % MAX_SIZE;
    }
    // 遍历完未找到
    if (i == q.rear)
    {
        cout << "未找到该联系人！" << endl;
        return;
    }

    // 后续元素向前覆盖，完成删除
    int j = (i + 1) % MAX_SIZE;
    while (j != q.rear)
    {
        q.data[i] = q.data[j];
        i = j;
        j = (j + 1) % MAX_SIZE;
    }
    // 队尾指针前移
    q.rear = (q.rear - 1 + MAX_SIZE) % MAX_SIZE;
    cout << "联系人删除成功！" << endl;
}

// 8.展示所有联系人
void showAll(SqQueue& q)
{
    if (isEmpty(q))
    {
        cout << "暂无联系人信息！" << endl;
        return;
    }
    cout << "\n====所有联系人====" << endl;
    int i = q.front;
    while (i != q.rear)
    {
        cout << "姓名：" << q.data[i].name << "  电话：" << q.data[i].phone << endl;
        i = (i + 1) % MAX_SIZE;
    }
}

// 功能菜单
void menu()
{
    cout << "\n====循环队列通讯录系统====" << endl;
    cout << "1.增加联系人" << endl;
    cout << "2.删除联系人" << endl;
    cout << "3.修改联系人" << endl;
    cout << "4.查找联系人" << endl;
    cout << "5.展示所有联系人" << endl;
    cout << "0.退出系统" << endl;
    cout << "==========================" << endl;
    cout << "请输入操作序号：";
}

int main()
{
    SqQueue q;
    InitQueue(q);  // 初始化队列
    int op;        // 接收用户操作

    // 循环运行系统
    while (true)
    {
        menu();
        cin >> op;
        switch (op)
        {
        case 1: addContact(q); break;
        case 2: delContact(q); break;
        case 3: modifyContact(q); break;
        case 4: searchContact(q); break;
        case 5: showAll(q); break;
        case 0: cout << "系统正常退出！" << endl; return 0;
        default: cout << "输入无效，请重新选择！" << endl;
        }
    }
    return 0;
}
