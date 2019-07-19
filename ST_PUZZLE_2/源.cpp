//
//	source.cpp
//	ST_PUZZLE
//
//	Created by Eden,Pjy on 17/5/18.
//	Copyright © 2018年 author. All rights reserved.
//
//
//	用Visual Studio 2017编译之前注意事项：
//	项目属性->c/c++->预处理器->预处理器定义 中添加：
//	_CRT_SECURE_NO_DEPRECATE
//	_CRT_NONSTDC_NO_DEPRECATE
//	项目属性->c/c++->代码生成->运行库 修改为 "多线程调试 (/MTd)"
//

//头文件
#include "winpaint.h"
#include "vector2.h"
#include <time.h>
#include <string>
#include <iostream>
using namespace std;
#define ref(i,x,y)for(int i=(x);i<=(y);++i)
#define def(i,x,y)for(int i=(x);i>=(y);--i)

const int ww = 768;
const int wh = 640;
const int gapwidth = 50;
const int gapheight = 30;

int brushr = 3;
int eraser = 10;
COLORREF brushcolor = rgb(94, 94, 78);
COLORREF backcolor = rgb(0, 92, 64);

const char* heiti = "黑体";
const char* courier_new = "Courier New";
const char* yahei = "微软雅黑";
const COLORREF white = rgb(255, 255, 255);
const COLORREF black = rgb(0, 0, 0);
const COLORREF darkgray = rgb(63, 63, 63);
const COLORREF lightgray = rgb(221, 221, 221);
const COLORREF gray = rgb(137, 137, 137);
const COLORREF lightlightblue = rgb(190, 250, 255);
const COLORREF lightblue = rgb(102, 204, 255);
const COLORREF lightlightgreen = rgb(200, 255, 200);
const COLORREF lightgreen = rgb(122, 255, 144);
const int blockcolor[3][2] = {
	{ gray,lightgray },
{ lightgreen,lightlightgreen },
{ lightblue,lightlightblue }
};
int sqr(int x) { return x * x; }

void flushmouse() { while (GetAsyncKeyState(VK_LBUTTON))delay(1); while (peekmsg())delay(1); }
void flushkey() { FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE)); }

char *constr(const char *S) {
	return const_cast<char*>(S);
}
string constr(int s) {
	if (s < 0)return "-" + constr(-s);
	if (s<10)return (string)((string)("") + char(s + 48));
	return constr(s / 10) + char(s % 10 + 48);
}


