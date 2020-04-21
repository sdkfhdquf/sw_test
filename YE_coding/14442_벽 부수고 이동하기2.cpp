﻿//백준 https://www.acmicpc.net/problem/14442
//벽 부수고 이동하기 2
#include<iostream>
#include<string>
#include<queue>

using namespace std;

struct Dir {
	int x, y;
};

struct state {
	int x, y, wall; // 벽뚫 할수 있는가, 0 ~ 10
};

Dir dir[4] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
int N, M, K, res;
string arr[1000];
bool flag, visit[1000][1000][11]; // 벽뚫 여부까지 체크

int main() {
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	queue<state> q;
	q.push({ 0, 0, K });
	visit[0][0][K] = true;

	//BFS
	while (!q.empty()) {
		int qsize = q.size();

		while (qsize--) {
			int x = q.front().x;
			int y = q.front().y;
			int w = q.front().wall;
			q.pop();

			//탈출
			if (x == N - 1 && y == M - 1) {
				flag = true;
				break;
			}

			for (int i = 0; i < 4; i++) {
				int xx = x + dir[i].x;
				int yy = y + dir[i].y;
				int ww = w;

				if (xx < 0 || xx >= N || yy < 0 || yy >= M || visit[xx][yy][ww]) continue; // 좌표이탈 or 이미 방문

				if (arr[xx][yy] == '0') { // 벽이 없을때
					q.push({ xx, yy, ww });
					visit[xx][yy][ww] = true;
				}
				else if (arr[xx][yy] == '1' && ww) { // 벽이 있지만 뚫을 수 있을때
					ww -= 1;
					q.push({ xx, yy, ww });
					visit[xx][yy][ww] = true;
				}
			}
		}
		res++;
		if (flag) break;
	}

	if (!flag) cout << -1;
	else cout << res;

	return 0;
}