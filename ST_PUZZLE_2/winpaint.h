#pragma once
#include "resource.h"
#include <Windows.h>
#include <cmath>
#define rgb RGB
#define delay Sleep				//delay(x) 延迟x毫秒 

//温馨提醒：
//
//	循环语句中，每次peekmsg来监听消息，否则有意想不到的事情发生(#^.^#)。
//	循环语句中，最后加上Sleep(1)或delay(1)来降低cpu占用率，否则打开任务管理器会发现(#^.^#)。
//	务必用WinMain函数，里面四个参数...
//	程序开始时，务必先调用initwin和showwin...
//	程序开始不必写beginpaint,程序结束也不必写endpaint
//	每次绘图都会绘制在内存DC上，并没有显示在显示屏上。需要flushpaint()才能显示在显示屏上
//	该头文件中有全局变量hwnd：窗口句柄；_isquit：窗口是否退出；_winw,_winh：窗口的宽和高
//	该头文件中有全局变量_ms：当前消息(#^.^#)
//	当你需要画大量像素点的时候，选择beginPdot。之后每次画点用Pdot。结束画点用endPdot。显示在屏幕上用flushpaint()。
//	在beginPdot和endPdot之间任何其他绘图函数都无效。只有Pdot有效。只有当flushPdot或endPdot之后才会绘制到内存DC上。
//	当你需要画少量像素点的时候，选择pdot。原因：代码短(#^.^#)

							//颜色常量
const COLORREF WHITE = rgb(255, 255, 255);
const COLORREF BLACK = rgb(0, 0, 0);
const COLORREF GRAY = rgb(127, 127, 127);
const COLORREF RED = rgb(255, 0, 0);
const COLORREF GREEN = rgb(0, 255, 0);
const COLORREF BLUE = rgb(0, 0, 255);
const COLORREF YELLOW = rgb(255, 255, 0);
const COLORREF PURPLE = rgb(255, 0, 255);
const COLORREF CYAN = rgb(0, 255, 255);
const COLORREF ORANGE = rgb(255, 127, 0);
const HANDLE hnullbrush = GetStockObject(NULL_BRUSH);
								//无画刷
const HANDLE hnullpen = GetStockObject(NULL_PEN);
								//无画笔

							//窗口变量
HWND hwnd;						//窗口句柄
bool _isquit = 0;				//窗口是否退出
bool _isinit = 0;
int _winw = 0;					//窗口绘图区域的宽
int _winh = 0;					//窗口绘图区域的高
HINSTANCE _hinst;				//窗口实例句柄
LPCSTR _title;					//窗口标题

							//消息变量
const int _msqmax = 10000;		
MSG _ms = { 0 };				//当前消息
MSG _msq[_msqmax];				//消息队列
MSG _msbuf[_msqmax];			//peekmsg后得到的消息组
int _msh=1, _mst=1, _msbufn=0;	

							//位图变量
HDC _hdc;						//设备描述表句柄
HDC _hDCMem;					//内存DC
int _w;							//位图的宽
int _h;							//位图的高
HBITMAP _hBMMem;				//位图句柄
HANDLE _hOld;					//旧位图句柄
BITMAPINFO _bInfo;				//位图信息
int _nLnBytes;					//位图每行字节数
BYTE* _pData;					//位图颜色信息
int _pDataSize;					//位图颜色信息数组的大小

							//绘图变量
COLORREF _tc;					//text颜色
HFONT _tfont;					//text字体
HPEN _dpen;						//线条风格
HBRUSH _fbrush;					//填充风格



const int _thmax = 100;	
HANDLE _th[_thmax];				//线程句柄
int _thi;						//线程句柄数量

													//窗口函数
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam);				
														//回调函数
ATOM MyRegisterClass(HINSTANCE hInstance);				//注册窗口
DWORD WINAPI _initwin(LPVOID lpParam);					//初始化窗口线程函数
void stopthread(int thi);								//停止线程
void newthread(LPTHREAD_START_ROUTINE t);				//新建线程
void initwin(HINSTANCE hInstance, int ww, int wh, LPCSTR title);
														//初始化窗口（包括注册，创建窗口）