void midptext(int x1, int y1, int x2, int y2, int h, int w, LPCSTR str, COLORREF tc) {
	int x = (x1 + x2 - strlen(str)*w) / 2, y = (y1 + y2 - h) / 2;
	sett(tc, h, w, "黑体"); ptext(x, y, str);
}
void colorlighter(int&r, int&g, int&b) { if (r < 255)r++; if (g < 255)g++; if (b < 255)b++; }
void colordarker(int&r, int&g, int&b) { if (r > 0)r--; if (g > 0)g--; if (b > 0)b--; }
void textappear(int r, int g, int b, const char* s) {
	ref(i, 1, 150) {
		colorlighter(r, g, b);
		midptext(0, 0, _winw, _winh, 36, 18, s, rgb(r, g, b));
		flushpaint(); peekmsg(); delay(1);
	}
	ref(i, 1, 150) {
		colordarker(r, g, b);
		midptext(0, 0, _winw, _winh, 36, 18, s, rgb(r, g, b));
		flushpaint(); peekmsg(); delay(1);
	}
}
void openning() {
	int r = 0, g = 92, b = 64;
	clearscreen(backcolor);

	int tw = wh / 2 - wh / 5, th = tw;
	setd(0, 8, white); setf(rgb(52, 154, 205));
	pbar(ww / 2 - tw, wh / 2 - th, ww / 2, wh / 2);
	sett(white, th - th / 30, tw - tw / 3, constr(courier_new));
	ptext(ww / 2 - tw + tw / 6, tw - tw / 3 + th / 60, "S");
	setf(rgb(102, 204, 255));
	pbar(ww / 2 - tw, wh / 2, ww / 2, wh / 2 + th);
	pbar(ww / 2, wh / 2 - th, ww / 2 + tw, wh / 2);
	setf(rgb(2, 104, 155));
	pbar(ww / 2, wh / 2, ww / 2 + tw, wh / 2 + th);
	ptext(ww / 2 + tw / 6, wh / 2 + th / 60, "T");
	setf(darkgray);
	fcircle(ww / 2 + tw / 2, wh / 2 - th / 2, tw / 6);
	flushpaint();
	setd(0, 20, white);
	ref(i, ww / 2 - tw / 2, ww / 2 + tw / 2 - 1) {
		pline(i, wh / 2 - th / 2, i + 1, wh / 2 - th / 2);
		flushpaint(); peekmsg(); delay(1);
	}
	ref(i, wh / 2 - th / 2, wh / 2 + th / 2 - 1) {
		pline(ww / 2 + tw / 2, i, ww / 2 + tw / 2, i + 1);
		flushpaint(); peekmsg(); delay(1);
	}

	ref(i, 1, tw/2) {
		clearscreen(backcolor);
		setd(0, 8 * (tw - i) / tw + 1, white); setf(rgb(52, 154, 205));
		pbar(ww / 2 - tw, wh / 2 - th + i, ww / 2 - i, wh / 2);
		sett(white, (th - i) - (th - i) / 30, (tw - i) - (tw - i) / 3, constr(courier_new));
		ptext(ww / 2 - tw + (tw - i) / 6, wh / 2 - th + i + (th - i) / 60, "S");
		setf(rgb(102, 204, 255));
		pbar(ww / 2 - tw, wh / 2, ww / 2 - i, wh / 2 + th - i);
		pbar(ww / 2 - i, wh / 2 - th + i, ww / 2 + tw - 2 * i, wh / 2);
		setf(rgb(2, 104, 155));
		pbar(ww / 2 - i, wh / 2, ww / 2 + tw - 2 * i, wh / 2 + th - i);
		ptext(ww / 2 - i + (tw - i) / 6, wh / 2 + (th - i) / 60, "T");
		setf(darkgray);
		fcircle(ww / 2 + tw / 2 - i * 3 / 2, wh / 2 - th / 2 + i / 2, (tw - i) / 6);
		setd(0, 20 * (tw - i) / tw + 1, white);
		pline((ww - tw - i) / 2, (wh - th + i) / 2, (ww + tw - 3 * i) / 2, (wh - th + i) / 2);
		pline((ww + tw - 3 * i) / 2, (wh - th + i) / 2, (ww + tw - 3 * i) / 2, (wh + th - i) / 2);
		flushpaint();
		peekmsg(); delay(5+i/20);
	}
	delay(200);
	setf(backcolor);
	ref(i, ww / 2 + 10, ww) {
		midptext(ww / 2, 0, ww * 7 / 9, wh, wh / 10, wh / 20, "PUZZLE", rgb(255, 255, 255));
		fbar(i, 0, ww, wh);
		flushpaint();
		peekmsg(); delay(2);
	}
	def(i, ww, 0) {
		fbar(i, 0, ww, wh);
		flushpaint();
		peekmsg(); delay(1);
	}
	flushpaint();
	textappear(r, g, b, "Powered by Microsoft Visual Studio 2017");
	textappear(r, g, b, "Designed by Eden, Pjy in Feb/2018");
	textappear(r, g, b, "ST_PUZZLE Edition 2.0");
}


