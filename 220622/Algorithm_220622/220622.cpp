#include <string>
#include <vector>

using namespace std;


// 4 1 4 1   ---
// 3 2 3 2
// ���� ���� ������ ���� ���� �ؾ߰ڴ�.
// ���� �� �ݶ�
// ���� ���� ���ϸ� �Ǵµ�
// ���δ� 1���� ����
// �̶� ���� ���̰� ���κ��� 2�� Ŀ�� ��.
// �׷��� ��ü ���α��̰� ���κ��� ���.

vector<int> solution(int brown, int yellow) {
    vector<int> answer;
    int temp = brown + yellow;
    int half_brown = brown / 2;
    int x = half_brown - 1, y = 1; // x+y = half_brown

    while (x > y - 1) {
        if ((x - 2) * y == yellow)
            break;
        x--;
        y++;
    }
    answer.push_back(x);
    answer.push_back(y + 2);

    return answer;
}