void closewin(HWND hwnd);								//关闭窗口
void showwin(int nCmdshow);								//显示窗口
bool checkprev(HINSTANCE hPrev);						//判断是否有先前实例

													//消息函数
void sendmsg(LPMSG ms);									//发送消息
bool peekmsg();											//尝试取出消息
bool iskeydown();										//是否按键
bool iskeydown(int x);									//是否按键x
int getkeydown();										//获取按键消息
bool islbuttondown();									//是否按下鼠标左键
bool islbuttonup();										//是否松开鼠标左键
bool isrbuttondown();									//是否按下鼠标右键
bool isrbuttonup();										//是否松开鼠标右键
bool iswheelrollup();									//是否鼠标滑轮向上滑
bool iswheelrolldown();									//是否鼠标滑轮向下滑
bool ismousemove();										//鼠标是否移动

													//长宽、位置函数
int getborderw();										//得到窗口边框宽
int getborderh();										//得到窗口边框高
int getbordertitle();									//得到窗口标题高
int getmouseabsx();										//得到鼠标绝对坐标x
int getmouseabsy();										//得到鼠标绝对坐标y
int getposx(HWND hwnd);									//得到窗口左上角坐标x
int getposy(HWND hwnd);									//得到窗口左上角坐标y
int getmousex(HWND hwnd);								//得到鼠标在绘图区域中坐标x
int getmousey(HWND hwnd);								//得到鼠标在绘图区域中坐标y

													//绘图函数
void beginpaint(HWND hwnd, int W, int H);				//准备双缓冲区绘图
void flushpaint();										//绘制
void endpaint(HWND hwnd);								//结束绘制
void beginPdot(bool flag);								//准备开始画像素点(flag为1则清屏)
void Pdot(int x, int y, BYTE r, BYTE g, BYTE b);		//快速画像素点
void Pdot(int x, int y, COLORREF c);					//快速画像素点
void flushPdot();										//更新内存DC
void endPdot();											//结束绘制像素点
void pdot(int x, int y, COLORREF c);					//画像素点
void setd(int pstyle, int pwidth, COLORREF pc);			//设置线条风格
void setf(int bc);										//设置填充颜色
void setf(int bstyle, int bc);							//设置填充风格和颜色
void setf(HBITMAP hbm);									//设置填充图案
void sett(COLORREF tc, int h, int w, LPCSTR lpf);		//设置text颜色和字体
void dbar(int x1, int y1, int x2, int y2);				//画矩形外框
void dcircle(int x, int y, int r);						//画圆外框
void dellipse(int x1, int y1, int x2, int y2);			//画椭圆外框
void dpolygon(const POINT* apt, int cpt);				//画多边形外框
void dchord(int x1, int y1, int x2, int y2, int xx1, int yy1, int xx2, int yy2);
														//画弓形外框
void dpie(int x1, int y1, int x2, int y2, int xx1, int yy1, int xx2, int yy2);
														//画扇形外框
void droundbar(int x1, int y1, int x2, int y2, int w, int h);
														//画圆角矩形外框
void fbar(int x1, int y1, int x2, int y2);				//填充矩形
void fcircle(int x, int y, int r);						//填充圆
void fellipse(int x1, int y1, int x2, int y2);			//填充椭圆
void fpolygon(const POINT* apt, int cpt);				//填充多边形
void fchord(int x1, int y1, int x2, int y2, int xx1, int yy1, int xx2, int yy2);
														//填充弓形
void fpie(int x1, int y1, int x2, int y2, int xx1, int yy1, int xx2, int yy2);
														//填充扇形
void froundbar(int x1, int y1, int x2, int y2, int w, int h);
														//填充圆角矩形
void pbar(int x1, int y1, int x2, int y2);				//画矩形外框，并填充矩形
void pcircle(int x, int y, int r);						//画圆外框，并填充圆
void pellipse(int x1, int y1, int x2, int y2);			//画椭圆外框，并填充椭圆
void ppolygon(const POINT* apt, int cpt);				//画多边形外框，并填充多边形
void pchord(int x1, int y1, int x2, int y2, int xx1, int yy1, int xx2, int yy2);
														//画弓形，并填充弓形