bool vis[21][21];
int n, m, mp[21][21], dir[21][21], fdir[21][21], gw, gh, sta[401][2], top, nowx, nowy;
int pt[ww + 1][wh + 1];
string hints, title;
struct xint { int x, y; }p[21][21];
const int d[5][2] = { { 0,0 },{ 1,0 },{ 0,1 },{ -1,0 },{ 0,-1 } };
const int fd[5] = { 0,3,4,1,2 };
const bool pd[5][5] = { { 0,0,0,0,0 },{ 0,0,1,0,1 },{ 0,1,0,1,0 },{ 0,0,1,0,1 },{ 0,1,0,1,0 } };
void drawrect(int x, int y, int tp) {
	setd(0, 8, white);
	if (tp == 1) setf(rgb(52, 154, 205)); else
		if (tp == 2)setf(rgb(2, 104, 155)); else
			setf(rgb(102, 204, 255));
	pbar(x, y, x + gw, y + gh);
	switch (tp) {
	case 1: {
		sett(white, gh - gh / 30, gw - gw / 3, constr(courier_new));
		ptext(x + gw / 6, y + gh / 60, "S");
		break;
	}
	case 2: {
		sett(white, gh - gh / 30, gw - gw / 3, constr(courier_new));
		ptext(x + gw / 6, y + gh / 60, "T");
		break;
	}
	case 3: {
		setf(darkgray);
		fcircle(x + gw / 2, y + gh / 2, min(gw, gh) / 6);
		break;
	}
	case 4: {
		setf(lightgray);
		fcircle(x + gw / 2, y + gh / 2, min(gw, gh) / 6);
		break;
	}
	case 5: {
		setd(0, 10, darkgray);
		pline(x + gw / 4, y + gh / 4, x + gw - gw / 4, y + gh - gh / 4); pline(x + gw - gw / 4, y + gh / 4, x + gw / 4, y + gh - gh / 4);
		setd(0, 4, gray);
		pline(x + gw / 4+2, y + gh / 4+2, x + gw - gw / 4-2, y + gh - gh / 4-2); pline(x + gw - gw / 4-2, y + gh / 4+2, x + gw / 4+2, y + gh - gh / 4-2);
		break;
	}
	case 6: {
		setf(darkgray); fcircle(x + gw / 2, y + gh / 2, min(gw, gh) / 6);
		setf(gray); fcircle(x + gw / 2, y + gh / 2, min(gw, gh) / 9);
		break;
	}
	}
}
void drawdir(int x, int y, int tp) {
	if (!tp)return;
	x += gw / 2, y += gh / 2;
	int X = x, Y = y;
	switch (tp) {
	case 1:Y += gh; break;
	case 2:X += gw; break;
	case 3:Y -= gh; break;
	case 4:X -= gw; break;
	}
	setd(0, 20, white); pline(x, y, X, Y);
}
void drawframe() {
	setd(0, 10, white); dbar(100, 100, ww - 100, wh - 100);
}
void drawcleaner() {
	POINT s = { getmousex(hwnd),getmousey(hwnd) };
	if (s.x >= ww - 210 && s.x <= ww - 115 && s.y >= wh - 80 && s.y <= wh - 30)
		setf(lightblue);
	else
		setf(lightlightblue);
	setd(0, 6, white);
	pbar(ww - 210, wh - 80, ww - 115, wh - 30);
	sett(darkgray, 30, 0, constr(heiti));
	ptext(ww - 200, wh - 70, "CLEAR");
}
void drawback() {
	POINT s = { getmousex(hwnd),getmousey(hwnd) };
	if (s.x >= 115 && s.x <= 195 && s.y >= 30 && s.y <= 80)
		setf(lightblue);
	else
		setf(lightlightblue);
	setd(0, 6, white);
	pbar(115, 30, 195, 80);
	sett(darkgray, 30, 0, constr(heiti));
	ptext(125, 40, "BACK");
}
void drawtitle() {
	sett(white, 50, 0, constr(yahei));
	ptext(ww - 300, 30, title.c_str());
}
void drawhints() {
	int sw = 62;
	sett(white, 20, 0, constr(yahei));
	for (int i = 0; i < hints.length(); i += sw) {
		string hint = "";
		for (int j = i; j < hints.length() && j < i + sw; ++j)hint = hint + hints[j];
		ptext(100, wh - 75 + (i / sw) * 15, hint.c_str());
	}
}
void drawdynamicpic() {
	drawback();
	drawcleaner();
	flushpaint();
}
void drawpic() {
	clearscreen(backcolor);
	gw = (ww - 200) / m;
	gh = (wh - 200) / n;
	ref(i, 1, n)ref(j, 1, m)drawrect((j - 1)*gw + 100, (i - 1)*gh + 100, mp[i][j]);
	ref(i, 1, n)ref(j, 1, m)drawdir((j - 1)*gw + 100, (i - 1)*gh + 100, dir[i][j]);

	beginPdot();
	ref(i, 0, ww - 1)ref(j, 0, wh - 1)if (pt[i][j])
		Pdot(i, j, brushcolor);
	endPdot();
	drawframe();
	drawtitle();
	drawhints();
	//flushpaint();
	drawdynamicpic();
}
void paintdot(int x, int y, int c, int r) {
	ref(i, x - r, x + r)if (i >= 0 && i < ww)
		ref(j, y - r, y + r)if (j >= 0 && j < wh)
		if (sqr(i - x) + sqr(j - y) <= r * r)pt[i][j] = c;
}
bool levelstart(int Fi, int Se, const char*str, string S) {
	memset(vis, 0, sizeof vis);
	memset(sta, 0, sizeof sta);
	memset(mp, 0, sizeof mp);
	memset(vis, 0, sizeof vis);
	memset(dir, 0, sizeof dir);
	memset(fdir, 0, sizeof fdir);
	memset(pt, 0, sizeof pt);
	top = 0;
	clearscreen(backcolor);
	flushmouse();
	flushkey();
	freopen(str, "r", stdin);
	scanf("%d%d", &n, &m);
	ref(i, 1, n)ref(j, 1, m) scanf("%d", &mp[i][j]);
	fclose(stdin);
	hints = S; title = "Level " + constr(Fi) + " - " + constr(Se);
	int posx = 0, posy = 0; top = 0;
	ref(i, 1, n)ref(j, 1, m)if (mp[i][j] == 1)posx = i, posy = j, sta[++top][0] = i, sta[top][1] = j;
	ref(i, 1, n)vis[i][0] = vis[i][m + 1] = 1;
	ref(i, 1, m)vis[0][i] = vis[n + 1][i] = 1;
	vis[posx][posy] = 1;
	if (!posx || !posy)return 0;
	bool lastlbutton = 0, lastrbutton = 0;
	vector2 Llbutton, Lrbutton; bool clickL = 0, clickR = 0;
	int times = 0;
	drawpic();
	while (1) {
		peekmsg();
		times++;
		if (mp[posx][posy] == 2) {
			delay(100);
			return 1;
		}
		bool isdraw = 0;
		bool isclick = islbuttondown();
		if (islbuttondown())clickL = 1;
		if (isrbuttondown())clickR = 1;
		if (islbuttonup())clickL = 0;
		if (isrbuttonup())clickR = 0;
		if (getmousex(hwnd) < 0 || getmousex(hwnd) > ww || getmousey(hwnd) < 0 || getmousey(hwnd) > wh)clickL = clickR = 0;
		if (clickL&&ismousemove()) {
			POINT ms = { getmousex(hwnd),getmousey(hwnd) };
			if (lastlbutton) {
				vector2 u = Llbutton, v = vector2(ms.x, ms.y), vu = v - u;
				int d = ceil(norm(vu)); vu = vu * (1.0 / d);
				ref(I, 1, d) {
					u = u + vu;
					paintdot(round(u.x), round(u.y), 1, brushr);
				}
				Llbutton = v;
			}
			lastlbutton = 1;
			Llbutton = vector2(ms.x, ms.y);
			paintdot(ms.x, ms.y, 1, brushr);
			isdraw = 1;
		}
		else {
			lastlbutton = 0;
			Llbutton = vector2(0, 0);
		}
		if (clickR&&ismousemove()) {
			POINT ms = { getmousex(hwnd),getmousey(hwnd) };
			if (lastrbutton) {
				vector2 u = Lrbutton, v = vector2(ms.x, ms.y), vu = v - u;
				int d = ceil(norm(vu)); vu = vu * (1.0 / d);
				ref(I, 1, d) {
					u = u + vu;
					paintdot(round(u.x), round(u.y), 0, eraser);
				}
				Lrbutton = v;
			}
			lastrbutton = 1;
			Lrbutton = vector2(ms.x, ms.y);
			paintdot(ms.x, ms.y, 0, eraser);
			isdraw = 1;
		}
		else {
			lastrbutton = 0;
			Lrbutton = vector2(0, 0);
		}
		if (isclick) {
			POINT s = { getmousex(hwnd),getmousey(hwnd) };
			if (s.x >= ww - 210 && s.x <= ww - 115 && s.y >= wh - 80 && s.y <= wh - 30) {
				ref(i, 0, ww)ref(j, 0, wh)pt[i][j] = 0;
				isdraw = 1;
			}
			if (s.x >= 115 && s.x <= 195 && s.y >= 30 && s.y <= 80) {
				return 0;
			}
		}
		char c = getkeydown();
		int x = 0;
		if (c == 27)return 0;
		if (c == 's' || c == 'S' || c == VK_DOWN)x = 1;
		if (c == 'd' || c == 'D' || c == VK_RIGHT)x = 2;
		if (c == 'w' || c == 'W' || c == VK_UP)x = 3;
		if (c == 'a' || c == 'A' || c == VK_LEFT)x = 4;
		if (c == VK_BACK) x = 5;
		if (x) {
			isdraw = 1;
			if (x == 5) { if (top > 1) vis[posx][posy] = 0, top--, posx = sta[top][0], posy = sta[top][1], dir[posx][posy] = 0; }
			else
			{
				bool flag = 1;
				if (mp[posx][posy] == 3)if (!pd[fdir[posx][posy]][x])flag = 0;
				if (mp[posx][posy] == 4)if (fd[fdir[posx][posy]] != x)flag = 0;
				if (flag) {
					int Posx = posx + d[x][0], Posy = posy + d[x][1];
					bool bo = 1;
					if (mp[Posx][Posy] == 2)
					{
						ref(i, 1, n)ref(j, 1, m)
							if ((mp[i][j] == 3 || mp[i][j] == 4 || mp[i][j] == 6) && vis[i][j] == 0) bo = 0;
					}
					if (bo && !vis[Posx][Posy] && mp[Posx][Posy] != 5) {
						dir[posx][posy] = x;
						posx = Posx, posy = Posy;
						vis[posx][posy] = 1;
						fdir[posx][posy] = fd[x];
						sta[++top][0] = posx, sta[top][1] = posy;
					}
				}
			}
		}
		if (isdraw)drawpic();
		drawdynamicpic();
		delay(1);
	}
}

void mkdir(const char* s) { CreateDirectory(s, NULL); }
bool mkfile(const char* s) {
	FILE *f = fopen(s, "r"); bool res = 0;
	if (f == NULL) f = fopen(s, "wt+"), res = 1;
	fclose(f); return res;
}
int _N, _M[21];
int userinf[21][31];
char fstr[21][31][31]; string gstr[21][31];
void readinfo() {
	freopen(".\\level\\levelinf.txt", "r", stdin);
	scanf("%d", &_N);
	for (int i = 0; i < _N; ++i) {
		scanf("%d", &_M[i]);
		for (int j = 0; j < _M[i]; ++j) {
			scanf("%s\n", &fstr[i][j]);
			getline(cin, gstr[i][j]);
		}
	}
	fclose(stdin);
	if (mkfile(".\\level\\levelnow.txt")) {
		freopen(".\\level\\levelnow.txt", "w", stdout);
		int tot = 0;
		for (int i = 0; i < _N; ++i)for (int j = 0; j < _M[i]; ++j) {
			if (tot < 5)++tot, printf("1 "); else printf("0 ");
		}
		fclose(stdout);
	}
	freopen(".\\level\\levelnow.txt", "r", stdin);
	for (int i = 0; i < _N; ++i)for (int j = 0; j < _M[i]; ++j)scanf("%d", &userinf[i][j]);
	fclose(stdin);
}
void saveinfo() {
	freopen(".\\level\\levelnow.txt", "w", stdout);
	ref(i, 0, _N - 1)ref(j, 0, _M[i] - 1)printf("%d ", userinf[i][j]);
	fclose(stdout);
}