void ppie(int x1, int y1, int x2, int y2, int xx1, int yy1, int xx2, int yy2);
														//画扇形，并填充扇形
void proundbar(int x1, int y1, int x2, int y2, int w, int h);
														//画圆角矩形，并填充圆角矩形
void pline(int x1, int y1, int x2, int y2);				//画线
void ptext(int x, int y, LPCSTR s);						//画text
void parc(int x1, int y1, int x2, int y2, int xx1, int yy1, int xx2, int yy2);
														//画弧
void pbezier(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
														//画贝赛尔曲线
void clearscreen(int c);								//清屏

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam) {
	switch (uMsg) {
	case WM_DESTROY: { exit(0); break; }
	case WM_CREATE: { beginpaint(hwnd, _winw, _winh); break; }
	case WM_CLOSE: { closewin(hwnd); break; }
	}
	return DefWindowProc(hwnd, uMsg, wparam, lparam);
}
ATOM MyRegisterClass(HINSTANCE hInstance) {
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = "DefaultClassName";
	wcex.hIconSm = LoadIcon(NULL, MAKEINTRESOURCE(IDI_ICON1));
	return RegisterClassEx(&wcex);
}
DWORD WINAPI _initwin(LPVOID lpParam) {
	if (!_isinit) {
		if (!MyRegisterClass(_hinst))
			MessageBox(NULL, "注册窗口失败", "错误", MB_OK);
		DWORD wsstyle = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE;
		RECT rect = { 0,0,_winw,_winh };
		AdjustWindowRectEx(&rect, wsstyle, 0, 0);
		hwnd = CreateWindowEx(
			NULL, "DefaultClassName", _title,
			wsstyle,
			CW_USEDEFAULT, CW_USEDEFAULT,
			rect.right - rect.left, rect.bottom - rect.top,
			NULL, NULL, _hinst, NULL
		);
		if (!hwnd) MessageBox(NULL, "创建窗口失败", "错误", MB_OK);
		_isinit = 1;
	}
	while (!_isquit) {
		MSG msg = { 0 };
		GetMessage(&msg, hwnd, 0, 0);
		sendmsg(&msg);
		_msq[_mst] = msg;
		_mst++; if (_mst >= _msqmax)_mst = 0;
	}
	return 0;
}
void stopthread(int thi) {
	TerminateThread(_th[thi], 0);
}
void newthread(LPTHREAD_START_ROUTINE t) {
	DWORD _tmp;
	_thi++;
	_thi=_thi % _thmax;
	stopthread(_thi);
	_th[_thi] = CreateThread(NULL, 0, t, NULL, 0, &_tmp);
}
void initwin(HINSTANCE hInstance, int ww,int wh,LPCSTR title) {
	_winw = ww; _winh = wh;
	_hinst = hInstance;
	_title = title;
	newthread(&_initwin);
	while (!_isinit)delay(1);
}
void closewin(HWND hwnd) { endpaint(hwnd); DestroyWindow(hwnd); _isquit = 1; }
void showwin(int nCmdshow) { ShowWindow(hwnd, nCmdshow); UpdateWindow(hwnd); }
bool checkprev(HINSTANCE hPrev) { if (hPrev) { MessageBox(NULL, "应用程序已在运行", "注意", MB_OK); return 1;  } else return 0; }
void sendmsg(LPMSG lpms) { TranslateMessage(lpms); DispatchMessage(lpms); }
bool peekmsg() {
	_msbufn = 0;
	if (_msh != _mst) {
		while (1) {
			_msbuf[++_msbufn] = _ms = _msq[_msh];
			_msh++; if (_msh >= _msqmax)_msh = 0;
			if ((_mst - _msh + _msqmax) % _msqmax <= 10)break;
		}
		return 1;
	}
	return 0;
}
bool iskeydown() {
	for (int i = 1; i <= _msbufn; ++i)if (_msbuf[i].message == WM_KEYDOWN)return 1;
	return 0;
}
bool iskeydown(int x) {
	for (int i = 1; i <= _msbufn; ++i)if (_msbuf[i].message == WM_KEYDOWN && _msbuf[i].wParam == x)return 1;
	return 0;
}
int getkeydown() {
	for (int i = 1; i <= _msbufn; ++i)if (_msbuf[i].message == WM_KEYDOWN)return _msbuf[i].wParam;
	return 0;
}
bool islbuttondown() { 
	for (int i = 1; i <= _msbufn; ++i)if (_msbuf[i].message == WM_LBUTTONDOWN)return 1;
	return 0;
}
bool islbuttonup() {

	for (int i = 1; i <= _msbufn; ++i)if (_msbuf[i].message == WM_LBUTTONUP)return 1;
	return 0;
}
bool isrbuttondown() {
	for (int i = 1; i <= _msbufn; ++i)if (_msbuf[i].message == WM_RBUTTONDOWN)return 1;
	return 0;
}
bool isrbuttonup() {
	for (int i = 1; i <= _msbufn; ++i)if (_msbuf[i].message == WM_RBUTTONUP)return 1;
	return 0;
}
bool iswheelrollup() {
	for (int i = 1; i <= _msbufn; ++i)if (_msbuf[i].message == WM_MOUSEWHEEL && (HIWORD(_msbuf[i].wParam) == 120))return 1;
	return 0;
}
bool iswheelrolldown() {
	for (int i = 1; i <= _msbufn; ++i)if (_msbuf[i].message == WM_MOUSEWHEEL && (HIWORD(_msbuf[i].wParam) == (WORD)-120))return 1;
	return 0;
}
bool ismousemove() {
	for (int i = 1; i <= _msbufn; ++i)if (_msbuf[i].message == WM_MOUSEMOVE)return 1;
	return 0;
}
int getborderw() { return GetSystemMetrics(SM_CXFRAME); }
int getborderh() { return GetSystemMetrics(SM_CYFRAME); }
int getbordertitle() { return GetSystemMetrics(SM_CYCAPTION); }
int getmouseabsx() { POINT p; GetCursorPos(&p);return p.x; }
int getmouseabsy() { POINT p; GetCursorPos(&p);return p.y; }
int getposx(HWND hwnd) { RECT r; GetWindowRect(hwnd, &r); return r.left; }
int getposy(HWND hwnd) { RECT r; GetWindowRect(hwnd, &r); return r.top; }
int getmousex(HWND hwnd) { return getmouseabsx() - getposx(hwnd) - getborderw(); }
int getmousey(HWND hwnd) { return getmouseabsy() - getposy(hwnd) - getborderh() - getbordertitle(); }
void beginpaint(HWND hwnd, int W,int H) {
	_w = W; _h = H;
	_hdc = GetDC(hwnd);
	_hDCMem = CreateCompatibleDC(_hdc);
	_hBMMem = CreateCompatibleBitmap(_hdc, W, H);
	_hOld = SelectObject(_hDCMem, _hBMMem);
	SetBkMode(_hDCMem, TRANSPARENT);
}
void flushpaint() {
	BitBlt(_hdc, 0, 0, _w, _h, _hDCMem, 0, 0, SRCCOPY);
}
void endpaint(HWND hwnd){
	flushpaint();
	SelectObject(_hDCMem, _hOld);
	DeleteObject(_hBMMem);
	DeleteDC(_hDCMem);
	ReleaseDC(hwnd, _hdc);
}
void beginPdot(bool flag = 0) {
	_bInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	_bInfo.bmiHeader.biWidth = _winw;
	_bInfo.bmiHeader.biHeight = _winh;
	_bInfo.bmiHeader.biPlanes = 1;
	_bInfo.bmiHeader.biBitCount = 24;
	_bInfo.bmiHeader.biCompression = BI_RGB;
	_bInfo.bmiHeader.biXPelsPerMeter = 0;
	_bInfo.bmiHeader.biYPelsPerMeter = 0;
	_bInfo.bmiHeader.biClrUsed = 0;
	_bInfo.bmiHeader.biClrImportant = 0;
	_nLnBytes = (_bInfo.bmiHeader.biWidth * 3 + 3) / 4 * 4;
	_pDataSize = _nLnBytes * _bInfo.bmiHeader.biHeight;
	_pData = new BYTE[_pDataSize];
	if (flag) memset(_pData, 0, _nLnBytes*abs(_bInfo.bmiHeader.biHeight)); 
	else GetDIBits(_hDCMem, _hBMMem, 0, _bInfo.bmiHeader.biHeight, _pData, &_bInfo, DIB_RGB_COLORS);
}
void Pdot(int x, int y, BYTE r, BYTE g, BYTE b) {
	int t = (_winh - 1 - y) * _nLnBytes + x * 3;
	*(_pData + t + 0) = b;
	*(_pData + t + 1) = g;
	*(_pData + t + 2) = r;
}
void Pdot(int x, int y, COLORREF c) {
	int t = (_winh - 1 - y) * _nLnBytes + x * 3;
	*(_pData + t + 0) = c >> 16 & 0xff;
	*(_pData + t + 1) = c >> 8 & 0xff;
	*(_pData + t + 2) = c >> 0 & 0xff;
}
void flushPdot() { SetDIBits(_hDCMem, _hBMMem, 0, _bInfo.bmiHeader.biHeight, _pData, &_bInfo, DIB_RGB_COLORS); }
void endPdot() { flushPdot(); delete[]_pData; }
void pdot(int x, int y, COLORREF c) { SetPixel(_hDCMem, x, y, c); }
void pline(int x1, int y1, int x2, int y2) { MoveToEx(_hDCMem, x1, y1, NULL); LineTo(_hDCMem, x2, y2); }
void setd(int pstyle, int pwidth, COLORREF pc) {
	DeleteObject(_dpen);
	_dpen=CreatePen(pstyle, pwidth, pc);
	SelectObject(_hDCMem, _dpen);
}
void setf(int bc) {
	DeleteObject(_fbrush);
	_fbrush = CreateSolidBrush(bc);
	SelectObject(_hDCMem, _fbrush);
}
void setf(int bstyle, int bc) {
	DeleteObject(_fbrush);
	if (bstyle==-1) _fbrush = CreateSolidBrush(bc);
	else _fbrush = CreateHatchBrush(bstyle, bc);
	SelectObject(_hDCMem, _fbrush);
}
void setf(HBITMAP hbm) {
	DeleteObject(_fbrush);
	_fbrush = CreatePatternBrush(hbm);
	SelectObject(_hDCMem, _fbrush);
}
void sett(COLORREF tc, int h, int w, LPCSTR lpf) {
	SetTextColor(_hDCMem, _tc = tc);
	DeleteObject(_tfont);
	HFONT hfont = CreateFont(h, w, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, lpf);
	SelectObject(_hDCMem, _tfont = hfont);
}
void dbar(int x1, int y1, int x2, int y2) {
	SelectObject(_hDCMem, hnullbrush);
	Rectangle(_hDCMem, x1, y1, x2, y2);
	SelectObject(_hDCMem, _fbrush);
}
void fbar(int x1, int y1, int x2, int y2) {
	SelectObject(_hDCMem, hnullpen);
	Rectangle(_hDCMem, x1, y1, x2, y2);
	SelectObject(_hDCMem, _dpen);
}
void pbar(int x1, int y1, int x2, int y2) { Rectangle(_hDCMem, x1, y1, x2, y2); }
void clearscreen(int c) {
	HBRUSH hbrush = CreateSolidBrush(c);
	SelectObject(_hDCMem, hbrush);
	SelectObject(_hDCMem, hnullpen);
	Rectangle(_hDCMem, 0, 0, _winw, _winh);
	SelectObject(_hDCMem, _fbrush);
	SelectObject(_hDCMem, _dpen);
	DeleteObject(hbrush);
}
void dcircle(int x, int y, int r) {
	SelectObject(_hDCMem, hnullbrush);
	Ellipse(_hDCMem, x - r, y - r, x + r, y + r);
	SelectObject(_hDCMem, _fbrush);
}
void fcircle(int x, int y, int r) {
	SelectObject(_hDCMem, hnullpen);
	Ellipse(_hDCMem, x - r, y - r, x + r, y + r);
	SelectObject(_hDCMem, _dpen);
}
void pcircle(int x, int y, int r) { Ellipse(_hDCMem, x - r, y - r, x + r, y + r); }
void dellipse(int x1, int y1, int x2, int y2) {
	SelectObject(_hDCMem, hnullbrush);
	Ellipse(_hDCMem, x1, y1, x2, y2);
	SelectObject(_hDCMem, _fbrush);
}
void fellipse(int x1, int y1, int x2, int y2) {
	SelectObject(_hDCMem, hnullpen);
	Ellipse(_hDCMem, x1, y1, x2, y2);
	SelectObject(_hDCMem, _dpen);
}
void pellipse(int x1, int y1, int x2, int y2) { Ellipse(_hDCMem, x1, y1, x2, y2); }
void dpolygon(const POINT* apt, int cpt) {
	SelectObject(_hDCMem, hnullbrush);
	Polygon(_hDCMem, apt, cpt);
	SelectObject(_hDCMem, _fbrush);
}
void fpolygon(const POINT* apt, int cpt) {
	SelectObject(_hDCMem, hnullpen);
	Polygon(_hDCMem, apt, cpt);
	SelectObject(_hDCMem, _dpen);
}
void ppolygon(const POINT* apt, int cpt) { Polygon(_hDCMem, apt, cpt); }
void parc(int x1, int y1, int x2, int y2, int xx1, int yy1, int xx2, int yy2) {
	Arc(_hDCMem, x1, y1, x2, y2, xx1, yy1, xx2, yy2);
}
void dchord(int x1, int y1, int x2, int y2, int xx1, int yy1, int xx2, int yy2) {
	SelectObject(_hDCMem, hnullbrush);
	Chord(_hDCMem, x1, y1, x2, y2, xx1, yy1, xx2, yy2);
	SelectObject(_hDCMem, _fbrush);
}
void fchord(int x1, int y1, int x2, int y2, int xx1, int yy1, int xx2, int yy2) {
	SelectObject(_hDCMem, hnullpen);
	Chord(_hDCMem, x1, y1, x2, y2, xx1, yy1, xx2, yy2);
	SelectObject(_hDCMem, _dpen);
}
void pchord(int x1,int y1,int x2,int y2,int xx1,int yy1,int xx2,int yy2) {
	Chord(_hDCMem, x1, y1, x2, y2, xx1, yy1, xx2, yy2);
}
void dpie(int x1, int y1, int x2, int y2, int xx1, int yy1, int xx2, int yy2) {
	SelectObject(_hDCMem, hnullbrush);
	Pie(_hDCMem, x1, y1, x2, y2, xx1, yy1, xx2, yy2);
	SelectObject(_hDCMem, _fbrush);
}
void fpie(int x1, int y1, int x2, int y2, int xx1, int yy1, int xx2, int yy2) {
	SelectObject(_hDCMem, hnullpen);
	Pie(_hDCMem, x1, y1, x2, y2, xx1, yy1, xx2, yy2);
	SelectObject(_hDCMem, _dpen);
}
void ppie(int x1, int y1, int x2, int y2, int xx1, int yy1, int xx2, int yy2) {
	Pie(_hDCMem, x1, y1, x2, y2, xx1, yy1, xx2, yy2);
}
void droundbar(int x1, int y1, int x2, int y2, int w, int h) {
	SelectObject(_hDCMem, hnullbrush);
	RoundRect(_hDCMem, x1, y1, x2, y2, w, h);
	SelectObject(_hDCMem, _fbrush);
}
void froundbar(int x1, int y1, int x2, int y2, int w, int h) {
	SelectObject(_hDCMem, hnullpen);
	RoundRect(_hDCMem, x1, y1, x2, y2, w, h);
	SelectObject(_hDCMem, _dpen);
}
void proundbar(int x1, int y1, int x2, int y2, int w, int h) {
	RoundRect(_hDCMem, x1, y1, x2, y2, w, h);
}
void ptext(int x, int y, LPCSTR s) { TextOut(_hDCMem, x, y, s, strlen(s)); }
void pbezier(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4) {
	POINT pt[] = { {x1,y1},{x2,y2},{x3,y3},{x4,y4} };
	PolyBezier(_hDCMem, pt, 4);
}