struct group {
	int tx, ty; string lnm;
	COLORREF c0, c1;
	int x1, y1, x2, y2;
	void painta(POINT v = { 0,0 }) {
		setd(0, 6, white); setf(c0);
		pbar(x1 + v.x, y1 + v.y, x2 + v.x, y2 + v.y);
		sett(darkgray, 60, 0, constr(heiti));
		ptext(tx + v.x, ty + v.y, lnm.c_str());
	}
	void paintb(POINT v = { 0,0 }) {
		setd(0, 6, white); setf(c1);
		pbar(x1 + v.x, y1 + v.y, x2 + v.x, y2 + v.y);
		sett(darkgray, 60, 0, constr(heiti));
		ptext(tx + v.x, ty + v.y, lnm.c_str());
	}
}fg[1001];
pair<int, int> lxy[1001];
int ltot;
bool lst[1001];

void showcatalog() {
showcatalog_:
	ltot = 0;
	ref(i, 0, _N - 1)ref(j, 0, _M[i] - 1)
		lxy[ltot++] = make_pair(i, j);
	ref(i, 0, ltot - 1) {
		int ix = lxy[i].first, iy = lxy[i].second;
		fg[i].x1 = (i % 3) * (ww - gapwidth) / 3 + gapwidth;
		fg[i].x2 = (i % 3 + 1)*(ww - gapwidth) / 3;
		int bw = fg[i].x2 - fg[i].x1;
		int bh = 100;
		fg[i].y1 = i / 3 * (gapheight + bh) + gapheight;
		fg[i].y2 = (i / 3 + 1)*(gapheight + bh);
		int uif = userinf[ix][iy];
		fg[i].c0 = blockcolor[uif][0];
		fg[i].c1 = blockcolor[uif][1];
		fg[i].lnm = constr(ix) + "-" + constr(iy);
		fg[i].tx = (fg[i].x1 + fg[i].x2) / 2 - 15 * fg[i].lnm.length();
		fg[i].ty = (fg[i].y1 + fg[i].y2) / 2 - 30;
	}
	clearscreen(backcolor);
	flushmouse();
	flushkey();
	ref(i, 0, ltot - 1)fg[i].painta();
	flushpaint();
	memset(lst, 0, sizeof lst);
	int vy = 0, sy = 0, ti = 0;
	while (1) {
		++ti;
		peekmsg();
		if (iskeydown(VK_ESCAPE)) {
			closewin(hwnd); break;
		}
		POINT ms = { getmousex(hwnd),getmousey(hwnd) };
		if (iswheelrollup())vy += 5; else
			if (iswheelrolldown())vy -= 5;
		if (ti % 2 == 0) { if (vy > 0)vy--; if (vy < 0)vy++; }
		if (sy + vy < -800 || sy + vy > 0)vy = 0;
		if (vy != 0) {
			clearscreen(backcolor);
			sy += vy;
			ref(i, 0, ltot - 1) {
				if (lst[i])fg[i].paintb(POINT{ 0,sy });
				else fg[i].painta(POINT{ 0, sy });
			}
			flushpaint();
		}
		bool isclick = islbuttondown();
		ref(i, 0, ltot - 1) {
			bool nst = (fg[i].x1 <= ms.x&&ms.x <= fg[i].x2&&fg[i].y1 + sy <= ms.y&&ms.y <= fg[i].y2 + sy);
			if (nst^lst[i]) {
				lst[i] = nst;
				if (nst)fg[i].paintb(POINT{ 0,sy });
				else fg[i].painta(POINT{ 0, sy });
				flushpaint();
			}
			int ix = lxy[i].first, iy = lxy[i].second;
			if (nst&&isclick&&userinf[ix][iy] != 0) {

				while (levelstart(ix, iy, fstr[ix][iy], gstr[ix][iy])) {
					if (userinf[ix][iy] != 2) {
						userinf[ix][iy] = 2;
						ref(I, 0, _N)ref(J, 0, _M[I] - 1)if (userinf[I][J] == 0) {
							userinf[I][J] = 1; break;
						}
						saveinfo();
					}
					iy++; if (iy >= _M[ix])ix++, iy = 0;
					if (ix >= _N)break;
				}

				goto showcatalog_;
			}
		}
		delay(10);
	}
}

//WinMain函数
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevinstance,
	LPSTR lpCmdline,
	int nCmdshow
) {
	//初始化
	if (checkprev(hPrevinstance))return 0;
	initwin(hInstance, ww, wh, "ST_PUZZLE_2");
	showwin(nCmdshow);

	//主程序
	//openning();
	readinfo();
	showcatalog();
}